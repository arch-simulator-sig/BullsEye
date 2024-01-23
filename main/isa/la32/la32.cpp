#include "la32.hpp"
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
//
//


// Implementation of: class LA32Instance::Eval
namespace Jasse {

    LA32ExecOutcome LA32Instance::Eval()
    {
        //
        if (LA32InstancePreEvalEvent(*this).Fire(GetEventBusId()).IsCancelled())
            return (this->lastOutcome = { LA32ExecStatus::EMULATION_CANCELLED, ECANCELED });

        // Instruction fetch
        if (LA32InstructionPreFetchEvent(*this, arch.PC()).Fire(GetEventBusId()).IsCancelled())
            return (this->lastOutcome = { LA32ExecStatus::FETCH_EMULATION_CANCELLED, ECANCELED });

        memdata_t fetched;
        LA32MOPOutcome mopoutcome = memory->ReadInsn(arch.PC(), MOPW_WORD, &fetched);

        if (mopoutcome.status != LA32MOPStatus::MOP_SUCCESS)
        {
            LA32ExecOutcome rexec;

            switch (mopoutcome.status)
            {
                case LA32MOPStatus::MOP_ACCESS_FAULT:
                    rexec = { LA32ExecStatus::FETCH_ACCESS_FAULT, mopoutcome.error };
                    break;

                case LA32MOPStatus::MOP_ADDRESS_MISALIGNED:
                    rexec = { LA32ExecStatus::FETCH_ADDRESS_MISALIGNED, mopoutcome.error };
                    break;

                case LA32MOPStatus::MOP_DEVICE_ERROR:
                    rexec = { LA32ExecStatus::FETCH_DEVICE_ERROR, mopoutcome.error };
                    break;

                [[unlikely]] default:
                    // *NOTICE: +You can add your own custom MOP status handler here if necessary,
                    //          or in switch cases.
                    //          For default routine, this cause a direct fault.
                    SHOULD_NOT_REACH_HERE;
            }

            return (this->lastOutcome = rexec);
        }

        if (IsTraceEnabled())
        {
            if (tracers.HasFetchTracer())
            {
                LA32TraceEntity::Reference trace_ref = tracePool->Acquire();
                if (trace_ref.IsValid())
                {
                    LA32TracedInstructionFetch& trace_content
                        = trace_ref->SetContentType(LA32TraceContentLegacyType::INSTRUCTION_FETCH);

                    trace_content.insn  = fetched.data32;
                    trace_content.pc    = arch.PC();

                    if (tracers.HasPCTracer())
                        trace_content.SetTracedAddressSource(*trace_ref, tracers.GetPCTracer()->Get().Get());

                    if (tracers.HasMemoryTracer())
                    {
                        auto mem_trace = tracers.GetMemoryTracer()->Get(arch.PC());
                        if (mem_trace)
                            trace_content.SetTracedMemorySource(*trace_ref, mem_trace->get().Get());
                    }
                }

                tracers.GetFetchTracer()->Get().Append(trace_ref);

                this->lastFetchTrace = trace_ref;
            }
            else if (tracers.HasPCTracer())
            {
                this->lastFetchTrace = tracers.GetPCTracer()->Get().Get();
            }
        }

        LA32Instruction insn(
            LA32InstructionPostFetchEvent(*this, arch.PC(), fetched.data32).Fire(GetEventBusId()).GetInstruction());

        // Instruction decode
        if (LA32InstructionPreDecodeEvent(*this, arch.PC(), insn).Fire(GetEventBusId()).IsCancelled())
            return (this->lastOutcome = { LA32ExecStatus::DECODE_EMULATION_CANCELLED, ECANCELED });

        if (!decoders.Decode(insn))
            return (this->lastOutcome = { LA32ExecStatus::EXEC_NOT_DECODED, ECANCELED });

        if (!insn.GetExecutor())
            return (this->lastOutcome = { LA32ExecStatus::EXEC_NOT_IMPLEMENTED, ECANCELED });

        LA32InstructionPostDecodeEvent(*this, arch.PC(), insn).Fire(GetEventBusId());

        // Instruction execution
        if (LA32InstructionPreExecutionEvent(*this, arch.PC(), insn).Fire(GetEventBusId()).IsCancelled())
            return (this->lastOutcome = { LA32ExecStatus::EXEC_EMULATION_CANCELLED, ECANCELED });

        LA32ExecOutcome outcome_exec = insn.GetExecutor()(insn, *this);

        // - note: @see LA32ExecStatus
        ASSERT(outcome_exec.status != LA32ExecStatus::FETCH_ACCESS_FAULT);
        ASSERT(outcome_exec.status != LA32ExecStatus::FETCH_ADDRESS_MISALIGNED);
        ASSERT(outcome_exec.status != LA32ExecStatus::FETCH_DEVICE_ERROR);
        ASSERT(outcome_exec.status != LA32ExecStatus::EXEC_NOT_DECODED);
        ASSERT(outcome_exec.status != LA32ExecStatus::EXEC_NOT_IMPLEMENTED);

        outcome_exec =
            (LA32InstructionPostExecutionEvent(*this, arch.PC(), insn, outcome_exec).Fire(GetEventBusId())).GetOutcome();

        // PC iteration
        pc_t                            new_pc;
        LA32PCIterationEvent::Action    pc_action;

        if (outcome_exec.status == LA32ExecStatus::EXEC_SEQUENTIAL)
        {
            new_pc      = arch.PC() + 4;
            pc_action   = LA32PCIterationEvent::Action::SEQUENTIAL;
        }
        else if (outcome_exec.status == LA32ExecStatus::EXEC_BRANCH)
        {
            if (IsBranchTaken())
            {
                new_pc      = GetBranchTarget();
                pc_action   = LA32PCIterationEvent::Action::BRANCH_TAKEN;
            }
            else
            {
                new_pc      = arch.PC() + 4;
                pc_action   = LA32PCIterationEvent::Action::BRANCH_NOT_TAKEN;
            }
        }

        LA32PCIterationEvent(*this, arch.PC(), new_pc, pc_action).Fire(GetEventBusId());

        arch.SetPC(new_pc);

        lastOutcome = outcome_exec;

        //
        LA32InstancePostEvalEvent(*this).Fire(GetEventBusId());

        //
        return outcome_exec;
    }
}



// Implementation of: class LA32GPRs
namespace Jasse {
    /*
    arch32_t        gpr[SIZE];
    */

    LA32GPRs::LA32GPRs() noexcept
        : gpr   ()
    { }

    LA32GPRs::LA32GPRs(const LA32GPRs& obj) noexcept
        : gpr   ()
    { 
        std::copy(obj.gpr, obj.gpr + SIZE, this->gpr);
    }

    LA32GPRs::~LA32GPRs() noexcept
    { }

    int LA32GPRs::GetSize() const noexcept
    {
        return SIZE;
    }

    bool LA32GPRs::CheckBound(int index) const noexcept
    {
        return (index >= 0) && (index < GetSize());
    }

    arch32_t LA32GPRs::Get(int index) const noexcept
    {
        return index ? this->gpr[index] : 0;
    }

    void LA32GPRs::Set(int index, arch32_t value) noexcept
    {
        if (index)
            this->gpr[index] = value;
    }

    bool LA32GPRs::Compare(const LA32GPRs& obj) const noexcept
    {
        return std::equal(this->gpr, this->gpr + SIZE, obj.gpr);
    }

    void LA32GPRs::operator=(const LA32GPRs& obj) noexcept
    {
        std::copy(obj.gpr, obj.gpr + SIZE, this->gpr);
    }

    bool LA32GPRs::operator==(const LA32GPRs& obj) const noexcept
    {
        return Compare(obj);
    }

    bool LA32GPRs::operator!=(const LA32GPRs& obj) const noexcept
    {
        return !Compare(obj);
    }

    arch32_t& LA32GPRs::operator[](int index) noexcept
    {
        return index ? this->gpr[index] : (this->gpr[0] = 0);
    }

    arch32_t LA32GPRs::operator[](int index) const noexcept
    {
        return index ? this->gpr[index] : 0;
    }
}


// Implementation of: class LA32Architectural
namespace Jasse {
    /*
    pc_t            pc;

    LA32GPRs*       gprs;
    */

    LA32Architectural::LA32Architectural(pc_t startupPC) noexcept
        : pc    (startupPC)
        , gprs  (new LA32GPRs)
    { }

    LA32Architectural::LA32Architectural(const LA32Architectural& obj) noexcept
        : pc    (obj.pc)
        , gprs  (new LA32GPRs(*(obj.gprs)))
    { }

    LA32Architectural::~LA32Architectural() noexcept
    {
        delete this->gprs;
    }

    pc_t LA32Architectural::PC() const noexcept
    {
        return this->pc;
    }

    void LA32Architectural::SetPC(pc_t pc) noexcept
    {
        this->pc = pc;
    }

    LA32GPRs& LA32Architectural::GPRs() noexcept
    {
        return *(this->gprs);
    }

    const LA32GPRs& LA32Architectural::GPRs() const noexcept
    {
        return *(this->gprs);
    }

    LA32GPRs* LA32Architectural::SwapGPRs(LA32GPRs* obj) noexcept
    {
        std::swap(this->gprs, obj);
        return obj;
    }
}


// Implementation of: class LA32TracerContainer
namespace Jasse {
    /*
    LA32PCTracer*           pcTracer;

    LA32FetchTracer*        fetchTracer;

    LA32ExecutionTracer*    executionTracer;

    LA32GPRTracer*          gprTracer;

    LA32MemoryTracer*       memoryTracer;
    */

    LA32TracerContainer::LA32TracerContainer() noexcept
        : pcTracer          (nullptr)
        , fetchTracer       (nullptr)
        , executionTracer   (nullptr)
        , gprTracer         (nullptr)
        , memoryTracer      (nullptr)
    { }

    LA32TracerContainer::LA32TracerContainer(LA32PCTracer*          pcTracer,
                                             LA32FetchTracer*       fetchTracer,
                                             LA32ExecutionTracer*   executionTracer,
                                             LA32GPRTracer*         gprTracer,
                                             LA32MemoryTracer*      memoryTracer) noexcept
        : pcTracer          (pcTracer)
        , fetchTracer       (fetchTracer)
        , executionTracer   (executionTracer)
        , gprTracer         (gprTracer)
        , memoryTracer      (memoryTracer)
    { }

    LA32TracerContainer::LA32TracerContainer(LA32TracerContainer&& obj) noexcept
        : pcTracer          (obj.pcTracer)
        , fetchTracer       (obj.fetchTracer)
        , executionTracer   (obj.executionTracer)
        , gprTracer         (obj.gprTracer)
        , memoryTracer      (obj.memoryTracer)
    {
        obj.pcTracer        = nullptr;
        obj.fetchTracer     = nullptr;
        obj.executionTracer = nullptr;
        obj.gprTracer       = nullptr;
        obj.memoryTracer    = nullptr;
    }

    LA32TracerContainer::~LA32TracerContainer() noexcept
    {
        DestroyPCTracer();
        DestroyFetchTracer();
        DestroyExecutionTracer();
        DestroyGPRTracer();
        DestroyMemoryTracer();
    }

    bool LA32TracerContainer::HasPCTracer() const noexcept
    {
        return this->pcTracer != nullptr;
    }

    LA32PCTracer* LA32TracerContainer::GetPCTracer() noexcept
    {
        return this->pcTracer;
    }

    const LA32PCTracer* LA32TracerContainer::GetPCTracer() const noexcept
    {
        return this->pcTracer;
    }

    void LA32TracerContainer::DestroyPCTracer() noexcept
    {
        if (this->pcTracer)
        {
            delete this->pcTracer;
            this->pcTracer = nullptr;
        }
    }

    LA32PCTracer* LA32TracerContainer::SwapPCTracer(LA32PCTracer* obj) noexcept
    {
        std::swap(this->pcTracer, obj);
        return obj;
    }

    bool LA32TracerContainer::HasFetchTracer() const noexcept
    {
        return this->fetchTracer != nullptr;
    }

    LA32FetchTracer* LA32TracerContainer::GetFetchTracer() noexcept
    {
        return this->fetchTracer;
    }

    const LA32FetchTracer* LA32TracerContainer::GetFetchTracer() const noexcept
    {
        return this->fetchTracer;
    }

    void LA32TracerContainer::DestroyFetchTracer() noexcept
    {
        if (this->fetchTracer)
        {
            delete this->fetchTracer;
            this->fetchTracer = nullptr;
        }
    }

    LA32FetchTracer* LA32TracerContainer::SwapFetchTracer(LA32FetchTracer* obj) noexcept
    {
        std::swap(this->fetchTracer, obj);
        return obj;
    }

    bool LA32TracerContainer::HasExecutionTracer() const noexcept
    {
        return this->executionTracer != nullptr;
    }

    LA32ExecutionTracer* LA32TracerContainer::GetExecutionTracer() noexcept
    {
        return this->executionTracer;
    }

    const LA32ExecutionTracer* LA32TracerContainer::GetExecutionTracer() const noexcept
    {
        return this->executionTracer;
    }

    void LA32TracerContainer::DestroyExecutionTracer() noexcept
    {
        if (this->executionTracer)
        {
            delete this->executionTracer;
            this->executionTracer = nullptr;
        }
    }

    LA32ExecutionTracer* LA32TracerContainer::SwapExecutionTracer(LA32ExecutionTracer* obj) noexcept
    {
        std::swap(this->executionTracer, obj);
        return obj;
    }

    bool LA32TracerContainer::HasGPRTracer() const noexcept
    {
        return this->gprTracer != nullptr;
    }

    LA32GPRTracer* LA32TracerContainer::GetGPRTracer() noexcept
    {
        return this->gprTracer;
    }

    const LA32GPRTracer* LA32TracerContainer::GetGPRTracer() const noexcept
    {
        return this->gprTracer;
    }

    void LA32TracerContainer::DestroyGPRTracer() noexcept
    {
        if (this->gprTracer)
        {
            delete this->gprTracer;
            this->gprTracer = nullptr;
        }
    }

    LA32GPRTracer* LA32TracerContainer::SwapGPRTracer(LA32GPRTracer* obj) noexcept
    {
        std::swap(this->gprTracer, obj);
        return obj;
    }

    bool LA32TracerContainer::HasMemoryTracer() const noexcept
    {
        return this->memoryTracer != nullptr;
    }

    LA32MemoryTracer* LA32TracerContainer::GetMemoryTracer() noexcept
    {
        return this->memoryTracer;
    }

    const LA32MemoryTracer* LA32TracerContainer::GetMemoryTracer() const noexcept
    {
        return this->memoryTracer;
    }

    void LA32TracerContainer::DestroyMemoryTracer() noexcept
    {
        if (this->memoryTracer)
        {
            delete this->memoryTracer;
            this->memoryTracer = nullptr;
        }
    }

    LA32MemoryTracer* LA32TracerContainer::SwapMemoryTracer(LA32MemoryTracer* obj) noexcept
    {
        std::swap(this->memoryTracer, obj);
        return obj;
    }

    LA32TracerContainer& LA32TracerContainer::operator=(LA32TracerContainer&& obj) noexcept
    {
        if (this != &obj)
        {
            DestroyPCTracer();
            DestroyGPRTracer();
            DestroyMemoryTracer();

            this->pcTracer      = obj.pcTracer;
            this->gprTracer     = obj.gprTracer;
            this->memoryTracer  = obj.memoryTracer;

            obj.pcTracer        = nullptr;
            obj.gprTracer       = nullptr;
            obj.memoryTracer    = nullptr;
        }

        return *this;
    }
}


// Implementation of: class LA32Instance
namespace Jasse {
    /*
    LA32DecoderCollection       decoders;

    LA32Architectural           arch;

    LA32MemoryInterface*        memory;

    LA32TraceEntity::Pool*      tracePool;

    LA32TracerContainer         tracers;

    LA32ExecOutcome             lastOutcome;

    bool                        branchTaken;
    pc_t                        branchTarget;

    LA32TraceEntity::Reference  lastFetchTrace;

    unsigned int                eventBusId;
    */

    LA32Instance::LA32Instance(const LA32DecoderCollection&   decoders,
                               const LA32Architectural&     arch,
                               LA32MemoryInterface*         memory,
                               LA32TraceEntity::Pool*       tracePool,
                               LA32TracerContainer&&        tracers,
                               unsigned int                 eventBusId) noexcept
        : decoders          (decoders)
        , arch              (arch)
        , memory            (memory)
        , tracePool         (tracePool)
        , tracers           (std::move(tracers))
        , lastOutcome       ({ LA32ExecStatus::EXEC_SEQUENTIAL, 0 })
        , branchTaken       (false)
        , branchTarget      (0)
        , lastFetchTrace    ()
        , eventBusId        (eventBusId)
    { }

    LA32Instance::~LA32Instance() noexcept
    { 
        if (this->tracePool)
            delete this->tracePool;
    }

    bool LA32Instance::IsBranchTaken() const noexcept
    {
        return this->branchTaken;
    }

    void LA32Instance::SetBranchTaken(bool taken) noexcept
    {
        this->branchTaken = taken;
    }

    pc_t LA32Instance::GetBranchTarget() const noexcept
    {
        return this->branchTarget;
    }

    void LA32Instance::SetBranchTarget(bool taken, pc_t target) noexcept
    {
        this->branchTaken  = taken;
        this->branchTarget = target;
    }

    LA32DecoderCollection& LA32Instance::Decoders() noexcept
    {
        return this->decoders;
    }

    const LA32DecoderCollection& LA32Instance::Decoders() const noexcept
    {
        return this->decoders;
    }

    LA32Architectural& LA32Instance::Arch() noexcept
    {
        return this->arch;
    }

    const LA32Architectural& LA32Instance::Arch() const noexcept
    {
        return this->arch;
    }

    LA32MemoryInterface* LA32Instance::Memory() noexcept
    {
        return this->memory;
    }

    const LA32MemoryInterface* LA32Instance::Memory() const noexcept
    {
        return this->memory;
    }

    LA32TraceEntity::Pool& LA32Instance::TracePool() noexcept
    {
        return *(this->tracePool);
    }

    const LA32TraceEntity::Pool& LA32Instance::TracePool() const noexcept
    {
        return *(this->tracePool);
    }

    LA32TracerContainer& LA32Instance::Tracers() noexcept
    {
        return this->tracers;
    }

    const LA32TracerContainer& LA32Instance::Tracers() const noexcept
    {
        return this->tracers;
    }

    bool LA32Instance::HasTracePool() const noexcept
    {
        return this->tracePool != nullptr;
    }

    bool LA32Instance::IsTraceEnabled() const noexcept
    {
        return HasTracePool();
    }

    LA32MemoryInterface* LA32Instance::SwapMemory(LA32MemoryInterface* memory) noexcept
    {
        std::swap(this->memory, memory);
        return memory;
    }

    LA32TraceEntity::Pool* LA32Instance::SwapTracePool(LA32TraceEntity::Pool* trace_pool) noexcept
    {
        std::swap(this->tracePool, trace_pool);
        return trace_pool;
    }

    LA32ExecOutcome LA32Instance::GetLastOutcome() const noexcept
    {
        return this->lastOutcome;
    }

    LA32TraceEntity::Reference LA32Instance::GetLastFetchTrace() const noexcept
    {
        return this->lastFetchTrace;
    }

    unsigned int LA32Instance::GetEventBusId() const noexcept
    {
        return this->eventBusId;
    }

    void LA32Instance::SetEventBusId(unsigned int id) noexcept
    {
        this->eventBusId = id;
    }
}


// Implementation of: class LA32Instance::Builder
namespace Jasse {
    /*
    LA32Architectural       arch;

    LA32MemoryInterface*    memory;

    LA32DecoderCollection   decoders;

    bool                    traceEnabled;
    size_t                  traceUnit;
    size_t                  traceMaxFactor;

    bool                    pcTracerEnabled;
    size_t                  pcTracerDepth;

    bool                    fetchTracerEnabled;
    size_t                  fetchTracerDepth;

    bool                    executionTracerEnabled;
    size_t                  executionTracerDepth;

    bool                    gprTracerEnabled;
    size_t                  gprTracerDepth;

    bool                    memoryTracerEnabled;
    size_t                  memoryTracerDepth;
    size_t                  memoryTracerSize;

    unsigned int            eventBusId;
    */

    LA32Instance::Builder::Builder() noexcept
        : arch                      ()
        , memory                    (nullptr)
        , decoders                  ()
        , traceEnabled              (false)
        , traceUnit                 (0)
        , traceMaxFactor            (0)
        , pcTracerEnabled           (false)
        , pcTracerDepth             (0)
        , fetchTracerEnabled        (false)
        , fetchTracerDepth          (0)
        , executionTracerEnabled    (false)
        , executionTracerDepth      (0)
        , gprTracerEnabled          (false)
        , gprTracerDepth            (0)
        , memoryTracerEnabled       (false)
        , memoryTracerDepth         (0)
        , memoryTracerSize          (0)
        , eventBusId                (0)
    { }

    LA32Instance::Builder::~Builder() noexcept
    { }

    LA32Instance::Builder& LA32Instance::Builder::StartupPC(pc_t pc) noexcept
    {
        this->arch.SetPC(pc);
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::GPR(int index, arch32_t value) noexcept
    {
        this->arch.GPRs()[index] = value;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::GPRs(arch32_t value) noexcept
    {
        for (int i = 0; i < this->arch.GPRs().GetSize(); i++)
            this->arch.GPRs()[i] = value;

        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::Decoder(const LA32Decoder* decoder) noexcept
    {
        this->decoders.ForceAdd(decoder);
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::Decoder(std::initializer_list<const LA32Decoder*> decoders) noexcept
    {
        for (auto decoder : decoders)
            this->decoders.ForceAdd(decoder);

        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::Decoder(const LA32DecoderCollection& decoders) noexcept
    {
        this->decoders.ForceAddAll(decoders);
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::Memory(LA32MemoryInterface* memory) noexcept
    {
        this->memory = memory;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::EventBusId(unsigned int id) noexcept
    {
        this->eventBusId = id;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::EnableTrace(size_t unit, size_t maxFactor) noexcept
    {
        this->traceEnabled      = true;
        this->traceUnit         = unit;
        this->traceMaxFactor    = maxFactor;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::DisableTrace() noexcept
    {
        this->traceEnabled      = false;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::EnablePCTracer() noexcept
    {
        this->pcTracerEnabled   = true;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::EnablePCTracer(size_t depth) noexcept
    {
        this->pcTracerEnabled   = true;
        this->pcTracerDepth     = depth;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::DisablePCTracer() noexcept
    {
        this->pcTracerEnabled   = false;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::PCTracerDepth(size_t depth) noexcept
    {
        this->pcTracerDepth     = depth;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::EnableFetchTracer() noexcept
    {
        this->fetchTracerEnabled    = true;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::EnableFetchTracer(size_t depth) noexcept
    {
        this->fetchTracerEnabled    = true;
        this->fetchTracerDepth      = depth;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::DisableFetchTracer() noexcept
    {
        this->fetchTracerEnabled    = false;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::FetchTracerDepth(size_t depth) noexcept
    {
        this->fetchTracerDepth      = depth;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::EnableExecutionTracer() noexcept
    {
        this->executionTracerEnabled    = true;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::EnableExecutionTracer(size_t depth) noexcept
    {
        this->executionTracerEnabled    = true;
        this->executionTracerDepth      = depth;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::DisableExecutionTracer() noexcept
    {
        this->executionTracerEnabled    = false;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::ExecutionTracerDepth(size_t depth) noexcept
    {
        this->executionTracerDepth      = depth;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::EnableGPRTracer() noexcept
    {
        this->gprTracerEnabled  = true;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::EnableGPRTracer(size_t depth) noexcept
    {
        this->gprTracerEnabled  = true;
        this->gprTracerDepth    = depth;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::DisableGPRTracer() noexcept
    {
        this->gprTracerEnabled  = false;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::GPRTracerDepth(size_t depth) noexcept
    {
        this->gprTracerDepth    = depth;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::EnableMemoryTracer() noexcept
    {
        this->memoryTracerEnabled   = true;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::EnableMemoryTracer(size_t depth, size_t size) noexcept
    {
        this->memoryTracerEnabled   = true;
        this->memoryTracerDepth     = depth;
        this->memoryTracerSize      = size;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::DisableMemoryTracer() noexcept
    {
        this->memoryTracerEnabled   = false;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::MemoryTracerDepth(size_t depth) noexcept
    {
        this->memoryTracerDepth     = depth;
        return *this;
    }

    LA32Instance::Builder& LA32Instance::Builder::MemoryTracerSize(size_t size) noexcept
    {
        this->memoryTracerSize      = size;
        return *this;
    }

    arch32_t LA32Instance::Builder::GPR(int index) const noexcept
    {
        return this->arch.GPRs()[index];
    }

    LA32DecoderCollection& LA32Instance::Builder::Decoders() noexcept
    {
        return this->decoders;
    }

    const LA32DecoderCollection& LA32Instance::Builder::Decoders() const noexcept
    {
        return this->decoders;
    }

    LA32MemoryInterface*& LA32Instance::Builder::Memory() noexcept
    {
        return this->memory;
    }

    LA32MemoryInterface* LA32Instance::Builder::Memory() const noexcept
    {
        return this->memory;
    }

    bool LA32Instance::Builder::IsTraceEnabled() const noexcept
    {
        return this->traceEnabled;
    }

    void LA32Instance::Builder::SetTraceEnabled(bool enabled) noexcept
    {
        this->traceEnabled = enabled;
    }

    size_t LA32Instance::Builder::GetTraceUnit() const noexcept
    {
        return this->traceUnit;
    }

    void LA32Instance::Builder::SetTraceUnit(size_t unit) noexcept
    {
        this->traceUnit = unit;
    }

    size_t LA32Instance::Builder::GetTraceMaxFactor() const noexcept
    {
        return this->traceMaxFactor;
    }

    void LA32Instance::Builder::SetTraceMaxFactor(size_t maxFactor) noexcept
    {
        this->traceMaxFactor = maxFactor;
    }

    bool LA32Instance::Builder::IsPCTracerEnabled() const noexcept
    {
        return this->pcTracerEnabled;
    }

    void LA32Instance::Builder::SetPCTracerEnabled(bool enabled) noexcept
    {
        this->pcTracerEnabled = enabled;
    }

    size_t LA32Instance::Builder::GetPCTracerDepth() const noexcept
    {
        return this->pcTracerDepth;
    }

    void LA32Instance::Builder::SetPCTracerDepth(size_t depth) noexcept
    {
        this->pcTracerDepth = depth;
    }

    bool LA32Instance::Builder::IsFetchTracerEnabled() const noexcept
    {
        return this->fetchTracerEnabled;
    }

    void LA32Instance::Builder::SetFetchTracerEnabled(bool enabled) noexcept
    {
        this->fetchTracerEnabled = enabled;
    }

    size_t LA32Instance::Builder::GetFetchTracerDepth() const noexcept
    {
        return this->fetchTracerDepth;
    }

    void LA32Instance::Builder::SetFetchTracerDepth(size_t depth) noexcept
    {
        this->fetchTracerDepth = depth;
    }

    bool LA32Instance::Builder::IsExecutionTracerEnabled() const noexcept
    {
        return this->executionTracerEnabled;
    }

    void LA32Instance::Builder::SetExecutionTracerEnabled(bool enabled) noexcept
    {
        this->executionTracerEnabled = enabled;
    }

    size_t LA32Instance::Builder::GetExecutionTracerDepth() const noexcept
    {
        return this->executionTracerDepth;
    }

    void LA32Instance::Builder::SetExecutionTracerDepth(size_t depth) noexcept
    {
        this->executionTracerDepth = depth;
    }

    bool LA32Instance::Builder::IsGPRTracerEnabled() const noexcept
    {
        return this->gprTracerEnabled;
    }

    void LA32Instance::Builder::SetGPRTracerEnabled(bool enabled) noexcept
    {
        this->gprTracerEnabled = enabled;
    }

    size_t LA32Instance::Builder::GetGPRTracerDepth() const noexcept
    {
        return this->gprTracerDepth;
    }

    void LA32Instance::Builder::SetGPRTracerDepth(size_t depth) noexcept
    {
        this->gprTracerDepth = depth;
    }

    bool LA32Instance::Builder::IsMemoryTracerEnabled() const noexcept
    {
        return this->memoryTracerEnabled;
    }

    void LA32Instance::Builder::SetMemoryTracerEnabled(bool enabled) noexcept
    {
        this->memoryTracerEnabled = enabled;
    }

    size_t LA32Instance::Builder::GetMemoryTracerDepth() const noexcept
    {
        return this->memoryTracerDepth;
    }

    void LA32Instance::Builder::SetMemoryTracerDepth(size_t depth) noexcept
    {
        this->memoryTracerDepth = depth;
    }

    size_t LA32Instance::Builder::GetMemoryTracerSize() const noexcept
    {
        return this->memoryTracerSize;
    }

    void LA32Instance::Builder::SetMemoryTracerSize(size_t size) noexcept
    {
        this->memoryTracerSize = size;
    }

    unsigned int LA32Instance::Builder::GetEventBusId() const noexcept
    {
        return this->eventBusId;
    }

    void LA32Instance::Builder::SetEventBusId(unsigned int id) noexcept
    {
        this->eventBusId = id;
    }

    LA32Instance* LA32Instance::Builder::Build() const noexcept
    {
        // copy-on-build
        LA32Instance* instance = new LA32Instance(
            decoders,
            arch,
            memory,
            traceEnabled ? new LA32TraceEntity::Pool(traceUnit, traceMaxFactor) : nullptr,
            LA32TracerContainer(
                traceEnabled && pcTracerEnabled     ? new LA32PCTracer(pcTracerDepth)                           : nullptr,
                traceEnabled && fetchTracerEnabled  ? new LA32FetchTracer(fetchTracerDepth)                     : nullptr,
                traceEnabled && executionTracerEnabled ? new LA32ExecutionTracer(executionTracerDepth)         : nullptr,
                traceEnabled && gprTracerEnabled    ? new LA32GPRTracer(gprTracerDepth)                         : nullptr,
                traceEnabled && memoryTracerEnabled ? new LA32MemoryTracer(memoryTracerDepth, memoryTracerSize) : nullptr
            ),
            eventBusId
        );

        return instance;
    }
}
