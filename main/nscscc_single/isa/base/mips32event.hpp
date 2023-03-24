#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// Basic Event Infrastructures
//

#include "mips32def.hpp"
#include "mips32decode.hpp"

#include "common/eventbus.hpp"


namespace Jasse {

    // MIPS32 (in instance) Event Base
    class MIPS32InstanceEventBase {
    private:
        MIPS32Instance&     instance;

    public:
        MIPS32InstanceEventBase(MIPS32Instance& instance) noexcept;

        MIPS32Instance&             GetInstance() noexcept;
        const MIPS32Instance&       GetInstance() const noexcept;
    };

    // MIPS32 PC-related Event Base
    class MIPS32PCEventBase {
    private:
        pc_t                pc;

    public:
        MIPS32PCEventBase(pc_t pc) noexcept;

        pc_t                        GetPC() const noexcept;
        void                        SetPC(pc_t value) noexcept;
    };

    // MIPS32 PC Change related Event Base
    class MIPS32PCChangeEventBase {
    private:
        pc_t                old_pc;
        pc_t                new_pc;

    public:
        MIPS32PCChangeEventBase(pc_t old_pc, pc_t new_pc) noexcept;

        pc_t                        GetOldPC() const noexcept;
        void                        SetOldPC(pc_t value) noexcept;

        pc_t                        GetNewPC() const noexcept;
        void                        SetNewPC(pc_t value) noexcept;
    };

    // MIPS32 Instruction related Event Base
    class MIPS32InstructionEventBase {
    private:
        MIPS32Instruction&  insn;

    public:
        MIPS32InstructionEventBase(MIPS32Instruction& insn) noexcept;

        MIPS32Instruction&          GetInstruction() noexcept;
        const MIPS32Instruction&    GetInstruction() const noexcept;
        void                        SetInstruction(const MIPS32Instruction& insn) noexcept;
    };

    // MIPS32 Raw Instruction related Event Base
    class MIPS32RawInstructionEventBase {
    private:
        insnraw_t           insn;

    public:
        MIPS32RawInstructionEventBase(insnraw_t insn) noexcept;

        insnraw_t                   GetInstruction() const noexcept;
        void                        SetInstruction(insnraw_t insn) noexcept;
    };


    // MIPS32 Instruction Pre-Fetch (in instance) Event
    class MIPS32InstructionPreFetchEvent
        : public MIPS32InstanceEventBase
        , public MIPS32PCEventBase
        , public BullsEye::Event<MIPS32InstructionPreFetchEvent>
        , public BullsEye::CancellableEvent {
    public:
        MIPS32InstructionPreFetchEvent(
            MIPS32Instance&     instance, 
            pc_t                pc) noexcept;
    };

    // MIPS32 Instruction Post-Fetch (in instance) Event
    class MIPS32InstructionPostFetchEvent
        : public MIPS32InstanceEventBase
        , public MIPS32PCEventBase
        , public MIPS32RawInstructionEventBase
        , public BullsEye::Event<MIPS32InstructionPostFetchEvent> {
    public:
        MIPS32InstructionPostFetchEvent(
            MIPS32Instance&     instance, 
            pc_t                pc, 
            insnraw_t           insn) noexcept;
    };

    // MIPS32 Instruction Pre-Decode (in instance) Event
    class MIPS32InstructionPreDecodeEvent 
        : public MIPS32InstanceEventBase
        , public MIPS32PCEventBase 
        , public MIPS32InstructionEventBase 
        , public BullsEye::Event<MIPS32InstructionPreDecodeEvent>
        , public BullsEye::CancellableEvent {
    public:
        MIPS32InstructionPreDecodeEvent(
            MIPS32Instance&     instance,
            pc_t                pc,
            MIPS32Instruction&  insn) noexcept;
    };

    // MIPS32 Instruction Post-Decode (in instance) Event
    class MIPS32InstructionPostDecodeEvent 
        : public MIPS32InstanceEventBase
        , public MIPS32PCEventBase 
        , public MIPS32InstructionEventBase 
        , public BullsEye::Event<MIPS32InstructionPostDecodeEvent> {
    public:
        MIPS32InstructionPostDecodeEvent(
            MIPS32Instance&     instance,
            pc_t                pc,
            MIPS32Instruction&  insn) noexcept;
    };


    // MIPS32 Instruction Pre-Execution (in instance) Event
    class MIPS32InstructionPreExecutionEvent 
        : public MIPS32InstanceEventBase
        , public MIPS32PCEventBase
        , public MIPS32InstructionEventBase
        , public BullsEye::Event<MIPS32InstructionPreExecutionEvent>
        , public BullsEye::CancellableEvent {
    public:
        MIPS32InstructionPreExecutionEvent(
            MIPS32Instance&     instance, 
            pc_t                pc, 
            MIPS32Instruction&  insn) noexcept;
    };


    // MIPS32 Instruction Post-Execution (in instance) Event
    class MIPS32InstructionPostExecutionEvent 
        : public MIPS32InstanceEventBase
        , public MIPS32PCEventBase
        , public MIPS32InstructionEventBase
        , public BullsEye::Event<MIPS32InstructionPostExecutionEvent> {
    private:
        MIPS32ExecOutcome   outcome;

    public:
        MIPS32InstructionPostExecutionEvent(
            MIPS32Instance&     instance, 
            pc_t                pc, 
            MIPS32Instruction&  insn,
            MIPS32ExecOutcome   outcome) noexcept;

        MIPS32ExecOutcome           GetOutcome() const noexcept;
        void                        SetOutcome(MIPS32ExecOutcome outcome) noexcept;
    };


    // MIPS32 PC Iteration (in instance) Event
    class MIPS32PCIterationEvent
        : public MIPS32InstanceEventBase
        , public MIPS32PCChangeEventBase
        , public BullsEye::Event<MIPS32PCIterationEvent> {
    public:
        enum class Action {
            SEQUENTIAL = 0,
            DELAY_SLOT,
            BRANCH_TAKEN,
            BRANCH_NOT_TAKEN
        };

    private:
        Action  action;

    public:
        MIPS32PCIterationEvent(
            MIPS32Instance&     instance, 
            pc_t                old_pc, 
            pc_t                new_pc, 
            Action              action) noexcept;

        Action                      GetAction() const noexcept;
        void                        SetAction(Action action) noexcept;
    };
}



// Implementation of: class MIPS32InstanceEventBase
namespace Jasse {
    //
    // MIPS32Instance&     instance;
    // 

    MIPS32InstanceEventBase::MIPS32InstanceEventBase(MIPS32Instance& instance) noexcept
        : instance  (instance)
    { }

    inline MIPS32Instance& MIPS32InstanceEventBase::GetInstance() noexcept
    {
        return instance;
    }

    inline const MIPS32Instance& MIPS32InstanceEventBase::GetInstance() const noexcept
    {
        return instance;
    }
}


// Implementation of: class MIPS32PCEventBase
namespace Jasse {
    //
    // pc_t                pc;
    //

    MIPS32PCEventBase::MIPS32PCEventBase(pc_t pc) noexcept
        : pc    (pc)
    { }

    inline pc_t MIPS32PCEventBase::GetPC() const noexcept
    {
        return pc;
    }

    inline void MIPS32PCEventBase::SetPC(pc_t pc) noexcept
    {
        this->pc = pc;
    }
}


// Implementation of: class MIPS32PCChangeEventBase
namespace Jasse {
    //
    // pc_t                old_pc;
    // pc_t                new_pc;
    //

    MIPS32PCChangeEventBase::MIPS32PCChangeEventBase(pc_t old_pc, pc_t new_pc) noexcept
        : old_pc    (old_pc)
        , new_pc    (new_pc)
    { }

    inline pc_t MIPS32PCChangeEventBase::GetOldPC() const noexcept
    {
        return old_pc;
    }

    inline void MIPS32PCChangeEventBase::SetOldPC(pc_t value) noexcept
    {
        old_pc = value;
    }

    inline pc_t MIPS32PCChangeEventBase::GetNewPC() const noexcept
    {
        return new_pc;
    }

    inline void MIPS32PCChangeEventBase::SetNewPC(pc_t value) noexcept
    {
        new_pc = value;
    }
}


// Implementation of: class MIPS32InstructionEventBase
namespace Jasse {
    //
    // MIPS32Instruction&  insn;
    //

    MIPS32InstructionEventBase::MIPS32InstructionEventBase(MIPS32Instruction& insn) noexcept
        : insn  (insn)
    { }

    inline MIPS32Instruction& MIPS32InstructionEventBase::GetInstruction() noexcept
    {
        return insn;
    }

    inline const MIPS32Instruction& MIPS32InstructionEventBase::GetInstruction() const noexcept
    {
        return insn;
    }

    inline void MIPS32InstructionEventBase::SetInstruction(const MIPS32Instruction& insn) noexcept
    {
        this->insn = insn;
    }
}


// Implementation of: class MIPS32RawInstructionEventBase
namespace Jasse {
    //
    // insnraw_t           insn;
    //

    MIPS32RawInstructionEventBase::MIPS32RawInstructionEventBase(insnraw_t insn) noexcept
        : insn  (insn)
    { }

    inline insnraw_t MIPS32RawInstructionEventBase::GetInstruction() const noexcept
    {
        return insn;
    }

    inline void MIPS32RawInstructionEventBase::SetInstruction(insnraw_t insn) noexcept
    {
        this->insn = insn;
    }
}



// Implementation of: class MIPS32InstructionPreFetchEvent
namespace Jasse {

    MIPS32InstructionPreFetchEvent::MIPS32InstructionPreFetchEvent(
            MIPS32Instance&     instance, 
            pc_t                pc) noexcept
        : MIPS32InstanceEventBase       (instance)
        , MIPS32PCEventBase             (pc)
    { }
}


// Implementation of: class MIPS32InstructionPostFetchEvent
namespace Jasse {

    MIPS32InstructionPostFetchEvent::MIPS32InstructionPostFetchEvent(
            MIPS32Instance&     instance, 
            pc_t                pc, 
            insnraw_t           insn) noexcept
        : MIPS32InstanceEventBase       (instance)
        , MIPS32PCEventBase             (pc)
        , MIPS32RawInstructionEventBase (insn)
    { }
}


// Implementation of: class MIPS32InstructionPreDecodeEvent
namespace Jasse {

    MIPS32InstructionPreDecodeEvent::MIPS32InstructionPreDecodeEvent(
            MIPS32Instance&     instance,
            pc_t                pc,
            MIPS32Instruction&  insn) noexcept
        : MIPS32InstanceEventBase       (instance)
        , MIPS32PCEventBase             (pc)
        , MIPS32InstructionEventBase    (insn)
    { }
}


// Implementation of: class MIPS32InstructionPostDecodeEvent
namespace Jasse {

    MIPS32InstructionPostDecodeEvent::MIPS32InstructionPostDecodeEvent(
            MIPS32Instance&     instance,
            pc_t                pc,
            MIPS32Instruction&  insn) noexcept
        : MIPS32InstanceEventBase       (instance)
        , MIPS32PCEventBase             (pc)
        , MIPS32InstructionEventBase    (insn)
    { }
}


// Implementation of: class MIPS32InstructionPreExecutionEvent
namespace Jasse {

    MIPS32InstructionPreExecutionEvent::MIPS32InstructionPreExecutionEvent(
            MIPS32Instance&     instance, 
            pc_t                pc, 
            MIPS32Instruction&  insn) noexcept
        : MIPS32InstanceEventBase       (instance)
        , MIPS32PCEventBase             (pc)
        , MIPS32InstructionEventBase    (insn)
    { }
}


// Implementation of: class MIPS32InstructionPostExecutionEvent
namespace Jasse {
    //
    // MIPS32ExecOutcome   outcome;
    //

    MIPS32InstructionPostExecutionEvent::MIPS32InstructionPostExecutionEvent(
            MIPS32Instance&     instance, 
            pc_t                pc, 
            MIPS32Instruction&  insn,
            MIPS32ExecOutcome   outcome) noexcept
        : MIPS32InstanceEventBase       (instance)
        , MIPS32PCEventBase             (pc)
        , MIPS32InstructionEventBase    (insn)
        , outcome                       (outcome)
    { }

    inline MIPS32ExecOutcome MIPS32InstructionPostExecutionEvent::GetOutcome() const noexcept
    {
        return outcome;
    }

    inline void MIPS32InstructionPostExecutionEvent::SetOutcome(MIPS32ExecOutcome outcome) noexcept
    {
        this->outcome = outcome;
    }
}



// Implementation of: class MIPS32PCIterationEvent
namespace Jasse {
    //
    // Action  action;
    //

    MIPS32PCIterationEvent::MIPS32PCIterationEvent(
            MIPS32Instance&     instance, 
            pc_t                old_pc, 
            pc_t                new_pc, 
            Action              action) noexcept
        : MIPS32InstanceEventBase   (instance)
        , MIPS32PCChangeEventBase   (old_pc, new_pc)
        , action                    (action)
    { }

    inline MIPS32PCIterationEvent::Action MIPS32PCIterationEvent::GetAction() const noexcept
    {
        return action;
    }

    inline void MIPS32PCIterationEvent::SetAction(MIPS32PCIterationEvent::Action action) noexcept
    {
        this->action = action;
    }
}
