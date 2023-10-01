#pragma once
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
//
//

#include <algorithm>
#include <initializer_list>

#include "jasse.hpp"

#include "base/la32def.hpp"
#include "base/la32code.hpp"
#include "base/la32decode.hpp"
#include "base/la32mem.hpp"
#include "base/la32event.hpp"
#include "base/la32trace.hpp"


namespace Jasse {

    // LA32 General Purpose Registers container
    class LA32GPRs {
    private:
        static constexpr int    SIZE    = LA32_ARCH_REG_COUNT;

        arch32_t        gpr[SIZE];

    public:
        LA32GPRs() noexcept;
        LA32GPRs(const LA32GPRs& obj) noexcept;
        ~LA32GPRs() noexcept;

        int             GetSize() const noexcept;
        bool            CheckBound(int index) const noexcept;

        arch32_t        Get(int index) const noexcept;
        void            Set(int index, arch32_t value) noexcept;

        bool            Compare(const LA32GPRs& obj) const noexcept;

        void            operator=(const LA32GPRs& obj) noexcept;

        bool            operator==(const LA32GPRs& obj) const noexcept;
        bool            operator!=(const LA32GPRs& obj) const noexcept;

        arch32_t&       operator[](int index) noexcept;
        arch32_t        operator[](int index) const noexcept;
    };

    
    // LA32 Architectural State and Interface
    class LA32Architectural {
    private:
        pc_t            pc;

        LA32GPRs*       gprs;

    public:
        LA32Architectural(pc_t startupPC = 0) noexcept;
        LA32Architectural(const LA32Architectural& obj) noexcept;
        ~LA32Architectural() noexcept;

        pc_t            PC() const noexcept;
        void            SetPC(pc_t pc) noexcept;

        LA32GPRs&       GPRs() noexcept;
        const LA32GPRs& GPRs() const noexcept;

        // *NOTICE: When the architectural instance (LA32Architectural) was finalized, 
        //          the GPR container instance (LA32GPRs) would be finalized too.
        //
        //          Performing ::SwapGPRs(LA32GPRs*) operation means that granting this 
        //          architectural instance the ONLY role of deallocator of the GPR container
        //          instance on call parameter. Furthermore, the GPR container instance on return
        //          value should be deallocated by the caller when necessary.
        //
        //          The GPR container instance should be allocated by operator 'new', coupling
        //          the 'delete' operation on deconstruction.
        //
        //          It's not recommended to swap GPR container in a concurrent procedure.
        [[nodiscard("potential memory leak : caller swap object management")]]
        LA32GPRs*       SwapGPRs(LA32GPRs* obj) noexcept;
    };


    // LA32 Tracers
    using LA32GPRTracer         = LA32GPRTracerSubtrate<LA32TraceHistoryManagement::Pretouch>;

    using LA32MemoryTracer      = LA32MemoryTracerSubtrate<LA32TraceHistoryManagement::Pretouch>;

    using LA32PCTracer          = LA32PCTracerSubtrate;


    // LA32 Tracer Container
    class LA32TracerContainer {
    private:
        LA32PCTracer*       pcTracer;

        LA32GPRTracer*      gprTracer;

        LA32MemoryTracer*   memoryTracer;

    public:
        LA32TracerContainer() noexcept;
        LA32TracerContainer(LA32TracerContainer&& obj) noexcept;
        ~LA32TracerContainer() noexcept;

        LA32TracerContainer(LA32PCTracer*       pcTracer,
                            LA32GPRTracer*      gprTracer,
                            LA32MemoryTracer*   memoryTracer) noexcept;

        LA32TracerContainer(const LA32TracerContainer&) = delete;

        //
        bool                    HasPCTracer() const noexcept;
        LA32PCTracer*           GetPCTracer() noexcept;
        const LA32PCTracer*     GetPCTracer() const noexcept;
        void                    DestroyPCTracer() noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        LA32PCTracer*           SwapPCTracer(LA32PCTracer* obj) noexcept;

        //
        bool                    HasGPRTracer() const noexcept;
        LA32GPRTracer*          GetGPRTracer() noexcept;
        const LA32GPRTracer*    GetGPRTracer() const noexcept;
        void                    DestroyGPRTracer() noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        LA32GPRTracer*          SwapGPRTracer(LA32GPRTracer* obj) noexcept;

        //
        bool                    HasMemoryTracer() const noexcept;
        LA32MemoryTracer*       GetMemoryTracer() noexcept;
        const LA32MemoryTracer* GetMemoryTracer() const noexcept;
        void                    DestroyMemoryTracer() noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        LA32MemoryTracer*       SwapMemoryTracer(LA32MemoryTracer* obj) noexcept;

        //
        LA32TracerContainer&    operator=(const LA32TracerContainer& obj) = delete;
        LA32TracerContainer&    operator=(LA32TracerContainer&& obj) noexcept;
    };


    // LA32 Instance
    class LA32Instance {
    public:
        class Builder;
    
    private:
        LA32DecoderCollection       decoders;

        LA32Architectural           arch;

        LA32MemoryInterface*        memory;

        LA32TraceEntity::Pool*      tracePool;

        LA32TracerContainer         tracers;

        LA32ExecOutcome             lastOutcome;

        bool                        branchTaken;
        pc_t                        branchTarget;

        LA32TraceEntity::Reference  lastFetchTrace;

    public:
        LA32Instance(const LA32DecoderCollection&   decoders,
                       const LA32Architectural&     arch,
                       LA32MemoryInterface*         memory,
                       LA32TraceEntity::Pool*       tracePool,
                       LA32TracerContainer&&        tracers) noexcept;

        LA32Instance() = delete;
        LA32Instance(const LA32Instance&) = delete;

        ~LA32Instance() noexcept;

        bool                            IsBranchTaken() const noexcept;
        void                            SetBranchTaken(bool taken) noexcept;
        pc_t                            GetBranchTarget() const noexcept;
        void                            SetBranchTarget(bool taken, pc_t target) noexcept;

        LA32DecoderCollection&          Decoders() noexcept;
        const LA32DecoderCollection&    Decoders() const noexcept;

        LA32Architectural&              Arch() noexcept;
        const LA32Architectural&        Arch() const noexcept;

        LA32MemoryInterface*            Memory() noexcept;
        const LA32MemoryInterface*      Memory() const noexcept;

        LA32TraceEntity::Pool&          TracePool() noexcept;
        const LA32TraceEntity::Pool&    TracePool() const noexcept;

        LA32TracerContainer&            Tracers() noexcept;
        const LA32TracerContainer&      Tracers() const noexcept;

        bool                            HasTracePool() const noexcept;
        bool                            IsTraceEnabled() const noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        LA32MemoryInterface*            SwapMemory(LA32MemoryInterface* memory) noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        LA32TraceEntity::Pool*          SwapTracePool(LA32TraceEntity::Pool* trace_pool) noexcept;

        LA32ExecOutcome                 Eval();

        LA32ExecOutcome                 GetLastOutcome() const noexcept;

        LA32TraceEntity::Reference      GetLastFetchTrace() const noexcept;
        
        void                            operator=(const LA32Instance&) = delete;
    };

    // LA32 Instance Builder
    class LA32Instance::Builder {
    private:
        LA32Architectural       arch;

        LA32MemoryInterface*    memory;

        LA32DecoderCollection   decoders;

        bool                    traceEnabled;
        size_t                  traceUnit;
        size_t                  traceMaxFactor;

        bool                    pcTracerEnabled;
        size_t                  pcTracerDepth;

        bool                    gprTracerEnabled;
        size_t                  gprTracerDepth;

        bool                    memoryTracerEnabled;
        size_t                  memoryTracerDepth;
        size_t                  memoryTracerSize;

    public:
        Builder() noexcept;
        ~Builder() noexcept;

        Builder&                        StartupPC(pc_t pc) noexcept;

        Builder&                        GPR(int index, arch32_t value) noexcept;
        Builder&                        GPRs(arch32_t value) noexcept;

        Builder&                        Decoder(const LA32Decoder* decoder) noexcept;
        Builder&                        Decoder(std::initializer_list<const LA32Decoder*> decoders) noexcept;
        Builder&                        Decoder(const LA32DecoderCollection& decoders) noexcept;

        Builder&                        Memory(LA32MemoryInterface* memory) noexcept;

        //
        Builder&                        EnableTrace(size_t unit, size_t maxFactor) noexcept;
        Builder&                        DisableTrace() noexcept;

        //
        Builder&                        EnablePCTracer() noexcept;
        Builder&                        EnablePCTracer(size_t depth) noexcept;
        Builder&                        DisablePCTracer() noexcept;

        Builder&                        PCTracerDepth(size_t depth) noexcept;

        //
        Builder&                        EnableGPRTracer() noexcept;
        Builder&                        EnableGPRTracer(size_t depth) noexcept;
        Builder&                        DisableGPRTracer() noexcept;

        Builder&                        GPRTracerDepth(size_t depth) noexcept;

        //
        Builder&                        EnableMemoryTracer() noexcept;
        Builder&                        EnableMemoryTracer(size_t depth, size_t size) noexcept;
        Builder&                        DisableMemoryTracer() noexcept;

        Builder&                        MemoryTracerDepth(size_t depth) noexcept;
        Builder&                        MemoryTracerSize(size_t size) noexcept;

        //
        arch32_t                        GPR(int index) const noexcept;
        LA32DecoderCollection&          Decoders() noexcept;
        const LA32DecoderCollection&    Decoders() const noexcept;
        LA32MemoryInterface*&           Memory() noexcept;
        LA32MemoryInterface*            Memory() const noexcept;

        bool                            IsTraceEnabled() const noexcept;
        void                            SetTraceEnabled(bool enabled) noexcept;

        size_t                          GetTraceUnit() const noexcept;
        void                            SetTraceUnit(size_t unit) noexcept;
        size_t                          GetTraceMaxFactor() const noexcept;
        void                            SetTraceMaxFactor(size_t maxFactor) noexcept;

        bool                            IsPCTracerEnabled() const noexcept;
        void                            SetPCTracerEnabled(bool enabled) noexcept;
        size_t                          GetPCTracerDepth() const noexcept;
        void                            SetPCTracerDepth(size_t depth) noexcept;

        bool                            IsGPRTracerEnabled() const noexcept;
        void                            SetGPRTracerEnabled(bool enabled) noexcept;
        size_t                          GetGPRTracerDepth() const noexcept;
        void                            SetGPRTracerDepth(size_t depth) noexcept;

        bool                            IsMemoryTracerEnabled() const noexcept;
        void                            SetMemoryTracerEnabled(bool enabled) noexcept;
        size_t                          GetMemoryTracerDepth() const noexcept;
        void                            SetMemoryTracerDepth(size_t depth) noexcept;
        size_t                          GetMemoryTracerSize() const noexcept;
        void                            SetMemoryTracerSize(size_t size) noexcept;

        //
        LA32Instance*                   Build() const noexcept;
    };
}


// Implementation of: class LA32GPRs
namespace Jasse {
    /*
    arch32_t        gpr[SIZE];
    */

    inline LA32GPRs::LA32GPRs() noexcept
        : gpr   ()
    { }

    inline LA32GPRs::LA32GPRs(const LA32GPRs& obj) noexcept
        : gpr   ()
    { 
        std::copy(obj.gpr, obj.gpr + SIZE, this->gpr);
    }

    inline LA32GPRs::~LA32GPRs() noexcept
    { }

    inline int LA32GPRs::GetSize() const noexcept
    {
        return SIZE;
    }

    inline bool LA32GPRs::CheckBound(int index) const noexcept
    {
        return (index >= 0) && (index < GetSize());
    }

    inline arch32_t LA32GPRs::Get(int index) const noexcept
    {
        return index ? this->gpr[index] : 0;
    }

    inline void LA32GPRs::Set(int index, arch32_t value) noexcept
    {
        if (index)
            this->gpr[index] = value;
    }

    inline bool LA32GPRs::Compare(const LA32GPRs& obj) const noexcept
    {
        return std::equal(this->gpr, this->gpr + SIZE, obj.gpr);
    }

    inline void LA32GPRs::operator=(const LA32GPRs& obj) noexcept
    {
        std::copy(obj.gpr, obj.gpr + SIZE, this->gpr);
    }

    inline bool LA32GPRs::operator==(const LA32GPRs& obj) const noexcept
    {
        return Compare(obj);
    }

    inline bool LA32GPRs::operator!=(const LA32GPRs& obj) const noexcept
    {
        return !Compare(obj);
    }

    inline arch32_t& LA32GPRs::operator[](int index) noexcept
    {
        return index ? this->gpr[index] : (this->gpr[0] = 0);
    }

    inline arch32_t LA32GPRs::operator[](int index) const noexcept
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

    inline LA32Architectural::LA32Architectural(pc_t startupPC) noexcept
        : pc    (startupPC)
        , gprs  (new LA32GPRs)
    { }

    inline LA32Architectural::LA32Architectural(const LA32Architectural& obj) noexcept
        : pc    (obj.pc)
        , gprs  (new LA32GPRs(*(obj.gprs)))
    { }

    inline LA32Architectural::~LA32Architectural() noexcept
    {
        delete this->gprs;
    }

    inline pc_t LA32Architectural::PC() const noexcept
    {
        return this->pc;
    }

    inline void LA32Architectural::SetPC(pc_t pc) noexcept
    {
        this->pc = pc;
    }

    inline LA32GPRs& LA32Architectural::GPRs() noexcept
    {
        return *(this->gprs);
    }

    inline const LA32GPRs& LA32Architectural::GPRs() const noexcept
    {
        return *(this->gprs);
    }

    inline LA32GPRs* LA32Architectural::SwapGPRs(LA32GPRs* obj) noexcept
    {
        std::swap(this->gprs, obj);
        return obj;
    }
}


// Implementation of: class LA32TracerContainer
namespace Jasse {
    /*
    LA32PCTracer*       pcTracer;

    LA32GPRTracer*      gprTracer;

    LA32MemoryTracer*   memoryTracer;
    */

    inline LA32TracerContainer::LA32TracerContainer() noexcept
        : pcTracer      (nullptr)
        , gprTracer     (nullptr)
        , memoryTracer  (nullptr)
    { }

    inline LA32TracerContainer::LA32TracerContainer(LA32PCTracer*       pcTracer,
                                             LA32GPRTracer*      gprTracer,
                                             LA32MemoryTracer*   memoryTracer) noexcept
        : pcTracer      (pcTracer)
        , gprTracer     (gprTracer)
        , memoryTracer  (memoryTracer)
    { }

    inline LA32TracerContainer::LA32TracerContainer(LA32TracerContainer&& obj) noexcept
        : pcTracer      (obj.pcTracer)
        , gprTracer     (obj.gprTracer)
        , memoryTracer  (obj.memoryTracer)
    {
        obj.pcTracer        = nullptr;
        obj.gprTracer       = nullptr;
        obj.memoryTracer    = nullptr;
    }

    inline LA32TracerContainer::~LA32TracerContainer() noexcept
    {
        DestroyPCTracer();
        DestroyGPRTracer();
        DestroyMemoryTracer();
    }

    inline bool LA32TracerContainer::HasPCTracer() const noexcept
    {
        return this->pcTracer != nullptr;
    }

    inline LA32PCTracer* LA32TracerContainer::GetPCTracer() noexcept
    {
        return this->pcTracer;
    }

    inline const LA32PCTracer* LA32TracerContainer::GetPCTracer() const noexcept
    {
        return this->pcTracer;
    }

    inline void LA32TracerContainer::DestroyPCTracer() noexcept
    {
        if (this->pcTracer)
        {
            delete this->pcTracer;
            this->pcTracer = nullptr;
        }
    }

    inline LA32PCTracer* LA32TracerContainer::SwapPCTracer(LA32PCTracer* obj) noexcept
    {
        std::swap(this->pcTracer, obj);
        return obj;
    }

    inline bool LA32TracerContainer::HasGPRTracer() const noexcept
    {
        return this->gprTracer != nullptr;
    }

    inline LA32GPRTracer* LA32TracerContainer::GetGPRTracer() noexcept
    {
        return this->gprTracer;
    }

    inline const LA32GPRTracer* LA32TracerContainer::GetGPRTracer() const noexcept
    {
        return this->gprTracer;
    }

    inline void LA32TracerContainer::DestroyGPRTracer() noexcept
    {
        if (this->gprTracer)
        {
            delete this->gprTracer;
            this->gprTracer = nullptr;
        }
    }

    inline LA32GPRTracer* LA32TracerContainer::SwapGPRTracer(LA32GPRTracer* obj) noexcept
    {
        std::swap(this->gprTracer, obj);
        return obj;
    }

    inline bool LA32TracerContainer::HasMemoryTracer() const noexcept
    {
        return this->memoryTracer != nullptr;
    }

    inline LA32MemoryTracer* LA32TracerContainer::GetMemoryTracer() noexcept
    {
        return this->memoryTracer;
    }

    inline const LA32MemoryTracer* LA32TracerContainer::GetMemoryTracer() const noexcept
    {
        return this->memoryTracer;
    }

    inline void LA32TracerContainer::DestroyMemoryTracer() noexcept
    {
        if (this->memoryTracer)
        {
            delete this->memoryTracer;
            this->memoryTracer = nullptr;
        }
    }

    inline LA32MemoryTracer* LA32TracerContainer::SwapMemoryTracer(LA32MemoryTracer* obj) noexcept
    {
        std::swap(this->memoryTracer, obj);
        return obj;
    }

    inline LA32TracerContainer& LA32TracerContainer::operator=(LA32TracerContainer&& obj) noexcept
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
    */

    inline LA32Instance::LA32Instance(const LA32DecoderCollection&   decoders,
                               const LA32Architectural&     arch,
                               LA32MemoryInterface*         memory,
                               LA32TraceEntity::Pool*       tracePool,
                               LA32TracerContainer&&        tracers) noexcept
        : decoders          (decoders)
        , arch              (arch)
        , memory            (memory)
        , tracePool         (tracePool)
        , tracers           (std::move(tracers))
        , lastOutcome       ({ LA32ExecStatus::EXEC_SEQUENTIAL, 0 })
        , branchTaken       (false)
        , branchTarget      (0)
        , lastFetchTrace    ()
    { }

    inline LA32Instance::~LA32Instance() noexcept
    { 
        if (this->tracePool)
            delete this->tracePool;
    }

    inline bool LA32Instance::IsBranchTaken() const noexcept
    {
        return this->branchTaken;
    }

    inline void LA32Instance::SetBranchTaken(bool taken) noexcept
    {
        this->branchTaken = taken;
    }

    inline pc_t LA32Instance::GetBranchTarget() const noexcept
    {
        return this->branchTarget;
    }

    inline void LA32Instance::SetBranchTarget(bool taken, pc_t target) noexcept
    {
        this->branchTaken  = taken;
        this->branchTarget = target;
    }

    inline LA32DecoderCollection& LA32Instance::Decoders() noexcept
    {
        return this->decoders;
    }

    inline const LA32DecoderCollection& LA32Instance::Decoders() const noexcept
    {
        return this->decoders;
    }

    inline LA32Architectural& LA32Instance::Arch() noexcept
    {
        return this->arch;
    }

    inline const LA32Architectural& LA32Instance::Arch() const noexcept
    {
        return this->arch;
    }

    inline LA32MemoryInterface* LA32Instance::Memory() noexcept
    {
        return this->memory;
    }

    inline const LA32MemoryInterface* LA32Instance::Memory() const noexcept
    {
        return this->memory;
    }

    inline LA32TraceEntity::Pool& LA32Instance::TracePool() noexcept
    {
        return *(this->tracePool);
    }

    inline const LA32TraceEntity::Pool& LA32Instance::TracePool() const noexcept
    {
        return *(this->tracePool);
    }

    inline LA32TracerContainer& LA32Instance::Tracers() noexcept
    {
        return this->tracers;
    }

    inline const LA32TracerContainer& LA32Instance::Tracers() const noexcept
    {
        return this->tracers;
    }

    inline bool LA32Instance::HasTracePool() const noexcept
    {
        return this->tracePool != nullptr;
    }

    inline bool LA32Instance::IsTraceEnabled() const noexcept
    {
        return HasTracePool();
    }

    inline LA32MemoryInterface* LA32Instance::SwapMemory(LA32MemoryInterface* memory) noexcept
    {
        std::swap(this->memory, memory);
        return memory;
    }

    inline LA32TraceEntity::Pool* LA32Instance::SwapTracePool(LA32TraceEntity::Pool* trace_pool) noexcept
    {
        std::swap(this->tracePool, trace_pool);
        return trace_pool;
    }

    inline LA32ExecOutcome LA32Instance::Eval()
    {
        // Instruction fetch
        if (LA32InstructionPreFetchEvent(*this, arch.PC()).Fire().IsCancelled())
            return { LA32ExecStatus::FETCH_EMULATION_CANCELLED, ECANCELED };

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

            this->lastFetchTrace = trace_ref;
        }

        LA32Instruction insn(
            LA32InstructionPostFetchEvent(*this, arch.PC(), fetched.data32).Fire().GetInstruction());

        // Instruction decode
        if (LA32InstructionPreDecodeEvent(*this, arch.PC(), insn).Fire().IsCancelled())
            return { LA32ExecStatus::DECODE_EMULATION_CANCELLED, ECANCELED };

        if (!decoders.Decode(insn))
            return { LA32ExecStatus::EXEC_NOT_DECODED, ECANCELED };

        if (!insn.GetExecutor())
            return { LA32ExecStatus::EXEC_NOT_IMPLEMENTED, ECANCELED };

        LA32InstructionPostDecodeEvent(*this, arch.PC(), insn).Fire();

        // Instruction execution
        if (LA32InstructionPreExecutionEvent(*this, arch.PC(), insn).Fire().IsCancelled())
            return { LA32ExecStatus::EXEC_EMULATION_CANCELLED, ECANCELED };

        LA32ExecOutcome outcome_exec = insn.GetExecutor()(insn, *this);

        // - note: @see LA32ExecStatus
        ASSERT(outcome_exec.status != LA32ExecStatus::FETCH_ACCESS_FAULT);
        ASSERT(outcome_exec.status != LA32ExecStatus::FETCH_ADDRESS_MISALIGNED);
        ASSERT(outcome_exec.status != LA32ExecStatus::FETCH_DEVICE_ERROR);
        ASSERT(outcome_exec.status != LA32ExecStatus::EXEC_NOT_DECODED);
        ASSERT(outcome_exec.status != LA32ExecStatus::EXEC_NOT_IMPLEMENTED);

        outcome_exec =
            (LA32InstructionPostExecutionEvent(*this, arch.PC(), insn, outcome_exec).Fire()).GetOutcome();

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

        LA32PCIterationEvent(*this, arch.PC(), new_pc, pc_action).Fire();

        arch.SetPC(new_pc);

        //
        return (lastOutcome = outcome_exec);
    }

    inline LA32ExecOutcome LA32Instance::GetLastOutcome() const noexcept
    {
        return this->lastOutcome;
    }

    inline LA32TraceEntity::Reference LA32Instance::GetLastFetchTrace() const noexcept
    {
        return this->lastFetchTrace;
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

    bool                    gprTracerEnabled;
    size_t                  gprTracerDepth;

    bool                    memoryTracerEnabled;
    size_t                  memoryTracerDepth;
    size_t                  memoryTracerSize;
    */

    inline LA32Instance::Builder::Builder() noexcept
        : arch                  ()
        , memory                (nullptr)
        , decoders              ()
        , traceEnabled          (false)
        , traceUnit             (0)
        , traceMaxFactor        (0)
        , pcTracerEnabled       (false)
        , pcTracerDepth         (0)
        , gprTracerEnabled      (false)
        , gprTracerDepth        (0)
        , memoryTracerEnabled   (false)
        , memoryTracerDepth     (0)
        , memoryTracerSize      (0)
    { }

    inline LA32Instance::Builder::~Builder() noexcept
    { }

    inline LA32Instance::Builder& LA32Instance::Builder::StartupPC(pc_t pc) noexcept
    {
        this->arch.SetPC(pc);
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::GPR(int index, arch32_t value) noexcept
    {
        this->arch.GPRs()[index] = value;
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::GPRs(arch32_t value) noexcept
    {
        for (int i = 0; i < this->arch.GPRs().GetSize(); i++)
            this->arch.GPRs()[i] = value;

        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::Decoder(const LA32Decoder* decoder) noexcept
    {
        this->decoders.ForceAdd(decoder);
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::Decoder(std::initializer_list<const LA32Decoder*> decoders) noexcept
    {
        for (auto decoder : decoders)
            this->decoders.ForceAdd(decoder);

        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::Decoder(const LA32DecoderCollection& decoders) noexcept
    {
        this->decoders.ForceAddAll(decoders);
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::Memory(LA32MemoryInterface* memory) noexcept
    {
        this->memory = memory;
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::EnableTrace(size_t unit, size_t maxFactor) noexcept
    {
        this->traceEnabled      = true;
        this->traceUnit         = unit;
        this->traceMaxFactor    = maxFactor;
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::DisableTrace() noexcept
    {
        this->traceEnabled      = false;
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::EnablePCTracer() noexcept
    {
        this->pcTracerEnabled   = true;
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::EnablePCTracer(size_t depth) noexcept
    {
        this->pcTracerEnabled   = true;
        this->pcTracerDepth     = depth;
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::DisablePCTracer() noexcept
    {
        this->pcTracerEnabled   = false;
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::PCTracerDepth(size_t depth) noexcept
    {
        this->pcTracerDepth     = depth;
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::EnableGPRTracer() noexcept
    {
        this->gprTracerEnabled  = true;
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::EnableGPRTracer(size_t depth) noexcept
    {
        this->gprTracerEnabled  = true;
        this->gprTracerDepth    = depth;
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::DisableGPRTracer() noexcept
    {
        this->gprTracerEnabled  = false;
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::GPRTracerDepth(size_t depth) noexcept
    {
        this->gprTracerDepth    = depth;
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::EnableMemoryTracer() noexcept
    {
        this->memoryTracerEnabled   = true;
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::EnableMemoryTracer(size_t depth, size_t size) noexcept
    {
        this->memoryTracerEnabled   = true;
        this->memoryTracerDepth     = depth;
        this->memoryTracerSize      = size;
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::DisableMemoryTracer() noexcept
    {
        this->memoryTracerEnabled   = false;
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::MemoryTracerDepth(size_t depth) noexcept
    {
        this->memoryTracerDepth     = depth;
        return *this;
    }

    inline LA32Instance::Builder& LA32Instance::Builder::MemoryTracerSize(size_t size) noexcept
    {
        this->memoryTracerSize      = size;
        return *this;
    }

    inline arch32_t LA32Instance::Builder::GPR(int index) const noexcept
    {
        return this->arch.GPRs()[index];
    }

    inline LA32DecoderCollection& LA32Instance::Builder::Decoders() noexcept
    {
        return this->decoders;
    }

    inline const LA32DecoderCollection& LA32Instance::Builder::Decoders() const noexcept
    {
        return this->decoders;
    }

    inline LA32MemoryInterface*& LA32Instance::Builder::Memory() noexcept
    {
        return this->memory;
    }

    inline LA32MemoryInterface* LA32Instance::Builder::Memory() const noexcept
    {
        return this->memory;
    }

    inline bool LA32Instance::Builder::IsTraceEnabled() const noexcept
    {
        return this->traceEnabled;
    }

    inline void LA32Instance::Builder::SetTraceEnabled(bool enabled) noexcept
    {
        this->traceEnabled = enabled;
    }

    inline size_t LA32Instance::Builder::GetTraceUnit() const noexcept
    {
        return this->traceUnit;
    }

    inline void LA32Instance::Builder::SetTraceUnit(size_t unit) noexcept
    {
        this->traceUnit = unit;
    }

    inline size_t LA32Instance::Builder::GetTraceMaxFactor() const noexcept
    {
        return this->traceMaxFactor;
    }

    inline void LA32Instance::Builder::SetTraceMaxFactor(size_t maxFactor) noexcept
    {
        this->traceMaxFactor = maxFactor;
    }

    inline bool LA32Instance::Builder::IsPCTracerEnabled() const noexcept
    {
        return this->pcTracerEnabled;
    }

    inline void LA32Instance::Builder::SetPCTracerEnabled(bool enabled) noexcept
    {
        this->pcTracerEnabled = enabled;
    }

    inline size_t LA32Instance::Builder::GetPCTracerDepth() const noexcept
    {
        return this->pcTracerDepth;
    }

    inline void LA32Instance::Builder::SetPCTracerDepth(size_t depth) noexcept
    {
        this->pcTracerDepth = depth;
    }

    inline bool LA32Instance::Builder::IsMemoryTracerEnabled() const noexcept
    {
        return this->memoryTracerEnabled;
    }

    inline void LA32Instance::Builder::SetMemoryTracerEnabled(bool enabled) noexcept
    {
        this->memoryTracerEnabled = enabled;
    }

    inline size_t LA32Instance::Builder::GetMemoryTracerDepth() const noexcept
    {
        return this->memoryTracerDepth;
    }

    inline void LA32Instance::Builder::SetMemoryTracerDepth(size_t depth) noexcept
    {
        this->memoryTracerDepth = depth;
    }

    inline size_t LA32Instance::Builder::GetMemoryTracerSize() const noexcept
    {
        return this->memoryTracerSize;
    }

    inline void LA32Instance::Builder::SetMemoryTracerSize(size_t size) noexcept
    {
        this->memoryTracerSize = size;
    }

    inline LA32Instance* LA32Instance::Builder::Build() const noexcept
    {
        // copy-on-build
        LA32Instance* instance = new LA32Instance(
            decoders,
            arch,
            memory,
            traceEnabled ? new LA32TraceEntity::Pool(traceUnit, traceMaxFactor) : nullptr,
            LA32TracerContainer(
                traceEnabled && pcTracerEnabled     ? new LA32PCTracer(pcTracerDepth)                           : nullptr,
                traceEnabled && gprTracerEnabled    ? new LA32GPRTracer(gprTracerDepth)                         : nullptr,
                traceEnabled && memoryTracerEnabled ? new LA32MemoryTracer(memoryTracerDepth, memoryTracerSize) : nullptr
            )
        );

        return instance;
    }
}
