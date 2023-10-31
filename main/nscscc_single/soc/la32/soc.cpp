#include "soc.hpp"
//
//


// Implementation of: class NSCSCC2023SoC
namespace BullsEye::NSCSCCSingle {
    //
    // unsigned int        eventBusId;
    //
    // BaseRAM*            baseRAM;
    // ExtRAM*             extRAM;
    //
    // SerialInterface*    serial;
    //
    // ClockCounter        clk_counter;
    //
    // NSCSCC2023MMU       mmu;
    //

    NSCSCC2023SoC::NSCSCC2023SoC(unsigned int           eventBusId,
                                 BaseRAM*               baseRAM, 
                                 ExtRAM*                extRAM, 
                                 SerialInterface*       serial,
                                 const ClockCounter&    clk_counter) noexcept
        : eventBusId    (eventBusId)
        , baseRAM       (baseRAM)
        , extRAM        (extRAM)
        , serial        (serial)
        , clk_counter   (clk_counter)
        , mmu           (eventBusId, baseRAM, extRAM, serial, &(this->clk_counter))
    { }

    NSCSCC2023SoC::~NSCSCC2023SoC() noexcept
    { }

    unsigned int NSCSCC2023SoC::GetEventBusId()
    {
        return eventBusId;
    }

    BaseRAM* NSCSCC2023SoC::BaseDOGGIES() noexcept
    {
        return baseRAM;
    }

    const BaseRAM* NSCSCC2023SoC::BaseDOGGIES() const noexcept
    {
        return baseRAM;
    }

    ExtRAM* NSCSCC2023SoC::ExtDOGGIES() noexcept
    {
        return extRAM;
    }

    const ExtRAM* NSCSCC2023SoC::ExtDOGGIES() const noexcept
    {
        return extRAM;
    }

    SerialInterface* NSCSCC2023SoC::Serial() noexcept
    {
        return serial;
    }

    const SerialInterface* NSCSCC2023SoC::Serial() const noexcept
    {
        return serial;
    }

    ClockCounter& NSCSCC2023SoC::CounterClock() noexcept
    {
        return clk_counter;
    }

    const ClockCounter& NSCSCC2023SoC::CounterClock() const noexcept
    {
        return clk_counter;
    }

    NSCSCC2023MMU& NSCSCC2023SoC::MMU() noexcept
    {
        return mmu;
    }

    const NSCSCC2023MMU& NSCSCC2023SoC::MMU() const noexcept
    {
        return mmu;
    }
}


// Implementation of: class NSCSCC2023SoC::Builder
namespace BullsEye::NSCSCCSingle {
    //
    // unsigned int        eventBusId;
    //
    // BaseRAM*            baseRAM;
    // ExtRAM*             extRAM;
    //
    // SerialInterface*    serial;
    //

    NSCSCC2023SoC::Builder::Builder() noexcept
        : eventBusId    (0)
        , baseRAM       (nullptr)
        , extRAM        (nullptr)
        , serial        (nullptr)
    { }

    NSCSCC2023SoC::Builder::~Builder() noexcept
    { }

    NSCSCC2023SoC::Builder& NSCSCC2023SoC::Builder::EventBusId(unsigned int eventBusId) noexcept
    {
        this->eventBusId = eventBusId;
        return *this;
    }

    NSCSCC2023SoC::Builder& NSCSCC2023SoC::Builder::BaseDOGGIES(BaseRAM* baseRAM) noexcept
    {
        this->baseRAM = baseRAM;
        return *this;
    }

    NSCSCC2023SoC::Builder& NSCSCC2023SoC::Builder::ExtDOGGIES(ExtRAM* extRAM) noexcept
    {
        this->extRAM = extRAM;
        return *this;
    }

    NSCSCC2023SoC::Builder& NSCSCC2023SoC::Builder::Serial(SerialInterface* serial) noexcept
    {
        this->serial = serial;
        return *this;
    }

    unsigned int& NSCSCC2023SoC::Builder::EventBusId() noexcept
    {
        return eventBusId;
    }

    unsigned int NSCSCC2023SoC::Builder::EventBusId() const noexcept
    {
        return eventBusId;
    }

    BaseRAM*& NSCSCC2023SoC::Builder::BaseDOGGIES() noexcept
    {
        return baseRAM;
    }

    const BaseRAM* NSCSCC2023SoC::Builder::BaseDOGGIES() const noexcept
    {
        return baseRAM;
    }

    ExtRAM*& NSCSCC2023SoC::Builder::ExtDOGGIES() noexcept
    {
        return extRAM;
    }

    const ExtRAM* NSCSCC2023SoC::Builder::ExtDOGGIES() const noexcept
    {
        return extRAM;
    }

    SerialInterface*& NSCSCC2023SoC::Builder::Serial() noexcept
    {
        return serial;
    }

    const SerialInterface* NSCSCC2023SoC::Builder::Serial() const noexcept
    {
        return serial;
    }

    NSCSCC2023SoC* NSCSCC2023SoC::Builder::Build() noexcept
    {
        return new NSCSCC2023SoC(eventBusId, baseRAM, extRAM, serial, ClockCounter());
    }
}
