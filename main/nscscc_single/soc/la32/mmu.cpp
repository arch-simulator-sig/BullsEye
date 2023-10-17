#include "mmu.hpp"
//
//


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

    NSCSCC2023MMU::NSCSCC2023MMU(BaseRAM*           baseRAM, 
                                 ExtRAM*            extRAM, 
                                 SerialInterface*   serial, 
                                 ClockCounter*      clk_counter) noexcept
        : baseRAM       (baseRAM)
        , extRAM        (extRAM)
        , serial        (serial)
        , clk_counter   (clk_counter)
    { }

    NSCSCC2023MMU::~NSCSCC2023MMU() noexcept
    { }

    LA32MOPOutcome NSCSCC2023MMU::_MMIO_ReadSerial(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        if (!serial)
            return { LA32MOPStatus::MOP_ACCESS_FAULT, ENOSYS };

        if (width != MOPW_BYTE)
            return { LA32MOPStatus::MOP_ACCESS_FAULT, ENOSYS };

        if (address == 0xBFD003F8)
            dst->data8 = serial->Read();
        else if (address == 0xBFD003FC)
            dst->data8 = ((serial->IsWriteAvailable() ? 0x01 : 0x00) | (serial->IsReadAvailable() ? 0x02 : 0x00));
        else
            return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };

        return { LA32MOPStatus::MOP_SUCCESS };
    }

    LA32MOPOutcome NSCSCC2023MMU::_MMIO_WriteSerial(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        if (!serial)
            return { LA32MOPStatus::MOP_ACCESS_FAULT, ENOSYS };

        if (width != MOPW_BYTE)
            return { LA32MOPStatus::MOP_ACCESS_FAULT, ENOSYS };

        if (address == 0xBFD003F8)
            serial->Write(src.data8);
        else
            return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };
        
        return { LA32MOPStatus::MOP_SUCCESS };
    }

    LA32MOPOutcome NSCSCC2023MMU::_MMIO_ReadClockCounter(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        if (!clk_counter)
            return { LA32MOPStatus::MOP_ACCESS_FAULT, ENOSYS };

        if (width != MOPW_WORD)
            return { LA32MOPStatus::MOP_ACCESS_FAULT, ENOSYS };

        if (address == 0xBFD00400)
            dst->data32 = clk_counter->GetCounterLo();
        else if (address == 0xBFD00404)
            dst->data32 = clk_counter->GetCounterHi();
        else
            return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };

        return { LA32MOPStatus::MOP_SUCCESS };
    }

    LA32MOPOutcome NSCSCC2023MMU::_MMIO_WriteClockCounter(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        return { LA32MOPStatus::MOP_ACCESS_FAULT, ENOSYS };
    }

    LA32MOPOutcome NSCSCC2023MMU::ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        addr_t phyaddress = address & 0x7FFFFFFF;

        if (phyaddress >= 0x00000000 && phyaddress <= 0x003FFFFF)
            return baseRAM->ReadInsn(phyaddress, width, dst);
        else if (phyaddress >= 0x00400000 && phyaddress <= 0x007FFFFF)
            return extRAM->ReadInsn(phyaddress - 0x00400000, width, dst);
        else
            return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };
    }

    LA32MOPOutcome NSCSCC2023MMU::ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        addr_t phyaddress = address & 0x7FFFFFFF;

        auto procedure = [&]() -> LA32MOPOutcome 
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
                return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };
        };

        LA32MOPOutcome outcome = procedure();

        if (outcome.status != LA32MOPStatus::MOP_SUCCESS)
            printf("Failed ReadData: 0x%08x %d\n", address, width.length);

        return outcome;
    }

    LA32MOPOutcome NSCSCC2023MMU::WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        addr_t phyaddress = address & 0x7FFFFFFF;

        if (phyaddress >= 0x00000000 && phyaddress <= 0x003FFFFF)
            return baseRAM->WriteInsn(phyaddress, width, src);
        else if (phyaddress >= 0x00400000 && phyaddress <= 0x007FFFFF)
            return extRAM->WriteInsn(phyaddress - 0x00400000, width, src);
        else
            return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };
    }

    LA32MOPOutcome NSCSCC2023MMU::WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {

        addr_t phyaddress = address & 0x7FFFFFFF;

        auto procedure = [&]() -> LA32MOPOutcome 
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
                return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };
        };

        LA32MOPOutcome outcome = procedure();

        if (outcome.status != LA32MOPStatus::MOP_SUCCESS)
            printf("Failed WriteData: 0x%08x %d\n", address, width.length);

        return outcome;
    }

    BaseRAM* NSCSCC2023MMU::GetBaseRAM() noexcept
    {
        return baseRAM;
    }

    const BaseRAM* NSCSCC2023MMU::GetBaseRAM() const noexcept
    {
        return baseRAM;
    }

    BaseRAM* NSCSCC2023MMU::SwapBaseRAM(BaseRAM* baseRAM) noexcept
    {
        std::swap(this->baseRAM, baseRAM);
        return baseRAM;
    }

    ExtRAM* NSCSCC2023MMU::GetExtRAM() noexcept
    {
        return extRAM;
    }

    const ExtRAM* NSCSCC2023MMU::GetExtRAM() const noexcept
    {
        return extRAM;
    }

    ExtRAM* NSCSCC2023MMU::SwapExtRAM(ExtRAM* extRAM) noexcept
    {
        std::swap(this->extRAM, extRAM);
        return extRAM;
    }

    SerialInterface* NSCSCC2023MMU::GetSerial() noexcept
    {
        return serial;
    }

    const SerialInterface* NSCSCC2023MMU::GetSerial() const noexcept
    {
        return serial;
    }

    SerialInterface* NSCSCC2023MMU::SwapSerial(SerialInterface* serial) noexcept
    {
        std::swap(this->serial, serial);
        return serial;
    }

    ClockCounter* NSCSCC2023MMU::GetClockCounter() noexcept
    {
        return clk_counter;
    }

    const ClockCounter* NSCSCC2023MMU::GetClockCounter() const noexcept
    {
        return clk_counter;
    }

    ClockCounter* NSCSCC2023MMU::SwapClockCounter(ClockCounter* clk_counter) noexcept
    {
        std::swap(this->clk_counter, clk_counter);
        return clk_counter;
    }
}
