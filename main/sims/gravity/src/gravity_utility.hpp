#pragma once

#ifndef __BULLSEYE_SIMS_GRAVITY__UTILITY
#define __BULLSEYE_SIMS_GRAVITY__UTILITY

#include <sstream>


namespace Gravity {

    /*
    * String Appender (builder pattern helper for std::ostringstream)
    * ----------------------------------------------------------------
    * Usage:
    *   StringAppender appender("Hello");
    *   appender.Append(", ").Append("World!").Append(123).ToString();
    * or
    *   StringAppender().Append("Hello, ").Append("World!").Append(123).ToString();
    *   StringAppender("Hello, ").Append("World!").Append(123).ToString();
    */
    class StringAppender {
    private:
        std::ostringstream  oss;

    public:
        inline StringAppender() noexcept {};
        inline ~StringAppender() noexcept {};

        template<class T>
        inline StringAppender(const T& value) noexcept 
        { oss << value; }

        template<class T>
        inline StringAppender& Append() noexcept 
        { return *this; }

        template<class T>
        inline StringAppender& Append(const T& value) noexcept 
        { oss << value; return *this; }

        template<class T>
        inline StringAppender& operator<<(const T& value) noexcept 
        { return Append(value); }

        inline std::string ToString() const noexcept 
        { return oss.str(); }
    };
}


#endif // __BULLSEYE_SIMS_GRAVITY__UTILITY
