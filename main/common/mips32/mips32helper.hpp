#pragma once
//
// MIPS-32 ISA helper utilities
// 
//

#include <cstdint>

#include "mips32def.hpp"


namespace BullsEye::MIPS32 {

    // Type definition of Architecture Register Value
    typedef     uint32_t        arch32_t;

    // Type definition of Immediate Value
    typedef     uint32_t        imm_t;

    // Type definition of PC Register Value
    typedef     uint32_t        pc_t;
    
    // Type definition of Raw Instruction
    typedef     uint32_t        insnraw_t;


    // MIPS32 Instruction Helper
    class MIPS32Instruction {
    private:
        insnraw_t               insn;

    public:
        MIPS32Instruction(insnraw_t insn = 0) noexcept;

        insnraw_t               GetRaw() const noexcept;
        imm_t                   GetImmediate() const noexcept;
        imm_t                   GetJumpIndex() const noexcept;
        unsigned int            GetOpcode() const noexcept;
        unsigned int            GetRS() const noexcept;
        unsigned int            GetRT() const noexcept;
        unsigned int            GetRD() const noexcept;
        unsigned int            GetShamt() const noexcept;
        unsigned int            GetFunct() const noexcept;

        void                    SetRaw(insnraw_t insn) noexcept;
        void                    SetImmediate(imm_t imm) noexcept;
        void                    SetJumpIndex(imm_t imm) noexcept;
        void                    SetOpcode(unsigned int opcode) noexcept;
        void                    SetRS(unsigned int rs) noexcept;
        void                    SetRT(unsigned int rt) noexcept;
        void                    SetRD(unsigned int rd) noexcept;
        void                    SetShamt(unsigned int shamt) noexcept;
        void                    SetFunct(unsigned int funct) noexcept;
    };


    // MIPS32 Instruction Helper functions
    imm_t           GetImmediate(insnraw_t insn) noexcept;
    imm_t           GetJumpIndex(insnraw_t insn) noexcept;
    unsigned int    GetOpcode(insnraw_t insn) noexcept;
    unsigned int    GetRS(insnraw_t insn) noexcept;
    unsigned int    GetRT(insnraw_t insn) noexcept;
    unsigned int    GetRD(insnraw_t insn) noexcept;
    unsigned int    GetShamt(insnraw_t insn) noexcept;
    unsigned int    GetFunct(insnraw_t insn) noexcept;

    insnraw_t       SetImmediate(insnraw_t insn, imm_t imm) noexcept;
    insnraw_t       SetJumpIndex(insnraw_t insn, imm_t imm) noexcept;
    insnraw_t       SetOpcode(insnraw_t insn, unsigned int opcode) noexcept;
    insnraw_t       SetRS(insnraw_t insn, unsigned int rs) noexcept;
    insnraw_t       SetRT(insnraw_t insn, unsigned int rt) noexcept;
    insnraw_t       SetRD(insnraw_t insn, unsigned int rd) noexcept;
    insnraw_t       SetShamt(insnraw_t insn, unsigned int shamt) noexcept;
    insnraw_t       SetFunct(insnraw_t insn, unsigned int funct) noexcept;
}


// Implementation of: MIPS32Instruction
namespace BullsEye::MIPS32 {
    //
    // insnraw_t               insn;
    //

    MIPS32Instruction::MIPS32Instruction(insnraw_t insn) noexcept
        : insn      (insn)
    { }

    MIPS32Instruction::~MIPS32Instruction() noexcept
    { }

    inline insnraw_t MIPS32Instruction::GetRaw() const noexcept
    {
        return insn;
    }

    inline imm_t MIPS32Instruction::GetImmediate() const noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_IMM16);
    }

    inline imm_t MIPS32Instruction::GetJumpIndex() const noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_IMM26);
    }

    inline unsigned int MIPS32Instruction::GetOpcode() const noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_OPCODE);
    }

    inline unsigned int MIPS32Instruction::GetRS() const noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_RS);
    }

    inline unsigned int MIPS32Instruction::GetRT() const noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_RT);
    }

    inline unsigned int MIPS32Instruction::GetRD() const noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_RD);
    }

    inline unsigned int MIPS32Instruction::GetShamt() const noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_SHAMT);
    }

    inline unsigned int MIPS32Instruction::GetFunct() const noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_FUNCT);
    }

    inline void MIPS32Instruction::SetRaw(insnraw_t insn) noexcept
    {
        this->insn = insn;
    }

    inline void MIPS32Instruction::SetImmediate(imm_t imm) noexcept
    {
        SET_MIPS32_STD_OPERAND(this->insn, MIPS32_IMM16, imm);
    }

    inline void MIPS32Instruction::SetJumpIndex(imm_t imm) noexcept
    {
        SET_MIPS32_STD_OPERAND(this->insn, MIPS32_IMM26, imm);
    }

    inline void MIPS32Instruction::SetOpcode(unsigned int opcode) noexcept
    {
        SET_MIPS32_STD_OPERAND(this->insn, MIPS32_OPCODE, opcode);
    }

    inline void MIPS32Instruction::SetRS(unsigned int rs) noexcept
    {
        SET_MIPS32_STD_OPERAND(this->insn, MIPS32_RS, rs);
    }

    inline void MIPS32Instruction::SetRT(unsigned int rt) noexcept
    {
        SET_MIPS32_STD_OPERAND(this->insn, MIPS32_RT, rt);
    }

    inline void MIPS32Instruction::SetRD(unsigned int rd) noexcept
    {
        SET_MIPS32_STD_OPERAND(this->insn, MIPS32_RD, rd);
    }

    inline void MIPS32Instruction::SetShamt(unsigned int shamt) noexcept
    {
        SET_MIPS32_STD_OPERAND(this->insn, MIPS32_SHAMT, shamt);
    }

    inline void MIPS32Instruction::SetFunct(unsigned int funct) noexcept
    {
        SET_MIPS32_STD_OPERAND(this->insn, MIPS32_FUNCT, funct);
    }
}


// Implementation of helper functions
namespace BullsEye::MIPS32 {

    imm_t GetImmediate(insnraw_t insn) noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_IMM16);
    }

    imm_t GetJumpIndex(insnraw_t insn) noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_IMM26);
    }

    unsigned int GetOpcode(insnraw_t insn) noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_OPCODE);
    }

    unsigned int GetRS(insnraw_t insn) noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_RS);
    }

    unsigned int GetRT(insnraw_t insn) noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_RT);
    }

    unsigned int GetRD(insnraw_t insn) noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_RD);
    }

    unsigned int GetShamt(insnraw_t insn) noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_SHAMT);
    }

    unsigned int GetFunct(insnraw_t insn) noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_FUNCT);
    }

    insnraw_t SetImmediate(insnraw_t insn, imm_t imm) noexcept
    {
        return SET_MIPS32_STD_OPERAND(insn, MIPS32_IMM16, imm);
    }

    insnraw_t SetJumpIndex(insnraw_t insn, imm_t imm) noexcept
    {
        return SET_MIPS32_STD_OPERAND(insn, MIPS32_IMM26, imm);
    }

    insnraw_t SetOpcode(insnraw_t insn, unsigned int opcode) noexcept
    {
        return SET_MIPS32_STD_OPERAND(insn, MIPS32_OPCODE, opcode);
    }

    insnraw_t SetRS(insnraw_t insn, unsigned int rs) noexcept
    {
        return SET_MIPS32_STD_OPERAND(insn, MIPS32_RS, rs);
    }

    insnraw_t SetRT(insnraw_t insn, unsigned int rt) noexcept
    {
        return SET_MIPS32_STD_OPERAND(insn, MIPS32_RT, rt);
    }

    insnraw_t SetRD(insnraw_t insn, unsigned int rd) noexcept
    {
        return SET_MIPS32_STD_OPERAND(insn, MIPS32_RD, rd);
    }

    insnraw_t SetShamt(insnraw_t insn, unsigned int shamt) noexcept
    {
        return SET_MIPS32_STD_OPERAND(insn, MIPS32_SHAMT, shamt);
    }

    insnraw_t SetFunct(insnraw_t insn, unsigned int funct) noexcept
    {
        return SET_MIPS32_STD_OPERAND(insn, MIPS32_FUNCT, funct);
    }

    insnraw_t SetImmediate(insnraw_t insn, imm_t imm) noexcept
    {
        return SET_MIPS32_STD_OPERAND(insn, MIPS32_IMM16, imm);
    }
}
