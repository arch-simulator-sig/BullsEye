#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// MIPS32-NSCSCC, event declarations
//

#include "mips32_nscscc_def_base.hpp"


#define eventdecl(name) \
    class name : public Base, public BullsEye::Event<name> { \
    public: \
        name(MIPS32Instance& instance, pc_t pc, MIPS32Instruction& insn) noexcept; \
    };


namespace Jasse::MIPS32PreExecutionEvents {

    class Base 
        : public MIPS32InstanceEventBase
        , public MIPS32PCEventBase
        , public MIPS32InstructionEventBase
        , public BullsEye::CancellableEvent {
    public:
        Base(MIPS32Instance& instance, pc_t pc, MIPS32Instruction& insn) noexcept;
    };


    eventdecl(ADD   );
    eventdecl(ADDI  );
    eventdecl(ADDU  );
    eventdecl(ADDIU );
    eventdecl(SUB   );
    eventdecl(SUBU  );
    eventdecl(SLT   );
    eventdecl(SLTI  );
    eventdecl(SLTU  );
    eventdecl(SLTIU );
    eventdecl(MUL   );

    eventdecl(AND   );
    eventdecl(ANDI  );
    eventdecl(LUI   );
    eventdecl(OR    );
    eventdecl(ORI   );
    eventdecl(XOR   );
    eventdecl(XORI  );

    eventdecl(SLL   );
    eventdecl(SLLV  );
    eventdecl(SRA   );
    eventdecl(SRAV  );
    eventdecl(SRL   );
    eventdecl(SRLV  );

    eventdecl(BEQ   );
    eventdecl(BNE   );
    eventdecl(BGEZ  );
    eventdecl(BGTZ  );
    eventdecl(BLEZ  );
    eventdecl(BLTZ  );
    eventdecl(J     );
    eventdecl(JAL   );
    eventdecl(JR    );
    eventdecl(JALR  );

    eventdecl(LB    );
    eventdecl(LW    );
    eventdecl(SB    );
    eventdecl(SW    );
}


namespace Jasse::MIPS32PostExecutionEvents {

    class Base 
        : public MIPS32InstanceEventBase
        , public MIPS32PCEventBase
        , public MIPS32InstructionEventBase {
    public:
        Base(MIPS32Instance& instance, pc_t pc, MIPS32Instruction& insn) noexcept;
    };


    eventdecl(ADD   );
    eventdecl(ADDI  );
    eventdecl(ADDU  );
    eventdecl(ADDIU );
    eventdecl(SUB   );
    eventdecl(SUBU  );
    eventdecl(SLT   );
    eventdecl(SLTI  );
    eventdecl(SLTU  );
    eventdecl(SLTIU );
    eventdecl(MUL   );

    eventdecl(AND   );
    eventdecl(ANDI  );
    eventdecl(LUI   );
    eventdecl(OR    );
    eventdecl(ORI   );
    eventdecl(XOR   );
    eventdecl(XORI  );

    eventdecl(SLL   );
    eventdecl(SLLV  );
    eventdecl(SRA   );
    eventdecl(SRAV  );
    eventdecl(SRL   );
    eventdecl(SRLV  );

    eventdecl(BEQ   );
    eventdecl(BNE   );
    eventdecl(BGEZ  );
    eventdecl(BGTZ  );
    eventdecl(BLEZ  );
    eventdecl(BLTZ  );
    eventdecl(J     );
    eventdecl(JAL   );
    eventdecl(JR    );
    eventdecl(JALR  );

    eventdecl(LB    );
    eventdecl(LW    );
    eventdecl(SB    );
    eventdecl(SW    );
}


#undef eventdecl
