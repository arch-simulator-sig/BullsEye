#pragma once
//
//

#ifndef __HEADER_BULLSEYE_NSCSCC2023_LA32_SOC__MMU
#define __HEADER_BULLSEYE_NSCSCC2023_LA32_SOC__MMU


#include <algorithm>

#include "memory.hpp"
#include "serial.hpp"
#include "counter.hpp"


using namespace Jasse;

namespace BullsEye::NSCSCCSingle {

    class NSCSCC2023MMU : public LA32MemoryInterface {
    private:
        BaseRAM*            baseRAM;
        ExtRAM*             extRAM;

        SerialInterface*    serial;

        ClockCounter*       clk_counter;

    private:
        LA32MOPOutcome            _MMIO_ReadSerial(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept;
        LA32MOPOutcome            _MMIO_WriteSerial(addr_t address, LA32MOPWidth width, memdata_t src) noexcept;

        LA32MOPOutcome            _MMIO_ReadClockCounter(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept;
        LA32MOPOutcome            _MMIO_WriteClockCounter(addr_t address, LA32MOPWidth width, memdata_t src) noexcept;

    public:
        NSCSCC2023MMU(BaseRAM*          baseRAM,
                      ExtRAM*           extRAM, 
                      SerialInterface*  serial, 
                      ClockCounter*     clk_counter) noexcept;

        ~NSCSCC2023MMU() noexcept;

        virtual LA32MOPOutcome      ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept override;
        virtual LA32MOPOutcome      ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept override;

        virtual LA32MOPOutcome      WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept override;
        virtual LA32MOPOutcome      WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept override;

        BaseRAM*                    GetBaseRAM() noexcept;
        const BaseRAM*              GetBaseRAM() const noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        BaseRAM*                    SwapBaseRAM(BaseRAM* baseRAM) noexcept;

        ExtRAM*                     GetExtRAM() noexcept;
        const ExtRAM*               GetExtRAM() const noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        ExtRAM*                     SwapExtRAM(ExtRAM* extRAM) noexcept;

        SerialInterface*            GetSerial() noexcept;
        const SerialInterface*      GetSerial() const noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        SerialInterface*            SwapSerial(SerialInterface* serial) noexcept;

        ClockCounter*               GetClockCounter() noexcept;
        const ClockCounter*         GetClockCounter() const noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        ClockCounter*               SwapClockCounter(ClockCounter* clk_counter) noexcept;
    };
}


#endif
