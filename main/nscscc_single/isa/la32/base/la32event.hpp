#pragma once
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
// Basic Event Infrastructures
//

#include "la32def.hpp"
#include "la32decode.hpp"
#include "la32trace.hpp"
#include "la32mem.hpp"

#include "common/eventbus.hpp"


namespace Jasse {

    // LA32 (in instance) Event Base
    class LA32InstanceEventBase {
    private:
        LA32Instance&     instance;

    public:
        LA32InstanceEventBase(LA32Instance& instance) noexcept;

        LA32Instance&               GetInstance() noexcept;
        const LA32Instance&         GetInstance() const noexcept;
    };

    // LA32 PC-related Event Base
    class LA32PCEventBase {
    private:
        pc_t                pc;

    public:
        LA32PCEventBase(pc_t pc) noexcept;

        pc_t                        GetPC() const noexcept;
        void                        SetPC(pc_t value) noexcept;
    };

    // LA32 PC Change related Event Base
    class LA32PCChangeEventBase {
    private:
        pc_t                old_pc;
        pc_t                new_pc;

    public:
        LA32PCChangeEventBase(pc_t old_pc, pc_t new_pc) noexcept;

        pc_t                        GetOldPC() const noexcept;
        void                        SetOldPC(pc_t value) noexcept;

        pc_t                        GetNewPC() const noexcept;
        void                        SetNewPC(pc_t value) noexcept;
    };

    // LA32 Instruction related Event Base
    class LA32InstructionEventBase {
    private:
        LA32Instruction&  insn;

    public:
        LA32InstructionEventBase(LA32Instruction& insn) noexcept;

        LA32Instruction&            GetInstruction() noexcept;
        const LA32Instruction&      GetInstruction() const noexcept;
        void                        SetInstruction(const LA32Instruction& insn) noexcept;
    };

    // LA32 Constant Instruction related Event Base
    class LA32ConstInstructionEventBase {
    private:
        const LA32Instruction& insn;

    public:
        LA32ConstInstructionEventBase(const LA32Instruction& insn) noexcept;

        const LA32Instruction&      GetInstruction() const noexcept;
    };

    // LA32 Raw Instruction related Event Base
    class LA32RawInstructionEventBase {
    private:
        insnraw_t           insn;

    public:
        LA32RawInstructionEventBase(insnraw_t insn) noexcept;

        insnraw_t                   GetInstruction() const noexcept;
        void                        SetInstruction(insnraw_t insn) noexcept;
    };

    // LA32 Execution Outcome related Event Base
    class LA32ExecOutcomeEventBase {
    private:
        LA32ExecOutcome   outcome;

    public:
        LA32ExecOutcomeEventBase(LA32ExecOutcome outcome) noexcept;

        LA32ExecOutcome             GetOutcome() const noexcept;
        void                        SetOutcome(LA32ExecOutcome outcome) noexcept;
    };

    // LA32 GPR related Event Base
    class LA32GPREventBase {
    private:
        unsigned int        index;
        arch32_t            value;

    public:
        LA32GPREventBase(unsigned int index, arch32_t value) noexcept;

        unsigned int                GetIndex() const noexcept;
        void                        SetIndex(unsigned int index) noexcept;

        arch32_t                    GetValue() const noexcept;
        void                        SetValue(arch32_t value) noexcept;
    };

    // LA32 GPR related Post-Event Base
    class LA32GPRPostEventBase {
    private:
        unsigned int        index;
        arch32_t            value;

    public:
        LA32GPRPostEventBase(unsigned int index, arch32_t value) noexcept;

        unsigned int                GetIndex() const noexcept;
        arch32_t                    GetValue() const noexcept;
    };

    // LA32 Traced GPR related Event Base
    class LA32TracedGPREventBase {
    private:
        unsigned int                index;
        arch32_t                    value;

        bool                        indexModified;
        bool                        valueModified;
        LA32TraceEntity::Reference  valueTrace;

    public:
        LA32TracedGPREventBase(unsigned int index, arch32_t value) noexcept;

        unsigned int                GetIndex() const noexcept;
        void                        SetIndex(unsigned int index) noexcept;

        arch32_t                    GetValue() const noexcept;
        void                        SetValue(arch32_t value) noexcept;
        void                        SetValue(arch32_t value, LA32TraceEntity::Reference trace) noexcept;

        bool                        IsIndexModified() const noexcept;
        bool                        IsValueModified() const noexcept;

        LA32TraceEntity::Reference  GetValueTrace() const noexcept;
    };

    // LA32 Traced GPR related Post-Event Base
    class LA32TracedGPRPostEventBase {
    private:
        unsigned int                index;
        arch32_t                    value;

    public:
        LA32TracedGPRPostEventBase(unsigned int index, arch32_t value) noexcept;

        unsigned int                GetIndex() const noexcept;
        arch32_t                    GetValue() const noexcept;
    };

    // LA32 GPR Pre-Modification Event Base 
    class LA32GPRPreModifyEventBase {
    private:
        unsigned int        index;
        arch32_t            oldValue;
        arch32_t            newValue;

    public:
        LA32GPRPreModifyEventBase(unsigned int index, arch32_t oldValue, arch32_t newValue) noexcept;

        unsigned int                GetIndex() const noexcept;
        void                        SetIndex(unsigned int index) noexcept;

        arch32_t                    GetOldValue() const noexcept;
        void                        SetOldValue(arch32_t value) noexcept;

        arch32_t                    GetNewValue() const noexcept;
        void                        SetNewValue(arch32_t value) noexcept;
    };

    // LA32 GPR Post-Modification Event Base 
    class LA32GPRPostModifyEventBase {
    private:
        unsigned int        index;
        arch32_t            oldValue;
        arch32_t            newValue;

    public:
        LA32GPRPostModifyEventBase(unsigned int index, arch32_t oldValue, arch32_t newValue) noexcept;

        unsigned int                GetIndex() const noexcept;
        arch32_t                    GetOldValue() const noexcept;
        arch32_t                    GetNewValue() const noexcept;
    };


    // LA32 Traced GPR Pre-Modification Event Base
    class LA32TracedGPRPreModifyEventBase {
    private:
        unsigned int                index;
        arch32_t                    oldValue;
        arch32_t                    newValue;

        bool                        indexModified;
        bool                        newValueModified;
        LA32TraceEntity::Reference  newValueTrace;

    public:
        LA32TracedGPRPreModifyEventBase(unsigned int index, arch32_t oldValue, arch32_t newValue) noexcept;

        unsigned int                GetIndex() const noexcept;
        void                        SetIndex(unsigned int index) noexcept;

        arch32_t                    GetOldValue() const noexcept;
        void                        SetOldValue(arch32_t value) noexcept;

        arch32_t                    GetNewValue() const noexcept;
        void                        SetNewValue(arch32_t value) noexcept;
        void                        SetNewValue(arch32_t value, LA32TraceEntity::Reference trace) noexcept;

        bool                        IsIndexModified() const noexcept;
        bool                        IsNewValueModified() const noexcept;

        LA32TraceEntity::Reference  GetNewValueTrace() const noexcept;
    };

    // LA32 Traced GPR Post-Modification Event Base
    class LA32TracedGPRPostModifyEventBase {
    private:
        unsigned int                index;
        arch32_t                    oldValue;
        arch32_t                    newValue;

    public:
        LA32TracedGPRPostModifyEventBase(unsigned int index, arch32_t oldValue, arch32_t newValue) noexcept;

        unsigned int                GetIndex() const noexcept;
        arch32_t                    GetOldValue() const noexcept;
        arch32_t                    GetNewValue() const noexcept;
    };


    // LA32 Traced Memory Pre-Load Event 
    class LA32TracedMemoryPreLoadEventBase {
    private:
        addr_t                      address;
        LA32MOPWidth                width;

        bool                        addressModified;
        LA32TraceEntity::Reference  addressTrace;

    public:
        LA32TracedMemoryPreLoadEventBase(addr_t address, LA32MOPWidth width) noexcept;

        addr_t                      GetAddress() const noexcept;
        void                        SetAddress(addr_t address) noexcept;
        void                        SetAddress(addr_t address, LA32TraceEntity::Reference trace) noexcept;

        LA32MOPWidth                GetWidth() const noexcept;
        void                        SetWidth(LA32MOPWidth width) noexcept;

        bool                        IsAddressModified() const noexcept;
        LA32TraceEntity::Reference  GetAddressTrace() const noexcept;
    };

    // LA32 Traced Memory Pre-Post-Load Event Base
    class LA32TracedMemoryPrePostLoadEventBase {
    private:
        addr_t                      address;
        LA32MOPWidth                width;
        memdata_t                   data;

        bool                        dataModified;
        LA32TraceEntity::Reference  dataTrace;
        
    public:
        LA32TracedMemoryPrePostLoadEventBase(addr_t address, LA32MOPWidth width, memdata_t data) noexcept;

        LA32MOPWidth                GetWidth() const noexcept;
        addr_t                      GetAddress() const noexcept;

        memdata_t                   GetData() const noexcept;
        void                        SetData(memdata_t data) noexcept;
        void                        SetData(memdata_t data, LA32TraceEntity::Reference trace) noexcept;

        bool                        IsDataModified() const noexcept;
        LA32TraceEntity::Reference  GetDataTrace() const noexcept;
    };

    // LA32 Traced Memory Post-Post-Load Event Base
    class LA32TracedMemoryPostPostLoadEventBase {
    private:
        addr_t                      address;
        LA32MOPWidth                width;
        arch32_t                    value;

    public:
        LA32TracedMemoryPostPostLoadEventBase(addr_t address, LA32MOPWidth width, arch32_t value) noexcept;

        LA32MOPWidth                GetWidth() const noexcept;
        addr_t                      GetAddress() const noexcept;
        arch32_t                    GetValue() const noexcept;
    };


    // LA32 Traced Memory Pre-Store Event Base
    class LA32TracedMemoryPreStoreEventBase {
    private:
        addr_t                      address;
        LA32MOPWidth                width;
        memdata_t                   data;

        bool                        addressModified;
        LA32TraceEntity::Reference  addressTrace;

        bool                        dataModified;
        LA32TraceEntity::Reference  dataTrace;

    public:
        LA32TracedMemoryPreStoreEventBase(addr_t address, LA32MOPWidth width, memdata_t data) noexcept;

        addr_t                      GetAddress() const noexcept;
        void                        SetAddress(addr_t address) noexcept;
        void                        SetAddress(addr_t address, LA32TraceEntity::Reference trace) noexcept;

        LA32MOPWidth                GetWidth() const noexcept;
        void                        SetWidth(LA32MOPWidth width) noexcept;

        memdata_t                   GetData() const noexcept;
        void                        SetData(memdata_t data) noexcept;
        void                        SetData(memdata_t data, LA32TraceEntity::Reference trace) noexcept;

        bool                        IsAddressModified() const noexcept;
        LA32TraceEntity::Reference  GetAddressTrace() const noexcept;

        bool                        IsDataModified() const noexcept;
        LA32TraceEntity::Reference  GetDataTrace() const noexcept;
    };

    // LA32 Traced Memory Post-Store Event Base
    class LA32TracedMemoryPostStoreEventBase {
    private:
        addr_t                      address;
        LA32MOPWidth                width;
        memdata_t                   data;

    public:
        LA32TracedMemoryPostStoreEventBase(addr_t address, LA32MOPWidth width, memdata_t data) noexcept;

        addr_t                      GetAddress() const noexcept;
        LA32MOPWidth                GetWidth() const noexcept;
        memdata_t                   GetData() const noexcept;
    };


    // LA32 Instruction Pre-Fetch (in instance) Event
    class LA32InstructionPreFetchEvent
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public BullsEye::Event<LA32InstructionPreFetchEvent>
        , public BullsEye::CancellableEvent {
    public:
        LA32InstructionPreFetchEvent(
            LA32Instance&       instance, 
            pc_t                pc) noexcept;
    };

    // LA32 Instruction Post-Fetch (in instance) Event
    class LA32InstructionPostFetchEvent
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32RawInstructionEventBase
        , public BullsEye::Event<LA32InstructionPostFetchEvent> {
    public:
        LA32InstructionPostFetchEvent(
            LA32Instance&       instance, 
            pc_t                pc, 
            insnraw_t           insn) noexcept;
    };

    // LA32 Instruction Pre-Decode (in instance) Event
    class LA32InstructionPreDecodeEvent 
        : public LA32InstanceEventBase
        , public LA32PCEventBase 
        , public LA32InstructionEventBase 
        , public BullsEye::Event<LA32InstructionPreDecodeEvent>
        , public BullsEye::CancellableEvent {
    public:
        LA32InstructionPreDecodeEvent(
            LA32Instance&       instance,
            pc_t                pc,
            LA32Instruction&    insn) noexcept;
    };

    // LA32 Instruction Post-Decode (in instance) Event
    class LA32InstructionPostDecodeEvent 
        : public LA32InstanceEventBase
        , public LA32PCEventBase 
        , public LA32InstructionEventBase 
        , public BullsEye::Event<LA32InstructionPostDecodeEvent> {
    public:
        LA32InstructionPostDecodeEvent(
            LA32Instance&       instance,
            pc_t                pc,
            LA32Instruction&  insn) noexcept;
    };


    // LA32 Instruction Pre-Execution (in instance) Event
    class LA32InstructionPreExecutionEvent 
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32InstructionEventBase
        , public BullsEye::Event<LA32InstructionPreExecutionEvent>
        , public BullsEye::CancellableEvent {
    public:
        LA32InstructionPreExecutionEvent(
            LA32Instance&       instance, 
            pc_t                pc, 
            LA32Instruction&    insn) noexcept;
    };


    // LA32 Instruction Post-Execution (in instance) Event
    class LA32InstructionPostExecutionEvent 
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32ConstInstructionEventBase
        , public LA32ExecOutcomeEventBase
        , public BullsEye::Event<LA32InstructionPostExecutionEvent> {
    public:
        LA32InstructionPostExecutionEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            LA32ExecOutcome             outcome) noexcept;
    };


    // LA32 PC Iteration (in instance) Event
    class LA32PCIterationEvent
        : public LA32InstanceEventBase
        , public LA32PCChangeEventBase
        , public BullsEye::Event<LA32PCIterationEvent> {
    public:
        enum class Action {
            SEQUENTIAL = 0,
            BRANCH_TAKEN,
            BRANCH_NOT_TAKEN
        };

    private:
        Action  action;

    public:
        LA32PCIterationEvent(
            LA32Instance&       instance, 
            pc_t                old_pc, 
            pc_t                new_pc, 
            Action              action) noexcept;

        Action                      GetAction() const noexcept;
        void                        SetAction(Action action) noexcept;
    };

    
    // LA32 Instruction GPR Pre-Modify (in execution) Event
    class LA32InstructionGPRPreModifyEvent
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32ConstInstructionEventBase
        , public LA32GPRPreModifyEventBase
        , public BullsEye::Event<LA32InstructionGPRPreModifyEvent>
        , public BullsEye::CancellableEvent {
    public:
        LA32InstructionGPRPreModifyEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            unsigned int                index,
            arch32_t                    oldValue,
            arch32_t                    newValue) noexcept;
    };

    // LA32 Instruction GPR Post-Modify (in execution) Event
    class LA32InstructionGPRPostModifyEvent
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32ConstInstructionEventBase
        , public LA32GPRPostModifyEventBase
        , public BullsEye::Event<LA32InstructionGPRPostModifyEvent>
        , public BullsEye::CancellableEvent {
    public:
        LA32InstructionGPRPostModifyEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            unsigned int                index,
            arch32_t                    oldValue,
            arch32_t                    newValue) noexcept;
    };


    // LA32 Traced Instruction GPR Pre-Modify (in execution) Event
    class LA32TracedInstructionGPRPreModifyEvent
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32ConstInstructionEventBase
        , public LA32TracedGPRPreModifyEventBase
        , public BullsEye::Event<LA32TracedInstructionGPRPreModifyEvent>
        , public BullsEye::CancellableEvent {
    public:
        LA32TracedInstructionGPRPreModifyEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            unsigned int                index,
            arch32_t                    oldValue,
            arch32_t                    newValue) noexcept;
    };

    // LA32 Traced Instruction GPR Post-Modify (in execution) Event
    class LA32TracedInstructionGPRPostModifyEvent
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32ConstInstructionEventBase
        , public LA32TracedGPRPostModifyEventBase
        , public BullsEye::Event<LA32TracedInstructionGPRPostModifyEvent>
        , public BullsEye::CancellableEvent {
    public:
        LA32TracedInstructionGPRPostModifyEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            unsigned int                index,
            arch32_t                    oldValue,
            arch32_t                    newValue) noexcept;
    };


    // LA32 Instruction GPR Read (in execution) Event
    class LA32InstructionGPRReadEvent
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32ConstInstructionEventBase
        , public LA32GPREventBase
        , public BullsEye::Event<LA32InstructionGPRReadEvent>
        , public BullsEye::CancellableEvent {
    private:
        unsigned int    ordinal;
        bool            last;

    public:
        LA32InstructionGPRReadEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            unsigned int                index,
            arch32_t                    value,
            unsigned int                ordinal,
            bool                        last) noexcept;

        unsigned int                GetOrdinal() const noexcept;
        bool                        IsLast() const noexcept;
    };

    // LA32 Instruction GPR Post-Read (in execution) Event
    class LA32InstructionGPRPostReadEvent
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32ConstInstructionEventBase
        , public LA32GPREventBase
        , public BullsEye::Event<LA32InstructionGPRPostReadEvent>
        , public BullsEye::CancellableEvent {
    private:
        unsigned int    ordinal;
        bool            last;

    public:
        LA32InstructionGPRPostReadEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            unsigned int                index,
            arch32_t                    value,
            unsigned int                ordinal,
            bool                        last) noexcept;

        unsigned int                GetOrdinal() const noexcept;
        bool                        IsLast() const noexcept;
    };


    // LA32 Traced Instruction GPR Read (in execution) Event
    class LA32TracedInstructionGPRReadEvent
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32ConstInstructionEventBase
        , public LA32TracedGPREventBase
        , public BullsEye::Event<LA32TracedInstructionGPRReadEvent>
        , public BullsEye::CancellableEvent {
    private:
        unsigned int    ordinal;
        bool            last;

    public:
        LA32TracedInstructionGPRReadEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            unsigned int                index,
            arch32_t                    value,
            unsigned int                ordinal,
            bool                        last) noexcept;

        unsigned int                GetOrdinal() const noexcept;
        bool                        IsLast() const noexcept;
    };

    // LA32 Traced Instruction GPR Post-Read (in execution) Event
    class LA32TracedInstructionGPRPostReadEvent
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32ConstInstructionEventBase
        , public LA32TracedGPREventBase
        , public BullsEye::Event<LA32TracedInstructionGPRPostReadEvent>
        , public BullsEye::CancellableEvent {
    private:
        unsigned int    ordinal;
        bool            last;

    public:
        LA32TracedInstructionGPRPostReadEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            unsigned int                index,
            arch32_t                    value,
            unsigned int                ordinal,
            bool                        last) noexcept;

        unsigned int                GetOrdinal() const noexcept;
        bool                        IsLast() const noexcept;
    };


    // LA32 Traced Memory Pre-Load Event
    class LA32TracedMemoryPreLoadEvent
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32ConstInstructionEventBase
        , public LA32TracedMemoryPreLoadEventBase
        , public BullsEye::Event<LA32TracedMemoryPreLoadEvent>
        , public BullsEye::CancellableEvent {
    public:
        LA32TracedMemoryPreLoadEvent(
            LA32Instance&               instance,
            pc_t                        pc,
            const LA32Instruction&      insn,
            addr_t                      address,
            LA32MOPWidth                width) noexcept;
    };

    // LA32 Traced Memory Pre-Post-Load Event
    class LA32TracedMemoryPrePostLoadEvent
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32ConstInstructionEventBase
        , public LA32TracedMemoryPrePostLoadEventBase
        , public BullsEye::Event<LA32TracedMemoryPrePostLoadEvent>
        , public BullsEye::CancellableEvent {
    public:
        LA32TracedMemoryPrePostLoadEvent(
            LA32Instance&               instance,
            pc_t                        pc,
            const LA32Instruction&      insn,
            addr_t                      address,
            LA32MOPWidth                width,
            memdata_t                   data) noexcept;
    };

    // LA32 Traced Memory Post-Post-Load Event
    class LA32TracedMemoryPostPostLoadEvent
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32ConstInstructionEventBase
        , public LA32TracedMemoryPostPostLoadEventBase
        , public BullsEye::Event<LA32TracedMemoryPostPostLoadEvent> {
    public:
        LA32TracedMemoryPostPostLoadEvent(
            LA32Instance&               instance,
            pc_t                        pc,
            const LA32Instruction&      insn,
            addr_t                      address,
            LA32MOPWidth                width,
            arch32_t                    value) noexcept;
    };


    // LA32 Traced Memory Pre-Store Event
    class LA32TracedMemoryPreStoreEvent
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32ConstInstructionEventBase
        , public LA32TracedMemoryPreStoreEventBase
        , public BullsEye::Event<LA32TracedMemoryPreStoreEvent>
        , public BullsEye::CancellableEvent {
    public:
        LA32TracedMemoryPreStoreEvent(
            LA32Instance&               instance,
            pc_t                        pc,
            const LA32Instruction&      insn,
            addr_t                      address,
            LA32MOPWidth                width,
            memdata_t                   data) noexcept;
    };

    // LA32 Traced Memory Post-Store Event
    class LA32TracedMemoryPostStoreEvent
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32ConstInstructionEventBase
        , public LA32TracedMemoryPostStoreEventBase
        , public BullsEye::Event<LA32TracedMemoryPostStoreEvent> {
    public:
        LA32TracedMemoryPostStoreEvent(
            LA32Instance&               instance,
            pc_t                        pc,
            const LA32Instruction&      insn,
            addr_t                      address,
            LA32MOPWidth                width,
            memdata_t                   data) noexcept;
    };
}



// Implementation of: class LA32InstanceEventBase
namespace Jasse {
    //
    // LA32Instance&     instance;
    // 

    inline LA32InstanceEventBase::LA32InstanceEventBase(LA32Instance& instance) noexcept
        : instance  (instance)
    { }

    inline LA32Instance& LA32InstanceEventBase::GetInstance() noexcept
    {
        return instance;
    }

    inline const LA32Instance& LA32InstanceEventBase::GetInstance() const noexcept
    {
        return instance;
    }
}


// Implementation of: class LA32PCEventBase
namespace Jasse {
    //
    // pc_t                pc;
    //

    inline LA32PCEventBase::LA32PCEventBase(pc_t pc) noexcept
        : pc    (pc)
    { }

    inline pc_t LA32PCEventBase::GetPC() const noexcept
    {
        return pc;
    }

    inline void LA32PCEventBase::SetPC(pc_t pc) noexcept
    {
        this->pc = pc;
    }
}


// Implementation of: class LA32PCChangeEventBase
namespace Jasse {
    //
    // pc_t                old_pc;
    // pc_t                new_pc;
    //

    inline LA32PCChangeEventBase::LA32PCChangeEventBase(pc_t old_pc, pc_t new_pc) noexcept
        : old_pc    (old_pc)
        , new_pc    (new_pc)
    { }

    inline pc_t LA32PCChangeEventBase::GetOldPC() const noexcept
    {
        return old_pc;
    }

    inline void LA32PCChangeEventBase::SetOldPC(pc_t value) noexcept
    {
        old_pc = value;
    }

    inline pc_t LA32PCChangeEventBase::GetNewPC() const noexcept
    {
        return new_pc;
    }

    inline void LA32PCChangeEventBase::SetNewPC(pc_t value) noexcept
    {
        new_pc = value;
    }
}


// Implementation of: class LA32InstructionEventBase
namespace Jasse {
    //
    // LA32Instruction&  insn;
    //

    inline LA32InstructionEventBase::LA32InstructionEventBase(LA32Instruction& insn) noexcept
        : insn  (insn)
    { }

    inline LA32Instruction& LA32InstructionEventBase::GetInstruction() noexcept
    {
        return insn;
    }

    inline const LA32Instruction& LA32InstructionEventBase::GetInstruction() const noexcept
    {
        return insn;
    }

    inline void LA32InstructionEventBase::SetInstruction(const LA32Instruction& insn) noexcept
    {
        this->insn = insn;
    }
}


// Implementation of: class LA32ConstInstructionEventBase
namespace Jasse {
    //
    // const LA32Instruction& insn;
    //

    inline LA32ConstInstructionEventBase::LA32ConstInstructionEventBase(const LA32Instruction& insn) noexcept
        : insn  (insn)
    { }

    inline const LA32Instruction& LA32ConstInstructionEventBase::GetInstruction() const noexcept
    {
        return insn;
    }
}


// Implementation of: class LA32RawInstructionEventBase
namespace Jasse {
    //
    // insnraw_t           insn;
    //

    inline LA32RawInstructionEventBase::LA32RawInstructionEventBase(insnraw_t insn) noexcept
        : insn  (insn)
    { }

    inline insnraw_t LA32RawInstructionEventBase::GetInstruction() const noexcept
    {
        return insn;
    }

    inline void LA32RawInstructionEventBase::SetInstruction(insnraw_t insn) noexcept
    {
        this->insn = insn;
    }
}


// Implementation of: class LA32ExecOutcomeEventBase
namespace Jasse {
    //
    // LA32ExecOutcome   outcome;
    //

    inline LA32ExecOutcomeEventBase::LA32ExecOutcomeEventBase(LA32ExecOutcome outcome) noexcept
        : outcome   (outcome)
    { }

    inline LA32ExecOutcome LA32ExecOutcomeEventBase::GetOutcome() const noexcept
    {
        return outcome;
    }

    inline void LA32ExecOutcomeEventBase::SetOutcome(LA32ExecOutcome outcome) noexcept
    {
        this->outcome = outcome;
    }
}



// Implementation of: class LA32GPREventBase
namespace Jasse {
    //
    // unsigned int        index;
    // arch32_t            value;
    //

    inline LA32GPREventBase::LA32GPREventBase(unsigned int index, arch32_t value) noexcept
        : index (index)
        , value (value)
    { }

    inline unsigned int LA32GPREventBase::GetIndex() const noexcept
    {
        return index;
    }

    inline void LA32GPREventBase::SetIndex(unsigned int index) noexcept
    {
        this->index = index;
    }

    inline arch32_t LA32GPREventBase::GetValue() const noexcept
    {
        return value;
    }

    inline void LA32GPREventBase::SetValue(arch32_t value) noexcept
    {
        this->value = value;
    }
}


// Implementation of: class LA32GPRPostEventBase
namespace Jasse {
    //
    // unsigned int        index;
    // arch32_t            value;
    //

    inline LA32GPRPostEventBase::LA32GPRPostEventBase(unsigned int index, arch32_t value) noexcept
        : index (index)
        , value (value)
    { }

    inline unsigned int LA32GPRPostEventBase::GetIndex() const noexcept
    {
        return index;
    }

    inline arch32_t LA32GPRPostEventBase::GetValue() const noexcept
    {
        return value;
    }
}


// Implementation of: class LA32TracedGPREventBase
namespace Jasse {
    /*
    unsigned int                index;
    arch32_t                    value;

    bool                        indexModified;
    bool                        valueModified;
    LA32TraceEntity::Reference  valueTrace;
    */

    inline LA32TracedGPREventBase::LA32TracedGPREventBase(unsigned int index, arch32_t value) noexcept
        : index             (index)
        , value             (value)
        , indexModified     (false)
        , valueModified     (false)
        , valueTrace        ()
    { }

    inline unsigned int LA32TracedGPREventBase::GetIndex() const noexcept
    {
        return this->index;
    }

    inline void LA32TracedGPREventBase::SetIndex(unsigned int index) noexcept
    {
        this->index         = index;
        this->indexModified = true;
    }

    inline arch32_t LA32TracedGPREventBase::GetValue() const noexcept
    {
        return this->value;
    }

    inline void LA32TracedGPREventBase::SetValue(arch32_t value) noexcept
    {
        this->value         = value;
        this->valueModified = true;
    }

    inline void LA32TracedGPREventBase::SetValue(arch32_t value, LA32TraceEntity::Reference trace) noexcept
    {
        this->value         = value;
        this->valueModified = true;
        this->valueTrace    = trace;
    }

    inline bool LA32TracedGPREventBase::IsIndexModified() const noexcept
    {
        return this->indexModified;
    }

    inline bool LA32TracedGPREventBase::IsValueModified() const noexcept
    {
        return this->valueModified;
    }

    inline LA32TraceEntity::Reference LA32TracedGPREventBase::GetValueTrace() const noexcept
    {
        return this->valueTrace;
    }
}


// Implementation of: class LA32TracedGPRPostEventBase
namespace Jasse {
    /*
    unsigned int                index;
    arch32_t                    value;
    */

    inline LA32TracedGPRPostEventBase::LA32TracedGPRPostEventBase(unsigned int index, arch32_t value) noexcept
        : index (index)
        , value (value)
    { }

    inline unsigned int LA32TracedGPRPostEventBase::GetIndex() const noexcept
    {
        return this->index;
    }

    inline arch32_t LA32TracedGPRPostEventBase::GetValue() const noexcept
    {
        return this->value;
    }
}


// Implementation of: class LA32GPRPreModifyEventBase
namespace Jasse {
    //
    // unsigned int        index;
    // arch32_t            oldValue;
    // arch32_t            newValue;
    //

    inline LA32GPRPreModifyEventBase::LA32GPRPreModifyEventBase(unsigned int index, arch32_t oldValue, arch32_t newValue) noexcept
        : index     (index)
        , oldValue  (oldValue)
        , newValue  (newValue)
    { }

    inline unsigned int LA32GPRPreModifyEventBase::GetIndex() const noexcept
    {
        return index;
    }

    inline void LA32GPRPreModifyEventBase::SetIndex(unsigned int index) noexcept
    {
        this->index = index;
    }

    inline arch32_t LA32GPRPreModifyEventBase::GetOldValue() const noexcept
    {
        return oldValue;
    }

    inline void LA32GPRPreModifyEventBase::SetOldValue(arch32_t value) noexcept
    {
        oldValue = value;
    }

    inline arch32_t LA32GPRPreModifyEventBase::GetNewValue() const noexcept
    {
        return newValue;
    }

    inline void LA32GPRPreModifyEventBase::SetNewValue(arch32_t value) noexcept
    {
        newValue = value;
    }
}


// Implementation of: class LA32GPRPostModifyEventBase
namespace Jasse {
    //
    // unsigned int        index;
    // arch32_t            oldValue;
    // arch32_t            newValue;
    //

    inline LA32GPRPostModifyEventBase::LA32GPRPostModifyEventBase(unsigned int index, arch32_t oldValue, arch32_t newValue) noexcept
        : index     (index)
        , oldValue  (oldValue)
        , newValue  (newValue)
    { }

    inline unsigned int LA32GPRPostModifyEventBase::GetIndex() const noexcept
    {
        return index;
    }

    inline arch32_t LA32GPRPostModifyEventBase::GetOldValue() const noexcept
    {
        return oldValue;
    }

    inline arch32_t LA32GPRPostModifyEventBase::GetNewValue() const noexcept
    {
        return newValue;
    }
}


// Implementation of: class LA32TracedGPRPreModifyEventBase
namespace Jasse {
    /*
    unsigned int                index;
    arch32_t                    oldValue;
    arch32_t                    newValue;

    bool                        indexModified;
    bool                        newValueModified;
    LA32TraceEntity::Reference  newValueTrace;
    */

    inline LA32TracedGPRPreModifyEventBase::LA32TracedGPRPreModifyEventBase(unsigned int index, arch32_t oldValue, arch32_t newValue) noexcept
        : index             (index)
        , oldValue          (oldValue)
        , newValue          (newValue)
        , indexModified     (false)
        , newValueModified  (false)
        , newValueTrace     ()
    { }

    inline unsigned int LA32TracedGPRPreModifyEventBase::GetIndex() const noexcept
    {
        return index;
    }

    inline void LA32TracedGPRPreModifyEventBase::SetIndex(unsigned int index) noexcept
    {
        this->index         = index;
        this->indexModified = true;
    }

    inline arch32_t LA32TracedGPRPreModifyEventBase::GetOldValue() const noexcept
    {
        return this->oldValue;
    }

    inline void LA32TracedGPRPreModifyEventBase::SetOldValue(arch32_t value) noexcept
    {
        this->oldValue = value;
    }

    inline arch32_t LA32TracedGPRPreModifyEventBase::GetNewValue() const noexcept
    {
        return this->newValue;
    }

    inline void LA32TracedGPRPreModifyEventBase::SetNewValue(arch32_t value) noexcept
    {
        this->newValue         = value;
        this->newValueModified = true;
    }

    inline void LA32TracedGPRPreModifyEventBase::SetNewValue(arch32_t value, LA32TraceEntity::Reference trace) noexcept
    {
        this->newValue         = value;
        this->newValueModified = true;
        this->newValueTrace    = trace;
    }

    inline bool LA32TracedGPRPreModifyEventBase::IsIndexModified() const noexcept
    {
        return this->indexModified;
    }

    inline bool LA32TracedGPRPreModifyEventBase::IsNewValueModified() const noexcept
    {
        return this->newValueModified;
    }

    inline LA32TraceEntity::Reference LA32TracedGPRPreModifyEventBase::GetNewValueTrace() const noexcept
    {
        return this->newValueTrace;
    }
}


// Implementation of: class LA32TracedGPRPostModifyEventBase
namespace Jasse {
    /*
    unsigned int                index;
    arch32_t                    oldValue;
    arch32_t                    newValue;
    */

    inline LA32TracedGPRPostModifyEventBase::LA32TracedGPRPostModifyEventBase(unsigned int index, arch32_t oldValue, arch32_t newValue) noexcept
        : index     (index)
        , oldValue  (oldValue)
        , newValue  (newValue)
    { }

    inline unsigned int LA32TracedGPRPostModifyEventBase::GetIndex() const noexcept
    {
        return index;
    }

    inline arch32_t LA32TracedGPRPostModifyEventBase::GetOldValue() const noexcept
    {
        return oldValue;
    }

    inline arch32_t LA32TracedGPRPostModifyEventBase::GetNewValue() const noexcept
    {
        return newValue;
    }
}



// Implementation of: class LA32TracedMemoryPreLoadEventBase
namespace Jasse {
    /*
    addr_t                      address;
    LA32MOPWidth                width;

    bool                        addressModified;
    LA32TraceEntity::Reference  addressTrace;
    */

    inline LA32TracedMemoryPreLoadEventBase::LA32TracedMemoryPreLoadEventBase(addr_t address, LA32MOPWidth width) noexcept
        : address           (address)
        , width             (width)
        , addressModified   (false)
        , addressTrace      ()
    { }

    inline addr_t LA32TracedMemoryPreLoadEventBase::GetAddress() const noexcept
    {
        return address;
    }

    inline void LA32TracedMemoryPreLoadEventBase::SetAddress(addr_t address) noexcept
    {
        this->address           = address;
        this->addressModified   = true;
    }

    inline void LA32TracedMemoryPreLoadEventBase::SetAddress(addr_t address, LA32TraceEntity::Reference trace) noexcept
    {
        this->address           = address;
        this->addressModified   = true;
        this->addressTrace      = trace;
    }

    inline LA32MOPWidth LA32TracedMemoryPreLoadEventBase::GetWidth() const noexcept
    {
        return width;
    }

    inline void LA32TracedMemoryPreLoadEventBase::SetWidth(LA32MOPWidth width) noexcept
    {
        this->width = width;
    }

    inline bool LA32TracedMemoryPreLoadEventBase::IsAddressModified() const noexcept
    {
        return addressModified;
    }

    inline LA32TraceEntity::Reference LA32TracedMemoryPreLoadEventBase::GetAddressTrace() const noexcept
    {
        return addressTrace;
    }
}


// Implementation of: class LA32TracedMemoryPrePostLoadEventBase
namespace Jasse {
    /*
    addr_t                      address;
    LA32MOPWidth                width;
    memdata_t                   data;

    bool                        dataModified;
    LA32TraceEntity::Reference  dataTrace;
    */

    inline LA32TracedMemoryPrePostLoadEventBase::LA32TracedMemoryPrePostLoadEventBase(addr_t address, LA32MOPWidth width, memdata_t data) noexcept
        : address           (address)
        , width             (width)
        , data              (data)
        , dataModified      (false)
        , dataTrace         ()
    { }

    inline LA32MOPWidth LA32TracedMemoryPrePostLoadEventBase::GetWidth() const noexcept
    {
        return width;
    }

    inline addr_t LA32TracedMemoryPrePostLoadEventBase::GetAddress() const noexcept
    {
        return address;
    }

    inline memdata_t LA32TracedMemoryPrePostLoadEventBase::GetData() const noexcept
    {
        return data;
    }

    inline void LA32TracedMemoryPrePostLoadEventBase::SetData(memdata_t data) noexcept
    {
        this->data             = data;
        this->dataModified     = true;
    }

    inline void LA32TracedMemoryPrePostLoadEventBase::SetData(memdata_t data, LA32TraceEntity::Reference trace) noexcept
    {
        this->data             = data;
        this->dataModified     = true;
        this->dataTrace        = trace;
    }

    inline bool LA32TracedMemoryPrePostLoadEventBase::IsDataModified() const noexcept
    {
        return dataModified;
    }

    inline LA32TraceEntity::Reference LA32TracedMemoryPrePostLoadEventBase::GetDataTrace() const noexcept
    {
        return dataTrace;
    }
}


// Implementation of: class LA32TracedMemoryPostPostLoadEventBase
namespace Jasse {
    /*
    addr_t                      address;
    LA32MOPWidth                width;
    arch32_t                    value;
    */

    inline LA32TracedMemoryPostPostLoadEventBase::LA32TracedMemoryPostPostLoadEventBase(addr_t address, LA32MOPWidth width, arch32_t value) noexcept
        : address           (address)
        , width             (width)
        , value             (value)
    { }

    inline LA32MOPWidth LA32TracedMemoryPostPostLoadEventBase::GetWidth() const noexcept
    {
        return width;
    }

    inline addr_t LA32TracedMemoryPostPostLoadEventBase::GetAddress() const noexcept
    {
        return address;
    }

    inline arch32_t LA32TracedMemoryPostPostLoadEventBase::GetValue() const noexcept
    {
        return value;
    }
}



// Implementation of: class LA32TracedMemoryPreStoreEventBase
namespace Jasse {
    /*
    addr_t                      address;
    LA32MOPWidth                width;
    memdata_t                   data;

    bool                        addressModified;
    LA32TraceEntity::Reference  addressTrace;

    bool                        dataModified;
    LA32TraceEntity::Reference  dataTrace;
    */

    inline LA32TracedMemoryPreStoreEventBase::LA32TracedMemoryPreStoreEventBase(addr_t address, LA32MOPWidth width, memdata_t data) noexcept
        : address           (address)
        , width             (width)
        , data              (data)
        , addressModified   (false)
        , addressTrace      ()
        , dataModified      (false)
        , dataTrace         ()
    { }

    inline addr_t LA32TracedMemoryPreStoreEventBase::GetAddress() const noexcept
    {
        return address;
    }

    inline void LA32TracedMemoryPreStoreEventBase::SetAddress(addr_t address) noexcept
    {
        this->address           = address;
        this->addressModified   = true;
    }

    inline void LA32TracedMemoryPreStoreEventBase::SetAddress(addr_t address, LA32TraceEntity::Reference trace) noexcept
    {
        this->address           = address;
        this->addressModified   = true;
        this->addressTrace      = trace;
    }

    inline LA32MOPWidth LA32TracedMemoryPreStoreEventBase::GetWidth() const noexcept
    {
        return width;
    }

    inline void LA32TracedMemoryPreStoreEventBase::SetWidth(LA32MOPWidth width) noexcept
    {
        this->width = width;
    }

    inline memdata_t LA32TracedMemoryPreStoreEventBase::GetData() const noexcept
    {
        return data;
    }

    inline void LA32TracedMemoryPreStoreEventBase::SetData(memdata_t data) noexcept
    {
        this->data             = data;
        this->dataModified     = true;
    }

    inline void LA32TracedMemoryPreStoreEventBase::SetData(memdata_t data, LA32TraceEntity::Reference trace) noexcept
    {
        this->data             = data;
        this->dataModified     = true;
        this->dataTrace        = trace;
    }

    inline bool LA32TracedMemoryPreStoreEventBase::IsAddressModified() const noexcept
    {
        return addressModified;
    }

    inline LA32TraceEntity::Reference LA32TracedMemoryPreStoreEventBase::GetAddressTrace() const noexcept
    {
        return addressTrace;
    }

    inline bool LA32TracedMemoryPreStoreEventBase::IsDataModified() const noexcept
    {
        return dataModified;
    }

    inline LA32TraceEntity::Reference LA32TracedMemoryPreStoreEventBase::GetDataTrace() const noexcept
    {
        return dataTrace;
    }
}


// Implementation of: class LA32TracedMemoryPostStoreEventBase
namespace Jasse {
    /*
    addr_t                      address;
    LA32MOPWidth                width;
    memdata_t                   data;
    */

    inline LA32TracedMemoryPostStoreEventBase::LA32TracedMemoryPostStoreEventBase(addr_t address, LA32MOPWidth width, memdata_t data) noexcept
        : address           (address)
        , width             (width)
        , data              (data)
    { }

    inline LA32MOPWidth LA32TracedMemoryPostStoreEventBase::GetWidth() const noexcept
    {
        return width;
    }

    inline addr_t LA32TracedMemoryPostStoreEventBase::GetAddress() const noexcept
    {
        return address;
    }

    inline memdata_t LA32TracedMemoryPostStoreEventBase::GetData() const noexcept
    {
        return data;
    }
}



// Implementation of: class LA32InstructionPreFetchEvent
namespace Jasse {

    inline LA32InstructionPreFetchEvent::LA32InstructionPreFetchEvent(
            LA32Instance&       instance, 
            pc_t                pc) noexcept
        : LA32InstanceEventBase         (instance)
        , LA32PCEventBase               (pc)
    { }
}


// Implementation of: class LA32InstructionPostFetchEvent
namespace Jasse {

    inline LA32InstructionPostFetchEvent::LA32InstructionPostFetchEvent(
            LA32Instance&       instance, 
            pc_t                pc, 
            insnraw_t           insn) noexcept
        : LA32InstanceEventBase         (instance)
        , LA32PCEventBase               (pc)
        , LA32RawInstructionEventBase   (insn)
    { }
}



// Implementation of: class LA32InstructionPreDecodeEvent
namespace Jasse {

    inline LA32InstructionPreDecodeEvent::LA32InstructionPreDecodeEvent(
            LA32Instance&       instance,
            pc_t                pc,
            LA32Instruction&    insn) noexcept
        : LA32InstanceEventBase         (instance)
        , LA32PCEventBase               (pc)
        , LA32InstructionEventBase      (insn)
    { }
}


// Implementation of: class LA32InstructionPostDecodeEvent
namespace Jasse {

    inline LA32InstructionPostDecodeEvent::LA32InstructionPostDecodeEvent(
            LA32Instance&       instance,
            pc_t                pc,
            LA32Instruction&    insn) noexcept
        : LA32InstanceEventBase         (instance)
        , LA32PCEventBase               (pc)
        , LA32InstructionEventBase      (insn)
    { }
}



// Implementation of: class LA32InstructionPreExecutionEvent
namespace Jasse {

    inline LA32InstructionPreExecutionEvent::LA32InstructionPreExecutionEvent(
            LA32Instance&       instance, 
            pc_t                pc, 
            LA32Instruction&    insn) noexcept
        : LA32InstanceEventBase         (instance)
        , LA32PCEventBase               (pc)
        , LA32InstructionEventBase      (insn)
    { }
}


// Implementation of: class LA32InstructionPostExecutionEvent
namespace Jasse {

    inline LA32InstructionPostExecutionEvent::LA32InstructionPostExecutionEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            LA32ExecOutcome             outcome) noexcept
        : LA32InstanceEventBase         (instance)
        , LA32PCEventBase               (pc)
        , LA32ConstInstructionEventBase (insn)
        , LA32ExecOutcomeEventBase      (outcome)
    { }
}



// Implementation of: class LA32PCIterationEvent
namespace Jasse {
    //
    // Action  action;
    //

    inline LA32PCIterationEvent::LA32PCIterationEvent(
            LA32Instance&       instance, 
            pc_t                old_pc, 
            pc_t                new_pc, 
            Action              action) noexcept
        : LA32InstanceEventBase         (instance)
        , LA32PCChangeEventBase         (old_pc, new_pc)
        , action                        (action)
    { }

    inline LA32PCIterationEvent::Action LA32PCIterationEvent::GetAction() const noexcept
    {
        return action;
    }

    inline void LA32PCIterationEvent::SetAction(LA32PCIterationEvent::Action action) noexcept
    {
        this->action = action;
    }
}



// Implementation of: class LA32InstructionGPRPreModifyEvent
namespace Jasse {
    
    inline LA32InstructionGPRPreModifyEvent::LA32InstructionGPRPreModifyEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            unsigned int                index,
            arch32_t                    oldValue,
            arch32_t                    newValue) noexcept
        : LA32InstanceEventBase             (instance)
        , LA32PCEventBase                   (pc)
        , LA32ConstInstructionEventBase     (insn)
        , LA32GPRPreModifyEventBase         (index, oldValue, newValue)
    { }
}


// Implementation of: class LA32InstructionGPRPostModifyEvent
namespace Jasse {

    inline LA32InstructionGPRPostModifyEvent::LA32InstructionGPRPostModifyEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            unsigned int                index,
            arch32_t                    oldValue,
            arch32_t                    newValue) noexcept
        : LA32InstanceEventBase             (instance)
        , LA32PCEventBase                   (pc)
        , LA32ConstInstructionEventBase     (insn)
        , LA32GPRPostModifyEventBase        (index, oldValue, newValue)
    { }
}


// Implementation of: class LA32TracedInstructionGPRPreModifyEvent
namespace Jasse {
        
    inline LA32TracedInstructionGPRPreModifyEvent::LA32TracedInstructionGPRPreModifyEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            unsigned int                index,
            arch32_t                    oldValue,
            arch32_t                    newValue) noexcept
        : LA32InstanceEventBase             (instance)
        , LA32PCEventBase                   (pc)
        , LA32ConstInstructionEventBase     (insn)
        , LA32TracedGPRPreModifyEventBase   (index, oldValue, newValue)
    { }
}


// Implementation of: class LA32TracedInstructionGPRPostModifyEvent
namespace Jasse {

    inline LA32TracedInstructionGPRPostModifyEvent::LA32TracedInstructionGPRPostModifyEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            unsigned int                index,
            arch32_t                    oldValue,
            arch32_t                    newValue) noexcept
        : LA32InstanceEventBase             (instance)
        , LA32PCEventBase                   (pc)
        , LA32ConstInstructionEventBase     (insn)
        , LA32TracedGPRPostModifyEventBase  (index, oldValue, newValue)
    { }
}



// Implementation of: class LA32InstructionGPRReadEvent
namespace Jasse {
    //
    // unsigned int    ordinal;
    // bool            last;
    //

    inline LA32InstructionGPRReadEvent::LA32InstructionGPRReadEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            unsigned int                index,
            arch32_t                    value,
            unsigned int                ordinal,
            bool                        last) noexcept
        : LA32InstanceEventBase         (instance)
        , LA32PCEventBase               (pc)
        , LA32ConstInstructionEventBase (insn)
        , LA32GPREventBase              (index, value)
        , ordinal                       (ordinal)
        , last                          (last)
    { }

    inline unsigned int LA32InstructionGPRReadEvent::GetOrdinal() const noexcept
    {
        return ordinal;
    }

    inline bool LA32InstructionGPRReadEvent::IsLast() const noexcept
    {
        return last;
    }
}


// Implementation of: class LA32InstructionGPRPostReadEvent
namespace Jasse {
    //
    // unsigned int    ordinal;
    // bool            last;
    //

    inline LA32InstructionGPRPostReadEvent::LA32InstructionGPRPostReadEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            unsigned int                index,
            arch32_t                    value,
            unsigned int                ordinal,
            bool                        last) noexcept
        : LA32InstanceEventBase         (instance)
        , LA32PCEventBase               (pc)
        , LA32ConstInstructionEventBase (insn)
        , LA32GPREventBase              (index, value)
        , ordinal                       (ordinal)
        , last                          (last)
    { }

    inline unsigned int LA32InstructionGPRPostReadEvent::GetOrdinal() const noexcept
    {
        return ordinal;
    }

    inline bool LA32InstructionGPRPostReadEvent::IsLast() const noexcept
    {
        return last;
    }
}


// Implementation of: class LA32TracedInstructionGPRReadEvent
namespace Jasse {
    //
    // unsigned int    ordinal;
    // bool            last;
    //

    inline LA32TracedInstructionGPRReadEvent::LA32TracedInstructionGPRReadEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            unsigned int                index,
            arch32_t                    value,
            unsigned int                ordinal,
            bool                        last) noexcept
        : LA32InstanceEventBase         (instance)
        , LA32PCEventBase               (pc)
        , LA32ConstInstructionEventBase (insn)
        , LA32TracedGPREventBase        (index, value)
        , ordinal                       (ordinal)
        , last                          (last)
    { }

    inline unsigned int LA32TracedInstructionGPRReadEvent::GetOrdinal() const noexcept
    {
        return ordinal;
    }

    inline bool LA32TracedInstructionGPRReadEvent::IsLast() const noexcept
    {
        return last;
    }
}


// Implementation of: class LA32TracedInstructionGPRPostReadEvent
namespace Jasse {
    //
    // unsigned int    ordinal;
    // bool            last;
    //

    inline LA32TracedInstructionGPRPostReadEvent::LA32TracedInstructionGPRPostReadEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            unsigned int                index,
            arch32_t                    value,
            unsigned int                ordinal,
            bool                        last) noexcept
        : LA32InstanceEventBase         (instance)
        , LA32PCEventBase               (pc)
        , LA32ConstInstructionEventBase (insn)
        , LA32TracedGPREventBase        (index, value)
        , ordinal                       (ordinal)
        , last                          (last)
    { }

    inline unsigned int LA32TracedInstructionGPRPostReadEvent::GetOrdinal() const noexcept
    {
        return ordinal;
    }

    inline bool LA32TracedInstructionGPRPostReadEvent::IsLast() const noexcept
    {
        return last;
    }
}



// Implementation of: class LA32TracedMemoryPreLoadEvent
namespace Jasse {
    
    inline LA32TracedMemoryPreLoadEvent::LA32TracedMemoryPreLoadEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            addr_t                      address,
            LA32MOPWidth                width) noexcept
        : LA32InstanceEventBase             (instance)
        , LA32PCEventBase                   (pc)
        , LA32ConstInstructionEventBase     (insn)
        , LA32TracedMemoryPreLoadEventBase  (address, width)
    { }
}


// Implementation of: class LA32TracedMemoryPrePostLoadEvent
namespace Jasse {

    inline LA32TracedMemoryPrePostLoadEvent::LA32TracedMemoryPrePostLoadEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            addr_t                      address,
            LA32MOPWidth                width,
            memdata_t                   data) noexcept
        : LA32InstanceEventBase                 (instance)
        , LA32PCEventBase                       (pc)
        , LA32ConstInstructionEventBase         (insn)
        , LA32TracedMemoryPrePostLoadEventBase  (address, width, data)
    { }
}


// Implementation of: class LA32TracedMemoryPostPostLoadEvent
namespace Jasse {

    inline LA32TracedMemoryPostPostLoadEvent::LA32TracedMemoryPostPostLoadEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            addr_t                      address,
            LA32MOPWidth                width,
            arch32_t                    value) noexcept
        : LA32InstanceEventBase                 (instance)
        , LA32PCEventBase                       (pc)
        , LA32ConstInstructionEventBase         (insn)
        , LA32TracedMemoryPostPostLoadEventBase (address, width, value)
    { }
}



// Implementation of: class LA32TracedMemoryPreStoreEvent
namespace Jasse {

    inline LA32TracedMemoryPreStoreEvent::LA32TracedMemoryPreStoreEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            addr_t                      address,
            LA32MOPWidth                width,
            memdata_t                   data) noexcept
        : LA32InstanceEventBase             (instance)
        , LA32PCEventBase                   (pc)
        , LA32ConstInstructionEventBase     (insn)
        , LA32TracedMemoryPreStoreEventBase (address, width, data)
    { }
}


// Implementation of: class LA32TracedMemoryPostStoreEvent
namespace Jasse {

    inline LA32TracedMemoryPostStoreEvent::LA32TracedMemoryPostStoreEvent(
            LA32Instance&               instance, 
            pc_t                        pc, 
            const LA32Instruction&      insn,
            addr_t                      address,
            LA32MOPWidth                width,
            memdata_t                   data) noexcept
        : LA32InstanceEventBase             (instance)
        , LA32PCEventBase                   (pc)
        , LA32ConstInstructionEventBase     (insn)
        , LA32TracedMemoryPostStoreEventBase(address, width, data)
    { }
}
