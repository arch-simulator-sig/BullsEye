#pragma once
//
//

#include <algorithm>

#include "memory.hpp"
#include "serial.hpp"
#include "counter.hpp"


using namespace Jasse;

namespace BullsEye::NSCSCCSingle {

    class NSCSCC2022MMU : public MIPS32MemoryInterface {
    private:
        BaseRAM*            baseRAM;
        ExtRAM*             extRAM;

        SerialInterface*    serial;

        ClockCounter*       clk_counter;

    private:
        MIPS32MOPOutcome            _MMIO_ReadSerial(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept;
        MIPS32MOPOutcome            _MMIO_WriteSerial(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept;

        MIPS32MOPOutcome            _MMIO_ReadClockCounter(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept;
        MIPS32MOPOutcome            _MMIO_WriteClockCounter(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept;

    public:
        NSCSCC2022MMU(BaseRAM*          baseRAM,
                      ExtRAM*           extRAM, 
                      SerialInterface*  serial, 
                      ClockCounter*     clk_counter) noexcept;

        ~NSCSCC2022MMU() noexcept;

        virtual MIPS32MOPOutcome    ReadInsn(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept override;
        virtual MIPS32MOPOutcome    ReadData(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept override;

        virtual MIPS32MOPOutcome    WriteInsn(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept override;
        virtual MIPS32MOPOutcome    WriteData(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept override;

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


// Implementation of: class NSCSCC2022MMU
namespace BullsEye::NSCSCCSingle {
    //
    // BaseRAM*            baseRAM;
    // ExtRAM*             extRAM;
    //
    // SerialInterface*    serial;
    //
    // ClockCounter*       clk_counter;
    //

    NSCSCC2022MMU::NSCSCC2022MMU(BaseRAM*           baseRAM, 
                                 ExtRAM*            extRAM, 
                                 SerialInterface*   serial, 
                                 ClockCounter*      clk_counter) noexcept
        : baseRAM       (baseRAM)
        , extRAM        (extRAM)
        , serial        (serial)
        , clk_counter   (clk_counter)
    { }

    NSCSCC2022MMU::~NSCSCC2022MMU() noexcept
    { }

    inline MIPS32MOPOutcome NSCSCC2022MMU::_MMIO_ReadSerial(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept
    {
        if (!serial)
            return { MOP_ACCESS_FAULT, ENOSYS };

        if (width != MOPW_BYTE)
            return { MOP_ACCESS_FAULT, ENOSYS };

        if (address == 0xBFD003F8)
            dst->data8 = serial->Read();
        else if (address == 0xBFD003FC)
            dst->data8 = ((serial->IsWriteAvailable() ? 0x01 : 0x00) | (serial->IsReadAvailable() ? 0x02 : 0x00));
        else
            return { MOP_ACCESS_FAULT, EFAULT };

        return { MOP_SUCCESS };
    }

    inline MIPS32MOPOutcome NSCSCC2022MMU::_MMIO_WriteSerial(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept
    {
        if (!serial)
            return { MOP_ACCESS_FAULT, ENOSYS };

        if (width != MOPW_BYTE)
            return { MOP_ACCESS_FAULT, ENOSYS };

        if (address == 0xBFD003F8)
            serial->Write(src.data8);
        else
            return { MOP_ACCESS_FAULT, EFAULT };
        
        return { MOP_SUCCESS };
    }

    inline MIPS32MOPOutcome NSCSCC2022MMU::_MMIO_ReadClockCounter(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept
    {
        if (!clk_counter)
            return { MOP_ACCESS_FAULT, ENOSYS };

        if (width != MOPW_WORD)
            return { MOP_ACCESS_FAULT, ENOSYS };

        if (address == 0xBFD00400)
            dst->data32 = clk_counter->GetCounterLo();
        else if (address == 0xBFD00404)
            dst->data32 = clk_counter->GetCounterHi();
        else
            return { MOP_ACCESS_FAULT, EFAULT };

        return { MOP_SUCCESS };
    }

    inline MIPS32MOPOutcome NSCSCC2022MMU::_MMIO_WriteClockCounter(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept
    {
        return { MOP_ACCESS_FAULT, ENOSYS };
    }

    MIPS32MOPOutcome NSCSCC2022MMU::ReadInsn(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept
    {
        addr_t phyaddress = address & 0x7FFFFFFF;

        if (phyaddress >= 0x00000000 && phyaddress <= 0x003FFFFF)
            return baseRAM->ReadInsn(phyaddress, width, dst);
        else if (phyaddress >= 0x00400000 && phyaddress <= 0x007FFFFF)
            return extRAM->ReadInsn(phyaddress - 0x00400000, width, dst);
        else
            return { MOP_ACCESS_FAULT, EFAULT };
    }

    MIPS32MOPOutcome NSCSCC2022MMU::ReadData(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept
    {
        addr_t phyaddress = address & 0x7FFFFFFF;

        auto procedure = [&]() -> MIPS32MOPOutcome 
        {
            if (phyaddress >= 0x00000000 && phyaddress <= 0x003FFFFF)
                return baseRAM->ReadData(phyaddress, width, dst);
            else if (phyaddress >= 0x00400000 && phyaddress <= 0x007FFFFF)
                return extRAM->ReadData(phyaddress - 0x00400000, width, dst);
            else if (address == 0xBFD003F8 || address == 0xBFD003FC)
                return _MMIO_ReadSerial(address, width, dst);
            else if (address == 0xBFD00400 || address == 0xBFD00404)
                return _MMIO_ReadClockCounter(address, width, dst);
            else
                return { MOP_ACCESS_FAULT, EFAULT };
        };

        MIPS32MOPOutcome outcome = procedure();

        if (outcome.status != MOP_SUCCESS)
            printf("Failed ReadData: 0x%08x %d\n", address, width.length);

        return outcome;
    }

    MIPS32MOPOutcome NSCSCC2022MMU::WriteInsn(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept
    {
        addr_t phyaddress = address & 0x7FFFFFFF;

        if (phyaddress >= 0x00000000 && phyaddress <= 0x003FFFFF)
            return baseRAM->WriteInsn(phyaddress, width, src);
        else if (phyaddress >= 0x00400000 && phyaddress <= 0x007FFFFF)
            return extRAM->WriteInsn(phyaddress - 0x00400000, width, src);
        else
            return { MOP_ACCESS_FAULT, EFAULT };
    }

    MIPS32MOPOutcome NSCSCC2022MMU::WriteData(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept
    {

        addr_t phyaddress = address & 0x7FFFFFFF;

        auto procedure = [&]() -> MIPS32MOPOutcome 
        {
            if (phyaddress >= 0x00000000 && phyaddress <= 0x003FFFFF)
                return baseRAM->WriteData(phyaddress, width, src);
            else if (phyaddress >= 0x00400000 && phyaddress <= 0x007FFFFF)
                return extRAM->WriteData(phyaddress - 0x00400000, width, src);
            else if (address == 0xBFD003F8 || address == 0xBFD003FC)
                return _MMIO_WriteSerial(address, width, src);
            else if (address == 0xBFD00400 || address == 0xBFD00404)
                return _MMIO_WriteClockCounter(address, width, src);
            else
                return { MOP_ACCESS_FAULT, EFAULT };
        };

        MIPS32MOPOutcome outcome = procedure();

        if (outcome.status != MOP_SUCCESS)
            printf("Failed WriteData: 0x%08x %d\n", address, width.length);

        return outcome;
    }

    inline BaseRAM* NSCSCC2022MMU::GetBaseRAM() noexcept
    {
        return baseRAM;
    }

    inline const BaseRAM* NSCSCC2022MMU::GetBaseRAM() const noexcept
    {
        return baseRAM;
    }

    inline BaseRAM* NSCSCC2022MMU::SwapBaseRAM(BaseRAM* baseRAM) noexcept
    {
        std::swap(this->baseRAM, baseRAM);
        return baseRAM;
    }

    inline ExtRAM* NSCSCC2022MMU::GetExtRAM() noexcept
    {
        return extRAM;
    }

    inline const ExtRAM* NSCSCC2022MMU::GetExtRAM() const noexcept
    {
        return extRAM;
    }

    inline ExtRAM* NSCSCC2022MMU::SwapExtRAM(ExtRAM* extRAM) noexcept
    {
        std::swap(this->extRAM, extRAM);
        return extRAM;
    }

    inline SerialInterface* NSCSCC2022MMU::GetSerial() noexcept
    {
        return serial;
    }

    inline const SerialInterface* NSCSCC2022MMU::GetSerial() const noexcept
    {
        return serial;
    }

    inline SerialInterface* NSCSCC2022MMU::SwapSerial(SerialInterface* serial) noexcept
    {
        std::swap(this->serial, serial);
        return serial;
    }

    inline ClockCounter* NSCSCC2022MMU::GetClockCounter() noexcept
    {
        return clk_counter;
    }

    inline const ClockCounter* NSCSCC2022MMU::GetClockCounter() const noexcept
    {
        return clk_counter;
    }

    inline ClockCounter* NSCSCC2022MMU::SwapClockCounter(ClockCounter* clk_counter) noexcept
    {
        std::swap(this->clk_counter, clk_counter);
        return clk_counter;
    }
}
