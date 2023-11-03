#include "ds232_diff.hpp"
//
//
//
//

#include "ds232_uop40.hpp"


#include <sstream>
#include <iomanip>


// Implementation of: class DS232Increment
namespace BullsEye::Draconids3014 {

    // DS232 Increment
    DS232Increment::DS232Increment(size_t term_count) noexcept
        : term_count    (term_count)
    { }

    size_t DS232Increment::GetTermCount() const noexcept
    {
        return term_count;
    }

    void DS232Increment::SetTermCount(size_t term_count) noexcept
    {
        this->term_count = term_count;
    }

    size_t DS232Increment::IncreaseTermCount() noexcept
    {
        return ++term_count;
    }
}


// Implementation of: class DS232IncrementPC
namespace BullsEye::Draconids3014 {
    /*
    pc_t        pc;
    */

    // DS232 Increment of PC
    DS232IncrementPC::DS232IncrementPC() noexcept
        : DS232Increment    ()
    { }

    pc_t DS232IncrementPC::GetPC() const noexcept
    {
        return pc;
    }

    void DS232IncrementPC::SetPC(pc_t pc) noexcept
    {
        this->pc = pc;
    }
}


// Implementation of: class DS232IncrementInstruction
namespace BullsEye::Draconids3014 {
    /*
    insnraw_t   instruction;
    */

    // DS232 Increment of Instruction
    DS232IncrementInstruction::DS232IncrementInstruction() noexcept
        : DS232Increment    ()
    { }

    insnraw_t DS232IncrementInstruction::GetInstruction() const noexcept
    {
        return instruction;
    }

    void DS232IncrementInstruction::SetInstruction(insnraw_t instruction) noexcept
    {
        this->instruction = instruction;
    }
}


// Implementation of: class DS232IncrementGPR
namespace BullsEye::Draconids3014 {
    /*
    unsigned int    gpr_index;
    arch32_t        gpr_value;
    */

    DS232IncrementGPR::DS232IncrementGPR() noexcept
        : DS232Increment    ()
    { }

    unsigned int DS232IncrementGPR::GetGPRIndex() const noexcept
    {
        return gpr_index;
    }

    void DS232IncrementGPR::SetGPRIndex(unsigned int gpr_index) noexcept
    {
        this->gpr_index = gpr_index;
    }

    arch32_t DS232IncrementGPR::GetGPRValue() const noexcept
    {
        return gpr_value;
    }

    void DS232IncrementGPR::SetGPRValue(arch32_t gpr_value) noexcept
    {
        this->gpr_value = gpr_value;
    }

    void DS232IncrementGPR::SetGPR(unsigned int gpr_index, arch32_t gpr_value)
    {
        this->gpr_index = gpr_index;
        this->gpr_value = gpr_value;
    }
}


// Implementation of: class DS232IncrementMemoryStore
namespace BullsEye::Draconids3014 {
    /*
    lswidth_t   width;
    lsstrb_t    strb;
    addr_t      address;
    uint32_t    data;
    bool        uncached;
    */

    DS232IncrementMemoryStore::DS232IncrementMemoryStore() noexcept
        : DS232Increment    ()
    { }

    lswidth_t DS232IncrementMemoryStore::GetWidth() const noexcept
    {
        return width;
    }

    void DS232IncrementMemoryStore::SetWidth(lswidth_t width) noexcept
    {
        this->width = width;
    }

    lsstrb_t DS232IncrementMemoryStore::GetStrobe() const noexcept
    {
        return strb;
    }

    void DS232IncrementMemoryStore::SetStrobe(lsstrb_t strb) noexcept
    {
        this->strb = strb;
    }

    addr_t DS232IncrementMemoryStore::GetAddress() const noexcept
    {
        return address;
    }

    void DS232IncrementMemoryStore::SetAddress(addr_t address) noexcept
    {
        this->address = address;
    }

    uint32_t DS232IncrementMemoryStore::GetData() const noexcept
    {
        return data;
    }

    void DS232IncrementMemoryStore::SetData(uint32_t data) noexcept
    {
        this->data = data;
    }

    bool DS232IncrementMemoryStore::IsUncached() const noexcept
    {
        return uncached;
    }

    void DS232IncrementMemoryStore::SetUncached(bool uncached) noexcept
    {
        this->uncached = uncached;
    }

    void DS232IncrementMemoryStore::SetMemoryStore(lswidth_t width, lsstrb_t strb, addr_t address, uint32_t data, bool uncached) noexcept
    {
        this->width     = width;
        this->strb      = strb;
        this->address   = address;
        this->data      = data;
        this->uncached  = uncached;
    }
}



// Implementation of: class DS232Differential
namespace BullsEye::Draconids3014 {
    /*
    FetchIDTracker*                                 fidTracker;

    unsigned int                                    eventBusId;
    int                                             eventPriority;

    bool                                            enabledIncrementPC;
    bool                                            enabledIncrementInstruction;
    bool                                            enabledIncrementGPR;
    bool                                            enabledIncrementMemoryStore;

    DS232IncrementVector<DS232IncrementPC>          incrementPC;
    DS232IncrementVector<DS232IncrementInstruction> incrementInstruction;
    DS232IncrementVector<DS232IncrementGPR>         incrementGPR;
    DS232IncrementVector<DS232IncrementMemoryStore> incrementMemoryStore;
    */

    DS232Differential::DS232Differential(FetchIDTracker*   fidTracker,
                                         unsigned int      eventBusId,
                                         int               eventPriority,
                                         bool              enabledIncrementPC,
                                         bool              enabledIncrementInstruction,
                                         bool              enabledIncrementGPR,
                                         bool              enabledIncrementMemoryStore) noexcept
        : fidTracker                    (fidTracker)
        , eventBusId                    (eventBusId)
        , eventPriority                 (eventPriority)
        , enabledIncrementPC            (enabledIncrementPC)
        , enabledIncrementInstruction   (enabledIncrementInstruction)
        , enabledIncrementGPR           (enabledIncrementGPR)
        , enabledIncrementMemoryStore   (enabledIncrementMemoryStore)
        , incrementPC                   ()
        , incrementInstruction          ()
        , incrementGPR                  ()
        , incrementMemoryStore          ()
    { 
        RegisterListeners();
    }

    DS232Differential::~DS232Differential() noexcept
    { 
        UnregisterListeners();
    }

    void DS232Differential::OnPreEval(DS232PreEvalEvent& event) noexcept
    {
        incrementPC         .Clear();
        incrementInstruction.Clear();
        incrementGPR        .Clear();
        incrementMemoryStore.Clear();
    }

    void DS232Differential::OnPostEval(DS232PostEvalEvent& event) noexcept
    {
        // nothing need to be done here
    }

    void DS232Differential::OnROBCommit(DS232ROBCommitEvent& event) noexcept
    {
        FetchIDTrack& fidTrack = fidTracker->At(event.GetFID());

        //
        if (enabledIncrementPC)
        {
            DS232IncrementPC& incr_pc = incrementPC.Emplace();

            incr_pc.SetTermCount(1);
            incr_pc.SetPC       (fidTrack.GetPC());
        }

        //
        if (enabledIncrementInstruction)
        {
            DS232IncrementInstruction& incr_insn = incrementInstruction.Emplace();

            std::optional<Jasse::insnraw_t> insn 
                = ReverseUOP40_OC3_LA32R(fidTrack.GetUOP());

            if (insn)
            {
                incr_insn.SetTermCount  (1);
                incr_insn.SetInstruction(insn.value());
            }
        }

        //
        if (enabledIncrementGPR)
        {
            DS232IncrementGPR& incr_gpr = incrementGPR.Emplace();

            incr_gpr.SetTermCount(1);
            incr_gpr.SetGPR(event.GetGPRIndex(), event.GetGPRValue());
        }

        //
        if (enabledIncrementMemoryStore)
        {
            // *NOTICE: MemoryStore Increment padding here.
            //          It's NOT NECESSARY for *DS232 Gen 4 Version 1/2/3* because the store commit port
            //          is only available for the first ROB commit port.
            //          While this is implemented as this is only for future compatibility.

            incrementMemoryStore.Emplace();
        }
    }

    void DS232Differential::OnStoreCommit(DS232StoreCommitEvent& event) noexcept
    {
        if (enabledIncrementMemoryStore)
        {
            if (event.GetPortID() < incrementMemoryStore.GetCount())
            {
                DS232IncrementMemoryStore& incr_store = incrementMemoryStore.Get(event.GetPortID());

                incr_store.SetTermCount(1);
                incr_store.SetMemoryStore(
                    event.GetWidth(), 
                    event.GetStrobe(), 
                    event.GetAddress(), 
                    event.GetData(),
                    event.IsUncached());
            }
            else
            {
                // *NOTICE: It's not allowed to receive StoreCommitEvent before padding.
                //          Something went wrong in DUT core or event logic.

                // TODO
            }
        }
    }

    std::string DS232Differential::GetListenerName(const char* increment_name) const noexcept
    {
        std::ostringstream oss;
        oss << "DS232Differential[";
        oss << std::hex << std::setw(16) << std::setfill('0') << uintptr_t(this);
        oss << "]::" << increment_name;
        return oss.str();
    }

    void DS232Differential::RegisterListeners() noexcept
    {
        BullsEye::RegisterListener(
            BullsEye::MakeListener(
                GetListenerName("OnPreEval"),
                eventPriority,
                &DS232Differential::OnPreEval,
                this
            ),
            eventBusId
        );

        BullsEye::RegisterListener(
            BullsEye::MakeListener(
                GetListenerName("OnPostEval"),
                eventPriority,
                &DS232Differential::OnPostEval,
                this
            ),
            eventBusId
        );

        BullsEye::RegisterListener(
            BullsEye::MakeListener(
                GetListenerName("OnROBCommit"),
                eventPriority,
                &DS232Differential::OnROBCommit,
                this
            ),
            eventBusId
        );

        BullsEye::RegisterListener(
            BullsEye::MakeListener(
                GetListenerName("OnStoreCommit"),
                eventPriority,
                &DS232Differential::OnStoreCommit,
                this
            ),
            eventBusId
        );
    }

    void DS232Differential::UnregisterListeners() noexcept
    {
        BullsEye::UnregisterListener(
            GetListenerName("OnPreEval"),
            &DS232Differential::OnPreEval,
            eventBusId
        );

        BullsEye::UnregisterListener(
            GetListenerName("OnPostEval"),
            &DS232Differential::OnPostEval,
            eventBusId
        );

        BullsEye::UnregisterListener(
            GetListenerName("OnROBCommit"),
            &DS232Differential::OnROBCommit,
            eventBusId
        );

        BullsEye::UnregisterListener(
            GetListenerName("OnStoreCommit"),
            &DS232Differential::OnStoreCommit,
            eventBusId
        );
    }

    FetchIDTracker* DS232Differential::GetFetchIDTracker() noexcept
    {
        return fidTracker;
    }

    unsigned int DS232Differential::GetEventBusId() const noexcept
    {
        return eventBusId;
    }

    int DS232Differential::GetEventPriority() const noexcept
    {
        return eventPriority;
    }

    bool DS232Differential::IsEnabledPC() const noexcept
    {
        return enabledIncrementPC;
    }

    bool DS232Differential::IsEnabledInstruction() const noexcept
    {
        return enabledIncrementInstruction;
    }

    bool DS232Differential::IsEnabledGPR() const noexcept
    {
        return enabledIncrementGPR;
    }

    bool DS232Differential::IsEnabledMemoryStore() const noexcept
    {
        return enabledIncrementMemoryStore;
    }

    DS232IncrementVector<DS232IncrementPC>& DS232Differential::GetIncrementPC() noexcept
    {
        return incrementPC;
    }

    const DS232IncrementVector<DS232IncrementPC>& DS232Differential::GetIncrementPC() const noexcept
    {
        return incrementPC;
    }

    DS232IncrementVector<DS232IncrementInstruction>& DS232Differential::GetIncrementInstruction() noexcept
    {
        return incrementInstruction;
    }

    const DS232IncrementVector<DS232IncrementInstruction>& DS232Differential::GetIncrementInstruction() const noexcept
    {
        return incrementInstruction;
    }

    DS232IncrementVector<DS232IncrementGPR>& DS232Differential::GetIncrementGPR() noexcept
    {
        return incrementGPR;
    }

    const DS232IncrementVector<DS232IncrementGPR>& DS232Differential::GetIncrementGPR() const noexcept
    {
        return incrementGPR;
    }

    DS232IncrementVector<DS232IncrementMemoryStore>& DS232Differential::GetIncrementMemoryStore() noexcept
    {
        return incrementMemoryStore;
    }

    const DS232IncrementVector<DS232IncrementMemoryStore>& DS232Differential::GetIncrementMemoryStore() const noexcept
    {
        return incrementMemoryStore;
    }
}


// Implementation of: class DS232Differential::Builder
namespace BullsEye::Draconids3014 {
    /*
    FetchIDTracker*     fidTracker;

    unsigned int        eventBusId;
    int                 eventPriority;

    bool                enabledIncrementPC;
    bool                enabledIncrementInstruction;
    bool                enabledIncrementGPR;
    bool                enabledIncrementMemoryStore;
    */

    DS232Differential::Builder::Builder() noexcept
        : fidTracker                    (nullptr)
        , eventBusId                    (0)
        , eventPriority                 (0)
        , enabledIncrementPC            (false)
        , enabledIncrementInstruction   (false)
        , enabledIncrementGPR           (false)
        , enabledIncrementMemoryStore   (false)
    { }

    DS232Differential::Builder& DS232Differential::Builder::FIDTracker(FetchIDTracker* fidTracker) noexcept
    {
        this->fidTracker = fidTracker;
        return *this;
    }

    DS232Differential::Builder& DS232Differential::Builder::EventBusId(unsigned int eventBusId) noexcept
    {
        this->eventBusId = eventBusId;
        return *this;
    }

    DS232Differential::Builder& DS232Differential::Builder::EventPriority(int eventPriority) noexcept
    {
        this->eventPriority = eventPriority;
        return *this;
    }

    DS232Differential::Builder& DS232Differential::Builder::EnablePC(bool enabledIncrementPC) noexcept
    {
        this->enabledIncrementPC = enabledIncrementPC;
        return *this;
    }

    DS232Differential::Builder& DS232Differential::Builder::EnableInstruction(bool enabledIncrementInstruction) noexcept
    {
        this->enabledIncrementInstruction = enabledIncrementInstruction;
        return *this;
    }

    DS232Differential::Builder& DS232Differential::Builder::EnableGPR(bool enabledIncrementGPR) noexcept
    {
        this->enabledIncrementGPR = enabledIncrementGPR;
        return *this;
    }

    DS232Differential::Builder& DS232Differential::Builder::EnableMemoryStore(bool enabledIncrementMemoryStore) noexcept
    {
        this->enabledIncrementMemoryStore = enabledIncrementMemoryStore;
        return *this;
    }

    FetchIDTracker* DS232Differential::Builder::GetFIDTracker() noexcept
    {
        return fidTracker;
    }

    void DS232Differential::Builder::SetFIDTracker(FetchIDTracker* fidTracker) noexcept
    {
        this->fidTracker = fidTracker;
    }

    unsigned int DS232Differential::Builder::GetEventBusId() const noexcept
    {
        return eventBusId;
    }

    void DS232Differential::Builder::SetEventBusId(unsigned int eventBusId) noexcept
    {
        this->eventBusId = eventBusId;
    }

    int DS232Differential::Builder::GetEventPriority() const noexcept
    {
        return eventPriority;
    }

    void DS232Differential::Builder::SetEventPriority(int eventPriority) noexcept
    {
        this->eventPriority = eventPriority;
    }

    bool DS232Differential::Builder::IsEnabledPC() const noexcept
    {
        return enabledIncrementPC;
    }

    void DS232Differential::Builder::SetEnabledPC(bool enabledIncrementPC) noexcept
    {
        this->enabledIncrementPC = enabledIncrementPC;
    }

    bool DS232Differential::Builder::IsEnabledInstruction() const noexcept
    {
        return enabledIncrementInstruction;
    }

    void DS232Differential::Builder::SetEnabledInstruction(bool enabledIncrementInstruction) noexcept
    {
        this->enabledIncrementInstruction = enabledIncrementInstruction;
    }

    bool DS232Differential::Builder::IsEnabledGPR() const noexcept
    {
        return enabledIncrementGPR;
    }

    void DS232Differential::Builder::SetEnabledGPR(bool enabledIncrementGPR) noexcept
    {
        this->enabledIncrementGPR = enabledIncrementGPR;
    }

    bool DS232Differential::Builder::IsEnabledMemoryStore() const noexcept
    {
        return enabledIncrementMemoryStore;
    }

    void DS232Differential::Builder::SetEnabledMemoryStore(bool enabledIncrementMemoryStore) noexcept
    {
        this->enabledIncrementMemoryStore = enabledIncrementMemoryStore;
    }

    DS232Differential* DS232Differential::Builder::Build() noexcept
    {
        return new DS232Differential(
            fidTracker,
            eventBusId,
            eventPriority,
            enabledIncrementPC,
            enabledIncrementInstruction,
            enabledIncrementGPR,
            enabledIncrementMemoryStore
        );
    }
}
