#include "la32trait.hpp"
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
// Trait set
//


// Implementation of: class LA32Trait
namespace Jasse {
    /*
    std::vector<Operand*>       operands;
    std::vector<Source*>        sources;
    std::vector<Destination*>   destinations;
    std::vector<Immediate*>     immediates;
    */

    LA32Trait::LA32Trait(std::initializer_list<Operand*>        operands,
                         std::initializer_list<Source*>         sources,
                         std::initializer_list<Destination*>    destinations,
                         std::initializer_list<Immediate*>      immediates) noexcept
        : operands      (operands)
        , destinations  (destinations)
        , immediates    (immediates)
    { }

    LA32Trait::~LA32Trait() noexcept
    {
        for (auto& operand : operands)
            delete operand;

        for (auto& source : sources)
            delete source;

        for (auto& destination : destinations)
            delete destination;

        for (auto& immediate : immediates)
            delete immediate;
    }

    bool LA32Trait::HasOperand() const noexcept
    {
        return !operands.empty();
    }

    unsigned int LA32Trait::GetOperandCount() const noexcept
    {
        return operands.size();
    }

    const LA32Trait::Operand* LA32Trait::GetOperand(unsigned int ordinal) const noexcept
    {
        return operands[ordinal];
    }

    bool LA32Trait::HasSource() const noexcept
    {
        return !sources.empty();
    }

    unsigned int LA32Trait::GetSourceCount() const noexcept
    {
        return sources.size();
    }

    const LA32Trait::Source* LA32Trait::GetSource(unsigned int ordinal) const noexcept
    {
        return sources[ordinal];
    }

    bool LA32Trait::HasDestination() const noexcept
    {
        return !destinations.empty();
    }

    unsigned int LA32Trait::GetDestinationCount() const noexcept
    {
        return destinations.size();
    }

    const LA32Trait::Destination* LA32Trait::GetDestination(unsigned int ordinal) const noexcept
    {
        return destinations[ordinal];
    }

    bool LA32Trait::HasImmediate() const noexcept
    {
        return !immediates.empty();
    }

    unsigned int LA32Trait::GetImmediateCount() const noexcept
    {
        return immediates.size();
    }

    const LA32Trait::Immediate* LA32Trait::GetImmediate(unsigned int ordinal) const noexcept
    {
        return immediates[ordinal];
    }
}



// Implementation of: class LA32Trait::Operand
namespace Jasse {
    /*
    const Type          type;
    const unsigned int  ordinal;
    */

    LA32Trait::Operand::Operand(Type type, unsigned int ordinal) noexcept
        : type      (type)
        , ordinal   (ordinal)
    { }

    LA32Trait::Operand::~Operand() noexcept
    { }

    LA32Trait::Operand::Type LA32Trait::Operand::GetType() const noexcept
    {
        return type;
    }

    unsigned int LA32Trait::Operand::GetOrdinal() const noexcept
    {
        return ordinal;
    }
}


// Implementation of: class LA32Trait::Operand::GPR
namespace Jasse {

    LA32Trait::Operand::GPR::GPR(unsigned int ordinal) noexcept
        : Operand   (type, ordinal)
    { }
}


// Implementation of: class LA32Trait::Operand::GPR::RD
namespace Jasse {

    LA32Trait::Operand::GPR::RD::RD(unsigned int ordinal) noexcept
        : GPR   (ordinal)
    { }

    unsigned int LA32Trait::Operand::GPR::RD::GetGPRIndex(const LA32Instruction& insn) const noexcept
    {
        return insn.GetRD();
    }

    void LA32Trait::Operand::GPR::RD::SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept
    {
        insn.SetRD(index);
    }

    unsigned int LA32Trait::Operand::GPR::RD::GetGPRIndex(insnraw_t insn) const noexcept
    {
        return LA32Instruction::GetRD(insn);
    }

    insnraw_t LA32Trait::Operand::GPR::RD::SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept
    {
        return LA32Instruction::SetRD(insn, index);
    }
}

// Implementation of: class LA32Trait::Operand::GPR::RJ
namespace Jasse {

    LA32Trait::Operand::GPR::RJ::RJ(unsigned int ordinal) noexcept
        : GPR   (ordinal)
    { }

    unsigned int LA32Trait::Operand::GPR::RJ::GetGPRIndex(const LA32Instruction& insn) const noexcept
    {
        return insn.GetRJ();
    }

    void LA32Trait::Operand::GPR::RJ::SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept
    {
        insn.SetRJ(index);
    }

    unsigned int LA32Trait::Operand::GPR::RJ::GetGPRIndex(insnraw_t insn) const noexcept
    {
        return LA32Instruction::GetRJ(insn);
    }

    insnraw_t LA32Trait::Operand::GPR::RJ::SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept
    {
        return LA32Instruction::SetRJ(insn, index);
    }
}

// Implementation of: class LA32Trait::Operand::GPR::RK
namespace Jasse {

    LA32Trait::Operand::GPR::RK::RK(unsigned int ordinal) noexcept
        : GPR   (ordinal)
    { }

    unsigned int LA32Trait::Operand::GPR::RK::GetGPRIndex(const LA32Instruction& insn) const noexcept
    {
        return insn.GetRK();
    }

    void LA32Trait::Operand::GPR::RK::SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept
    {
        insn.SetRK(index);
    }

    unsigned int LA32Trait::Operand::GPR::RK::GetGPRIndex(insnraw_t insn) const noexcept
    {
        return LA32Instruction::GetRK(insn);
    }

    insnraw_t LA32Trait::Operand::GPR::RK::SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept
    {
        return LA32Instruction::SetRK(insn, index);
    }
}

// Implementation of: class LA32Trait::Operand::GPR::RA
namespace Jasse {

    LA32Trait::Operand::GPR::RA::RA(unsigned int ordinal) noexcept
        : GPR   (ordinal)
    { }

    unsigned int LA32Trait::Operand::GPR::RA::GetGPRIndex(const LA32Instruction& insn) const noexcept
    {
        return insn.GetRA();
    }

    void LA32Trait::Operand::GPR::RA::SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept
    {
        insn.SetRA(index);
    }

    unsigned int LA32Trait::Operand::GPR::RA::GetGPRIndex(insnraw_t insn) const noexcept
    {
        return LA32Instruction::GetRA(insn);
    }

    insnraw_t LA32Trait::Operand::GPR::RA::SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept
    {
        return LA32Instruction::SetRA(insn, index);
    }
}



// Implementation of: class LA32Trait::Source
namespace Jasse {
    /*
    const Type          type;
    const unsigned int  ordinal;
    */

    LA32Trait::Source::Source(Type type, unsigned int ordinal) noexcept
        : type      (type)
        , ordinal   (ordinal)
    { }

    LA32Trait::Source::~Source() noexcept
    { }

    LA32Trait::Source::Type LA32Trait::Source::GetType() const noexcept
    {
        return type;
    }

    unsigned int LA32Trait::Source::GetOrdinal() const noexcept
    {
        return ordinal;
    }
}


// Implementation of: class LA32Trait::Source::PC
namespace Jasse {

    LA32Trait::Source::PC::PC(unsigned int ordinal) noexcept
        : Source   (type, ordinal)
    { }
}


// Implementation of: class LA32Trait::Source::Memory
namespace Jasse {

    LA32Trait::Source::Memory::Memory(MemoryType memoryType, unsigned int ordinal) noexcept
        : Source        (type, ordinal)
        , memoryType    (memoryType)
    { }

    LA32Trait::Source::Memory::MemoryType LA32Trait::Source::Memory::GetMemoryType() const noexcept
    {
        return memoryType;
    }
}

// Implementation of: class LA32Trait::Source::Memory::NormalLoad
namespace Jasse {

    LA32Trait::Source::Memory::NormalLoad::NormalLoad(unsigned int ordinal) noexcept
        : Memory    (memoryType, ordinal)
    { }

    addr_t LA32Trait::Source::Memory::NormalLoad::GetAddress(arch32_t operand0, imm_t si12) noexcept
    {
        return operand0 + SEXT32_IMM12(si12);
    }
}



// Implementation of: class LA32Trait::Destination
namespace Jasse {
    /*
    const Type          type;
    const unsigned int  ordinal;
    */

    LA32Trait::Destination::Destination(Type type, unsigned int ordinal) noexcept
        : type      (type)
        , ordinal   (ordinal)
    { }

    LA32Trait::Destination::~Destination() noexcept
    { }

    LA32Trait::Destination::Type LA32Trait::Destination::GetType() const noexcept
    {
        return type;
    }

    unsigned int LA32Trait::Destination::GetOrdinal() const noexcept
    {
        return ordinal;
    }
}


// Implementation of: class LA32Trait::Destination::GPR
namespace Jasse {

    LA32Trait::Destination::GPR::GPR(unsigned int ordinal) noexcept
        : Destination   (type, ordinal)
    { }
}

// Implementation of: class LA32Trait::Destination::GPR::RD
namespace Jasse {

    LA32Trait::Destination::GPR::RD::RD(unsigned int ordinal) noexcept
        : GPR   (ordinal)
    { }

    unsigned int LA32Trait::Destination::GPR::RD::GetGPRIndex(const LA32Instruction& insn) const noexcept
    {
        return insn.GetRD();
    }

    void LA32Trait::Destination::GPR::RD::SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept
    {
        insn.SetRD(index);
    }

    unsigned int LA32Trait::Destination::GPR::RD::GetGPRIndex(insnraw_t insn) const noexcept
    {
        return LA32Instruction::GetRD(insn);
    }

    insnraw_t LA32Trait::Destination::GPR::RD::SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept
    {
        return LA32Instruction::SetRD(insn, index);
    }
}

// Implementation of: class LA32Trait::Destination::GPR::RJ
namespace Jasse {

    LA32Trait::Destination::GPR::RJ::RJ(unsigned int ordinal) noexcept
        : GPR   (ordinal)
    { }

    unsigned int LA32Trait::Destination::GPR::RJ::GetGPRIndex(const LA32Instruction& insn) const noexcept
    {
        return insn.GetRJ();
    }

    void LA32Trait::Destination::GPR::RJ::SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept
    {
        insn.SetRJ(index);
    }

    unsigned int LA32Trait::Destination::GPR::RJ::GetGPRIndex(insnraw_t insn) const noexcept
    {
        return LA32Instruction::GetRJ(insn);
    }

    insnraw_t LA32Trait::Destination::GPR::RJ::SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept
    {
        return LA32Instruction::SetRJ(insn, index);
    }
}

// Implementation of: class LA32Trait::Destination::GPR::RK
namespace Jasse {

    LA32Trait::Destination::GPR::RK::RK(unsigned int ordinal) noexcept
        : GPR   (ordinal)
    { }

    unsigned int LA32Trait::Destination::GPR::RK::GetGPRIndex(const LA32Instruction& insn) const noexcept
    {
        return insn.GetRK();
    }

    void LA32Trait::Destination::GPR::RK::SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept
    {
        insn.SetRK(index);
    }

    unsigned int LA32Trait::Destination::GPR::RK::GetGPRIndex(insnraw_t insn) const noexcept
    {
        return LA32Instruction::GetRK(insn);
    }

    insnraw_t LA32Trait::Destination::GPR::RK::SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept
    {
        return LA32Instruction::SetRK(insn, index);
    }
}

// Implementation of: class LA32Trait::Destination::GPR::RA
namespace Jasse {

    LA32Trait::Destination::GPR::RA::RA(unsigned int ordinal) noexcept
        : GPR   (ordinal)
    { }

    unsigned int LA32Trait::Destination::GPR::RA::GetGPRIndex(const LA32Instruction& insn) const noexcept
    {
        return insn.GetRA();
    }

    void LA32Trait::Destination::GPR::RA::SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept
    {
        insn.SetRA(index);
    }

    unsigned int LA32Trait::Destination::GPR::RA::GetGPRIndex(insnraw_t insn) const noexcept
    {
        return LA32Instruction::GetRA(insn);
    }

    insnraw_t LA32Trait::Destination::GPR::RA::SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept
    {
        return LA32Instruction::SetRA(insn, index);
    }
}

// Implementation of: class LA32Trait::Destination::GPR::R1
namespace Jasse {

    LA32Trait::Destination::GPR::R1::R1(unsigned int ordinal) noexcept
        : GPR   (ordinal)
    { }

    unsigned int LA32Trait::Destination::GPR::R1::GetGPRIndex(const LA32Instruction& insn) const noexcept
    {
        return 1;
    }

    void LA32Trait::Destination::GPR::R1::SetGPRIndex(LA32Instruction& insn, unsigned int index) const noexcept
    { }

    unsigned int LA32Trait::Destination::GPR::R1::GetGPRIndex(insnraw_t insn) const noexcept
    {
        return 1;
    }

    insnraw_t LA32Trait::Destination::GPR::R1::SetGPRIndex(insnraw_t insn, unsigned int index) const noexcept
    { 
        return insn;
    }
}


// Implementation of: class LA32Trait::Destination::PC
namespace Jasse {

    LA32Trait::Destination::PC::PC(unsigned int ordinal) noexcept
        : Destination   (type, ordinal)
    { }
}


// Implementation of: class LA32Trait::Destination::Memory
namespace Jasse {

    LA32Trait::Destination::Memory::Memory(MemoryType memoryType, unsigned int ordinal) noexcept
        : Destination   (type, ordinal)
        , memoryType    (memoryType)
    { }

    LA32Trait::Destination::Memory::MemoryType LA32Trait::Destination::Memory::GetMemoryType() const noexcept
    {
        return memoryType;
    }
}

// Implementation of: class LA32Trait::Destination::Memory::NormalStore
namespace Jasse {

    LA32Trait::Destination::Memory::NormalStore::NormalStore(unsigned int ordinal) noexcept
        : Memory    (memoryType, ordinal)
    { }

    addr_t LA32Trait::Destination::Memory::NormalStore::GetAddress(arch32_t operand0, imm_t si12) noexcept
    {
        return operand0 + SEXT32_IMM12(si12);
    }
}

// Implementation of: class LA32Trait::Destination::Memory::NormalStoreAddress
namespace Jasse {

    LA32Trait::Destination::Memory::NormalStoreAddress::NormalStoreAddress(unsigned int ordinal) noexcept
        : Memory    (memoryType, ordinal)
    { }
}

// Implementation of: class LA32Trait::Destination::Memory::NormalLoadAddress
namespace Jasse {

    LA32Trait::Destination::Memory::NormalLoadAddress::NormalLoadAddress(unsigned int ordinal) noexcept
        : Memory    (memoryType, ordinal)
    { }
}



// Implementation of: class LA32Trait::Immediate
namespace Jasse {
    /*
    const Type          type;
    const unsigned int  ordinal;
    */

    LA32Trait::Immediate::Immediate(Type type, unsigned int ordinal) noexcept
        : type      (type)
        , ordinal   (ordinal)
    { }

    LA32Trait::Immediate::~Immediate() noexcept
    { }

    LA32Trait::Immediate::Type LA32Trait::Immediate::GetType() const noexcept
    {
        return type;
    }

    unsigned int LA32Trait::Immediate::GetOrdinal() const noexcept
    {
        return ordinal;
    }
}


// Implementation of: class LA32Trait::Immediate::Imm8
namespace Jasse {

    LA32Trait::Immediate::Imm8::Imm8(unsigned int ordinal) noexcept
        : Immediate (type, ordinal)
    { }

    imm_t LA32Trait::Immediate::Imm8::GetImmediate(const LA32Instruction& insn) const noexcept
    {
        return insn.GetImm8();
    }

    void LA32Trait::Immediate::Imm8::SetImmediate(LA32Instruction& insn, imm_t imm) const noexcept
    {
        insn.SetImm8(imm);
    }

    imm_t LA32Trait::Immediate::Imm8::GetImmediate(insnraw_t insn) const noexcept
    {
        return LA32Instruction::GetImm8(insn);
    }

    insnraw_t LA32Trait::Immediate::Imm8::SetImmediate(insnraw_t insn, imm_t imm) const noexcept
    {
        return LA32Instruction::SetImm8(insn, imm);
    }
}

// Implementation of: class LA32Trait::Immediate::Imm12
namespace Jasse {

    LA32Trait::Immediate::Imm12::Imm12(unsigned int ordinal) noexcept
        : Immediate (type, ordinal)
    { }

    imm_t LA32Trait::Immediate::Imm12::GetImmediate(const LA32Instruction& insn) const noexcept
    {
        return insn.GetImm12();
    }

    void LA32Trait::Immediate::Imm12::SetImmediate(LA32Instruction& insn, imm_t imm) const noexcept
    {
        insn.SetImm12(imm);
    }

    imm_t LA32Trait::Immediate::Imm12::GetImmediate(insnraw_t insn) const noexcept
    {
        return LA32Instruction::GetImm12(insn);
    }

    insnraw_t LA32Trait::Immediate::Imm12::SetImmediate(insnraw_t insn, imm_t imm) const noexcept
    {
        return LA32Instruction::SetImm12(insn, imm);
    }
}

// Implementation of: class LA32Trait::Immediate::Imm14
namespace Jasse {

    LA32Trait::Immediate::Imm14::Imm14(unsigned int ordinal) noexcept
        : Immediate (type, ordinal)
    { }

    imm_t LA32Trait::Immediate::Imm14::GetImmediate(const LA32Instruction& insn) const noexcept
    {
        return insn.GetImm14();
    }

    void LA32Trait::Immediate::Imm14::SetImmediate(LA32Instruction& insn, imm_t imm) const noexcept
    {
        insn.SetImm14(imm);
    }

    imm_t LA32Trait::Immediate::Imm14::GetImmediate(insnraw_t insn) const noexcept
    {
        return LA32Instruction::GetImm14(insn);
    }

    insnraw_t LA32Trait::Immediate::Imm14::SetImmediate(insnraw_t insn, imm_t imm) const noexcept
    {
        return LA32Instruction::SetImm14(insn, imm);
    }
}

// Implementation of: class LA32Trait::Immediate::Imm16
namespace Jasse {

    LA32Trait::Immediate::Imm16::Imm16(unsigned int ordinal) noexcept
        : Immediate (type, ordinal)
    { }

    imm_t LA32Trait::Immediate::Imm16::GetImmediate(const LA32Instruction& insn) const noexcept
    {
        return insn.GetImm16();
    }

    void LA32Trait::Immediate::Imm16::SetImmediate(LA32Instruction& insn, imm_t imm) const noexcept
    {
        insn.SetImm16(imm);
    }

    imm_t LA32Trait::Immediate::Imm16::GetImmediate(insnraw_t insn) const noexcept
    {
        return LA32Instruction::GetImm16(insn);
    }

    insnraw_t LA32Trait::Immediate::Imm16::SetImmediate(insnraw_t insn, imm_t imm) const noexcept
    {
        return LA32Instruction::SetImm16(insn, imm);
    }
}

// Implementation of: class LA32Trait::Immediate::Imm21
namespace Jasse {

    LA32Trait::Immediate::Imm21::Imm21(unsigned int ordinal) noexcept
        : Immediate (type, ordinal)
    { }

    imm_t LA32Trait::Immediate::Imm21::GetImmediate(const LA32Instruction& insn) const noexcept
    {
        return insn.GetImm21();
    }

    void LA32Trait::Immediate::Imm21::SetImmediate(LA32Instruction& insn, imm_t imm) const noexcept
    {
        insn.SetImm21(imm);
    }

    imm_t LA32Trait::Immediate::Imm21::GetImmediate(insnraw_t insn) const noexcept
    {
        return LA32Instruction::GetImm21(insn);
    }

    insnraw_t LA32Trait::Immediate::Imm21::SetImmediate(insnraw_t insn, imm_t imm) const noexcept
    {
        return LA32Instruction::SetImm21(insn, imm);
    }
}

// Implementation of: class LA32Trait::Immediate::Imm26
namespace Jasse {

    LA32Trait::Immediate::Imm26::Imm26(unsigned int ordinal) noexcept
        : Immediate (type, ordinal)
    { }

    imm_t LA32Trait::Immediate::Imm26::GetImmediate(const LA32Instruction& insn) const noexcept
    {
        return insn.GetImm26();
    }

    void LA32Trait::Immediate::Imm26::SetImmediate(LA32Instruction& insn, imm_t imm) const noexcept
    {
        insn.SetImm26(imm);
    }

    imm_t LA32Trait::Immediate::Imm26::GetImmediate(insnraw_t insn) const noexcept
    {
        return LA32Instruction::GetImm26(insn);
    }

    insnraw_t LA32Trait::Immediate::Imm26::SetImmediate(insnraw_t insn, imm_t imm) const noexcept
    {
        return LA32Instruction::SetImm26(insn, imm);
    }
}

// Implementation of: class LA32Trait::Immediate::ExImm20
namespace Jasse {

    LA32Trait::Immediate::ExImm20::ExImm20(unsigned int ordinal) noexcept
        : Immediate (type, ordinal)
    { }

    imm_t LA32Trait::Immediate::ExImm20::GetImmediate(const LA32Instruction& insn) const noexcept
    {
        return insn.GetExImm20();
    }

    void LA32Trait::Immediate::ExImm20::SetImmediate(LA32Instruction& insn, imm_t imm) const noexcept
    {
        insn.SetExImm20(imm);
    }

    imm_t LA32Trait::Immediate::ExImm20::GetImmediate(insnraw_t insn) const noexcept
    {
        return LA32Instruction::GetExImm20(insn);
    }

    insnraw_t LA32Trait::Immediate::ExImm20::SetImmediate(insnraw_t insn, imm_t imm) const noexcept
    {
        return LA32Instruction::SetExImm20(insn, imm);
    }
}

// Implementation of: class LA32Trait::Immediate::ExImm5
namespace Jasse {

    LA32Trait::Immediate::ExImm5::ExImm5(unsigned int ordinal) noexcept
        : Immediate (type, ordinal)
    { }

    imm_t LA32Trait::Immediate::ExImm5::GetImmediate(const LA32Instruction& insn) const noexcept
    {
        return insn.GetExImm5();
    }

    void LA32Trait::Immediate::ExImm5::SetImmediate(LA32Instruction& insn, imm_t imm) const noexcept
    {
        insn.SetExImm5(imm);
    }

    imm_t LA32Trait::Immediate::ExImm5::GetImmediate(insnraw_t insn) const noexcept
    {
        return LA32Instruction::GetExImm5(insn);
    }

    insnraw_t LA32Trait::Immediate::ExImm5::SetImmediate(insnraw_t insn, imm_t imm) const noexcept
    {
        return LA32Instruction::SetExImm5(insn, imm);
    }
}


// Implementation of: class LA32Trait::Immediate::UI5
namespace Jasse {

    LA32Trait::Immediate::UI5::UI5(unsigned int ordinal) noexcept
        : Immediate (type, ordinal)
    { }

    imm_t LA32Trait::Immediate::UI5::GetImmediate(const LA32Instruction& insn) const noexcept
    {
        return ZEXT32_IMM5(insn.GetExImm5());
    }

    void LA32Trait::Immediate::UI5::SetImmediate(LA32Instruction& insn, imm_t imm) const noexcept
    {
        insn.SetExImm5(imm);
    }

    imm_t LA32Trait::Immediate::UI5::GetImmediate(insnraw_t insn) const noexcept
    {
        return ZEXT32_IMM5(LA32Instruction::GetExImm5(insn));
    }

    insnraw_t LA32Trait::Immediate::UI5::SetImmediate(insnraw_t insn, imm_t imm) const noexcept
    {
        return LA32Instruction::SetExImm5(insn, imm);
    }
}

// Implementation of: class LA32Trait::Immediate::SI12
namespace Jasse {

    LA32Trait::Immediate::SI12::SI12(unsigned int ordinal) noexcept
        : Immediate (type, ordinal)
    { }

    imm_t LA32Trait::Immediate::SI12::GetImmediate(const LA32Instruction& insn) const noexcept
    {
        return SEXT32_IMM12(insn.GetImm12());
    }

    void LA32Trait::Immediate::SI12::SetImmediate(LA32Instruction& insn, imm_t imm) const noexcept
    {
        insn.SetImm12(imm);
    }

    imm_t LA32Trait::Immediate::SI12::GetImmediate(insnraw_t insn) const noexcept
    {
        return SEXT32_IMM12(LA32Instruction::GetImm12(insn));
    }

    insnraw_t LA32Trait::Immediate::SI12::SetImmediate(insnraw_t insn, imm_t imm) const noexcept
    {
        return LA32Instruction::SetImm12(insn, imm);
    }
}

// Implementation of: class LA32Trait::Immediate::UI12
namespace Jasse {

    LA32Trait::Immediate::UI12::UI12(unsigned int ordinal) noexcept
        : Immediate (type, ordinal)
    { }

    imm_t LA32Trait::Immediate::UI12::GetImmediate(const LA32Instruction& insn) const noexcept
    {
        return ZEXT32_IMM12(insn.GetImm12());
    }

    void LA32Trait::Immediate::UI12::SetImmediate(LA32Instruction& insn, imm_t imm) const noexcept
    {
        insn.SetImm12(imm);
    }

    imm_t LA32Trait::Immediate::UI12::GetImmediate(insnraw_t insn) const noexcept
    {
        return ZEXT32_IMM12(LA32Instruction::GetImm12(insn));
    }

    insnraw_t LA32Trait::Immediate::UI12::SetImmediate(insnraw_t insn, imm_t imm) const noexcept
    {
        return LA32Instruction::SetImm12(insn, imm);
    }
}

// Implementation of: class LA32Trait::Immediate::SI14
namespace Jasse {

    LA32Trait::Immediate::SI14::SI14(unsigned int ordinal) noexcept
        : Immediate (type, ordinal)
    { }

    imm_t LA32Trait::Immediate::SI14::GetImmediate(const LA32Instruction& insn) const noexcept
    {
        return SEXT32_IMM14(insn.GetImm14());
    }

    void LA32Trait::Immediate::SI14::SetImmediate(LA32Instruction& insn, imm_t imm) const noexcept
    {
        insn.SetImm14(imm);
    }

    imm_t LA32Trait::Immediate::SI14::GetImmediate(insnraw_t insn) const noexcept
    {
        return SEXT32_IMM14(LA32Instruction::GetImm14(insn));
    }

    insnraw_t LA32Trait::Immediate::SI14::SetImmediate(insnraw_t insn, imm_t imm) const noexcept
    {
        return LA32Instruction::SetImm14(insn, imm);
    }
}

// Implementation of: class LA32Trait::Immediate::SI20
namespace Jasse {

    LA32Trait::Immediate::SI20::SI20(unsigned int ordinal) noexcept
        : Immediate (type, ordinal)
    { }

    imm_t LA32Trait::Immediate::SI20::GetImmediate(const LA32Instruction& insn) const noexcept
    {
        return SEXT32_IMM20(insn.GetExImm20());
    }

    void LA32Trait::Immediate::SI20::SetImmediate(LA32Instruction& insn, imm_t imm) const noexcept
    {
        insn.SetExImm20(imm);
    }

    imm_t LA32Trait::Immediate::SI20::GetImmediate(insnraw_t insn) const noexcept
    {
        return SEXT32_IMM20(LA32Instruction::GetExImm20(insn));
    }

    insnraw_t LA32Trait::Immediate::SI20::SetImmediate(insnraw_t insn, imm_t imm) const noexcept
    {
        return LA32Instruction::SetExImm20(insn, imm);
    }
}


// Implementation of: class LA32Trait::Immediate::OFFS16
namespace Jasse {

    LA32Trait::Immediate::OFFS16::OFFS16(unsigned int ordinal) noexcept
        : Immediate (type, ordinal)
    { }

    imm_t LA32Trait::Immediate::OFFS16::GetImmediate(const LA32Instruction& insn) const noexcept
    {
        return SEXT32_IMM16(insn.GetImm16()) << 2;
    }

    void LA32Trait::Immediate::OFFS16::SetImmediate(LA32Instruction& insn, imm_t imm) const noexcept
    {
        insn.SetImm16(imm >> 2);
    }

    imm_t LA32Trait::Immediate::OFFS16::GetImmediate(insnraw_t insn) const noexcept
    {
        return SEXT32_IMM16(LA32Instruction::GetImm16(insn)) << 2;
    }

    insnraw_t LA32Trait::Immediate::OFFS16::SetImmediate(insnraw_t insn, imm_t imm) const noexcept
    {
        return LA32Instruction::SetImm16(insn, imm >> 2);
    }
}

// Implementation of: class LA32Trait::Immediate::OFFS21
namespace Jasse {

    LA32Trait::Immediate::OFFS21::OFFS21(unsigned int ordinal) noexcept
        : Immediate (type, ordinal)
    { }

    imm_t LA32Trait::Immediate::OFFS21::GetImmediate(const LA32Instruction& insn) const noexcept
    {
        return SEXT32_IMM21(insn.GetImm21()) << 2;
    }

    void LA32Trait::Immediate::OFFS21::SetImmediate(LA32Instruction& insn, imm_t imm) const noexcept
    {
        insn.SetImm21(imm >> 2);
    }

    imm_t LA32Trait::Immediate::OFFS21::GetImmediate(insnraw_t insn) const noexcept
    {
        return SEXT32_IMM21(LA32Instruction::GetImm21(insn)) << 2;
    }

    insnraw_t LA32Trait::Immediate::OFFS21::SetImmediate(insnraw_t insn, imm_t imm) const noexcept
    {
        return LA32Instruction::SetImm21(insn, imm >> 2);
    }
}

// Implementation of: class LA32Trait::Immediate::OFFS26
namespace Jasse {

    LA32Trait::Immediate::OFFS26::OFFS26(unsigned int ordinal) noexcept
        : Immediate (type, ordinal)
    { }

    imm_t LA32Trait::Immediate::OFFS26::GetImmediate(const LA32Instruction& insn) const noexcept
    {
        return SEXT32_IMM26(insn.GetImm26()) << 2;
    }

    void LA32Trait::Immediate::OFFS26::SetImmediate(LA32Instruction& insn, imm_t imm) const noexcept
    {
        insn.SetImm26(imm >> 2);
    }

    imm_t LA32Trait::Immediate::OFFS26::GetImmediate(insnraw_t insn) const noexcept
    {
        return SEXT32_IMM26(LA32Instruction::GetImm26(insn)) << 2;
    }

    insnraw_t LA32Trait::Immediate::OFFS26::SetImmediate(insnraw_t insn, imm_t imm) const noexcept
    {
        return LA32Instruction::SetImm26(insn, imm >> 2);
    }
}



// Implementation of: struct LA32Traits
namespace Jasse {

    const LA32Trait LA32Traits::NORMAL_3R = LA32Trait(
        {
            new LA32Trait::Operand::GPR::RJ(0),
            new LA32Trait::Operand::GPR::RK(1)
        }, 
        {},
        {
            new LA32Trait::Destination::GPR::RD(0)
        },
        {}
    );

    const LA32Trait LA32Traits::NORMAL_2RSI12 = LA32Trait(
        {
            new LA32Trait::Operand::GPR::RJ(0)
        }, 
        {}, 
        {
            new LA32Trait::Destination::GPR::RD(0)
        }, 
        {
            new LA32Trait::Immediate::SI12(0)
        }
    );

    const LA32Trait LA32Traits::NORMAL_2RUI12 = LA32Trait(
        {
            new LA32Trait::Operand::GPR::RJ(0)
        },
        {},
        {
            new LA32Trait::Destination::GPR::RD(0)
        },
        {
            new LA32Trait::Immediate::UI12(0)
        }
    );


    const LA32Trait LA32Traits::NORMAL_2ROFFS16 = LA32Trait(
        {
            new LA32Trait::Operand::GPR::RJ(0),
            new LA32Trait::Operand::GPR::RD(1)
        },
        {
            new LA32Trait::Source::PC(0)
        },
        {
            new LA32Trait::Destination::PC(0)
        },
        {
            new LA32Trait::Immediate::OFFS16(0)
        }
    );

    const LA32Trait LA32Traits::NORMAL_OFFS26 = LA32Trait(
        {},
        {
            new LA32Trait::Source::PC(0)
        },
        {
            new LA32Trait::Destination::PC(0)
        },
        {
            new LA32Trait::Immediate::OFFS26(0)
        }
    );

    const LA32Trait LA32Traits::NORMAL_OFFS26R1 = LA32Trait(
        {},
        {
            new LA32Trait::Source::PC(0)
        },
        {
            new LA32Trait::Destination::GPR::R1(0),
            new LA32Trait::Destination::PC(1)
        },
        {
            new LA32Trait::Immediate::OFFS26(0)
        }
    );


    const LA32Trait LA32Traits::NORMAL_LOAD_2RSI12 = LA32Trait(
        {
            new LA32Trait::Operand::GPR::RJ(0)
        },
        {
            new LA32Trait::Source::Memory::NormalLoad(0)
        },
        {
            new LA32Trait::Destination::GPR::RD(0),
            new LA32Trait::Destination::Memory::NormalLoadAddress(1)
        },
        {
            new LA32Trait::Immediate::SI12(0)
        }
    );

    const LA32Trait LA32Traits::NORMAL_STORE_2RSI12 = LA32Trait(
        {
            new LA32Trait::Operand::GPR::RJ(0),
            new LA32Trait::Operand::GPR::RD(1)
        },
        {},
        {
            new LA32Trait::Destination::Memory::NormalStore(0),
            new LA32Trait::Destination::Memory::NormalStoreAddress(1)
        },
        {
            new LA32Trait::Immediate::SI12(0)
        }
    );


    const LA32Trait LA32Traits::EXTENDED_1RI20 = LA32Trait(
        {},
        {},
        {
            new LA32Trait::Destination::GPR::RD(0)
        },
        {
            new LA32Trait::Immediate::SI20(0)
        }
    );

    const LA32Trait LA32Traits::EXTENDED_1RI20PC = LA32Trait(
        {},
        {
            new LA32Trait::Source::PC(0)
        },
        {
            new LA32Trait::Destination::GPR::RD(0)
        },
        {
            new LA32Trait::Immediate::SI20(0)
        }
    );


    const LA32Trait LA32Traits::EXTENDED_2RI5 = LA32Trait(
        {
            new LA32Trait::Operand::GPR::RJ(0)
        },
        {},
        {
            new LA32Trait::Destination::GPR::RD(0)
        },
        {
            new LA32Trait::Immediate::UI5(0)
        }
    );


    const LA32Trait LA32Traits::JIRL_2ROFFS16 = LA32Trait(
        {
            new LA32Trait::Operand::GPR::RJ(0)
        },
        {
            new LA32Trait::Source::PC(0)
        },
        {
            new LA32Trait::Destination::GPR::RD(0),
            new LA32Trait::Destination::PC(1)
        },
        {
            new LA32Trait::Immediate::OFFS16(0)
        }
    );
}
