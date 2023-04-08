#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// MIPS32-NSCSCC, event implementations
//

#include "mips32_nscscc_def_event.hpp"


#define implevent(name) \
    name::name(MIPS32Instance& instance, pc_t pc, MIPS32Instruction& insn) noexcept \
        : Base(instance, pc, insn) \
    { } \


// Implementation of: class MIPS32PreExecutionEvents::Base
namespace Jasse::MIPS32PreExecutionEvents {

    Base::Base(MIPS32Instance& instance, pc_t pc, MIPS32Instruction& insn) noexcept
        : MIPS32InstanceEventBase       (instance)
        , MIPS32PCEventBase             (pc)
        , MIPS32InstructionEventBase    (insn)
    { }
}

// Implementation of MIPS32PreExecutionEvents
namespace Jasse::MIPS32PreExecutionEvents {

    implevent(ADD   );
    implevent(ADDI  );
    implevent(ADDU  );
    implevent(ADDIU );
    implevent(SUB   );
    implevent(SUBU  );
    implevent(SLT   );
    implevent(SLTI  );
    implevent(SLTU  );
    implevent(SLTIU );
    implevent(MUL   );

    implevent(AND   );
    implevent(ANDI  );
    implevent(LUI   );
    implevent(OR    );
    implevent(ORI   );
    implevent(XOR   );
    implevent(XORI  );

    implevent(SLL   );
    implevent(SLLV  );
    implevent(SRA   );
    implevent(SRAV  );
    implevent(SRL   );
    implevent(SRLV  );

    implevent(BEQ   );
    implevent(BNE   );
    implevent(BGEZ  );
    implevent(BGTZ  );
    implevent(BLEZ  );
    implevent(BLTZ  );
    implevent(J     );
    implevent(JAL   );
    implevent(JR    );
    implevent(JALR  );

    implevent(MFHI  );
    implevent(MFLO  );
    implevent(MTHI  );
    implevent(MTLO  );

    implevent(LB    );
    implevent(LBU   );
    implevent(LH    );
    implevent(LHU   );
    implevent(LW    );

    implevent(SB    );
    implevent(SH    );
    implevent(SW    );
}

#undef implevent


#define implevent(name) \
    name::name(MIPS32Instance& instance, pc_t pc, const MIPS32Instruction& insn, MIPS32ExecOutcome outcome) noexcept \
        : Base(instance, pc, insn, outcome) \
    { } \

// Implementation of: class MIPS32PostExecutionEvents::Base
namespace Jasse::MIPS32PostExecutionEvents {

    Base::Base(MIPS32Instance& instance, pc_t pc, const MIPS32Instruction& insn, MIPS32ExecOutcome outcome) noexcept
        : MIPS32InstanceEventBase           (instance)
        , MIPS32PCEventBase                 (pc)
        , MIPS32ConstInstructionEventBase   (insn)
        , MIPS32ExecOutcomeEventBase        (outcome)
    { }
}

// Implementation of MIPS32PostExecutionEvents
namespace Jasse::MIPS32PostExecutionEvents {

    implevent(ADD   );
    implevent(ADDI  );
    implevent(ADDU  );
    implevent(ADDIU );
    implevent(SUB   );
    implevent(SUBU  );
    implevent(SLT   );
    implevent(SLTI  );
    implevent(SLTU  );
    implevent(SLTIU );
    implevent(MUL   );

    implevent(AND   );
    implevent(ANDI  );
    implevent(LUI   );
    implevent(OR    );
    implevent(ORI   );
    implevent(XOR   );
    implevent(XORI  );

    implevent(SLL   );
    implevent(SLLV  );
    implevent(SRA   );
    implevent(SRAV  );
    implevent(SRL   );
    implevent(SRLV  );

    implevent(BEQ   );
    implevent(BNE   );
    implevent(BGEZ  );
    implevent(BGTZ  );
    implevent(BLEZ  );
    implevent(BLTZ  );
    implevent(J     );
    implevent(JAL   );
    implevent(JR    );
    implevent(JALR  );

    implevent(MFHI  );
    implevent(MFLO  );
    implevent(MTHI  );
    implevent(MTLO  );

    implevent(LB    );
    implevent(LBU   );
    implevent(LH    );
    implevent(LHU   );
    implevent(LW    );

    implevent(SB    );
    implevent(SH    );
    implevent(SW    );
}


#undef implevent
