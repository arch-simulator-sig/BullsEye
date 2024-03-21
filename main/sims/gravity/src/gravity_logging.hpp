#pragma once

#ifndef __BULLSEYE_SIMS_GRAVITY__LOGGING
#define __BULLSEYE_SIMS_GRAVITY__LOGGING

#include <chrono>
#include <string>

#include "gravity_configmacros.hpp"
#include "gravity_eventbus.hpp"


namespace Gravity {

    /*
    Base class for all logging events.
    */
    class Log {
    protected:
        std::string                             source;
        std::string                             message;
        std::chrono::system_clock::time_point   timestamp;

    public:
        Log() noexcept;
        Log(const std::string& source) noexcept;
        Log(const std::string& source, const std::string& message) noexcept;

        const std::string&  GetSource() const noexcept;
        void                SetSource(const std::string& source) noexcept;

        const std::string&  GetMessage() const noexcept;
        void                SetMessage(const std::string& message) noexcept;

        const std::chrono::system_clock::time_point&    GetTimestamp() const noexcept;
        void                SetTimestamp(const std::chrono::system_clock::time_point& timestamp) noexcept;
    };


    /* 
    Basic Info Logging Event
    */
    class LogInfo : public Log, public Event<LogInfo> {
    public:
        LogInfo() noexcept;
        LogInfo(const std::string& source) noexcept;
        LogInfo(const std::string& source, const std::string& message) noexcept;
    };

    /*
    Warning Logging Event
    */
    class LogWarn : public Log, public Event<LogWarn> {
    public:
        LogWarn() noexcept;
        LogWarn(const std::string& source) noexcept;
        LogWarn(const std::string& source, const std::string& message) noexcept;
    };

    /*
    Error Logging Event
    */
    class LogError : public Log, public Event<LogError> {
    public:
        LogError() noexcept;
        LogError(const std::string& source) noexcept;
        LogError(const std::string& source, const std::string& message) noexcept;
    };
}


#endif // __BULLSEYE_SIMS_GRAVITY__LOGGING
