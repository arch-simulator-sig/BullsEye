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
    oss << "ErrorCapture[";
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
