#pragma once
//
//
//
//

#include <string>


#include "appmain_err.hpp"
#include "appmain_periph.hpp"
#include "appmain_verifier.hpp"


#include "autoinclude.h"

#include AUTOINC_BE_N1_SOC_LA32(mmu_event.hpp)


class PeripheralErrorCapture {
public:
    class Builder;

private:
    CapturedErrors* capturedTo;

    unsigned int    errorEventBusId;
    int             errorEventPriority;

protected:
    friend class Builder;
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



class DifferentialVerifierErrorCapture {
public:
    class Builder;

private:
    CapturedErrors* capturedTo;

    unsigned int    errorEventBusId;
    int             errorEventPriority;

protected:
    friend class Builder;
    DifferentialVerifierErrorCapture(CapturedErrors* capturedTo, unsigned int errorEventBusId, int errorEventPriority) noexcept;

protected:
    std::string     GetListenerName(const char* listener_name) noexcept;
    void            RegisterListeners() noexcept;
    void            UnregisterListeners() noexcept;

protected:
    void            OnMismatchedPC(DifferentialVerifier::MismatchedPCEvent& event) noexcept;
    void            OnMismatchedInstruction(DifferentialVerifier::MismatchedInstructionEvent& event) noexcept;
    void            OnMismatchedGPR(DifferentialVerifier::MismatchedGPREvent& event) noexcept;
    void            OnMismatchedMemoryStore(DifferentialVerifier::MismatchedMemoryStoreEvent& event) noexcept;

public:
    ~DifferentialVerifierErrorCapture() noexcept;

    DifferentialVerifierErrorCapture(const DifferentialVerifierErrorCapture&) = delete;
    DifferentialVerifierErrorCapture(DifferentialVerifierErrorCapture&&) = delete;

    CapturedErrors*         GetCapturedTo() noexcept;
    const CapturedErrors*   GetCapturedTo() const noexcept;
    void                    SetCapturedTo(CapturedErrors* capturedTo) noexcept;

    unsigned int            GetErrorEventBusId() const noexcept;
    int                     GetErrorEventPriority() const noexcept;

    void                    operator=(const DifferentialVerifierErrorCapture&) = delete;
    void                    operator=(DifferentialVerifierErrorCapture&&) = delete;
};

class DifferentialVerifierErrorCapture::Builder {
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
    DifferentialVerifierErrorCapture* Build() noexcept;
};



class MMUErrorCapture {
public:
    class Builder;

private:
    std::string     source;

    CapturedErrors* capturedTo;

    unsigned int    errorEventBusId;
    int             errorEventPriority;

protected:
    friend class Builder;
    MMUErrorCapture(const char* source, CapturedErrors* capturedTo, unsigned int errorEventBusId, int errorEventPriority) noexcept;

protected:
    std::string     GetListenerName(const char* listener_name) const noexcept;
    void            RegisterListeners() noexcept;
    void            UnregisterListeners() noexcept;

protected:
    void            OnMMUPostReadPostEvent(BullsEye::NSCSCCSingle::NSCSCC2023MMUPostReadPostEvent& event) noexcept;
    void            OnMMUPostWritePostEvent(BullsEye::NSCSCCSingle::NSCSCC2023MMUPostWritePostEvent& event) noexcept;

public:
    ~MMUErrorCapture() noexcept;

    MMUErrorCapture(const MMUErrorCapture&) = delete;
    MMUErrorCapture(MMUErrorCapture&&) = delete;

    std::string             GetSource() const noexcept;

    CapturedErrors*         GetCapturedTo() noexcept;
    const CapturedErrors*   GetCapturedTo() const noexcept;
    void                    SetCapturedTo(CapturedErrors* capturedTo) noexcept;

    unsigned int            GetErrorEventBusId() const noexcept;
    int                     GetErrorEventPriority() const noexcept;

    void                    operator=(const MMUErrorCapture&) = delete;
    void                    operator=(MMUErrorCapture&&) = delete;
};

class MMUErrorCapture::Builder {
private:
    std::string     source;

    CapturedErrors* capturedTo;

    unsigned int    errorEventBusId;
    int             errorEventPriority;

public:
    Builder() noexcept;

    //
    Builder&                Source(const char* source) noexcept;
    Builder&                CapturedTo(CapturedErrors* capturedTo) noexcept;
    Builder&                ErrorEventBusId(unsigned int errorEventBusId) noexcept;
    Builder&                ErrorEventPriority(int errorEventPriority) noexcept;

    //
    std::string             GetSource() const noexcept;
    void                    SetSource(const char* source) noexcept;

    CapturedErrors*         GetCapturedTo() noexcept;
    const CapturedErrors*   GetCapturedTo() const noexcept;
    void                    SetCapturedTo(CapturedErrors* capturedTo) noexcept;

    unsigned int            GetErrorEventBusId() const noexcept;
    void                    SetErrorEventBusId(unsigned int errorEventBusId) noexcept;

    int                     GetErrorEventPriority() const noexcept;
    void                    SetErrorEventPriority(int errorEventPriority) noexcept;

    //
    MMUErrorCapture*        Build() noexcept;
};

