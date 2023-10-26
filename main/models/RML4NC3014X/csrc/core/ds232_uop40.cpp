#include "ds232_uop40.hpp"

#include <functional>


#include AUTOINC_BE_JASSE2_LA32(la32_nscscc.hpp)


// Implementation of: class uop40::imm26_t
namespace BullsEye::Draconids3014::uop40 {
    /*
    uint26_t    value;
    */

    imm26_t::imm26_t() noexcept
        : value ()
    { }

    imm26_t::imm26_t(uint26_t value) noexcept
        : value (value)
    { }

    imm26_t::imm26_t(uint26_t::value_type value) noexcept
        : value (value)
    { }

    uint26_t imm26_t::Get() const noexcept
    {
        return value;
    }

    void imm26_t::Set(uint26_t value) noexcept
    {
        this->value = value;
    }

    uint5_t imm26_t::GetRK() const noexcept
    {
        return uint5_t(value);
    }

    void imm26_t::SetRK(uint5_t rk) noexcept
    {
        value = (value & ~0x0000001F) | (uint32_t(rk));
    }

    uint5_t imm26_t::GetRA() const noexcept
    {
        return uint5_t(value >> 5);
    }

    void imm26_t::SetRA(uint5_t ra) noexcept
    {
        value = (value & ~0x000003E0) | (uint32_t(ra) << 5);
    }

    uint5_t imm26_t::GetRD() const noexcept
    {
        return uint5_t(value >> 16);
    }

    void imm26_t::SetRD(uint5_t rd) noexcept
    {
        value = (value & ~0x001F0000) | (uint32_t(rd) << 16);
    }

    uint5_t imm26_t::GetRJ() const noexcept
    {
        return uint5_t(value >> 21);
    }

    void imm26_t::SetRJ(uint5_t rj) noexcept
    {
        value = (value & ~0x03E00000) | (uint32_t(rj) << 21);
    }

    uint20_t imm26_t::AsI20() const noexcept
    {
        return uint20_t((value << 5) | GetRJ());
    }

    imm26_t& imm26_t::operator=(uint26_t value) noexcept
    {
        this->value = value;
        return *this;
    }

    imm26_t::operator uint26_t() const noexcept
    {
        return value;
    }

    imm26_t::operator uint26_t&() noexcept
    {
        return value;
    }
}


// Implementation of: ReverseUOP40_OC3_LA32R
namespace BullsEye::Draconids3014 {

    std::optional<Jasse::insnraw_t> ReverseUOP40_OC3_LA32R(uop40_t uop) noexcept
    {
        static std::function<std::optional<Jasse::insnraw_t>(uop40_t)> rev_waystone[] = {
            // 0x00 CACHE
            [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                return std::nullopt;
            },

            // 0x01 ALU
            [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                static std::function<std::optional<Jasse::insnraw_t>(uop40_t)> rev_cmd[] = {
                    // 0x00 ADD
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        if (uop.imm2 == uop40::imm2::alu::I0_UI5)
                            return { ENCODE_LA32_ADD_W(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                        else if (uop.imm2 == uop40::imm2::alu::SI12)
                            return { ENCODE_LA32_ADDI_W(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                        return std::nullopt;
                    },

                    // 0x01 SUB
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_SUB_W(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                    },

                    // 0x02 LU12I
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_LU12I_W(uop.imm26.GetRD(), uop.imm26.AsI20() ) };
                    },

                    // 0x03 SLT
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        if (uop.imm2 == uop40::imm2::alu::I0_UI5)
                            return { ENCODE_LA32_SLT(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                        else if (uop.imm2 == uop40::imm2::alu::SI12)
                            return { ENCODE_LA32_SLTI(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                        return std::nullopt;
                    },

                    // 0x04 SLTU
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        if (uop.imm2 == uop40::imm2::alu::I0_UI5)
                            return { ENCODE_LA32_SLTU(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                        else if (uop.imm2 == uop40::imm2::alu::SI12)
                            return { ENCODE_LA32_SLTUI(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                        return std::nullopt;
                    },

                    // 0x05 PCADDU12I
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_PCADDU12I(uop.imm26.GetRD(), uop.imm26.AsI20()) };
                    },

                    // 0x06 AND
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        if (uop.imm2 == uop40::imm2::alu::I0_UI5)
                            return { ENCODE_LA32_AND(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                        else if (uop.imm2 == uop40::imm2::alu::UI12)
                            return { ENCODE_LA32_ANDI(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                        return std::nullopt;
                    },

                    // 0x07 OR
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        if (uop.imm2 == uop40::imm2::alu::I0_UI5)
                            return { ENCODE_LA32_OR(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                        else if (uop.imm2 == uop40::imm2::alu::UI12)
                            return { ENCODE_LA32_ORI(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                        return std::nullopt;
                    },

                    // 0x08 NOR
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_NOR(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                    },

                    // 0x09 XOR
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        if (uop.imm2 == uop40::imm2::alu::I0_UI5)
                            return { ENCODE_LA32_XOR(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                        else if (uop.imm2 == uop40::imm2::alu::UI12)
                            return { ENCODE_LA32_XORI(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                        return std::nullopt;
                    },

                    // 0x0A SLL
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_SLL_W(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                    },

                    // 0x0B SRL
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_SRL_W(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                    },

                    // 0x0C SRA
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_SRA_W(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                    },

                    // 0x0D SLLI
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_SLLI_W(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                    },

                    // 0x0E SRLI
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_SRLI_W(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                    },

                    // 0x0F SRAI
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_SRAI_W(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                    }
                };

                return rev_cmd[uop.cmd](uop);
            },

            // 0x02 BRANCH
            [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                static std::function<std::optional<Jasse::insnraw_t>(uop40_t)> rev_cmd[] = {
                    // 0x00 BEQ
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_BEQ(uop.imm26.GetRJ(), uop.imm26.GetRD(), uop.imm26.Get()) };
                    },

                    // 0x01 BNE
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_BNE(uop.imm26.GetRJ(), uop.imm26.GetRD(), uop.imm26.Get()) };
                    },

                    // 0x02 BLT
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_BLT(uop.imm26.GetRJ(), uop.imm26.GetRD(), uop.imm26.Get()) };
                    },

                    // 0x03 BLTU
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_BLTU(uop.imm26.GetRJ(), uop.imm26.GetRD(), uop.imm26.Get()) };
                    },

                    // 0x04 BGE
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_BGE(uop.imm26.GetRJ(), uop.imm26.GetRD(), uop.imm26.Get()) };
                    },

                    // 0x05 BGEU
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_BGEU(uop.imm26.GetRJ(), uop.imm26.GetRD(), uop.imm26.Get()) };
                    },

                    // 0x06 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x07 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x08 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x09 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0A --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0B --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0C --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0D --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0E --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0F --
                    [](uop40_t uop) { return std::nullopt; }
                };

                return rev_cmd[uop.cmd](uop);
            },

            // 0x03 MUL
            [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                static std::function<std::optional<Jasse::insnraw_t>(uop40_t)> rev_cmd[] = {
                    // 0x00 MUL
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_MUL_W(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                    },

                    // 0x01 MULH
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_MULH_W(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                    },

                    // 0x02 MULHU
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_MULH_WU(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                    },

                    // 0x03 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x04 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x05 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x06 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x07 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x08 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x09
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0A
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0B
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0C
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0D
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0E
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0F
                    [](uop40_t uop) { return std::nullopt; }
                };

                return rev_cmd[uop.cmd](uop);
            },

            // 0x04 DIV
            [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                static std::function<std::optional<Jasse::insnraw_t>(uop40_t)> rev_cmd[] = {
                    // 0x00 DIV
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_DIV_W(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                    },

                    // 0x01 DIVU
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_DIV_WU(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                    },

                    // 0x02 MOD
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_MOD_W(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                    },

                    // 0x03 MODU
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_MOD_WU(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.GetRK()) };
                    },

                    // 0x04 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x05 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x06 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x07 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x08 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x09 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0A --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0B --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0C --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0D --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0E --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0F --
                    [](uop40_t uop) { return std::nullopt; }
                };

                return rev_cmd[uop.cmd](uop);
            },

            // 0x05 MEM
            [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                static std::function<std::optional<Jasse::insnraw_t>(uop40_t)> rev_cmd[] = {
                    // 0x00 LD_B
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_LD_B(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                    },

                    // 0x01 LD_H
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_LD_H(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                    },

                    // 0x02 LD_W
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_LD_W(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                    },

                    // 0x03 LD_BU
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_LD_BU(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                    },

                    // 0x04 LD_HU
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_LD_HU(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                    },

                    // 0x05 ST_B
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_ST_B(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                    },

                    // 0x06 ST_H
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_ST_H(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                    },

                    // 0x07 ST_W
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_ST_W(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                    },

                    // 0x08 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x09 -- 
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0A --
                    [](uop40_t uop) { return std::nullopt; },
                    
                    // 0x0B --
                    [](uop40_t uop) { return std::nullopt; },
                    
                    // 0x0C --
                    [](uop40_t uop) { return std::nullopt; },
                    
                    // 0x0D --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0E --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0F --
                    [](uop40_t uop) { return std::nullopt; }
                };

                return rev_cmd[uop.cmd](uop);
            },

            // 0x06 PLACEHOLDER
            [](uop40_t uop) { return std::nullopt; },

            // 0x07 UNKNOWN
            [](uop40_t uop) { return std::nullopt; },

            // 0x08 --
            [](uop40_t uop) { return std::nullopt; },

            // 0x09 --
            [](uop40_t uop) { return std::nullopt; },

            // 0x0A JUMP
            [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                static std::function<std::optional<Jasse::insnraw_t>(uop40_t)> rev_cmd[] = {
                    // 0x00 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x01 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x02 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x03 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x04 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x05 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x06 B
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_B(uop.imm26.Get()) };
                    },

                    // 0x07 BL
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_BL(uop.imm26.Get()) };
                    },

                    // 0x08 JIRL
                    [](uop40_t uop) noexcept -> std::optional<Jasse::insnraw_t> {
                        return { ENCODE_LA32_JIRL(uop.imm26.GetRD(), uop.imm26.GetRJ(), uop.imm26.Get()) };
                    },

                    // 0x09 --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0A --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0B --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0C --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0D --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0E --
                    [](uop40_t uop) { return std::nullopt; },

                    // 0x0F --
                    [](uop40_t uop) { return std::nullopt; }
                };

                return rev_cmd[uop.cmd](uop);
            },

            // 0x0B --
            [](uop40_t uop) { return std::nullopt; },

            // 0x0C --
            [](uop40_t uop) { return std::nullopt; },

            // 0x0D --
            [](uop40_t uop) { return std::nullopt; },

            // 0x0E --
            [](uop40_t uop) { return std::nullopt; },

            // 0x0F --
            [](uop40_t uop) { return std::nullopt; }
        };

        return rev_waystone[uop.waystone](uop);
    }
}
