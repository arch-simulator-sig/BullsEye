#pragma once
//
//
//
//

#include <string>
#include <deque>


#include "appmain_err.hpp"
#include "appmain_periph.hpp"
#include "appmain_verifier.hpp"


#include "autoinclude.h"

#include AUTOINC_BE_N1_SOC_LA32(mmu_event.hpp)

#include "../../csrc/soc/soc_axi_event.hpp"


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



class AXIBridgeErrorCapture {
public:
    class Builder;

public:
    class Trace {
    public:
        enum class Type {
            READ = 0,
            WRITE
        };

        enum class Path {
            INSN = 0,
            DATA
        };

    public:
        Type                            type;
        Path                            path;

        uint4_t                         id;
        uint32_t                        address;
        BullsEye::AXI4::attr_len_t      length;
        BullsEye::AXI4::attr_size_t     size;
        BullsEye::AXI4::attr_burst_t    burst;
        uint1_t                         uncached;
    };

private:
    std::string         source;

    CapturedErrors*     capturedTo;

    unsigned int        errorEventBusId;
    int                 errorEventPriority;

    unsigned int        traceDepth;
    std::deque<Trace>   traces;

public:
    friend class Builder;
    AXIBridgeErrorCapture(const char* source, CapturedErrors* capturedTo, unsigned int errorEventBusId, int errorEventPriority, unsigned traceDepth) noexcept;

protected:
    std::string     GetListenerName(const char* listener_name) const noexcept;
    void            RegisterListeners() noexcept;
    void            UnregisterListeners() noexcept;

protected:
    void            OnFetchReadAccepted(BullsEye::Draconids3014::SoCAXIBridgeFetchReadAddressAcceptedPostEvent& event) noexcept;
    void            OnDataReadAccepted(BullsEye::Draconids3014::SoCAXIBridgeDataReadAddressAcceptedPostEvent& event) noexcept;
    void            OnDataWriteAccepted(BullsEye::Draconids3014::SoCAXIBridgeDataWriteAddressAcceptedPostEvent& event) noexcept;

    void            OnFetchError(BullsEye::Draconids3014::SoCAXIBridgeFetchErrorEvent& event) noexcept;
    void            OnDataError(BullsEye::Draconids3014::SoCAXIBridgeDataErrorEvent& event) noexcept;

public:
    ~AXIBridgeErrorCapture() noexcept;

    AXIBridgeErrorCapture(const AXIBridgeErrorCapture&) = delete;
    AXIBridgeErrorCapture(AXIBridgeErrorCapture&&) = delete;

    std::string             GetSource() const noexcept;

    CapturedErrors*         GetCapturedTo() noexcept;
    const CapturedErrors*   GetCapturedTo() const noexcept;
    void                    SetCapturedTo(CapturedErrors* capturedTo) noexcept;

    unsigned int            GetErrorEventBusId() const noexcept;
    int                     GetErrorEventPriority() const noexcept;

    unsigned int            GetTraceDepth() const noexcept;

    void                    operator=(const AXIBridgeErrorCapture&) = delete;
    void                    operator=(AXIBridgeErrorCapture&&) = delete;
};

class AXIBridgeErrorCapture::Builder {
private:
    std::string     source;

    CapturedErrors* capturedTo;

    unsigned int    errorEventBusId;
    int             errorEventPriority;

    unsigned int    traceDepth;

public:
    Builder() noexcept;

    //
    Builder&                Source(const char* source) noexcept;
    Builder&                CapturedTo(CapturedErrors* capturedTo) noexcept;
    Builder&                ErrorEventBusId(unsigned int errorEventBusId) noexcept;
    Builder&                ErrorEventPriority(int errorEventPriority) noexcept;
    Builder&                TraceDepth(unsigned int traceDepth) noexcept;

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

    unsigned int            GetTraceDepth() const noexcept;
    void                    SetTraceDepth(unsigned int traceDepth) noexcept;

    //
    AXIBridgeErrorCapture*  Build() noexcept;
};


