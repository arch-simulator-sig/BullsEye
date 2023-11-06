#pragma once
//
//

#ifndef __HEADER_BULLSEYE_NSCSCC2023_LA32_SOC__MMU
#define __HEADER_BULLSEYE_NSCSCC2023_LA32_SOC__MMU


#include "memory.hpp"
#include "serial.hpp"
#include "counter.hpp"


namespace BullsEye::NSCSCCSingle {

    class NSCSCC2023MMU : public LA32MemoryInterface {
    private:
        unsigned int        eventBusId;

        BaseRAM*            baseRAM;
        ExtRAM*             extRAM;

        SerialInterface*    serial;

        ClockCounter*       clk_counter;

    private:
        //
        LA32MOPOutcome              _BaseRAM_Read(LA32MOPPath path, addr_t phyaddress, LA32MOPWidth width, memdata_t* dst) noexcept;
        LA32MOPOutcome              _BaseRAM_Write(LA32MOPPath path, addr_t phyaddress, LA32MOPWidth width, memdata_t src) noexcept;

        LA32MOPOutcome              _BaseRAM_ReadInsn(addr_t phyaddress, LA32MOPWidth width, memdata_t* dst) noexcept;
        LA32MOPOutcome              _BaseRAM_ReadData(addr_t phyaddress, LA32MOPWidth width, memdata_t* dst) noexcept;

        LA32MOPOutcome              _BaseRAM_WriteInsn(addr_t phyaddress, LA32MOPWidth width, memdata_t src) noexcept;
        LA32MOPOutcome              _BaseRAM_WriteData(addr_t phyaddress, LA32MOPWidth width, memdata_t src) noexcept;

        //
        LA32MOPOutcome              _ExtRAM_Read(LA32MOPPath path, addr_t phyaddress, LA32MOPWidth width, memdata_t* dst) noexcept;
        LA32MOPOutcome              _ExtRAM_Write(LA32MOPPath path, addr_t phyaddress, LA32MOPWidth width, memdata_t src) noexcept;

        LA32MOPOutcome              _ExtRAM_ReadInsn(addr_t phyaddress, LA32MOPWidth width, memdata_t* dst) noexcept;
        LA32MOPOutcome              _ExtRAM_ReadData(addr_t phyaddress, LA32MOPWidth width, memdata_t* dst) noexcept;

        LA32MOPOutcome              _ExtRAM_WriteInsn(addr_t phyaddress, LA32MOPWidth width, memdata_t src) noexcept;
        LA32MOPOutcome              _ExtRAM_WriteData(addr_t phyaddress, LA32MOPWidth width, memdata_t src) noexcept;

        //
        LA32MOPOutcome              _MMIO_ReadSerial(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept;
        LA32MOPOutcome              _MMIO_WriteSerial(addr_t address, LA32MOPWidth width, memdata_t src) noexcept;

        //
        LA32MOPOutcome              _MMIO_ReadClockCounter(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept;
        LA32MOPOutcome              _MMIO_WriteClockCounter(addr_t address, LA32MOPWidth width, memdata_t src) noexcept;

    public:
        static bool                 IsSerial(addr_t address) noexcept;

    public:
        NSCSCC2023MMU(unsigned int      eventBusId,
                      BaseRAM*          baseRAM,
                      ExtRAM*           extRAM, 
                      SerialInterface*  serial, 
                      ClockCounter*     clk_counter) noexcept;

        ~NSCSCC2023MMU() noexcept;

        virtual LA32MOPOutcome      ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept override;
        virtual LA32MOPOutcome      ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept override;

        virtual LA32MOPOutcome      WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept override;
        virtual LA32MOPOutcome      WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept override;

        unsigned int                GetEventBusId() const noexcept;

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
