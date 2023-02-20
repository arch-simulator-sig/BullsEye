#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// MIPS32-NSCSCC, bahaviour functions
//

#include "mips32_nscscc_def_execute.hpp"


#define RS                          inst.Arch().GPRs()[insn.GetRS()]
#define RT                          inst.Arch().GPRs()[insn.GetRT()]
#define RD                          inst.Arch().GPRs()[insn.GetRD()]
#define R31                         inst.Arch().GPRs()[31]
#define SA                          insn.GetShamt()
#define PC                          inst.Arch().PC()
#define IMM16_SEXT                  SEXT32_IMM16(insn.GetImmediate())
#define IMM16_ZEXT                  insn.GetImmediate()
#define IMM26_SEXT                  SEXT32_IMM26(insn.GetJumpIndex())
#define IMM26_ZEXT                  insn.GetJumpIndex()


#define sequential(expr)            { expr; return { EXEC_SEQUENTIAL }; }

#define branch_if(pred)             { inst.SetBranchTarget(pred, PC + 4 + (IMM16_SEXT << 2)); return { EXEC_DELAYSLOT }; }

#define jump(dst)                   { inst.SetBranchTarget(true, dst); return { EXEC_DELAYSLOT }; }

#define jumplink(dst, lnk)          { inst.SetBranchTarget(true, dst); lnk = PC + 8; return { EXEC_DELAYSLOT }; }

#define load(dst, width)            { \
    memdata_t memdata; \
    MIPS32MOPOutcome mopoutcome = inst.MI()->ReadData( \
        RS + IMM16_SEXT, MOPW_##width, &memdata); \
    switch (mopoutcome.status) { \
        case MOP_SUCCESS:               dst = SEXT32_##width(memdata);  return { EXEC_SEQUENTIAL }; \
        case MOP_ACCESS_FAULT:          return { EXEC_MEMORY_ACCESS_FAULT, mopoutcome.error }; \
        case MOP_ADDRESS_MISALIGNED:    return { EXEC_MEMORY_ADDRESS_MISALIGNED, mopoutcome.error }; \
        case MOP_DEVICE_ERROR:          return { EXEC_MEMORY_DEVICE_ERROR, mopoutcome.error }; \
        [[unlikely]] default:           SHOULD_NOT_REACH_HERE; \
    } \
} 

#define store(src, width)           { \
    memdata_t memdata; \
    memdata.data32 = src; \
    MIPS32MOPOutcome mopoutcome = inst.MI()->WriteData( \
        RS + IMM16_SEXT, MOPW_##width, memdata); \
    switch (mopoutcome.status) { \
        case MOP_SUCCESS:               return { EXEC_SEQUENTIAL }; \
        case MOP_ACCESS_FAULT:          return { EXEC_MEMORY_ACCESS_FAULT, mopoutcome.error }; \
        case MOP_ADDRESS_MISALIGNED:    return { EXEC_MEMORY_ADDRESS_MISALIGNED, mopoutcome.error }; \
        case MOP_DEVICE_ERROR:          return { EXEC_MEMORY_DEVICE_ERROR, mopoutcome.error }; \
        [[unlikely]] default:           SHOULD_NOT_REACH_HERE; \
    } \
}


#define implexec(name, expr) \
    MIPS32ExecOutcome MIPS32_EXECUTOR(name)(MIPS32_EXECUTOR_PARAMS) expr


namespace Jasse {

    // ADD rd, rs, rt
    implexec(ADD, 
        noexcept sequential(RD = RS + RT));

    // ADDI rt, rs, imm
    implexec(ADDI,
        noexcept sequential(RT = RS + IMM16_SEXT));

    // ADDU rd, rs, rt
    implexec(ADDU,
        noexcept sequential(RD = RS + RT));

    // ADDIU rt, rs, imm
    implexec(ADDIU,
        noexcept sequential(RT = RS + IMM16_SEXT));

    // SUB rd, rs, rt
    implexec(SUB, 
        noexcept sequential(RD = RS - RT));

    // SUBU rd, rs, rt
    implexec(SUBU,
        noexcept sequential(RD = RS - RT));

    // SLT rd, rs, rt
    implexec(SLT,
        noexcept sequential(RD = (signed) RS < (signed) RT));

    // SLTI rt, rs, imm
    implexec(SLTI,
        noexcept sequential(RT = (signed) RS < (signed) IMM16_SEXT));

    // SLTU rd, rs, rt
    implexec(SLTU,
        noexcept sequential(RD = RS < RT));

    // SLTIU rt, rs, imm
    implexec(SLTIU,
        noexcept sequential(RD = RS < IMM16_ZEXT));

    // MUL rd, rs, rt
    implexec(MUL,
        noexcept sequential(RD = RS * RT));


    // AND rd, rs, rt
    implexec(AND,
        noexcept sequential(RD = RS & RT));

    // ANDI rt, rs, imm
    implexec(ANDI,
        noexcept sequential(RT = RS & IMM16_ZEXT));

    // LUI rt, imm
    implexec(LUI,
        noexcept sequential(RT = IMM16_ZEXT << 16));

    // OR rd, rs, rt
    implexec(OR,
        noexcept sequential(RD = RS | RT));

    // ORI rt, rs, imm
    implexec(ORI,
        noexcept sequential(RT = RS | IMM16_ZEXT));

    // XOR rd, rs, rt
    implexec(XOR,
        noexcept sequential(RD = RS ^ RT));

    // XORI rt, rs, imm
    implexec(XORI,
        noexcept sequential(RT = RS ^ IMM16_ZEXT));


    // SLL rd, rt, sa
    implexec(SLL,
        noexcept sequential(RD = RT << SA));

    // SLLV rd, rt, rs
    implexec(SLLV,
        noexcept sequential(RD = RT << RS));

    // SRA rd, rt, sa
    implexec(SRA,
        noexcept sequential(RD = (signed) RT >> SA));
    
    // SRAV rd, rt, rs
    implexec(SRAV,
        noexcept sequential(RD = (signed) RT >> RS));

    // SRL rd, rt, sa
    implexec(SRL,
        noexcept sequential(RD = RT >> SA));

    // SRLV rd, rt, rs
    implexec(SRLV,
        noexcept sequential(RD = RT >> RS));


    // BEQ rs, rt, offset
    implexec(BEQ,
        noexcept branch_if(RS == RT));

    // BNE rs, rt, offset
    implexec(BNE,
        noexcept branch_if(RS != RT));

    // BGEZ rs, offset
    implexec(BGEZ,
        noexcept branch_if(RS >= 0));

    // BGTZ rs, offset
    implexec(BGTZ,
        noexcept branch_if(RS > 0));

    // BLEZ rs, offset
    implexec(BLEZ,
        noexcept branch_if(RS <= 0));

    // BLTZ rs, offset
    implexec(BLTZ,
        noexcept branch_if(RS < 0));
    
    // J target
    implexec(J,
        noexcept jump((IMM26_ZEXT << 2) | (PC & 0xF0000000)));

    // JAL target
    implexec(JAL,
        noexcept jumplink((IMM26_ZEXT << 2) | (PC & 0xF0000000), R31));

    // JR rs
    implexec(JR,
        noexcept jump(RS));

    // JALR rd, rs
    implexec(JALR,
        noexcept jumplink(RS, RD));


    // LB rt, offset(base)
    implexec(LB,
        noexcept load(RT, BYTE));

    // LW rt, offset(base)
    implexec(LW,
        noexcept load(RT, WORD));

    // SB rt, offset(base)
    implexec(SB,
        noexcept store(RT, BYTE));

    // SW rt, offset(base)
    implexec(SW,
        noexcept store(RT, WORD));
}


#undef RS
#undef RT
#undef RD
#undef R31
#undef SA
#undef PC
#undef IMM16_SEXT
#undef IMM16_ZEXT
#undef IMM26_SEXT
#undef IMM26_ZEXT

#undef sequential
#undef branch_if
#undef jump
#undef jumplink
#undef load
#undef store

#undef implexec
