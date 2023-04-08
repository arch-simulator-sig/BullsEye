#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// MIPS32-NSCSCC, decoding infrastructure implementations
//

#include "mips32_nscscc_def_decode.hpp"

#include <algorithm>


#define impldec_stub_static(prefix, name, codepoint) \
    inline bool MIPS32_DECODER_STUB(prefix, name)(MIPS32Instruction& insn) noexcept { insn.SetCodepoint(&codepoint); return true; }

#define impldec_stub_pred(prefix, name, expr) \
    inline bool MIPS32_DECODER_STUB(prefix, name)(MIPS32Instruction& insn) noexcept { expr; }


#define impldec_stub2_static(prefix, cat, name, codepoint) \
    inline bool MIPS32_DECODER_STUB2(prefix, cat, name)(MIPS32Instruction& insn) noexcept { insn.SetCodepoint(&codepoint); return true; }

#define impldec_stub2_pred(prefix, cat, name, expr) \
    inline bool MIPS32_DECODER_STUB2(prefix, cat, name)(MIPS32Instruction& insn) noexcept { expr; }


// 
namespace Jasse {

    //
    impldec_stub_static(Opcode, ADDI,   MIPS32_ADDI);
    impldec_stub_static(Opcode, ADDIU,  MIPS32_ADDIU);
    impldec_stub_static(Opcode, SLTI,   MIPS32_SLTI);
    impldec_stub_static(Opcode, SLTIU,  MIPS32_SLTIU);

    impldec_stub_static(Opcode, ANDI,   MIPS32_ANDI);
    impldec_stub_static(Opcode, LUI,    MIPS32_LUI);
    impldec_stub_static(Opcode, ORI,    MIPS32_ORI);
    impldec_stub_static(Opcode, XORI,   MIPS32_XORI);

    impldec_stub_static(Opcode, BEQ,    MIPS32_BEQ);
    impldec_stub_static(Opcode, BNE,    MIPS32_BNE);
    impldec_stub_static(Opcode, BGTZ,   MIPS32_BGTZ);
    impldec_stub_static(Opcode, BLEZ,   MIPS32_BLEZ);
    impldec_stub_static(Opcode, J,      MIPS32_J);
    impldec_stub_static(Opcode, JAL,    MIPS32_JAL);

    impldec_stub_static(Opcode, LB,     MIPS32_LB);
    impldec_stub_static(Opcode, LBU,    MIPS32_LBU);
    impldec_stub_static(Opcode, LH,     MIPS32_LH);
    impldec_stub_static(Opcode, LHU,    MIPS32_LHU);
    impldec_stub_static(Opcode, LW,     MIPS32_LW);

    impldec_stub_static(Opcode, SB,     MIPS32_SB);
    impldec_stub_static(Opcode, SH,     MIPS32_SH);
    impldec_stub_static(Opcode, SW,     MIPS32_SW);

    //
    impldec_stub2_static(Funct, SPECIAL, ADD,    MIPS32_ADD);
    impldec_stub2_static(Funct, SPECIAL, ADDU,   MIPS32_ADDU);
    impldec_stub2_static(Funct, SPECIAL, SUB,    MIPS32_SUB);
    impldec_stub2_static(Funct, SPECIAL, SUBU,   MIPS32_SUBU);
    impldec_stub2_static(Funct, SPECIAL, SLT,    MIPS32_SLT);
    impldec_stub2_static(Funct, SPECIAL, SLTU,   MIPS32_SLTU);

    impldec_stub2_static(Funct, SPECIAL, AND,    MIPS32_AND);
    impldec_stub2_static(Funct, SPECIAL, OR,     MIPS32_OR);
    impldec_stub2_static(Funct, SPECIAL, XOR,    MIPS32_XOR);

    impldec_stub2_static(Funct, SPECIAL, SLL,    MIPS32_SLL);
    impldec_stub2_static(Funct, SPECIAL, SLLV,   MIPS32_SLLV);
    impldec_stub2_static(Funct, SPECIAL, SRA,    MIPS32_SRA);
    impldec_stub2_static(Funct, SPECIAL, SRAV,   MIPS32_SRAV);
    impldec_stub2_static(Funct, SPECIAL, SRL,    MIPS32_SRL);
    impldec_stub2_static(Funct, SPECIAL, SRLV,   MIPS32_SRLV);

    impldec_stub2_static(Funct, SPECIAL, JR,     MIPS32_JR);
    impldec_stub2_static(Funct, SPECIAL, JALR,   MIPS32_JALR);

    //
    impldec_stub2_static(Funct, SPECIAL, MFHI,   MIPS32_MFHI);
    impldec_stub2_static(Funct, SPECIAL, MFLO,   MIPS32_MFLO);
    impldec_stub2_static(Funct, SPECIAL, MTHI,   MIPS32_MTHI);
    impldec_stub2_static(Funct, SPECIAL, MTLO,   MIPS32_MTLO);

    //
    impldec_stub2_static(Funct, SPECIAL2, MUL,   MIPS32_MUL);

    //
    impldec_stub2_static(Rt, REGIMM, BGEZ,  MIPS32_BGEZ);
    impldec_stub2_static(Rt, REGIMM, BLTZ,  MIPS32_BLTZ);
}


//
namespace Jasse {

    //
#define stub_slot(name) stubs[MIPS32_FUNCT_SPECIAL_##name] = &MIPS32_DECODER_STUB2(Funct, SPECIAL, name)

    static class _IMPLDEC_NSCSCC_STUB_CLASS_GROUP_SPECIAL final {
    public:
        static constexpr size_t     SIZE = 1U << 6;

        MIPS32DecodePath*           stubs;

    public:
        _IMPLDEC_NSCSCC_STUB_CLASS_GROUP_SPECIAL() noexcept
            : stubs (new MIPS32DecodePath[SIZE])
        {
            std::fill(stubs, stubs + SIZE, nullptr);

            stub_slot(ADD   );
            stub_slot(ADDU  );
            stub_slot(SUB   );
            stub_slot(SUBU  ); 
            stub_slot(SLT   );
            stub_slot(SLTU  );

            stub_slot(AND   );
            stub_slot(OR    );
            stub_slot(XOR   );

            stub_slot(SLL   );
            stub_slot(SLLV  );
            stub_slot(SRA   );
            stub_slot(SRAV  );
            stub_slot(SRL   );
            stub_slot(SRLV  );

            stub_slot(JR    );
            stub_slot(JALR  );
        }

        ~_IMPLDEC_NSCSCC_STUB_CLASS_GROUP_SPECIAL() noexcept
        {
            delete[] stubs;
        }

    } const *const _IMPLDEC_NSCSCC_STUB_GROUP_SPECIAL = new _IMPLDEC_NSCSCC_STUB_CLASS_GROUP_SPECIAL; 

    impldec_stub_pred(Opcode, SPECIAL, {

        MIPS32DecodePath stub 
            = _IMPLDEC_NSCSCC_STUB_GROUP_SPECIAL->stubs[insn.GetFunct()];

        return stub ? (*stub)(insn) : false;
    });

#undef stub_slot

    //
    impldec_stub_pred(Opcode, SPECIAL2, {
        
        if (insn.GetFunct() == MIPS32_FUNCT_SPECIAL2_MUL)
            return MIPS32_DECODER_STUB2(Funct, SPECIAL2, MUL)(insn);

        return false;
    });

    //
    impldec_stub_pred(Opcode, REGIMM, {
        
        if (insn.GetRT() == MIPS32_RT_REGIMM_BGEZ)
            return MIPS32_DECODER_STUB2(Rt, REGIMM, BGEZ)(insn);
        else if (insn.GetRT() == MIPS32_RT_REGIMM_BLTZ)
            return MIPS32_DECODER_STUB2(Rt, REGIMM, BLTZ)(insn);

        return false;
    });
}


// Implementation of: class MIPS32NSCSCCDecoder
namespace Jasse {

    //
#define stub_slot(name) stubs[MIPS32_OPCODE_##name] = &MIPS32_DECODER_STUB(Opcode, name)

    static class _IMPLDEC_NSCSCC_STUB_CLASS_GLOBAL final {
    public:
        static constexpr size_t     SIZE = 1U << 6;

        MIPS32DecodePath*           stubs;

    public:
        _IMPLDEC_NSCSCC_STUB_CLASS_GLOBAL() noexcept
            : stubs (new MIPS32DecodePath[SIZE])
        {
            std::fill(stubs, stubs + SIZE, nullptr);

            //
            stub_slot(SPECIAL   );
            stub_slot(SPECIAL2  );

            stub_slot(REGIMM    );

            //
            stub_slot(ADDI  );
            stub_slot(ADDIU );
            stub_slot(SLTI  );
            stub_slot(SLTIU );

            stub_slot(ANDI  );
            stub_slot(LUI   );
            stub_slot(ORI   );
            stub_slot(XORI  );

            stub_slot(BEQ   );
            stub_slot(BNE   );
            stub_slot(BGTZ  );
            stub_slot(BLEZ  );
            stub_slot(J     );
            stub_slot(JAL   );

            stub_slot(LB    );
            stub_slot(LBU   );
            stub_slot(LH    );
            stub_slot(LHU   );
            stub_slot(LW    );

            stub_slot(SB    );
            stub_slot(SH    );
            stub_slot(SW    );
        }

        ~_IMPLDEC_NSCSCC_STUB_CLASS_GLOBAL() noexcept
        {
            delete[] stubs;
        }

    } const *const _IMPLDEC_NSCSCC_STUB_GLOBAL = new _IMPLDEC_NSCSCC_STUB_CLASS_GLOBAL;

#undef stub_slot

    //
    MIPS32NSCSCCDecoder::MIPS32NSCSCCDecoder() noexcept
        : MIPS32Decoder("mips32", "MIPS32-NSCSCC")
    { }

    MIPS32NSCSCCDecoder::~MIPS32NSCSCCDecoder() noexcept
    { }

    bool MIPS32NSCSCCDecoder::Decode(MIPS32Instruction& insn) const noexcept
    {
        MIPS32DecodePath stub 
            = _IMPLDEC_NSCSCC_STUB_GLOBAL->stubs[insn.GetOpcode()];

        return stub ? (*stub)(insn) : false;
    }
}

#undef impldec_stub_static
#undef impldec_stub_pred

#undef impldec_stub2_static
#undef impldec_stub2_pred
