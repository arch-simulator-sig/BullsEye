#pragma once
//
//

#ifndef __HEADER_BULLSEYE_NSCSCC2023_LA32_SOC__SOC
#define __HEADER_BULLSEYE_NSCSCC2023_LA32_SOC__SOC


#include "memory.hpp"
#include "serial.hpp"
#include "counter.hpp"
#include "mmu.hpp"


namespace BullsEye::NSCSCCSingle {

    // NSCSCC 2023 SoC Instance
    class NSCSCC2023SoC {
    private:
        unsigned int        eventBusId;

        BaseRAM*            baseRAM;
        ExtRAM*             extRAM;

        SerialInterface*    serial;

        ClockCounter        clk_counter;

        NSCSCC2023MMU       mmu;

    public:
        class Builder;

    private:
        friend class Builder;
        NSCSCC2023SoC(unsigned int          eventBusId,
                      BaseRAM*              baseRAM, 
                      ExtRAM*               extRAM, 
                      SerialInterface*      serial, 
                      const ClockCounter&   clk_counter) noexcept;

    public:
        ~NSCSCC2023SoC() noexcept;

        unsigned int            GetEventBusId();

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
        unsigned int        eventBusId;

        BaseRAM*            baseRAM;
        ExtRAM*             extRAM;

        SerialInterface*    serial;

    public:
        Builder() noexcept;
        ~Builder() noexcept;

        Builder&                EventBusId(unsigned int eventBusId) noexcept;
        Builder&                BaseDOGGIES(BaseRAM* baseRAM) noexcept;
        Builder&                ExtDOGGIES(ExtRAM* extRAM) noexcept;
        Builder&                Serial(SerialInterface* serial) noexcept;

        unsigned int&           EventBusId() noexcept;
        unsigned int            EventBusId() const noexcept;

        BaseRAM*&               BaseDOGGIES() noexcept;
        const BaseRAM*          BaseDOGGIES() const noexcept;

        ExtRAM*&                ExtDOGGIES() noexcept;
        const ExtRAM*           ExtDOGGIES() const noexcept;

        SerialInterface*&       Serial() noexcept;
        const SerialInterface*  Serial() const noexcept;

        NSCSCC2023SoC*          Build() noexcept;
    };
}


#endif
