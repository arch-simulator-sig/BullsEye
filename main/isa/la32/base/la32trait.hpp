#pragma once
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
// Trait set
//

#include <initializer_list>
#include <vector>

#include "la32def.hpp"
#include "la32decode.hpp"
#include "la32mem.hpp"


// LA32 Trait total declaration
namespace Jasse {

    // LA32 Trait
    class LA32Trait {
    public:
        class Operand;
        class Source;
        class Destination;
        class Immediate;

    private:
        std::vector<Operand*>       operands;
        std::vector<Source*>        sources;
        std::vector<Destination*>   destinations;
        std::vector<Immediate*>     immediates;

    public:
        LA32Trait(std::initializer_list<Operand*>       operands,
                  std::initializer_list<Source*>        sources,
                  std::initializer_list<Destination*>   destinations,
                  std::initializer_list<Immediate*>     immediates) noexcept;
        
        ~LA32Trait() noexcept;

        bool                HasOperand() const noexcept;
        unsigned int        GetOperandCount() const noexcept;
        const Operand&      GetOperand(unsigned int ordinal) const noexcept;

        bool                HasSource() const noexcept;
        unsigned int        GetSourceCount() const noexcept;
        const Source&       GetSource(unsigned int ordinal) const noexcept;

        bool                HasDestination() const noexcept;
        unsigned int        GetDestinationCount() const noexcept;
        const Destination&  GetDestination(unsigned int ordinal) const noexcept;

        bool                HasImmediate() const noexcept;
        unsigned int        GetImmediateCount() const noexcept;
        const Immediate&    GetImmediate(unsigned int ordinal) const noexcept;
    };
}


// LA32 Trait of Operand
namespace Jasse {

    // LA32 Trait of Operand
    class LA32Trait::Operand {
    public:
        class GPR;

    public:
        enum class Type {
            GPR = 0
        };

    private:
        const Type          type;
        const unsigned int  ordinal;

    public:
        Operand(Type type, unsigned int ordinal) noexcept;
        virtual ~Operand() noexcept;

        Type            GetType() const noexcept;
        unsigned int    GetOrdinal() const noexcept;
    };


    // LA32 Trait of GPR Operand
    class LA32Trait::Operand::GPR 
        : public LA32Trait::Operand {
    public:
        static constexpr Type type  = Type::GPR;

    public:
        class RD;
        class RJ;
        class RK;
        class RA;

    public:
        GPR(unsigned int ordinal) noexcept;

        virtual unsigned int    GetGPRIndex(const LA32Instruction& insn) const noexcept = 0;
        virtual void            SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept = 0;

        virtual unsigned int    GetGPRIndex(insnraw_t insn) const noexcept = 0;
        virtual insnraw_t       SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept = 0;
    };

    // LA32 Trait of GPR Operand (RD)
    class LA32Trait::Operand::GPR::RD 
        : public LA32Trait::Operand::GPR {
    public:
        RD(unsigned int ordinal) noexcept;

        virtual unsigned int    GetGPRIndex(const LA32Instruction& insn) const noexcept override;
        virtual void            SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept override;

        virtual unsigned int    GetGPRIndex(insnraw_t insn) const noexcept override;
        virtual insnraw_t       SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept override;
    };

    // LA32 Trait of GPR Operand (RJ)
    class LA32Trait::Operand::GPR::RJ 
        : public LA32Trait::Operand::GPR {
    public:
        RJ(unsigned int ordinal) noexcept;

        virtual unsigned int    GetGPRIndex(const LA32Instruction& insn) const noexcept override;
        virtual void            SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept override;

        virtual unsigned int    GetGPRIndex(insnraw_t insn) const noexcept override;
        virtual insnraw_t       SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept override;
    };

    // LA32 Trait of GPR Operand (RK)
    class LA32Trait::Operand::GPR::RK 
        : public LA32Trait::Operand::GPR {
    public:
        RK(unsigned int ordinal) noexcept;

        virtual unsigned int    GetGPRIndex(const LA32Instruction& insn) const noexcept override;
        virtual void            SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept override;

        virtual unsigned int    GetGPRIndex(insnraw_t insn) const noexcept override;
        virtual insnraw_t       SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept override;
    };

    // LA32 Trait of GPR Operand (RA)
    class LA32Trait::Operand::GPR::RA 
        : public LA32Trait::Operand::GPR {
    public:
        RA(unsigned int ordinal) noexcept;

        virtual unsigned int    GetGPRIndex(const LA32Instruction& insn) const noexcept override;
        virtual void            SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept override;

        virtual unsigned int    GetGPRIndex(insnraw_t insn) const noexcept override;
        virtual insnraw_t       SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept override;
    };
}


// LA32 Trait of Source
namespace Jasse {

    // LA32 Trait of Source
    class LA32Trait::Source {
    public:
        class PC;
        class Memory;

    public:
        enum class Type {
            PC = 0,
            Memory
        };

    private:
        const Type          type;
        const unsigned int  ordinal;

    public:
        Source(Type type, unsigned int ordinal) noexcept;
        virtual ~Source() noexcept;

        Type            GetType() const noexcept;
        unsigned int    GetOrdinal() const noexcept;
    };


    // LA32 Trait of PC Source
    class LA32Trait::Source::PC 
        : public LA32Trait::Source {
    public:
        static constexpr Type type  = Type::PC;

    public:
        PC(unsigned int ordinal) noexcept;
    };


    // LA32 Trait of Memory Source
    class LA32Trait::Source::Memory
        : public LA32Trait::Source {
    public:
        static constexpr Type type  = Type::Memory;

    public:
        class NormalLoad;

    public:
        enum class MemoryType {
            NormalLoad = 0
        };

    private:
        const MemoryType    memoryType;

    public:
        Memory(MemoryType memoryType, unsigned int ordinal) noexcept;

        MemoryType  GetMemoryType() const noexcept;
    };

    // LA32 Trait of Memory Source (NormalLoad)
    class LA32Trait::Source::Memory::NormalLoad 
        : public LA32Trait::Source::Memory {
    public:
        static constexpr MemoryType memoryType  = MemoryType::NormalLoad;

    public:
        static addr_t   GetAddress(arch32_t operand0, imm_t si12) noexcept;

    public:
        NormalLoad(unsigned int ordinal) noexcept;
    };
}


// LA32 Trait of Destination
namespace Jasse {

    // LA32 Trait of Destination
    class LA32Trait::Destination {
    public:
        class GPR;
        class PC;
        class Memory;

    public:
        enum class Type {
            GPR = 0,
            PC,
            Memory
        };

    private:
        const Type          type;
        const unsigned int  ordinal;

    public:
        Destination(Type type, unsigned int ordinal) noexcept;
        virtual ~Destination() noexcept;

        Type            GetType() const noexcept;
        unsigned int    GetOrdinal() const noexcept;
    };


    // LA32 Trait of GPR Destination
    class LA32Trait::Destination::GPR 
        : public LA32Trait::Destination {
    public:
        static constexpr Type type  = Type::GPR;

    public:
        class RD;
        class RJ;
        class RK;
        class RA;

        class R1;

    public:
        GPR(unsigned int ordinal) noexcept;

        virtual unsigned int    GetGPRIndex(const LA32Instruction& insn) const noexcept = 0;
        virtual void            SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept = 0;

        virtual unsigned int    GetGPRIndex(insnraw_t insn) const noexcept = 0;
        virtual insnraw_t       SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept = 0;
    };

    // LA32 Trait of GPR Destination (RD)
    class LA32Trait::Destination::GPR::RD 
        : public LA32Trait::Destination::GPR {
    public:
        RD(unsigned int ordinal) noexcept;

        virtual unsigned int    GetGPRIndex(const LA32Instruction& insn) const noexcept override;
        virtual void            SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept override;

        virtual unsigned int    GetGPRIndex(insnraw_t insn) const noexcept override;
        virtual insnraw_t       SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept override;
    };

    // LA32 Trait of GPR Destination (RJ)
    class LA32Trait::Destination::GPR::RJ 
        : public LA32Trait::Destination::GPR {
    public:
        RJ(unsigned int ordinal) noexcept;

        virtual unsigned int    GetGPRIndex(const LA32Instruction& insn) const noexcept override;
        virtual void            SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept override;

        virtual unsigned int    GetGPRIndex(insnraw_t insn) const noexcept override;
        virtual insnraw_t       SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept override;
    };

    // LA32 Trait of GPR Destination (RK)
    class LA32Trait::Destination::GPR::RK 
        : public LA32Trait::Destination::GPR {
    public:
        RK(unsigned int ordinal) noexcept;

        virtual unsigned int    GetGPRIndex(const LA32Instruction& insn) const noexcept override;
        virtual void            SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept override;

        virtual unsigned int    GetGPRIndex(insnraw_t insn) const noexcept override;
        virtual insnraw_t       SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept override;
    };

    // LA32 Trait of GPR Destination (RA)
    class LA32Trait::Destination::GPR::RA 
        : public LA32Trait::Destination::GPR {
    public:
        RA(unsigned int ordinal) noexcept;

        virtual unsigned int    GetGPRIndex(const LA32Instruction& insn) const noexcept override;
        virtual void            SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept override;

        virtual unsigned int    GetGPRIndex(insnraw_t insn) const noexcept override;
        virtual insnraw_t       SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept override;
    };

    // LA32 Trait of GPR Destination (R1)
    class LA32Trait::Destination::GPR::R1
        : public LA32Trait::Destination::GPR {
    public:
        R1(unsigned int ordinal) noexcept;

        virtual unsigned int    GetGPRIndex(const LA32Instruction& insn) const noexcept override;
        virtual void            SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept override;

        virtual unsigned int    GetGPRIndex(insnraw_t) const noexcept override;
        virtual insnraw_t       SetGPRIndex(insnraw_t, unsigned int index) const noexcept override;
    };


    // LA32 Trait of PC Destination
    class LA32Trait::Destination::PC 
        : public LA32Trait::Destination {
    public:
        static constexpr Type type  = Type::PC;

    public:
        PC(unsigned int ordinal) noexcept;
    };


    // LA32 Trait of Memory Destination
    class LA32Trait::Destination::Memory 
        : public LA32Trait::Destination {
    public:
        static constexpr Type type  = Type::Memory;

    public:
        class NormalStore;

        class NormalStoreAddress;
        class NormalLoadAddress;

    public:
        enum class MemoryType {
            NormalStore = 0,

            NormalStoreAddress,
            NormalLoadAddress
        };

    private:
        const MemoryType    memoryType;

    public:
        Memory(MemoryType memoryType, unsigned int ordinal) noexcept;

        MemoryType  GetMemoryType() const noexcept;
    };

    // LA32 Trait of Memory Destination (NormalStore)
    class LA32Trait::Destination::Memory::NormalStore 
        : public LA32Trait::Destination::Memory {
    public:
        static constexpr MemoryType memoryType  = MemoryType::NormalStore;

    public:
        static addr_t   GetAddress(arch32_t operand0, imm_t si12) noexcept;

    public:
        NormalStore(unsigned int ordinal) noexcept;
    };

    // LA32 Trait of Memory Destination (NormalStoreAddress)
    class LA32Trait::Destination::Memory::NormalStoreAddress 
        : public LA32Trait::Destination::Memory {
    public:
        static constexpr MemoryType memoryType  = MemoryType::NormalStoreAddress;

    public:
        NormalStoreAddress(unsigned int ordinal) noexcept;
    };

    // LA32 Trait of Memory Destination (NormalLoadAddress)
    class LA32Trait::Destination::Memory::NormalLoadAddress 
        : public LA32Trait::Destination::Memory {
    public:
        static constexpr MemoryType memoryType  = MemoryType::NormalLoadAddress;
    
    public:
        NormalLoadAddress(unsigned int ordinal) noexcept;
    };

}


// LA32 Trait of Immediate
namespace Jasse {

    // LA32 Trait of Immediate
    class LA32Trait::Immediate {
    public:
        class Imm8;
        class Imm12;
        class Imm14;
        class Imm16;
        class Imm21;
        class Imm26;
        class ExImm20;
        class ExImm5;

        class UI5;
        class SI12;
        class UI12;
        class SI14;
        class SI20;

        class OFFS16;
        class OFFS21;
        class OFFS26;

    public:
        enum class Type {
            Imm8 = 0,
            Imm12,
            Imm14,
            Imm16,
            Imm21,
            Imm26,
            ExImm20,
            ExImm5,

            UI5,
            SI12,
            UI12,
            SI14,
            SI20,

            OFFS16,
            OFFS21,
            OFFS26
        };

    private:
        const Type          type;
        const unsigned int  ordinal;

    public:
        Immediate(Type type, unsigned int ordinal) noexcept;
        virtual ~Immediate() noexcept;

        Type                GetType() const noexcept;
        unsigned int        GetOrdinal() const noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction& insn) const noexcept = 0;
        virtual void        SetImmediate(LA32Instruction& insn, imm_t value) const noexcept = 0;

        virtual imm_t       GetImmediate(insnraw_t insn) const noexcept = 0;
        virtual insnraw_t   SetImmediate(insnraw_t insn, imm_t value) const noexcept = 0;
    };


    // LA32 Trait of Immediate (Imm8)
    class LA32Trait::Immediate::Imm8 
        : public LA32Trait::Immediate {
    public:
        static constexpr Type type  = Type::Imm8;

    public:
        Imm8(unsigned int ordinal) noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction& insn) const noexcept override;
        virtual void        SetImmediate(LA32Instruction& insn, imm_t value) const noexcept override;

        virtual imm_t       GetImmediate(insnraw_t insn) const noexcept override;
        virtual insnraw_t   SetImmediate(insnraw_t insn, imm_t value) const noexcept override;
    };

    // LA32 Trait of Immediate (Imm12)
    class LA32Trait::Immediate::Imm12 
        : public LA32Trait::Immediate {
    public:
        static constexpr Type type  = Type::Imm12;

    public:
        Imm12(unsigned int ordinal) noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction& insn) const noexcept override;
        virtual void        SetImmediate(LA32Instruction& insn, imm_t value) const noexcept override;

        virtual imm_t       GetImmediate(insnraw_t insn) const noexcept override;
        virtual insnraw_t   SetImmediate(insnraw_t insn, imm_t value) const noexcept override;
    };

    // LA32 Trait of Immediate (Imm14)
    class LA32Trait::Immediate::Imm14 
        : public LA32Trait::Immediate {
    public:
        static constexpr Type type  = Type::Imm14;

    public:
        Imm14(unsigned int ordinal) noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction& insn) const noexcept override;
        virtual void        SetImmediate(LA32Instruction& insn, imm_t value) const noexcept override;

        virtual imm_t       GetImmediate(insnraw_t insn) const noexcept override;
        virtual insnraw_t   SetImmediate(insnraw_t insn, imm_t value) const noexcept override;
    };

    // LA32 Trait of Immediate (Imm16)
    class LA32Trait::Immediate::Imm16 
        : public LA32Trait::Immediate {
    public:
        static constexpr Type type  = Type::Imm16;

    public:
        Imm16(unsigned int ordinal) noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction& insn) const noexcept override;
        virtual void        SetImmediate(LA32Instruction& insn, imm_t value) const noexcept override;

        virtual imm_t       GetImmediate(insnraw_t insn) const noexcept override;
        virtual insnraw_t   SetImmediate(insnraw_t insn, imm_t value) const noexcept override;
    };

    // LA32 Trait of Immediate (Imm21)
    class LA32Trait::Immediate::Imm21 
        : public LA32Trait::Immediate {
    public:
        static constexpr Type type  = Type::Imm21;

    public:
        Imm21(unsigned int ordinal) noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction& insn) const noexcept override;
        virtual void        SetImmediate(LA32Instruction& insn, imm_t value) const noexcept override;

        virtual imm_t       GetImmediate(insnraw_t insn) const noexcept override;
        virtual insnraw_t   SetImmediate(insnraw_t insn, imm_t value) const noexcept override;
    };

    // LA32 Trait of Immediate (Imm26)
    class LA32Trait::Immediate::Imm26 
        : public LA32Trait::Immediate {
    public:
        static constexpr Type type  = Type::Imm26;

    public:
        Imm26(unsigned int ordinal) noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction& insn) const noexcept override;
        virtual void        SetImmediate(LA32Instruction& insn, imm_t value) const noexcept override;

        virtual imm_t       GetImmediate(insnraw_t insn) const noexcept override;
        virtual insnraw_t   SetImmediate(insnraw_t insn, imm_t value) const noexcept override;
    };

    // LA32 Trait of Immediate (ExImm20)
    class LA32Trait::Immediate::ExImm20 
        : public LA32Trait::Immediate {
    public:
        static constexpr Type type  = Type::ExImm20;

    public:
        ExImm20(unsigned int ordinal) noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction& insn) const noexcept override;
        virtual void        SetImmediate(LA32Instruction& insn, imm_t value) const noexcept override;

        virtual imm_t       GetImmediate(insnraw_t insn) const noexcept override;
        virtual insnraw_t   SetImmediate(insnraw_t insn, imm_t value) const noexcept override;
    };

    // LA32 Trait of Immediate (ExImm5)
    class LA32Trait::Immediate::ExImm5 
        : public LA32Trait::Immediate {
    public:
        static constexpr Type type  = Type::ExImm5;

    public:
        ExImm5(unsigned int ordinal) noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction& insn) const noexcept override;
        virtual void        SetImmediate(LA32Instruction& insn, imm_t value) const noexcept override;

        virtual imm_t       GetImmediate(insnraw_t insn) const noexcept override;
        virtual insnraw_t   SetImmediate(insnraw_t insn, imm_t value) const noexcept override;
    };


    // LA32 Trait of Immediate (UI5)
    class LA32Trait::Immediate::UI5 
        : public LA32Trait::Immediate {
    public:
        static constexpr Type type  = Type::UI5;

    public:
        UI5(unsigned int ordinal) noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction& insn) const noexcept override;
        virtual void        SetImmediate(LA32Instruction& insn, imm_t value) const noexcept override;

        virtual imm_t       GetImmediate(insnraw_t) const noexcept override;
        virtual insnraw_t   SetImmediate(insnraw_t, imm_t value) const noexcept override;
    };

    // LA32 Trait of Immediate (SI12)
    class LA32Trait::Immediate::SI12 
        : public LA32Trait::Immediate {
    public:
        static constexpr Type type  = Type::SI12;

    public:
        SI12(unsigned int ordinal) noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction& insn) const noexcept override;
        virtual void        SetImmediate(LA32Instruction& insn, imm_t) const noexcept override;

        virtual imm_t       GetImmediate(insnraw_t) const noexcept override;
        virtual insnraw_t   SetImmediate(insnraw_t, imm_t value) const noexcept override;
    };

    // LA32 Trait of Immediate (UI12)
    class LA32Trait::Immediate::UI12 
        : public LA32Trait::Immediate {
    public:
        static constexpr Type type  = Type::UI12;

    public:
        UI12(unsigned int ordinal) noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction& insn) const noexcept override;
        virtual void        SetImmediate(LA32Instruction& insn, imm_t) const noexcept override;

        virtual imm_t       GetImmediate(insnraw_t) const noexcept override;
        virtual insnraw_t   SetImmediate(insnraw_t, imm_t value) const noexcept override;
    };

    // LA32 Trait of Immediate (SI14)
    class LA32Trait::Immediate::SI14 
        : public LA32Trait::Immediate {
    public:
        static constexpr Type type  = Type::SI14;

    public:
        SI14(unsigned int ordinal) noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction& insn) const noexcept override;
        virtual void        SetImmediate(LA32Instruction& insn, imm_t) const noexcept override;

        virtual imm_t       GetImmediate(insnraw_t) const noexcept override;
        virtual insnraw_t   SetImmediate(insnraw_t, imm_t value) const noexcept override;
    };

    // LA32 Trait of Immediate (SI20)
    class LA32Trait::Immediate::SI20 
        : public LA32Trait::Immediate {
    public:
        static constexpr Type type  = Type::SI20;

    public:
        SI20(unsigned int ordinal) noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction& insn) const noexcept override;
        virtual void        SetImmediate(LA32Instruction& insn, imm_t) const noexcept override;

        virtual imm_t       GetImmediate(insnraw_t) const noexcept override;
        virtual insnraw_t   SetImmediate(insnraw_t, imm_t value) const noexcept override;
    };


    // LA32 Trait of Immediate (OFFS16)
    class LA32Trait::Immediate::OFFS16 
        : public LA32Trait::Immediate {
    public:
        static constexpr Type type  = Type::OFFS16;

    public:
        OFFS16(unsigned int ordinal) noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction&) const noexcept override;
        virtual void        SetImmediate(LA32Instruction&, imm_t) const noexcept override;

        virtual imm_t       GetImmediate(insnraw_t) const noexcept override;
        virtual insnraw_t   SetImmediate(insnraw_t, imm_t) const noexcept override;
    };

    // LA32 Trait of Immediate (OFFS21)
    class LA32Trait::Immediate::OFFS21 
        : public LA32Trait::Immediate {
    public:
        static constexpr Type type  = Type::OFFS21;

    public:
        OFFS21(unsigned int ordinal) noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction&) const noexcept override;
        virtual void        SetImmediate(LA32Instruction&, imm_t) const noexcept override;

        virtual imm_t       GetImmediate(insnraw_t) const noexcept override;
        virtual insnraw_t   SetImmediate(insnraw_t, imm_t) const noexcept override;
    };

    // LA32 Trait of Immediate (OFFS26)
    class LA32Trait::Immediate::OFFS26 
        : public LA32Trait::Immediate {
    public:
        static constexpr Type type  = Type::OFFS26;
    
    public:
        OFFS26(unsigned int ordinal) noexcept;

        virtual imm_t       GetImmediate(const LA32Instruction&) const noexcept override;
        virtual void        SetImmediate(LA32Instruction&, imm_t) const noexcept override;

        virtual imm_t       GetImmediate(insnraw_t) const noexcept override;
        virtual insnraw_t   SetImmediate(insnraw_t, imm_t) const noexcept override;
    };

}



// LA32 Traits
namespace Jasse {

    struct LA32Traits {

        static const LA32Trait* NORMAL_3R;

        static const LA32Trait* NORMAL_2RSI12;

        static const LA32Trait* NORMAL_2RUI12;


        static const LA32Trait* NORMAL_2ROFFS16;

        static const LA32Trait* NORMAL_OFFS26;

        static const LA32Trait* NORMAL_OFFS26R1;

        
        static const LA32Trait* NORMAL_LOAD_2RSI12;

        static const LA32Trait* NORMAL_STORE_2RSI12;


        static const LA32Trait* EXTENDED_1RI20;

        static const LA32Trait* EXTENDED_1RI20PC;


        static const LA32Trait* EXTENDED_2RI5;
        

        static const LA32Trait* JIRL_2ROFFS16;
    };
}
