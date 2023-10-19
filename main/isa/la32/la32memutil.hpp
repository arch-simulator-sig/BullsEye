#pragma once
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
// Memory utilities
//


#ifndef __HEADER_JASSE_LA32_MEMUTIL
#define __HEADER_JASSE_LA32_MEMUTIL


#include <algorithm>

#include "base/la32mem.hpp"


namespace Jasse {

    // Harvard Architecture Memory Interface
    class HarvardMemoryInterface : public LA32MemoryInterface {
    private:
        LA32MemoryInterface*    insnMemory;
        LA32MemoryInterface*    dataMemory;

    public:
        HarvardMemoryInterface(LA32MemoryInterface* insnMemory, LA32MemoryInterface* dataMemory) noexcept;
        HarvardMemoryInterface(const HarvardMemoryInterface& obj) noexcept;
        virtual ~HarvardMemoryInterface() noexcept;

        LA32MemoryInterface*        GetInsnMemory() noexcept;
        LA32MemoryInterface*        GetDataMemory() noexcept;

        void                        SetInsnMemory(LA32MemoryInterface* insnMemory) noexcept;
        void                        SetDataMemory(LA32MemoryInterface* dataMemory) noexcept;

        virtual LA32MOPOutcome      ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept override;
        virtual LA32MOPOutcome      ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept override;

        virtual LA32MOPOutcome      WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept override;
        virtual LA32MOPOutcome      WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept override;
    };

    // Princeton Architecture Memory Interface
    class PrincetonMemoryInterface : public LA32MemoryInterface {
    private:
        LA32MemoryInterface*    memory;

    public:
        PrincetonMemoryInterface(LA32MemoryInterface* memory) noexcept;
        PrincetonMemoryInterface(const PrincetonMemoryInterface& obj) noexcept;
        virtual ~PrincetonMemoryInterface() noexcept;

        LA32MemoryInterface*        GetMemory() noexcept;

        void                        SetMemory(LA32MemoryInterface* memory) noexcept;

        virtual LA32MOPOutcome      ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept override;
        virtual LA32MOPOutcome      ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept override;

        virtual LA32MOPOutcome      WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept override;
        virtual LA32MOPOutcome      WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept override;
    };


    // Simple Aligned Memory Interface
    class SimpleAlignedMemoryInterface : public LA32MemoryInterface {
    private:
        LA32MemoryInterface*    memory;

    public:
        SimpleAlignedMemoryInterface(LA32MemoryInterface* memory) noexcept;
        SimpleAlignedMemoryInterface(const SimpleAlignedMemoryInterface& obj) noexcept;
        virtual ~SimpleAlignedMemoryInterface() noexcept;
        
        LA32MemoryInterface*        GetMemory() noexcept;

        void                        SetMemory(LA32MemoryInterface* memory) noexcept;
        
        bool                        CheckAlignment(addr_t address, LA32MOPWidth width) noexcept;

        virtual LA32MOPOutcome      ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept override;
        virtual LA32MOPOutcome      ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept override;

        virtual LA32MOPOutcome      WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept override;
        virtual LA32MOPOutcome      WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept override;
    };

    // Simple Circular Memory Interface
    class SimpleCircularMemoryInterface : public LA32MemoryInterface {
    private:
        addr_t                  cycle;
        LA32MemoryInterface*    memory;

    public:
        SimpleCircularMemoryInterface(addr_t cycle, LA32MemoryInterface* memory) noexcept;
        SimpleCircularMemoryInterface(const SimpleCircularMemoryInterface& obj) noexcept;
        virtual ~SimpleCircularMemoryInterface() noexcept;

        addr_t                      GetCycle() const noexcept;
        LA32MemoryInterface*        GetMemory() noexcept;

        void                        SetCycle(addr_t cycle) noexcept;
        void                        SetMemory(LA32MemoryInterface* memory) noexcept;

        virtual LA32MOPOutcome      ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept override;
        virtual LA32MOPOutcome      ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept override;

        virtual LA32MOPOutcome      WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept override;
        virtual LA32MOPOutcome      WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept override;
    };


    // Simple Linear Memory Interface
    class SimpleLinearMemory : public LA32MemoryInterface {
    private:
        const size_t    size;
        arch32_t*       heap;

    protected:
        LA32MOPOutcome              __Read_Unchecked(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept;
        LA32MOPOutcome              __Write_Unchecked(addr_t address, LA32MOPWidth width, memdata_t src) noexcept;

    public:
        SimpleLinearMemory(size_t size);
        SimpleLinearMemory(const SimpleLinearMemory& obj);
        virtual ~SimpleLinearMemory();

        arch32_t*                   GetHeap() noexcept;
        const arch32_t*             GetHeap() const noexcept;
        size_t                      GetHeapSize() const noexcept;
        size_t                      GetHeapCapacity() const noexcept;

        bool                        CheckWidth(LA32MOPWidth width) const noexcept;
        bool                        CheckBound(addr_t address, LA32MOPWidth width) const noexcept;

        virtual LA32MOPOutcome      ReadInsn(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept override;
        virtual LA32MOPOutcome      ReadData(addr_t address, LA32MOPWidth width, memdata_t* dst) noexcept override;

        virtual LA32MOPOutcome      WriteInsn(addr_t address, LA32MOPWidth width, memdata_t src) noexcept override;
        virtual LA32MOPOutcome      WriteData(addr_t address, LA32MOPWidth width, memdata_t src) noexcept override;
    };
}


#include "la32memutil.inl"

#endif
