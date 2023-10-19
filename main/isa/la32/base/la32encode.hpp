#pragma once
//
// LA32R (NSCSCC) ISA Emulator (Jasse)
//
// Instruction encoding helper macros
//

#ifndef __HEADER_JASSE_LA32__BASE_ENCODE
#define __HEADER_JASSE_LA32__BASE_ENCODE


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


#endif