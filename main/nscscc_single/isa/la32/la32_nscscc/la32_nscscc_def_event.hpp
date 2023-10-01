#pragma once
//
// LA32R (NSCSCC) ISA Emulator (Jasse)
//
// LA32R-NSCSCC, event declarations
//

#include "la32_nscscc_def_base.hpp"


#define eventdecl(name) \
    class name : public Base, public BullsEye::Event<name> { \
    public: \
        name(LA32Instance& instance, pc_t pc, LA32Instruction& insn) noexcept; \
    };


namespace Jasse::LA32R_NSCSCC::PreExecutionEvent {

    class Base
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32InstructionEventBase
        , public BullsEye::CancellableEvent {
    public:
        Base(LA32Instance& instance, pc_t pc, LA32Instruction& insn) noexcept;
    };


    eventdecl( ADD_W        );
    eventdecl( SUB_W        );

    eventdecl( ADDI_W       );

    eventdecl( LU12I_W      );

    eventdecl( SLT          );
    eventdecl( SLTU         );

    eventdecl( SLTI         );
    eventdecl( SLTUI        );

    eventdecl( PCADDU12I    );

    eventdecl( AND          );
    eventdecl( OR           );
    eventdecl( NOR          );
    eventdecl( XOR          );

    eventdecl( ANDI         );
    eventdecl( ORI          );
    eventdecl( XORI         );

    //
    eventdecl( MUL_W        );
    eventdecl( MULH_W       );
    eventdecl( MULH_WU      );

    eventdecl( DIV_W        );
    eventdecl( DIV_WU       );
    eventdecl( MOD_W        );
    eventdecl( MOD_WU       );

    //
    eventdecl( SLL_W        );
    eventdecl( SRL_W        );
    eventdecl( SRA_W        );

    eventdecl( SLLI_W       );
    eventdecl( SRLI_W       );
    eventdecl( SRAI_W       );

    //
    eventdecl( BEQ          );
    eventdecl( BNE          );
    eventdecl( BLT          );
    eventdecl( BGE          );
    eventdecl( BLTU         );
    eventdecl( BGEU         );

    eventdecl( B            );
    eventdecl( BL           );
    eventdecl( JIRL         );

    //
    eventdecl( LD_B         );
    eventdecl( LD_H         );
    eventdecl( LD_W         );
    eventdecl( LD_BU        );
    eventdecl( LD_HU        );

    eventdecl( ST_B         );
    eventdecl( ST_H         );
    eventdecl( ST_W         );
}

#undef eventdecl


#define eventdecl(name) \
    class name : public Base, public BullsEye::Event<name> { \
    public: \
        name(LA32Instance& instance, pc_t pc, const LA32Instruction& insn, LA32ExecOutcome outcome) noexcept; \
    }

namespace Jasse::LA32R_NSCSCC::PostExecutionEvent {
    
    class Base
        : public LA32InstanceEventBase
        , public LA32PCEventBase
        , public LA32ConstInstructionEventBase
        , public LA32ExecOutcomeEventBase {
    public:
        Base(LA32Instance& instance, pc_t pc, const LA32Instruction& insn, LA32ExecOutcome outcome) noexcept;
    };


    eventdecl( ADD_W        );
    eventdecl( SUB_W        );

    eventdecl( ADDI_W       );

    eventdecl( LU12I_W      );

    eventdecl( SLT          );
    eventdecl( SLTU         );

    eventdecl( SLTI         );
    eventdecl( SLTUI        );

    eventdecl( PCADDU12I    );

    eventdecl( AND          );
    eventdecl( OR           );
    eventdecl( NOR          );
    eventdecl( XOR          );

    eventdecl( ANDI         );
    eventdecl( ORI          );
    eventdecl( XORI         );

    //
    eventdecl( MUL_W        );
    eventdecl( MULH_W       );
    eventdecl( MULH_WU      );

    eventdecl( DIV_W        );
    eventdecl( DIV_WU       );
    eventdecl( MOD_W        );
    eventdecl( MOD_WU       );

    //
    eventdecl( SLL_W        );
    eventdecl( SRL_W        );
    eventdecl( SRA_W        );

    eventdecl( SLLI_W       );
    eventdecl( SRLI_W       );
    eventdecl( SRAI_W       );

    //
    eventdecl( BEQ          );
    eventdecl( BNE          );
    eventdecl( BLT          );
    eventdecl( BGE          );
    eventdecl( BLTU         );
    eventdecl( BGEU         );

    eventdecl( B            );
    eventdecl( BL           );
    eventdecl( JIRL         );

    //
    eventdecl( LD_B         );
    eventdecl( LD_H         );
    eventdecl( LD_W         );
    eventdecl( LD_BU        );
    eventdecl( LD_HU        );

    eventdecl( ST_B         );
    eventdecl( ST_H         );
    eventdecl( ST_W         );
}

#undef eventdecl
