#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// MIPS32-NSCSCC, bahaviour function declarations
//

#include "mips32_nscscc_def_base.hpp"


#define MIPS32_EXECUTOR_PARAMS          const MIPS32Instruction& insn, MIPS32Instance& inst
#define MIPS32_EXECUTOR(name)           MIPS32NSCSCCExecutor_##name


#define execdecl(name) \
    MIPS32ExecOutcome MIPS32_EXECUTOR(name)(MIPS32_EXECUTOR_PARAMS)


// Executors
namespace Jasse {

    execdecl(ADD    ) noexcept;
    execdecl(ADDI   ) noexcept;
    execdecl(ADDU   ) noexcept;
    execdecl(ADDIU  ) noexcept;
    execdecl(SUB    ) noexcept;
    execdecl(SUBU   ) noexcept;
    execdecl(SLT    ) noexcept;
    execdecl(SLTI   ) noexcept;
    execdecl(SLTU   ) noexcept;
    execdecl(SLTIU  ) noexcept;
    execdecl(MUL    ) noexcept;

    execdecl(AND    ) noexcept;
    execdecl(ANDI   ) noexcept;
    execdecl(LUI    ) noexcept;
    execdecl(OR     ) noexcept;
    execdecl(ORI    ) noexcept;
    execdecl(XOR    ) noexcept;
    execdecl(XORI   ) noexcept;

    execdecl(SLL    ) noexcept;
    execdecl(SLLV   ) noexcept;
    execdecl(SRA    ) noexcept;
    execdecl(SRAV   ) noexcept;
    execdecl(SRL    ) noexcept;
    execdecl(SRLV   ) noexcept;

    execdecl(BEQ    ) noexcept;
    execdecl(BNE    ) noexcept;
    execdecl(BGEZ   ) noexcept;
    execdecl(BGTZ   ) noexcept;
    execdecl(BLEZ   ) noexcept;
    execdecl(BLTZ   ) noexcept;
    execdecl(J      ) noexcept;
    execdecl(JAL    ) noexcept;
    execdecl(JR     ) noexcept;
    execdecl(JALR   ) noexcept;

    execdecl(MFHI   ) noexcept;
    execdecl(MFLO   ) noexcept;
    execdecl(MTHI   ) noexcept;
    execdecl(MTLO   ) noexcept;

    execdecl(DIV    ) noexcept;
    execdecl(DIVU   ) noexcept;
    execdecl(MULT   ) noexcept;
    execdecl(MULTU  ) noexcept;

    execdecl(LB     ) noexcept;
    execdecl(LBU    ) noexcept;
    execdecl(LH     ) noexcept;
    execdecl(LHU    ) noexcept;
    execdecl(LW     ) noexcept;

    execdecl(SB     ) noexcept;
    execdecl(SH     ) noexcept;
    execdecl(SW     ) noexcept;

    execdecl(TEQ    ) noexcept;
}

#undef execdecl
