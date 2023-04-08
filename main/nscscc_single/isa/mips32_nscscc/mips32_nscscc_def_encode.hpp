#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// MIPS32-NSCSCC, encoding definitions
//

#include "mips32_nscscc_def_base.hpp"


//
#define ENCODE_MIPS32_ADD(rd, rs, rt)           ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, rs, rt, rd, 0, MIPS32_FUNCT_SPECIAL_ADD)
#define ENCODE_MIPS32_ADDI(rt, rs, imm)         ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_ADDI, rs, rt, imm)
#define ENCODE_MIPS32_ADDU(rd, rs, rt)          ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, rs, rt, rd, 0, MIPS32_FUNCT_SPECIAL_ADDU)
#define ENCODE_MIPS32_ADDIU(rt, rs, imm)        ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_ADDIU, rs, rt, imm)
#define ENCODE_MIPS32_SUB(rd, rs, rt)           ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, rs, rt, rd, 0, MIPS32_FUNCT_SPECIAL_SUB)
#define ENCODE_MIPS32_SUBU(rd, rs, rt)          ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, rs, rt, rd, 0, MIPS32_FUNCT_SPECIAL_SUBU)
#define ENCODE_MIPS32_SLT(rd, rs, rt)           ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, rs, rt, rd, 0, MIPS32_FUNCT_SPECIAL_SLT)
#define ENCODE_MIPS32_SLTI(rt, rs, imm)         ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_SLTI, rs, rt, imm)
#define ENCODE_MIPS32_SLTU(rd, rs, rt)          ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, rs, rt, rd, 0, MIPS32_FUNCT_SPECIAL_SLTU)
#define ENCODE_MIPS32_SLTIU(rt, rs, imm)        ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_SLTIU, rs, rt, imm)
#define ENCODE_MIPS32_MUL(rd, rs, rt)           ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL2, rs, rt, rd, 0, MIPS32_FUNCT_SPECIAL2_MUL)

#define ENCODE_MIPS32_AND(rd, rs, rt)           ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, rs, rt, rd, 0, MIPS32_FUNCT_SPECIAL_AND)
#define ENCODE_MIPS32_ANDI(rt, rs, imm)         ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_ANDI, rs, rt, imm)
#define ENCODE_MIPS32_LUI(rt, imm)              ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_LUI, 0, rt, imm)
#define ENCODE_MIPS32_OR(rd, rs, rt)            ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, rs, rt, rd, 0, MIPS32_FUNCT_SPECIAL_OR)
#define ENCODE_MIPS32_ORI(rt, rs, imm)          ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_ORI, rs, rt, imm)
#define ENCODE_MIPS32_XOR(rd, rs, rt)           ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, rs, rt, rd, 0, MIPS32_FUNCT_SPECIAL_XOR)
#define ENCODE_MIPS32_XORI(rt, rs, imm)         ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_XORI, rs, rt, imm)

#define ENCODE_MIPS32_SLL(rd, rt, sa)           ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, 0, rt, rd, sa, MIPS32_FUNCT_SPECIAL_SLL)
#define ENCODE_MIPS32_SLLV(rd, rt, rs)          ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, rs, rt, rd, 0, MIPS32_FUNCT_SPECIAL_SLLV)
#define ENCODE_MIPS32_SRA(rd, rt, sa)           ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, 0, rt, rd, sa, MIPS32_FUNCT_SPECIAL_SRA)
#define ENCODE_MIPS32_SRAV(rd, rt, rs)          ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, rs, rt, rd, 0, MIPS32_FUNCT_SPECIAL_SRAV)
#define ENCODE_MIPS32_SRL(rd, rt, sa)           ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, 0, rt, rd, sa, MIPS32_FUNCT_SPECIAL_SRL)
#define ENCODE_MIPS32_SRLV(rd, rt, rs)          ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, rs, rt, rd, 0, MIPS32_FUNCT_SPECIAL_SRLV)

#define ENCODE_MIPS32_BEQ(rs, rt, offset)       ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_BEQ, rs, rt, offset)
#define ENCODE_MIPS32_BNE(rs, rt, offset)       ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_BNE, rs, rt, offset)
#define ENCODE_MIPS32_BGEZ(rs, offset)          ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_REGIMM, rs, MIPS32_RT_REGIMM_BGEZ, offset)
#define ENCODE_MIPS32_BGTZ(rs, offset)          ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_BGTZ, rs, 0, offset)
#define ENCODE_MIPS32_BLEZ(rs, offset)          ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_BLEZ, rs, 0, offset)
#define ENCODE_MIPS32_BLTZ(rs, offset)          ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_REGIMM, rs, MIPS32_RT_REGIMM_BLTZ, offset)
#define ENCODE_MIPS32_J(target)                 ENCODE_MIPS32_TYPE_J(MIPS32_OPCODE_J, target)
#define ENCODE_MIPS32_JAL(target)               ENCODE_MIPS32_TYPE_J(MIPS32_OPCODE_JAL, target)
#define ENCODE_MIPS32_JR(rs)                    ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, rs, 0, 0, 0, MIPS32_FUNCT_SPECIAL_JR)
#define ENCODE_MIPS32_JALR(rd, rs)              ENCODE_MIPS32_TYPE_R(MIPS32_OPCODE_SPECIAL, rs, 0, rd, 0, MIPS32_FUNCT_SPECIAL_JALR)

#define ENCODE_MIPS32_LB(rt, offset, base)      ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_LB,  base, rt, offset)
#define ENCODE_MIPS32_LBU(rt, offset, base)     ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_LBU, base, rt, offset)
#define ENCODE_MIPS32_LH(rt, offset, base)      ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_LH,  base, rt, offset)
#define ENCODE_MIPS32_LHU(rt, offset, base)     ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_LHU, base, rt, offset)
#define ENCODE_MIPS32_LW(rt, offset, base)      ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_LW,  base, rt, offset)

#define ENCODE_MIPS32_SB(rt, offset, base)      ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_SB,  base, rt, offset)
#define ENCODE_MIPS32_SH(rt, offset, base)      ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_SH,  base, rt, offset)
#define ENCODE_MIPS32_SW(rt, offset, base)      ENCODE_MIPS32_TYPE_I(MIPS32_OPCODE_SW,  base, rt, offset)
