#pragma once
//
//
//
//

#include <string>
#include <deque>


#include "autoinclude.h"

#include AUTOINC_BE_COMMON(eventbus.hpp)

#include AUTOINC_BE_N1_SOC_LA32(mmu_event.hpp)


class PeripheralInjector {
public:
    class Builder;

public:
    class Element {
    public:
        enum class Type {
            LOAD = 0,
            STORE
        };

    private:
        Type                type;
    
        Jasse::addr_t       address;
        Jasse::LA32MOPWidth width;
        Jasse::memdata_t    data;

    public:
        Element() noexcept;
        Element(Type                type, 
                Jasse::addr_t       address, 
                Jasse::LA32MOPWidth width, 
                Jasse::memdata_t    data) noexcept;

        Type                GetType() const noexcept;
        void                SetType(Type type) noexcept;

        Jasse::addr_t       GetAddress() const noexcept;
        void                SetAddress(Jasse::addr_t address) noexcept;

        Jasse::LA32MOPWidth GetWidth() const noexcept;
        void                SetWidth(Jasse::LA32MOPWidth width) noexcept;

        Jasse::memdata_t    GetData() const noexcept;
        void                SetData(Jasse::memdata_t data) noexcept;
    };

public:
    class InjectedEventBase;
    class RejectedEventBase;
    class NojectedEventBase;

    class InjectedEvent;
    class RejectedEvent;
    class NojectedEvent;

private:
    unsigned int            thisEventBusId;

    unsigned int            refEventBusId;
    int                     refEventPriority;

    unsigned int            dutEventBusId;
    int                     dutEventPriority;

    std::deque<Element>     injections;

protected:
    friend class Builder;
    friend class Element;
    PeripheralInjector(unsigned int thisEventBusId,
                       unsigned int refEventBusId,
                       int          refEventPriority,
                       unsigned int dutEventBusId,
                       int          dutEventPriority) noexcept;

protected:
    std::string     GetListenerName(const char* listener_name) noexcept;
    void            RegisterListeners() noexcept;
    void            UnregisterListeners() noexcept;

protected:
    void            OnRefSerialRead(BullsEye::NSCSCCSingle::NSCSCC2023MMUMappedIOSerialPreReadPreEvent& event) noexcept;
    void            OnRefSerialWrite(BullsEye::NSCSCCSingle::NSCSCC2023MMUMappedIOSerialPreWritePreEvent& event) noexcept;

    void            OnDUTSerialRead(BullsEye::NSCSCCSingle::NSCSCC2023MMUMappedIOSerialPostReadPostEvent& event) noexcept;
    void            OnDUTSerialWrite(BullsEye::NSCSCCSingle::NSCSCC2023MMUMappedIOSerialPostWritePostEvent& event) noexcept;

public:
    ~PeripheralInjector() noexcept;

    PeripheralInjector(const PeripheralInjector&) = delete;
    PeripheralInjector(PeripheralInjector&&) = delete;

    unsigned int    GetThisEventBusId() const noexcept;

    unsigned int    GetRefEventBusId() const noexcept;
    int             GetRefEventPriority() const noexcept;

    unsigned int    GetDUTEventBusId() const noexcept;
    int             GetDUTEventPriority() const noexcept;

    void            operator=(const PeripheralInjector&) = delete;
    void            operator=(PeripheralInjector&&) = delete;
};


class PeripheralInjector::Builder {
private:
    unsigned int        thisEventBusId;

    unsigned int        refEventBusId;
    int                 refEventPriority;

    unsigned int        dutEventBusId;
    int                 dutEventPriority;

public:
    Builder() noexcept;

    //
    Builder&            ThisEventBusId(unsigned int thisEventBusId) noexcept;

    Builder&            RefEventBusId(unsigned int refEventBusId) noexcept;
    Builder&            RefEventPriority(int refEventPriority) noexcept;

    Builder&            DUTEventBusId(unsigned int dutEventBusId) noexcept;
    Builder&            DUTEventPriority(int dutEventPriority) noexcept;

    //
    unsigned int        GetThisEventBusId() const noexcept;
    void                SetThisEventBusId(unsigned int thisEventBusId) noexcept;

    unsigned int        GetRefEventBusId() const noexcept;
    void                SetRefEventBusId(unsigned int refEventBusId) noexcept;

    int                 GetRefEventPriority() const noexcept;
    void                SetRefEventPriority(int refEventPriority) noexcept;

    unsigned int        GetDUTEventBusId() const noexcept;
    void                SetDUTEventBusId(unsigned int dutEventBusId) noexcept;

    int                 GetDUTEventPriority() const noexcept;
    void                SetDUTEventPriority(int dutEventPriority) noexcept;

    //
    PeripheralInjector* Build() noexcept;
};


class PeripheralInjector::InjectedEventBase {
private:
    const Element&  injection;

public:
    InjectedEventBase(const Element& injection) noexcept;

    const Element&  GetInjection() const noexcept;
};

class PeripheralInjector::RejectedEventBase {
private:
    const Element&  injection;
    const Element&  rejection;

public:
    RejectedEventBase(const Element& injection, const Element& rejection) noexcept;

    const Element&  GetInjection() const noexcept;
    const Element&  GetRejection() const noexcept;
};

class PeripheralInjector::NojectedEventBase {
private:
    const Element&  rejection;

public:
    NojectedEventBase(const Element& rejection) noexcept;

    const Element&  GetRejection() const noexcept;
};


class PeripheralInjector::InjectedEvent
    : public InjectedEventBase
    , public BullsEye::Event<InjectedEvent> {
public:
    InjectedEvent(const Element& injection) noexcept;
};

class PeripheralInjector::RejectedEvent
    : public RejectedEventBase
    , public BullsEye::Event<RejectedEvent> {
public:
    RejectedEvent(const Element& injection, const Element& rejection) noexcept;
};

class PeripheralInjector::NojectedEvent
    : public NojectedEventBase
    , public BullsEye::Event<NojectedEvent> {
public:
    NojectedEvent(const Element& rejection) noexcept;
};
