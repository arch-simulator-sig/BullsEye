#include "mmu.hpp"
//
//

#include <utility>


#include "mmu_event.hpp"


// Implementation of: class NSCSCC2022MMU
namespace BullsEye::NSCSCCSingle {
    //
    // unsigned int        eventBusId;
    //
    // BaseRAM*            baseRAM;
    // ExtRAM*             extRAM;
    //
    // SerialInterface*    serial;
    //
    // ClockCounter*       clk_counter;
    //

    NSCSCC2023MMU::NSCSCC2023MMU(unsigned int       eventBusId,
                                 BaseRAM*           baseRAM, 
                                 ExtRAM*            extRAM, 
                                 SerialInterface*   serial, 
                                 ClockCounter*      clk_counter) noexcept
        : eventBusId    (eventBusId)
        , baseRAM       (baseRAM)
        , extRAM        (extRAM)
        , serial        (serial)
        , clk_counter   (clk_counter)
    { }

    NSCSCC2023MMU::~NSCSCC2023MMU() noexcept
    { }

    addr_t NSCSCC2023MMU::GetPhysicalAddress(addr_t vaddress) noexcept
    {
        return vaddress & 0x7FFFFFFF;
    }

    addr_t NSCSCC2023MMU::GetBaseRAMAddress(addr_t vaddress) noexcept
    {
        return GetPhysicalAddress(vaddress);
    }

    addr_t NSCSCC2023MMU::GetExtRAMAddress(addr_t vaddress) noexcept
    {
        return GetPhysicalAddress(vaddress) - 0x00400000;
    }

    bool NSCSCC2023MMU::IsBaseRAM(addr_t vaddress) noexcept
    {
        addr_t paddress = GetPhysicalAddress(vaddress);

        return (paddress >= 0x00000000 && paddress <= 0x003FFFFF);
    }

    bool NSCSCC2023MMU::IsExtRAM(addr_t vaddress) noexcept
    {
        addr_t paddress = GetPhysicalAddress(vaddress);

        return (paddress >= 0x00400000 && paddress <= 0x007FFFFF);
    }

    bool NSCSCC2023MMU::IsSerial(addr_t vaddress) noexcept
    {
        return (vaddress == 0xBFD003F8 || vaddress == 0xBFD003FC);
    }

    bool NSCSCC2023MMU::IsSerialData(addr_t vaddress) noexcept
    {
        return (vaddress == 0xBFD003F8);
    }

    bool NSCSCC2023MMU::IsSerialStat(addr_t vaddress) noexcept
    {
        return (vaddress == 0xBFD003FC);
    }

    bool NSCSCC2023MMU::IsClockCounter(addr_t vaddress) noexcept
    {
        return (vaddress == 0xBFD00400 || vaddress == 0xBFD00404);
    }

    LA32MOPOutcome NSCSCC2023MMU::_BaseRAM_Read(LA32MOPPath path, addr_t phyaddress, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        // Pre-Read Event
        NSCSCC2023MMUBaseRAMPreReadPreEvent preReadPreEvent(this, path, phyaddress, width);
        if (preReadPreEvent.Fire(eventBusId).HasException())
            return preReadPreEvent.GetException();

        NSCSCC2023MMUBaseRAMPreReadPostEvent(this, path, phyaddress, width, preReadPreEvent.HasProxy())
            .Fire(eventBusId);

        // BaseRAM device read
        LA32MOPOutcome mopoutcome;
        if (!preReadPreEvent.HasProxy())
            mopoutcome = baseRAM->Read(path, phyaddress, width, dst);
        else
            mopoutcome = preReadPreEvent.GetProxyRoutine()(path, phyaddress, width, dst);

        // Post-Read Event
        NSCSCC2023MMUBaseRAMPostReadPreEvent postReadPreEvent(this, path, phyaddress, width, *dst, mopoutcome);
        if (postReadPreEvent.Fire(eventBusId).HasException())
            return postReadPreEvent.GetException();

        NSCSCC2023MMUBaseRAMPostReadPostEvent(this, path, phyaddress, width, *dst, mopoutcome)
            .Fire(eventBusId);

        //
        return mopoutcome;
    }

    LA32MOPOutcome NSCSCC2023MMU::_BaseRAM_Write(LA32MOPPath path, addr_t phyaddress, LA32MOPWidth width, memdata_t src) noexcept
    {
        // Pre-Write Event
        NSCSCC2023MMUBaseRAMPreWritePreEvent preWritePreEvent(this, path, phyaddress, width, src);
        if (preWritePreEvent.Fire(eventBusId).HasException())
            return preWritePreEvent.GetException();

        NSCSCC2023MMUBaseRAMPreWritePostEvent(this, path, phyaddress, width, src, preWritePreEvent.HasProxy())
            .Fire(eventBusId);

        // BaseRAM device write
        LA32MOPOutcome mopoutcome;
        if (!preWritePreEvent.HasProxy())
            mopoutcome = baseRAM->Write(path, phyaddress, width, src);
        else
            mopoutcome = preWritePreEvent.GetProxyRoutine()(path, phyaddress, width, src);

        // Post-Write Event
        NSCSCC2023MMUBaseRAMPostWritePreEvent postWritePreEvent(this, path, phyaddress, width, src, mopoutcome);
        if (postWritePreEvent.Fire(eventBusId).HasException())
            return postWritePreEvent.GetException();

        NSCSCC2023MMUBaseRAMPostWritePostEvent(this, path, phyaddress, width, src, mopoutcome)
            .Fire(eventBusId);

        //
        return mopoutcome;
    }

    LA32MOPOutcome NSCSCC2023MMU::_BaseRAM_ReadInsn(addr_t phyaddress, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        return _BaseRAM_Read(LA32MOPPath::MOP_INSN, phyaddress, width, dst);
    }

    LA32MOPOutcome NSCSCC2023MMU::_BaseRAM_ReadData(addr_t phyaddress, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        return _BaseRAM_Read(LA32MOPPath::MOP_DATA, phyaddress, width, dst);
    }

    LA32MOPOutcome NSCSCC2023MMU::_BaseRAM_WriteInsn(addr_t phyaddress, LA32MOPWidth width, memdata_t src) noexcept
    {
        return _BaseRAM_Write(LA32MOPPath::MOP_INSN, phyaddress, width, src);
    }

    LA32MOPOutcome NSCSCC2023MMU::_BaseRAM_WriteData(addr_t phyaddress, LA32MOPWidth width, memdata_t src) noexcept
    {
        return _BaseRAM_Write(LA32MOPPath::MOP_DATA, phyaddress, width, src);
    }

    LA32MOPOutcome NSCSCC2023MMU::_ExtRAM_Read(LA32MOPPath path, addr_t phyaddress, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        // Pre-Read Event
        NSCSCC2023MMUExtRAMPreReadPreEvent preReadPreEvent(this, path, phyaddress, width);
        if (preReadPreEvent.Fire(eventBusId).HasException())
            return preReadPreEvent.GetException();

        NSCSCC2023MMUExtRAMPreReadPostEvent(this, path, phyaddress, width, preReadPreEvent.HasProxy())
            .Fire(eventBusId);

        // ExtRAM device read
        LA32MOPOutcome mopoutcome;
        if (!preReadPreEvent.HasProxy())
            mopoutcome = extRAM->Read(path, phyaddress, width, dst);
        else
            mopoutcome = preReadPreEvent.GetProxyRoutine()(path, phyaddress, width, dst);

        // Post-Read Event
        NSCSCC2023MMUExtRAMPostReadPreEvent postReadPreEvent(this, path, phyaddress, width, *dst, mopoutcome);
        if (postReadPreEvent.Fire(eventBusId).HasException())
            return postReadPreEvent.GetException();

        NSCSCC2023MMUExtRAMPostReadPostEvent(this, path, phyaddress, width, *dst, mopoutcome)
            .Fire(eventBusId);

        //
        return mopoutcome;
    }

    LA32MOPOutcome NSCSCC2023MMU::_ExtRAM_Write(LA32MOPPath path, addr_t phyaddress, LA32MOPWidth width, memdata_t src) noexcept
    {
        // Pre-Write Event
        NSCSCC2023MMUExtRAMPreWritePreEvent preWritePreEvent(this, path, phyaddress, width, src);
        if (preWritePreEvent.Fire(eventBusId).HasException())
            return preWritePreEvent.GetException();

        NSCSCC2023MMUExtRAMPreWritePostEvent(this, path, phyaddress, width, src, preWritePreEvent.HasProxy())
            .Fire(eventBusId);

        // ExtRAM device write
        LA32MOPOutcome mopoutcome;
        if (!preWritePreEvent.HasProxy())
            mopoutcome = extRAM->Write(path, phyaddress, width, src);
        else
            mopoutcome = preWritePreEvent.GetProxyRoutine()(path, phyaddress, width, src);

        // Post-Write Event
        NSCSCC2023MMUExtRAMPostWritePreEvent postWritePreEvent(this, path, phyaddress, width, src, mopoutcome);
        if (postWritePreEvent.Fire(eventBusId).HasException())
            return postWritePreEvent.GetException();

        NSCSCC2023MMUExtRAMPostWritePostEvent(this, path, phyaddress, width, src, mopoutcome)
            .Fire(eventBusId);

        //
        return mopoutcome;
    }

    LA32MOPOutcome NSCSCC2023MMU::_ExtRAM_ReadInsn(addr_t phyaddress, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        return _ExtRAM_Read(LA32MOPPath::MOP_INSN, phyaddress, width, dst);
    }

    LA32MOPOutcome NSCSCC2023MMU::_ExtRAM_ReadData(addr_t phyaddress, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        return _ExtRAM_Read(LA32MOPPath::MOP_DATA, phyaddress, width, dst);
    }

    LA32MOPOutcome NSCSCC2023MMU::_ExtRAM_WriteInsn(addr_t phyaddress, LA32MOPWidth width, memdata_t src) noexcept
    {
        return _ExtRAM_Write(LA32MOPPath::MOP_INSN, phyaddress, width, src);
    }

    LA32MOPOutcome NSCSCC2023MMU::_ExtRAM_WriteData(addr_t phyaddress, LA32MOPWidth width, memdata_t src) noexcept
    {
        return _ExtRAM_Write(LA32MOPPath::MOP_DATA, phyaddress, width, src);
    }

    LA32MOPOutcome NSCSCC2023MMU::_MMIO_ReadSerial(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        //
        LA32MOPPath path = LA32MOPPath::MOP_DATA;

        // Pre-Read Event
        NSCSCC2023MMUMappedIOSerialPreReadPreEvent preReadPreEvent(this, path, address, width);
        if (preReadPreEvent.Fire(eventBusId).HasException())
            return preReadPreEvent.GetException();
        
        NSCSCC2023MMUMappedIOSerialPreReadPostEvent(this, path, address, width, preReadPreEvent.HasProxy())
            .Fire(eventBusId);

        // Serial device read
        LA32MOPOutcome mopoutcome = [&]() -> LA32MOPOutcome 
        {
            if (!preReadPreEvent.HasProxy())
            {
                if (!serial)
                    return { LA32MOPStatus::MOP_ACCESS_FAULT, ENOSYS };

                if (width != MOPW_BYTE)
                    return { LA32MOPStatus::MOP_ACCESS_FAULT, ENOSYS };

                if (IsSerialData(address))
                    dst->data8 = serial->Read();
                else if (IsSerialStat(address))
                    dst->data8 = ((serial->IsWriteAvailable() ? 0x01 : 0x00) | (serial->IsReadAvailable() ? 0x02 : 0x00));
                else
                    return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };

                return { LA32MOPStatus::MOP_SUCCESS };
            }
            else
            {
                return preReadPreEvent.GetProxyRoutine()(path, address, width, dst);
            }
        }();

        // Post-Read Event
        NSCSCC2023MMUMappedIOSerialPostReadPreEvent postReadPreEvent(this, path, address, width, *dst, mopoutcome);
        if (postReadPreEvent.Fire(eventBusId).HasException())
            return preReadPreEvent.GetException();

        NSCSCC2023MMUMappedIOSerialPostReadPostEvent(this, path, address, width, *dst, mopoutcome)
            .Fire(eventBusId);

        //
        return mopoutcome;;
    }

    LA32MOPOutcome NSCSCC2023MMU::_MMIO_WriteSerial(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        //
        LA32MOPPath path = LA32MOPPath::MOP_DATA;

        // Pre-Write Event
        NSCSCC2023MMUMappedIOSerialPreWritePreEvent preWritePreEvent(this, path, address, width, src);
        if (preWritePreEvent.Fire(eventBusId).HasException())
            return preWritePreEvent.GetException();

        NSCSCC2023MMUMappedIOSerialPreWritePostEvent(this, path, address, width, src, preWritePreEvent.HasProxy())
            .Fire(eventBusId);

        // Serial device write
        LA32MOPOutcome mopoutcome = [&]() -> LA32MOPOutcome
        {
            if (!preWritePreEvent.HasProxy())
            {
                if (!serial)
                    return { LA32MOPStatus::MOP_ACCESS_FAULT, ENOSYS };

                if (width != MOPW_BYTE)
                    return { LA32MOPStatus::MOP_ACCESS_FAULT, ENOSYS };

                if (IsSerialData(address))
                    serial->Write(src.data8);
                else
                    return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };

                return { LA32MOPStatus::MOP_SUCCESS };
            }
            else
            {
                return preWritePreEvent.GetProxyRoutine()(path, address, width, src);
            }
        }();

        // Post-Write Event
        NSCSCC2023MMUMappedIOSerialPostWritePreEvent postWritePreEvent(this, path, address, width, src, mopoutcome);
        if (postWritePreEvent.Fire(eventBusId).HasException())
            return postWritePreEvent.GetException();

        NSCSCC2023MMUMappedIOSerialPostWritePostEvent(this, path, address, width, src, mopoutcome)
            .Fire(eventBusId);
        
        //
        return mopoutcome;
    }

    LA32MOPOutcome NSCSCC2023MMU::_MMIO_ReadClockCounter(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        //
        LA32MOPPath path = LA32MOPPath::MOP_DATA;

        // Pre-Read Event
        NSCSCC2023MMUMappedIOClockCounterPreReadPreEvent preReadPreEvent(this, path, address, width);
        if (preReadPreEvent.Fire(eventBusId).HasException())
            return preReadPreEvent.GetException();

        NSCSCC2023MMUMappedIOClockCounterPreReadPostEvent(this, path, address, width, preReadPreEvent.HasProxy())
            .Fire(eventBusId);

        // device read
        LA32MOPOutcome mopoutcome = [&]() -> LA32MOPOutcome 
        {
            if (!preReadPreEvent.HasProxy())
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
            else
            {
                return preReadPreEvent.GetProxyRoutine()(path, address, width, dst);
            }
        }();

        // Post-Read Event
        NSCSCC2023MMUMappedIOClockCounterPostReadPreEvent postReadPreEvent(this, path, address, width, *dst, mopoutcome);
        if (postReadPreEvent.Fire(eventBusId).HasException())
            return postReadPreEvent.GetException();

        NSCSCC2023MMUMappedIOClockCounterPostReadPostEvent(this, path, address, width, *dst, mopoutcome)
            .Fire(eventBusId);

        //
        return mopoutcome;
    }

    LA32MOPOutcome NSCSCC2023MMU::_MMIO_WriteClockCounter(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        return { LA32MOPStatus::MOP_ACCESS_FAULT, ENOSYS };
    }

    LA32MOPOutcome NSCSCC2023MMU::ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        // Pre-Read Event
        NSCSCC2023MMUPreReadPreEvent preReadPreEvent(this, LA32MOPPath::MOP_INSN, address, width);
        if (preReadPreEvent.Fire(eventBusId).HasException())
            return preReadPreEvent.GetException();

        NSCSCC2023MMUPreReadPostEvent(this, LA32MOPPath::MOP_INSN, address, width, preReadPreEvent.HasProxy())
            .Fire(eventBusId);

        // device read
        LA32MOPOutcome mopoutcome = [&]() -> LA32MOPOutcome 
        {
            if (!preReadPreEvent.HasProxy())
            {
                if (IsBaseRAM(address))
                    return _BaseRAM_ReadInsn(GetBaseRAMAddress(address), width, dst);
                else if (IsExtRAM(address))
                    return _ExtRAM_ReadInsn(GetExtRAMAddress(address), width, dst);
                else
                    return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };
            }
            else
            {
                return preReadPreEvent.GetProxyRoutine()(LA32MOPPath::MOP_INSN, address, width, dst);
            }
        }();

        // Post-Read Event
        NSCSCC2023MMUPostReadPreEvent postReadPreEvent(this, LA32MOPPath::MOP_INSN, address, width, *dst, mopoutcome);
        if (postReadPreEvent.Fire(eventBusId).HasException())
            return postReadPreEvent.GetException();

        NSCSCC2023MMUPostReadPostEvent(this, LA32MOPPath::MOP_INSN, address, width, *dst, mopoutcome)
            .Fire(eventBusId);

        //
        return mopoutcome;
    }

    LA32MOPOutcome NSCSCC2023MMU::ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        // Pre-Read Event
        NSCSCC2023MMUPreReadPreEvent preReadPreEvent(this, LA32MOPPath::MOP_DATA, address, width);
        if (preReadPreEvent.Fire(eventBusId).HasException())
            return preReadPreEvent.GetException();

        NSCSCC2023MMUPreReadPostEvent(this, LA32MOPPath::MOP_DATA, address, width, preReadPreEvent.HasProxy())
            .Fire(eventBusId);

        // device read
        LA32MOPOutcome mopoutcome = [&]() -> LA32MOPOutcome 
        {
            if (!preReadPreEvent.HasProxy())
            {
                if (IsBaseRAM(address))
                    return _BaseRAM_ReadData(GetBaseRAMAddress(address), width, dst);
                else if (IsExtRAM(address))
                    return _ExtRAM_ReadData(GetExtRAMAddress(address), width, dst);
                else if (IsSerial(address))
                    return _MMIO_ReadSerial(address, width, dst);
                else if (IsClockCounter(address))
                    return _MMIO_ReadClockCounter(address, width, dst);
                else
                    return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };
            }
            else 
            {
                return preReadPreEvent.GetProxyRoutine()(LA32MOPPath::MOP_DATA, address, width, dst);
            }
        }();

        // Post-Read Event
        NSCSCC2023MMUPostReadPreEvent postReadPreEvent(this, LA32MOPPath::MOP_DATA, address, width, *dst, mopoutcome);
        if (postReadPreEvent.Fire(eventBusId).HasException())
            return postReadPreEvent.GetException();

        NSCSCC2023MMUPostReadPostEvent(this, LA32MOPPath::MOP_DATA, address, width, *dst, mopoutcome)
            .Fire(eventBusId);

        //
        return mopoutcome;
    }

    LA32MOPOutcome NSCSCC2023MMU::WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        // Pre-Write Event
        NSCSCC2023MMUPreWritePreEvent preWritePreEvent(this, LA32MOPPath::MOP_INSN, address, width, src);
        if (preWritePreEvent.Fire(eventBusId).HasException())
            return preWritePreEvent.GetException();

        NSCSCC2023MMUPreWritePostEvent(this, LA32MOPPath::MOP_INSN, address, width, src, preWritePreEvent.HasProxy())
            .Fire(eventBusId);

        // device write
        LA32MOPOutcome mopoutcome = [&]() -> LA32MOPOutcome 
        {
            if (!preWritePreEvent.HasProxy())
            {
                if (IsBaseRAM(address))
                    return _BaseRAM_WriteInsn(GetBaseRAMAddress(address), width, src);
                else if (IsExtRAM(address))
                    return _ExtRAM_WriteInsn(GetExtRAMAddress(address), width, src);
                else
                    return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };
            }
            else
            {
                return preWritePreEvent.GetProxyRoutine()(LA32MOPPath::MOP_INSN, address, width, src);
            }
        }();

        // Post-Write Event
        NSCSCC2023MMUPostWritePreEvent postWritePreEvent(this, LA32MOPPath::MOP_INSN, address, width, src, mopoutcome);
        if (postWritePreEvent.Fire(eventBusId).HasException())
            return postWritePreEvent.GetException();

        NSCSCC2023MMUPostWritePostEvent(this, LA32MOPPath::MOP_INSN, address, width, src, mopoutcome)
            .Fire(eventBusId);

        //
        return mopoutcome;
    }

    LA32MOPOutcome NSCSCC2023MMU::WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        // Pre-Write Event
        NSCSCC2023MMUPreWritePreEvent preWritePreEvent(this, LA32MOPPath::MOP_DATA, address, width, src);
        if (preWritePreEvent.Fire(eventBusId).HasException())
            return preWritePreEvent.GetException();

        NSCSCC2023MMUPreWritePostEvent(this, LA32MOPPath::MOP_DATA, address, width, src, preWritePreEvent.HasProxy())
            .Fire(eventBusId);

        // device write
        LA32MOPOutcome mopoutcome = [&]() -> LA32MOPOutcome
        {
            if (!preWritePreEvent.HasProxy())
            {
                if (IsBaseRAM(address))
                    return _BaseRAM_WriteData(GetBaseRAMAddress(address), width, src);
                else if (IsExtRAM(address))
                    return _ExtRAM_WriteData(GetExtRAMAddress(address), width, src);
                else if (IsSerial(address))
                    return _MMIO_WriteSerial(address, width, src);
                else if (IsClockCounter(address))
                    return _MMIO_WriteClockCounter(address, width, src);
                else
                    return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };
            }
            else 
            {
                return preWritePreEvent.GetProxyRoutine()(LA32MOPPath::MOP_DATA, address, width, src);
            }
        }();

        // Post-Write Event
        NSCSCC2023MMUPostWritePreEvent postWritePreEvent(this, LA32MOPPath::MOP_DATA, address, width, src, mopoutcome);
        if (postWritePreEvent.Fire(eventBusId).HasException())
            return postWritePreEvent.GetException();

        NSCSCC2023MMUPostWritePostEvent(this, LA32MOPPath::MOP_DATA, address, width, src, mopoutcome)
            .Fire(eventBusId);

        //
        return mopoutcome;
    }

    unsigned int NSCSCC2023MMU::GetEventBusId() const noexcept
    {
        return eventBusId;
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
