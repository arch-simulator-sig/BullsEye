#pragma once
//
// Add-ons for DiffTest support
//
//

#ifndef __HEADER_JASSE_LA32__ADDON__DIFFTEST
#define __HEADER_JASSE_LA32__ADDON__DIFFTEST


#include "../la32.hpp"


namespace Jasse {

    // Differential Increment Base
    class LA32Increment {
    private:
        uint32_t    term_count;

    public:
        LA32Increment(uint32_t term_count = 0) noexcept;

        uint32_t    GetTermCount() const noexcept;
        void        SetTermCount(uint32_t term_count) noexcept;
        uint32_t    IncreaseTermCount() noexcept;
    };


    // Differential Increment of PC
    class LA32IncrementPC : public LA32Increment {
    private:
        pc_t        pc;

    public:
        LA32IncrementPC() noexcept;

        pc_t        GetPC() const noexcept;
        void        SetPC(pc_t pc) noexcept;
    };

    // Differential Increment of Instruction
    class LA32IncrementInstruction : public LA32Increment {
    private:
        LA32Instruction instruction;

    public:
        LA32IncrementInstruction() noexcept;

        const LA32Instruction&  GetInstruction() const noexcept;
        void                    SetInstruction(const LA32Instruction& instruction) noexcept;
    };

    // Differential Increment of Branch
    class LA32IncrementBranch : public LA32Increment {
    private:
        bool        branch_taken;
        pc_t        branch_target;

    public:
        LA32IncrementBranch() noexcept;

        bool        GetBranchTaken() const noexcept;
        void        SetBranchTaken(bool branch_taken) noexcept;

        pc_t        GetBranchTarget() const noexcept;
        void        SetBranchTarget(pc_t branch_target) noexcept;

        void        SetBranch(bool branch_taken, pc_t branch_target) noexcept;
    };

    // Differential Increment of GPR
    class LA32IncrementGPR : public LA32Increment {
    private:
        unsigned int    gpr_index;
        arch32_t        gpr_value;

    public:
        LA32IncrementGPR() noexcept;

        unsigned int    GetGPRIndex() const noexcept;
        void            SetGPRIndex(unsigned int gpr_index) noexcept;

        arch32_t        GetGPRValue() const noexcept;
        void            SetGPRValue(arch32_t gpr_value) noexcept;

        void            SetGPR(unsigned int gpr_index, arch32_t gpr_value) noexcept;
    };

    // Differential Increment of Memory Store
    class LA32IncrementMemoryStore : public LA32Increment {
    private:
        addr_t          address;
        LA32MOPWidth    width;
        memdata_t       data;

    public:
        LA32IncrementMemoryStore() noexcept;

        addr_t          GetAddress() const noexcept;
        void            SetAddress(addr_t address) noexcept;

        LA32MOPWidth    GetWidth() const noexcept;
        void            SetWidth(LA32MOPWidth width) noexcept;

        memdata_t       GetData() const noexcept;
        void            SetData(memdata_t data) noexcept;

        void            SetMemoryStore(addr_t address, LA32MOPWidth width, memdata_t data) noexcept;
    };

    // Differential Increment of Memory Load
    class LA32IncrementMemoryLoad : public LA32Increment {
    private:
        addr_t          address;
        LA32MOPWidth    width;
        arch32_t        value;

    public:
        LA32IncrementMemoryLoad() noexcept;

        addr_t          GetAddress() const noexcept;
        void            SetAddress(addr_t address) noexcept;

        LA32MOPWidth    GetWidth() const noexcept;
        void            SetWidth(LA32MOPWidth width) noexcept;

        arch32_t        GetValue() const noexcept;
        void            SetValue(arch32_t value) noexcept;

        void            SetMemoryLoad(addr_t address, LA32MOPWidth width, arch32_t value) noexcept;
    };


    // LA32 Differential Instance
    class LA32Differential {
    public:
        class Builder;

    private:
        unsigned int                eventBusId;
        int                         eventPriority;

        bool                        enabledIncrementPC;
        bool                        enabledIncrementInstruction;
        bool                        enabledIncrementBranch;
        bool                        enabledIncrementGPR;
        bool                        enabledIncrementMemoryStore;
        bool                        enabledIncrementMemoryLoad;

        LA32IncrementPC             incrementPC;
        LA32IncrementInstruction    incrementInstruction;
        LA32IncrementBranch         incrementBranch;
        LA32IncrementGPR            incrementGPR;
        LA32IncrementMemoryStore    incrementMemoryStore;
        LA32IncrementMemoryLoad     incrementMemoryLoad;

    protected:
        friend class Builder;
        LA32Differential(unsigned int   eventBusId,
                         int            eventPriority,
                         bool           enabledIncrementPC,
                         bool           enabledIncrementInstruction,
                         bool           enabledIncrementBranch,
                         bool           enabledIncrementGPR,
                         bool           enabledIncrementMemoryStore,
                         bool           enabledIncrementMemoryLoad) noexcept;

    protected:
        void                            OnPreEval(LA32InstancePreEvalEvent& event) noexcept;
        void                            OnPostEval(LA32InstancePostEvalEvent& event) noexcept;

        void                            OnPostFetch(LA32InstructionPostFetchEvent& event) noexcept;
        // -> PC Increment

        void                            OnPostDecode(LA32InstructionPostDecodeEvent& event) noexcept;
        // -> Instruction Increment

        void                            OnPCIteration(LA32PCIterationEvent& event) noexcept;
        // -> Branch Increment

        void                            OnPostGPRModify(LA32TracedInstructionGPRPostModifyEvent& event) noexcept;
        // -> GPR Increment

        void                            OnPostMemoryStore(LA32TracedMemoryPostStoreEvent& event) noexcept;
        // -> Memory Store Increment

        void                            OnPostMemoryLoad(LA32TracedMemoryPostPostLoadEvent& event) noexcept;
        // -> Memory Load Increment

    protected:
        std::string                     GetListenerName(const char* increment_name) const noexcept;

        void                            RegisterListeners() noexcept;
        void                            UnregisterListeners() noexcept;

    public:
        LA32Differential(const LA32Differential&) = delete;
        LA32Differential(LA32Differential&& obj) = delete;

        ~LA32Differential() noexcept;

        unsigned int                    GetEventBusId() const noexcept;
        int                             GetEventPriority() const noexcept;

        bool                            IsEnabledPC() const noexcept;
        bool                            IsEnabledInstruction() const noexcept;
        bool                            IsEnabledBranch() const noexcept;
        bool                            IsEnabledGPR() const noexcept;
        bool                            IsEnabledMemoryStore() const noexcept;
        bool                            IsEnabledMemoryLoad() const noexcept;

        const LA32IncrementPC&          GetIncrementPC() const noexcept;
        const LA32IncrementInstruction& GetIncrementInstruction() const noexcept;
        const LA32IncrementBranch&      GetIncrementBranch() const noexcept;
        const LA32IncrementGPR&         GetIncrementGPR() const noexcept;
        const LA32IncrementMemoryStore& GetIncrementMemoryStore() const noexcept;
        const LA32IncrementMemoryLoad&  GetIncrementMemoryLoad() const noexcept;

        LA32Differential& operator=(const LA32Differential&) = delete;
        LA32Differential& operator=(LA32Differential&& obj) = delete;
    };

    // LA32 Differential Instance Builder
    class LA32Differential::Builder {
    private:
        unsigned int    eventBusId;
        int             eventPriority;

        bool            enabledIncrementPC;
        bool            enabledIncrementInstruction;
        bool            enabledIncrementBranch;
        bool            enabledIncrementGPR;
        bool            enabledIncrementMemoryStore;
        bool            enabledIncrementMemoryLoad;

    public:
        Builder() noexcept;

        //
        Builder&            EventBusId(unsigned int eventBusId) noexcept;
        Builder&            EventPriority(int eventPriority) noexcept;

        Builder&            EnablePC(bool enabledIncrementPC = true) noexcept;
        Builder&            EnableInstruction(bool enabledIncrementInstruction = true) noexcept;
        Builder&            EnableBranch(bool enabledIncrementBranch = true) noexcept;
        Builder&            EnableGPR(bool enabledIncrementGPR = true) noexcept;
        Builder&            EnableMemoryStore(bool enabledIncrementMemoryStore = true) noexcept;
        Builder&            EnableMemoryLoad(bool enabledIncrementMemoryLoad = true) noexcept;

        //
        unsigned int        GetEventBusId() const noexcept;
        void                SetEventBusId(unsigned int eventBusId) noexcept;

        int                 GetEventPriority() const noexcept;
        void                SetEventPriority(int eventPriority) noexcept;

        bool                IsEnabledPC() const noexcept;
        void                SetEnabledPC(bool enabledIncrementPC) noexcept;

        bool                IsEnabledBranch() const noexcept;
        void                SetEnabledBranch(bool enabledIncrementBranch) noexcept;

        bool                IsEnabledInstruction() const noexcept;
        void                SetEnabledInstruction(bool enabledIncrementInstruction) noexcept;

        bool                IsEnabledGPR() const noexcept;
        void                SetEnabledGPR(bool enabledIncrementGPR) noexcept;

        bool                IsEnabledMemoryStore() const noexcept;
        void                SetEnabledMemoryStore(bool enabledIncrementMemoryStore) noexcept;

        bool                IsEnabledMemoryLoad() const noexcept;
        void                SetEnabledMemoryLoad(bool enabledIncrementMemoryLoad) noexcept;

        //
        LA32Differential*   Build() noexcept;
    };
}


#endif
