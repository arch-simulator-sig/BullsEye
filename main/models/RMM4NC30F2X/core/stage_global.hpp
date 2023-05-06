#pragma once
//
// Stage Global models for RMM4NC30F2X (Gemini 30F2)
//
//
//

#include <cstdint>

#include "common/nonstdint.hpp"


#include "def_global.hpp"


namespace BullsEye::Gemini30F2::Global {

    class VPAddressConvertion {
    public:
        struct PhysicalAddressBundle {
            Global::PhysicalAddress paddr;
            bool                    kseg1;
        };

    public:
        VPAddressConvertion() noexcept;
        ~VPAddressConvertion() noexcept;

        PhysicalAddressBundle   Comb(Global::VirtualAddress vaddr) const noexcept;
    };
}


// Implementation of: class VPAddressConvertion
namespace BullsEye::Gemini30F2::Global {

    inline VPAddressConvertion::VPAddressConvertion() noexcept
    { }

    inline VPAddressConvertion::~VPAddressConvertion() noexcept
    { }

    inline VPAddressConvertion::PhysicalAddressBundle VPAddressConvertion::Comb(Global::VirtualAddress vaddr) const noexcept
    {
        PhysicalAddressBundle result;

        result.paddr = vaddr & 0x1FFFFFFF;
        result.kseg1 = ((vaddr & 0xE0000000) == 0xA0000000) || ((vaddr & 0xE0000000) == 0xB0000000);

        return result;
    }
}
