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
