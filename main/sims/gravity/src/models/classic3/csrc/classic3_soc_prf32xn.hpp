#pragma once

#ifndef __BULLSEYE_SIMS_GRAVITY__CLASSIC3_SOC_PRF32XN
#define __BULLSEYE_SIMS_GRAVITY__CLASSIC3_SOC_PRF32XN

#include "../../../gravity_modeling.hpp"


namespace Gravity::Classic3 {

    /*
    PRF Read Address (Port A) Wavefront.
    */
    class PRFReadAddressA : public Wavefront<PRFReadAddressA> {
    public:
        uint32_t    address;

    public:
        PRFReadAddressA(Phase& source) noexcept;
        PRFReadAddressA(Phase& source, uint32_t address) noexcept;
    };

    /*
    PRF Read Data (Port A) Wavefront.
    */
    class PRFReadDataA : public Wavefront<PRFReadDataA> {
    public:
        uint32_t    data;

    public:
        PRFReadDataA(Phase& source) noexcept;
        PRFReadDataA(Phase& source, uint32_t data) noexcept;
    };


    /*
    PRF Read Address (Port B) Wavefront.
    */
    class PRFReadAddressB : public Wavefront<PRFReadAddressB> {
    public:
        uint32_t    address;

    public:
        PRFReadAddressB(Phase& source) noexcept;
        PRFReadAddressB(Phase& source, uint32_t address) noexcept;
    };

    /*
    PRF Read Data (Port B) Wavefront.
    */
    class PRFReadDataB : public Wavefront<PRFReadDataB> {
    public:
        uint32_t    data;
    
    public:
        PRFReadDataB(Phase& source) noexcept;
        PRFReadDataB(Phase& source, uint32_t data) noexcept;
    };


    /*
    PRF Write Wavefront.
    */
    class PRFWrite : public Wavefront<PRFWrite> {
    public:
        uint32_t    address;
        bool        enable;
        uint32_t    data;
        uint32_t    bitEnable;

    public:
        PRFWrite(Phase& source) noexcept;
        PRFWrite(Phase& source, uint32_t address, bool enable, uint32_t data, uint32_t bitEnable) noexcept;
    };


    /*
    PRF Payload.
    */
    class PRF32Payload {
    protected:
        uint32_t*   const array;
        size_t      const size;

    public:
        PRF32Payload(size_t sizeInWord) noexcept;
        virtual ~PRF32Payload() noexcept;

    public:
        uint32_t&       operator[](size_t index) noexcept;
        const uint32_t& operator[](size_t index) const noexcept;

        size_t          GetSize() const noexcept;

        uint32_t*       GetArray() noexcept;
        const uint32_t* GetArray() const noexcept;
    };


    /*
    PRF Instance.

    PRF1W2R : PRF 32xN with 1 Write and 2 Read Ports with Clock Synchronized on Posedge & Bit Write Enable.
    */
    class PRF32XN1W2RCPBW : public PRF32Payload, public Phase {
    // wavefront out
    protected:
        GRAVITY_WAVEFRONT_OUT(PRFReadDataA)     readDataA;
        GRAVITY_WAVEFRONT_OUT(PRFReadDataB)     readDataB;

    // wavefront in
    protected:
        GRAVITY_WAVEFRONT_IN(ClockPosedge)      OnClockPosedge(const ClockPosedge& in) noexcept;

        GRAVITY_WAVEFRONT_IN(PRFWrite)          OnWrite(const PRFWrite& in) noexcept;
        GRAVITY_WAVEFRONT_IN(PRFReadAddressA)   OnReadAddressA(const PRFReadAddressA& in) noexcept;
        GRAVITY_WAVEFRONT_IN(PRFReadAddressB)   OnReadAddressB(const PRFReadAddressB& in) noexcept;

    //
    protected:
        const PRFWrite* write;

    //
    public:
        PRF32XN1W2RCPBW(size_t              sizeInWord,
                        DimensionId         inDimension,
                        DimensionId         outDimension) noexcept;

        PRF32XN1W2RCPBW(size_t              sizeInWord,
                        DimensionId         inDimension,
                        DimensionId         outDimension,
                        const std::string&  name) noexcept;

        virtual ~PRF32XN1W2RCPBW() noexcept;
    };
}


#endif // __BULLSEYE_SIMS_GRAVITY__CLASSIC3_SOC_PRF32XN
