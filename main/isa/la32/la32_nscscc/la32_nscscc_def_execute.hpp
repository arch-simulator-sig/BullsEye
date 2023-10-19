#pragma once
//
// LA32R (NSCSCC) ISA Emulator (Jasse)
//
// LA32R-NSCSCC, bahaviour function declarations
//

#ifndef __HEADER_JASSE_LA32__EXT_NSCSCC_EXECUTE_DEF
#define __HEADER_JASSE_LA32__EXT_NSCSCC_EXECUTE_DEF


#include "la32_nscscc_def_base.hpp"


#define LA32R_EXECUTOR_PARAMS          const LA32Instruction& insn, LA32Instance& inst
#define LA32R_EXECUTOR(name)           LA32NSCSCCExecutor_##name


#define execdecl(name) \
    LA32ExecOutcome LA32R_EXECUTOR(name)(LA32R_EXECUTOR_PARAMS) noexcept


// Executors
namespace Jasse::LA32R_NSCSCC {

    //
    execdecl( ADD_W     );
    execdecl( SUB_W     );

    execdecl( ADDI_W    );

    execdecl( LU12I_W   );

    execdecl( SLT       );
    execdecl( SLTU      );

    execdecl( SLTI      );
    execdecl( SLTUI     );

    execdecl( PCADDU12I );

    execdecl( AND       );
    execdecl( OR        );
    execdecl( NOR       );
    execdecl( XOR       );

    execdecl( ANDI      );
    execdecl( ORI       );
    execdecl( XORI      );

    //
    execdecl( MUL_W     );
    execdecl( MULH_W    );
    execdecl( MULH_WU   );

    execdecl( DIV_W     );
    execdecl( DIV_WU    );
    execdecl( MOD_W     );
    execdecl( MOD_WU    );

    //
    execdecl( SLL_W     );
    execdecl( SRL_W     );
    execdecl( SRA_W     );

    execdecl( SLLI_W    );
    execdecl( SRLI_W    );
    execdecl( SRAI_W    );

    //
    execdecl( BEQ       );
    execdecl( BNE       );
    execdecl( BLT       );
    execdecl( BGE       );
    execdecl( BLTU      );
    execdecl( BGEU      );

    execdecl( B         );
    execdecl( BL        );
    execdecl( JIRL      );

    //
    execdecl( LD_B      );
    execdecl( LD_H      );
    execdecl( LD_W      );
    execdecl( LD_BU     );
    execdecl( LD_HU     );

    execdecl( ST_B      );
    execdecl( ST_H      );
    execdecl( ST_W      );
}


#undef execdecl


#endif
