#pragma once

#ifndef __HEADER_DS232__CORE_DEF
#define __HEADER_DS232__CORE_DEF

#include <bitset>


#include "autoinclude.h"

#include AUTOINC_BE_COMMON(nonstdint.hpp)


namespace BullsEye::Draconids3014 {

    // Type definition of FID
    typedef uint8_t             fid_t;


    // Type definition of Load/Store Width
    typedef uint2_t             lswidth_t;

    static constexpr lswidth_t  LSWIDTH_BYTE        = 0b00;
    static constexpr lswidth_t  LSWIDTH_HALF_WORD   = 0b01;
    static constexpr lswidth_t  LSWIDTH_WORD        = 0b10;
    static constexpr lswidth_t  LSWIDTH_DOUBLE_WORD = 0b11;


    // Type definition of Load/Store Strobe
    typedef std::bitset<4>      lsstrb_t;
}

#endif
