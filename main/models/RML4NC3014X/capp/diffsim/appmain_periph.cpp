#include "appmain_periph.hpp"
//
//
//
//

#include <sstream>
#include <iomanip>


// Implementation of: class PeripheralInjector
/*
unsigned int            thisEventBusId;

unsigned int            refEventBusId;
int                     refEventPriority;

unsigned int            dutEventBusId;
int                     dutEventPriority;

std::deque<Element>     injections;
*/

PeripheralInjector::PeripheralInjector(unsigned int thisEventBusId,
                                       unsigned int refEventBusId,
                                       int          refEventPriority,
                                       unsigned int dutEventBusId,
                                       int          dutEventPriority) noexcept
    : thisEventBusId    (thisEventBusId)
    , refEventBusId     (refEventBusId)
    , refEventPriority  (refEventPriority)
    , dutEventBusId     (dutEventBusId)
    , dutEventPriority  (dutEventPriority)
    , injections        ()
{ 
    RegisterListeners();
}

PeripheralInjector::~PeripheralInjector() noexcept
{
    UnregisterListeners();
}

std::string PeripheralInjector::GetListenerName(const char* listener_name) noexcept
{
    std::ostringstream oss;
    oss << "PeripheralInjector[";
    oss << std::hex << std::setw(16) << std::setfill('0') << uintptr_t(this);
    oss << "]::" << listener_name;
    return oss.str();
}

void PeripheralInjector::RegisterListeners() noexcept
{
    //
    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnRefSerialRead"),
            refEventPriority,
            &PeripheralInjector::OnRefSerialRead,
            this
        ),
        refEventBusId
    );

    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnRefSerialWrite"),
            refEventPriority,
            &PeripheralInjector::OnRefSerialWrite,
            this
        ),
        refEventBusId
    );

    //
    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnDUTSerialRead"),
            dutEventPriority,
            &PeripheralInjector::OnDUTSerialRead,
            this
        ),
        dutEventBusId
    );

    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnDUTSerialWrite"),
            dutEventPriority,
            &PeripheralInjector::OnDUTSerialWrite,
            this
        ),
        dutEventBusId
    );
}

void PeripheralInjector::UnregisterListeners() noexcept
{
    //
    BullsEye::UnregisterListener(
        GetListenerName("OnRefSerialRead"),
        &PeripheralInjector::OnRefSerialWrite,
        refEventBusId
    );

    BullsEye::UnregisterListener(
        GetListenerName("OnRefSerialWrite"),
        &PeripheralInjector::OnRefSerialWrite,
        refEventBusId
    );

    //
    BullsEye::UnregisterListener(
        GetListenerName("OnDUTSerialRead"),
        &PeripheralInjector::OnDUTSerialRead,
        dutEventBusId
    );

    BullsEye::UnregisterListener(
        GetListenerName("OnDUTSerialWrite"),
        &PeripheralInjector::OnDUTSerialWrite,
        dutEventBusId
    );
}

void PeripheralInjector::OnRefSerialRead(BullsEye::NSCSCCSingle::NSCSCC2023MMUMappedIOSerialPreReadPreEvent& event) noexcept
{
    Element target(
        Element::Type::LOAD,
        event.GetAddress(),
        event.GetWidth(),
        { 0 });

    // check injection
    if (injections.empty())
    {
        NojectedEvent(target).Fire(thisEventBusId);
        return;
    }

    Element& inject = injections.front();

    if (inject.GetType()    != Element::Type::LOAD
    ||  inject.GetAddress() != target.GetAddress()
    ||  inject.GetWidth()   != target.GetWidth())
    {
        RejectedEvent(inject, target).Fire(thisEventBusId);
        return;
    }

    // inject
    event.SetProxy(true, [&](
            Jasse::LA32MOPPath, Jasse::addr_t, Jasse::LA32MOPWidth, 
            Jasse::memdata_t*   data) -> Jasse::LA32MOPOutcome {
        *data = inject.GetData();
        return { Jasse::LA32MOPStatus::MOP_SUCCESS };
    });

    InjectedEvent(inject).Fire(thisEventBusId);

    //
    injections.pop_front();
}

void PeripheralInjector::OnRefSerialWrite(BullsEye::NSCSCCSingle::NSCSCC2023MMUMappedIOSerialPreWritePreEvent& event) noexcept
{
    Element target(
        Element::Type::STORE,
        event.GetAddress(),
        event.GetWidth(),
        event.GetData());

    // check injection
    if (injections.empty())
    {
        NojectedEvent(target).Fire(thisEventBusId);
        return;
    }

    Element& inject = injections.front();

    if (inject.GetType()    != Element::Type::STORE
    ||  inject.GetAddress() != target.GetAddress()
    ||  inject.GetWidth()   != target.GetWidth()
    ||  inject.GetData().As(inject.GetWidth()) != target.GetData().As(inject.GetWidth()))
    {
        RejectedEvent(inject, target).Fire(thisEventBusId);
        return;
    }

    // inject
    event.SetProxy(true, [&](
            Jasse::LA32MOPPath, Jasse::addr_t, Jasse::LA32MOPWidth, Jasse::memdata_t) -> Jasse::LA32MOPOutcome {
        return { Jasse::LA32MOPStatus::MOP_SUCCESS };
    });

    InjectedEvent(inject).Fire(thisEventBusId);

    //
    injections.pop_front();
}

void PeripheralInjector::OnDUTSerialRead(BullsEye::NSCSCCSingle::NSCSCC2023MMUMappedIOSerialPostReadPostEvent& event) noexcept
{
    injections.emplace_back(
        Element::Type::LOAD,
        event.GetAddress(),
        event.GetWidth(),
        event.GetData());
}

void PeripheralInjector::OnDUTSerialWrite(BullsEye::NSCSCCSingle::NSCSCC2023MMUMappedIOSerialPostWritePostEvent& event) noexcept
{
    injections.emplace_back(
        Element::Type::STORE,
        event.GetAddress(),
        event.GetWidth(),
        event.GetData()
    );
}

unsigned int PeripheralInjector::GetThisEventBusId() const noexcept
{
    return thisEventBusId;
}

unsigned int PeripheralInjector::GetRefEventBusId() const noexcept
{
    return refEventBusId;
}

int PeripheralInjector::GetRefEventPriority() const noexcept
{
    return refEventPriority;
}

unsigned int PeripheralInjector::GetDUTEventBusId() const noexcept
{
    return dutEventBusId;
}

int PeripheralInjector::GetDUTEventPriority() const noexcept
{
    return dutEventPriority;
}




// Implementation of: class PeripheralInjector::Builder
/*
unsigned int        thisEventBusId;

unsigned int        refEventBusId;
int                 refEventPriority;

unsigned int        dutEventBusId;
int                 dutEventPriority;
*/

PeripheralInjector::Builder::Builder() noexcept
    : thisEventBusId    (0)
    , refEventBusId     (0)
    , refEventPriority  (0)
    , dutEventBusId     (0)
    , dutEventPriority  (0)
{ }

PeripheralInjector::Builder& PeripheralInjector::Builder::ThisEventBusId(unsigned int thisEventBusId) noexcept
{
    this->thisEventBusId = thisEventBusId;
    return *this;
}

PeripheralInjector::Builder& PeripheralInjector::Builder::RefEventBusId(unsigned int refEventBusId) noexcept
{
    this->refEventBusId = refEventBusId;
    return *this;
}

PeripheralInjector::Builder& PeripheralInjector::Builder::RefEventPriority(int refEventPriority) noexcept
{
    this->refEventPriority = refEventPriority;
    return *this;
}

PeripheralInjector::Builder& PeripheralInjector::Builder::DUTEventBusId(unsigned int dutEventBusId) noexcept
{
    this->dutEventBusId = dutEventBusId;
    return *this;
}

PeripheralInjector::Builder& PeripheralInjector::Builder::DUTEventPriority(int dutEventPriority) noexcept
{
    this->dutEventPriority = dutEventPriority;
    return *this;
}

unsigned int PeripheralInjector::Builder::GetThisEventBusId() const noexcept
{
    return thisEventBusId;
}

void PeripheralInjector::Builder::SetThisEventBusId(unsigned int thisEventBusId) noexcept
{
    this->thisEventBusId = thisEventBusId;
}

unsigned int PeripheralInjector::Builder::GetRefEventBusId() const noexcept
{
    return refEventBusId;
}

void PeripheralInjector::Builder::SetRefEventBusId(unsigned int refEventBusId) noexcept
{
    this->refEventBusId = refEventBusId;
}

int PeripheralInjector::Builder::GetRefEventPriority() const noexcept
{
    return refEventPriority;
}

void PeripheralInjector::Builder::SetRefEventPriority(int refEventPriority) noexcept
{
    this->refEventPriority = refEventPriority;
}

unsigned int PeripheralInjector::Builder::GetDUTEventBusId() const noexcept
{
    return dutEventBusId;
}

void PeripheralInjector::Builder::SetDUTEventBusId(unsigned int dutEventBusId) noexcept
{
    this->dutEventBusId = dutEventBusId;
}

int PeripheralInjector::Builder::GetDUTEventPriority() const noexcept
{
    return dutEventPriority;
}

void PeripheralInjector::Builder::SetDUTEventPriority(int dutEventPriority) noexcept
{
    this->dutEventPriority = dutEventPriority;
}

PeripheralInjector* PeripheralInjector::Builder::Build() noexcept
{
    return new PeripheralInjector(thisEventBusId, refEventBusId, refEventPriority, dutEventBusId, dutEventPriority);
}




// Implementation of: class PeripheralInjector::Element
/*
Type                type;
    
Jasse::addr_t       address;
Jasse::LA32MOPWidth width;
Jasse::memdata_t    data;
*/

PeripheralInjector::Element::Element() noexcept
    : type      ()
    , address   ()
    , width     ()
    , data      ()
{ }

PeripheralInjector::Element::Element(Type                type, 
                                     Jasse::addr_t       address, 
                                     Jasse::LA32MOPWidth width, 
                                     Jasse::memdata_t    data) noexcept
    : type      (type)
    , address   (address)
    , width     (width)
    , data      (data)
{ }

PeripheralInjector::Element::Type PeripheralInjector::Element::GetType() const noexcept
{
    return type;
}

void PeripheralInjector::Element::SetType(Type type) noexcept
{
    this->type = type;
}

Jasse::addr_t PeripheralInjector::Element::GetAddress() const noexcept
{
    return address;
}

void PeripheralInjector::Element::SetAddress(Jasse::addr_t address) noexcept
{
    this->address = address;
}

Jasse::LA32MOPWidth PeripheralInjector::Element::GetWidth() const noexcept
{
    return width;
}

void PeripheralInjector::Element::SetWidth(Jasse::LA32MOPWidth width) noexcept
{
    this->width = width;
}

Jasse::memdata_t PeripheralInjector::Element::GetData() const noexcept
{
    return data;
}

void PeripheralInjector::Element::SetData(Jasse::memdata_t data) noexcept
{
    this->data = data;
}



// Implementation of: class PeripheralInjector::InjectedEventBase
/*
const Element&  injection;
*/

PeripheralInjector::InjectedEventBase::InjectedEventBase(const Element& injection) noexcept
    : injection (injection)
{ }

const PeripheralInjector::Element& PeripheralInjector::InjectedEventBase::GetInjection() const noexcept
{
    return injection;
}



// Implementation of: class PeripheralInjector::RejectedEventBase
/*
const Element&  injection;
const Element&  rejection;
*/

PeripheralInjector::RejectedEventBase::RejectedEventBase(const Element& injection, const Element& rejection) noexcept
    : injection (injection)
    , rejection (rejection)
{ }

const PeripheralInjector::Element& PeripheralInjector::RejectedEventBase::GetInjection() const noexcept
{
    return injection;
}

const PeripheralInjector::Element& PeripheralInjector::RejectedEventBase::GetRejection() const noexcept
{
    return rejection;
}



// Implementation of: class PeripheralInjector::NojectedEventBase
/*
const Element&  rejection;
*/

PeripheralInjector::NojectedEventBase::NojectedEventBase(const Element& rejection) noexcept
    : rejection (rejection)
{ }

const PeripheralInjector::Element& PeripheralInjector::NojectedEventBase::GetRejection() const noexcept
{
    return rejection;
}



// Implementation of: class PeripheralInjector::InjectedEvent

PeripheralInjector::InjectedEvent::InjectedEvent(const Element& injection) noexcept
    : InjectedEventBase (injection)
{ }



// Implementation of: class PeripheralInjector::RejectedEvent

PeripheralInjector::RejectedEvent::RejectedEvent(const Element& injection, const Element& rejection) noexcept
    : RejectedEventBase (injection, rejection)
{ }



// Implementation of: class PeripheralInjector::NojectedEvent

PeripheralInjector::NojectedEvent::NojectedEvent(const Element& rejection) noexcept
    : NojectedEventBase (rejection)
{ }
