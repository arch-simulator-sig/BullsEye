#pragma once
//
// Core global definitions
//
//

#include <cstdint>

#include "common/nonstdint.hpp"

#include "models/util/mips32def.hpp"
#include "models/util/mips32helper.hpp"


#define FETCH_PREDECODED_NORMAL           0b0000

#define FETCH_PREDECODED_BRANCH           0b0100
#define FETCH_PREDECODED_JUMP             0b0010
#define FETCH_PREDECODED_JUMP_LINK        0b0011


// Type definitions
namespace BullsEye::Gemini30F2::Global {


    using VirtualAddress            = uint32_t;

    using PhysicalAddress           = uint32_t;


    using FID                       = uint8_t;

    using RawInstruction            = uint32_t;

    struct _PredecodedInstruction {
        RawInstruction  insn;
        uint4_t         tag;

        inline constexpr operator uint36_t() const noexcept
        {
            return ((uint64_t) insn) | (((uint64_t) tag) << 32);
        }
    };

    using PredecodedInstruction     = _PredecodedInstruction;

    using PC                        = pc_t;


    using ArchitecturalRegisterIndex    = uint5_t;

    using ArchitecturalRegisterValue    = uint32_t;
}


// Value configurations
namespace BullsEye::Gemini30F2::Global {

    static constexpr PC     START_UP_PC     = 0x80000000;
}
