#pragma once
//
//

#include "isa/la32/la32.hpp"
#include "isa/la32/la32memutil.hpp"


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


// Implementation of: class Memory4MB
namespace BullsEye::NSCSCCSingle {
    //
    // SimpleAlignedMemoryInterface    mem;
    //

    Memory4MB::Memory4MB() noexcept
        : mem   (new SimpleLinearMemory(1024 * 1024))
    { }

    Memory4MB::~Memory4MB() noexcept
    { 
        delete mem.GetMemory();
    }

    inline LA32MOPOutcome Memory4MB::ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        return mem.ReadInsn(address, width, dst);
    }

    inline LA32MOPOutcome Memory4MB::ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        return mem.ReadData(address, width, dst);
    }

    inline LA32MOPOutcome Memory4MB::WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        return mem.WriteInsn(address, width, src);
    }

    inline LA32MOPOutcome Memory4MB::WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        return mem.WriteData(address, width, src);
    }
}
