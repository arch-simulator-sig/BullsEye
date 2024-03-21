#include "gravity_logging.hpp"


// Implementation of: class Log
namespace Gravity {
    /*
    std::string                             source;
    std::string                             message;
    std::chrono::system_clock::time_point   timestamp;
    */

    Log::Log() noexcept
        : source        ("")
        , message       ("")
        , timestamp     (std::chrono::system_clock::now())
    { }

    Log::Log(const std::string& source) noexcept
        : source        (source)
        , message       ("")
        , timestamp     (std::chrono::system_clock::now())
    { }

    Log::Log(const std::string& source, const std::string& message) noexcept
        : source        (source)
        , message       (message)
        , timestamp     (std::chrono::system_clock::now())
    { }

    const std::string& Log::GetSource() const noexcept
    {
        return this->source;
    }

    void Log::SetSource(const std::string& source) noexcept
    {
        this->source = source;
    }

    const std::string& Log::GetMessage() const noexcept
    {
        return this->message;
    }

    void Log::SetMessage(const std::string& message) noexcept
    {
        this->message = message;
    }

    const std::chrono::system_clock::time_point& Log::GetTimestamp() const noexcept
    {
        return this->timestamp;
    }

    void Log::SetTimestamp(const std::chrono::system_clock::time_point& timestamp) noexcept
    {
        this->timestamp = timestamp;
    }
}


// Implementation of: class LogInfo
namespace Gravity {

    LogInfo::LogInfo() noexcept
        : Log   ()
    { }

    LogInfo::LogInfo(const std::string& source) noexcept
        : Log   (source)
    { }

    LogInfo::LogInfo(const std::string& source, const std::string& message) noexcept
        : Log   (source, message)
    { }
}


// Implementation of: class LogWarn
namespace Gravity {

    LogWarn::LogWarn() noexcept
        : Log   ()
    { }

    LogWarn::LogWarn(const std::string& source) noexcept
        : Log   (source)
    { }

    LogWarn::LogWarn(const std::string& source, const std::string& message) noexcept
        : Log   (source, message)
    { }
}


// Implementation of: class LogError
namespace Gravity {

    LogError::LogError() noexcept
        : Log   ()
    { }

    LogError::LogError(const std::string& source) noexcept
        : Log   (source)
    { }

    LogError::LogError(const std::string& source, const std::string& message) noexcept
        : Log   (source, message)
    { }
}
