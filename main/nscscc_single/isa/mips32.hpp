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

    using MIPS32PCTracer        = MIPS32PCTracerSubtrate;


    // MIPS32 Tracer Container
    class MIPS32TracerContainer {
    private:
        MIPS32PCTracer*         pc_tracer;

        MIPS32GPRTracer*        gpr_tracer;

        MIPS32MemoryTracer*     memory_tracer;

    public:
        MIPS32TracerContainer() noexcept;
        MIPS32TracerContainer(MIPS32TracerContainer&& obj) noexcept;
        ~MIPS32TracerContainer() noexcept;

        MIPS32TracerContainer(MIPS32PCTracer*       pc_tracer, 
                              MIPS32GPRTracer*      gpr_tracer, 
                              MIPS32MemoryTracer*   memory_tracer) noexcept;

        MIPS32TracerContainer(const MIPS32TracerContainer& obj) = delete;

        //
        bool                            HasPCTracer() const noexcept;
        MIPS32PCTracer*                 GetPCTracer() noexcept;
        const MIPS32PCTracer*           GetPCTracer() const noexcept;
        void                            DestroyPCTracer() noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        MIPS32PCTracer*                 SwapPCTracer(MIPS32PCTracer* obj) noexcept;

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
        MIPS32DecoderCollection     decoders;

        MIPS32Architectural         arch;

        MIPS32MemoryInterface*      mem;

        MIPS32TraceEntity::Pool*    trace_pool;

        MIPS32TracerContainer       tracers;

        MIPS32ExecOutcome           outcome_last;

        bool                        branch_taken;
        pc_t                        branch_target_pc;

    public:
        MIPS32Instance(const MIPS32DecoderCollection&   decoders,
                       const MIPS32Architectural&       arch,
                       MIPS32MemoryInterface*           MI,
                       MIPS32TraceEntity::Pool*         trace_pool,
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

        MIPS32TraceEntity::Pool&        TracePool() noexcept;
        const MIPS32TraceEntity::Pool&  TracePool() const noexcept;

        MIPS32TracerContainer&          Tracers() noexcept;
        const MIPS32TracerContainer&    Tracers() const noexcept;

        bool                            HasTracePool() const noexcept;
        bool                            IsTraceEnabled() const noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        MIPS32MemoryInterface*          SwapMI(MIPS32MemoryInterface* MI) noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        MIPS32TraceEntity::Pool*        SwapTracePool(MIPS32TraceEntity::Pool* trace_pool) noexcept;

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

        bool                    trace_enabled;
        size_t                  trace_unit;
        size_t                  trace_max_factor;

        bool                    tracer_enabled_pc;
        size_t                  tracer_depth_pc;

        bool                    tracer_enabled_gpr;
        size_t                  tracer_depth_gpr;

        bool                    tracer_enabled_memory;
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

        //
        Builder&                        EnableTrace(size_t unit, size_t max_factor) noexcept;
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
        Builder&                        EnableMemoryTracer(size_t size, size_t depth) noexcept;
        Builder&                        DisableMemoryTracer() noexcept;

        Builder&                        MemoryTracerDepth(size_t depth) noexcept;
        Builder&                        MemoryTracerSize(size_t size) noexcept;

        //
        arch32_t                        GPR(int index) const noexcept;
        MIPS32DecoderCollection&        Decoders() noexcept;
        const MIPS32DecoderCollection&  Decoders() const noexcept;
        MIPS32MemoryInterface*&         MI() noexcept;
        MIPS32MemoryInterface*          MI() const noexcept;

        bool                            IsTraceEnabled() const noexcept;
        void                            SetTraceEnabled(bool enabled) noexcept;

        size_t                          GetTraceUnit() const noexcept;
        void                            SetTraceUnit(size_t unit) noexcept;
        size_t                          GetTraceMaxFactor() const noexcept;
        void                            SetTraceMaxFactor(size_t max_factor) noexcept;

        bool                            IsPCTracerEnabled() const noexcept;
        void                            SetPCTracerEnabled(bool enabled) noexcept;
        bool                            IsGPRTracerEnabled() const noexcept;
        void                            SetGPRTracerEnabled(bool enabled) noexcept;
        bool                            IsMemoryTracerEnabled() const noexcept;
        void                            SetMemoryTracerEnabled(bool enabled) noexcept;

        size_t                          GetPCTracerDepth() const noexcept;
        void                            SetPCTracerDepth(size_t depth) noexcept;
        
        size_t                          GetGPRTracerDepth() const noexcept;
        void                            SetGPRTracerDepth(size_t depth) noexcept;

        size_t                          GetMemoryTracerDepth() const noexcept;
        void                            SetMemoryTracerDepth(size_t depth) noexcept;
        size_t                          GetMemoryTracerSize() const noexcept;
        void                            SetMemoryTracerSize(size_t size) noexcept;

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
        : pc_tracer     (nullptr)
        , gpr_tracer    (nullptr)
        , memory_tracer (nullptr)
    { }

    MIPS32TracerContainer::MIPS32TracerContainer(MIPS32PCTracer*        pc_tracer, 
                                                 MIPS32GPRTracer*       gpr_tracer, 
                                                 MIPS32MemoryTracer*    memory_tracer) noexcept
        : pc_tracer     (pc_tracer)
        , gpr_tracer    (gpr_tracer)
        , memory_tracer (memory_tracer)
    { }

    MIPS32TracerContainer::MIPS32TracerContainer(MIPS32TracerContainer&& obj) noexcept
        : pc_tracer     (obj.pc_tracer)
        , gpr_tracer    (obj.gpr_tracer)
        , memory_tracer (obj.memory_tracer)
    {
        obj.pc_tracer       = nullptr;
        obj.gpr_tracer      = nullptr;
        obj.memory_tracer   = nullptr;
    }

    MIPS32TracerContainer::~MIPS32TracerContainer() noexcept
    {
        DestroyPCTracer();
        DestroyGPRTracer();
        DestroyMemoryTracer();
    }

    inline bool MIPS32TracerContainer::HasPCTracer() const noexcept
    {
        return pc_tracer != nullptr;
    }

    inline MIPS32PCTracer* MIPS32TracerContainer::GetPCTracer() noexcept
    {
        return pc_tracer;
    }

    inline const MIPS32PCTracer* MIPS32TracerContainer::GetPCTracer() const noexcept
    {
        return pc_tracer;
    }

    inline void MIPS32TracerContainer::DestroyPCTracer() noexcept
    {
        if (pc_tracer)
        {
            delete pc_tracer;
            pc_tracer = nullptr;
        }
    }

    inline MIPS32PCTracer* MIPS32TracerContainer::SwapPCTracer(MIPS32PCTracer* obj) noexcept
    {
        std::swap(obj, pc_tracer);
        return obj;
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
    // MIPS32DecoderCollection     decoders;
    //
    // MIPS32Architectural         arch;
    //
    // MIPS32MemoryInterface*      mem;
    //
    // MIPS32TraceEntity::Pool*    trace_pool;
    //
    // MIPS32TracerContainer       tracers;
    //
    // MIPS32ExecOutcome           outcome_last;
    //
    // bool                        branch_taken;
    // pc_t                        branch_target_pc;
    //

    MIPS32Instance::MIPS32Instance(const MIPS32DecoderCollection&   decoders,
                                   const MIPS32Architectural&       arch,
                                   MIPS32MemoryInterface*           mem,
                                   MIPS32TraceEntity::Pool*         trace_pool,
                                   MIPS32TracerContainer&&          tracers) noexcept
        : decoders          (decoders)
        , arch              (arch)
        , mem               (mem)
        , trace_pool        (trace_pool)
        , tracers           (std::move(tracers))
        , outcome_last      ({ EXEC_SEQUENTIAL, 0 })
        , branch_taken      (false)
        , branch_target_pc  (0)
    { }

    MIPS32Instance::~MIPS32Instance()
    { 
        if (trace_pool)
            delete trace_pool;
    }
    
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

    inline MIPS32TraceEntity::Pool& MIPS32Instance::TracePool() noexcept
    {
        return *trace_pool;
    }

    inline const MIPS32TraceEntity::Pool& MIPS32Instance::TracePool() const noexcept
    {
        return *trace_pool;
    }

    inline MIPS32TracerContainer& MIPS32Instance::Tracers() noexcept
    {
        return tracers;
    }

    inline const MIPS32TracerContainer& MIPS32Instance::Tracers() const noexcept
    {
        return tracers;
    }

    inline bool MIPS32Instance::HasTracePool() const noexcept
    {
        return trace_pool != nullptr;
    }

    inline bool MIPS32Instance::IsTraceEnabled() const noexcept
    {
        return HasTracePool();
    }

    inline MIPS32MemoryInterface* MIPS32Instance::SwapMI(MIPS32MemoryInterface* mem) noexcept
    {
        std::swap(this->mem, mem);
        return mem;
    }

    inline MIPS32TraceEntity::Pool* MIPS32Instance::SwapTracePool(MIPS32TraceEntity::Pool* trace_pool) noexcept
    {
        std::swap(this->trace_pool, trace_pool);
        return trace_pool;
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
    // bool                    trace_enabled;
    // size_t                  trace_unit;
    // size_t                  trace_max_factor;
    //
    // bool                    tracer_enabled_pc;
    // size_t                  tracer_depth_pc;
    //
    // bool                    tracer_enabled_gpr;
    // size_t                  tracer_depth_gpr;
    //
    // bool                    tracer_enabled_memory;
    // size_t                  tracer_depth_memory;
    // size_t                  tracer_size_memory;
    //

    MIPS32Instance::Builder::Builder() noexcept
        : arch                  (0)
        , mem                   (nullptr)
        , decoders              ()
        , trace_enabled         (false)
        , trace_unit            (0)
        , trace_max_factor      (0)
        , tracer_enabled_pc     (false)
        , tracer_depth_pc       (0)
        , tracer_enabled_gpr    (false)
        , tracer_depth_gpr      (0)
        , tracer_enabled_memory (false)
        , tracer_depth_memory   (0)
        , tracer_size_memory    (0)
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

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::EnableTrace(size_t unit, size_t max_factor) noexcept
    {
        trace_enabled       = true;
        trace_unit          = unit;
        trace_max_factor    = max_factor;
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::DisableTrace() noexcept
    {
        trace_enabled = false;
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::EnablePCTracer() noexcept
    {
        tracer_enabled_pc = true;
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::EnablePCTracer(size_t depth) noexcept
    {
        tracer_enabled_pc   = true;
        tracer_depth_pc     = depth;
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::DisablePCTracer() noexcept
    {
        tracer_enabled_pc = false;
        return *this;
    }

    inline MIPS32Instance::Builder& MIPS32Instance::Builder::PCTracerDepth(size_t depth) noexcept
    {
        tracer_depth_pc = depth;
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

    inline bool MIPS32Instance::Builder::IsTraceEnabled() const noexcept
    {
        return trace_enabled;
    }

    inline void MIPS32Instance::Builder::SetTraceEnabled(bool enabled) noexcept
    {
        trace_enabled = enabled;
    }

    inline size_t MIPS32Instance::Builder::GetTraceUnit() const noexcept
    {
        return trace_unit;
    }

    inline void MIPS32Instance::Builder::SetTraceUnit(size_t unit) noexcept
    {
        trace_unit = unit;
    }

    inline size_t MIPS32Instance::Builder::GetTraceMaxFactor() const noexcept
    {
        return trace_max_factor;
    }

    inline void MIPS32Instance::Builder::SetTraceMaxFactor(size_t max_factor) noexcept
    {
        trace_max_factor = max_factor;
    }

    inline bool MIPS32Instance::Builder::IsPCTracerEnabled() const noexcept
    {
        return tracer_enabled_pc;
    }

    inline void MIPS32Instance::Builder::SetPCTracerEnabled(bool enabled) noexcept
    {
        tracer_enabled_pc = enabled;
    }

    inline bool MIPS32Instance::Builder::IsGPRTracerEnabled() const noexcept
    {
        return tracer_enabled_gpr;
    }

    inline void MIPS32Instance::Builder::SetGPRTracerEnabled(bool enabled) noexcept
    {
        tracer_enabled_gpr = enabled;
    }

    inline bool MIPS32Instance::Builder::IsMemoryTracerEnabled() const noexcept
    {
        return tracer_enabled_memory;
    }

    inline void MIPS32Instance::Builder::SetMemoryTracerEnabled(bool enabled) noexcept
    {
        tracer_enabled_memory = enabled;
    }

    inline size_t MIPS32Instance::Builder::GetPCTracerDepth() const noexcept
    {
        return tracer_depth_pc;
    }

    inline void MIPS32Instance::Builder::SetPCTracerDepth(size_t depth) noexcept
    {
        tracer_depth_pc = depth;
    }

    inline size_t MIPS32Instance::Builder::GetGPRTracerDepth() const noexcept
    {
        return tracer_depth_gpr;
    }

    inline void MIPS32Instance::Builder::SetGPRTracerDepth(size_t depth) noexcept
    {
        tracer_depth_gpr = depth;
    }

    inline size_t MIPS32Instance::Builder::GetMemoryTracerDepth() const noexcept
    {
        return tracer_depth_memory;
    }

    inline void MIPS32Instance::Builder::SetMemoryTracerDepth(size_t depth) noexcept
    {
        tracer_depth_memory = depth;
    }

    inline size_t MIPS32Instance::Builder::GetMemoryTracerSize() const noexcept
    {
        return tracer_size_memory;
    }

    inline void MIPS32Instance::Builder::SetMemoryTracerSize(size_t size) noexcept
    {
        tracer_size_memory = size;
    }

    MIPS32Instance* MIPS32Instance::Builder::Build() const noexcept
    {
        // copy-on-build
        MIPS32Instance* instance = new MIPS32Instance(
            decoders,
            arch,
            mem,
            trace_enabled ? new MIPS32TraceEntity::Pool(trace_unit, trace_max_factor) : nullptr,
            MIPS32TracerContainer(
                trace_enabled && tracer_enabled_pc       ? new MIPS32PCTracer(tracer_depth_pc) : nullptr,
                trace_enabled && tracer_enabled_gpr      ? new MIPS32GPRTracer(tracer_depth_gpr) : nullptr,
                trace_enabled && tracer_enabled_memory   ? new MIPS32MemoryTracer(tracer_size_memory, tracer_depth_memory) : nullptr
            ));

        return instance;
    }
}
