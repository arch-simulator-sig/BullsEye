#pragma once
//
// MIPS32 (NSCSCC) ISA Definitions
//
//
//

#include <cstdint>

#include "mips32r5def.hpp"


#ifndef __HEADER_MIPS32_DEFINITIONS

// Type definition of Architecture Register Value
typedef     uint32_t        arch32_t;

// Type definition of Immediate Value
typedef     uint32_t        imm_t;

// Type definition of PC Register Value
typedef     uint32_t        pc_t;
    
// Type definition of Raw Instruction
typedef     uint32_t        insnraw_t;

// Integral extension
#define SEXT32_H(expr)      ((uint32_t) ((int16_t)  (expr)))
#define SEXT32_B(expr)      ((uint32_t) ((int8_t)   (expr)))
#define SEXT32_W(expr)      ((uint32_t) (           (expr)))

#define SEXT32(expr, len)   ((uint32_t) (((int32_t) (expr)) << (32 - len)) >> (32 - len))

#define SEXT32_IMM16(expr)  SEXT32_H(expr)
#define SEXT32_IMM26(expr)  SEXT32(expr, 26)

#define ZEXT32_H(expr)      ((uint32_t) ((uint16_t) (expr)))
#define ZEXT32_B(expr)      ((uint32_t) ((uint8_t)  (expr)))
#define ZEXT32_W(expr)      ((uint32_t) (           (expr)))

// Integral extension alias
#define SEXT32_HALF_WORD    SEXT32_H
#define SEXT32_BYTE         SEXT32_B
#define SEXT32_WORD         SEXT32_W

#define ZEXT32_HALF_WORD    ZEXT32_H
#define ZEXT32_BYTE         ZEXT32_B
#define ZEXT32_WORD         ZEXT32_W


// Standard operand format
#define GET_MIPS32_OEPRAND(insn, mask, offset) \
    ((insn & mask) >> offset)

#define GET_MIPS32_STD_OPERAND(insn, name) \
    ((insn & name##_MASK) >> name##_OFFSET)

#define SET_MIPS32_OPERAND(dst, mask, offset, value) \
    dst = ((dst & ~mask) | ((value << offset) & mask))

#define SET_MIPS32_STD_OPERAND(dst, name, value) \
    dst = ((dst & ~name##_MASK) | ((value << name##_OFFSET) & name##_MASK))


// Basis
#define MIPS32_ARCH_REG_COUNT                   32

#define MIPS32_FUNCT_MASK                       0x0000003FU
#define MIPS32_FUNCT_OFFSET                     0

#define MIPS32_SHAMT_MASK                       0x000007C0U
#define MIPS32_SHAMT_OFFSET                     6

#define MIPS32_RD_MASK                          0x0000F800U
#define MIPS32_RD_OFFSET                        11

#define MIPS32_RT_MASK                          0x001F0000U
#define MIPS32_RT_OFFSET                        16

#define MIPS32_RS_MASK                          0x03E00000U
#define MIPS32_RS_OFFSET                        21

#define MIPS32_OPCODE_MASK                      0xFC000000U
#define MIPS32_OPCODE_OFFSET                    26

#define MIPS32_IMM16_MASK                       0x0000FFFFU
#define MIPS32_IMM16_OFFSET                     0

#define MIPS32_IMM26_MASK                       0x03FFFFFFU
#define MIPS32_IMM26_OFFSET                     0


// General registers
#define MIPS32_GR_X0                            0
#define MIPS32_GR_X1                            1
#define MIPS32_GR_X2                            2
#define MIPS32_GR_X3                            3
#define MIPS32_GR_X4                            4
#define MIPS32_GR_X5                            5
#define MIPS32_GR_X6                            6
#define MIPS32_GR_X7                            7
#define MIPS32_GR_X8                            8
#define MIPS32_GR_X9                            9
#define MIPS32_GR_X10                           10
#define MIPS32_GR_X11                           11
#define MIPS32_GR_X12                           12
#define MIPS32_GR_X13                           13
#define MIPS32_GR_X14                           14
#define MIPS32_GR_X15                           15
#define MIPS32_GR_X16                           16
#define MIPS32_GR_X17                           17
#define MIPS32_GR_X18                           18
#define MIPS32_GR_X19                           19
#define MIPS32_GR_X20                           20
#define MIPS32_GR_X21                           21
#define MIPS32_GR_X22                           22
#define MIPS32_GR_X23                           23
#define MIPS32_GR_X24                           24
#define MIPS32_GR_X25                           25
#define MIPS32_GR_X26                           26
#define MIPS32_GR_X27                           27
#define MIPS32_GR_X28                           28
#define MIPS32_GR_X29                           29
#define MIPS32_GR_X30                           30
#define MIPS32_GR_X31                           31

// General registers (ABI-defined)
// $zero        : Always zero.
#define MIPS32_GR_ZERO                          0

// $at          : Assembler temporary.
#define MIPS32_GR_AT                            1

// $v0 ... $v1  : Function return values.
#define MIPS32_GR_V0                            2
#define MIPS32_GR_V1                            3

// $a0 ... $a3  : Function parameters.
#define MIPS32_GR_A0                            4
#define MIPS32_GR_A1                            5
#define MIPS32_GR_A2                            6
#define MIPS32_GR_A3                            7

// $t0 ... $t7  : Temporary. Not saved on function call.
#define MIPS32_GR_T0                            8
#define MIPS32_GR_T1                            9
#define MIPS32_GR_T2                            10
#define MIPS32_GR_T3                            11
#define MIPS32_GR_T4                            12
#define MIPS32_GR_T5                            13
#define MIPS32_GR_T6                            14
#define MIPS32_GR_T7                            15

// $s0 ... $s7  : Temporary. Saved on function call.
#define MIPS32_GR_S0                            16
#define MIPS32_GR_S1                            17
#define MIPS32_GR_S2                            18
#define MIPS32_GR_S3                            19
#define MIPS32_GR_S4                            20
#define MIPS32_GR_S5                            21
#define MIPS32_GR_S6                            22
#define MIPS32_GR_S7                            23

// $t8 ... $t9  : Temporary. Not saved on function call.
#define MIPS32_GR_T8                            24
#define MIPS32_GR_T9                            25

// $k0 ... $k1  : Reserved for trap procedure.
#define MIPS32_GR_K0                            26
#define MIPS32_GR_K1                            27

// $gp          : Global pointer.
#define MIPS32_GR_GP                            28

// $sp          : Stack pointer.
#define MIPS32_GR_SP                            29

// $fp          : Frame pointer.
#define MIPS32_GR_FP                            30

// $ra          : Return address.
#define MIPS32_GR_RA                            31

#endif
