#pragma once
//
//
//
//

#include <string>


#include "appmain_err.hpp"
#include "appmain_periph.hpp"


class PeripheralErrorCapture {
public:
    class Builder;

private:
    CapturedErrors* capturedTo;

    unsigned int    errorEventBusId;
    int             errorEventPriority;

protected:
    PeripheralErrorCapture(CapturedErrors* capturedTo, unsigned int errorEventBusId, int errorEventPriority) noexcept;

protected:
    std::string     GetListenerName(const char* listener_name) noexcept;
    void            RegisterListeners() noexcept;
    void            UnregisterListeners() noexcept;

protected:
    void            OnPeripheralInjectorRejected(PeripheralInjector::RejectedEvent& event) noexcept;
    void            OnPeripheralInjectorNojected(PeripheralInjector::NojectedEvent& event) noexcept;

public:
    ~PeripheralErrorCapture() noexcept;

    PeripheralErrorCapture(const PeripheralErrorCapture&) = delete;
    PeripheralErrorCapture(PeripheralErrorCapture&&) = delete;

    CapturedErrors*         GetCapturedTo() noexcept;
    const CapturedErrors*   GetCapturedTo() const noexcept;
    void                    SetCapturedTo(CapturedErrors* capturedTo) noexcept;

    unsigned int            GetErrorEventBusId() const noexcept;
    int                     GetErrorEventPriority() const noexcept;

    void                    operator=(const PeripheralErrorCapture&) = delete;
    void                    operator=(PeripheralErrorCapture&&) = delete;
};

class PeripheralErrorCapture::Builder {
private:
    CapturedErrors* capturedTo;

    unsigned int    errorEventBusId;
    int             errorEventPriority;

public:
    Builder() noexcept;

    //
    Builder&                CapturedTo(CapturedErrors* capturedTo) noexcept;
    Builder&                ErrorEventBusId(unsigned int errorEventBusId) noexcept;
    Builder&                ErrorEventPriority(int errorEventPriority) noexcept;

    //
    CapturedErrors*         GetCapturedTo() noexcept;
    const CapturedErrors*   GetCapturedTo() const noexcept;
    void                    SetCapturedTo(CapturedErrors* capturedTo) noexcept;

    unsigned int            GetErrorEventBusId() const noexcept;
    void                    SetErrorEventBusId(unsigned int errorEventBusId) noexcept;

    int                     GetErrorEventPriority() const noexcept;
    void                    SetErrorEventPriority(int errorEventPriority) noexcept;

    //
    PeripheralErrorCapture* Build() noexcept;
};
