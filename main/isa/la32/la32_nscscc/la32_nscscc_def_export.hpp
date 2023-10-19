#pragma once
//
// LA32R (NSCSCC) ISA Emulator (Jasse)
//
// LA32R-NSCSCC, exporting declarations
//

#ifndef __HEADER_JASSE_LA32__EXT_NSCSCC_EXPORT_DEF
#define __HEADER_JASSE_LA32__EXT_NSCSCC_EXPORT_DEF


#include "la32.hpp"


// LA32-NSCSCC codepoint exporting declarations
namespace Jasse::Decoder {

    decdecl     LA32R_NSCSCC;
}

namespace Jasse::Codepoint::LA32R_NSCSCC {

    codedecl    ADD_W;
    codedecl    SUB_W;
    codedecl    ADDI_W;
    codedecl    LU12I_W;
    codedecl    SLT;
    codedecl    SLTU;
    codedecl    SLTI;
    codedecl    SLTUI;
    codedecl    PCADDU12I;
    codedecl    AND;
    codedecl    OR;
    codedecl    NOR;
    codedecl    XOR;
    codedecl    ANDI;
    codedecl    ORI;
    codedecl    XORI;

    codedecl    MUL_W;
    codedecl    MULH_W;
    codedecl    MULH_WU;

    codedecl    DIV_W;
    codedecl    DIV_WU;
    codedecl    MOD_W;
    codedecl    MOD_WU;

    codedecl    SLL_W;
    codedecl    SRL_W;
    codedecl    SRA_W;
    codedecl    SLLI_W;
    codedecl    SRLI_W;
    codedecl    SRAI_W;

    codedecl    BEQ;
    codedecl    BNE;
    codedecl    BLT;
    codedecl    BLTU;
    codedecl    BGE;
    codedecl    BGEU;
    codedecl    B;
    codedecl    BL;
    codedecl    JIRL;

    codedecl    LD_B;
    codedecl    LD_H;
    codedecl    LD_W;
    codedecl    LD_BU;
    codedecl    LD_HU;
    codedecl    ST_B;
    codedecl    ST_H;
    codedecl    ST_W;
}

namespace Jasse::CodepointSet {

    codesetdecl LA32R_NSCSCC;
}


#endif
