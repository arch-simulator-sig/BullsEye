#pragma once

#ifndef __BULLSEYE_SIMS_GRAVITY__CLASSIC3_SOC
#define __BULLSEYE_SIMS_GRAVITY__CLASSIC3_SOC


#include <cstdint>

#include "../../../gravity_modeling.hpp"


namespace Gravity::Classic3 {

    /*
    SRAM Read Address (Port A) Wavefront.
    */
    class SRAMReadAddressA : public Wavefront<SRAMReadAddressA> {
    public:
        uint32_t    address;
        bool        enable;

    public:
        SRAMReadAddressA(Phase& source) noexcept;
    };

    /*
    SRAM Read Data (Port A) Wavefront.
    */
    class SRAMReadDataA : public Wavefront<SRAMReadDataA> {
    public:
        uint32_t    data;

    public:
        SRAMReadDataA(Phase& source) noexcept;
    };


    /*
    SRAM Read Address (Port B) Wavefront.
    */
    class SRAMReadAddressB : public Wavefront<SRAMReadAddressB> {
    public:
        uint32_t    address;
        bool        enable;

    public:
        SRAMReadAddressB(Phase& source) noexcept;
    };

    /*
    SRAM Read Data (Port B) Wavefront.
    */
    class SRAMReadDataB : public Wavefront<SRAMReadDataB> {
    public:
        uint32_t    data;

    public:
        SRAMReadDataB(Phase& source) noexcept;
    };


    /*
    SRAM Write Wavefront.
    */
    class SRAMWrite : public Wavefront<SRAMWrite> {
    public:
        uint32_t    address;
        bool        enable;
        uint32_t    data;
        uint32_t    bitEnable;

    public:
        SRAMWrite(Phase& source) noexcept;
    };


    /*
    SRAM Payload.
    */
    class SRAM32Payload {
    protected:
        uint32_t* const array;
        size_t    const size;

    public:
        SRAM32Payload(size_t sizeInWord) noexcept;
        virtual ~SRAM32Payload() noexcept;

    public:
        uint32_t&       operator[](size_t index) noexcept;
        const uint32_t& operator[](size_t index) const noexcept;

        size_t          GetSize() const noexcept;

        uint32_t*       GetArray() noexcept;
        const uint32_t* GetArray() const noexcept;
    };


    /*
    SRAM Instance.

    SRAM1W2RCP : SRAM 32xN with 1 Write and 2 Read Ports with Clock Synchronized on Posedge & Bit Write Enable.
    */
    class SRAM32XN1W2RCPBW : public SRAM32Payload, public Phase {
    // wavefront out
    protected:
        GRAVITY_WAVEFRONT_OUT(SRAMReadDataA)    readDataA;
        GRAVITY_WAVEFRONT_OUT(SRAMReadDataB)    readDataB;

    // wavefront in
    protected:
        GRAVITY_WAVEFRONT_IN(ClockPosedge)      OnClockPosedge(const ClockPosedge& in) noexcept;

        GRAVITY_WAVEFRONT_IN(SRAMWrite)         OnSRAMWrite(const SRAMWrite& in) noexcept;
        GRAVITY_WAVEFRONT_IN(SRAMReadAddressA)  OnSRAMReadAddressA(const SRAMReadAddressA& in) noexcept;
        GRAVITY_WAVEFRONT_IN(SRAMReadAddressB)  OnSRAMReadAddressB(const SRAMReadAddressB& in) noexcept;

    //
    protected:
        const SRAMWrite*            write;
        const SRAMReadAddressA*     readAddressA;
        const SRAMReadAddressB*     readAddressB;

    //
    public:
        SRAM32XN1W2RCPBW(size_t             sizeInWord,
                         DimensionId          inDimension, 
                         DimensionId          outDimension) noexcept;

        SRAM32XN1W2RCPBW(size_t             sizeInWord, 
                         DimensionId          inDimension, 
                         DimensionId          outDimension, 
                         const std::string& name) noexcept;

        virtual ~SRAM32XN1W2RCPBW() noexcept;
    };
}


#endif // __BULLSEYE_SIMS_GRAVITY__CLASSIC3_SOC
