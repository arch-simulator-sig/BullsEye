#include "la32mem.hpp"
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
// Memory interface infrastructure
//


// Implementation of: struct LA32MOPWidth
namespace Jasse {

    inline bool operator==(const LA32MOPWidth& lhs, const LA32MOPWidth& rhs) noexcept
    {
        return lhs.mask == rhs.mask && lhs.alignment == rhs.alignment && lhs.length == rhs.length;
    }

    inline bool operator!=(const LA32MOPWidth& lhs, const LA32MOPWidth& rhs) noexcept
    {
        return !(lhs == rhs);
    }
}


// Implementation of: union memdata_t
namespace Jasse {

    inline memdata_t::operator uint32_t() const noexcept
    {
        return data32;
    }

    inline memdata_t::operator uint16_t() const noexcept
    {
        return data16;
    }

    inline memdata_t::operator uint8_t() const noexcept
    {
        return data8;
    }

    inline memdata_t::operator int32_t() const noexcept
    {
        return data32;
    }

    inline memdata_t::operator int16_t() const noexcept
    {
        return data16;
    }

    inline memdata_t::operator int8_t() const noexcept
    {
        return data8;
    }
}
