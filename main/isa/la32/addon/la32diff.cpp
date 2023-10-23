#include "la32diff.hpp"
//
// Add-ons for DiffTest support
//
//

#include <memory>
#include <sstream>
#include <iomanip>
#include <functional>


// Implementation of: class LA32Increment
namespace Jasse {
    /*
    uint32_t    term_count;
    */

    LA32Increment::LA32Increment(uint32_t term_count) noexcept
        : term_count    (term_count)
    { }

    uint32_t LA32Increment::GetTermCount() const noexcept
    {
        return this->term_count;
    }

    void LA32Increment::SetTermCount(uint32_t term_count) noexcept
    {
        this->term_count = term_count;
    }

    uint32_t LA32Increment::IncreaseTermCount() noexcept
    {
        return (this->term_count)++;
    }
}


// Implementation of: class LA32IncrementPC
namespace Jasse {
    /*
    pc_t        pc;
    */

    LA32IncrementPC::LA32IncrementPC() noexcept
        : LA32Increment ()
        , pc            ()
    { }

    pc_t LA32IncrementPC::GetPC() const noexcept
    {
        return this->pc;
    }

    void LA32IncrementPC::SetPC(pc_t pc) noexcept
    {
        this->pc = pc;
    }
}


// Implementation of: class LA32IncrementInstruction
namespace Jasse {
    /*
    LA32Instruction instruction;
    */

    LA32IncrementInstruction::LA32IncrementInstruction() noexcept
        : LA32Increment ()
        , instruction   ()
    { }

    const LA32Instruction& LA32IncrementInstruction::GetInstruction() const noexcept
    {
        return this->instruction;
    }

    void LA32IncrementInstruction::SetInstruction(const LA32Instruction& instruction) noexcept
    {
        this->instruction = instruction;
    }
}


// Implementation of: class LA32IncrementBranch
namespace Jasse {
    /*
    bool        branch_taken;
    pc_t        branch_target;
    */

    LA32IncrementBranch::LA32IncrementBranch() noexcept
        : LA32Increment ()
        , branch_taken  ()
        , branch_target ()
    { }

    bool LA32IncrementBranch::GetBranchTaken() const noexcept
    {
        return this->branch_taken;
    }

    void LA32IncrementBranch::SetBranchTaken(bool branch_taken) noexcept
    {
        this->branch_taken = branch_taken;
    }

    pc_t LA32IncrementBranch::GetBranchTarget() const noexcept
    {
        return this->branch_target;
    }

    void LA32IncrementBranch::SetBranchTarget(pc_t branch_target) noexcept
    {
        this->branch_target = branch_target;
    }

    void LA32IncrementBranch::SetBranch(bool branch_taken, pc_t branch_target) noexcept
    {
        this->branch_taken  = branch_taken;
        this->branch_target = branch_target;
    }
}


// Implementation of: class LA32IncrementGPR
namespace Jasse {
    /*
    unsigned int    gpr_index;
    arch32_t        gpr_value;
    */

    LA32IncrementGPR::LA32IncrementGPR() noexcept
        : LA32Increment ()
        , gpr_index     ()
        , gpr_value     ()
    { }

    unsigned int LA32IncrementGPR::GetGPRIndex() const noexcept
    {
        return this->gpr_index;
    }

    void LA32IncrementGPR::SetGPRIndex(unsigned int gpr_index) noexcept
    {
        this->gpr_index = gpr_index;
    }

    arch32_t LA32IncrementGPR::GetGPRValue() const noexcept
    {
        return this->gpr_value;
    }

    void LA32IncrementGPR::SetGPRValue(arch32_t gpr_value) noexcept
    {
        this->gpr_value = gpr_value;
    }

    void LA32IncrementGPR::SetGPR(unsigned int gpr_index, arch32_t gpr_value) noexcept
    {
        this->gpr_index = gpr_index;
        this->gpr_value = gpr_value;
    }
}


// Implementation of: class LA32IncrementMemoryStore
namespace Jasse {
    /*
    addr_t          address;
    LA32MOPWidth    width;
    memdata_t       data;
    */

    LA32IncrementMemoryStore::LA32IncrementMemoryStore() noexcept
        : LA32Increment ()
        , address       ()
        , width         ()
        , data          ()
    { }

    addr_t LA32IncrementMemoryStore::GetAddress() const noexcept
    {
        return this->address;
    }

    void LA32IncrementMemoryStore::SetAddress(addr_t address) noexcept
    {
        this->address = address;
    }

    LA32MOPWidth LA32IncrementMemoryStore::GetWidth() const noexcept
    {
        return this->width;
    }

    void LA32IncrementMemoryStore::SetWidth(LA32MOPWidth width) noexcept
    {
        this->width = width;
    }

    memdata_t LA32IncrementMemoryStore::GetData() const noexcept
    {
        return this->data;
    }

    void LA32IncrementMemoryStore::SetData(memdata_t data) noexcept
    {
        this->data = data;
    }

    void LA32IncrementMemoryStore::SetMemoryStore(addr_t address, LA32MOPWidth width, memdata_t data) noexcept
    {
        this->address = address;
        this->width   = width;
        this->data    = data;
    }
}


// Implementation of: class LA32IncrementMemoryLoad
namespace Jasse {
    /*
    addr_t          address;
    LA32MOPWidth    width;
    arch32_t        value;
    */

    LA32IncrementMemoryLoad::LA32IncrementMemoryLoad() noexcept
        : LA32Increment ()
        , address       ()
        , width         ()
        , value         ()
    { }

    addr_t LA32IncrementMemoryLoad::GetAddress() const noexcept
    {
        return this->address;
    }

    void LA32IncrementMemoryLoad::SetAddress(addr_t address) noexcept
    {
        this->address = address;
    }

    LA32MOPWidth LA32IncrementMemoryLoad::GetWidth() const noexcept
    {
        return this->width;
    }

    void LA32IncrementMemoryLoad::SetWidth(LA32MOPWidth width) noexcept
    {
        this->width = width;
    }

    arch32_t LA32IncrementMemoryLoad::GetValue() const noexcept
    {
        return this->value;
    }

    void LA32IncrementMemoryLoad::SetValue(arch32_t value) noexcept
    {
        this->value = value;
    }

    void LA32IncrementMemoryLoad::SetMemoryLoad(addr_t address, LA32MOPWidth width, arch32_t value) noexcept
    {
        this->address = address;
        this->width   = width;
        this->value   = value;
    }
}



// Implementation of: class LA32Differential
namespace Jasse {
    /*
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
    */

    LA32Differential::LA32Differential(unsigned int eventBusId,
                                       int          eventPriority,
                                       bool         enabledIncrementPC,
                                       bool         enabledIncrementInstruction,
                                       bool         enabledIncrementBranch,
                                       bool         enabledIncrementGPR,
                                       bool         enabledIncrementMemoryStore,
                                       bool         enabledIncrementMemoryLoad) noexcept
        : eventBusId                    (eventBusId)
        , eventPriority                 (eventPriority)
        , enabledIncrementPC            (enabledIncrementPC)
        , enabledIncrementInstruction   (enabledIncrementInstruction)
        , enabledIncrementBranch        (enabledIncrementBranch)
        , enabledIncrementGPR           (enabledIncrementGPR)
        , enabledIncrementMemoryStore   (enabledIncrementMemoryStore)
        , enabledIncrementMemoryLoad    (enabledIncrementMemoryLoad)
    { 
        RegisterListeners();
    }

    LA32Differential::~LA32Differential() noexcept
    {
        UnregisterListeners();
    }

    void LA32Differential::OnPreEval(LA32InstancePreEvalEvent& event) noexcept
    {
        incrementPC         .SetTermCount(0);
        incrementInstruction.SetTermCount(0);
        incrementBranch     .SetTermCount(0);
        incrementGPR        .SetTermCount(0);
        incrementMemoryStore.SetTermCount(0);
        incrementMemoryLoad .SetTermCount(0);
    }

    void LA32Differential::OnPostEval(LA32InstancePostEvalEvent& event) noexcept
    {
        // nothing to be done here currently
    }

    void LA32Differential::OnPostFetch(LA32InstructionPostFetchEvent& event) noexcept
    {
        incrementPC.SetPC(event.GetPC());
        incrementPC.IncreaseTermCount();
    }

    void LA32Differential::OnPostDecode(LA32InstructionPostDecodeEvent& event) noexcept
    {
        incrementInstruction.SetInstruction(event.GetInstruction());
        incrementInstruction.IncreaseTermCount();
    }

    void LA32Differential::OnPCIteration(LA32PCIterationEvent& event) noexcept
    {
        switch (event.GetAction())
        {
            case LA32PCIterationEvent::Action::BRANCH_TAKEN:
                incrementBranch.SetBranch(true, event.GetNewPC());
                incrementBranch.IncreaseTermCount();
                break;

            case LA32PCIterationEvent::Action::BRANCH_NOT_TAKEN:
                incrementBranch.SetBranch(false, event.GetNewPC());
                incrementBranch.IncreaseTermCount();
                break;
            
            default:
                break;
        }
    }

    void LA32Differential::OnPostGPRModify(LA32TracedInstructionGPRPostModifyEvent& event) noexcept
    {
        incrementGPR.SetGPR(
            event.GetIndex(), 
            event.GetNewValue());
        
        incrementGPR.IncreaseTermCount();
    }

    void LA32Differential::OnPostMemoryStore(LA32TracedMemoryPostStoreEvent& event) noexcept
    {
        incrementMemoryStore.SetMemoryStore(
            event.GetAddress(), 
            event.GetWidth(), 
            event.GetData());

        incrementMemoryStore.IncreaseTermCount();
    }

    void LA32Differential::OnPostMemoryLoad(LA32TracedMemoryPostPostLoadEvent& event) noexcept
    {
        incrementMemoryLoad.SetMemoryLoad(
            event.GetAddress(), 
            event.GetWidth(), 
            event.GetValue());

        incrementMemoryLoad.IncreaseTermCount();
    }

    std::string LA32Differential::GetListenerName(const char* increment_name) const noexcept
    {
        std::ostringstream oss;
        oss << "LA32Differential[";
        oss << std::hex << std::setw(16) << std::setfill('0') << uintptr_t(this);
        oss << "]::" << increment_name;
        return oss.str();
    }

    void LA32Differential::RegisterListeners() noexcept
    {
        BullsEye::RegisterListener(
            BullsEye::MakeListener(
                GetListenerName("OnPreEval"), 
                eventPriority,
                &LA32Differential::OnPreEval, 
                this),
            eventBusId);

        BullsEye::RegisterListener(
            BullsEye::MakeListener(
                GetListenerName("OnPostEval"),
                eventPriority,
                &LA32Differential::OnPostEval,
                this),
            eventBusId);

        if (enabledIncrementPC)
        {
            BullsEye::RegisterListener(
                BullsEye::MakeListener(
                    GetListenerName("OnPostFetch"),
                    eventPriority,
                    &LA32Differential::OnPostFetch,
                    this),
                eventBusId);
        }

        if (enabledIncrementInstruction)
        {
            BullsEye::RegisterListener(
                BullsEye::MakeListener(
                    GetListenerName("OnPostDecode"),
                    eventPriority,
                    &LA32Differential::OnPostDecode,
                    this),
                eventBusId);
        }

        if (enabledIncrementBranch)
        {
            BullsEye::RegisterListener(
                BullsEye::MakeListener(
                    GetListenerName("OnPCIteration"),
                    eventPriority,
                    &LA32Differential::OnPCIteration,
                    this),
                eventBusId);
        }

        if (enabledIncrementGPR)
        {
            BullsEye::RegisterListener(
                BullsEye::MakeListener(
                    GetListenerName("OnPostGPRModify"),
                    eventPriority,
                    &LA32Differential::OnPostGPRModify,
                    this),
                eventBusId);
        }

        if (enabledIncrementMemoryStore)
        {
            BullsEye::RegisterListener(
                BullsEye::MakeListener(
                    GetListenerName("OnPostMemoryStore"),
                    eventPriority,
                    &LA32Differential::OnPostMemoryStore,
                    this),
                eventBusId);
        }

        if (enabledIncrementMemoryLoad)
        {
            BullsEye::RegisterListener(
                BullsEye::MakeListener(
                    GetListenerName("OnPostMemoryLoad"),
                    eventPriority,
                    &LA32Differential::OnPostMemoryLoad,
                    this),
                eventBusId);
        }
    }

    void LA32Differential::UnregisterListeners() noexcept
    {
        BullsEye::UnregisterListener(
            GetListenerName("OnPreEval"), 
            &LA32Differential::OnPreEval, 
            eventBusId);

        BullsEye::UnregisterListener(
            GetListenerName("OnPostEval"), 
            &LA32Differential::OnPostEval, 
            eventBusId);

        if (enabledIncrementPC)
        {
            BullsEye::UnregisterListener(
                GetListenerName("OnPostFetch"), 
                &LA32Differential::OnPostFetch, 
                eventBusId);
        }

        if (enabledIncrementInstruction)
        {
            BullsEye::UnregisterListener(
                GetListenerName("OnPostDecode"), 
                &LA32Differential::OnPostDecode, 
                eventBusId);
        }

        if (enabledIncrementBranch)
        {
            BullsEye::UnregisterListener(
                GetListenerName("OnPCIteration"), 
                &LA32Differential::OnPCIteration, 
                eventBusId);
        }

        if (enabledIncrementGPR)
        {
            BullsEye::UnregisterListener(
                GetListenerName("OnPostGPRModify"), 
                &LA32Differential::OnPostGPRModify, 
                eventBusId);
        }

        if (enabledIncrementMemoryStore)
        {
            BullsEye::UnregisterListener(
                GetListenerName("OnPostMemoryStore"), 
                &LA32Differential::OnPostMemoryStore, 
                eventBusId);
        }

        if (enabledIncrementMemoryLoad)
        {
            BullsEye::UnregisterListener(
                GetListenerName("OnPostMemoryLoad"), 
                &LA32Differential::OnPostMemoryLoad, 
                eventBusId);
        }
    }

    unsigned int LA32Differential::GetEventBusId() const noexcept
    {
        return this->eventBusId;
    }

    int LA32Differential::GetEventPriority() const noexcept
    {
        return this->eventPriority;
    }

    bool LA32Differential::IsEnabledPC() const noexcept
    {
        return this->enabledIncrementPC;
    }

    bool LA32Differential::IsEnabledInstruction() const noexcept
    {
        return this->enabledIncrementInstruction;
    }

    bool LA32Differential::IsEnabledBranch() const noexcept
    {
        return this->enabledIncrementBranch;
    }

    bool LA32Differential::IsEnabledGPR() const noexcept
    {
        return this->enabledIncrementGPR;
    }

    bool LA32Differential::IsEnabledMemoryStore() const noexcept
    {
        return this->enabledIncrementMemoryStore;
    }

    bool LA32Differential::IsEnabledMemoryLoad() const noexcept
    {
        return this->enabledIncrementMemoryLoad;
    }

    const LA32IncrementPC& LA32Differential::GetIncrementPC() const noexcept
    {
        return this->incrementPC;
    }

    const LA32IncrementInstruction& LA32Differential::GetIncrementInstruction() const noexcept
    {
        return this->incrementInstruction;
    }

    const LA32IncrementBranch& LA32Differential::GetIncrementBranch() const noexcept
    {
        return this->incrementBranch;
    }

    const LA32IncrementGPR& LA32Differential::GetIncrementGPR() const noexcept
    {
        return this->incrementGPR;
    }

    const LA32IncrementMemoryStore& LA32Differential::GetIncrementMemoryStore() const noexcept
    {
        return this->incrementMemoryStore;
    }

    const LA32IncrementMemoryLoad& LA32Differential::GetIncrementMemoryLoad() const noexcept
    {
        return this->incrementMemoryLoad;
    }
}


// Implementation of: class LA32Differential::Builder
namespace Jasse {
    /*
    unsigned int    eventBusId;
    int             eventPriority;

    bool            enabledIncrementPC;
    bool            enabledIncrementInstruction;
    bool            enabledIncrementBranch;
    bool            enabledIncrementGPR;
    bool            enabledIncrementMemoryStore;
    bool            enabledIncrementMemoryLoad;
    */

    LA32Differential::Builder::Builder() noexcept
        : eventBusId                    (0)
        , eventPriority                 (0)
        , enabledIncrementPC            (false)
        , enabledIncrementInstruction   (false)
        , enabledIncrementBranch        (false)
        , enabledIncrementGPR           (false)
        , enabledIncrementMemoryStore   (false)
        , enabledIncrementMemoryLoad    (false)
    { }

    LA32Differential::Builder& LA32Differential::Builder::EventBusId(unsigned int eventBusId) noexcept
    {
        this->eventBusId = eventBusId;
        return *this;
    }

    LA32Differential::Builder& LA32Differential::Builder::EventPriority(int eventPriority) noexcept
    {
        this->eventPriority = eventPriority;
        return *this;
    }

    LA32Differential::Builder& LA32Differential::Builder::EnablePC(bool enabledIncrementPC) noexcept
    {
        this->enabledIncrementPC = enabledIncrementPC;
        return *this;
    }

    LA32Differential::Builder& LA32Differential::Builder::EnableInstruction(bool enabledIncrementInstruction) noexcept
    {
        this->enabledIncrementInstruction = enabledIncrementInstruction;
        return *this;
    }

    LA32Differential::Builder& LA32Differential::Builder::EnableBranch(bool enabledIncrementBranch) noexcept
    {
        this->enabledIncrementBranch = enabledIncrementBranch;
        return *this;
    }

    LA32Differential::Builder& LA32Differential::Builder::EnableGPR(bool enabledIncrementGPR) noexcept
    {
        this->enabledIncrementGPR = enabledIncrementGPR;
        return *this;
    }

    LA32Differential::Builder& LA32Differential::Builder::EnableMemoryStore(bool enabledIncrementMemoryStore) noexcept
    {
        this->enabledIncrementMemoryStore = enabledIncrementMemoryStore;
        return *this;
    }

    LA32Differential::Builder& LA32Differential::Builder::EnableMemoryLoad(bool enabledIncrementMemoryLoad) noexcept
    {
        this->enabledIncrementMemoryLoad = enabledIncrementMemoryLoad;
        return *this;
    }

    unsigned int LA32Differential::Builder::GetEventBusId() const noexcept
    {
        return this->eventBusId;
    }
    
    void LA32Differential::Builder::SetEventBusId(unsigned int eventBusId) noexcept
    {
        this->eventBusId = eventBusId;
    }

    int LA32Differential::Builder::GetEventPriority() const noexcept
    {
        return this->eventPriority;
    }

    void LA32Differential::Builder::SetEventPriority(int eventPriority) noexcept
    {
        this->eventPriority = eventPriority;
    }

    bool LA32Differential::Builder::IsEnabledPC() const noexcept
    {
        return this->enabledIncrementPC;
    }

    void LA32Differential::Builder::SetEnabledPC(bool enabledIncrementPC) noexcept
    {
        this->enabledIncrementPC = enabledIncrementPC;
    }

    bool LA32Differential::Builder::IsEnabledInstruction() const noexcept
    {
        return this->enabledIncrementInstruction;
    }

    void LA32Differential::Builder::SetEnabledInstruction(bool enabledIncrementInstruction) noexcept
    {
        this->enabledIncrementInstruction = enabledIncrementInstruction;
    }

    bool LA32Differential::Builder::IsEnabledBranch() const noexcept
    {
        return this->enabledIncrementBranch;
    }

    void LA32Differential::Builder::SetEnabledBranch(bool enabledIncrementBranch) noexcept
    {
        this->enabledIncrementBranch = enabledIncrementBranch;
    }

    bool LA32Differential::Builder::IsEnabledGPR() const noexcept
    {
        return this->enabledIncrementGPR;
    }

    void LA32Differential::Builder::SetEnabledGPR(bool enabledIncrementGPR) noexcept
    {
        this->enabledIncrementGPR = enabledIncrementGPR;
    }

    bool LA32Differential::Builder::IsEnabledMemoryStore() const noexcept
    {
        return this->enabledIncrementMemoryStore;
    }

    void LA32Differential::Builder::SetEnabledMemoryStore(bool enabledIncrementMemoryStore) noexcept
    {
        this->enabledIncrementMemoryStore = enabledIncrementMemoryStore;
    }

    bool LA32Differential::Builder::IsEnabledMemoryLoad() const noexcept
    {
        return this->enabledIncrementMemoryLoad;
    }

    void LA32Differential::Builder::SetEnabledMemoryLoad(bool enabledIncrementMemoryLoad) noexcept
    {
        this->enabledIncrementMemoryLoad = enabledIncrementMemoryLoad;
    }

    LA32Differential* LA32Differential::Builder::Build() noexcept
    {
        return new LA32Differential(
                eventBusId,
                eventPriority,
                enabledIncrementPC,
                enabledIncrementInstruction,
                enabledIncrementBranch,
                enabledIncrementGPR,
                enabledIncrementMemoryStore,
                enabledIncrementMemoryLoad);
    }
}
