#pragma once
//
// BullsEye Utility
//
//

#include <cstring>
#include <string>


namespace BullsEye {

    inline char* NewStringAndCopy(const char* src, size_t length) noexcept
    {
        char* newString = new char[length + 1];
        std::memcpy(newString, src, sizeof(char) * (length + 1));
        return newString;
    }

    inline char* NewStringAndCopy(const char* src) noexcept
    {
        return NewStringAndCopy(src, std::strlen(src));
    }

    inline char* NewStringAndCopy(std::string src) noexcept
    {
        return NewStringAndCopy(src.c_str(), src.length());
    }
}
