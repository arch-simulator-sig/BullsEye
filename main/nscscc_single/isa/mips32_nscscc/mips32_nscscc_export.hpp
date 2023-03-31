#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// MIPS32-NSCSCC, exporting header
//

#include "mips32_nscscc_def_encode.hpp"

#include "mips32_nscscc_impl_decode.hpp"
#include "mips32_nscscc_impl_execute.hpp"
#include "mips32_nscscc_impl_event.hpp"


namespace Jasse {

    decdef  MIPS32          { new MIPS32NSCSCCDecoder };

    codedef MIPS32_ADD      {"add"   , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, ADD)    , &MIPS32_EXECUTOR(ADD)     , &TextualizeMIPS32TypeR };
    codedef MIPS32_ADDI     {"addi"  , MIPS32_TYPE_I, &MIPS32_DECODER_STUB(Opcode, ADDI)            , &MIPS32_EXECUTOR(ADDI)    , &TextualizeMIPS32TypeI };
    codedef MIPS32_ADDU     {"addu"  , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, ADDU)   , &MIPS32_EXECUTOR(ADDU)    , &TextualizeMIPS32TypeR };
    codedef MIPS32_ADDIU    {"addiu" , MIPS32_TYPE_I, &MIPS32_DECODER_STUB(Opcode, ADDIU)           , &MIPS32_EXECUTOR(ADDIU)   , &TextualizeMIPS32TypeI };
    codedef MIPS32_SUB      {"sub"   , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, SUB)    , &MIPS32_EXECUTOR(SUB)     , &TextualizeMIPS32TypeR };
    codedef MIPS32_SUBU     {"subu"  , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, SUBU)   , &MIPS32_EXECUTOR(SUBU)    , &TextualizeMIPS32TypeR };
    codedef MIPS32_SLT      {"slt"   , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, SLT)    , &MIPS32_EXECUTOR(SLT)     , &TextualizeMIPS32TypeR };
    codedef MIPS32_SLTI     {"slti"  , MIPS32_TYPE_I, &MIPS32_DECODER_STUB(Opcode, SLTI)            , &MIPS32_EXECUTOR(SLTI)    , &TextualizeMIPS32TypeI };
    codedef MIPS32_SLTU     {"sltu"  , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, SLTU)   , &MIPS32_EXECUTOR(SLTU)    , &TextualizeMIPS32TypeR };
    codedef MIPS32_SLTIU    {"sltiu" , MIPS32_TYPE_I, &MIPS32_DECODER_STUB(Opcode, SLTIU)           , &MIPS32_EXECUTOR(SLTIU)   , &TextualizeMIPS32TypeI };
    codedef MIPS32_MUL      {"mul"   , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL2, MUL)   , &MIPS32_EXECUTOR(MUL)     , &TextualizeMIPS32TypeR };

    codedef MIPS32_AND      {"and"   , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, AND)    , &MIPS32_EXECUTOR(AND)     , &TextualizeMIPS32TypeR };
    codedef MIPS32_ANDI     {"andi"  , MIPS32_TYPE_I, &MIPS32_DECODER_STUB(Opcode, ANDI)            , &MIPS32_EXECUTOR(ANDI)    , &TextualizeMIPS32TypeI };
    codedef MIPS32_LUI      {"lui"   , MIPS32_TYPE_I, &MIPS32_DECODER_STUB(Opcode, LUI)             , &MIPS32_EXECUTOR(LUI)     , &TextualizeMIPS32RtExclusiveTypeI };
    codedef MIPS32_OR       {"or"    , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, OR)     , &MIPS32_EXECUTOR(OR)      , &TextualizeMIPS32TypeR };
    codedef MIPS32_ORI      {"ori"   , MIPS32_TYPE_I, &MIPS32_DECODER_STUB(Opcode, ORI)             , &MIPS32_EXECUTOR(ORI)     , &TextualizeMIPS32TypeI };
    codedef MIPS32_XOR      {"xor"   , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, XOR)    , &MIPS32_EXECUTOR(XOR)     , &TextualizeMIPS32TypeR };
    codedef MIPS32_XORI     {"xori"  , MIPS32_TYPE_I, &MIPS32_DECODER_STUB(Opcode, XORI)            , &MIPS32_EXECUTOR(XORI)    , &TextualizeMIPS32TypeI };

    codedef MIPS32_SLL      {"sll"   , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, SLL)    , &MIPS32_EXECUTOR(SLL)     , &TextualizeMIPS32ShiftConstant };
    codedef MIPS32_SLLV     {"sllv"  , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, SLLV)   , &MIPS32_EXECUTOR(SLLV)    , &TextualizeMIPS32TypeR };
    codedef MIPS32_SRA      {"sra"   , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, SRA)    , &MIPS32_EXECUTOR(SRA)     , &TextualizeMIPS32ShiftConstant };
    codedef MIPS32_SRAV     {"srav"  , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, SRAV)   , &MIPS32_EXECUTOR(SRAV)    , &TextualizeMIPS32TypeR };
    codedef MIPS32_SRL      {"srl"   , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, SRL)    , &MIPS32_EXECUTOR(SRL)     , &TextualizeMIPS32ShiftConstant };
    codedef MIPS32_SRLV     {"srlv"  , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, SRLV)   , &MIPS32_EXECUTOR(SRLV)    , &TextualizeMIPS32TypeR };

    codedef MIPS32_BEQ      {"beq"   , MIPS32_TYPE_I, &MIPS32_DECODER_STUB(Opcode, BEQ)             , &MIPS32_EXECUTOR(BEQ)     , &TextualizeMIPS32TypeI };
    codedef MIPS32_BNE      {"bne"   , MIPS32_TYPE_I, &MIPS32_DECODER_STUB(Opcode, BNE)             , &MIPS32_EXECUTOR(BNE)     , &TextualizeMIPS32TypeI };
    codedef MIPS32_BGEZ     {"bgez"  , MIPS32_TYPE_I, &MIPS32_DECODER_STUB2(Rt, REGIMM, BGEZ)       , &MIPS32_EXECUTOR(BGEZ)    , &TextualizeMIPS32RsExclusiveTypeI };
    codedef MIPS32_BGTZ     {"bgtz"  , MIPS32_TYPE_I, &MIPS32_DECODER_STUB(Opcode, BGTZ)            , &MIPS32_EXECUTOR(BGTZ)    , &TextualizeMIPS32RsExclusiveTypeI };
    codedef MIPS32_BLEZ     {"blez"  , MIPS32_TYPE_I, &MIPS32_DECODER_STUB(Opcode, BLEZ)            , &MIPS32_EXECUTOR(BLEZ)    , &TextualizeMIPS32RsExclusiveTypeI };
    codedef MIPS32_BLTZ     {"bltz"  , MIPS32_TYPE_I, &MIPS32_DECODER_STUB2(Rt, REGIMM, BLTZ)       , &MIPS32_EXECUTOR(BLTZ)    , &TextualizeMIPS32RsExclusiveTypeI };
    codedef MIPS32_J        {"j"     , MIPS32_TYPE_J, &MIPS32_DECODER_STUB(Opcode, J)               , &MIPS32_EXECUTOR(J)       , &TextualizeMIPS32TypeJ };
    codedef MIPS32_JAL      {"jal"   , MIPS32_TYPE_J, &MIPS32_DECODER_STUB(Opcode, JAL)             , &MIPS32_EXECUTOR(JAL)     , &TextualizeMIPS32TypeJ };
    codedef MIPS32_JR       {"jr"    , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, JR)     , &MIPS32_EXECUTOR(JR)      , &TextualizeMIPS32RsExclusiveTypeR };
    codedef MIPS32_JALR     {"jalr"  , MIPS32_TYPE_R, &MIPS32_DECODER_STUB2(Funct, SPECIAL, JALR)   , &MIPS32_EXECUTOR(JALR)    , &TextualizeMIPS32RtExcludedTypeR };

    codedef MIPS32_LB       {"lb"    , MIPS32_TYPE_I, &MIPS32_DECODER_STUB(Opcode, LB)              , &MIPS32_EXECUTOR(LB)      , &TextualizeMIPS32LoadStore };
    codedef MIPS32_LW       {"lw"    , MIPS32_TYPE_I, &MIPS32_DECODER_STUB(Opcode, LW)              , &MIPS32_EXECUTOR(LW)      , &TextualizeMIPS32LoadStore };
    codedef MIPS32_SB       {"sb"    , MIPS32_TYPE_I, &MIPS32_DECODER_STUB(Opcode, SB)              , &MIPS32_EXECUTOR(SB)      , &TextualizeMIPS32LoadStore };
    codedef MIPS32_SW       {"sw"    , MIPS32_TYPE_I, &MIPS32_DECODER_STUB(Opcode, SW)              , &MIPS32_EXECUTOR(SW)      , &TextualizeMIPS32LoadStore };

    
    codesetdef  ALL_OF_MIPS32 {
        &MIPS32_ADD,    &MIPS32_ADDI,   &MIPS32_ADDU,   &MIPS32_ADDIU,  &MIPS32_SUB,    &MIPS32_SUBU,
        &MIPS32_SLT,    &MIPS32_SLTI,   &MIPS32_SLTU,   &MIPS32_SLTIU,
        &MIPS32_MUL,
        &MIPS32_LUI,
        &MIPS32_AND,    &MIPS32_ANDI,   &MIPS32_OR,     &MIPS32_ORI,    &MIPS32_XOR,    &MIPS32_XORI,
        &MIPS32_SLL,    &MIPS32_SLLV,   &MIPS32_SRA,    &MIPS32_SRAV,   &MIPS32_SRL,    &MIPS32_SRLV,
        &MIPS32_BEQ,    &MIPS32_BNE,    &MIPS32_BGEZ,   &MIPS32_BGTZ,   &MIPS32_BLEZ,   &MIPS32_BLTZ,
        &MIPS32_J,      &MIPS32_JAL,    &MIPS32_JR,     &MIPS32_JALR,
        &MIPS32_LB,     &MIPS32_LW,     &MIPS32_SB,     &MIPS32_SW
    };
}
