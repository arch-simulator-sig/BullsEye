#pragma once
//
//
//
//

#include "../../csrc/core/ds232_diff.hpp"


#include "autoinclude.h"

#include AUTOINC_BE_COMMON(eventbus.hpp)

#include AUTOINC_BE_JASSE2_LA32(addon/la32diff.hpp)


class DifferentialVerifier {
public:
    class Builder;

public:
    template<class _TIncrementRef, class _TIncrementDUT>
    class MismatchedEvent;

    using MismatchedPCEvent             = MismatchedEvent<Jasse::LA32IncrementPC, BullsEye::Draconids3014::DS232IncrementPC>;
    using MismatchedInstructionEvent    = MismatchedEvent<Jasse::LA32IncrementInstruction, BullsEye::Draconids3014::DS232IncrementInstruction>;
    using MismatchedGPREvent            = MismatchedEvent<Jasse::LA32IncrementGPR, BullsEye::Draconids3014::DS232IncrementGPR>;
    using MismatchedMemoryStoreEvent    = MismatchedEvent<Jasse::LA32IncrementMemoryStore, BullsEye::Draconids3014::DS232IncrementMemoryStore>;

private:
    unsigned int                                eventBusId;

    Jasse::LA32Differential*                    diffRef;

    BullsEye::Draconids3014::DS232Differential* diffDUT;

protected:
    friend class Builder;
    DifferentialVerifier(unsigned int eventBusId, Jasse::LA32Differential* diffRef, BullsEye::Draconids3014::DS232Differential* diffDUT) noexcept;

    void                                                VerifyPC(unsigned int dut_offset) const noexcept;
    void                                                VerifyInstruction(unsigned int dut_offset) const noexcept;
    void                                                VerifyGPR(unsigned int dut_offset) const noexcept;
    void                                                VerifyMemoryStore(unsigned int dut_offset) const noexcept;

public:
    unsigned int                                        GetEventBusId() const noexcept;

    Jasse::LA32Differential*                            GetDifferentialRef() noexcept;
    const Jasse::LA32Differential*                      GetDifferentialRef() const noexcept;

    BullsEye::Draconids3014::DS232Differential*         GetDifferentialDUT() noexcept;
    const BullsEye::Draconids3014::DS232Differential*   GetDifferentialDUT() const noexcept;

    void                                                Verify(unsigned int dut_offset) const noexcept;
};


class DifferentialVerifier::Builder {
private:
    unsigned int                                eventBusId;

    Jasse::LA32Differential*                    diffRef;

    BullsEye::Draconids3014::DS232Differential* diffDUT;

public:
    Builder() noexcept;

    //
    Builder&    EventBusId(unsigned int eventBusId) noexcept;
    Builder&    DifferentialRef(Jasse::LA32Differential* diffRef) noexcept;
    Builder&    DifferentialDUT(BullsEye::Draconids3014::DS232Differential* diffDUT) noexcept;

    //
    unsigned int                                        GetEventBusId() const noexcept;
    void                                                SetEventBusId(unsigned int eventBusId) noexcept;

    Jasse::LA32Differential*                            GetDifferentialRef() noexcept;
    const Jasse::LA32Differential*                      GetDifferentialRef() const noexcept;
    void                                                SetDifferentialRef(Jasse::LA32Differential* diffRef) noexcept;

    BullsEye::Draconids3014::DS232Differential*         GetDifferentialDUT() noexcept;
    const BullsEye::Draconids3014::DS232Differential*   GetDifferentialDUT() const noexcept;
    void                                                SetDifferentialDUT(BullsEye::Draconids3014::DS232Differential* diffDUT) noexcept;

    //
    DifferentialVerifier*                               Build() noexcept;
};


template<class _TIncrementRef, class _TIncrementDUT>
class DifferentialVerifier::MismatchedEvent
    : public BullsEye::Event<DifferentialVerifier::MismatchedEvent<_TIncrementRef, _TIncrementDUT>> {
private:
    const _TIncrementRef& incrementRef;
    const _TIncrementDUT& incrementDUT;

public:
    MismatchedEvent(const _TIncrementRef& incrementRef, const _TIncrementDUT& incrementDUT) noexcept;

    const _TIncrementRef& GetIncrementRef() const noexcept;
    const _TIncrementDUT& GetIncrementDUT() const noexcept;
};




// Implmementation of: template class DifferentialVerifier::MismatchedEvent
/*
const _TIncrementRef& incrementRef;
const _TIncrementDUT& incrementDUT;
*/

template<class _TIncrementRef, class _TIncrementDUT>
DifferentialVerifier::MismatchedEvent<_TIncrementRef, _TIncrementDUT>::MismatchedEvent(const _TIncrementRef& incrementRef, const _TIncrementDUT& incrementDUT) noexcept
    : incrementRef  (incrementRef)
    , incrementDUT  (incrementDUT) {
}

template<class _TIncrementRef, class _TIncrementDUT>
const _TIncrementRef& DifferentialVerifier::MismatchedEvent<_TIncrementRef, _TIncrementDUT>::GetIncrementRef() const noexcept
{
    return incrementRef;
}

template<class _TIncrementRef, class _TIncrementDUT>
const _TIncrementDUT& DifferentialVerifier::MismatchedEvent<_TIncrementRef, _TIncrementDUT>::GetIncrementDUT() const noexcept
{
    return incrementDUT;
}
