#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// Memory utilities
//

#include <algorithm>

#include "base/mips32mem.hpp"


namespace Jasse {

    // Harvard Architecture Memory Interface
    class HarvardMemoryInterface : public MIPS32MemoryInterface {
    private:
        MIPS32MemoryInterface*  insnMemory;
        MIPS32MemoryInterface*  dataMemory;

    public:
        HarvardMemoryInterface(MIPS32MemoryInterface* insnMemory, MIPS32MemoryInterface* dataMemory) noexcept;
        HarvardMemoryInterface(const HarvardMemoryInterface& obj) noexcept;
        virtual ~HarvardMemoryInterface() noexcept;

        MIPS32MemoryInterface*      GetInsnMemory() noexcept;
        MIPS32MemoryInterface*      GetDataMemory() noexcept;

        void                        SetInsnMemory(MIPS32MemoryInterface* insnMemory) noexcept;
        void                        SetDataMemory(MIPS32MemoryInterface* dataMemory) noexcept;

        virtual MIPS32MOPOutcome    ReadInsn(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept override;
        virtual MIPS32MOPOutcome    ReadData(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept override;

        virtual MIPS32MOPOutcome    WriteInsn(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept override;
        virtual MIPS32MOPOutcome    WriteData(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept override;
    };

    // Princeton Architecture Memory Interface
    class PrincetonMemoryInterface : public MIPS32MemoryInterface {
    private:
        MIPS32MemoryInterface*  memory;

    public:
        PrincetonMemoryInterface(MIPS32MemoryInterface* memory) noexcept;
        PrincetonMemoryInterface(const PrincetonMemoryInterface& obj) noexcept;
        virtual ~PrincetonMemoryInterface() noexcept;

        MIPS32MemoryInterface*      GetMemory() noexcept;

        void                        SetMemory(MIPS32MemoryInterface* memory) noexcept;

        virtual MIPS32MOPOutcome    ReadInsn(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept override;
        virtual MIPS32MOPOutcome    ReadData(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept override;

        virtual MIPS32MOPOutcome    WriteInsn(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept override;
        virtual MIPS32MOPOutcome    WriteData(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept override;
    };


    // Simple Aligned Memory Interface
    class SimpleAlignedMemoryInterface : public MIPS32MemoryInterface {
    private:
        MIPS32MemoryInterface*  memory;

    public:
        SimpleAlignedMemoryInterface(MIPS32MemoryInterface* memory) noexcept;
        SimpleAlignedMemoryInterface(const SimpleAlignedMemoryInterface& obj) noexcept;
        virtual ~SimpleAlignedMemoryInterface() noexcept;
        
        MIPS32MemoryInterface*      GetMemory() noexcept;

        void                        SetMemory(MIPS32MemoryInterface* memory) noexcept;
        
        bool                        CheckAlignment(addr_t address, MIPS32MOPWidth width) noexcept;

        virtual MIPS32MOPOutcome    ReadInsn(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept override;
        virtual MIPS32MOPOutcome    ReadData(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept override;

        virtual MIPS32MOPOutcome    WriteInsn(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept override;
        virtual MIPS32MOPOutcome    WriteData(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept override;
    };

    // Simple Circular Memory Interface
    class SimpleCircularMemoryInterface : public MIPS32MemoryInterface {
    private:
        addr_t                  cycle;
        MIPS32MemoryInterface*  memory;

    public:
        SimpleCircularMemoryInterface(addr_t cycle, MIPS32MemoryInterface* memory) noexcept;
        SimpleCircularMemoryInterface(const SimpleCircularMemoryInterface& obj) noexcept;
        virtual ~SimpleCircularMemoryInterface() noexcept;

        addr_t                      GetCycle() const noexcept;
        MIPS32MemoryInterface*      GetMemory() noexcept;

        void                        SetCycle(addr_t cycle) noexcept;
        void                        SetMemory(MIPS32MemoryInterface* memory) noexcept;

        virtual MIPS32MOPOutcome    ReadInsn(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept override;
        virtual MIPS32MOPOutcome    ReadData(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept override;

        virtual MIPS32MOPOutcome    WriteInsn(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept override;
        virtual MIPS32MOPOutcome    WriteData(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept override;
    };


    // Simple Linear Memory Interface
    class SimpleLinearMemory : public MIPS32MemoryInterface {
    private:
        const size_t    size;
        arch32_t*       heap;

    protected:
        MIPS32MOPOutcome            __Read_Unchecked(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept;
        MIPS32MOPOutcome            __Write_Unchecked(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept;

    public:
        SimpleLinearMemory(size_t size);
        SimpleLinearMemory(const SimpleLinearMemory& obj);
        virtual ~SimpleLinearMemory();

        arch32_t*                   GetHeap() noexcept;
        const arch32_t*             GetHeap() const noexcept;
        size_t                      GetHeapSize() const noexcept;
        size_t                      GetHeapCapacity() const noexcept;

        bool                        CheckWidth(MIPS32MOPWidth width) const noexcept;
        bool                        CheckBound(addr_t address, MIPS32MOPWidth width) const noexcept;

        virtual MIPS32MOPOutcome    ReadInsn(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept override;
        virtual MIPS32MOPOutcome    ReadData(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept override;

        virtual MIPS32MOPOutcome    WriteInsn(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept override;
        virtual MIPS32MOPOutcome    WriteData(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept override;
    };
}



// Implementation of: class HarvardMemoryInterface
namespace Jasse {
    //
    // MIPS32MemoryInterface*  insnMemory;
    // MIPS32MemoryInterface*  dataMemory;
    //

    HarvardMemoryInterface::HarvardMemoryInterface(MIPS32MemoryInterface* insnMemory,
                                                   MIPS32MemoryInterface* dataMemory) noexcept
        : insnMemory    (insnMemory)
        , dataMemory    (dataMemory)
    { }

    HarvardMemoryInterface::HarvardMemoryInterface(const HarvardMemoryInterface& obj) noexcept
        : insnMemory    (obj.insnMemory)
        , dataMemory    (obj.dataMemory)
    { }

    HarvardMemoryInterface::~HarvardMemoryInterface() noexcept
    { }

    inline MIPS32MemoryInterface* HarvardMemoryInterface::GetInsnMemory() noexcept
    {
        return insnMemory;
    }

    inline MIPS32MemoryInterface* HarvardMemoryInterface::GetDataMemory() noexcept
    {
        return dataMemory;
    }

    inline void HarvardMemoryInterface::SetInsnMemory(MIPS32MemoryInterface* memory) noexcept
    {
        this->insnMemory = memory;
    }

    inline void HarvardMemoryInterface::SetDataMemory(MIPS32MemoryInterface* memory) noexcept
    {
        this->dataMemory = memory;
    }
    
    MIPS32MOPOutcome HarvardMemoryInterface::ReadInsn(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept
    {
        return this->insnMemory->ReadInsn(address, width, dst);
    }

    MIPS32MOPOutcome HarvardMemoryInterface::ReadData(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept
    {
        return this->dataMemory->ReadData(address, width, dst);
    }

    MIPS32MOPOutcome HarvardMemoryInterface::WriteInsn(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept
    {
        return this->insnMemory->WriteInsn(address, width, src);
    }

    MIPS32MOPOutcome HarvardMemoryInterface::WriteData(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept
    {
        return this->dataMemory->WriteData(address, width, src);
    }
}


// Implementation of: class PrincetonMemoryInterface
namespace Jasse {
    //
    // MIPS32MemoryInterface*  memory;
    //

    PrincetonMemoryInterface::PrincetonMemoryInterface(MIPS32MemoryInterface* memory) noexcept
        : memory    (memory)
    { }

    PrincetonMemoryInterface::PrincetonMemoryInterface(const PrincetonMemoryInterface& obj) noexcept
        : memory    (obj.memory)
    { }

    PrincetonMemoryInterface::~PrincetonMemoryInterface() noexcept
    { }

    inline MIPS32MemoryInterface* PrincetonMemoryInterface::GetMemory() noexcept
    {
        return this->memory;
    }

    inline void PrincetonMemoryInterface::SetMemory(MIPS32MemoryInterface* memory) noexcept
    {
        this->memory = memory;
    }

    MIPS32MOPOutcome PrincetonMemoryInterface::ReadInsn(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept
    {
        return this->memory->ReadInsn(address, width, dst);
    }

    MIPS32MOPOutcome PrincetonMemoryInterface::ReadData(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept
    {
        return this->memory->ReadData(address, width, dst);
    }

    MIPS32MOPOutcome PrincetonMemoryInterface::WriteInsn(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept
    {
        return this->memory->WriteInsn(address, width, src);
    }

    MIPS32MOPOutcome PrincetonMemoryInterface::WriteData(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept
    {
        return this->memory->WriteData(address, width, src);
    }
}


// Implementation of: class SimpleAlignedMemoryInterface
namespace Jasse {
    //
    // MIPS32MemoryInterface*  memory;
    //

    SimpleAlignedMemoryInterface::SimpleAlignedMemoryInterface(MIPS32MemoryInterface* memory) noexcept
        : memory    (memory)
    { }

    SimpleAlignedMemoryInterface::SimpleAlignedMemoryInterface(const SimpleAlignedMemoryInterface& obj) noexcept
        : memory    (obj.memory)
    { }

    SimpleAlignedMemoryInterface::~SimpleAlignedMemoryInterface() noexcept
    { }

    inline MIPS32MemoryInterface* SimpleAlignedMemoryInterface::GetMemory() noexcept
    {
        return this->memory;
    }

    inline void SimpleAlignedMemoryInterface::SetMemory(MIPS32MemoryInterface* memory) noexcept
    {
        this->memory = memory;
    }

    inline bool SimpleAlignedMemoryInterface::CheckAlignment(addr_t address, MIPS32MOPWidth width) noexcept
    {
        return !(address & ((addr_t) width.alignment));
    }

    MIPS32MOPOutcome SimpleAlignedMemoryInterface::ReadInsn(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept
    {
        if (!CheckAlignment(address, width))
            return { MOP_ADDRESS_MISALIGNED, ECANCELED };

        return this->memory->ReadInsn(address, width, dst);
    }

    MIPS32MOPOutcome SimpleAlignedMemoryInterface::ReadData(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept
    {
        if (!CheckAlignment(address, width))
            return { MOP_ADDRESS_MISALIGNED, ECANCELED };

        return this->memory->ReadData(address, width, dst);
    }

    MIPS32MOPOutcome SimpleAlignedMemoryInterface::WriteInsn(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept
    {
        if (!CheckAlignment(address, width))
            return { MOP_ADDRESS_MISALIGNED, ECANCELED };

        return this->memory->WriteInsn(address, width, src);
    }

    MIPS32MOPOutcome SimpleAlignedMemoryInterface::WriteData(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept
    {
        if (!CheckAlignment(address, width))
            return { MOP_ADDRESS_MISALIGNED, ECANCELED };

        return this->memory->WriteData(address, width, src);
    }
}


// Implementation of: class SimpleCircularMemoryInterface
namespace Jasse {
    //
    // addr_t                  cycle;
    // MIPS32MemoryInterface*  memory;
    //

    SimpleCircularMemoryInterface::SimpleCircularMemoryInterface(addr_t cycle, MIPS32MemoryInterface* memory) noexcept
        : cycle     (cycle)
        , memory    (memory)
    { }

    SimpleCircularMemoryInterface::SimpleCircularMemoryInterface(const SimpleCircularMemoryInterface& obj) noexcept
        : cycle     (obj.cycle)
        , memory    (obj.memory)
    { }

    SimpleCircularMemoryInterface::~SimpleCircularMemoryInterface()
    { }

    inline addr_t SimpleCircularMemoryInterface::GetCycle() const noexcept
    {
        return this->cycle;
    }

    inline MIPS32MemoryInterface* SimpleCircularMemoryInterface::GetMemory() noexcept
    {
        return this->memory;
    }

    inline void SimpleCircularMemoryInterface::SetCycle(addr_t cycle) noexcept
    {
        this->cycle = cycle;
    }

    inline void SimpleCircularMemoryInterface::SetMemory(MIPS32MemoryInterface* memory) noexcept
    {
        this->memory = memory;
    }
    
    MIPS32MOPOutcome SimpleCircularMemoryInterface::ReadInsn(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept
    {
        return this->memory->ReadInsn(address % cycle, width, dst);
    }

    MIPS32MOPOutcome SimpleCircularMemoryInterface::ReadData(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept
    {
        return this->memory->ReadData(address % cycle, width, dst);
    }

    MIPS32MOPOutcome SimpleCircularMemoryInterface::WriteInsn(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept
    {
        return this->memory->WriteInsn(address % cycle, width, src);
    }

    MIPS32MOPOutcome SimpleCircularMemoryInterface::WriteData(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept
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

    SimpleLinearMemory::SimpleLinearMemory(size_t size)
        : size          (size)
        , heap          (new arch32_t[size])
    { }

    SimpleLinearMemory::SimpleLinearMemory(const SimpleLinearMemory& obj)
        : size          (obj.size)
        , heap          (new arch32_t[obj.size])
    { 
        std::copy(obj.heap, obj.heap + obj.size, heap);
    }

    SimpleLinearMemory::~SimpleLinearMemory()
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

    inline bool SimpleLinearMemory::CheckWidth(MIPS32MOPWidth width) const noexcept
    {
        return !(width.length > 4);
    }

    inline bool SimpleLinearMemory::CheckBound(addr_t address, MIPS32MOPWidth width) const noexcept
    {
        return !(address + width.length > GetHeapCapacity());
    }

    inline MIPS32MOPOutcome SimpleLinearMemory::__Read_Unchecked(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept
    {
        std::memmove(dst, ((uint8_t*) heap) + address, width.length);
        return { MOP_SUCCESS };
    }

    MIPS32MOPOutcome SimpleLinearMemory::ReadInsn(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept
    {
        if (CheckWidth(width) && CheckBound(address, width))
            return __Read_Unchecked(address, width, dst);

        return { MOP_ACCESS_FAULT, ECANCELED };
    }

    MIPS32MOPOutcome SimpleLinearMemory::ReadData(addr_t address, MIPS32MOPWidth width, memdata_t* dst) noexcept
    {
        if (CheckWidth(width) && CheckBound(address, width))
            return __Read_Unchecked(address, width, dst);

        return { MOP_ACCESS_FAULT, ECANCELED };
    }

    inline MIPS32MOPOutcome SimpleLinearMemory::__Write_Unchecked(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept
    {
        std::memmove(((uint8_t*) heap) + address, &src, width.length);
        return { MOP_SUCCESS };
    }

    MIPS32MOPOutcome SimpleLinearMemory::WriteInsn(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept
    {
        if (CheckWidth(width) && CheckBound(address, width))
            return __Write_Unchecked(address, width, src);

        return { MOP_ACCESS_FAULT, ECANCELED };
    }

    MIPS32MOPOutcome SimpleLinearMemory::WriteData(addr_t address, MIPS32MOPWidth width, memdata_t src) noexcept
    {
        if (CheckWidth(width) && CheckBound(address, width))
            return __Write_Unchecked(address, width, src);

        return { MOP_ACCESS_FAULT, ECANCELED };
    }
}
