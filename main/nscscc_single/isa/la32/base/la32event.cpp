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
