#pragma once
//
//

#include "memory.hpp"
#include "serial.hpp"
#include "counter.hpp"
#include "mmu.hpp"


using namespace Jasse;

namespace BullsEye::NSCSCCSingle {

    // NSCSCC 2023 SoC Instance
    class NSCSCC2023SoC {
    private:
        BaseRAM*            baseRAM;
        ExtRAM*             extRAM;

        SerialInterface*    serial;

        ClockCounter        clk_counter;

        NSCSCC2023MMU       mmu;

    public:
        class Builder;

    private:
        friend class Builder;
        NSCSCC2023SoC(BaseRAM*              baseRAM, 
                      ExtRAM*               extRAM, 
                      SerialInterface*      serial, 
                      const ClockCounter&   clk_counter) noexcept;

    public:
        ~NSCSCC2023SoC() noexcept;

        BaseRAM*                BaseDOGGIES() noexcept;
        const BaseRAM*          BaseDOGGIES() const noexcept;

        ExtRAM*                 ExtDOGGIES() noexcept;
        const ExtRAM*           ExtDOGGIES() const noexcept;

        SerialInterface*        Serial() noexcept;
        const SerialInterface*  Serial() const noexcept;

        ClockCounter&           CounterClock() noexcept;
        const ClockCounter&     CounterClock() const noexcept;

        NSCSCC2023MMU&          MMU() noexcept;
        const NSCSCC2023MMU&    MMU() const noexcept;
    };

    // NSCSCC 2023 SoC Instance Builder
    class NSCSCC2023SoC::Builder {
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

        NSCSCC2023SoC*          Build() noexcept;
    };
}


// Implementation of: class NSCSCC2023SoC
namespace BullsEye::NSCSCCSingle {
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

    NSCSCC2023SoC::NSCSCC2023SoC(BaseRAM*               baseRAM, 
                                 ExtRAM*                extRAM, 
                                 SerialInterface*       serial,
                                 const ClockCounter&    clk_counter) noexcept
        : baseRAM       (baseRAM)
        , extRAM        (extRAM)
        , serial        (serial)
        , clk_counter   (clk_counter)
        , mmu           (baseRAM, extRAM, serial, &(this->clk_counter))
    { }

    NSCSCC2023SoC::~NSCSCC2023SoC() noexcept
    { }

    inline BaseRAM* NSCSCC2023SoC::BaseDOGGIES() noexcept
    {
        return baseRAM;
    }

    inline const BaseRAM* NSCSCC2023SoC::BaseDOGGIES() const noexcept
    {
        return baseRAM;
    }

    inline ExtRAM* NSCSCC2023SoC::ExtDOGGIES() noexcept
    {
        return extRAM;
    }

    inline const ExtRAM* NSCSCC2023SoC::ExtDOGGIES() const noexcept
    {
        return extRAM;
    }

    inline SerialInterface* NSCSCC2023SoC::Serial() noexcept
    {
        return serial;
    }

    inline const SerialInterface* NSCSCC2023SoC::Serial() const noexcept
    {
        return serial;
    }

    inline ClockCounter& NSCSCC2023SoC::CounterClock() noexcept
    {
        return clk_counter;
    }

    inline const ClockCounter& NSCSCC2023SoC::CounterClock() const noexcept
    {
        return clk_counter;
    }

    inline NSCSCC2023MMU& NSCSCC2023SoC::MMU() noexcept
    {
        return mmu;
    }

    inline const NSCSCC2023MMU& NSCSCC2023SoC::MMU() const noexcept
    {
        return mmu;
    }
}


// Implementation of: class NSCSCC2023SoC::Builder
namespace BullsEye::NSCSCCSingle {
    //
    // BaseRAM*            baseRAM;
    // ExtRAM*             extRAM;
    //
    // SerialInterface*    serial;
    //

    NSCSCC2023SoC::Builder::Builder() noexcept
        : baseRAM       (nullptr)
        , extRAM        (nullptr)
        , serial        (nullptr)
    { }

    NSCSCC2023SoC::Builder::~Builder() noexcept
    { }

    inline NSCSCC2023SoC::Builder& NSCSCC2023SoC::Builder::BaseDOGGIES(BaseRAM* baseRAM) noexcept
    {
        this->baseRAM = baseRAM;
        return *this;
    }

    inline NSCSCC2023SoC::Builder& NSCSCC2023SoC::Builder::ExtDOGGIES(ExtRAM* extRAM) noexcept
    {
        this->extRAM = extRAM;
        return *this;
    }

    inline NSCSCC2023SoC::Builder& NSCSCC2023SoC::Builder::Serial(SerialInterface* serial) noexcept
    {
        this->serial = serial;
        return *this;
    }

    inline BaseRAM*& NSCSCC2023SoC::Builder::BaseDOGGIES() noexcept
    {
        return baseRAM;
    }

    inline const BaseRAM* NSCSCC2023SoC::Builder::BaseDOGGIES() const noexcept
    {
        return baseRAM;
    }

    inline ExtRAM*& NSCSCC2023SoC::Builder::ExtDOGGIES() noexcept
    {
        return extRAM;
    }

    inline const ExtRAM* NSCSCC2023SoC::Builder::ExtDOGGIES() const noexcept
    {
        return extRAM;
    }

    inline SerialInterface*& NSCSCC2023SoC::Builder::Serial() noexcept
    {
        return serial;
    }

    inline const SerialInterface* NSCSCC2023SoC::Builder::Serial() const noexcept
    {
        return serial;
    }

    inline NSCSCC2023SoC* NSCSCC2023SoC::Builder::Build() noexcept
    {
        return new NSCSCC2023SoC(baseRAM, extRAM, serial, ClockCounter());
    }
}
