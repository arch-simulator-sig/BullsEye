#include "la32mem.hpp"
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
// Memory interface infrastructure
//


#include <cerrno>


// Implementation of: struct LA32MOPWidth
namespace Jasse {

    bool operator==(const LA32MOPWidth& lhs, const LA32MOPWidth& rhs) noexcept
    {
        return lhs.mask == rhs.mask && lhs.alignment == rhs.alignment && lhs.length == rhs.length;
    }

    bool operator!=(const LA32MOPWidth& lhs, const LA32MOPWidth& rhs) noexcept
    {
        return !(lhs == rhs);
    }
}


// Implementation of: union memdata_t
namespace Jasse {

    memdata_t::operator uint32_t() const noexcept
    {
        return data32;
    }

    memdata_t::operator uint16_t() const noexcept
    {
        return data16;
    }

    memdata_t::operator uint8_t() const noexcept
    {
        return data8;
    }

    memdata_t::operator int32_t() const noexcept
    {
        return data32;
    }

    memdata_t::operator int16_t() const noexcept
    {
        return data16;
    }

    memdata_t::operator int8_t() const noexcept
    {
        return data8;
    }

    uint32_t memdata_t::As(LA32MOPWidth width) const noexcept
    {
        switch (width.length) 
        {
            case 1:
                return data8;

            case 2:
                return data16;

            case 4:
                return data32;

            [[unlikely]] default:
                return data32;
        }
    }
}


// Implementation of: class LA32MemoryInterface
namespace Jasse {

    LA32MOPOutcome LA32MemoryInterface::Read(LA32MOPPath path, addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        switch (path) 
        {
            case LA32MOPPath::MOP_INSN:
                return ReadInsn(address, width, dst);

            case LA32MOPPath::MOP_DATA:
                return ReadData(address, width, dst);

            [[unlikely]] default:
                return { LA32MOPStatus::MOP_INVALID_PATH, ENOSYS };
        }
    }

    LA32MOPOutcome LA32MemoryInterface::Write(LA32MOPPath path, addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        switch (path) 
        {
            case LA32MOPPath::MOP_INSN:
                return WriteInsn(address, width, src);

            case LA32MOPPath::MOP_DATA:
                return WriteData(address, width, src);

            [[unlikely]] default:
                return { LA32MOPStatus::MOP_INVALID_PATH, ENOSYS };
        }
    }
}
