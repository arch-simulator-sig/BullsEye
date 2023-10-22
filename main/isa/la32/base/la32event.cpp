#include "la32event.hpp"
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
// Basic Event Infrastructures
//


// Implementation of: class LA32InstanceEventBase
namespace Jasse {
    //
    // LA32Instance&     instance;
    // 

    LA32InstanceEventBase::LA32InstanceEventBase(LA32Instance& instance) noexcept
        : instance  (instance)
    { }

    LA32Instance& LA32InstanceEventBase::GetInstance() noexcept
    {
        return instance;
    }

    const LA32Instance& LA32InstanceEventBase::GetInstance() const noexcept
    {
        return instance;
    }
}


// Implementation of: class LA32PCEventBase
namespace Jasse {
    //
    // pc_t                pc;
    //

    LA32PCEventBase::LA32PCEventBase(pc_t pc) noexcept
        : pc    (pc)
    { }

    pc_t LA32PCEventBase::GetPC() const noexcept
    {
        return pc;
    }

    void LA32PCEventBase::SetPC(pc_t pc) noexcept
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

    LA32PCChangeEventBase::LA32PCChangeEventBase(pc_t old_pc, pc_t new_pc) noexcept
        : old_pc    (old_pc)
        , new_pc    (new_pc)
    { }

    pc_t LA32PCChangeEventBase::GetOldPC() const noexcept
    {
        return old_pc;
    }

    void LA32PCChangeEventBase::SetOldPC(pc_t value) noexcept
    {
        old_pc = value;
    }

    pc_t LA32PCChangeEventBase::GetNewPC() const noexcept
    {
        return new_pc;
    }

    void LA32PCChangeEventBase::SetNewPC(pc_t value) noexcept
    {
        new_pc = value;
    }
}


// Implementation of: class LA32InstructionEventBase
namespace Jasse {
    //
    // LA32Instruction&  insn;
    //

    LA32InstructionEventBase::LA32InstructionEventBase(LA32Instruction& insn) noexcept
        : insn  (insn)
    { }

    LA32Instruction& LA32InstructionEventBase::GetInstruction() noexcept
    {
        return insn;
    }

    const LA32Instruction& LA32InstructionEventBase::GetInstruction() const noexcept
    {
        return insn;
    }

    void LA32InstructionEventBase::SetInstruction(const LA32Instruction& insn) noexcept
    {
        this->insn = insn;
    }
}


// Implementation of: class LA32ConstInstructionEventBase
namespace Jasse {
    //
    // const LA32Instruction& insn;
    //

    LA32ConstInstructionEventBase::LA32ConstInstructionEventBase(const LA32Instruction& insn) noexcept
        : insn  (insn)
    { }

    const LA32Instruction& LA32ConstInstructionEventBase::GetInstruction() const noexcept
    {
        return insn;
    }
}


// Implementation of: class LA32RawInstructionEventBase
namespace Jasse {
    //
    // insnraw_t           insn;
    //

    LA32RawInstructionEventBase::LA32RawInstructionEventBase(insnraw_t insn) noexcept
        : insn  (insn)
    { }

    insnraw_t LA32RawInstructionEventBase::GetInstruction() const noexcept
    {
        return insn;
    }

    void LA32RawInstructionEventBase::SetInstruction(insnraw_t insn) noexcept
    {
        this->insn = insn;
    }
}


// Implementation of: class LA32ExecOutcomeEventBase
namespace Jasse {
    //
    // LA32ExecOutcome   outcome;
    //

    LA32ExecOutcomeEventBase::LA32ExecOutcomeEventBase(LA32ExecOutcome outcome) noexcept
        : outcome   (outcome)
    { }

    LA32ExecOutcome LA32ExecOutcomeEventBase::GetOutcome() const noexcept
    {
        return outcome;
    }

    void LA32ExecOutcomeEventBase::SetOutcome(LA32ExecOutcome outcome) noexcept
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

    LA32GPREventBase::LA32GPREventBase(unsigned int index, arch32_t value) noexcept
        : index (index)
        , value (value)
    { }

    unsigned int LA32GPREventBase::GetIndex() const noexcept
    {
        return index;
    }

    void LA32GPREventBase::SetIndex(unsigned int index) noexcept
    {
        this->index = index;
    }

    arch32_t LA32GPREventBase::GetValue() const noexcept
    {
        return value;
    }

    void LA32GPREventBase::SetValue(arch32_t value) noexcept
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

    LA32GPRPostEventBase::LA32GPRPostEventBase(unsigned int index, arch32_t value) noexcept
        : index (index)
        , value (value)
    { }

    unsigned int LA32GPRPostEventBase::GetIndex() const noexcept
    {
        return index;
    }

    arch32_t LA32GPRPostEventBase::GetValue() const noexcept
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

    LA32TracedGPREventBase::LA32TracedGPREventBase(unsigned int index, arch32_t value) noexcept
        : index             (index)
        , value             (value)
        , indexModified     (false)
        , valueModified     (false)
        , valueTrace        ()
    { }

    unsigned int LA32TracedGPREventBase::GetIndex() const noexcept
    {
        return this->index;
    }

    void LA32TracedGPREventBase::SetIndex(unsigned int index) noexcept
    {
        this->index         = index;
        this->indexModified = true;
    }

    arch32_t LA32TracedGPREventBase::GetValue() const noexcept
    {
        return this->value;
    }

    void LA32TracedGPREventBase::SetValue(arch32_t value) noexcept
    {
        this->value         = value;
        this->valueModified = true;
    }

    void LA32TracedGPREventBase::SetValue(arch32_t value, LA32TraceEntity::Reference trace) noexcept
    {
        this->value         = value;
        this->valueModified = true;
        this->valueTrace    = trace;
    }

    bool LA32TracedGPREventBase::IsIndexModified() const noexcept
    {
        return this->indexModified;
    }

    bool LA32TracedGPREventBase::IsValueModified() const noexcept
    {
        return this->valueModified;
    }

    LA32TraceEntity::Reference LA32TracedGPREventBase::GetValueTrace() const noexcept
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

    LA32TracedGPRPostEventBase::LA32TracedGPRPostEventBase(unsigned int index, arch32_t value) noexcept
        : index (index)
        , value (value)
    { }

    unsigned int LA32TracedGPRPostEventBase::GetIndex() const noexcept
    {
        return this->index;
    }

    arch32_t LA32TracedGPRPostEventBase::GetValue() const noexcept
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

    LA32GPRPreModifyEventBase::LA32GPRPreModifyEventBase(unsigned int index, arch32_t oldValue, arch32_t newValue) noexcept
        : index     (index)
        , oldValue  (oldValue)
        , newValue  (newValue)
    { }

    unsigned int LA32GPRPreModifyEventBase::GetIndex() const noexcept
    {
        return index;
    }

    void LA32GPRPreModifyEventBase::SetIndex(unsigned int index) noexcept
    {
        this->index = index;
    }

    arch32_t LA32GPRPreModifyEventBase::GetOldValue() const noexcept
    {
        return oldValue;
    }

    void LA32GPRPreModifyEventBase::SetOldValue(arch32_t value) noexcept
    {
        oldValue = value;
    }

    arch32_t LA32GPRPreModifyEventBase::GetNewValue() const noexcept
    {
        return newValue;
    }

    void LA32GPRPreModifyEventBase::SetNewValue(arch32_t value) noexcept
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

    LA32GPRPostModifyEventBase::LA32GPRPostModifyEventBase(unsigned int index, arch32_t oldValue, arch32_t newValue) noexcept
        : index     (index)
        , oldValue  (oldValue)
        , newValue  (newValue)
    { }

    unsigned int LA32GPRPostModifyEventBase::GetIndex() const noexcept
    {
        return index;
    }

    arch32_t LA32GPRPostModifyEventBase::GetOldValue() const noexcept
    {
        return oldValue;
    }

    arch32_t LA32GPRPostModifyEventBase::GetNewValue() const noexcept
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

    LA32TracedGPRPreModifyEventBase::LA32TracedGPRPreModifyEventBase(unsigned int index, arch32_t oldValue, arch32_t newValue) noexcept
        : index             (index)
        , oldValue          (oldValue)
        , newValue          (newValue)
        , indexModified     (false)
        , newValueModified  (false)
        , newValueTrace     ()
    { }

    unsigned int LA32TracedGPRPreModifyEventBase::GetIndex() const noexcept
    {
        return index;
    }

    void LA32TracedGPRPreModifyEventBase::SetIndex(unsigned int index) noexcept
    {
        this->index         = index;
        this->indexModified = true;
    }

    arch32_t LA32TracedGPRPreModifyEventBase::GetOldValue() const noexcept
    {
        return this->oldValue;
    }

    void LA32TracedGPRPreModifyEventBase::SetOldValue(arch32_t value) noexcept
    {
        this->oldValue = value;
    }

    arch32_t LA32TracedGPRPreModifyEventBase::GetNewValue() const noexcept
    {
        return this->newValue;
    }

    void LA32TracedGPRPreModifyEventBase::SetNewValue(arch32_t value) noexcept
    {
        this->newValue         = value;
        this->newValueModified = true;
    }

    void LA32TracedGPRPreModifyEventBase::SetNewValue(arch32_t value, LA32TraceEntity::Reference trace) noexcept
    {
        this->newValue         = value;
        this->newValueModified = true;
        this->newValueTrace    = trace;
    }

    bool LA32TracedGPRPreModifyEventBase::IsIndexModified() const noexcept
    {
        return this->indexModified;
    }

    bool LA32TracedGPRPreModifyEventBase::IsNewValueModified() const noexcept
    {
        return this->newValueModified;
    }

    LA32TraceEntity::Reference LA32TracedGPRPreModifyEventBase::GetNewValueTrace() const noexcept
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

    LA32TracedGPRPostModifyEventBase::LA32TracedGPRPostModifyEventBase(unsigned int index, arch32_t oldValue, arch32_t newValue) noexcept
        : index     (index)
        , oldValue  (oldValue)
        , newValue  (newValue)
    { }

    unsigned int LA32TracedGPRPostModifyEventBase::GetIndex() const noexcept
    {
        return index;
    }

    arch32_t LA32TracedGPRPostModifyEventBase::GetOldValue() const noexcept
    {
        return oldValue;
    }

    arch32_t LA32TracedGPRPostModifyEventBase::GetNewValue() const noexcept
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

    LA32TracedMemoryPreLoadEventBase::LA32TracedMemoryPreLoadEventBase(addr_t address, LA32MOPWidth width) noexcept
        : address           (address)
        , width             (width)
        , addressModified   (false)
        , addressTrace      ()
    { }

    addr_t LA32TracedMemoryPreLoadEventBase::GetAddress() const noexcept
    {
        return address;
    }

    void LA32TracedMemoryPreLoadEventBase::SetAddress(addr_t address) noexcept
    {
        this->address           = address;
        this->addressModified   = true;
    }

    void LA32TracedMemoryPreLoadEventBase::SetAddress(addr_t address, LA32TraceEntity::Reference trace) noexcept
    {
        this->address           = address;
        this->addressModified   = true;
        this->addressTrace      = trace;
    }

    LA32MOPWidth LA32TracedMemoryPreLoadEventBase::GetWidth() const noexcept
    {
        return width;
    }

    void LA32TracedMemoryPreLoadEventBase::SetWidth(LA32MOPWidth width) noexcept
    {
        this->width = width;
    }

    bool LA32TracedMemoryPreLoadEventBase::IsAddressModified() const noexcept
    {
        return addressModified;
    }

    LA32TraceEntity::Reference LA32TracedMemoryPreLoadEventBase::GetAddressTrace() const noexcept
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

    LA32TracedMemoryPrePostLoadEventBase::LA32TracedMemoryPrePostLoadEventBase(addr_t address, LA32MOPWidth width, memdata_t data) noexcept
        : address           (address)
        , width             (width)
        , data              (data)
        , dataModified      (false)
        , dataTrace         ()
    { }

    LA32MOPWidth LA32TracedMemoryPrePostLoadEventBase::GetWidth() const noexcept
    {
        return width;
    }

    addr_t LA32TracedMemoryPrePostLoadEventBase::GetAddress() const noexcept
    {
        return address;
    }

    memdata_t LA32TracedMemoryPrePostLoadEventBase::GetData() const noexcept
    {
        return data;
    }

    void LA32TracedMemoryPrePostLoadEventBase::SetData(memdata_t data) noexcept
    {
        this->data             = data;
        this->dataModified     = true;
    }

    void LA32TracedMemoryPrePostLoadEventBase::SetData(memdata_t data, LA32TraceEntity::Reference trace) noexcept
    {
        this->data             = data;
        this->dataModified     = true;
        this->dataTrace        = trace;
    }

    bool LA32TracedMemoryPrePostLoadEventBase::IsDataModified() const noexcept
    {
        return dataModified;
    }

    LA32TraceEntity::Reference LA32TracedMemoryPrePostLoadEventBase::GetDataTrace() const noexcept
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

    LA32TracedMemoryPostPostLoadEventBase::LA32TracedMemoryPostPostLoadEventBase(addr_t address, LA32MOPWidth width, arch32_t value) noexcept
        : address           (address)
        , width             (width)
        , value             (value)
    { }

    LA32MOPWidth LA32TracedMemoryPostPostLoadEventBase::GetWidth() const noexcept
    {
        return width;
    }

    addr_t LA32TracedMemoryPostPostLoadEventBase::GetAddress() const noexcept
    {
        return address;
    }

    arch32_t LA32TracedMemoryPostPostLoadEventBase::GetValue() const noexcept
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

    LA32TracedMemoryPreStoreEventBase::LA32TracedMemoryPreStoreEventBase(addr_t address, LA32MOPWidth width, memdata_t data) noexcept
        : address           (address)
        , width             (width)
        , data              (data)
        , addressModified   (false)
        , addressTrace      ()
        , dataModified      (false)
        , dataTrace         ()
    { }

    addr_t LA32TracedMemoryPreStoreEventBase::GetAddress() const noexcept
    {
        return address;
    }

    void LA32TracedMemoryPreStoreEventBase::SetAddress(addr_t address) noexcept
    {
        this->address           = address;
        this->addressModified   = true;
    }

    void LA32TracedMemoryPreStoreEventBase::SetAddress(addr_t address, LA32TraceEntity::Reference trace) noexcept
    {
        this->address           = address;
        this->addressModified   = true;
        this->addressTrace      = trace;
    }

    LA32MOPWidth LA32TracedMemoryPreStoreEventBase::GetWidth() const noexcept
    {
        return width;
    }

    void LA32TracedMemoryPreStoreEventBase::SetWidth(LA32MOPWidth width) noexcept
    {
        this->width = width;
    }

    memdata_t LA32TracedMemoryPreStoreEventBase::GetData() const noexcept
    {
        return data;
    }

    void LA32TracedMemoryPreStoreEventBase::SetData(memdata_t data) noexcept
    {
        this->data             = data;
        this->dataModified     = true;
    }

    void LA32TracedMemoryPreStoreEventBase::SetData(memdata_t data, LA32TraceEntity::Reference trace) noexcept
    {
        this->data             = data;
        this->dataModified     = true;
        this->dataTrace        = trace;
    }

    bool LA32TracedMemoryPreStoreEventBase::IsAddressModified() const noexcept
    {
        return addressModified;
    }

    LA32TraceEntity::Reference LA32TracedMemoryPreStoreEventBase::GetAddressTrace() const noexcept
    {
        return addressTrace;
    }

    bool LA32TracedMemoryPreStoreEventBase::IsDataModified() const noexcept
    {
        return dataModified;
    }

    LA32TraceEntity::Reference LA32TracedMemoryPreStoreEventBase::GetDataTrace() const noexcept
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

    LA32TracedMemoryPostStoreEventBase::LA32TracedMemoryPostStoreEventBase(addr_t address, LA32MOPWidth width, memdata_t data) noexcept
        : address           (address)
        , width             (width)
        , data              (data)
    { }

    LA32MOPWidth LA32TracedMemoryPostStoreEventBase::GetWidth() const noexcept
    {
        return width;
    }

    addr_t LA32TracedMemoryPostStoreEventBase::GetAddress() const noexcept
    {
        return address;
    }

    memdata_t LA32TracedMemoryPostStoreEventBase::GetData() const noexcept
    {
        return data;
    }
}



// Implementation of: class LA32InstructionPreFetchEvent
namespace Jasse {

    LA32InstructionPreFetchEvent::LA32InstructionPreFetchEvent(
            LA32Instance&       instance, 
            pc_t                pc) noexcept
        : LA32InstanceEventBase         (instance)
        , LA32PCEventBase               (pc)
    { }
}


// Implementation of: class LA32InstructionPostFetchEvent
namespace Jasse {

    LA32InstructionPostFetchEvent::LA32InstructionPostFetchEvent(
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

    LA32InstructionPreDecodeEvent::LA32InstructionPreDecodeEvent(
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

    LA32InstructionPostDecodeEvent::LA32InstructionPostDecodeEvent(
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

    LA32InstructionPreExecutionEvent::LA32InstructionPreExecutionEvent(
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

    LA32InstructionPostExecutionEvent::LA32InstructionPostExecutionEvent(
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

    LA32PCIterationEvent::LA32PCIterationEvent(
            LA32Instance&       instance, 
            pc_t                old_pc, 
            pc_t                new_pc, 
            Action              action) noexcept
        : LA32InstanceEventBase         (instance)
        , LA32PCChangeEventBase         (old_pc, new_pc)
        , action                        (action)
    { }

    LA32PCIterationEvent::Action LA32PCIterationEvent::GetAction() const noexcept
    {
        return action;
    }

    void LA32PCIterationEvent::SetAction(LA32PCIterationEvent::Action action) noexcept
    {
        this->action = action;
    }
}



// Implementation of: class LA32InstructionGPRPreModifyEvent
namespace Jasse {
    
    LA32InstructionGPRPreModifyEvent::LA32InstructionGPRPreModifyEvent(
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

    LA32InstructionGPRPostModifyEvent::LA32InstructionGPRPostModifyEvent(
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
        
    LA32TracedInstructionGPRPreModifyEvent::LA32TracedInstructionGPRPreModifyEvent(
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

    LA32TracedInstructionGPRPostModifyEvent::LA32TracedInstructionGPRPostModifyEvent(
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

    LA32InstructionGPRReadEvent::LA32InstructionGPRReadEvent(
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

    unsigned int LA32InstructionGPRReadEvent::GetOrdinal() const noexcept
    {
        return ordinal;
    }

    bool LA32InstructionGPRReadEvent::IsLast() const noexcept
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

    LA32InstructionGPRPostReadEvent::LA32InstructionGPRPostReadEvent(
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

    unsigned int LA32InstructionGPRPostReadEvent::GetOrdinal() const noexcept
    {
        return ordinal;
    }

    bool LA32InstructionGPRPostReadEvent::IsLast() const noexcept
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

    LA32TracedInstructionGPRReadEvent::LA32TracedInstructionGPRReadEvent(
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

    unsigned int LA32TracedInstructionGPRReadEvent::GetOrdinal() const noexcept
    {
        return ordinal;
    }

    bool LA32TracedInstructionGPRReadEvent::IsLast() const noexcept
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

    LA32TracedInstructionGPRPostReadEvent::LA32TracedInstructionGPRPostReadEvent(
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

    unsigned int LA32TracedInstructionGPRPostReadEvent::GetOrdinal() const noexcept
    {
        return ordinal;
    }

    bool LA32TracedInstructionGPRPostReadEvent::IsLast() const noexcept
    {
        return last;
    }
}



// Implementation of: class LA32TracedMemoryPreLoadEvent
namespace Jasse {
    
    LA32TracedMemoryPreLoadEvent::LA32TracedMemoryPreLoadEvent(
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

    LA32TracedMemoryPrePostLoadEvent::LA32TracedMemoryPrePostLoadEvent(
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

    LA32TracedMemoryPostPostLoadEvent::LA32TracedMemoryPostPostLoadEvent(
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

    LA32TracedMemoryPreStoreEvent::LA32TracedMemoryPreStoreEvent(
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

    LA32TracedMemoryPostStoreEvent::LA32TracedMemoryPostStoreEvent(
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



// Implementation of: class LA32InstancePreEvalEvent
namespace Jasse {

    LA32InstancePreEvalEvent::LA32InstancePreEvalEvent(
            LA32Instance&       instance) noexcept
        : LA32InstanceEventBase (instance)
    { }
}


// Implementation of: class LA32InstancePostEvalEvent
namespace Jasse {

    LA32InstancePostEvalEvent::LA32InstancePostEvalEvent(
            LA32Instance&       instance) noexcept
        : LA32InstanceEventBase (instance)
    { }
}
