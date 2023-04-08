#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// MIPS32-NSCSCC, decoding infrastructure declarations
//

#include "mips32_nscscc_def_base.hpp"
#include "mips32_nscscc_def_export.hpp"


#define MIPS32_DECODER_STUB(prefix, name)           MIPS32_NSCSCC_DecoderStub_##prefix##_##name
#define MIPS32_DECODER_STUB2(prefix, cat, name)     MIPS32_NSCSCC_DecoderStub_##prefix##_##cat##_##name


#define decdecl_stub(prefix, name) \
    bool MIPS32_DECODER_STUB(prefix, name)(MIPS32Instruction& insn) noexcept

#define decdecl_stub2(prefix, cat, name) \
    bool MIPS32_DECODER_STUB2(prefix, cat, name)(MIPS32Instruction& insn) noexcept


namespace Jasse {

    //
    decdecl_stub(Opcode, SPECIAL    );
    decdecl_stub(Opcode, SPECIAL2   );

    decdecl_stub(Opcode, REGIMM     );

    //
    decdecl_stub(Opcode, ADDI   );
    decdecl_stub(Opcode, ADDIU  );
    decdecl_stub(Opcode, SLTI   );
    decdecl_stub(Opcode, SLTIU  );

    decdecl_stub(Opcode, ANDI   );
    decdecl_stub(Opcode, LUI    );
    decdecl_stub(Opcode, ORI    );
    decdecl_stub(Opcode, XORI   );

    decdecl_stub(Opcode, BEQ    );
    decdecl_stub(Opcode, BNE    );
    decdecl_stub(Opcode, BGTZ   );
    decdecl_stub(Opcode, BLEZ   );
    decdecl_stub(Opcode, J      );
    decdecl_stub(Opcode, JAL    );

    decdecl_stub(Opcode, LB     );
    decdecl_stub(Opcode, LBU    );
    decdecl_stub(Opcode, LH     );
    decdecl_stub(Opcode, LHU    );
    decdecl_stub(Opcode, LW     );

    decdecl_stub(Opcode, SB     );
    decdecl_stub(Opcode, SH     );
    decdecl_stub(Opcode, SW     );


    //
    decdecl_stub2(Funct, SPECIAL, ADD   );
    decdecl_stub2(Funct, SPECIAL, ADDU  );
    decdecl_stub2(Funct, SPECIAL, SUB   );
    decdecl_stub2(Funct, SPECIAL, SUBU  );
    decdecl_stub2(Funct, SPECIAL, SLT   );
    decdecl_stub2(Funct, SPECIAL, SLTU  );

    decdecl_stub2(Funct, SPECIAL, AND   );
    decdecl_stub2(Funct, SPECIAL, OR    );
    decdecl_stub2(Funct, SPECIAL, XOR   );

    decdecl_stub2(Funct, SPECIAL, SLL   );
    decdecl_stub2(Funct, SPECIAL, SLLV  );
    decdecl_stub2(Funct, SPECIAL, SRA   );
    decdecl_stub2(Funct, SPECIAL, SRAV  );
    decdecl_stub2(Funct, SPECIAL, SRL   );
    decdecl_stub2(Funct, SPECIAL, SRLV  );

    decdecl_stub2(Funct, SPECIAL, JR    );
    decdecl_stub2(Funct, SPECIAL, JALR  );

    //
    decdecl_stub2(Funct, SPECIAL2, MUL  );

    //
    decdecl_stub2(Rt, REGIMM, BGEZ  );
    decdecl_stub2(Rt, REGIMM, BLTZ  );


    // MIPS32-NSCSCC Decoder
    class MIPS32NSCSCCDecoder : public MIPS32Decoder {
    public:
        MIPS32NSCSCCDecoder() noexcept;
        ~MIPS32NSCSCCDecoder() noexcept;

        virtual bool    Decode(MIPS32Instruction& insn) const noexcept override;
    };
}


#undef decdecl_stub
#undef decdecl_stub2
