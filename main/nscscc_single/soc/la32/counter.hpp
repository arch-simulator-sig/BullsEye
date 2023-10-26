#pragma once
//
//

#ifndef __HEADER_BULLSEYE_NSCSCC2023_LA32_SOC__COUNTER
#define __HEADER_BULLSEYE_NSCSCC2023_LA32_SOC__COUNTER

#include <cstdint>


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


#endif
