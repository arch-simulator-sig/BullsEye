#include "appmain_historycommit.hpp"
//
//
//
//

#include <utility>
#include <sstream>
#include <iomanip>


// Implementation of: class CommitHistory
/*
unsigned int                                eventBusId;
int                                         eventPriority;

size_t                                      depth;
std::deque<Entry>                           history;

BullsEye::Draconids3014::Thinpad*           dut;
*/

CommitHistory::CommitHistory(BullsEye::Draconids3014::Thinpad* dut, size_t depth, unsigned int eventBusId, int eventPriority) noexcept
    : eventBusId        (eventBusId)
    , eventPriority     (eventPriority)
    , depth             (depth)
    , history           ()
    , dut               (dut)
{ 
    RegisterListeners();
}

CommitHistory::~CommitHistory() noexcept
{
    UnregisterListeners();
}

unsigned int CommitHistory::GetEventBusId() const noexcept
{
    return eventBusId;
}

int CommitHistory::GetEventPriority() const noexcept
{
    return eventPriority;
}

size_t CommitHistory::GetDepth() const noexcept
{
    return depth;
}

void CommitHistory::SetDepth(size_t depth) noexcept
{
    this->depth = depth;

    while (history.size() > depth)
        history.pop_back();
}

CommitHistory::Entry& CommitHistory::Push() noexcept
{
    while (history.size() >= depth)
        history.pop_back();

    return history.emplace_front();
}

void CommitHistory::Push(const Entry& entry) noexcept
{
    history.push_front(entry);
}

void CommitHistory::Push(Entry&& entry) noexcept
{
    history.push_front(std::move(entry));
}

template<class... Args>
CommitHistory::Entry& CommitHistory::Push(Args&&... args) noexcept
{
    while (history.size() >= depth)
        history.pop_back();

    return history.emplace_front(std::forward<Args>(args)...);
}

size_t CommitHistory::GetSize() const noexcept
{
    return history.size();
}

const CommitHistory::Entry& CommitHistory::Get(unsigned int index) const noexcept
{
    return history[index];
}

void CommitHistory::Clear() noexcept
{
    history.clear();
}

void CommitHistory::SetDUT(BullsEye::Draconids3014::Thinpad* dut) noexcept
{
    this->dut = dut;
}

BullsEye::Draconids3014::Thinpad* CommitHistory::GetDUT() noexcept
{
    return dut;
}

const BullsEye::Draconids3014::Thinpad* CommitHistory::GetDUT() const noexcept
{
    return dut;
}

CommitHistory::iterator CommitHistory::begin() noexcept
{
    return history.begin();
}

CommitHistory::const_iterator CommitHistory::begin() const noexcept
{
    return history.begin();
}

CommitHistory::iterator CommitHistory::end() noexcept
{
    return history.end();
}

CommitHistory::const_iterator CommitHistory::end() const noexcept
{
    return history.end();
}

std::string CommitHistory::GetListenerName(const char* name) const noexcept
{
    std::ostringstream oss;
    oss << "CommitHistory[";
    oss << std::hex << std::setw(16) << std::setfill('0') << uintptr_t(this);
    oss << "]::" << name;
    return oss.str();
}

void CommitHistory::RegisterListeners() noexcept
{
    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnROBCommit"),
            eventPriority,
            &CommitHistory::OnROBCommit,
            this
        ),
        eventBusId
    );
}

void CommitHistory::UnregisterListeners() noexcept
{
    BullsEye::UnregisterListener(
        GetListenerName("OnROBCommit"),
        &CommitHistory::OnROBCommit,
        eventBusId
    );
}

void CommitHistory::OnROBCommit(BullsEye::Draconids3014::DS232ROBCommitEvent& event) noexcept
{
    if (dut)
    {
        auto& entry = Push();
        entry.SetEvalTime(dut->GetEvalTime());

        auto& track = dut->GetFetchIDTracker().Get(event.GetFID());
        entry.SetUOP40  (track.GetUOP());
        entry.SetPC     (track.GetPC());

        auto insn = BullsEye::Draconids3014::ReverseUOP40_OC3_LA32R(track.GetUOP());
        if (insn)
            entry.SetInstruction(*insn);
        else
            entry.SetInstruction(0xDEADBEEF); // better implementation but not this time
    }
}



// Implementation of: class CommitHistory::Entry
/*
uint64_t                            eval_time;

BullsEye::Draconids3014::uop40_t    uop40;

Jasse::pc_t                         pc;
Jasse::insnraw_t                    insn;
*/

CommitHistory::Entry::Entry() noexcept
    : eval_time (0)
    , uop40     ()
    , pc        (0)
    , insn      ()
{ }

CommitHistory::Entry::Entry(uint64_t eval_time, BullsEye::Draconids3014::uop40_t uop40, Jasse::pc_t pc, Jasse::insnraw_t insn) noexcept
    : eval_time (eval_time)
    , uop40     (uop40)
    , pc        (pc)
    , insn      (insn)
{ }

uint64_t CommitHistory::Entry::GetEvalTime() const noexcept
{
    return eval_time;
}

void CommitHistory::Entry::SetEvalTime(uint64_t eval_time) noexcept
{
    this->eval_time = eval_time;
}

BullsEye::Draconids3014::uop40_t CommitHistory::Entry::GetUOP40() const noexcept
{
    return uop40;
}

void CommitHistory::Entry::SetUOP40(BullsEye::Draconids3014::uop40_t uop40) noexcept
{
    this->uop40 = uop40;
}

Jasse::pc_t CommitHistory::Entry::GetPC() const noexcept
{
    return pc;
}

void CommitHistory::Entry::SetPC(Jasse::pc_t pc) noexcept
{
    this->pc = pc;
}

Jasse::insnraw_t CommitHistory::Entry::GetInstruction() const noexcept
{
    return insn;
}

void CommitHistory::Entry::SetInstruction(Jasse::insnraw_t insn) noexcept
{
    this->insn = insn;
}


// Implementation of: class CommitHistory::Builder
/*
BullsEye::Draconids3014::Thinpad*           dut;
size_t                                      depth;
unsigned int                                eventBusId;
int                                         eventPriority;
*/

CommitHistory::Builder::Builder() noexcept
    : dut               (nullptr)
    , depth             (DEFAULT_DEPTH)
    , eventBusId        (0)
    , eventPriority     (0)
{ }

CommitHistory::Builder& CommitHistory::Builder::DUT(BullsEye::Draconids3014::Thinpad* dut) noexcept
{
    this->dut = dut;
    return *this;
}

CommitHistory::Builder& CommitHistory::Builder::Depth(size_t depth) noexcept
{
    this->depth = depth;
    return *this;
}

CommitHistory::Builder& CommitHistory::Builder::EventBusId(unsigned int eventBusId) noexcept
{
    this->eventBusId = eventBusId;
    return *this;
}

CommitHistory::Builder& CommitHistory::Builder::EventPriority(int eventPriority) noexcept
{
    this->eventPriority = eventPriority;
    return *this;
}

BullsEye::Draconids3014::Thinpad* CommitHistory::Builder::GetDUT() noexcept
{
    return dut;
}

void CommitHistory::Builder::SetDUT(BullsEye::Draconids3014::Thinpad* dut) noexcept
{
    this->dut = dut;
}

size_t CommitHistory::Builder::GetDepth() const noexcept
{
    return depth;
}

void CommitHistory::Builder::SetDepth(size_t depth) noexcept
{
    this->depth = depth;
}

unsigned int CommitHistory::Builder::GetEventBusId() const noexcept
{
    return eventBusId;
}

void CommitHistory::Builder::SetEventBusId(unsigned int eventBusId) noexcept
{
    this->eventBusId = eventBusId;
}

int CommitHistory::Builder::GetEventPriority() const noexcept
{
    return eventPriority;
}

void CommitHistory::Builder::SetEventPriority(int eventPriority) noexcept
{
    this->eventPriority = eventPriority;
}

CommitHistory* CommitHistory::Builder::Build() noexcept
{
    return new CommitHistory(
        dut, 
        depth, 
        eventBusId, 
        eventPriority);
}
