#pragma once
//
//

#ifndef __HEADER_BULLSEYE_NSCSCC2023_LA32_SOC__MEMORY
#define __HEADER_BULLSEYE_NSCSCC2023_LA32_SOC__MEMORY


#include "autoinclude.h"

#include AUTOINC_BE_JASSE2_LA32(la32.hpp)
#include AUTOINC_BE_JASSE2_LA32(la32memutil.hpp)


using namespace Jasse;

namespace BullsEye::NSCSCCSingle {
    
    // 32b Aligned 4MB On-board Memory
    class Memory4MB : public LA32MemoryInterface {
    private:
        SimpleAlignedMemoryInterface    mem;

    public:
        Memory4MB() noexcept;
        virtual ~Memory4MB() noexcept;

        virtual LA32MOPOutcome      ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept override;
        virtual LA32MOPOutcome      ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept override;

        virtual LA32MOPOutcome      WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept override;
        virtual LA32MOPOutcome      WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept override;
    };

    
    // 4MB BaseRAM
    using BaseRAM   = Memory4MB;

    // 4MB ExtRAM
    using ExtRAM    = Memory4MB;
}


#endif
