#pragma once
//
//

#include "memory.hpp"
#include "serial.hpp"
#include "counter.hpp"
#include "mmu.hpp"


using namespace Jasse;

namespace BullsEye::NSCSCCSingle {

    // NSCSCC 2022 SoC Instance
    class NSCSCC2022SoC {
    private:
        BaseRAM*            baseRAM;
        ExtRAM*             extRAM;

        SerialInterface*    serial;

        ClockCounter       clk_counter;

        NSCSCC2022MMU       mmu;

    public:
        class Builder;

    private:
        friend class Builder;
        NSCSCC2022SoC(BaseRAM*              baseRAM, 
                      ExtRAM*               extRAM, 
                      SerialInterface*      serial, 
                      const ClockCounter&   clk_counter) noexcept;

    public:
        ~NSCSCC2022SoC() noexcept;

        BaseRAM*                BaseDOGGIES() noexcept;
        const BaseRAM*          BaseDOGGIES() const noexcept;

        ExtRAM*                 ExtDOGGIES() noexcept;
        const ExtRAM*           ExtDOGGIES() const noexcept;

        SerialInterface*        Serial() noexcept;
        const SerialInterface*  Serial() const noexcept;

        ClockCounter&           CounterClock() noexcept;
        const ClockCounter&     CounterClock() const noexcept;

        NSCSCC2022MMU&          MMU() noexcept;
        const NSCSCC2022MMU&    MMU() const noexcept;
    };

    // NSCSCC 2022 SoC Instance Builder
    class NSCSCC2022SoC::Builder {
    private:
        BaseRAM*            baseRAM;
        ExtRAM*             extRAM;

        SerialInterface*    serial;

    public:
        Builder() noexcept;
        ~Builder() noexcept;

        Builder&                BaseDOGGIES(BaseRAM* baseRAM) noexcept;
        Builder&                ExtDOGGIES(ExtRAM* extRAM) noexcept;
        Builder&                Serial(SerialInterface* serial) noexcept;

        BaseRAM*&               BaseDOGGIES() noexcept;
        const BaseRAM*          BaseDOGGIES() const noexcept;

        ExtRAM*&                ExtDOGGIES() noexcept;
        const ExtRAM*           ExtDOGGIES() const noexcept;

        SerialInterface*&       Serial() noexcept;
        const SerialInterface*  Serial() const noexcept;

        NSCSCC2022SoC*          Build() noexcept;
    };
}


// Implementation of: class NSCSCC2022SoC
namespace BullsEye::NSCSCCSingle {
    //
    // BaseRAM*            baseRAM;
    // ExtRAM*             extRAM;
    //
    // SerialInterface*    serial;
    //
    // ClockCounter        clk_counter;
    //
    // NSCSCC2022MMU       mmu;
    //

    NSCSCC2022SoC::NSCSCC2022SoC(BaseRAM*               baseRAM, 
                                 ExtRAM*                extRAM, 
                                 SerialInterface*       serial,
                                 const ClockCounter&    clk_counter) noexcept
        : baseRAM       (baseRAM)
        , extRAM        (extRAM)
        , serial        (serial)
        , clk_counter   (clk_counter)
        , mmu           (baseRAM, extRAM, serial, &(this->clk_counter))
    { }

    NSCSCC2022SoC::~NSCSCC2022SoC() noexcept
    { }

    inline BaseRAM* NSCSCC2022SoC::BaseDOGGIES() noexcept
    {
        return baseRAM;
    }

    inline const BaseRAM* NSCSCC2022SoC::BaseDOGGIES() const noexcept
    {
        return baseRAM;
    }

    inline ExtRAM* NSCSCC2022SoC::ExtDOGGIES() noexcept
    {
        return extRAM;
    }

    inline const ExtRAM* NSCSCC2022SoC::ExtDOGGIES() const noexcept
    {
        return extRAM;
    }

    inline SerialInterface* NSCSCC2022SoC::Serial() noexcept
    {
        return serial;
    }

    inline const SerialInterface* NSCSCC2022SoC::Serial() const noexcept
    {
        return serial;
    }

    inline ClockCounter& NSCSCC2022SoC::CounterClock() noexcept
    {
        return clk_counter;
    }

    inline const ClockCounter& NSCSCC2022SoC::CounterClock() const noexcept
    {
        return clk_counter;
    }

    inline NSCSCC2022MMU& NSCSCC2022SoC::MMU() noexcept
    {
        return mmu;
    }

    inline const NSCSCC2022MMU& NSCSCC2022SoC::MMU() const noexcept
    {
        return mmu;
    }
}


// Implementation of: class NSCSCC2022SoC::Builder
namespace BullsEye::NSCSCCSingle {
    //
    // BaseRAM*            baseRAM;
    // ExtRAM*             extRAM;
    //
    // SerialInterface*    serial;
    //

    NSCSCC2022SoC::Builder::Builder() noexcept
        : baseRAM       (nullptr)
        , extRAM        (nullptr)
        , serial        (nullptr)
    { }

    NSCSCC2022SoC::Builder::~Builder() noexcept
    { }

    inline NSCSCC2022SoC::Builder& NSCSCC2022SoC::Builder::BaseDOGGIES(BaseRAM* baseRAM) noexcept
    {
        this->baseRAM = baseRAM;
        return *this;
    }

    inline NSCSCC2022SoC::Builder& NSCSCC2022SoC::Builder::ExtDOGGIES(ExtRAM* extRAM) noexcept
    {
        this->extRAM = extRAM;
        return *this;
    }

    inline NSCSCC2022SoC::Builder& NSCSCC2022SoC::Builder::Serial(SerialInterface* serial) noexcept
    {
        this->serial = serial;
        return *this;
    }

    inline BaseRAM*& NSCSCC2022SoC::Builder::BaseDOGGIES() noexcept
    {
        return baseRAM;
    }

    inline const BaseRAM* NSCSCC2022SoC::Builder::BaseDOGGIES() const noexcept
    {
        return baseRAM;
    }

    inline ExtRAM*& NSCSCC2022SoC::Builder::ExtDOGGIES() noexcept
    {
        return extRAM;
    }

    inline const ExtRAM* NSCSCC2022SoC::Builder::ExtDOGGIES() const noexcept
    {
        return extRAM;
    }

    inline SerialInterface*& NSCSCC2022SoC::Builder::Serial() noexcept
    {
        return serial;
    }

    inline const SerialInterface* NSCSCC2022SoC::Builder::Serial() const noexcept
    {
        return serial;
    }

    inline NSCSCC2022SoC* NSCSCC2022SoC::Builder::Build() noexcept
    {
        return new NSCSCC2022SoC(baseRAM, extRAM, serial, ClockCounter());
    }
}
