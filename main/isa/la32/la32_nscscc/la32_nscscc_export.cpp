#include "la32_nscscc_export.hpp"   // IWYU pragma: keep
//
// LA32R (NSCSCC) ISA Emulator (Jasse)
//
// LA32R-NSCSCC, exporting header
//


namespace Jasse::Decoder {

    decdef  LA32R_NSCSCC     { new LA32R_NSCSCC::Decoder };
}


namespace Jasse::Codepoint::LA32R_NSCSCC {

#define _T(name)            LA32CodepointType::TYPE_##name
#define _TR(name)           &LA32Traits::name

#define _D_U6L0(name)       &Jasse::LA32R_NSCSCC::LA32R_DECODER_STUB_U6L0(name)
#define _D_U6L1(name)       &Jasse::LA32R_NSCSCC::LA32R_DECODER_STUB_U6L1(name)
#define _D_U6L4(name)       &Jasse::LA32R_NSCSCC::LA32R_DECODER_STUB_U6L4(name)
#define _D_U6L11(name)      &Jasse::LA32R_NSCSCC::LA32R_DECODER_STUB_U6L11(name)

#define _E(name)            &Jasse::LA32R_NSCSCC::LA32R_EXECUTOR(name)

#define _TXT(name)          &Jasse::TextualizeLA32Type##name


    //
    codedef ADD_W       { "add.w"       , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( ADD_W     ) , _E(ADD_W    ) , _TXT(3R         ) };
    codedef SUB_W       { "sub.w"       , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( SUB_W     ) , _E(SUB_W    ) , _TXT(3R         ) };

    codedef ADDI_W      { "addi.w"      , _T(2RI12    ) , _TR(NORMAL_2RSI12         ) , _D_U6L4(  ADDI_W    ) , _E(ADDI_W   ) , _TXT(2RI12      ) };

    codedef LU12I_W     { "lu12i.w"     , _T(X_1RI20  ) , _TR(EXTENDED_1RI20        ) , _D_U6L1(  LU12I_W   ) , _E(LU12I_W  ) , _TXT(X1RI20     ) };

    codedef SLT         { "slt"         , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( SLT       ) , _E(SLT      ) , _TXT(3R         ) };
    codedef SLTU        { "sltu"        , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( SLTU      ) , _E(SLTU     ) , _TXT(3R         ) };

    codedef SLTI        { "slti"        , _T(2RI12    ) , _TR(NORMAL_2RSI12         ) , _D_U6L4(  SLTI      ) , _E(SLTI     ) , _TXT(2RI12      ) };
    codedef SLTUI       { "sltui"       , _T(2RI12    ) , _TR(NORMAL_2RSI12         ) , _D_U6L4(  SLTUI     ) , _E(SLTUI    ) , _TXT(2RI12      ) };

    codedef PCADDU12I   { "pcaddu12i"   , _T(X_1RI20  ) , _TR(EXTENDED_1RI20PC      ) , _D_U6L1(  PCADDU12I ) , _E(PCADDU12I) , _TXT(X1RI20     ) };

    codedef AND         { "and"         , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( AND       ) , _E(AND      ) , _TXT(3R         ) };
    codedef OR          { "or"          , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( OR        ) , _E(OR       ) , _TXT(3R         ) };
    codedef NOR         { "nor"         , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( NOR       ) , _E(NOR      ) , _TXT(3R         ) };
    codedef XOR         { "xor"         , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( XOR       ) , _E(XOR      ) , _TXT(3R         ) };

    codedef ANDI        { "andi"        , _T(2RI12    ) , _TR(NORMAL_2RUI12         ) , _D_U6L4(  ANDI      ) , _E(ANDI     ) , _TXT(2RI12      ) };
    codedef ORI         { "ori"         , _T(2RI12    ) , _TR(NORMAL_2RUI12         ) , _D_U6L4(  ORI       ) , _E(ORI      ) , _TXT(2RI12      ) };
    codedef XORI        { "xori"        , _T(2RI12    ) , _TR(NORMAL_2RUI12         ) , _D_U6L4(  XORI      ) , _E(XORI     ) , _TXT(2RI12      ) };

    //
    codedef MUL_W       { "mul.w"       , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( MUL_W     ) , _E(MUL_W    ) , _TXT(3R         ) };
    codedef MULH_W      { "mulh.w"      , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( MULH_W    ) , _E(MULH_W   ) , _TXT(3R         ) };
    codedef MULH_WU     { "mulh.wu"     , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( MULH_WU   ) , _E(MULH_WU  ) , _TXT(3R         ) };

    codedef DIV_W       { "div.w"       , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( DIV_W     ) , _E(DIV_W    ) , _TXT(3R         ) };
    codedef DIV_WU      { "div.wu"      , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( DIV_WU    ) , _E(DIV_WU   ) , _TXT(3R         ) };
    codedef MOD_W       { "mod.w"       , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( MOD_W     ) , _E(MOD_W    ) , _TXT(3R         ) };
    codedef MOD_WU      { "mod.wu"      , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( MOD_WU    ) , _E(MOD_WU   ) , _TXT(3R         ) };

    //
    codedef SLL_W       { "sll.w"       , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( SLL_W     ) , _E(SLL_W    ) , _TXT(3R         ) };
    codedef SRL_W       { "srl.w"       , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( SRL_W     ) , _E(SRL_W    ) , _TXT(3R         ) };
    codedef SRA_W       { "sra.w"       , _T(3R       ) , _TR(NORMAL_3R             ) , _D_U6L11( SRA_W     ) , _E(SRA_W    ) , _TXT(3R         ) };

    codedef SLLI_W      { "slli.w"      , _T(X_2RI5   ) , _TR(EXTENDED_2RI5         ) , _D_U6L11( SLLI_W    ) , _E(SLLI_W   ) , _TXT(X2RI5      ) };
    codedef SRLI_W      { "srli.w"      , _T(X_2RI5   ) , _TR(EXTENDED_2RI5         ) , _D_U6L11( SRLI_W    ) , _E(SRLI_W   ) , _TXT(X2RI5      ) };
    codedef SRAI_W      { "srai.w"      , _T(X_2RI5   ) , _TR(EXTENDED_2RI5         ) , _D_U6L11( SRAI_W    ) , _E(SRAI_W   ) , _TXT(X2RI5      ) };

    //
    codedef BEQ         { "beq"         , _T(2RI16    ) , _TR(NORMAL_2ROFFS16       ) , _D_U6L0(  BEQ       ) , _E(BEQ      ) , _TXT(2ROffs16   ) };
    codedef BNE         { "bne"         , _T(2RI16    ) , _TR(NORMAL_2ROFFS16       ) , _D_U6L0(  BNE       ) , _E(BNE      ) , _TXT(2ROffs16   ) };
    codedef BLT         { "blt"         , _T(2RI16    ) , _TR(NORMAL_2ROFFS16       ) , _D_U6L0(  BLT       ) , _E(BLT      ) , _TXT(2ROffs16   ) };
    codedef BGE         { "bge"         , _T(2RI16    ) , _TR(NORMAL_2ROFFS16       ) , _D_U6L0(  BGE       ) , _E(BGE      ) , _TXT(2ROffs16   ) };
    codedef BLTU        { "bltu"        , _T(2RI16    ) , _TR(NORMAL_2ROFFS16       ) , _D_U6L0(  BLTU      ) , _E(BLTU     ) , _TXT(2ROffs16   ) };
    codedef BGEU        { "bgeu"        , _T(2RI16    ) , _TR(NORMAL_2ROFFS16       ) , _D_U6L0(  BGEU      ) , _E(BGEU     ) , _TXT(2ROffs16   ) };

    codedef B           { "b"           , _T(I26      ) , _TR(NORMAL_OFFS26         ) , _D_U6L0(  B         ) , _E(B        ) , _TXT(Offs26     ) };
    codedef BL          { "bl"          , _T(I26      ) , _TR(NORMAL_OFFS26R1       ) , _D_U6L0(  BL        ) , _E(BL       ) , _TXT(Offs26     ) };

    codedef JIRL        { "jirl"        , _T(2RI16    ) , _TR(JIRL_2ROFFS16         ) , _D_U6L0(  JIRL      ) , _E(JIRL     ) , _TXT(2ROffs16   ) };

    //
    codedef LD_B        { "ld.b"        , _T(2RI12    ) , _TR(NORMAL_LOAD_2RSI12    ) , _D_U6L4(  LD_B      ) , _E(LD_B     ) , _TXT(2RI12      ) };
    codedef LD_H        { "ld.h"        , _T(2RI12    ) , _TR(NORMAL_LOAD_2RSI12    ) , _D_U6L4(  LD_H      ) , _E(LD_H     ) , _TXT(2RI12      ) };
    codedef LD_W        { "ld.w"        , _T(2RI12    ) , _TR(NORMAL_LOAD_2RSI12    ) , _D_U6L4(  LD_W      ) , _E(LD_W     ) , _TXT(2RI12      ) };
    codedef LD_BU       { "ld.bu"       , _T(2RI12    ) , _TR(NORMAL_LOAD_2RSI12    ) , _D_U6L4(  LD_BU     ) , _E(LD_BU    ) , _TXT(2RI12      ) };
    codedef LD_HU       { "ld.hu"       , _T(2RI12    ) , _TR(NORMAL_LOAD_2RSI12    ) , _D_U6L4(  LD_HU     ) , _E(LD_HU    ) , _TXT(2RI12      ) };

    codedef ST_B        { "st.b"        , _T(2RI12    ) , _TR(NORMAL_STORE_2RSI12   ) , _D_U6L4(  ST_B      ) , _E(ST_B     ) , _TXT(2RI12      ) };
    codedef ST_H        { "st.h"        , _T(2RI12    ) , _TR(NORMAL_STORE_2RSI12   ) , _D_U6L4(  ST_H      ) , _E(ST_H     ) , _TXT(2RI12      ) };
    codedef ST_W        { "st.w"        , _T(2RI12    ) , _TR(NORMAL_STORE_2RSI12   ) , _D_U6L4(  ST_W      ) , _E(ST_W     ) , _TXT(2RI12      ) };


#undef _T
#undef _TR

#undef _D_U6L0
#undef _D_U6L1
#undef _D_U6L4
#undef _D_U6L11

#undef _E
}

namespace Jasse::CodepointSet {

#define _C(name)        &Jasse::Codepoint::LA32R_NSCSCC::name

    codesetdef LA32R_NSCSCC {
        //
        _C(ADD_W    ),
        _C(SUB_W    ),

        _C(ADDI_W   ),

        _C(LU12I_W  ),

        _C(SLT      ),
        _C(SLTU     ),

        _C(SLTI     ),
        _C(SLTUI    ),

        _C(PCADDU12I),

        _C(AND      ),
        _C(OR       ),
        _C(NOR      ),
        _C(XOR      ),
        
        _C(ANDI     ),
        _C(ORI      ),
        _C(XORI     ),

        //
        _C(MUL_W    ),
        _C(MULH_W   ),
        _C(MULH_WU  ),
        
        _C(DIV_W    ),
        _C(DIV_WU   ),
        _C(MOD_W    ),
        _C(MOD_WU   ),

        //
        _C(SLL_W    ),
        _C(SRL_W    ),
        _C(SRA_W    ),

        _C(SLLI_W   ),
        _C(SRLI_W   ),
        _C(SRAI_W   ),

        //
        _C(BEQ      ),
        _C(BNE      ),
        _C(BLT      ),
        _C(BGE      ),
        _C(BLTU     ),
        _C(BGEU     ),

        _C(B        ),
        _C(BL       ),
        _C(JIRL     ),

        //
        _C(LD_B     ),
        _C(LD_H     ),
        _C(LD_W     ),
        _C(LD_BU    ),
        _C(LD_HU    ),

        _C(ST_B     ),
        _C(ST_H     ),
        _C(ST_W     )
    };

#undef _C
}

