#pragma once
//
// LoongArch32R (NSCSCC) ISA Definitions
//
//
//

#include <cstdint>


#define __HEADER_LA32R_DEFINITIONS


// Global type definitions
namespace Jasse {

    // Type definition of Architecture Register Value
    typedef     uint32_t        arch32_t;

    // Type definition of Immediate Value
    typedef     uint32_t        imm_t;

    // Type definition of PC Register Value
    typedef     uint32_t        pc_t;

    // Type definition of Raw Instruction
    typedef     uint32_t        insnraw_t;


    // Type definition of Error Number
    typedef     uint32_t        errno_t;


    // LA32R Codepoint (declaration)
    class LA32Codepoint;

    // LA32R Codepoint Type
    typedef enum class __tag_LA32CodepointType {
        TYPE_2R,
        TYPE_3R,
        TYPE_4R,
        TYPE_2RI8,
        TYPE_2RI12,
        TYPE_2RI14,
        TYPE_2RI16,
        TYPE_1RI21,
        TYPE_I26,
        TYPE_X_1RI20,
        TYPE_X_2RI5
    } LA32CodepointType;

    
    // LA32 Instruction Instance (declaration)
    class LA32Instruction;


    // LA32 VM Instance
    class LA32Instance;


    // LA32 Instruction Execution Status
    typedef enum class __tag_LA32ExecStatus {
        // Naturally increase the PC. Execute instruction stream in sequence normally.
        EXEC_SEQUENTIAL = 0,

        // PC Branch. PC is changed in instruction execution procedure.
        EXEC_BRANCH,

        // Memory Access Fault.
        // Memory address access fault in execution.
        // The 'error' field in MIPS32ExecOutcome is default to be ECANCEL.
        EXEC_MEMORY_ACCESS_FAULT,

        // Memory Address Misaligned.
        // Memory address misaligned fault in execution.
        // The 'error' field in MIPS32ExecOutcome is default to be ECANCEL.
        EXEC_MEMORY_ADDRESS_MISALIGNED,

        // Memory Device Operation Error.
        // Memory device error or custom EEI-defined memory operation fault.
        // The 'error' field in MIPS32ExecOutcome should give further information.
        EXEC_MEMORY_DEVICE_ERROR,

        // Not Decoded. (Not implemented in codepoint & decoders).
        // Instruction codepoint doesn't exist or not initialized. 
        // This usually indicates that an instruction was properly fetched but it was illegal, or 
        // a instruction was executed before it was properly decoded.
        // This status SHOULDN'T be produced in any execution procedure.
        EXEC_NOT_DECODED,

        // Not Implemented. *EEI-defined*
        // Instruction codepoint exists, but the execution procedure not implemented.
        // This status SHOULDN'T be produced in any execution procedure.
        EXEC_NOT_IMPLEMENTED,

        // Fetch Access Fault. *EEI-defined*
        // MOP_ACCESS_FAULT when fetching instruction by PC from Memory Interface.
        // This status SHOULDN'T be produced in any execution procedure.
        // The way of handling this status (Raising an exception, or .etc) is EEI-defined.
        // The 'error' field in MIPS32ExecOutcome is default to be ECANCEL.
        FETCH_ACCESS_FAULT,

        // Fetch Address Misaligned. *EEI-defined*
        // MOP_ADDRESS_MISALIGNED when fetching instruction by PC from Memory Interface.
        // This status SHOULDN'T be produced in any execution procedure.
        // The way of handling this status (Raising an exception, or .etc) is EEI-defined.
        // The 'error' field in MIPS32ExecOutcome is default to be ECANCEL.
        FETCH_ADDRESS_MISALIGNED,

        // Fetch Device Operation Error. *EEI-defined*
        // Memory device error or custom EEI-defined memory operation fault.
        // This status SHOULDN'T be produced in any execution procedure.
        // The way of handling this status (Raising an exception, or .etc) is EEI-defined.
        // The 'error' field in MIPS32ExecOutcome should give further information.
        FETCH_DEVICE_ERROR,


        // Decode Procedure Cancelled by Emulator.
        DECODE_EMULATION_CANCELLED,

        // Decode Procedure Error occurred in Emulator.
        DECODE_EMULATION_ERROR,

        // Execution Procedure Cancelled by Emulator.
        EXEC_EMULATION_CANCELLED,

        // Execution Procedure Error occurred in Emulator.
        EXEC_EMULATION_ERROR,

        // Fetch Procedure Cancelled by Emulator.
        FETCH_EMULATION_CANCELLED,

        // Fetch Procedure Error occurred in Emulator.
        FETCH_EMULATION_ERROR,


        // Cancelled by Emulator.
        EMULATION_CANCELLED
        
    } LA32ExecStatus;

    // LA32 Instruction Execution Outcome
    struct LA32ExecOutcome {
        LA32ExecStatus  status;
        errno_t         error = 0;
    };

}


namespace BullsEye {
    // to export Jasse namespace to the BullsEye global namespace
    using namespace Jasse;
}


// Integral extension
#define SEXT32_H(expr)      ((uint32_t) ((int16_t)  (expr)))
#define SEXT32_B(expr)      ((uint32_t) ((int8_t)   (expr)))
#define SEXT32_W(expr)      ((uint32_t) (           (expr)))

#define SEXT32(expr, len)   ((uint32_t) ((((int32_t) (expr)) << (32 - len)) >> (32 - len)))

#define SEXT32_IMM8(expr)   SEXT32_B(expr)
#define SEXT32_IMM12(expr)  SEXT32(expr, 12)
#define SEXT32_IMM14(expr)  SEXT32(expr, 14)
#define SEXT32_IMM16(expr)  SEXT32_H(expr)
#define SEXT32_IMM21(expr)  SEXT32(expr, 21)
#define SEXT32_IMM26(expr)  SEXT32(expr, 26)
#define SEXT32_IMM20(expr)  SEXT32(expr, 20)
#define SEXT32_IMM5(expr)   SEXT32(expr, 5)

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
#define GET_LA32_OPERAND(insn, mask, offset) \
    ((insn & mask) >> offset)

#define GET_LA32_STD_OPERAND(insn, name) \
    ((insn & name##_MASK) >> name##_OFFSET)

#define SET_LA32_OPERAND(dst, mask, offset, value) \
    (dst = ((dst & ~mask) | ((value << offset) & mask)))

#define SET_LA32_STD_OPERAND(dst, name, value) \
    (dst = ((dst & ~name##_MASK) | ((value << name##_OFFSET) & name##_MASK)))


#define GET_LA32_IMM8(insn) \
    GET_LA32_STD_OPERAND(insn, LA32_IMM8)

#define GET_LA32_IMM12(insn) \
    GET_LA32_STD_OPERAND(insn, LA32_IMM12)

#define GET_LA32_IMM14(insn) \
    GET_LA32_STD_OPERAND(insn, LA32_IMM14)

#define GET_LA32_IMM16(insn) \
    GET_LA32_STD_OPERAND(insn, LA32_IMM16)

#define GET_LA32_IMM21(insn) \
    ((GET_LA32_STD_OPERAND(insn, LA32_IMM21_U5) << 16) | GET_LA32_STD_OPERAND(insn, LA32_IMM21_L16))

#define GET_LA32_IMM26(insn) \
    ((GET_LA32_STD_OPERAND(insn, LA32_IMM26_U10) << 16) | GET_LA32_STD_OPERAND(insn, LA32_IMM26_L16))

#define GET_LA32_X_IMM20(insn) \
    GET_LA32_STD_OPERAND(insn, LA32_X_IMM20)

#define GET_LA32_X_IMM5(insn) \
    GET_LA32_STD_OPERAND(insn, LA32_X_IMM5)    


#define SET_LA32_IMM8(dst, value) \
    SET_LA32_STD_OPERAND(dst, LA32_IMM8, value)

#define SET_LA32_IMM12(dst, value) \
    SET_LA32_STD_OPERAND(dst, LA32_IMM12, value)

#define SET_LA32_IMM14(dst, value) \
    SET_LA32_STD_OPERAND(dst, LA32_IMM14, value)

#define SET_LA32_IMM16(dst, value) \
    SET_LA32_STD_OPERAND(dst, LA32_IMM16, value)

#define SET_LA32_IMM21(dst, value) \
    (SET_LA32_STD_OPERAND(dst, LA32_IMM21_U5, (value >> 16)), \
     SET_LA32_STD_OPERAND(dst, LA32_IMM21_L16, (value & 0xFFFF)))

#define SET_LA32_IMM26(dst, value) \
    (SET_LA32_STD_OPERAND(dst, LA32_IMM26_U10, (value >> 16)), \
     SET_LA32_STD_OPERAND(dst, LA32_IMM26_L16, (value & 0xFFFF)))

#define SET_LA32_X_IMM20(dst, value) \
    SET_LA32_STD_OPERAND(dst, LA32_X_IMM20, value)

#define SET_LA32_X_IMM5(dst, value) \
    SET_LA32_STD_OPERAND(dst, LA32_X_IMM5, value)


// Basis
#define LA32_ARCH_REG_COUNT                     32

#define LA32_RD_MASK                            0x0000001FU
#define LA32_RD_OFFSET                          0

#define LA32_RJ_MASK                            0x000003E0U
#define LA32_RJ_OFFSET                          5

#define LA32_RK_MASK                            0x00007C00U
#define LA32_RK_OFFSET                          10

#define LA32_RA_MASK                            0x000F8000U
#define LA32_RA_OFFSET                          15

#define LA32_OPCODE_U6_MASK                     0xFC000000U
#define LA32_OPCODE_U6_OFFSET                   26

#define LA32_OPCODE_L2_MASK                     0x03000000U
#define LA32_OPCODE_L2_OFFSET                   24

#define LA32_OPCODE_L1_MASK                     0x02000000U
#define LA32_OPCODE_L1_OFFSET                   25

#define LA32_OPCODE_L4_MASK                     0x03C00000U
#define LA32_OPCODE_L4_OFFSET                   22

#define LA32_OPCODE_L8_MASK                     0x03FC0000U
#define LA32_OPCODE_L8_OFFSET                   18

#define LA32_OPCODE_L6_MASK                     0x03F00000U
#define LA32_OPCODE_L6_OFFSET                   20

#define LA32_OPCODE_L11_MASK                    0x03FF8000U
#define LA32_OPCODE_L11_OFFSET                  15

#define LA32_OPCODE_L16_MASK                    0x03FFFC00U
#define LA32_OPCODE_L16_OFFSET                  10

#define LA32_IMM8_MASK                          0x0003FC00U
#define LA32_IMM8_OFFSET                        10

#define LA32_IMM12_MASK                         0x003FFC00U
#define LA32_IMM12_OFFSET                       10

#define LA32_IMM14_MASK                         0x00FFFC00U
#define LA32_IMM14_OFFSET                       10

#define LA32_IMM16_MASK                         0x03FFFC00U
#define LA32_IMM16_OFFSET                       10

#define LA32_IMM21_L16_MASK                     0x03FFFC00U
#define LA32_IMM21_L16_OFFSET                   10

#define LA32_IMM21_U5_MASK                      0x0000001FU
#define LA32_IMM21_U5_OFFSET                    0

#define LA32_IMM26_L16_MASK                     0x03FFFC00U
#define LA32_IMM26_L16_OFFSET                   10

#define LA32_IMM26_U10_MASK                     0x000003FFU
#define LA32_IMM26_U10_OFFSET                   0

#define LA32_X_IMM20_MASK                       0x01FFFFE0U
#define LA32_X_IMM20_OFFSET                     5

#define LA32_X_IMM5_MASK                        0x00007C00U
#define LA32_X_IMM5_OFFSET                      10


// General registers
#define LA32_GR_R0                              0
#define LA32_GR_R1                              1
#define LA32_GR_R2                              2
#define LA32_GR_R3                              3
#define LA32_GR_R4                              4
#define LA32_GR_R5                              5
#define LA32_GR_R6                              6
#define LA32_GR_R7                              7
#define LA32_GR_R8                              8
#define LA32_GR_R9                              9
#define LA32_GR_R10                             10
#define LA32_GR_R11                             11
#define LA32_GR_R12                             12
#define LA32_GR_R13                             13
#define LA32_GR_R14                             14
#define LA32_GR_R15                             15
#define LA32_GR_R16                             16
#define LA32_GR_R17                             17
#define LA32_GR_R18                             18
#define LA32_GR_R19                             19
#define LA32_GR_R20                             20
#define LA32_GR_R21                             21
#define LA32_GR_R22                             22
#define LA32_GR_R23                             23
#define LA32_GR_R24                             24
#define LA32_GR_R25                             25
#define LA32_GR_R26                             26
#define LA32_GR_R27                             27
#define LA32_GR_R28                             28
#define LA32_GR_R29                             29
#define LA32_GR_R30                             30
#define LA32_GR_R31                             31


// General registers (ABI-defined)
// $zero        : Always zero.
#define LA32_GR_ZERO                            0

// $ra          : Return address. 
#define LA32_GR_RA                              1

// $tp          : Thread pointer.
#define LA32_GR_TP                              2

// $sp          : Stack pointer.
#define LA32_GR_SP                              3

// $a0 ... $a1  : Function parameters or return values.
#define LA32_GR_A0                              4
#define LA32_GR_A1                              5

// $a2 ... $a7  : Function parameters.
#define LA32_GR_A2                              6
#define LA32_GR_A3                              7
#define LA32_GR_A4                              8
#define LA32_GR_A5                              9
#define LA32_GR_A6                              10
#define LA32_GR_A7                              11

// $t0 ... $t8  : Temporary.
#define LA32_GR_T0                              12
#define LA32_GR_T1                              13
#define LA32_GR_T2                              14
#define LA32_GR_T3                              15
#define LA32_GR_T4                              16
#define LA32_GR_T5                              17
#define LA32_GR_T6                              18
#define LA32_GR_T7                              19
#define LA32_GR_T8                              20

// $fp          : Frame pointer.
#define LA32_GR_FP                              22

// $s0 ... $s8  : Static register.
#define LA32_GR_S0                              23
#define LA32_GR_S1                              24
#define LA32_GR_S2                              25
#define LA32_GR_S3                              26
#define LA32_GR_S4                              27
#define LA32_GR_S5                              28
#define LA32_GR_S6                              29
#define LA32_GR_S7                              30
#define LA32_GR_S8                              31

// $s9          : Static register.
#define LA32_GR_S9                              22


//
#define decdef              const LA32Decoder* const
#define decdecl             extern const LA32Decoder* const

#define codedef             const LA32Codepoint
#define codedecl            extern const LA32Codepoint

#define codesetdef          const LA32CodepointCollection
#define codesetdecl         extern const LA32CodepointCollection


// Instruction codepoint opcode definitions
#define LA32_OPCODE_U6_ADD_W                    0b000000
#define LA32_OPCODE_L11_ADD_W                   0b00000100000

#define LA32_OPCODE_U6_SUB_W                    0b000000
#define LA32_OPCODE_L11_SUB_W                   0b00000100010

#define LA32_OPCODE_U6_ADDI_W                   0b000000
#define LA32_OPCODE_L4_ADDI_W                   0b1010

#define LA32_OPCODE_U6_LU12I_W                  0b000101
#define LA32_OPCODE_L1_LU12I_W                  0b0

#define LA32_OPCODE_U6_SLT                      0b000000 
#define LA32_OPCODE_L11_SLT                     0b00000100100

#define LA32_OPCODE_U6_SLTU                     0b000000
#define LA32_OPCODE_L11_SLTU                    0b00000100101

#define LA32_OPCODE_U6_SLTI                     0b000000
#define LA32_OPCODE_L4_SLTI                     0b1000

#define LA32_OPCODE_U6_SLTUI                    0b000000
#define LA32_OPCODE_L4_SLTUI                    0b1001

#define LA32_OPCODE_U6_PCADDU12I                0b000111 
#define LA32_OPCODE_L1_PCADDU12I                0b0

#define LA32_OPCODE_U6_NOR                      0b000000
#define LA32_OPCODE_L11_NOR                     0b00000101000

#define LA32_OPCODE_U6_AND                      0b000000 
#define LA32_OPCODE_L11_AND                     0b00000101001

#define LA32_OPCODE_U6_OR                       0b000000 
#define LA32_OPCODE_L11_OR                      0b00000101010

#define LA32_OPCODE_U6_XOR                      0b000000 
#define LA32_OPCODE_L11_XOR                     0b00000101011

#define LA32_OPCODE_U6_ANDI                     0b000000 
#define LA32_OPCODE_L4_ANDI                     0b1101

#define LA32_OPCODE_U6_ORI                      0b000000 
#define LA32_OPCODE_L4_ORI                      0b1110

#define LA32_OPCODE_U6_XORI                     0b000000 
#define LA32_OPCODE_L4_XORI                     0b1111

#define LA32_OPCODE_U6_MUL_W                    0b000000 
#define LA32_OPCODE_L11_MUL_W                   0b00000111000

#define LA32_OPCODE_U6_MULH_W                   0b000000 
#define LA32_OPCODE_L11_MULH_W                  0b00000111001

#define LA32_OPCODE_U6_MULH_WU                  0b000000 
#define LA32_OPCODE_L11_MULH_WU                 0b00000111010

#define LA32_OPCODE_U6_DIV_W                    0b000000 
#define LA32_OPCODE_L11_DIV_W                   0b00001000000

#define LA32_OPCODE_U6_MOD_W                    0b000000 
#define LA32_OPCODE_L11_MOD_W                   0b00001000001

#define LA32_OPCODE_U6_DIV_WU                   0b000000 
#define LA32_OPCODE_L11_DIV_WU                  0b00001000010

#define LA32_OPCODE_U6_MOD_WU                   0b000000 
#define LA32_OPCODE_L11_MOD_WU                  0b00001000011

#define LA32_OPCODE_U6_SLL_W                    0b000000 
#define LA32_OPCODE_L11_SLL_W                   0b00000101110

#define LA32_OPCODE_U6_SRL_W                    0b000000 
#define LA32_OPCODE_L11_SRL_W                   0b00000101111

#define LA32_OPCODE_U6_SRA_W                    0b000000 
#define LA32_OPCODE_L11_SRA_W                   0b00000110000

#define LA32_OPCODE_U6_SLLI_W                   0b000000 
#define LA32_OPCODE_L11_SLLI_W                  0b00010000001

#define LA32_OPCODE_U6_SRLI_W                   0b000000 
#define LA32_OPCODE_L11_SRLI_W                  0b00010001001

#define LA32_OPCODE_U6_SRAI_W                   0b000000 
#define LA32_OPCODE_L11_SRAI_W                  0b00010010001

#define LA32_OPCODE_U6_BEQ                      0b010110

#define LA32_OPCODE_U6_BNE                      0b010111

#define LA32_OPCODE_U6_BLT                      0b011000

#define LA32_OPCODE_U6_BGE                      0b011001

#define LA32_OPCODE_U6_BLTU                     0b011010

#define LA32_OPCODE_U6_BGEU                     0b011011

#define LA32_OPCODE_U6_B                        0b010100

#define LA32_OPCODE_U6_BL                       0b010101

#define LA32_OPCODE_U6_JIRL                     0b010011

#define LA32_OPCODE_U6_LD_B                     0b001010 
#define LA32_OPCODE_L4_LD_B                     0b0000

#define LA32_OPCODE_U6_LD_H                     0b001010 
#define LA32_OPCODE_L4_LD_H                     0b0001

#define LA32_OPCODE_U6_LD_W                     0b001010 
#define LA32_OPCODE_L4_LD_W                     0b0010

#define LA32_OPCODE_U6_LD_BU                    0b001010 
#define LA32_OPCODE_L4_LD_BU                    0b1000

#define LA32_OPCODE_U6_LD_HU                    0b001010
#define LA32_OPCODE_L4_LD_HU                    0b1001

#define LA32_OPCODE_U6_ST_B                     0b001010
#define LA32_OPCODE_L4_ST_B                     0b0100

#define LA32_OPCODE_U6_ST_H                     0b001010 
#define LA32_OPCODE_L4_ST_H                     0b0101

#define LA32_OPCODE_U6_ST_W                     0b001010
#define LA32_OPCODE_L4_ST_W                     0b0110
