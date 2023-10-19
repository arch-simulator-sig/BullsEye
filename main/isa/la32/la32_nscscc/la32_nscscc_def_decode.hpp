#pragma once
//
// LA32R (NSCSCC) ISA Emulator (Jasse)
//
// LA32R-NSCSCC, decoding infrastructure declarations
//

#ifndef __HEADER_JASSE_LA32__EXT_NSCSCC_DECODE_DEF
#define __HEADER_JASSE_LA32__EXT_NSCSCC_DECODE_DEF


#include "la32_nscscc_def_base.hpp"
#include "la32_nscscc_def_export.hpp"

#include <map>


#define LA32R_DECODER_STUB_U6L0(name)       DecoderStub_U6L0_##name
#define LA32R_DECODER_STUB_U6L1(name)       DecoderStub_U6L1_##name
#define LA32R_DECODER_STUB_U6L2(name)       DecoderStub_U6L2_##name
#define LA32R_DECODER_STUB_U6L4(name)       DecoderStub_U6L4_##name
#define LA32R_DECODER_STUB_U6L8(name)       DecoderStub_U6L8_##name
#define LA32R_DECODER_STUB_U6L6(name)       DecoderStub_U6L6_##name
#define LA32R_DECODER_STUB_U6L11(name)      DecoderStub_U6L11_##name
#define LA32R_DECODER_STUB_U6L16(name)      DecoderStub_U6L16_##name


#define decdecl_stub_U6L0(name) \
    bool LA32R_DECODER_STUB_U6L0(name)(LA32Instruction& insn) noexcept

#define decdecl_stub_U6L1(name) \
    bool LA32R_DECODER_STUB_U6L1(name)(LA32Instruction& insn) noexcept

#define decdecl_stub_U6L2(name) \
    bool LA32R_DECODER_STUB_U6L2(name)(LA32Instruction& insn) noexcept

#define decdecl_stub_U6L4(name) \
    bool LA32R_DECODER_STUB_U6L4(name)(LA32Instruction& insn) noexcept

#define decdecl_stub_U6L8(name) \
    bool LA32R_DECODER_STUB_U6L8(name)(LA32Instruction& insn) noexcept

#define decdecl_stub_U6L6(name) \
    bool LA32R_DECODER_STUB_U6L6(name)(LA32Instruction& insn) noexcept

#define decdecl_stub_U6L11(name) \
    bool LA32R_DECODER_STUB_U6L11(name)(LA32Instruction& insn) noexcept

#define decdecl_stub_U6L16(name) \
    bool LA32R_DECODER_STUB_U6L16(name)(LA32Instruction& insn) noexcept


namespace Jasse::LA32R_NSCSCC {

    //
    decdecl_stub_U6L11( ADD_W       );
    decdecl_stub_U6L11( SUB_W       );

    decdecl_stub_U6L4(  ADDI_W      );

    decdecl_stub_U6L1(  LU12I_W     );

    decdecl_stub_U6L11( SLT         );
    decdecl_stub_U6L11( SLTU        );

    decdecl_stub_U6L4(  SLTI        );
    decdecl_stub_U6L4(  SLTUI       );

    decdecl_stub_U6L1(  PCADDU12I   );

    decdecl_stub_U6L11( AND         );
    decdecl_stub_U6L11( OR          );
    decdecl_stub_U6L11( NOR         );
    decdecl_stub_U6L11( XOR         );

    decdecl_stub_U6L4(  ANDI        );
    decdecl_stub_U6L4(  ORI         );
    decdecl_stub_U6L4(  XORI        );

    //
    decdecl_stub_U6L11( MUL_W       );
    decdecl_stub_U6L11( MULH_W      );
    decdecl_stub_U6L11( MULH_WU     );

    decdecl_stub_U6L11( DIV_W       );
    decdecl_stub_U6L11( DIV_WU      );
    decdecl_stub_U6L11( MOD_W       );
    decdecl_stub_U6L11( MOD_WU      );

    //
    decdecl_stub_U6L11( SLL_W       );
    decdecl_stub_U6L11( SRL_W       );
    decdecl_stub_U6L11( SRA_W       );

    decdecl_stub_U6L11( SLLI_W      );
    decdecl_stub_U6L11( SRLI_W      );
    decdecl_stub_U6L11( SRAI_W      );

    //
    decdecl_stub_U6L0(  BEQ         );
    decdecl_stub_U6L0(  BNE         );
    decdecl_stub_U6L0(  BLT         );
    decdecl_stub_U6L0(  BGE         );
    decdecl_stub_U6L0(  BLTU        );
    decdecl_stub_U6L0(  BGEU        );

    decdecl_stub_U6L0(  B           );
    decdecl_stub_U6L0(  BL          );
    decdecl_stub_U6L0(  JIRL        );

    //
    decdecl_stub_U6L4(  LD_B        );
    decdecl_stub_U6L4(  LD_H        );
    decdecl_stub_U6L4(  LD_W        );
    decdecl_stub_U6L4(  LD_BU       );
    decdecl_stub_U6L4(  LD_HU       );

    decdecl_stub_U6L4(  ST_B        );
    decdecl_stub_U6L4(  ST_H        );
    decdecl_stub_U6L4(  ST_W        );


    // LA32R-NSCSCC Decoder
    class Decoder : public LA32Decoder {
    private:
        LA32DecodeCapable** tree;

    public:
        Decoder() noexcept;
        ~Decoder() noexcept;

        virtual bool    Decode(LA32Instruction& insn) const noexcept override;
    };
}


#undef decdecl_stub_U6L0
#undef decdecl_stub_U6L2
#undef decdecl_stub_U6L4
#undef decdecl_stub_U6L8
#undef decdecl_stub_U6L6
#undef decdecl_stub_U6L11
#undef decdecl_stub_U6L16


#endif
