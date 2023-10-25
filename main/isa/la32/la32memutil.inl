//#include "la32memutil.hpp"
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
// Memory utilities
//

#include <cstring>
#include <cerrno>

#include <algorithm>


// Implementation of: class HarvardMemoryInterface
namespace Jasse {
    //
    // LA32MemoryInterface*    insnMemory;
    // LA32MemoryInterface*    dataMemory;
    //

    inline HarvardMemoryInterface::HarvardMemoryInterface(LA32MemoryInterface* insnMemory,
                                                   LA32MemoryInterface* dataMemory) noexcept
        : insnMemory    (insnMemory)
        , dataMemory    (dataMemory)
    { }

    inline HarvardMemoryInterface::HarvardMemoryInterface(const HarvardMemoryInterface& obj) noexcept
        : insnMemory    (obj.insnMemory)
        , dataMemory    (obj.dataMemory)
    { }

    inline HarvardMemoryInterface::~HarvardMemoryInterface() noexcept
    { }

    inline LA32MemoryInterface* HarvardMemoryInterface::GetInsnMemory() noexcept
    {
        return insnMemory;
    }

    inline LA32MemoryInterface* HarvardMemoryInterface::GetDataMemory() noexcept
    {
        return dataMemory;
    }

    inline void HarvardMemoryInterface::SetInsnMemory(LA32MemoryInterface* memory) noexcept
    {
        this->insnMemory = memory;
    }

    inline void HarvardMemoryInterface::SetDataMemory(LA32MemoryInterface* memory) noexcept
    {
        this->dataMemory = memory;
    }
    
    inline LA32MOPOutcome HarvardMemoryInterface::ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        return this->insnMemory->ReadInsn(address, width, dst);
    }

    inline LA32MOPOutcome HarvardMemoryInterface::ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        return this->dataMemory->ReadData(address, width, dst);
    }

    inline LA32MOPOutcome HarvardMemoryInterface::WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        return this->insnMemory->WriteInsn(address, width, src);
    }

    inline LA32MOPOutcome HarvardMemoryInterface::WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        return this->dataMemory->WriteData(address, width, src);
    }
}


// Implementation of: class PrincetonMemoryInterface
namespace Jasse {
    //
    // LA32MemoryInterface*    memory;
    //

    inline PrincetonMemoryInterface::PrincetonMemoryInterface(LA32MemoryInterface* memory) noexcept
        : memory    (memory)
    { }

    inline PrincetonMemoryInterface::PrincetonMemoryInterface(const PrincetonMemoryInterface& obj) noexcept
        : memory    (obj.memory)
    { }

    inline PrincetonMemoryInterface::~PrincetonMemoryInterface() noexcept
    { }

    inline LA32MemoryInterface* PrincetonMemoryInterface::GetMemory() noexcept
    {
        return this->memory;
    }

    inline void PrincetonMemoryInterface::SetMemory(LA32MemoryInterface* memory) noexcept
    {
        this->memory = memory;
    }

    inline LA32MOPOutcome PrincetonMemoryInterface::ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        return this->memory->ReadInsn(address, width, dst);
    }

    inline LA32MOPOutcome PrincetonMemoryInterface::ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        return this->memory->ReadData(address, width, dst);
    }

    inline LA32MOPOutcome PrincetonMemoryInterface::WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        return this->memory->WriteInsn(address, width, src);
    }

    inline LA32MOPOutcome PrincetonMemoryInterface::WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        return this->memory->WriteData(address, width, src);
    }
}


// Implementation of: class SimpleAlignedMemoryInterface
namespace Jasse {
    //
    // LA32MemoryInterface*  memory;
    //

    inline SimpleAlignedMemoryInterface::SimpleAlignedMemoryInterface(LA32MemoryInterface* memory) noexcept
        : memory    (memory)
    { }

    inline SimpleAlignedMemoryInterface::SimpleAlignedMemoryInterface(const SimpleAlignedMemoryInterface& obj) noexcept
        : memory    (obj.memory)
    { }

    inline SimpleAlignedMemoryInterface::~SimpleAlignedMemoryInterface() noexcept
    { }

    inline LA32MemoryInterface* SimpleAlignedMemoryInterface::GetMemory() noexcept
    {
        return this->memory;
    }

    inline void SimpleAlignedMemoryInterface::SetMemory(LA32MemoryInterface* memory) noexcept
    {
        this->memory = memory;
    }

    inline bool SimpleAlignedMemoryInterface::CheckAlignment(addr_t address, LA32MOPWidth width) noexcept
    {
        return !(address & ((addr_t) width.alignment));
    }

    inline LA32MOPOutcome SimpleAlignedMemoryInterface::ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        if (!CheckAlignment(address, width))
            return { LA32MOPStatus::MOP_ADDRESS_MISALIGNED, ECANCELED };

        return this->memory->ReadInsn(address, width, dst);
    }

    inline LA32MOPOutcome SimpleAlignedMemoryInterface::ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        if (!CheckAlignment(address, width))
            return { LA32MOPStatus::MOP_ADDRESS_MISALIGNED, ECANCELED };

        return this->memory->ReadData(address, width, dst);
    }

    inline LA32MOPOutcome SimpleAlignedMemoryInterface::WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        if (!CheckAlignment(address, width))
            return { LA32MOPStatus::MOP_ADDRESS_MISALIGNED, ECANCELED };

        return this->memory->WriteInsn(address, width, src);
    }

    inline LA32MOPOutcome SimpleAlignedMemoryInterface::WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        if (!CheckAlignment(address, width))
            return { LA32MOPStatus::MOP_ADDRESS_MISALIGNED, ECANCELED };

        return this->memory->WriteData(address, width, src);
    }
}


// Implementation of: class SimpleCircularMemoryInterface
namespace Jasse {
    //
    // addr_t                  cycle;
    // LA32MemoryInterface*    memory;
    //

    inline SimpleCircularMemoryInterface::SimpleCircularMemoryInterface(addr_t cycle, LA32MemoryInterface* memory) noexcept
        : cycle     (cycle)
        , memory    (memory)
    { }

    inline SimpleCircularMemoryInterface::SimpleCircularMemoryInterface(const SimpleCircularMemoryInterface& obj) noexcept
        : cycle     (obj.cycle)
        , memory    (obj.memory)
    { }

    inline SimpleCircularMemoryInterface::~SimpleCircularMemoryInterface()
    { }

    inline addr_t SimpleCircularMemoryInterface::GetCycle() const noexcept
    {
        return this->cycle;
    }

    inline LA32MemoryInterface* SimpleCircularMemoryInterface::GetMemory() noexcept
    {
        return this->memory;
    }

    inline void SimpleCircularMemoryInterface::SetCycle(addr_t cycle) noexcept
    {
        this->cycle = cycle;
    }

    inline void SimpleCircularMemoryInterface::SetMemory(LA32MemoryInterface* memory) noexcept
    {
        this->memory = memory;
    }
    
    inline LA32MOPOutcome SimpleCircularMemoryInterface::ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        return this->memory->ReadInsn(address % cycle, width, dst);
    }

    inline LA32MOPOutcome SimpleCircularMemoryInterface::ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        return this->memory->ReadData(address % cycle, width, dst);
    }

    inline LA32MOPOutcome SimpleCircularMemoryInterface::WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        return this->memory->WriteInsn(address % cycle, width, src);
    }

    inline LA32MOPOutcome SimpleCircularMemoryInterface::WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        return this->memory->WriteData(address % cycle, width, src);
    }
}


// Implementation of: class SimpleLinearMemory
namespace Jasse {
    //
    // const size_t    size;
    // arch32_t*       heap;
    //
    // errno_t         last_error;
    //

    inline SimpleLinearMemory::SimpleLinearMemory(size_t size)
        : size          (size)
        , heap          (new arch32_t[size])
    { }

    inline SimpleLinearMemory::SimpleLinearMemory(const SimpleLinearMemory& obj)
        : size          (obj.size)
        , heap          (new arch32_t[obj.size])
    { 
        std::copy(obj.heap, obj.heap + obj.size, heap);
    }

    inline SimpleLinearMemory::~SimpleLinearMemory()
    {
        delete[] heap;
    }

    inline arch32_t* SimpleLinearMemory::GetHeap() noexcept
    {
        return heap;
    }

    inline const arch32_t* SimpleLinearMemory::GetHeap() const noexcept
    {
        return heap;
    }

    inline size_t SimpleLinearMemory::GetHeapSize() const noexcept
    {
        return size;
    }

    inline size_t SimpleLinearMemory::GetHeapCapacity() const noexcept
    {
        return size * sizeof(arch32_t);
    }

    inline bool SimpleLinearMemory::CheckWidth(LA32MOPWidth width) const noexcept
    {
        return !(width.length > 4);
    }

    inline bool SimpleLinearMemory::CheckBound(addr_t address, LA32MOPWidth width) const noexcept
    {
        return !(address + width.length > GetHeapCapacity());
    }

    inline LA32MOPOutcome SimpleLinearMemory::__Read_Unchecked(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        std::memmove(dst, ((uint8_t*) heap) + address, width.length);
        return { LA32MOPStatus::MOP_SUCCESS };
    }

    inline LA32MOPOutcome SimpleLinearMemory::ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        if (CheckWidth(width) && CheckBound(address, width))
            return __Read_Unchecked(address, width, dst);

        return { LA32MOPStatus::MOP_ACCESS_FAULT, ECANCELED };
    }

    inline LA32MOPOutcome SimpleLinearMemory::ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept
    {
        if (CheckWidth(width) && CheckBound(address, width))
            return __Read_Unchecked(address, width, dst);

        return { LA32MOPStatus::MOP_ACCESS_FAULT, ECANCELED };
    }

    inline LA32MOPOutcome SimpleLinearMemory::__Write_Unchecked(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        std::memmove(((uint8_t*) heap) + address, &src, width.length);
        return { LA32MOPStatus::MOP_SUCCESS };
    }

    inline LA32MOPOutcome SimpleLinearMemory::WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        if (CheckWidth(width) && CheckBound(address, width))
            return __Write_Unchecked(address, width, src);

        return { LA32MOPStatus::MOP_ACCESS_FAULT, ECANCELED };
    }

    inline LA32MOPOutcome SimpleLinearMemory::WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept
    {
        if (CheckWidth(width) && CheckBound(address, width))
            return __Write_Unchecked(address, width, src);

        return { LA32MOPStatus::MOP_ACCESS_FAULT, ECANCELED };
    }
}
