#pragma once
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
// Basic Event Infrastructures
//

#ifndef __HEADER_JASSE_LA32__BASE_EVENT
#define __HEADER_JASSE_LA32__BASE_EVENT


#include "autoinclude.h"


#include "la32def.hpp"
#include "la32decode.hpp"
#include "la32trace.hpp"
#include "la32mem.hpp"

#include AUTOINC_BE_COMMON(eventbus.hpp)


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


    // LA32 Instance Pre-Eval Event
    class LA32InstancePreEvalEvent
        : public LA32InstanceEventBase
        , public BullsEye::Event<LA32InstancePreEvalEvent>
        , public BullsEye::CancellableEvent {
    public:
        LA32InstancePreEvalEvent(
            LA32Instance&       instance) noexcept;
    };

    // LA32 Instance Post-Eval Event
    class LA32InstancePostEvalEvent
        : public LA32InstanceEventBase
        , public BullsEye::Event<LA32InstancePostEvalEvent> {
    public:
        LA32InstancePostEvalEvent(
            LA32Instance&       instance) noexcept;
    };
}


#endif
