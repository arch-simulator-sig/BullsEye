#pragma once
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
// Memory interface infrastructure
//

#include <cstdint>
#include <cerrno>

#include "la32def.hpp"


namespace Jasse {

    // Type definition of Memory Address (32 bits unified)
    typedef     uint32_t        addr32_t;

    typedef     addr32_t        addr_t;

    // LA32 Memory Operation Status
    typedef enum class __tag_LA32MOPStatus {
        MOP_SUCCESS = 0,
        MOP_ADDRESS_MISALIGNED,
        MOP_ACCESS_FAULT,
        MOP_EMULATION_FAULT,
        MOP_SYSTEM_ERROR,
        MOP_DEVICE_ERROR
    } LA32MOPStatus;

    // LA32 Memory Operation Outcome
    typedef struct {
        LA32MOPStatus status;
        errno_t         error = 0;
    } LA32MOPOutcome;

    // LA32 Memory Operation Width
    typedef struct {
        uint32_t    mask;
        uint16_t    alignment;
        uint16_t    length;
    } LA32MOPWidth;

    bool operator==(const LA32MOPWidth& lhs, const LA32MOPWidth& rhs) noexcept;
    bool operator!=(const LA32MOPWidth& lhs, const LA32MOPWidth& rhs) noexcept;

    static constexpr LA32MOPWidth MOPW_BYTE           = { 0x000000FFU, 0x00U, 1 };
    static constexpr LA32MOPWidth MOPW_HALF_WORD      = { 0x0000FFFFU, 0x01U, 2 };
    static constexpr LA32MOPWidth MOPW_WORD           = { 0xFFFFFFFFU, 0x03U, 4 };


    // Type definition of LA32 Memory Data
    typedef union {
        uint32_t    data32;     // word
        uint16_t    data16;     // half-word
        uint8_t     data8;      // byte

        explicit operator uint32_t() const noexcept;
        explicit operator uint16_t() const noexcept;
        explicit operator uint8_t() const noexcept;

        explicit operator int32_t() const noexcept;
        explicit operator int16_t() const noexcept;
        explicit operator int8_t() const noexcept;
    } memdata_t;

    // LA32 Memory Interface
    class LA32MemoryInterface {
    public:
        virtual ~LA32MemoryInterface() noexcept {};

        virtual LA32MOPOutcome    ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept = 0;
        virtual LA32MOPOutcome    ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept = 0;

        virtual LA32MOPOutcome    WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept = 0;
        virtual LA32MOPOutcome    WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept = 0;
    };
}


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
