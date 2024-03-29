#pragma once
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
//
//

#ifndef __HEADER_JASSE_LA32
#define __HEADER_JASSE_LA32

#include <initializer_list>

#include "jasse.hpp"                // IWYU pragma: export

#include "base/la32def.hpp"         // IWYU pragma: export
#include "base/la32code.hpp"        // IWYU pragma: export
#include "base/la32trait.hpp"       // IWYU pragma: export
#include "base/la32decode.hpp"      // IWYU pragma: export
#include "base/la32mem.hpp"         // IWYU pragma: export
#include "base/la32event.hpp"       // IWYU pragma: export
#include "base/la32trace.hpp"       // IWYU pragma: export
#include "base/la32encode.hpp"      // IWYU pragma: export
#include "base/la32disasm.hpp"      // IWYU pragma: export


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


    // LA32 Branch Progress
    class LA32BranchProgress {
    private:
        bool    taken;
        pc_t    target;

    public:
        LA32BranchProgress() noexcept;
        ~LA32BranchProgress() noexcept;

        bool    IsBranchTaken() const noexcept;
        pc_t    GetBranchTarget() const noexcept;

        void    SetBranchTaken(bool taken) noexcept;
        void    SetBranchTarget(pc_t target) noexcept;
        
        void    SetBranch(bool taken, pc_t target) noexcept;

        void    ResetBranch() noexcept;
    };

    // LA32 Evaluation Context
    class LA32EvaluationContext : public LA32BranchProgress {
    private:
        LA32TraceEntity::Reference  fetchTrace;

        unsigned int                eventBusId;

    public:
        LA32EvaluationContext(unsigned int eventBusId = 0) noexcept;
        ~LA32EvaluationContext() noexcept;

        LA32TraceEntity::Reference  GetFetchTrace() const noexcept;
        void                        SetFetchTrace(LA32TraceEntity::Reference trace) noexcept;

        unsigned int                GetEventBusId() const noexcept;
        void                        SetEventBusId(unsigned int id) noexcept;
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

    using LA32ExecutionTracer   = LA32ExecutionTracerSubtrate;

    using LA32FetchTracer       = LA32FetchTracerSubtrate;

    using LA32PCTracer          = LA32PCTracerSubtrate;



    // LA32 Tracer Container
    class LA32TracerContainer {
    private:
        LA32PCTracer*           pcTracer;

        LA32FetchTracer*        fetchTracer;

        LA32ExecutionTracer*    executionTracer;

        LA32GPRTracer*          gprTracer;

        LA32MemoryTracer*       memoryTracer;

    public:
        LA32TracerContainer() noexcept;
        LA32TracerContainer(LA32TracerContainer&& obj) noexcept;
        ~LA32TracerContainer() noexcept;

        LA32TracerContainer(LA32PCTracer*           pcTracer,
                            LA32FetchTracer*        fetchTracer,
                            LA32ExecutionTracer*    executionTracer,
                            LA32GPRTracer*          gprTracer,
                            LA32MemoryTracer*       memoryTracer) noexcept;

        LA32TracerContainer(const LA32TracerContainer&) = delete;

        //
        bool                        HasPCTracer() const noexcept;
        LA32PCTracer*               GetPCTracer() noexcept;
        const LA32PCTracer*         GetPCTracer() const noexcept;
        void                        DestroyPCTracer() noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        LA32PCTracer*               SwapPCTracer(LA32PCTracer* obj) noexcept;

        //
        bool                        HasFetchTracer() const noexcept;
        LA32FetchTracer*            GetFetchTracer() noexcept;
        const LA32FetchTracer*      GetFetchTracer() const noexcept;
        void                        DestroyFetchTracer() noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        LA32FetchTracer*            SwapFetchTracer(LA32FetchTracer* obj) noexcept;

        //
        bool                        HasExecutionTracer() const noexcept;
        LA32ExecutionTracer*        GetExecutionTracer() noexcept;
        const LA32ExecutionTracer*  GetExecutionTracer() const noexcept;
        void                        DestroyExecutionTracer() noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        LA32ExecutionTracer*        SwapExecutionTracer(LA32ExecutionTracer* obj) noexcept;

        //
        bool                        HasGPRTracer() const noexcept;
        LA32GPRTracer*              GetGPRTracer() noexcept;
        const LA32GPRTracer*        GetGPRTracer() const noexcept;
        void                        DestroyGPRTracer() noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        LA32GPRTracer*              SwapGPRTracer(LA32GPRTracer* obj) noexcept;

        //
        bool                        HasMemoryTracer() const noexcept;
        LA32MemoryTracer*           GetMemoryTracer() noexcept;
        const LA32MemoryTracer*     GetMemoryTracer() const noexcept;
        void                        DestroyMemoryTracer() noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        LA32MemoryTracer*           SwapMemoryTracer(LA32MemoryTracer* obj) noexcept;

        //
        LA32TracerContainer&        operator=(const LA32TracerContainer& obj) = delete;
        LA32TracerContainer&        operator=(LA32TracerContainer&& obj) noexcept;
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

    public:
        LA32Instance(const LA32DecoderCollection&   decoders,
                     const LA32Architectural&       arch,
                     LA32MemoryInterface*           memory,
                     LA32TraceEntity::Pool*         tracePool,
                     LA32TracerContainer&&          tracers) noexcept;

        LA32Instance() = delete;
        LA32Instance(const LA32Instance&) = delete;

        ~LA32Instance() noexcept;

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

        bool                    fetchTracerEnabled;
        size_t                  fetchTracerDepth;

        bool                    executionTracerEnabled;
        size_t                  executionTracerDepth;

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
        Builder&                        EnableFetchTracer() noexcept;
        Builder&                        EnableFetchTracer(size_t depth) noexcept;
        Builder&                        DisableFetchTracer() noexcept;

        Builder&                        FetchTracerDepth(size_t depth) noexcept;

        //
        Builder&                        EnableExecutionTracer() noexcept;
        Builder&                        EnableExecutionTracer(size_t depth) noexcept;
        Builder&                        DisableExecutionTracer() noexcept;

        Builder&                        ExecutionTracerDepth(size_t depth) noexcept;

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

        bool                            IsFetchTracerEnabled() const noexcept;
        void                            SetFetchTracerEnabled(bool enabled) noexcept;
        size_t                          GetFetchTracerDepth() const noexcept;
        void                            SetFetchTracerDepth(size_t depth) noexcept;

        bool                            IsExecutionTracerEnabled() const noexcept;
        void                            SetExecutionTracerEnabled(bool enabled) noexcept;
        size_t                          GetExecutionTracerDepth() const noexcept;
        void                            SetExecutionTracerDepth(size_t depth) noexcept;

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


    // LA32 Evaluator for ISA Simulation
    class LA32Evaluator : public LA32EvaluationContext {
    private:
        LA32Instance*               instance;

        LA32ExecOutcome             lastOutcome;

    public:
        LA32Evaluator(LA32Instance* instance, unsigned int eventBusId = 0) noexcept;
        ~LA32Evaluator() noexcept;

        LA32Instance*               GetInstance() noexcept;
        const LA32Instance*         GetInstance() const noexcept;

        LA32ExecOutcome             Eval();

        LA32ExecOutcome             GetLastOutcome() const noexcept;
    };
    
}


#endif
