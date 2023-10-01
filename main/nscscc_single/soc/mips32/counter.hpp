#pragma once
//
//

#include "isa/mips32/mips32.hpp"


namespace BullsEye::NSCSCCSingle {

    // Clock Counter (Performance Counter)
    class ClockCounter {
    private:
        uint64_t    counter;

    public:
        ClockCounter() noexcept;
        ~ClockCounter() noexcept;

        void        SetCounter(uint64_t val = 0) noexcept;
        void        ResetCounter() noexcept;

        uint64_t    GetCounter() const noexcept;
        uint32_t    GetCounterHi() const noexcept;
        uint32_t    GetCounterLo() const noexcept;

        void        IncreaseCounter() noexcept;
        void        DecreaseCounter() noexcept;

        operator    uint64_t() const noexcept;

        uint64_t    operator++() noexcept;
        uint64_t    operator--() noexcept;

        uint64_t    operator++(int) noexcept;
        uint64_t    operator--(int) noexcept;
    };


    // Performance Counter Container
    class PerfCounterContainer {
    private:
        ClockCounter*   counter;

    public:
        // Not implemented currently (unused)
    };
}


// Implementation of: class ClockCounter
namespace BullsEye::NSCSCCSingle {
    //
    // uint64_t    counter;
    //

    ClockCounter::ClockCounter() noexcept
        : counter   (0)
    { }

    ClockCounter::~ClockCounter() noexcept
    { }

    inline void ClockCounter::SetCounter(uint64_t val) noexcept
    {
        counter = val;
    }

    inline void ClockCounter::ResetCounter() noexcept
    {
        counter = 0;
    }

    inline uint64_t ClockCounter::GetCounter() const noexcept
    {
        return counter;
    }

    inline uint32_t ClockCounter::GetCounterHi() const noexcept
    {
        return static_cast<uint32_t>(counter >> 32);
    }

    inline uint32_t ClockCounter::GetCounterLo() const noexcept
    {
        return static_cast<uint32_t>(counter);
    }

    inline void ClockCounter::IncreaseCounter() noexcept
    {
        counter++;
    }

    inline void ClockCounter::DecreaseCounter() noexcept
    {
        counter--;
    }

    inline ClockCounter::operator uint64_t() const noexcept
    {
        return counter;
    }

    inline uint64_t ClockCounter::operator++() noexcept
    {
        return ++counter;
    }

    inline uint64_t ClockCounter::operator--() noexcept
    {
        return --counter;
    }

    inline uint64_t ClockCounter::operator++(int) noexcept
    {
        return counter++;
    }

    inline uint64_t ClockCounter::operator--(int) noexcept
    {
        return counter--;
    }
}
