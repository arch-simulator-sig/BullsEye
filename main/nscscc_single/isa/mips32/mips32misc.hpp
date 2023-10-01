#pragma once
//
// MIPS32 Instruction Set Architecture 
//
// Miscs and utilities
//

#include "mips32.hpp"

#include <sstream>
#include <iomanip>


#define ENCODE_MIPS32_STD_OPERAND(val, name) \
    ((val & (name##_MASK >> name##_OFFSET)) << name##_OFFSET)


#define ENCODE_MIPS32_TYPE_I(opcode, rs, rt, imm) \
    ( ENCODE_MIPS32_STD_OPERAND(opcode , MIPS32_OPCODE) \
    | ENCODE_MIPS32_STD_OPERAND(rs     , MIPS32_RS) \
    | ENCODE_MIPS32_STD_OPERAND(rt     , MIPS32_RT) \
    | ENCODE_MIPS32_STD_OPERAND(imm    , MIPS32_IMM16))

#define ENCODE_MIPS32_TYPE_J(opcode, jindex) \
    ( ENCODE_MIPS32_STD_OPERAND(opcode , MIPS32_OPCODE) \
    | ENCODE_MIPS32_STD_OPERAND(jindex , MIPS32_IMM26))

#define ENCODE_MIPS32_TYPE_R(opcode, rs, rt, rd, shamt, funct) \
    ( ENCODE_MIPS32_STD_OPERAND(opcode , MIPS32_OPCODE) \
    | ENCODE_MIPS32_STD_OPERAND(rs     , MIPS32_RS) \
    | ENCODE_MIPS32_STD_OPERAND(rt     , MIPS32_RT) \
    | ENCODE_MIPS32_STD_OPERAND(rd     , MIPS32_RD) \
    | ENCODE_MIPS32_STD_OPERAND(shamt  , MIPS32_SHAMT) \
    | ENCODE_MIPS32_STD_OPERAND(funct  , MIPS32_FUNCT))


// Implementation of Instruction Textualizers
namespace Jasse {

#define MIPS32_TEXTUALIZE_GPR_AS_ABI
#define MIPS32_TEXTUALIZE_GPR_WITH_PREFIX

#define MIPS32_TEXTUALIZE_NAME_ALIGNMENT                    8

#ifdef MIPS32_TEXTUALIZE_GPR_AS_ABI
    std::string TextualizeMIPS32GPR(int GPR) noexcept
    {
        // ABI form

        static const std::string ABI_NAMES[] = {
            "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
            "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
            "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
            "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"
        };

        if (GPR < 0 || GPR > 31)
        {
            std::ostringstream oss;

#ifdef MIPS32_TEXTUALIZE_GPR_WITH_PREFIX
            oss << "$";        
#else
            oss << "x";
#endif

            oss << GPR;

            return oss.str();
        }

#ifdef MIPS32_TEXTUALIZE_GPR_WITH_PREFIX
        std::ostringstream oss;

        oss << "$";
        oss << ABI_NAMES[GPR];

        return oss.str();
#else
        return ABI_NAMES[GPR];
#endif
    }
#else

    std::string TextualizeMIPS32GPR(int GPR) noexcept
    {
        std::ostringstream oss;

#ifdef MIPS32_TEXTUALIZE_GPR_WITH_PREFIX
        oss << "$";        
#else
        oss << "x";
#endif

        oss << std::left << std::setw(2) << GPR;

        return oss.str();
    }
#endif

    inline std::string TextualizeMIPS32Name(const std::string& name) noexcept
    {
        int alignment = MIPS32_TEXTUALIZE_NAME_ALIGNMENT - (name.length() % MIPS32_TEXTUALIZE_NAME_ALIGNMENT);

        std::ostringstream oss;

        oss << name;

        for (int i = 0; i < alignment; i++)
            oss << " ";

        return oss.str();
    }

    std::string TextualizeMIPS32TypeR(const MIPS32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeMIPS32Name(insn.GetName());
        oss << TextualizeMIPS32GPR(insn.GetRD()) << ", ";
        oss << TextualizeMIPS32GPR(insn.GetRS()) << ", ";
        oss << TextualizeMIPS32GPR(insn.GetRT());

        return oss.str();
    }

    std::string TextualizeMIPS32TypeI(const MIPS32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeMIPS32Name(insn.GetName());
        oss << TextualizeMIPS32GPR(insn.GetRT()) << ", ";
        oss << TextualizeMIPS32GPR(insn.GetRS()) << ", ";
        oss << "0x" << std::hex << std::setw(4) << std::setfill('0') << insn.GetImmediate();

        return oss.str();
    }

    std::string TextualizeMIPS32TypeJ(const MIPS32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeMIPS32Name(insn.GetName());
        oss << "0x" << std::hex << std::setw(7) << std::setfill('0') << insn.GetJumpIndex();

        return oss.str();
    }

    std::string TextualizeMIPS32LoadStore(const MIPS32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeMIPS32Name(insn.GetName());
        oss << TextualizeMIPS32GPR(insn.GetRT()) << ", ";
        oss << "0x" << std::hex << std::setw(4) << std::setfill('0') << insn.GetImmediate();
        oss << "(" << TextualizeMIPS32GPR(insn.GetRS()) << ")";

        return oss.str();
    }

    std::string TextualizeMIPS32RtExclusiveTypeI(const MIPS32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeMIPS32Name(insn.GetName());
        oss << TextualizeMIPS32GPR(insn.GetRT()) << ", ";
        oss << "0x" << std::hex << std::setw(4) << std::setfill('0') << insn.GetImmediate();

        return oss.str();
    }

    std::string TextualizeMIPS32RsExclusiveTypeI(const MIPS32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeMIPS32Name(insn.GetName());
        oss << TextualizeMIPS32GPR(insn.GetRS()) << ", ";
        oss << "0x" << std::hex << std::setw(4) << std::setfill('0') << insn.GetImmediate();

        return oss.str();
    }

    std::string TextualizeMIPS32RdExcludedTypeR(const MIPS32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeMIPS32Name(insn.GetName());
        oss << TextualizeMIPS32GPR(insn.GetRS()) << ", ";
        oss << TextualizeMIPS32GPR(insn.GetRT());

        return oss.str();
    }

    std::string TextualizeMIPS32RtExcludedTypeR(const MIPS32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeMIPS32Name(insn.GetName());
        oss << TextualizeMIPS32GPR(insn.GetRD()) << ", ";
        oss << TextualizeMIPS32GPR(insn.GetRS());

        return oss.str();
    }

    std::string TextualizeMIPS32RsExclusiveTypeR(const MIPS32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeMIPS32Name(insn.GetName());
        oss << TextualizeMIPS32GPR(insn.GetRS());

        return oss.str();
    }

     std::string TextualizeMIPS32RdExclusiveTypeR(const MIPS32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeMIPS32Name(insn.GetName());
        oss << TextualizeMIPS32GPR(insn.GetRD());

        return oss.str();
    }

    std::string TextualizeMIPS32ShiftConstant(const MIPS32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeMIPS32Name(insn.GetName());
        oss << TextualizeMIPS32GPR(insn.GetRD()) << ", ";
        oss << TextualizeMIPS32GPR(insn.GetRT()) << ", ";
        oss << insn.GetShamt();

        return oss.str();
    }
}
