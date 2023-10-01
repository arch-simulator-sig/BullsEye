#pragma once
//
// LA32R (NSCSCC) ISA Emulator (Jasse)
//
// LA32R-NSCSCC, encoding definitions
//

#include "la32_nscscc_def_base.hpp"


//
#define ENCODE_LA32_ADD_W(rd, rj, rk)           ENCODE_LA32_STD_TYPE_3R(ADD_W, rk, rj, rd)
#define ENCODE_LA32_SUB_W(rd, rj, rk)           ENCODE_LA32_STD_TYPE_3R(SUB_W, rk, rj, rd)

#define ENCODE_LA32_ADDI_W(rd, rj, si12)        ENCODE_LA32_STD_TYPE_2RI12(ADDI_W, si12, rj, rd)

#define ENCODE_LA32_LU12I_W(rd, si20)           ENCODE_LA32_STD_TYPE_X_1RI20(LU12I_W, si20, rd)

#define ENCODE_LA32_SLT(rd, rj, rk)             ENCODE_LA32_STD_TYPE_3R(SLT, rk, rj, rd)
#define ENCODE_LA32_SLTU(rd, rj, rk)            ENCODE_LA32_STD_TYPE_3R(SLTU, rk, rj, rd)

#define ENCODE_LA32_SLTI(rd, rj, si12)          ENCODE_LA32_STD_TYPE_2RI12(SLTI, si12, rj, rd)
#define ENCODE_LA32_SLTUI(rd, rj, si12)         ENCODE_LA32_STD_TYPE_2RI12(SLTUI, si12, rj, rd)

#define ENCODE_LA32_PCADDU12I(rd, si20)         ENCODE_LA32_STD_TYPE_X_1RI20(PCADDU12I, si20, rd)

#define ENCODE_LA32_AND(rd, rj, rk)             ENCODE_LA32_STD_TYPE_3R(AND, rk, rj, rd)
#define ENCODE_LA32_OR(rd, rj, rk)              ENCODE_LA32_STD_TYPE_3R(OR, rk, rj, rd)
#define ENCODE_LA32_NOR(rd, rj, rk)             ENCODE_LA32_STD_TYPE_3R(NOR, rk, rj, rd)
#define ENCODE_LA32_XOR(rd, rj, rk)             ENCODE_LA32_STD_TYPE_3R(XOR, rk, rj, rd)

#define ENCODE_LA32_ANDI(rd, rj, si12)          ENCODE_LA32_STD_TYPE_2RI12(ANDI, si12, rj, rd)
#define ENCODE_LA32_ORI(rd, rj, si12)           ENCODE_LA32_STD_TYPE_2RI12(ORI, si12, rj, rd)
#define ENCODE_LA32_XORI(rd, rj, si12)          ENCODE_LA32_STD_TYPE_2RI12(XORI, si12, rj, rd)

#define ENCODE_LA32_MUL_W(rd, rj, rk)           ENCODE_LA32_STD_TYPE_3R(MUL_W, rk, rj, rd)
#define ENCODE_LA32_MULH_W(rd, rj, rk)          ENCODE_LA32_STD_TYPE_3R(MULH_W, rk, rj, rd)
#define ENCODE_LA32_MULH_WU(rd, rj, rk)         ENCODE_LA32_STD_TYPE_3R(MULH_WU, rk, rj, rd)

#define ENCODE_LA32_DIV_W(rd, rj, rk)           ENCODE_LA32_STD_TYPE_3R(DIV_W, rk, rj, rd)
#define ENCODE_LA32_DIV_WU(rd, rj, rk)          ENCODE_LA32_STD_TYPE_3R(DIV_WU, rk, rj, rd)
#define ENCODE_LA32_MOD_W(rd, rj, rk)           ENCODE_LA32_STD_TYPE_3R(MOD_W, rk, rj, rd)
#define ENCODE_LA32_MOD_WU(rd, rj, rk)          ENCODE_LA32_STD_TYPE_3R(MOD_WU, rk, rj, rd)

#define ENCODE_LA32_SLL_W(rd, rj, rk)           ENCODE_LA32_STD_TYPE_3R(SLL_W, rk, rj, rd)
#define ENCODE_LA32_SRL_W(rd, rj, rk)           ENCODE_LA32_STD_TYPE_3R(SRL_W, rk, rj, rd)
#define ENCODE_LA32_SRA_W(rd, rj, rk)           ENCODE_LA32_STD_TYPE_3R(SRA_W, rk, rj, rd)

#define ENCODE_LA32_SLLI_W(rd, rj, ui5)         ENCODE_LA32_STD_TYPE_X_2RI5(SLLI_W, ui5, rj, rd)
#define ENCODE_LA32_SRLI_W(rd, rj, ui5)         ENCODE_LA32_STD_TYPE_X_2RI5(SRLI_W, ui5, rj, rd)
#define ENCODE_LA32_SRAI_W(rd, rj, ui5)         ENCODE_LA32_STD_TYPE_X_2RI5(SRAI_W, ui5, rj, rd)

#define ENCODE_LA32_BEQ(rj, rd, offs16)         ENCODE_LA32_STD_TYPE_2RI16(BEQ, offs16, rj, rd)
#define ENCODE_LA32_BNE(rj, rd, offs16)         ENCODE_LA32_STD_TYPE_2RI16(BNE, offs16, rj, rd)
#define ENCODE_LA32_BLT(rj, rd, offs16)         ENCODE_LA32_STD_TYPE_2RI16(BLT, offs16, rj, rd)
#define ENCODE_LA32_BGE(rj, rd, offs16)         ENCODE_LA32_STD_TYPE_2RI16(BGE, offs16, rj, rd)
#define ENCODE_LA32_BLTU(rj, rd, offs16)        ENCODE_LA32_STD_TYPE_2RI16(BLTU, offs16, rj, rd)
#define ENCODE_LA32_BGEU(rj, rd, offs16)        ENCODE_LA32_STD_TYPE_2RI16(BGEU, offs16, rj, rd)

#define ENCODE_LA32_B(offs26)                   ENCODE_LA32_STD_TYPE_I26(B, offs26)
#define ENCODE_LA32_BL(offs26)                  ENCODE_LA32_STD_TYPE_I26(BL, offs26)

#define ENCODE_LA32_JIRL(rd, rj, offs16)        ENCODE_LA32_STD_TYPE_2RI16(JIRL, offs16, rj, rd)

#define ENCODE_LA32_LD_B(rd, rj, si12)          ENCODE_LA32_STD_TYPE_2RI12(LD_B, si12, rj, rd)
#define ENCODE_LA32_LD_H(rd, rj, si12)          ENCODE_LA32_STD_TYPE_2RI12(LD_H, si12, rj, rd)
#define ENCODE_LA32_LD_W(rd, rj, si12)          ENCODE_LA32_STD_TYPE_2RI12(LD_W, si12, rj, rd)
#define ENCODE_LA32_LD_BU(rd, rj, si12)         ENCODE_LA32_STD_TYPE_2RI12(LD_BU, si12, rj, rd)
#define ENCODE_LA32_LD_HU(rd, rj, si12)         ENCODE_LA32_STD_TYPE_2RI12(LD_HU, si12, rj, rd)

#define ENCODE_LA32_ST_B(rd, rj, si12)          ENCODE_LA32_STD_TYPE_2RI12(ST_B, si12, rj, rd)
#define ENCODE_LA32_ST_H(rd, rj, si12)          ENCODE_LA32_STD_TYPE_2RI12(ST_H, si12, rj, rd)
#define ENCODE_LA32_ST_W(rd, rj, si12)          ENCODE_LA32_STD_TYPE_2RI12(ST_W, si12, rj, rd)


// Functionalized namespaced encoding macros
namespace Jasse::Encoder::LA32R_NSCSCC {
    
    inline constexpr insnraw_t ADD_W(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_ADD_W(rd, rj, rk);
    }

    inline constexpr insnraw_t SUB_W(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_SUB_W(rd, rj, rk);
    }

    inline constexpr insnraw_t ADDI_W(unsigned int rd, unsigned int rj, imm_t si12) noexcept
    {
        return ENCODE_LA32_ADDI_W(rd, rj, si12);
    }

    inline constexpr insnraw_t LU12I_W(unsigned int rd, imm_t si20) noexcept
    {
        return ENCODE_LA32_LU12I_W(rd, si20);
    }

    inline constexpr insnraw_t SLT(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_SLT(rd, rj, rk);
    }

    inline constexpr insnraw_t SLTU(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_SLTU(rd, rj, rk);
    }

    inline constexpr insnraw_t SLTI(unsigned int rd, unsigned int rj, imm_t si12) noexcept
    {
        return ENCODE_LA32_SLTI(rd, rj, si12);
    }

    inline constexpr insnraw_t SLTUI(unsigned int rd, unsigned int rj, imm_t si12) noexcept
    {
        return ENCODE_LA32_SLTUI(rd, rj, si12);
    }

    inline constexpr insnraw_t PCADDU12I(unsigned int rd, imm_t si20) noexcept
    {
        return ENCODE_LA32_PCADDU12I(rd, si20);
    }

    inline constexpr insnraw_t AND(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_AND(rd, rj, rk);
    }

    inline constexpr insnraw_t OR(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_OR(rd, rj, rk);
    }

    inline constexpr insnraw_t NOR(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_NOR(rd, rj, rk);
    }

    inline constexpr insnraw_t XOR(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_XOR(rd, rj, rk);
    }

    inline constexpr insnraw_t ANDI(unsigned int rd, unsigned int rj, imm_t si12) noexcept
    {
        return ENCODE_LA32_ANDI(rd, rj, si12);
    }

    inline constexpr insnraw_t ORI(unsigned int rd, unsigned int rj, imm_t si12) noexcept
    {
        return ENCODE_LA32_ORI(rd, rj, si12);
    }

    inline constexpr insnraw_t XORI(unsigned int rd, unsigned int rj, imm_t si12) noexcept
    {
        return ENCODE_LA32_XORI(rd, rj, si12);
    }

    inline constexpr insnraw_t MUL_W(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_MUL_W(rd, rj, rk);
    }

    inline constexpr insnraw_t MULH_W(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_MULH_W(rd, rj, rk);
    }

    inline constexpr insnraw_t MULH_WU(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_MULH_WU(rd, rj, rk);
    }

    inline constexpr insnraw_t DIV_W(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_DIV_W(rd, rj, rk);
    }

    inline constexpr insnraw_t DIV_WU(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_DIV_WU(rd, rj, rk);
    }

    inline constexpr insnraw_t MOD_W(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_MOD_W(rd, rj, rk);
    }

    inline constexpr insnraw_t MOD_WU(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_MOD_WU(rd, rj, rk);
    }

    inline constexpr insnraw_t SLL_W(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_SLL_W(rd, rj, rk);
    }

    inline constexpr insnraw_t SRL_W(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_SRL_W(rd, rj, rk);
    }

    inline constexpr insnraw_t SRA_W(unsigned int rd, unsigned int rj, unsigned int rk) noexcept
    {
        return ENCODE_LA32_SRA_W(rd, rj, rk);
    }

    inline constexpr insnraw_t SLLI_W(unsigned int rd, unsigned int rj, imm_t ui5) noexcept
    {
        return ENCODE_LA32_SLLI_W(rd, rj, ui5);
    }

    inline constexpr insnraw_t SRLI_W(unsigned int rd, unsigned int rj, imm_t ui5) noexcept
    {
        return ENCODE_LA32_SRLI_W(rd, rj, ui5);
    }

    inline constexpr insnraw_t SRAI_W(unsigned int rd, unsigned int rj, imm_t ui5) noexcept
    {
        return ENCODE_LA32_SRAI_W(rd, rj, ui5);
    }

    inline constexpr insnraw_t BEQ(unsigned int rj, unsigned int rd, imm_t offs16) noexcept
    {
        return ENCODE_LA32_BEQ(rj, rd, offs16);
    }

    inline constexpr insnraw_t BNE(unsigned int rj, unsigned int rd, imm_t offs16) noexcept
    {
        return ENCODE_LA32_BNE(rj, rd, offs16);
    }

    inline constexpr insnraw_t BLT(unsigned int rj, unsigned int rd, imm_t offs16) noexcept
    {
        return ENCODE_LA32_BLT(rj, rd, offs16);
    }

    inline constexpr insnraw_t BGE(unsigned int rj, unsigned int rd, imm_t offs16) noexcept
    {
        return ENCODE_LA32_BGE(rj, rd, offs16);
    }

    inline constexpr insnraw_t BLTU(unsigned int rj, unsigned int rd, imm_t offs16) noexcept
    {
        return ENCODE_LA32_BLTU(rj, rd, offs16);
    }

    inline constexpr insnraw_t BGEU(unsigned int rj, unsigned int rd, imm_t offs16) noexcept
    {
        return ENCODE_LA32_BGEU(rj, rd, offs16);
    }

    inline constexpr insnraw_t B(imm_t offs26) noexcept
    {
        return ENCODE_LA32_B(offs26);
    }

    inline constexpr insnraw_t BL(imm_t offs26) noexcept
    {
        return ENCODE_LA32_BL(offs26);
    }

    inline constexpr insnraw_t JIRL(unsigned int rd, unsigned int rj, imm_t offs16) noexcept
    {
        return ENCODE_LA32_JIRL(rd, rj, offs16);
    }

    inline constexpr insnraw_t LD_B(unsigned int rd, unsigned int rj, imm_t si12) noexcept
    {
        return ENCODE_LA32_LD_B(rd, rj, si12);
    }

    inline constexpr insnraw_t LD_H(unsigned int rd, unsigned int rj, imm_t si12) noexcept
    {
        return ENCODE_LA32_LD_H(rd, rj, si12);
    }

    inline constexpr insnraw_t LD_W(unsigned int rd, unsigned int rj, imm_t si12) noexcept
    {
        return ENCODE_LA32_LD_W(rd, rj, si12);
    }

    inline constexpr insnraw_t LD_BU(unsigned int rd, unsigned int rj, imm_t si12) noexcept
    {
        return ENCODE_LA32_LD_BU(rd, rj, si12);
    }

    inline constexpr insnraw_t LD_HU(unsigned int rd, unsigned int rj, imm_t si12) noexcept
    {
        return ENCODE_LA32_LD_HU(rd, rj, si12);
    }

    inline constexpr insnraw_t ST_B(unsigned int rd, unsigned int rj, imm_t si12) noexcept
    {
        return ENCODE_LA32_ST_B(rd, rj, si12);
    }

    inline constexpr insnraw_t ST_H(unsigned int rd, unsigned int rj, imm_t si12) noexcept
    {
        return ENCODE_LA32_ST_H(rd, rj, si12);
    }

    inline constexpr insnraw_t ST_W(unsigned int rd, unsigned int rj, imm_t si12) noexcept
    {
        return ENCODE_LA32_ST_W(rd, rj, si12);
    }
}
