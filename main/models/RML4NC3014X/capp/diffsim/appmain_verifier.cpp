#include "appmain_verifier.hpp"
//
//
//
//

#include "appmain_periph.hpp"


// Implementation of: class DifferentialVerifier
/*
unsigned int                                eventBusId;

Jasse::LA32Differential*                    diffRef;

BullsEye::Draconids3014::DS232Differential* diffDUT;
*/

DifferentialVerifier::DifferentialVerifier(unsigned int eventBusId, Jasse::LA32Differential* diffRef, BullsEye::Draconids3014::DS232Differential* diffDUT) noexcept
    : eventBusId    (eventBusId)
    , diffRef       (diffRef)
    , diffDUT       (diffDUT)
{ }

unsigned int DifferentialVerifier::GetEventBusId() const noexcept
{
    return eventBusId;
}

Jasse::LA32Differential* DifferentialVerifier::GetDifferentialRef() noexcept
{
    return diffRef;
}

const Jasse::LA32Differential* DifferentialVerifier::GetDifferentialRef() const noexcept
{
    return diffRef;
}

BullsEye::Draconids3014::DS232Differential* DifferentialVerifier::GetDifferentialDUT() noexcept
{
    return diffDUT;
}

const BullsEye::Draconids3014::DS232Differential* DifferentialVerifier::GetDifferentialDUT() const noexcept
{
    return diffDUT;
}

void DifferentialVerifier::VerifyPC(unsigned int dut_offset) const noexcept
{
    // verify PC increment
    if (diffDUT->IsEnabledPC() && diffRef->IsEnabledPC())
    {
        auto& incrementPCDUT = diffDUT->GetIncrementPC().Get(dut_offset);
        auto& incrementPCRef = diffRef->GetIncrementPC();

        if (incrementPCDUT.GetTermCount() != incrementPCRef.GetTermCount())
        {
            MismatchedPCEvent(incrementPCRef, incrementPCDUT).Fire(eventBusId);
            return;
        }

        if (!incrementPCDUT.GetTermCount())
            return;

        if (incrementPCDUT.GetPC() != incrementPCRef.GetPC())
        {
            MismatchedPCEvent(incrementPCRef, incrementPCDUT).Fire(eventBusId);
            return;
        }
    }
}

void DifferentialVerifier::VerifyInstruction(unsigned int dut_offset) const noexcept
{
    // verify instruction increment
    if (diffDUT->IsEnabledInstruction() && diffRef->IsEnabledInstruction())
    {
        auto& incrementInstructionDUT = diffDUT->GetIncrementInstruction().Get(dut_offset);
        auto& incrementInstructionRef = diffRef->GetIncrementInstruction();

        if (incrementInstructionDUT.GetTermCount() != incrementInstructionRef.GetTermCount())
        {
            MismatchedInstructionEvent(incrementInstructionRef, incrementInstructionDUT).Fire(eventBusId);
            return;
        }

        if (!incrementInstructionDUT.GetTermCount())
            return;

        if (incrementInstructionDUT.GetInstruction() != incrementInstructionRef.GetInstruction().GetRaw())
        {
            MismatchedInstructionEvent(incrementInstructionRef, incrementInstructionDUT).Fire(eventBusId);
            return;
        }
    }
}

void DifferentialVerifier::VerifyGPR(unsigned int dut_offset) const noexcept
{
    // verify register increment
    if (diffDUT->IsEnabledGPR() && diffRef->IsEnabledGPR())
    {
        auto& incrementGPRDUT = diffDUT->GetIncrementGPR().Get(dut_offset);
        auto& incrementGPRRef = diffRef->GetIncrementGPR();

        if (!incrementGPRDUT.GetTermCount())
        {
            if (incrementGPRRef.GetTermCount())
            {
                MismatchedGPREvent(incrementGPRRef, incrementGPRDUT).Fire(eventBusId);
                return;
            }
        }
        else
        {
            if (incrementGPRRef.GetTermCount())
            {
                if (incrementGPRDUT.GetTermCount() != incrementGPRRef.GetTermCount())
                {
                    MismatchedGPREvent(incrementGPRRef, incrementGPRDUT).Fire(eventBusId);
                    return;
                }

                if (incrementGPRDUT.GetGPRIndex() != incrementGPRRef.GetGPRIndex())
                {
                    MismatchedGPREvent(incrementGPRRef, incrementGPRDUT).Fire(eventBusId);
                    return;
                }

                if (incrementGPRDUT.GetGPRValue() != incrementGPRRef.GetGPRValue())
                {
                    MismatchedGPREvent(incrementGPRRef, incrementGPRDUT).Fire(eventBusId);
                    return;
                }
            }
            else 
            {
                if (incrementGPRDUT.GetGPRIndex() != 0)
                {
                    MismatchedGPREvent(incrementGPRRef, incrementGPRDUT).Fire(eventBusId);
                    return;
                }
            }
        }
    }
}

static inline Jasse::LA32MOPWidth __Width(BullsEye::Draconids3014::lswidth_t width) noexcept
{
    switch (width)
    {
        case BullsEye::Draconids3014::LSWIDTH_BYTE:
            return Jasse::MOPW_BYTE;

        case BullsEye::Draconids3014::LSWIDTH_HALF_WORD:
            return Jasse::MOPW_HALF_WORD;

        case BullsEye::Draconids3014::LSWIDTH_WORD:
            return Jasse::MOPW_WORD;

        [[unlikely]] default:
            return Jasse::MOPW_WORD;
    }
}

static inline Jasse::LA32MOPWidth __Width(Jasse::LA32MOPWidth width) noexcept
{
    return width;
}

static inline uint32_t __Data(uint32_t data, BullsEye::Draconids3014::lswidth_t width) noexcept
{
    return data & __Width(width).mask;
}

static inline uint32_t __Data(Jasse::memdata_t data, Jasse::LA32MOPWidth width) noexcept
{
    return data.As(width);
}

static inline bool __AddressComp(Jasse::addr_t addr0, Jasse::addr_t addr1)
{
    return (addr0 & 0x7FFFFFFF) == (addr1 & 0x7FFFFFFF);
}

void DifferentialVerifier::VerifyMemoryStore(unsigned int dut_offset) const noexcept
{
    // verify memory store increment
    if (diffDUT->IsEnabledMemoryStore() && diffRef->IsEnabledMemoryStore())
    {
        auto& incrementMemoryStoreDUT = diffDUT->GetIncrementMemoryStore().Get(dut_offset);
        auto& incrementMemoryStoreRef = diffRef->GetIncrementMemoryStore();

        if (incrementMemoryStoreDUT.GetTermCount() 
        !=  incrementMemoryStoreRef.GetTermCount())
        {
            MismatchedMemoryStoreEvent(incrementMemoryStoreRef, incrementMemoryStoreDUT).Fire(eventBusId);
            return;
        }

        if (!incrementMemoryStoreDUT.GetTermCount())
            return;

        if (!__AddressComp(
            PeripheralInjector::ConvertBusAddress(incrementMemoryStoreDUT.GetAddress(), incrementMemoryStoreDUT.IsUncached()),
            incrementMemoryStoreRef.GetAddress()))
        {
            MismatchedMemoryStoreEvent(incrementMemoryStoreRef, incrementMemoryStoreDUT).Fire(eventBusId);
            return;
        }

        if (__Width(incrementMemoryStoreDUT.GetWidth()) 
        !=  __Width(incrementMemoryStoreRef.GetWidth()))
        {
            MismatchedMemoryStoreEvent(incrementMemoryStoreRef, incrementMemoryStoreDUT).Fire(eventBusId);
            return;
        }

        if (__Data(incrementMemoryStoreDUT.GetData(), incrementMemoryStoreDUT.GetWidth())
        !=  __Data(incrementMemoryStoreRef.GetData(), incrementMemoryStoreRef.GetWidth()))
        {
            MismatchedMemoryStoreEvent(incrementMemoryStoreRef, incrementMemoryStoreDUT).Fire(eventBusId);
            return;
        }
    }
}

void DifferentialVerifier::Verify(unsigned int dut_offset) const noexcept
{
    VerifyPC            (dut_offset);
    VerifyInstruction   (dut_offset);
    VerifyGPR           (dut_offset);
    VerifyMemoryStore   (dut_offset);
}


// Implementation of: class DifferentialVerifier::Builder
/*
unsigned int                                eventBusId;

Jasse::LA32Differential*                    diffRef;

BullsEye::Draconids3014::DS232Differential* diffDUT;
*/

DifferentialVerifier::Builder::Builder() noexcept
    : eventBusId    (0)
    , diffRef       (nullptr)
    , diffDUT       (nullptr)
{ }

DifferentialVerifier::Builder& DifferentialVerifier::Builder::EventBusId(unsigned int eventBusId) noexcept
{
    this->eventBusId = eventBusId;
    return *this;
}

DifferentialVerifier::Builder& DifferentialVerifier::Builder::DifferentialRef(Jasse::LA32Differential* diffRef) noexcept
{
    this->diffRef = diffRef;
    return *this;
}

DifferentialVerifier::Builder& DifferentialVerifier::Builder::DifferentialDUT(BullsEye::Draconids3014::DS232Differential* diffDUT) noexcept
{
    this->diffDUT = diffDUT;
    return *this;
}

unsigned int DifferentialVerifier::Builder::GetEventBusId() const noexcept
{
    return eventBusId;
}

void DifferentialVerifier::Builder::SetEventBusId(unsigned int eventBusId) noexcept
{
    this->eventBusId = eventBusId;
}

Jasse::LA32Differential* DifferentialVerifier::Builder::GetDifferentialRef() noexcept
{
    return diffRef;
}

const Jasse::LA32Differential* DifferentialVerifier::Builder::GetDifferentialRef() const noexcept
{
    return diffRef;
}

void DifferentialVerifier::Builder::SetDifferentialRef(Jasse::LA32Differential* diffRef) noexcept
{
    this->diffRef = diffRef;
}

BullsEye::Draconids3014::DS232Differential* DifferentialVerifier::Builder::GetDifferentialDUT() noexcept
{
    return diffDUT;
}

const BullsEye::Draconids3014::DS232Differential* DifferentialVerifier::Builder::GetDifferentialDUT() const noexcept
{
    return diffDUT;
}

void DifferentialVerifier::Builder::SetDifferentialDUT(BullsEye::Draconids3014::DS232Differential* diffDUT) noexcept
{
    this->diffDUT = diffDUT;
}

DifferentialVerifier* DifferentialVerifier::Builder::Build() noexcept
{
    return new DifferentialVerifier(eventBusId, diffRef, diffDUT);
}

