#pragma once
//
// LA32 Instruction Set Architecture 
//
// Miscs and utilities
//

#include "la32.hpp"

#include <sstream>
#include <iomanip>


#define ENCODE_LA32_STD_OPERAND(val, name) \
    ((val & (name##_MASK >> name##_OFFSET)) << name##_OFFSET)


#define ENCODE_LA32_IMM8(value) \
    ( ENCODE_LA32_STD_OPERAND(value, LA32_IMM8))

#define ENCODE_LA32_IMM12(value) \
    ( ENCODE_LA32_STD_OPERAND(value, LA32_IMM12))

#define ENCODE_LA32_IMM14(value) \
    ( ENCODE_LA32_STD_OPERAND(value, LA32_IMM14))

#define ENCODE_LA32_IMM16(value) \
    ( ENCODE_LA32_STD_OPERAND(value, LA32_IMM16))

#define ENCODE_LA32_IMM21(value) \
    ( ENCODE_LA32_STD_OPERAND((value >> 16), LA32_IMM21_U5) \
    | ENCODE_LA32_STD_OPERAND((value & 0xFFFF), LA32_IMM21_L16))

#define ENCODE_LA32_IMM26(value) \
    ( ENCODE_LA32_STD_OPERAND((value >> 16), LA32_IMM26_U10) \
    | ENCODE_LA32_STD_OPERAND((value & 0xFFFF), LA32_IMM26_L16))

#define ENCODE_LA32_X_IMM20(value) \
    ( (value & 0x000FFFFF) << 5)

#define ENCODE_LA32_X_IMM5(value) \
    ( (value & 0x0000001F) << 10)


#define ENCODE_LA32_TYPE_2R(opcode_u6, opcode_l16, rj, rd) \
    ( ENCODE_LA32_STD_OPERAND(opcode_u6 , LA32_OPCODE_U6) \
    | ENCODE_LA32_STD_OPERAND(opcode_l16, LA32_OPCODE_L16) \
    | ENCODE_LA32_STD_OPERAND(rj        , LA32_RJ) \
    | ENCODE_LA32_STD_OPERAND(rd        , LA32_RD))

#define ENCODE_LA32_STD_TYPE_2R(name, rj, rd) \
    ENCODE_LA32_TYPE_2R(LA32_OPCODE_U6_##name, LA32_OPCODE_L16_##name, rj, rd)

#define ENCODE_LA32_TYPE_3R(opcode_u6, opcode_l11, rk, rj, rd) \
    ( ENCODE_LA32_STD_OPERAND(opcode_u6 , LA32_OPCODE_U6) \
    | ENCODE_LA32_STD_OPERAND(opcode_l11, LA32_OPCODE_L11) \
    | ENCODE_LA32_STD_OPERAND(rk        , LA32_RK) \
    | ENCODE_LA32_STD_OPERAND(rj        , LA32_RJ) \
    | ENCODE_LA32_STD_OPERAND(rd        , LA32_RD))

#define ENCODE_LA32_STD_TYPE_3R(name, rk, rj, rd) \
    ENCODE_LA32_TYPE_3R(LA32_OPCODE_U6_##name, LA32_OPCODE_L11_##name, rk, rj, rd)

#define ENCODE_LA32_TYPE_4R(opcode_u6, opcode_l6, ra, rk, rj, rd) \
    ( ENCODE_LA32_STD_OPERAND(opcode_u6 , LA32_OPCODE_U6) \
    | ENCODE_LA32_STD_OPERAND(opcode_l6 , LA32_OPCODE_L6) \
    | ENCODE_LA32_STD_OPERAND(ra        , LA32_RA) \
    | ENCODE_LA32_STD_OPERAND(rk        , LA32_RK) \
    | ENCODE_LA32_STD_OPERAND(rj        , LA32_RJ) \
    | ENCODE_LA32_STD_OPERAND(rd        , LA32_RD))

#define ENCODE_LA32_STD_TYPE_4R(name, ra, rk, rj, rd) \
    ENCODE_LA32_TYPE_4R(LA32_OPCODE_U6_##name, LA32_OPCODE_L6_##name, ra, rk, rj, rd)

#define ENCODE_LA32_TYPE_2RI8(opcode_u6, opcode_l8, imm8, rj, rd) \
    ( ENCODE_LA32_STD_OPERAND(opcode_u6 , LA32_OPCODE_U6) \
    | ENCODE_LA32_STD_OPERAND(opcode_l8 , LA32_OPCODE_L8) \
    | ENCODE_LA32_STD_OPERAND(rj        , LA32_RJ) \
    | ENCODE_LA32_STD_OPERAND(rd        , LA32_RD) \
    | ENCODE_LA32_IMM8(imm8))

#define ENCODE_LA32_STD_TYPE_2RI8(name, imm8, rj, rd) \
    ENCODE_LA32_TYPE_2RI8(LA32_OPCODE_U6_##name, LA32_OPCODE_L8_##name, imm8, rj, rd)

#define ENCODE_LA32_TYPE_2RI12(opcode_u6, opcode_l4, imm12, rj, rd) \
    ( ENCODE_LA32_STD_OPERAND(opcode_u6 , LA32_OPCODE_U6) \
    | ENCODE_LA32_STD_OPERAND(opcode_l4 , LA32_OPCODE_L4) \
    | ENCODE_LA32_STD_OPERAND(rj        , LA32_RJ) \
    | ENCODE_LA32_STD_OPERAND(rd        , LA32_RD) \
    | ENCODE_LA32_IMM12(imm12))

#define ENCODE_LA32_STD_TYPE_2RI12(name, imm12, rj, rd) \
    ENCODE_LA32_TYPE_2RI12(LA32_OPCODE_U6_##name, LA32_OPCODE_L4_##name, imm12, rj, rd)

#define ENCODE_LA32_TYPE_2RI14(opcode_u6, opcode_l2, imm14, rj, rd) \
    ( ENCODE_LA32_STD_OPERAND(opcode_u6 , LA32_OPCODE_U6) \
    | ENCODE_LA32_STD_OPERAND(opcode_l2 , LA32_OPCODE_L2) \
    | ENCODE_LA32_STD_OPERAND(rj        , LA32_RJ) \
    | ENCODE_LA32_STD_OPERAND(rd        , LA32_RD) \
    | ENCODE_LA32_IMM14(imm14))

#define ENCODE_LA32_STD_TYPE_2RI14(name, imm14, rj, rd) \
    ENCODE_LA32_TYPE_2RI14(LA32_OPCODE_U6_##name, LA32_OPCODE_L2_##name, imm14, rj, rd)

#define ENCODE_LA32_TYPE_2RI16(opcode_u6, imm16, rj, rd) \
    ( ENCODE_LA32_STD_OPERAND(opcode_u6 , LA32_OPCODE_U6) \
    | ENCODE_LA32_STD_OPERAND(rj        , LA32_RJ) \
    | ENCODE_LA32_STD_OPERAND(rd        , LA32_RD) \
    | ENCODE_LA32_IMM16(imm16))

#define ENCODE_LA32_STD_TYPE_2RI16(name, imm16, rj, rd) \
    ENCODE_LA32_TYPE_2RI16(LA32_OPCODE_U6_##name, imm16, rj, rd)

#define ENCODE_LA32_TYPE_1RI21(opcode_u6, imm21, rj) \
    ( ENCODE_LA32_STD_OPERAND(opcode_u6 , LA32_OPCODE_U6) \
    | ENCODE_LA32_STD_OPERAND(rj        , LA32_RJ) \
    | ENCODE_LA32_IMM21(imm21))

#define ENCODE_LA32_STD_TYPE_1RI21(name, imm21, rj) \
    ENCODE_LA32_TYPE_1RI21(LA32_OPCODE_U6_##name, imm21, rj)

#define ENCODE_LA32_TYPE_I26(opcode_u6, imm26) \
    ( ENCODE_LA32_STD_OPERAND(opcode_u6 , LA32_OPCODE_U6) \
    | ENCODE_LA32_IMM26(imm26))

#define ENCODE_LA32_STD_TYPE_I26(name, imm26) \
    ENCODE_LA32_TYPE_I26(LA32_OPCODE_U6_##name, imm26)


#define ENCODE_LA32_TYPE_X_1RI20(opcode_u6, opcode_l1, imm20, rd) \
    ( ENCODE_LA32_STD_OPERAND(opcode_u6 , LA32_OPCODE_U6) \
    | ENCODE_LA32_STD_OPERAND(opcode_l1 , LA32_OPCODE_L1) \
    | ENCODE_LA32_STD_OPERAND(rd        , LA32_RD) \
    | ENCODE_LA32_X_IMM20(imm20))

#define ENCODE_LA32_STD_TYPE_X_1RI20(name, imm20, rd) \
    ENCODE_LA32_TYPE_X_1RI20(LA32_OPCODE_U6_##name, LA32_OPCODE_L1_##name, imm20, rd)


#define ENCODE_LA32_TYPE_X_2RI5(opcode_u6, opcode_l11, imm5, rj, rd) \
    ( ENCODE_LA32_STD_OPERAND(opcode_u6 , LA32_OPCODE_U6) \
    | ENCODE_LA32_STD_OPERAND(opcode_l11, LA32_OPCODE_L11) \
    | ENCODE_LA32_STD_OPERAND(rj        , LA32_RJ) \
    | ENCODE_LA32_STD_OPERAND(rd        , LA32_RD) \
    | ENCODE_LA32_X_IMM5(imm5))

#define ENCODE_LA32_STD_TYPE_X_2RI5(name, imm5, rj, rd) \
    ENCODE_LA32_TYPE_X_2RI5(LA32_OPCODE_U6_##name, LA32_OPCODE_L11_##name, imm5, rj, rd)



// Implementation of Instruction Textualizers
namespace Jasse {

#define LA32_TEXTUALIZE_GPR_AS_ABI
#define LA32_TEXTUALIZE_GPR_WITH_PREFIX

#define LA32_TEXTUALIZE_NAME_ALIGNMENT              8

#ifdef LA32_TEXTUALIZE_GPR_AS_ABI
    inline std::string TextualizeLA32GPR(int GPR) noexcept
    {
        // ABI form

        static const std::string ABI_NAMES[] = {
            "zero", 
            "ra  ", 
            "tp  ", 
            "sp  ",
            "a0  ", "a1  ",
            "a2  ", "a3  ", "a4  ", "a5  ", "a6  ", "a7  ",
            "t0  ", "t1  ", "t2  ", "t3  ", "t4  ", "t5  ", "t6  ", "t7  ", "t8  ",
            "r21 ",
            "fp  ",
            "s0  ", "s1  ", "s2  ", "s3  ", "s4  ", "s5  ", "s6  ", "s7  ", "s8  "
        };

        if (GPR < 0 || GPR > 31)
        {
            std::ostringstream oss;

#ifdef LA32_TEXTUALIZE_GPR_WITH_PREFIX
            oss << "$";
#else
            oss << "x";
#endif

            oss << GPR;

            return oss.str();
        }

#ifdef LA32_TEXTUALIZE_GPR_WITH_PREFIX
        std::ostringstream oss;

        oss << "$";
        oss << ABI_NAMES[GPR];

        return oss.str();
#else
        return ABI_NAMES[GPR];
#endif
    }

#else
    inline std::string TextualizeLA32GPR(int GPR) noexcept
    {
        std::ostringstream oss;

#ifdef LA32_TEXTUALIZE_GPR_WITH_PREFIX
        oss << "$r";
#else
        oss << "r";
#endif

        oss << std::left << std::setw(2) << GPR;

        return oss.str();
    }
#endif

    inline std::string TextualizeLA32Name(const std::string& name) noexcept
    {
        int alignment = LA32_TEXTUALIZE_NAME_ALIGNMENT - (name.length() % LA32_TEXTUALIZE_NAME_ALIGNMENT);

        std::ostringstream oss;

        oss << name;

        for (int i = 0; i < alignment; i++)
            oss << " ";

        return oss.str();
    }

    inline std::string TextualizeLA32Type2R(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ());

        return oss.str();
    }
    
    inline std::string TextualizeLA32Type3R(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRK());

        return oss.str();
    }

    inline std::string TextualizeLA32Type4R(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRK()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRA());

        return oss.str();
    }

    inline std::string TextualizeLA32Type2RI8(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << "0x" << std::hex << std::setw(2) << std::setfill('0') << insn.GetImm8();

        return oss.str();
    }

    inline std::string TextualizeLA32Type2RI12(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << "0x" << std::hex << std::setw(3) << std::setfill('0') << insn.GetImm12();

        return oss.str();
    }

    inline std::string TextualizeLA32Type2RI14(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << "0x" << std::hex << std::setw(4) << std::setfill('0') << insn.GetImm14();

        return oss.str();
    }

    inline std::string TextualizeLA32Type2RI16(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << "0x" << std::hex << std::setw(4) << std::setfill('0') << insn.GetImm16();

        return oss.str();
    }

    inline std::string TextualizeLA32TypeX2RI5(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << insn.GetExImm5();

        return oss.str();
    }

    inline std::string TextualizeLA32Type1RI21(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << "0x" << std::hex << std::setw(6) << std::setfill('0') << insn.GetImm21();

        return oss.str();
    }

    inline std::string TextualizeLA32TypeX1RI20(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << "0x" << std::hex << std::setw(5) << std::setfill('0') << insn.GetExImm20();

        return oss.str();
    }

    inline std::string TextualizeLA32TypeI26(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << "0x" << std::hex << std::setw(7) << std::setfill('0') << insn.GetImm26();

        return oss.str();
    }
}
