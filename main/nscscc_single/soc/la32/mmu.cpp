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

        if (mopoutcome.status != LA32MOPStatus::MOP_SUCCESS)
            return mopoutcome;

        // Post-Read Event
        NSCSCC2023MMUBaseRAMPostReadPreEvent postReadPreEvent(this, path, phyaddress, width, *dst);
        if (postReadPreEvent.Fire(eventBusId).HasException())
            return postReadPreEvent.GetException();

        NSCSCC2023MMUBaseRAMPostReadPostEvent(this, path, phyaddress, width, *dst)
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

        if (mopoutcome.status != LA32MOPStatus::MOP_SUCCESS)
            return mopoutcome;

        // Post-Write Event
        NSCSCC2023MMUBaseRAMPostWritePreEvent postWritePreEvent(this, path, phyaddress, width, src);
        if (postWritePreEvent.Fire(eventBusId).HasException())
            return postWritePreEvent.GetException();

        NSCSCC2023MMUBaseRAMPostWritePostEvent(this, path, phyaddress, width, src)
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

        if (mopoutcome.status != LA32MOPStatus::MOP_SUCCESS)
            return mopoutcome;

        // Post-Read Event
        NSCSCC2023MMUExtRAMPostReadPreEvent postReadPreEvent(this, path, phyaddress, width, *dst);
        if (postReadPreEvent.Fire(eventBusId).HasException())
            return postReadPreEvent.GetException();

        NSCSCC2023MMUExtRAMPostReadPostEvent(this, path, phyaddress, width, *dst)
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

        if (mopoutcome.status != LA32MOPStatus::MOP_SUCCESS)
            return mopoutcome;

        // Post-Write Event
        NSCSCC2023MMUExtRAMPostWritePreEvent postWritePreEvent(this, path, phyaddress, width, src);
        if (postWritePreEvent.Fire(eventBusId).HasException())
            return postWritePreEvent.GetException();

        NSCSCC2023MMUExtRAMPostWritePostEvent(this, path, phyaddress, width, src)
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
        NSCSCC2023MMUSerialPreReadPreEvent preReadPreEvent(this, path, address, width);
        if (preReadPreEvent.Fire(eventBusId).HasException())
            return preReadPreEvent.GetException();
        
        NSCSCC2023MMUSerialPreReadPostEvent(this, path, address, width, preReadPreEvent.HasProxy())
            .Fire(eventBusId);

        // Serial device read
        if (!preReadPreEvent.HasProxy())
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
        }
        else
        {
            LA32MOPOutcome proxy_mopoutcome 
                = preReadPreEvent.GetProxyRoutine()(path, address, width, dst);

            if (proxy_mopoutcome.status != LA32MOPStatus::MOP_SUCCESS)
                return proxy_mopoutcome;
        }

        // Post-Read Event
        NSCSCC2023MMUSerialPostReadPreEvent postReadPreEvent(this, path, address, width, *dst);
        if (postReadPreEvent.Fire(eventBusId).HasException())
            return preReadPreEvent.GetException();

        NSCSCC2023MMUSerialPostReadPostEvent(this, path, address, width, *dst)
            .Fire(eventBusId);

        //
        return { LA32MOPStatus::MOP_SUCCESS };
    }

    LA32MOPOutcome NSCSCC2023MMU::_MMIO_WriteSerial(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        //
        LA32MOPPath path = LA32MOPPath::MOP_DATA;

        // Pre-Write Event
        NSCSCC2023MMUSerialPreWritePreEvent preWritePreEvent(this, path, address, width, src);
        if (preWritePreEvent.Fire(eventBusId).HasException())
            return preWritePreEvent.GetException();

        NSCSCC2023MMUSerialPreWritePostEvent(this, path, address, width, src, preWritePreEvent.HasProxy())
            .Fire(eventBusId);

        // Serial device write
        if (!preWritePreEvent.HasProxy())
        {
            if (!serial)
                return { LA32MOPStatus::MOP_ACCESS_FAULT, ENOSYS };

            if (width != MOPW_BYTE)
                return { LA32MOPStatus::MOP_ACCESS_FAULT, ENOSYS };

            if (address == 0xBFD003F8)
                serial->Write(src.data8);
            else
                return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };
        }
        else
        {
            LA32MOPOutcome proxy_mopoutcome 
                = preWritePreEvent.GetProxyRoutine()(path, address, width, src);

            if (proxy_mopoutcome.status != LA32MOPStatus::MOP_SUCCESS)
                return proxy_mopoutcome;
        }

        // Post-Write Event
        NSCSCC2023MMUSerialPostWritePreEvent postWritePreEvent(this, path, address, width, src);
        if (postWritePreEvent.Fire(eventBusId).HasException())
            return postWritePreEvent.GetException();

        NSCSCC2023MMUSerialPostWritePostEvent(this, path, address, width, src)
            .Fire(eventBusId);
        
        //
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

        // Pre-Read Event
        NSCSCC2023MMUPreReadPreEvent preReadPreEvent(this, LA32MOPPath::MOP_INSN, phyaddress, width);
        if (preReadPreEvent.Fire(eventBusId).HasException())
            return preReadPreEvent.GetException();

        NSCSCC2023MMUPreReadPostEvent(this, LA32MOPPath::MOP_INSN, phyaddress, width, preReadPreEvent.HasProxy())
            .Fire(eventBusId);

        // device read
        LA32MOPOutcome mopoutcome;
        if (!preReadPreEvent.HasProxy())
        {
            if (phyaddress >= 0x00000000 && phyaddress <= 0x003FFFFF)
                mopoutcome = _BaseRAM_ReadInsn(phyaddress, width, dst);
            else if (phyaddress >= 0x00400000 && phyaddress <= 0x007FFFFF)
                mopoutcome = _ExtRAM_ReadInsn(phyaddress - 0x00400000, width, dst);
            else
                return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };
        }
        else
        {
            mopoutcome = preReadPreEvent.GetProxyRoutine()(LA32MOPPath::MOP_INSN, phyaddress, width, dst);
        }

        if (mopoutcome.status != LA32MOPStatus::MOP_SUCCESS)
            return mopoutcome;

        // Post-Read Event
        NSCSCC2023MMUPostReadPreEvent postReadPreEvent(this, LA32MOPPath::MOP_INSN, phyaddress, width, *dst);
        if (postReadPreEvent.Fire(eventBusId).HasException())
            return postReadPreEvent.GetException();

        NSCSCC2023MMUPostReadPostEvent(this, LA32MOPPath::MOP_INSN, phyaddress, width, *dst)
            .Fire(eventBusId);

        //
        return mopoutcome;
    }

    LA32MOPOutcome NSCSCC2023MMU::ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        addr_t phyaddress = address & 0x7FFFFFFF;

        // Pre-Read Event
        NSCSCC2023MMUPreReadPreEvent preReadPreEvent(this, LA32MOPPath::MOP_DATA, phyaddress, width);
        if (preReadPreEvent.Fire(eventBusId).HasException())
            return preReadPreEvent.GetException();

        NSCSCC2023MMUPreReadPostEvent(this, LA32MOPPath::MOP_DATA, phyaddress, width, preReadPreEvent.HasProxy())
            .Fire(eventBusId);

        // device read
        LA32MOPOutcome mopoutcome;
        if (!preReadPreEvent.HasProxy())
        {
            if (phyaddress >= 0x00000000 && phyaddress <= 0x003FFFFF)
                mopoutcome = _BaseRAM_ReadData(phyaddress, width, dst);
            else if (phyaddress >= 0x00400000 && phyaddress <= 0x007FFFFF)
                mopoutcome = _ExtRAM_ReadData(phyaddress - 0x00400000, width, dst);
            else if (address == 0xBFD003F8 || address == 0xBFD003FC)
                mopoutcome = _MMIO_ReadSerial(address, width, dst);
            else if (address == 0xBFD00400 || address == 0xBFD00404)
                mopoutcome = _MMIO_ReadClockCounter(address, width, dst);
            else
                return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };
        }
        else 
        {
            mopoutcome = preReadPreEvent.GetProxyRoutine()(LA32MOPPath::MOP_DATA, phyaddress, width, dst);
        }

        if (mopoutcome.status != LA32MOPStatus::MOP_SUCCESS)
        {
            printf("Failed ReadData: 0x%08x %d\n", address, width.length); // TODO: DEBUG purpose, removed in future
            return mopoutcome;
        }

        // Post-Read Event
        NSCSCC2023MMUPostReadPreEvent postReadPreEvent(this, LA32MOPPath::MOP_DATA, phyaddress, width, *dst);
        if (postReadPreEvent.Fire(eventBusId).HasException())
            return postReadPreEvent.GetException();

        NSCSCC2023MMUPostReadPostEvent(this, LA32MOPPath::MOP_DATA, phyaddress, width, *dst)
            .Fire(eventBusId);

        //
        return mopoutcome;
    }

    LA32MOPOutcome NSCSCC2023MMU::WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        addr_t phyaddress = address & 0x7FFFFFFF;

        // Pre-Write Event
        NSCSCC2023MMUPreWritePreEvent preWritePreEvent(this, LA32MOPPath::MOP_INSN, phyaddress, width, src);
        if (preWritePreEvent.Fire(eventBusId).HasException())
            return preWritePreEvent.GetException();

        NSCSCC2023MMUPreWritePostEvent(this, LA32MOPPath::MOP_INSN, phyaddress, width, src, preWritePreEvent.HasProxy())
            .Fire(eventBusId);

        // device write
        LA32MOPOutcome mopoutcome;
        if (!preWritePreEvent.HasProxy())
        {
            if (phyaddress >= 0x00000000 && phyaddress <= 0x003FFFFF)
                mopoutcome = _BaseRAM_WriteInsn(phyaddress, width, src);
            else if (phyaddress >= 0x00400000 && phyaddress <= 0x007FFFFF)
                mopoutcome = _ExtRAM_WriteInsn(phyaddress - 0x00400000, width, src);
            else
                return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };
        }
        else
        {
            mopoutcome = preWritePreEvent.GetProxyRoutine()(LA32MOPPath::MOP_INSN, phyaddress, width, src);
        }

        if (mopoutcome.status != LA32MOPStatus::MOP_SUCCESS)
            return mopoutcome;

        // Post-Write Event
        NSCSCC2023MMUPostWritePreEvent postWritePreEvent(this, LA32MOPPath::MOP_INSN, phyaddress, width, src);
        if (postWritePreEvent.Fire(eventBusId).HasException())
            return postWritePreEvent.GetException();

        NSCSCC2023MMUPostWritePostEvent(this, LA32MOPPath::MOP_INSN, phyaddress, width, src)
            .Fire(eventBusId);

        //
        return mopoutcome;
    }

    LA32MOPOutcome NSCSCC2023MMU::WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        addr_t phyaddress = address & 0x7FFFFFFF;

        // Pre-Write Event
        NSCSCC2023MMUPreWritePreEvent preWritePreEvent(this, LA32MOPPath::MOP_DATA, phyaddress, width, src);
        if (preWritePreEvent.Fire(eventBusId).HasException())
            return preWritePreEvent.GetException();

        NSCSCC2023MMUPreWritePostEvent(this, LA32MOPPath::MOP_DATA, phyaddress, width, src, preWritePreEvent.HasProxy())
            .Fire(eventBusId);

        // device write
        LA32MOPOutcome mopoutcome;
        if (!preWritePreEvent.HasProxy())
        {
            if (phyaddress >= 0x00000000 && phyaddress <= 0x003FFFFF)
                mopoutcome = _BaseRAM_WriteData(phyaddress, width, src);
            else if (phyaddress >= 0x00400000 && phyaddress <= 0x007FFFFF)
                mopoutcome = _ExtRAM_WriteData(phyaddress - 0x00400000, width, src);
            else if (address == 0xBFD003F8 || address == 0xBFD003FC)
                mopoutcome = _MMIO_WriteSerial(address, width, src);
            else if (address == 0xBFD00400 || address == 0xBFD00404)
                mopoutcome = _MMIO_WriteClockCounter(address, width, src);
            else
                return { LA32MOPStatus::MOP_ACCESS_FAULT, EFAULT };
        }
        else 
        {
            mopoutcome = preWritePreEvent.GetProxyRoutine()(LA32MOPPath::MOP_DATA, phyaddress, width, src);
        }

        if (mopoutcome.status != LA32MOPStatus::MOP_SUCCESS)
        {
            printf("Failed WriteData: 0x%08x %d\n", address, width.length); // TODO: DEBUG purpose, removed in future
            return mopoutcome;
        }

        // Post-Write Event
        NSCSCC2023MMUPostWritePreEvent postWritePreEvent(this, LA32MOPPath::MOP_DATA, phyaddress, width, src);
        if (postWritePreEvent.Fire(eventBusId).HasException())
            return postWritePreEvent.GetException();

        NSCSCC2023MMUPostWritePostEvent(this, LA32MOPPath::MOP_DATA, phyaddress, width, src)
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
