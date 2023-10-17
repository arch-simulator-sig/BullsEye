#include "memory.hpp"
//
//


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

    LA32MOPOutcome Memory4MB::ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        return mem.ReadInsn(address, width, dst);
    }

    LA32MOPOutcome Memory4MB::ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        return mem.ReadData(address, width, dst);
    }

    LA32MOPOutcome Memory4MB::WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        return mem.WriteInsn(address, width, src);
    }

    LA32MOPOutcome Memory4MB::WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        return mem.WriteData(address, width, src);
    }
}
