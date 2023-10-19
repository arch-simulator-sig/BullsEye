#include "la32_nscscc_def_event.hpp"
//
// LA32R (NSCSCC) ISA Emulator (Jasse)
//
// LA32R-NSCSCC, event implementations
//


#define implevent(name) \
    name::name(LA32Instance& instance, pc_t pc, LA32Instruction& insn) noexcept \
        : Base(instance, pc, insn) \
    { }


// Implementation of: class LA32R_NSCSCC::PreExecutionEvent::Base
namespace Jasse::LA32R_NSCSCC::PreExecutionEvent {

    Base::Base(LA32Instance& instance, pc_t pc, LA32Instruction& insn) noexcept
        : LA32InstanceEventBase       (instance)
        , LA32PCEventBase             (pc)
        , LA32InstructionEventBase    (insn)
    { }
}

// Implementation of PreExecutionEvent
namespace Jasse::LA32R_NSCSCC::PreExecutionEvent {

    implevent( ADD_W        );
    implevent( SUB_W        );

    implevent( ADDI_W       );

    implevent( LU12I_W      );

    implevent( SLT          );
    implevent( SLTU         );

    implevent( SLTI         );
    implevent( SLTUI        );

    implevent( PCADDU12I    );

    implevent( AND          );
    implevent( OR           );
    implevent( NOR          );
    implevent( XOR          );

    implevent( ANDI         );
    implevent( ORI          );
    implevent( XORI         );

    //
    implevent( MUL_W        );
    implevent( MULH_W       );
    implevent( MULH_WU      );

    implevent( DIV_W        );
    implevent( DIV_WU       );
    implevent( MOD_W        );
    implevent( MOD_WU       );

    //
    implevent( SLL_W        );
    implevent( SRL_W        );
    implevent( SRA_W        );

    implevent( SLLI_W       );
    implevent( SRLI_W       );
    implevent( SRAI_W       );

    //
    implevent( BEQ          );
    implevent( BNE          );
    implevent( BLT          );
    implevent( BGE          );
    implevent( BLTU         );
    implevent( BGEU         );

    implevent( B            );
    implevent( BL           );
    implevent( JIRL         );

    //
    implevent( LD_B         );
    implevent( LD_H         );
    implevent( LD_W         );
    implevent( LD_BU        );
    implevent( LD_HU        );

    implevent( ST_B         );
    implevent( ST_H         );
    implevent( ST_W         );
}

#undef implevent


#define implevent(name) \
    name::name(LA32Instance& instance, pc_t pc, const LA32Instruction& insn, LA32ExecOutcome outcome) noexcept \
        : Base(instance, pc, insn, outcome) \
    { }

// Implementation of: class LA32R_NSCSCC::PostExecutionEvent::Base
namespace Jasse::LA32R_NSCSCC::PostExecutionEvent {

    Base::Base(LA32Instance& instance, pc_t pc, const LA32Instruction& insn, LA32ExecOutcome outcome) noexcept
        : LA32InstanceEventBase           (instance)
        , LA32PCEventBase                 (pc)
        , LA32ConstInstructionEventBase   (insn)
        , LA32ExecOutcomeEventBase        (outcome)
    { }
}

// Implementation of PostExecutionEvent
namespace Jasse::LA32R_NSCSCC::PostExecutionEvent {

    implevent( ADD_W        );
    implevent( SUB_W        );

    implevent( ADDI_W       );

    implevent( LU12I_W      );

    implevent( SLT          );
    implevent( SLTU         );

    implevent( SLTI         );
    implevent( SLTUI        );

    implevent( PCADDU12I    );

    implevent( AND          );
    implevent( OR           );
    implevent( NOR          );
    implevent( XOR          );

    implevent( ANDI         );
    implevent( ORI          );
    implevent( XORI         );

    //
    implevent( MUL_W        );
    implevent( MULH_W       );
    implevent( MULH_WU      );

    implevent( DIV_W        );
    implevent( DIV_WU       );
    implevent( MOD_W        );
    implevent( MOD_WU       );

    //
    implevent( SLL_W        );
    implevent( SRL_W        );
    implevent( SRA_W        );

    implevent( SLLI_W       );
    implevent( SRLI_W       );
    implevent( SRAI_W       );

    //
    implevent( BEQ          );
    implevent( BNE          );
    implevent( BLT          );
    implevent( BGE          );
    implevent( BLTU         );
    implevent( BGEU         );

    implevent( B            );
    implevent( BL           );
    implevent( JIRL         );

    //
    implevent( LD_B         );
    implevent( LD_H         );
    implevent( LD_W         );
    implevent( LD_BU        );
    implevent( LD_HU        );

    implevent( ST_B         );
    implevent( ST_H         );
    implevent( ST_W         );
}

#undef implevent
