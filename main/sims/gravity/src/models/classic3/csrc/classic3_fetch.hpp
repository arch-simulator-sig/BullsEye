#pragma once

#ifndef __BULLSEYE_SIMS_GRAVITY__CLASSIC3_FETCH
#define __BULLSEYE_SIMS_GRAVITY__CLASSIC3_FETCH

#include "../../../gravity_modeling.hpp"

#include "classic3_soc.hpp"


namespace Gravity::Classic3 {

    /*
    Stage 1 of 3 : Fetch Stage (Phase)
    */
    class Fetch : public Phase {
    // wavefront out
    protected:
        GRAVITY_WAVEFRONT_OUT(SRAMReadAddressA) sramReadAddressA;

    // wavefront in
    protected:
        GRAVITY_WAVEFRONT_IN(ClockPosedge)  OnClockPosedge(const ClockPosedge& in) noexcept;
    
        GRAVITY_WAVEFRONT_IN(SRAMReadDataA) OnSRAMReadData(const SRAMReadDataA& in) noexcept;

    public:
        Fetch() noexcept;
        virtual ~Fetch() noexcept;

    protected:
        void            OnClockPosedge(ClockPosedge& in) noexcept;

    public:

    };
}

#endif // __BULLSEYE_SIMS_GRAVITY__CLASSIC3_FETCH
