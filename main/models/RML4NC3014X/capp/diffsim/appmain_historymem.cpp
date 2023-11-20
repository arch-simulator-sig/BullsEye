#include "appmain_historymem.hpp"
//
//
//
//

#include <sstream>
#include <iomanip>


#include "autoinclude.h"

#include AUTOINC_BE_COMMON(eventbus.hpp)


// Implementation of: class MMIOHistory::Entry
/*
Type                    type;
Jasse::LA32MOPPath      path;
Jasse::addr_t           address;
Jasse::LA32MOPWidth     width;
Jasse::memdata_t        data;
Jasse::LA32MOPOutcome   outcome;
*/

MMIOHistory::Entry::Entry(Entry::Type           type,
                          Jasse::LA32MOPPath    path,
                          Jasse::addr_t         address,
                          Jasse::LA32MOPWidth   width,
                          Jasse::memdata_t      data,
                          Jasse::LA32MOPOutcome outcome) noexcept
    : type      (type)
    , path      (path)
    , address   (address)
    , width     (width)
    , data      (data)
    , outcome   (outcome)
{ }

MMIOHistory::Entry::Type MMIOHistory::Entry::GetType() const noexcept
{
    return type;
}

Jasse::LA32MOPPath MMIOHistory::Entry::GetPath() const noexcept
{
    return path;
}

Jasse::addr_t MMIOHistory::Entry::GetAddress() const noexcept
{
    return address;
}

Jasse::LA32MOPWidth MMIOHistory::Entry::GetWidth() const noexcept
{
    return width;
}

Jasse::memdata_t MMIOHistory::Entry::GetData() const noexcept
{
    return data;
}

Jasse::LA32MOPOutcome MMIOHistory::Entry::GetOutcome() const noexcept
{
    return outcome;
}


// Implementation of: class MMIOHistory
/*
size_T              depth;
std::deque<Entry>   history;
*/

MMIOHistory::MMIOHistory(size_t depth) noexcept
    : depth     (depth)
    , history   ()
{ }

size_t MMIOHistory::GetDepth() const noexcept
{
    return depth;
}

void MMIOHistory::SetDepth(size_t depth) noexcept
{
    this->depth = depth;

    while (history.size() > depth)
        history.pop_back();
}

void MMIOHistory::Push(const Entry& entry) noexcept
{
    history.push_front(entry);

    while (history.size() > depth)
        history.pop_back();
}

void MMIOHistory::Emplace(Entry::Type           type, 
                          Jasse::LA32MOPPath    path,
                          Jasse::addr_t         address,
                          Jasse::LA32MOPWidth   width,
                          Jasse::memdata_t      data,
                          Jasse::LA32MOPOutcome outcome) noexcept
{
    history.emplace_front(type, path, address, width, data, outcome);

    while (history.size() > depth)
        history.pop_back();
}

size_t MMIOHistory::GetCount() const noexcept
{
    return history.size();
}

const MMIOHistory::Entry& MMIOHistory::Get(unsigned int index) const noexcept
{
    return history[index];
}

void MMIOHistory::Clear() noexcept
{
    history.clear();
}

MMIOHistory::iterator MMIOHistory::begin() noexcept
{
    return history.begin();
}

MMIOHistory::const_iterator MMIOHistory::begin() const noexcept
{
    return history.begin();
}

MMIOHistory::iterator MMIOHistory::end() noexcept
{
    return history.end();
}

MMIOHistory::const_iterator MMIOHistory::end() const noexcept
{
    return history.end();
}



// Implementation of: class MMIOReadHistory
/*
unsigned int    eventBusId;
int             eventPriority;
*/

MMIOReadHistory::MMIOReadHistory(size_t depth, unsigned int eventBusId, int eventPriority) noexcept
    : MMIOHistory   (depth)
    , eventBusId    (eventBusId)
    , eventPriority (eventPriority)
{ 
    RegisterListeners();
}

MMIOReadHistory::~MMIOReadHistory() noexcept
{
    UnregisterListeners();
}

unsigned int MMIOReadHistory::GetEventBusId() const noexcept
{
    return eventBusId;
}

int MMIOReadHistory::GetEventPriority() const noexcept
{
    return eventPriority;
}

std::string MMIOReadHistory::GetListenerName(const char* listener_name) const noexcept
{
    std::ostringstream oss;
    oss << "MMIOReadHistory[";
    oss << std::hex << std::setw(16) << std::setfill('0') << uintptr_t(this);
    oss << "]::" << listener_name;
    return oss.str();
}

void MMIOReadHistory::RegisterListeners() noexcept
{
    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnMMUPostReadPostEvent"),
            eventPriority,
            &MMIOReadHistory::OnMMUPostReadPostEvent,
            this
        ),
        eventBusId
    );
}

void MMIOReadHistory::UnregisterListeners() noexcept
{
    BullsEye::UnregisterListener(
        GetListenerName("OnMMUPostReadPostEvent"),
        &MMIOReadHistory::OnMMUPostReadPostEvent,
        eventBusId
    );
}

void MMIOReadHistory::OnMMUPostReadPostEvent(BullsEye::NSCSCCSingle::NSCSCC2023MMUPostReadPostEvent& event) noexcept
{
    Emplace(
        Entry::Type::READ,
        event.GetPath(),
        event.GetAddress(),
        event.GetWidth(),
        event.GetData(),
        event.GetOutcome()
    );
}


// Implementation of: class MMIOReadHistory::Builder
/*
size_t          depth;
unsigned int    eventBusId;
int             eventPriority;
*/

MMIOReadHistory::Builder::Builder() noexcept
    : depth         (DEFAULT_DEPTH)
    , eventBusId    (0)
    , eventPriority (0)
{ }

MMIOReadHistory::Builder& MMIOReadHistory::Builder::Depth(size_t depth) noexcept
{
    this->depth = depth;
    return *this;
}

MMIOReadHistory::Builder& MMIOReadHistory::Builder::EventBusId(unsigned int eventBusId) noexcept
{
    this->eventBusId = eventBusId;
    return *this;
}

MMIOReadHistory::Builder& MMIOReadHistory::Builder::EventPriority(int eventPriority) noexcept
{
    this->eventPriority = eventPriority;
    return *this;
}

size_t MMIOReadHistory::Builder::GetDepth() const noexcept
{
    return depth;
}

void MMIOReadHistory::Builder::SetDepth(size_t depth) noexcept
{
    this->depth = depth;
}

unsigned int MMIOReadHistory::Builder::GetEventBusId() const noexcept
{
    return eventBusId;
}

void MMIOReadHistory::Builder::SetEventBusId(unsigned int eventBusId) noexcept
{
    this->eventBusId = eventBusId;
}

int MMIOReadHistory::Builder::GetEventPriority() const noexcept
{
    return eventPriority;
}

void MMIOReadHistory::Builder::SetEventPriority(int eventPriority) noexcept
{
    this->eventPriority = eventPriority;
}

MMIOReadHistory* MMIOReadHistory::Builder::Build() noexcept
{
    return new MMIOReadHistory(depth, eventBusId, eventPriority);
}



// Implementation of: class MMIOWriteHistory
/*
unsigned int    eventBusId;
int             eventPriority;
*/

MMIOWriteHistory::MMIOWriteHistory(size_t depth, unsigned int eventBusId, int eventPriority) noexcept
    : MMIOHistory   (depth)
    , eventBusId    (eventBusId)
    , eventPriority (eventPriority)
{ 
    RegisterListeners();
}

MMIOWriteHistory::~MMIOWriteHistory() noexcept
{
    UnregisterListeners();
}

unsigned int MMIOWriteHistory::GetEventBusId() const noexcept
{
    return eventBusId;
}

int MMIOWriteHistory::GetEventPriority() const noexcept
{
    return eventPriority;
}

std::string MMIOWriteHistory::GetListenerName(const char* listener_name) const noexcept
{
    std::ostringstream oss;
    oss << "MMIOWriteHistory[";
    oss << std::hex << std::setw(16) << std::setfill('0') << uintptr_t(this);
    oss << "]::" << listener_name;
    return oss.str();
}

void MMIOWriteHistory::RegisterListeners() noexcept
{
    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnMMUPostWritePostEvent"),
            eventPriority,
            &MMIOWriteHistory::OnMMUPostWritePostEvent,
            this
        ),
        eventBusId
    );
}

void MMIOWriteHistory::UnregisterListeners() noexcept
{
    BullsEye::UnregisterListener(
        GetListenerName("OnMMUPostWritePostEvent"),
        &MMIOWriteHistory::OnMMUPostWritePostEvent,
        eventBusId
    );
}

void MMIOWriteHistory::OnMMUPostWritePostEvent(BullsEye::NSCSCCSingle::NSCSCC2023MMUPostWritePostEvent& event) noexcept
{
    Emplace(
        Entry::Type::WRITE,
        event.GetPath(),
        event.GetAddress(),
        event.GetWidth(),
        event.GetData(),
        event.GetOutcome()
    );
}


// Implementation of: class MMIOWriteHistory::Builder
/*
size_t          depth;
unsigned int    eventBusId;
int             eventPriority;
*/

MMIOWriteHistory::Builder::Builder() noexcept
    : depth         (DEFAULT_DEPTH)
    , eventBusId    (0)
    , eventPriority (0)
{ }

MMIOWriteHistory::Builder& MMIOWriteHistory::Builder::Depth(size_t depth) noexcept
{
    this->depth = depth;
    return *this;
}

MMIOWriteHistory::Builder& MMIOWriteHistory::Builder::EventBusId(unsigned int eventBusId) noexcept
{
    this->eventBusId = eventBusId;
    return *this;
}

MMIOWriteHistory::Builder& MMIOWriteHistory::Builder::EventPriority(int eventPriority) noexcept
{
    this->eventPriority = eventPriority;
    return *this;
}

size_t MMIOWriteHistory::Builder::GetDepth() const noexcept
{
    return depth;
}

void MMIOWriteHistory::Builder::SetDepth(size_t depth) noexcept
{
    this->depth = depth;
}

unsigned int MMIOWriteHistory::Builder::GetEventBusId() const noexcept
{
    return eventBusId;
}

void MMIOWriteHistory::Builder::SetEventBusId(unsigned int eventBusId) noexcept
{
    this->eventBusId = eventBusId;
}

int MMIOWriteHistory::Builder::GetEventPriority() const noexcept
{
    return eventPriority;
}

void MMIOWriteHistory::Builder::SetEventPriority(int eventPriority) noexcept
{
    this->eventPriority = eventPriority;
}

MMIOWriteHistory* MMIOWriteHistory::Builder::Build() noexcept
{
    return new MMIOWriteHistory(depth, eventBusId, eventPriority);
}



// Implementation of: class MMIOReadWriteHistory
/*
unsigned int    eventBusId;
int             eventPriority;
*/

MMIOReadWriteHistory::MMIOReadWriteHistory(size_t depth, unsigned int eventBusId, int eventPriority) noexcept
    : MMIOHistory   (depth)
    , eventBusId    (eventBusId)
    , eventPriority (eventPriority)
{ 
    RegisterListeners();
}

MMIOReadWriteHistory::~MMIOReadWriteHistory() noexcept
{
    UnregisterListeners();
}

unsigned int MMIOReadWriteHistory::GetEventBusId() const noexcept
{
    return eventBusId;
}

int MMIOReadWriteHistory::GetEventPriority() const noexcept
{
    return eventPriority;
}

std::string MMIOReadWriteHistory::GetListenerName(const char* listener_name) const noexcept
{
    std::ostringstream oss;
    oss << "MMIOReadWriteHistory[";
    oss << std::hex << std::setw(16) << std::setfill('0') << uintptr_t(this);
    oss << "]::" << listener_name;
    return oss.str();
}

void MMIOReadWriteHistory::RegisterListeners() noexcept
{
    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnMMUPostReadPostEvent"),
            eventPriority,
            &MMIOReadWriteHistory::OnMMUPostReadPostEvent,
            this
        ),
        eventBusId
    );

    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnMMUPostWritePostEvent"),
            eventPriority,
            &MMIOReadWriteHistory::OnMMUPostWritePostEvent,
            this
        ),
        eventBusId
    );
}

void MMIOReadWriteHistory::UnregisterListeners() noexcept
{
    BullsEye::UnregisterListener(
        GetListenerName("OnMMUPostReadPostEvent"),
        &MMIOReadWriteHistory::OnMMUPostReadPostEvent,
        eventBusId
    );

    BullsEye::UnregisterListener(
        GetListenerName("OnMMUPostWritePostEvent"),
        &MMIOReadWriteHistory::OnMMUPostWritePostEvent,
        eventBusId
    );
}

void MMIOReadWriteHistory::OnMMUPostReadPostEvent(BullsEye::NSCSCCSingle::NSCSCC2023MMUPostReadPostEvent& event) noexcept
{
    Emplace(
        Entry::Type::READ,
        event.GetPath(),
        event.GetAddress(),
        event.GetWidth(),
        event.GetData(),
        event.GetOutcome()
    );
}

void MMIOReadWriteHistory::OnMMUPostWritePostEvent(BullsEye::NSCSCCSingle::NSCSCC2023MMUPostWritePostEvent& event) noexcept
{
    Emplace(
        Entry::Type::WRITE,
        event.GetPath(),
        event.GetAddress(),
        event.GetWidth(),
        event.GetData(),
        event.GetOutcome()
    );
}


// Implementation of: class MMIOReadWriteHistory::Builder
/*
size_t          depth;
unsigned int    eventBusId;
int             eventPriority;
*/

MMIOReadWriteHistory::Builder::Builder() noexcept
    : depth         (DEFAULT_DEPTH)
    , eventBusId    (0)
    , eventPriority (0)
{ }

MMIOReadWriteHistory::Builder& MMIOReadWriteHistory::Builder::Depth(size_t depth) noexcept
{
    this->depth = depth;
    return *this;
}

MMIOReadWriteHistory::Builder& MMIOReadWriteHistory::Builder::EventBusId(unsigned int eventBusId) noexcept
{
    this->eventBusId = eventBusId;
    return *this;
}

MMIOReadWriteHistory::Builder& MMIOReadWriteHistory::Builder::EventPriority(int eventPriority) noexcept
{
    this->eventPriority = eventPriority;
    return *this;
}

size_t MMIOReadWriteHistory::Builder::GetDepth() const noexcept
{
    return depth;
}

void MMIOReadWriteHistory::Builder::SetDepth(size_t depth) noexcept
{
    this->depth = depth;
}

unsigned int MMIOReadWriteHistory::Builder::GetEventBusId() const noexcept
{
    return eventBusId;
}

void MMIOReadWriteHistory::Builder::SetEventBusId(unsigned int eventBusId) noexcept
{
    this->eventBusId = eventBusId;
}

int MMIOReadWriteHistory::Builder::GetEventPriority() const noexcept
{
    return eventPriority;
}

void MMIOReadWriteHistory::Builder::SetEventPriority(int eventPriority) noexcept
{
    this->eventPriority = eventPriority;
}

MMIOReadWriteHistory* MMIOReadWriteHistory::Builder::Build() noexcept
{
    return new MMIOReadWriteHistory(depth, eventBusId, eventPriority);
}
