#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
//
//

#include <algorithm>
#include <initializer_list>

#include "jasse.hpp"

#include "base/mips32def.hpp"
#include "base/mips32code.hpp"
#include "base/mips32decode.hpp"
#include "base/mips32mem.hpp"
#include "base/mips32event.hpp"
#include "base/mips32trace.hpp"


namespace Jasse {

    // MIPS32 General Purpose Registers container
    class MIPS32GPRs {
    private:
        static constexpr int    SIZE    = MIPS32_ARCH_REG_COUNT;

        arch32_t    gpr[SIZE];

    public:
        MIPS32GPRs() noexcept;
        MIPS32GPRs(const MIPS32GPRs& obj) noexcept;
        
        int             GetSize() const noexcept;
        bool            CheckBound(int index) const noexcept;

        arch32_t        Get(int index) const noexcept;
        void            Set(int index, arch32_t value) noexcept;

        void            operator=(const MIPS32GPRs& obj) noexcept;

        arch32_t&       operator[](int index) noexcept;
        arch32_t        operator[](int index) const noexcept;
    };


    // MIPS32 Architectural State and Interface
    class MIPS32Architectural {
    private:
        pc_t                pc;

        MIPS32GPRs*         gprs;

    public:
        MIPS32Architectural() noexcept;
        MIPS32Architectural(pc_t startupPC) noexcept;
        MIPS32Architectural(const MIPS32Architectural& obj) noexcept;
        ~MIPS32Architectural() noexcept;

        pc_t                PC() const noexcept;
        void                SetPC(pc_t pc) noexcept;

        MIPS32GPRs&         GPRs() noexcept;
        const MIPS32GPRs&   GPRs() const noexcept;

        // *NOTICE: When the architectural instance (MIPS32Architectural) was finalized, 
        //          the GPR container instance (MIPS32GPRs) would be finalized too.
        //
        //          Performing ::SwapGPRs(MIPS32GPRs*) operation means that granting this 
        //          architectural instance the ONLY role of deallocator of the GPR container
        //          instance on call parameter. Furthermore, the GPR container instance on return
        //          value should be deallocated by the caller when necessary.
        //
        //          The GPR container instance should be allocated by operator 'new', coupling
        //          the 'delete' operation on deconstruction.
        //
        //          It's not recommended to swap GPR container in a concurrent procedure.
        [[nodiscard("potential memory leak : caller swap object management")]]
        MIPS32GPRs*         SwapGPRs(MIPS32GPRs* obj) noexcept;
    };


    // MIPS32 Tracers
    using MIPS32GPRTracer       = MIPS32GPRTracerSubtrate<MIPS32TraceHistoryManagement::Pretouch>;

    using MIPS32MemoryTracer    = MIPS32MemoryTracerSubtrate<MIPS32TraceHistoryManagement::CompressedIncremental<>>;


    // MIPS32 Tracer Container
    class MIPS32TracerContainer {
    private:
        MIPS32GPRTracer*        gpr_tracer;

        MIPS32MemoryTracer*     memory_tracer;

    public:
        MIPS32TracerContainer() noexcept;
        MIPS32TracerContainer(MIPS32GPRTracer* gpr_tracer, MIPS32MemoryTracer* memory_tracer) noexcept;
        MIPS32TracerContainer(MIPS32TracerContainer&& obj) noexcept;
        ~MIPS32TracerContainer() noexcept;

        MIPS32TracerContainer(const MIPS32TracerContainer& obj) = delete;

        //
        bool                            HasGPRTracer() const noexcept;
        MIPS32GPRTracer*                GetGPRTracer() noexcept;
        const MIPS32GPRTracer*          GetGPRTracer() const noexcept;
        void                            DestroyGPRTracer() noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        MIPS32GPRTracer*                SwapGPRTracer(MIPS32GPRTracer* obj) noexcept;

        //
        bool                            HasMemoryTracer() const noexcept;
        MIPS32MemoryTracer*             GetMemoryTracer() noexcept; 
        const MIPS32MemoryTracer*       GetMemoryTracer() const noexcept;
        void                            DestroyMemoryTracer() noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        MIPS32MemoryTracer*             SwapMemoryTracer(MIPS32MemoryTracer* obj) noexcept;

        MIPS32TracerContainer&          operator=(const MIPS32TracerContainer& obj) = delete;
        MIPS32TracerContainer&          operator=(MIPS32TracerContainer&& obj) noexcept;
    };



    // MIPS32 Instance
    class MIPS32Instance {
    public:
        class Builder;

    private:
        MIPS32DecoderCollection decoders;

        MIPS32Architectural     arch;

        MIPS32MemoryInterface*  mem;

        MIPS32TracerContainer   tracers;

        MIPS32ExecOutcome       outcome_last;

        bool                    branch_taken;
        pc_t                    branch_target_pc;

    public:
        MIPS32Instance(const MIPS32DecoderCollection&   decoders,
                       const MIPS32Architectural&       arch,
                       MIPS32MemoryInterface*           MI,
                       MIPS32TracerContainer&&          tracers) noexcept;

        MIPS32Instance() = delete;
        MIPS32Instance(const MIPS32Instance&) = delete;

        ~MIPS32Instance() noexcept;

        bool                            IsBranchTaken() const noexcept;
        pc_t                            GetBranchTargetPC() const noexcept;
        void                            SetBranchTarget(bool target_taken, pc_t target_pc) noexcept;

        MIPS32DecoderCollection&        Decoders() noexcept;
        const MIPS32DecoderCollection&  Decoders() const noexcept;

        MIPS32Architectural&            Arch() noexcept;
        const MIPS32Architectural&      Arch() const noexcept;

        MIPS32MemoryInterface*&         MI() noexcept;
        const MIPS32MemoryInterface*    MI() const noexcept;

        MIPS32TracerContainer&          Tracers() noexcept;
        const MIPS32TracerContainer&    Tracers() const noexcept;

        MIPS32ExecOutcome               Eval();

        MIPS32ExecOutcome               GetLastOutcome() const noexcept;
        
        void                            operator=(const MIPS32Instance&) = delete;
    };
    
    // MIPS32 Instance Builder
    class MIPS32Instance::Builder {
    private:
        MIPS32Architectural     arch;

        MIPS32MemoryInterface*  mem;

        MIPS32DecoderCollection decoders;

        bool                    tracer_enabled_gpr;

        bool                    tracer_enabled_memory;

        size_t                  tracer_depth_gpr;

        size_t                  tracer_depth_memory;

        size_t                  tracer_size_memory;

    public:
        Builder() noexcept;
        ~Builder() noexcept;

        Builder&                        StartupPC(pc_t pc) noexcept;

        Builder&                        GPR(int index, arch32_t value) noexcept;
        Builder&                        GPRs(arch32_t value) noexcept;

        Builder&                        Decoder(const MIPS32Decoder* decoder) noexcept;
        Builder&                        Decoder(std::initializer_list<const MIPS32Decoder*> decoders) noexcept;
        Builder&                        Decoder(const MIPS32DecoderCollection& decoders) noexcept;

        Builder&                        MI(MIPS32MemoryInterface* MI) noexcept;

        Builder&                        EnableGPRTracer() noexcept;
        Builder&                        EnableGPRTracer(size_t depth) noexcept;
        Builder&                        DisableGPRTracer() noexcept;

        Builder&                        GPRTracerDepth(size_t depth) noexcept;

        Builder&                        EnableMemoryTracer() noexcept;
        Builder&                        EnableMemoryTracer(size_t size, size_t depth) noexcept;
        Builder&                        DisableMemoryTracer() noexcept;

        Builder&                        MemoryTracerDepth(size_t depth) noexcept;
        Builder&                        MemoryTracerSize(size_t size) noexcept;

        arch32_t                        GPR(int index) const noexcept;
        MIPS32DecoderCollection&        Decoders() noexcept;
        const MIPS32DecoderCollection&  Decoders() const noexcept;
        MIPS32MemoryInterface*&         MI() noexcept;
        MIPS32MemoryInterface*          MI() const noexcept;

        bool                            IsGPRTracerEnabled() const noexcept;
        bool                            IsMemoryTracerEnabled() const noexcept;

        size_t                          GetGPRTracerDepth() const noexcept;

        size_t                          GetMemoryTracerDepth() const noexcept;
        size_t                          GetMemoryTracerSize() const noexcept;

        MIPS32Instance*                 Build() const noexcept;
    };
}



// Implementation of: class MIPS32GPRs
namespace Jasse {
    //
    // arch32_t     gpr[SIZE];
    //

    MIPS32GPRs::MIPS32GPRs() noexcept
        : gpr   ()
    { }

    MIPS32GPRs::MIPS32GPRs(const MIPS32GPRs& obj) noexcept
        : gpr   ()
    {
        std::copy(obj.gpr, obj.gpr + SIZE, gpr);
    }

    inline int MIPS32GPRs::GetSize() const noexcept
    {
        return SIZE;
    }

    inline bool MIPS32GPRs::CheckBound(int index) const noexcept
    {
        return (index >= 0) && (index < GetSize());
    }

    inline arch32_t MIPS32GPRs::Get(int index) const noexcept
    {
        return index ? gpr[index] : 0;
    }

    inline void MIPS32GPRs::Set(int index, arch32_t value) noexcept
    {
        if (index)
            gpr[index] = value;
    }

    inline void MIPS32GPRs::operator=(const MIPS32GPRs& obj) noexcept
    {
        std::copy(obj.gpr, obj.gpr + SIZE, gpr);
    }

    inline arch32_t& MIPS32GPRs::operator[](int index) noexcept
    {
        return index ? gpr[index] : (gpr[index] = 0);
    }

    inline arch32_t MIPS32GPRs::operator[](int index) const noexcept
    {
        return index ? gpr[index] : 0;
    }
}


// Implementation of: class MIPS32Architectural
namespace Jasse {
    //
    // pc_t             pc;
    //
    // MIPS32GPRs*      gprs;
    //

    MIPS32Architectural::MIPS32Architectural() noexcept
        : pc                (0)
        , gprs              (new MIPS32GPRs)
    { }

    MIPS32Architectural::MIPS32Architectural(pc_t startupPC) noexcept
        : pc                (startupPC)
        , gprs              (new MIPS32GPRs)
    { }

    MIPS32Architectural::MIPS32Architectural(const MIPS32Architectural& obj) noexcept
        : pc                (obj.pc)
        , gprs              (new MIPS32GPRs(*(obj.gprs)))
    { }

    MIPS32Architectural::~MIPS32Architectural()
    {
        delete gprs;
    }

    inline pc_t MIPS32Architectural::PC() const noexcept
    {
        return pc;
    }

    inline void MIPS32Architectural::SetPC(pc_t pc) noexcept
    {
        this->pc = pc;
    }

    inline MIPS32GPRs& MIPS32Architectural::GPRs() noexcept
    {
        return *gprs;
    }

    inline const MIPS32GPRs& MIPS32Architectural::GPRs() const noexcept
    {
        return *gprs;
    }

    inline MIPS32GPRs* MIPS32Architectural::SwapGPRs(MIPS32GPRs* obj) noexcept
    {
        std::swap(gprs, obj);
        return obj;
    }
}


// Implementation of: class MIPS32TracerContainer
namespace Jasse {
    //
    // MIPS32GPRTracer*        gpr_tracer;
    //
    // MIPS32MemoryTracer*     memory_tracer;
    //

    MIPS32TracerContainer::MIPS32TracerContainer() noexcept
        : gpr_tracer    (nullptr)
        , memory_tracer (nullptr)
    { }

    MIPS32TracerContainer::MIPS32TracerContainer(MIPS32GPRTracer* gpr_tracer, MIPS32MemoryTracer* memory_tracer) noexcept
        : gpr_tracer    (gpr_tracer)
        , memory_tracer (memory_tracer)
    { }

    MIPS32TracerContainer::MIPS32TracerContainer(MIPS32TracerContainer&& obj) noexcept
        : gpr_tracer    (obj.gpr_tracer)
        , memory_tracer (obj.memory_tracer)
    {
        obj.gpr_tracer      = nullptr;
        obj.memory_tracer   = nullptr;
    }

    MIPS32TracerContainer::~MIPS32TracerContainer() noexcept
    {
        DestroyGPRTracer();
        DestroyMemoryTracer();
    }

    inline bool MIPS32TracerContainer::HasGPRTracer() const noexcept
    {
        return gpr_tracer != nullptr;
    }

    inline MIPS32GPRTracer* MIPS32TracerContainer::GetGPRTracer() noexcept
    {
        return gpr_tracer;
    }

    inline const MIPS32GPRTracer* MIPS32TracerContainer::GetGPRTracer() const noexcept
    {
        return gpr_tracer;
    }

    inline void MIPS32TracerContainer::DestroyGPRTracer() noexcept
    {
        if (gpr_tracer)
        {
            delete gpr_tracer;
            gpr_tracer = nullptr;
        }
    }

    inline MIPS32GPRTracer* MIPS32TracerContainer::SwapGPRTracer(MIPS32GPRTracer* obj) noexcept
    {
        std::swap(obj, gpr_tracer);
        return obj;
    }

    inline bool MIPS32TracerContainer::HasMemoryTracer() const noexcept
    {
        return memory_tracer != nullptr;
    }

    inline MIPS32MemoryTracer* MIPS32TracerContainer::GetMemoryTracer() noexcept
    {
        return memory_tracer;
    }

    inline const MIPS32MemoryTracer* MIPS32TracerContainer::GetMemoryTracer() const noexcept
    {
        return memory_tracer;
    }

    inline void MIPS32TracerContainer::DestroyMemoryTracer() noexcept
    {
        if (memory_tracer)
        {
            delete memory_tracer;
            memory_tracer = nullptr;
        }
    }

    inline MIPS32MemoryTracer* MIPS32TracerContainer::SwapMemoryTracer(MIPS32MemoryTracer* obj) noexcept
    {
        std::swap(obj, memory_tracer);
        return obj;
    }

    inline MIPS32TracerContainer& MIPS32TracerContainer::operator=(MIPS32TracerContainer&& obj) noexcept
    {
        gpr_tracer      = obj.gpr_tracer;
        memory_tracer   = obj.memory_tracer;

        obj.gpr_tracer      = nullptr;
        obj.memory_tracer   = nullptr;

        return *this;
    }
}


// Implementation of: class MIPS32Instance
namespace Jasse {
    //
    // MIPS32DecoderCollection decoders;
    //
    // MIPS32Architectural     arch;
    //
    // MIPS32MemoryInterface*  mem;
    //
    // MIPS32TracerContainer   tracers;
    //
    // bool                    branch_taken;
    // pc_t                    branch_target_pc;
    //

    MIPS32Instance::MIPS32Instance(const MIPS32DecoderCollection&   decoders,
                                   const MIPS32Architectural&       arch,
                                   MIPS32MemoryInterface*           mem,
                                   MIPS32TracerContainer&&          tracers) noexcept
        : decoders          (decoders)
        , arch              (arch)
        , mem               (mem)
        , tracers           (std::move(tracers))
        , outcome_last      ({ EXEC_SEQUENTIAL, 0 })
        , branch_taken      (false)
        , branch_target_pc  (0)
    { }

    MIPS32Instance::~MIPS32Instance()
    { }
    
    inline bool MIPS32Instance::IsBranchTaken() const noexcept
    {
        return branch_taken;
    }

    inline pc_t MIPS32Instance::GetBranchTargetPC() const noexcept
    {
        return branch_target_pc;
    }

    inline void MIPS32Instance::SetBranchTarget(bool target_taken, pc_t target_pc) noexcept
    {
        this->branch_taken      = target_taken;
        this->branch_target_pc  = target_pc;
    }

    inline MIPS32DecoderCollection& MIPS32Instance::Decoders() noexcept
    {
        return decoders;
    }

    inline const MIPS32DecoderCollection& MIPS32Instance::Decoders() const noexcept
    {
        return decoders;
    }

    inline MIPS32Architectural& MIPS32Instance::Arch() noexcept
    {
        return arch;
    }

    inline const MIPS32Architectural& MIPS32Instance::Arch() const noexcept
    {
        return arch;
    }

    inline MIPS32MemoryInterface*& MIPS32Instance::MI() noexcept
    {
        return mem;
    }

    inline const MIPS32MemoryInterface* MIPS32Instance::MI() const noexcept
    {
        return mem;
    }

    inline MIPS32TracerContainer& MIPS32Instance::Tracers() noexcept
    {
        return tracers;
    }

    inline const MIPS32TracerContainer& MIPS32Instance::Tracers() const noexcept
    {
        return tracers;
    }

    MIPS32ExecOutcome MIPS32Instance::Eval()
    {
        // Instruction fetch
        if (MIPS32InstructionPreFetchEvent(*this, arch.PC()).Fire().IsCancelled())
            return { FETCH_EMULATION_CANCELLED, ECANCELED };

        memdata_t fetched;
        MIPS32MOPOutcome mopoutcome = mem->ReadInsn(arch.PC(), MOPW_WORD, &fetched);

        if (mopoutcome.status != MOP_SUCCESS)
        {
            MIPS32ExecOutcome rexec;

            switch (mopoutcome.status)
            {
                case MOP_ACCESS_FAULT:
                    rexec = { FETCH_ACCESS_FAULT, mopoutcome.error };
                    break;

                case MOP_ADDRESS_MISALIGNED:
                    rexec = { FETCH_ADDRESS_MISALIGNED, mopoutcome.error };
                    break;

                case MOP_DEVICE_ERROR:
                    rexec = { FETCH_DEVICE_ERROR, mopoutcome.error };
                    break;

                [[unlikely]] default:
                    // *NOTICE: +You can add your own custom MOP status handler here if necessary,
                    //          or in switch cases.
                    //          For default routine, this cause a direct fault.
                    SHOULD_NOT_REACH_HERE;
            }

            return (outcome_last = rexec);
        }

        // Instruction decode
        MIPS32Instruction insn(
            MIPS32InstructionPostFetchEvent(*this, arch.PC(), fetched.data32).Fire().GetInstruction());

        if (MIPS32InstructionPreDecodeEvent(*this, arch.PC(), insn).Fire().IsCancelled())
            return { DECODE_EMULATION_CANCELLED, ECANCELED };

        if (!decoders.Decode(insn))
            return { EXEC_NOT_DECODED, ECANCELED };

        if (!insn.GetExecutor())
            return { EXEC_NOT_IMPLEMENTED, ECANCELED };

        MIPS32InstructionPostDecodeEvent(*this, arch.PC(), insn).Fire();

        // Instruction execution
        if (MIPS32InstructionPreExecutionEvent(*this, arch.PC(), insn).Fire().IsCancelled())
            return { EXEC_EMULATION_CANCELLED, ECANCELED };

        MIPS32ExecOutcome outcome_exec = insn.GetExecutor()(insn, *this);

        // - note: @see MIPS32ExecStatus
        ASSERT(outcome_exec.status != FETCH_ACCESS_FAULT);
        ASSERT(outcome_exec.status != FETCH_ADDRESS_MISALIGNED);
        ASSERT(outcome_exec.status != FETCH_DEVICE_ERROR);
        ASSERT(outcome_exec.status != EXEC_NOT_DECODED);
        ASSERT(outcome_exec.status != EXEC_NOT_IMPLEMENTED);

        outcome_exec =
            (MIPS32InstructionPostExecutionEvent(*this, arch.PC(), insn, outcome_exec).Fire()).GetOutcome();

        // PC iteration
        pc_t                            new_pc;
        MIPS32PCIterationEvent::Action  pc_action;

        if (outcome_last.status == EXEC_DELAYSLOT) // delay slot
        {
            if (IsBranchTaken())
            {
                new_pc      = GetBranchTargetPC();
                pc_action   = MIPS32PCIterationEvent::Action::BRANCH_TAKEN;
            }
            else
            {
                new_pc      = arch.PC() + 4;
                pc_action   = MIPS32PCIterationEvent::Action::BRANCH_NOT_TAKEN;
            }
        }
        else if (outcome_exec.status == EXEC_SEQUENTIAL)
        {
            new_pc      = arch.PC() + 4;
            pc_action   = MIPS32PCIterationEvent::Action::SEQUENTIAL;
        }
        else if (outcome_exec.status == EXEC_DELAYSLOT)
        {
            new_pc      = arch.PC() + 4;
            pc_action   = MIPS32PCIterationEvent::Action::DELAY_SLOT;
        }

        MIPS32PCIterationEvent(*this, arch.PC(), new_pc, pc_action).Fire();

        arch.SetPC(new_pc);

        //
        return (outcome_last = outcome_exec);
    }

    inline MIPS32ExecOutcome MIPS32Instance::GetLastOutcome() const noexcept
    {
        return outcome_last;
    }
}


// Implementation of: class MIPS32Instance::Builder
namespace Jasse {
    //
    // MIPS32Architectural     arch;
    //
    // MIPS32MemoryInterface*  mem;
    //
    // MIPS32DecoderCollection decoders;
    //
    // bool                    tracer_enabled_gpr;
    //
    // bool                    tracer_enabled_memory;
    //
    // size_t                  tracer_depth_gpr;
    //
    // size_t                  tracer_depth_memory;
    //
    // size_t                  tracer_size_memory;
    //

    MIPS32Instance::Builder::Builder() noexcept
        : arch          (0)
        , mem           (nullptr)
        , decoders      ()
    { }

    MIPS32Instance::Builder::~Builder() noexcept
    { }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::StartupPC(pc_t pc) noexcept
    {
        arch.SetPC(pc);
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::GPR(int index, arch32_t value) noexcept
    {
        arch.GPRs()[index] = value;
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::GPRs(arch32_t value) noexcept
    {
        for (int i = 0; i < arch.GPRs().GetSize(); i++)
            arch.GPRs()[i] = value;
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::Decoder(const MIPS32Decoder* decoder) noexcept
    {
        decoders.ForceAdd(decoder);
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::Decoder(std::initializer_list<const MIPS32Decoder*> decoders) noexcept
    {
        for (const MIPS32Decoder* decoder : decoders)
            this->decoders.ForceAdd(decoder);
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::Decoder(const MIPS32DecoderCollection& decoders) noexcept
    {
        this->decoders.ForceAddAll(decoders);
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::MI(MIPS32MemoryInterface* MI) noexcept
    {
        mem = MI;
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::EnableGPRTracer() noexcept
    {
        tracer_enabled_gpr = true;
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::EnableGPRTracer(size_t depth) noexcept
    {
        tracer_enabled_gpr  = true;
        tracer_depth_gpr    = depth;
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::DisableGPRTracer() noexcept
    {
        tracer_enabled_gpr = false;
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::GPRTracerDepth(size_t depth) noexcept
    {
        tracer_depth_gpr = depth;
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::EnableMemoryTracer() noexcept
    {
        tracer_enabled_memory = true;
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::EnableMemoryTracer(size_t size, size_t depth) noexcept
    {
        tracer_enabled_memory   = true;
        tracer_size_memory      = size;
        tracer_depth_memory     = depth;
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::DisableMemoryTracer() noexcept
    {
        tracer_enabled_memory = false;
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::MemoryTracerDepth(size_t depth) noexcept
    {
        tracer_depth_memory = depth;
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::MemoryTracerSize(size_t size) noexcept
    {
        tracer_size_memory = size;
        return *this;
    }

    inline arch32_t MIPS32Instance::Builder::GPR(int index) const noexcept
    {
        return arch.GPRs()[index];
    }

    inline MIPS32DecoderCollection& MIPS32Instance::Builder::Decoders() noexcept
    {
        return decoders;
    }

    inline const MIPS32DecoderCollection& MIPS32Instance::Builder::Decoders() const noexcept
    {
        return decoders;
    }

    inline MIPS32MemoryInterface*& MIPS32Instance::Builder::MI() noexcept
    {
        return mem;
    }

    inline MIPS32MemoryInterface* MIPS32Instance::Builder::MI() const noexcept
    {
        return mem;
    }

    inline bool MIPS32Instance::Builder::IsGPRTracerEnabled() const noexcept
    {
        return tracer_enabled_gpr;
    }

    inline bool MIPS32Instance::Builder::IsMemoryTracerEnabled() const noexcept
    {
        return tracer_enabled_memory;
    }

    inline size_t MIPS32Instance::Builder::GetGPRTracerDepth() const noexcept
    {
        return tracer_depth_gpr;
    }

    inline size_t MIPS32Instance::Builder::GetMemoryTracerDepth() const noexcept
    {
        return tracer_depth_memory;
    }

    inline size_t MIPS32Instance::Builder::GetMemoryTracerSize() const noexcept
    {
        return tracer_size_memory;
    }

    MIPS32Instance* MIPS32Instance::Builder::Build() const noexcept
    {
        // copy-on-build
        MIPS32Instance* instance = new MIPS32Instance(
            decoders,
            arch,
            mem,
            MIPS32TracerContainer(
                tracer_enabled_gpr      ? new MIPS32GPRTracer(tracer_depth_gpr) : nullptr,
                tracer_enabled_memory   ? new MIPS32MemoryTracer(tracer_size_memory, tracer_depth_memory) : nullptr
            ));

        return instance;
    }
}
