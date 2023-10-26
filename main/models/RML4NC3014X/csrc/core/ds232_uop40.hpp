#pragma once

#ifndef __HEADER_DS232__CORE_UOP40
#define __HEADER_DS232__CORE_UOP40

#include <optional>


#include "autoinclude.h"

#include AUTOINC_BE_COMMON(nonstdint.hpp)

#include AUTOINC_BE_JASSE2_LA32(la32.hpp)


namespace BullsEye::Draconids3014 {

    // uOP-40 field types
    namespace uop40 {
    //  typedef uint26_t    imm26_t;
        typedef uint2_t     regctrl_w_t;
        typedef uint2_t     regctrl_r_t;
        typedef uint4_t     waystone_t;
        typedef uint2_t     imm2_t;
        typedef uint4_t     cmd_t;

        class imm26_t {
        private:
            uint26_t    value;

        public:
            imm26_t() noexcept;
            imm26_t(uint26_t value) noexcept;
            imm26_t(uint26_t::value_type value) noexcept;

            uint26_t    Get() const noexcept;
            void        Set(uint26_t value) noexcept;

            uint5_t     GetRK() const noexcept;
            void        SetRK(uint5_t rk) noexcept;

            uint5_t     GetRA() const noexcept;
            void        SetRA(uint5_t ra) noexcept;

            uint5_t     GetRD() const noexcept;
            void        SetRD(uint5_t rd) noexcept;

            uint5_t     GetRJ() const noexcept;
            void        SetRJ(uint5_t rj) noexcept;

            uint20_t    AsI20() const noexcept;

            imm26_t&    operator=(uint26_t value) noexcept;

            operator    uint26_t() const noexcept;
            operator    uint26_t&() noexcept;
        };
    }

    // uOP-40 type
    struct uop40_t {
        uop40::imm26_t      imm26;
        uop40::regctrl_w_t  regctrl_w;
        uop40::regctrl_r_t  regctrl_r;
        uop40::waystone_t   waystone;
        uop40::imm2_t       imm2;
        uop40::cmd_t        cmd;
    };

    
    // uOP-40 definitions
    namespace uop40 {

        // uOP-40 waystone definitions
        namespace waystone {
            static constexpr waystone_t         CACHE       = 0x00;

            static constexpr waystone_t         ALU         = 0x01;
        //  static constexpr waystone_t         BRU         = 0x02;
            static constexpr waystone_t         MUL         = 0x03;
            static constexpr waystone_t         DIV         = 0x04;

            static constexpr waystone_t         MEM         = 0x05;

            static constexpr waystone_t         BRANCH      = 0x02;
            static constexpr waystone_t         JUMP        = 0x0A;

            static constexpr waystone_t         PLACEHOLDER = 0x06;

            static constexpr waystone_t         UNKNOWN     = 0x07;
        }

        // uOP-40 regctrl definitions
        namespace regctrl {
            static constexpr regctrl_r_t        R_NONE      = 0x00;
            static constexpr regctrl_r_t        R_RJ_RK     = 0x01;
            static constexpr regctrl_r_t        R_RJ        = 0x02;
            static constexpr regctrl_r_t        R_RJ_RD     = 0x03;

            static constexpr regctrl_w_t        W_NONE      = 0x00;
            static constexpr regctrl_w_t        W_RD        = 0x01;
            static constexpr regctrl_w_t        W_R1        = 0x02;
        }

        // uOP-40 command definitions
        namespace cmd {

            // uOP-40 command definitions for ALU
            namespace alu {
                static constexpr cmd_t          ADD         = 0x00;
                static constexpr cmd_t          SUB         = 0x01;

                static constexpr cmd_t          LU12I       = 0x02;

                static constexpr cmd_t          SLT         = 0x03;
                static constexpr cmd_t          SLTU        = 0x04;

                static constexpr cmd_t          PCADDU12I   = 0x05;

                static constexpr cmd_t          AND         = 0x06;
                static constexpr cmd_t          OR          = 0x07;
                static constexpr cmd_t          NOR         = 0x08;
                static constexpr cmd_t          XOR         = 0x09;

                static constexpr cmd_t          SLL         = 0x0A;
                static constexpr cmd_t          SRL         = 0x0B;
                static constexpr cmd_t          SRA         = 0x0C;

                static constexpr cmd_t          SLLI        = 0x0D;
                static constexpr cmd_t          SRLI        = 0x0E;
                static constexpr cmd_t          SRAI        = 0x0F;
            }

            // uOP-40 command definitions for BRU
            namespace bru {
                static constexpr cmd_t          BEQ         = 0x00;
                static constexpr cmd_t          BNE         = 0x01;
                static constexpr cmd_t          BLT         = 0x02;
                static constexpr cmd_t          BLTU        = 0x03;
                static constexpr cmd_t          BGE         = 0x04;
                static constexpr cmd_t          BGEU        = 0x05;
                static constexpr cmd_t          B           = 0x06;
                static constexpr cmd_t          BL          = 0x07;
                static constexpr cmd_t          JIRL        = 0x08;
            }

            // uOP-40 command definitions for CACHE
            namespace cache {
                static constexpr cmd_t          DBAR        = 0x00;
                static constexpr cmd_t          IBAR        = 0x01;
            }

            // uOP-40 command definitions for MUL
            namespace mul {
                static constexpr cmd_t          MUL         = 0x00;
                static constexpr cmd_t          MULH        = 0x01;
                static constexpr cmd_t          MULHU       = 0x02;
            }

            // uOP-40 command definitions for DIV
            namespace div {
                static constexpr cmd_t          DIV         = 0x00;
                static constexpr cmd_t          DIVU        = 0x01;
                static constexpr cmd_t          MOD         = 0x02;
                static constexpr cmd_t          MODU        = 0x03;
            }

            // uOP-40 comman definitions for MEM
            namespace mem {
                static constexpr cmd_t          LD_B        = 0x00;
                static constexpr cmd_t          LD_H        = 0x01;
                static constexpr cmd_t          LD_W        = 0x02;
                static constexpr cmd_t          LD_BU       = 0x03;
                static constexpr cmd_t          LD_HU       = 0x04;

                static constexpr cmd_t          ST_B        = 0x05;
                static constexpr cmd_t          ST_H        = 0x06;
                static constexpr cmd_t          ST_W        = 0x07;
            }
        }

        // uOP-40 imm2 definitions
        namespace imm2 {

            // uOP-40 imm2 definitions for ALU
            namespace alu {
                static constexpr imm2_t         SI12        = 0x00;
                static constexpr imm2_t         UI12        = 0x01;
                static constexpr imm2_t         SI20        = 0x02;
                static constexpr imm2_t         I0_UI5      = 0x03;
            }

            // uOP-40 imm2 definitions for BRU
            namespace bru {
                static constexpr imm2_t         OFFS16      = 0x00;
                static constexpr imm2_t         OFFS26      = 0x01;
            }

            // uOP-40 imm2 definitions for CACHE
            namespace cache {
                static constexpr imm2_t         I0          = 0x00;
            }

            // uOP-40 imm2 definitions for MUL
            namespace mul {
                static constexpr imm2_t         I0          = 0x00;
            }

            // uOP-40 imm2 definitions for DIV
            namespace div {
                static constexpr imm2_t         I0          = 0x00;
            }

            // uOP-40 imm2 definitions for MEM
            namespace mem {
                static constexpr imm2_t         SI12        = 0x00;
            }
        }
    }


    // Reverse uOP-40 code to LA32R code by specification Off-Core(3)
    std::optional<Jasse::insnraw_t> ReverseUOP40_OC3_LA32R(uop40_t uop) noexcept;
}


#endif
