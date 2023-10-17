#include "counter.hpp"
//
//


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

    void ClockCounter::SetCounter(uint64_t val) noexcept
    {
        counter = val;
    }

    void ClockCounter::ResetCounter() noexcept
    {
        counter = 0;
    }

    uint64_t ClockCounter::GetCounter() const noexcept
    {
        return counter;
    }

    uint32_t ClockCounter::GetCounterHi() const noexcept
    {
        return static_cast<uint32_t>(counter >> 32);
    }

    uint32_t ClockCounter::GetCounterLo() const noexcept
    {
        return static_cast<uint32_t>(counter);
    }

    void ClockCounter::IncreaseCounter() noexcept
    {
        counter++;
    }

    void ClockCounter::DecreaseCounter() noexcept
    {
        counter--;
    }

    ClockCounter::operator uint64_t() const noexcept
    {
        return counter;
    }

    uint64_t ClockCounter::operator++() noexcept
    {
        return ++counter;
    }

    uint64_t ClockCounter::operator--() noexcept
    {
        return --counter;
    }

    uint64_t ClockCounter::operator++(int) noexcept
    {
        return counter++;
    }

    uint64_t ClockCounter::operator--(int) noexcept
    {
        return counter--;
    }
}
