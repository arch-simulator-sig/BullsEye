#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// MIPS32-NSCSCC, exporting declarations
//

#include "mips32.hpp"


// MIPS32-NSCSCC codepoint exporting declarations
namespace Jasse {

    decdecl     MIPS32;

    codedecl    MIPS32_ADD   ;
    codedecl    MIPS32_ADDI  ;
    codedecl    MIPS32_ADDU  ;
    codedecl    MIPS32_ADDIU ;
    codedecl    MIPS32_SUB   ;
    codedecl    MIPS32_SUBU  ;
    codedecl    MIPS32_SLT   ;
    codedecl    MIPS32_SLTI  ;
    codedecl    MIPS32_SLTU  ;
    codedecl    MIPS32_SLTIU ;
    codedecl    MIPS32_MUL   ;

    codedecl    MIPS32_AND   ; 
    codedecl    MIPS32_ANDI  ;
    codedecl    MIPS32_LUI   ;
    codedecl    MIPS32_OR    ;
    codedecl    MIPS32_ORI   ;
    codedecl    MIPS32_XOR   ;
    codedecl    MIPS32_XORI  ;

    codedecl    MIPS32_SLL   ;
    codedecl    MIPS32_SLLV  ;
    codedecl    MIPS32_SRA   ;
    codedecl    MIPS32_SRAV  ;
    codedecl    MIPS32_SRL   ;
    codedecl    MIPS32_SRLV  ;

    codedecl    MIPS32_BEQ   ;
    codedecl    MIPS32_BNE   ;
    codedecl    MIPS32_BGEZ  ;
    codedecl    MIPS32_BGTZ  ;
    codedecl    MIPS32_BLEZ  ;
    codedecl    MIPS32_BLTZ  ;
    codedecl    MIPS32_J     ;
    codedecl    MIPS32_JAL   ;
    codedecl    MIPS32_JR    ;
    codedecl    MIPS32_JALR  ;

    codedecl    MIPS32_MFHI  ;
    codedecl    MIPS32_MFLO  ;
    codedecl    MIPS32_MTHI  ;
    codedecl    MIPS32_MTLO  ;

    codedecl    MIPS32_DIV   ;
    codedecl    MIPS32_DIVU  ;
    codedecl    MIPS32_MULT  ;
    codedecl    MIPS32_MULTU ;

    codedecl    MIPS32_LB    ;
    codedecl    MIPS32_LBU   ;
    codedecl    MIPS32_LH    ;
    codedecl    MIPS32_LHU   ;
    codedecl    MIPS32_LW    ;

    codedecl    MIPS32_SB    ;
    codedecl    MIPS32_SH    ;
    codedecl    MIPS32_SW    ;

    codesetdecl ALL_OF_MIPS32;
}
