#include "appmain_errcapt.hpp"
//
//
//
//

#include <sstream>
#include <iomanip>


// Implementation of: class PeripheralErrorCapture
/*
CapturedErrors* capturedTo;

unsigned int    errorEventBusId;
int             errorEventPriority;
*/

PeripheralErrorCapture::PeripheralErrorCapture(CapturedErrors* capturedTo, unsigned int errorEventBusId, int errorEventPriority) noexcept
    : capturedTo            (capturedTo)
    , errorEventBusId       (errorEventBusId)
    , errorEventPriority    (errorEventPriority)
{
    RegisterListeners();
}

PeripheralErrorCapture::~PeripheralErrorCapture() noexcept
{
    UnregisterListeners();
}

std::string PeripheralErrorCapture::GetListenerName(const char* listener_name) noexcept
{
    std::ostringstream oss;
    oss << "PeripheralErrorCapture[";
    oss << std::hex << std::setw(16) << std::setfill('0') << uintptr_t(this);
    oss << "]::" << listener_name;
    return oss.str();
}

CapturedErrors* PeripheralErrorCapture::GetCapturedTo() noexcept
{
    return capturedTo;
}

const CapturedErrors* PeripheralErrorCapture::GetCapturedTo() const noexcept
{
    return capturedTo;
}

void PeripheralErrorCapture::SetCapturedTo(CapturedErrors* capturedTo) noexcept
{
    this->capturedTo = capturedTo;
}

unsigned int PeripheralErrorCapture::GetErrorEventBusId() const noexcept
{
    return errorEventBusId;
}

int PeripheralErrorCapture::GetErrorEventPriority() const noexcept
{
    return errorEventPriority;
}



// Implementation of: class ErrorCapture::Builder
/*
CapturedErrors* capturedTo;

unsigned int    errorEventBusId;
int             errorEventPriority;
*/

PeripheralErrorCapture::Builder::Builder() noexcept
    : errorEventBusId       (0)
    , errorEventPriority    (0)
{ }

PeripheralErrorCapture::Builder& PeripheralErrorCapture::Builder::CapturedTo(CapturedErrors* capturedTo) noexcept
{
    this->capturedTo = capturedTo;
    return *this;
}

PeripheralErrorCapture::Builder& PeripheralErrorCapture::Builder::ErrorEventBusId(unsigned int errorEventBusId) noexcept
{
    this->errorEventBusId = errorEventBusId;
    return *this;
}

PeripheralErrorCapture::Builder& PeripheralErrorCapture::Builder::ErrorEventPriority(int errorEventPriority) noexcept
{
    this->errorEventPriority = errorEventPriority;
    return *this;
}

CapturedErrors* PeripheralErrorCapture::Builder::GetCapturedTo() noexcept
{
    return capturedTo;
}

const CapturedErrors* PeripheralErrorCapture::Builder::GetCapturedTo() const noexcept
{
    return capturedTo;
}

void PeripheralErrorCapture::Builder::SetCapturedTo(CapturedErrors* capturedTo) noexcept
{
    this->capturedTo = capturedTo;
}

unsigned int PeripheralErrorCapture::Builder::GetErrorEventBusId() const noexcept
{
    return errorEventBusId;
}

void PeripheralErrorCapture::Builder::SetErrorEventBusId(unsigned int errorEventBusId) noexcept
{
    this->errorEventBusId = errorEventBusId;
}

int PeripheralErrorCapture::Builder::GetErrorEventPriority() const noexcept
{
    return errorEventPriority;
}

void PeripheralErrorCapture::Builder::SetErrorEventPriority(int errorEventPriority) noexcept
{
    this->errorEventPriority = errorEventPriority;
}

PeripheralErrorCapture* PeripheralErrorCapture::Builder::Build() noexcept
{
    return new PeripheralErrorCapture(capturedTo, errorEventBusId, errorEventPriority);
}



// Implementation of: class DifferentialVerifierErrorCapture
/*
CapturedErrors* capturedTo;

unsigned int    errorEventBusId;
int             errorEventPriority;
*/

DifferentialVerifierErrorCapture::DifferentialVerifierErrorCapture(CapturedErrors* capturedTo, unsigned int errorEventBusId, int errorEventPriority) noexcept
    : capturedTo            (capturedTo)
    , errorEventBusId       (errorEventBusId)
    , errorEventPriority    (errorEventPriority)
{
    RegisterListeners();
}

DifferentialVerifierErrorCapture::~DifferentialVerifierErrorCapture() noexcept
{
    UnregisterListeners();
}

std::string DifferentialVerifierErrorCapture::GetListenerName(const char* listener_name) noexcept
{
    std::ostringstream oss;
    oss << "DifferentialVerifierErrorCapture[";
    oss << std::hex << std::setw(16) << std::setfill('0') << uintptr_t(this);
    oss << "]::" << listener_name;
    return oss.str();
}

CapturedErrors* DifferentialVerifierErrorCapture::GetCapturedTo() noexcept
{
    return capturedTo;
}

const CapturedErrors* DifferentialVerifierErrorCapture::GetCapturedTo() const noexcept
{
    return capturedTo;
}

void DifferentialVerifierErrorCapture::SetCapturedTo(CapturedErrors* capturedTo) noexcept
{
    this->capturedTo = capturedTo;
}

unsigned int DifferentialVerifierErrorCapture::GetErrorEventBusId() const noexcept
{
    return errorEventBusId;
}

int DifferentialVerifierErrorCapture::GetErrorEventPriority() const noexcept
{
    return errorEventPriority;
}



// Implementation of: class DifferentialVerifierErrorCapture::Builder
/*
CapturedErrors* capturedTo;

unsigned int    errorEventBusId;
int             errorEventPriority;
*/

DifferentialVerifierErrorCapture::Builder::Builder() noexcept
    : errorEventBusId       (0)
    , errorEventPriority    (0)
{ }

DifferentialVerifierErrorCapture::Builder& DifferentialVerifierErrorCapture::Builder::CapturedTo(CapturedErrors* capturedTo) noexcept
{
    this->capturedTo = capturedTo;
    return *this;
}

DifferentialVerifierErrorCapture::Builder& DifferentialVerifierErrorCapture::Builder::ErrorEventBusId(unsigned int errorEventBusId) noexcept
{
    this->errorEventBusId = errorEventBusId;
    return *this;
}

DifferentialVerifierErrorCapture::Builder& DifferentialVerifierErrorCapture::Builder::ErrorEventPriority(int errorEventPriority) noexcept
{
    this->errorEventPriority = errorEventPriority;
    return *this;
}

CapturedErrors* DifferentialVerifierErrorCapture::Builder::GetCapturedTo() noexcept
{
    return capturedTo;
}

const CapturedErrors* DifferentialVerifierErrorCapture::Builder::GetCapturedTo() const noexcept
{
    return capturedTo;
}

void DifferentialVerifierErrorCapture::Builder::SetCapturedTo(CapturedErrors* capturedTo) noexcept
{
    this->capturedTo = capturedTo;
}

unsigned int DifferentialVerifierErrorCapture::Builder::GetErrorEventBusId() const noexcept
{
    return errorEventBusId;
}

void DifferentialVerifierErrorCapture::Builder::SetErrorEventBusId(unsigned int errorEventBusId) noexcept
{
    this->errorEventBusId = errorEventBusId;
}

int DifferentialVerifierErrorCapture::Builder::GetErrorEventPriority() const noexcept
{
    return errorEventPriority;
}

void DifferentialVerifierErrorCapture::Builder::SetErrorEventPriority(int errorEventPriority) noexcept
{
    this->errorEventPriority = errorEventPriority;
}

DifferentialVerifierErrorCapture* DifferentialVerifierErrorCapture::Builder::Build() noexcept
{
    return new DifferentialVerifierErrorCapture(capturedTo, errorEventBusId, errorEventPriority);
}




// Implementation of: class MMUErrorCapture
/*
std::string     source;

CapturedErrors* capturedTo;

unsigned int    errorEventBusId;
int             errorEventPriority;
*/

MMUErrorCapture::MMUErrorCapture(const char* source, CapturedErrors* capturedTo, unsigned int errorEventBusId, int errorEventPriority) noexcept
    : source                (source)
    , capturedTo            (capturedTo)
    , errorEventBusId       (errorEventBusId)
    , errorEventPriority    (errorEventPriority)
{
    RegisterListeners();
}

MMUErrorCapture::~MMUErrorCapture() noexcept
{
    UnregisterListeners();
}

std::string MMUErrorCapture::GetListenerName(const char* listener_name) const noexcept
{
    std::ostringstream oss;
    oss << "MMUErrorCapture[";
    oss << std::hex << std::setw(16) << std::setfill('0') << uintptr_t(this);
    oss << "]::" << listener_name;
    return oss.str();
}

std::string MMUErrorCapture::GetSource() const noexcept
{
    return source;
}

CapturedErrors* MMUErrorCapture::GetCapturedTo() noexcept
{
    return capturedTo;
}

const CapturedErrors* MMUErrorCapture::GetCapturedTo() const noexcept
{
    return capturedTo;
}

void MMUErrorCapture::SetCapturedTo(CapturedErrors* capturedTo) noexcept
{
    this->capturedTo = capturedTo;
}

unsigned int MMUErrorCapture::GetErrorEventBusId() const noexcept
{
    return errorEventBusId;
}

int MMUErrorCapture::GetErrorEventPriority() const noexcept
{
    return errorEventPriority;
}



// Implementation of: class MMUErrorCapture::Builder
/*
std::string     source;

CapturedErrors* capturedTo;

unsigned int    errorEventBusId;
int             errorEventPriority;
*/

MMUErrorCapture::Builder::Builder() noexcept
    : source                ()
    , capturedTo            (nullptr)
    , errorEventBusId       (0)
    , errorEventPriority    (0)
{ }

MMUErrorCapture::Builder& MMUErrorCapture::Builder::Source(const char* source) noexcept
{
    this->source = source;
    return *this;
}

MMUErrorCapture::Builder& MMUErrorCapture::Builder::CapturedTo(CapturedErrors* capturedTo) noexcept
{
    this->capturedTo = capturedTo;
    return *this;
}

MMUErrorCapture::Builder& MMUErrorCapture::Builder::ErrorEventBusId(unsigned int errorEventBusId) noexcept
{
    this->errorEventBusId = errorEventBusId;
    return *this;
}

MMUErrorCapture::Builder& MMUErrorCapture::Builder::ErrorEventPriority(int errorEventPriority) noexcept
{
    this->errorEventPriority = errorEventPriority;
    return *this;
}

std::string MMUErrorCapture::Builder::GetSource() const noexcept
{
    return source;
}

void MMUErrorCapture::Builder::SetSource(const char* source) noexcept
{
    this->source = source;
}

CapturedErrors* MMUErrorCapture::Builder::GetCapturedTo() noexcept
{
    return capturedTo;
}

const CapturedErrors* MMUErrorCapture::Builder::GetCapturedTo() const noexcept
{
    return capturedTo;
}

void MMUErrorCapture::Builder::SetCapturedTo(CapturedErrors* capturedTo) noexcept
{
    this->capturedTo = capturedTo;
}

unsigned int MMUErrorCapture::Builder::GetErrorEventBusId() const noexcept
{
    return errorEventBusId;
}

void MMUErrorCapture::Builder::SetErrorEventBusId(unsigned int errorEventBusId) noexcept
{
    this->errorEventBusId = errorEventBusId;
}

int MMUErrorCapture::Builder::GetErrorEventPriority() const noexcept
{
    return errorEventPriority;
}

void MMUErrorCapture::Builder::SetErrorEventPriority(int errorEventPriority) noexcept
{
    this->errorEventPriority = errorEventPriority;
}

MMUErrorCapture* MMUErrorCapture::Builder::Build() noexcept
{
    return new MMUErrorCapture(source.c_str(), capturedTo, errorEventBusId, errorEventPriority);
}




// Implementation of: class AXIBridgeErrorCapture
/*
std::string         source;

CapturedErrors*     capturedTo;

unsigned int        errorEventBusId;
int                 errorEventPriority;

unsigned int        traceDepth;
std::deque<Trace>   traces;
*/

AXIBridgeErrorCapture::AXIBridgeErrorCapture(const char* source, CapturedErrors* capturedTo, unsigned int errorEventBusId, int errorEventPriority, unsigned int traceDepth) noexcept
    : source                (source)
    , capturedTo            (capturedTo)
    , errorEventBusId       (errorEventBusId)
    , errorEventPriority    (errorEventPriority)
    , traceDepth            (traceDepth)
    , traces                ()
{
    RegisterListeners();
}

AXIBridgeErrorCapture::~AXIBridgeErrorCapture() noexcept
{
    UnregisterListeners();
}

std::string AXIBridgeErrorCapture::GetListenerName(const char* listener_name) const noexcept
{
    std::ostringstream oss;
    oss << "AXIBridgeErrorCapture[";
    oss << std::hex << std::setw(16) << std::setfill('0') << uintptr_t(this);
    oss << "]::" << listener_name;
    return oss.str();
}

std::string AXIBridgeErrorCapture::GetSource() const noexcept
{
    return source;
}

CapturedErrors* AXIBridgeErrorCapture::GetCapturedTo() noexcept
{
    return capturedTo;
}

const CapturedErrors* AXIBridgeErrorCapture::GetCapturedTo() const noexcept
{
    return capturedTo;
}

void AXIBridgeErrorCapture::SetCapturedTo(CapturedErrors* capturedTo) noexcept
{
    this->capturedTo = capturedTo;
}

unsigned int AXIBridgeErrorCapture::GetErrorEventBusId() const noexcept
{
    return errorEventBusId;
}

int AXIBridgeErrorCapture::GetErrorEventPriority() const noexcept
{
    return errorEventPriority;
}



// Implementation of: class AXIBridgeErrorCapture::Builder
/*
std::string     source;

CapturedErrors* capturedTo;

unsigned int    errorEventBusId;
int             errorEventPriority;

unsigned int    traceDepth;
*/

AXIBridgeErrorCapture::Builder::Builder() noexcept
    : source                ()
    , capturedTo            (nullptr)
    , errorEventBusId       (0)
    , errorEventPriority    (0)
    , traceDepth            (32)
{ }

AXIBridgeErrorCapture::Builder& AXIBridgeErrorCapture::Builder::Source(const char* source) noexcept
{
    this->source = source;
    return *this;
}

AXIBridgeErrorCapture::Builder& AXIBridgeErrorCapture::Builder::CapturedTo(CapturedErrors* capturedTo) noexcept
{
    this->capturedTo = capturedTo;
    return *this;
}

AXIBridgeErrorCapture::Builder& AXIBridgeErrorCapture::Builder::ErrorEventBusId(unsigned int errorEventBusId) noexcept
{
    this->errorEventBusId = errorEventBusId;
    return *this;
}

AXIBridgeErrorCapture::Builder& AXIBridgeErrorCapture::Builder::ErrorEventPriority(int errorEventPriority) noexcept
{
    this->errorEventPriority = errorEventPriority;
    return *this;
}

AXIBridgeErrorCapture::Builder& AXIBridgeErrorCapture::Builder::TraceDepth(unsigned int traceDepth) noexcept
{
    this->traceDepth = traceDepth;
    return *this;
}

std::string AXIBridgeErrorCapture::Builder::GetSource() const noexcept
{
    return source;
}

void AXIBridgeErrorCapture::Builder::SetSource(const char* source) noexcept
{
    this->source = source;
}

CapturedErrors* AXIBridgeErrorCapture::Builder::GetCapturedTo() noexcept
{
    return capturedTo;
}

const CapturedErrors* AXIBridgeErrorCapture::Builder::GetCapturedTo() const noexcept
{
    return capturedTo;
}

void AXIBridgeErrorCapture::Builder::SetCapturedTo(CapturedErrors* capturedTo) noexcept
{
    this->capturedTo = capturedTo;
}

unsigned int AXIBridgeErrorCapture::Builder::GetErrorEventBusId() const noexcept
{
    return errorEventBusId;
}

void AXIBridgeErrorCapture::Builder::SetErrorEventBusId(unsigned int errorEventBusId) noexcept
{
    this->errorEventBusId = errorEventBusId;
}

int AXIBridgeErrorCapture::Builder::GetErrorEventPriority() const noexcept
{
    return errorEventPriority;
}

void AXIBridgeErrorCapture::Builder::SetErrorEventPriority(int errorEventPriority) noexcept
{
    this->errorEventPriority = errorEventPriority;
}

unsigned int AXIBridgeErrorCapture::Builder::GetTraceDepth() const noexcept
{
    return traceDepth;
}

void AXIBridgeErrorCapture::Builder::SetTraceDepth(unsigned int traceDepth) noexcept
{
    this->traceDepth = traceDepth;
}

AXIBridgeErrorCapture* AXIBridgeErrorCapture::Builder::Build() noexcept
{
    return new AXIBridgeErrorCapture(source.c_str(), capturedTo, errorEventBusId, errorEventPriority, traceDepth);
}
