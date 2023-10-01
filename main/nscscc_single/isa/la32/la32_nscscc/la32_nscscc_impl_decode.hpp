#pragma once
//
// LA32R (NSCSCC) ISA Emulator (Jasse)
//
// LA32R-NSCSCC, decoding infrastructure implementations
//

#include "la32_nscscc_def_decode.hpp"


#define impldec_stub_U6L0(name, codepoint) \
    inline bool LA32R_DECODER_STUB_U6L0(name)(LA32Instruction& insn) noexcept { insn.SetCodepoint(&codepoint); return true; }

#define impldec_stub_U6L1(name, codepoint) \
    inline bool LA32R_DECODER_STUB_U6L1(name)(LA32Instruction& insn) noexcept { insn.SetCodepoint(&codepoint); return true; }

#define impldec_stub_U6L2(name, codepoint) \
    inline bool LA32R_DECODER_STUB_U6L2(name)(LA32Instruction& insn) noexcept { insn.SetCodepoint(&codepoint); return true; }

#define impldec_stub_U6L4(name, codepoint) \
    inline bool LA32R_DECODER_STUB_U6L4(name)(LA32Instruction& insn) noexcept { insn.SetCodepoint(&codepoint); return true; }

#define impldec_stub_U6L8(name, codepoint) \
    inline bool LA32R_DECODER_STUB_U6L8(name)(LA32Instruction& insn) noexcept { insn.SetCodepoint(&codepoint); return true; }

#define impldec_stub_U6L6(name, codepoint) \
    inline bool LA32R_DECODER_STUB_U6L6(name)(LA32Instruction& insn) noexcept { insn.SetCodepoint(&codepoint); return true; }

#define impldec_stub_U6L11(name, codepoint) \
    inline bool LA32R_DECODER_STUB_U6L11(name)(LA32Instruction& insn) noexcept { insn.SetCodepoint(&codepoint); return true; }

#define impldec_stub_U6L16(name, codepoint) \
    inline bool LA32R_DECODER_STUB_U6L16(name)(LA32Instruction& insn) noexcept { insn.SetCodepoint(&codepoint); return true; }


namespace Jasse::LA32R_NSCSCC {

    //
    impldec_stub_U6L11( ADD_W       , Codepoint::LA32R_NSCSCC::ADD_W    );
    impldec_stub_U6L11( SUB_W       , Codepoint::LA32R_NSCSCC::SUB_W    );

    impldec_stub_U6L4(  ADDI_W      , Codepoint::LA32R_NSCSCC::ADDI_W   );

    impldec_stub_U6L1(  LU12I_W     , Codepoint::LA32R_NSCSCC::LU12I_W  );

    impldec_stub_U6L11( SLT         , Codepoint::LA32R_NSCSCC::SLT     );
    impldec_stub_U6L11( SLTU        , Codepoint::LA32R_NSCSCC::SLTU    );

    impldec_stub_U6L4(  SLTI        , Codepoint::LA32R_NSCSCC::SLTI    );
    impldec_stub_U6L4(  SLTUI       , Codepoint::LA32R_NSCSCC::SLTUI   );

    impldec_stub_U6L1(  PCADDU12I   , Codepoint::LA32R_NSCSCC::PCADDU12I);

    impldec_stub_U6L11( AND         , Codepoint::LA32R_NSCSCC::AND     );
    impldec_stub_U6L11( OR          , Codepoint::LA32R_NSCSCC::OR      );
    impldec_stub_U6L11( NOR         , Codepoint::LA32R_NSCSCC::NOR     );
    impldec_stub_U6L11( XOR         , Codepoint::LA32R_NSCSCC::XOR     );

    impldec_stub_U6L4(  ANDI        , Codepoint::LA32R_NSCSCC::ANDI    );
    impldec_stub_U6L4(  ORI         , Codepoint::LA32R_NSCSCC::ORI     );
    impldec_stub_U6L4(  XORI        , Codepoint::LA32R_NSCSCC::XORI    );

    //
    impldec_stub_U6L11( MUL_W       , Codepoint::LA32R_NSCSCC::MUL_W   );
    impldec_stub_U6L11( MULH_W      , Codepoint::LA32R_NSCSCC::MULH_W  );
    impldec_stub_U6L11( MULH_WU     , Codepoint::LA32R_NSCSCC::MULH_WU );

    impldec_stub_U6L11( DIV_W       , Codepoint::LA32R_NSCSCC::DIV_W   );
    impldec_stub_U6L11( DIV_WU      , Codepoint::LA32R_NSCSCC::DIV_WU  );
    impldec_stub_U6L11( MOD_W       , Codepoint::LA32R_NSCSCC::MOD_W   );
    impldec_stub_U6L11( MOD_WU      , Codepoint::LA32R_NSCSCC::MOD_WU  );

    //
    impldec_stub_U6L11( SLL_W       , Codepoint::LA32R_NSCSCC::SLL_W   );
    impldec_stub_U6L11( SRL_W       , Codepoint::LA32R_NSCSCC::SRL_W   );
    impldec_stub_U6L11( SRA_W       , Codepoint::LA32R_NSCSCC::SRA_W   );

    impldec_stub_U6L11( SLLI_W      , Codepoint::LA32R_NSCSCC::SLLI_W  );
    impldec_stub_U6L11( SRLI_W      , Codepoint::LA32R_NSCSCC::SRLI_W  );
    impldec_stub_U6L11( SRAI_W      , Codepoint::LA32R_NSCSCC::SRAI_W  );

    //
    impldec_stub_U6L0(  BEQ         , Codepoint::LA32R_NSCSCC::BEQ     );
    impldec_stub_U6L0(  BNE         , Codepoint::LA32R_NSCSCC::BNE     );
    impldec_stub_U6L0(  BLT         , Codepoint::LA32R_NSCSCC::BLT     );
    impldec_stub_U6L0(  BGE         , Codepoint::LA32R_NSCSCC::BGE     );
    impldec_stub_U6L0(  BLTU        , Codepoint::LA32R_NSCSCC::BLTU    );
    impldec_stub_U6L0(  BGEU        , Codepoint::LA32R_NSCSCC::BGEU    );

    impldec_stub_U6L0(  B           , Codepoint::LA32R_NSCSCC::B       );
    impldec_stub_U6L0(  BL          , Codepoint::LA32R_NSCSCC::BL      );
    impldec_stub_U6L0(  JIRL        , Codepoint::LA32R_NSCSCC::JIRL    );

    //
    impldec_stub_U6L4(  LD_B        , Codepoint::LA32R_NSCSCC::LD_B    );
    impldec_stub_U6L4(  LD_H        , Codepoint::LA32R_NSCSCC::LD_H    );
    impldec_stub_U6L4(  LD_W        , Codepoint::LA32R_NSCSCC::LD_W    );
    impldec_stub_U6L4(  LD_BU       , Codepoint::LA32R_NSCSCC::LD_BU   );
    impldec_stub_U6L4(  LD_HU       , Codepoint::LA32R_NSCSCC::LD_HU   );

    impldec_stub_U6L4(  ST_B        , Codepoint::LA32R_NSCSCC::ST_B    );
    impldec_stub_U6L4(  ST_H        , Codepoint::LA32R_NSCSCC::ST_H    );
    impldec_stub_U6L4(  ST_W        , Codepoint::LA32R_NSCSCC::ST_W    );
}


namespace Jasse::LA32R_NSCSCC {

    template<unsigned int _IDepth, unsigned int _IOffset>
    class HuffmanNode : public LA32DecodeCapable {
    public:
        static constexpr unsigned int _IMask    = 0xFFFFFFFFU >> (32 - _IDepth);

    public:
        LA32DecodeCapable** next;

    public:
        HuffmanNode() noexcept;
        virtual ~HuffmanNode() noexcept;

        virtual bool    Decode(LA32Instruction& insn) const noexcept override;
    };

    template<unsigned int _IDepth, unsigned int _IOffset>
    inline HuffmanNode<_IDepth, _IOffset>::HuffmanNode() noexcept
        : next (new LA32DecodeCapable* [1U << _IDepth])
    {
        for (int i = 0; i < (1U << _IDepth); ++i)
            next[i] = nullptr;
    }

    template<unsigned int _IDepth, unsigned int _IOffset>
    inline HuffmanNode<_IDepth, _IOffset>::~HuffmanNode() noexcept
    {
        for (int i = 0; i < (1U << _IDepth); ++i)
            if (next[i] != nullptr)
                delete next[i];
        delete[] next;
    }

    template<unsigned int _IDepth, unsigned int _IOffset>
    inline bool HuffmanNode<_IDepth, _IOffset>::Decode(LA32Instruction& insn) const noexcept
    {
        LA32DecodeCapable* nextNode = next[(insn.GetRaw() >> _IOffset) & _IMask];

        if (nextNode != nullptr)
            return nextNode->Decode(insn);

        return false;
    }
}


// Implementation of LA32R-NSCSCC Decoder
namespace Jasse::LA32R_NSCSCC {

    #define cpmap_leaftype(name) name

    #define cpmap_leaf(dst, name, tag) \
        class cpmap_leaftype(name) : public LA32DecodeCapable { \
        public: \
            virtual bool Decode(LA32Instruction& insn) const noexcept override \
            { return LA32R_DECODER_STUB_##tag(name)(insn); } \
        }; \
        dst = new cpmap_leaftype(name);


    #define cpmap_U6L0(name) /* 6 */ \
        { \
            cpmap_leaf(tree[LA32_OPCODE_U6_##name], name, U6L0); \
        } \

    #define cpmap_U6L1(name) /* 6 -> 1 (Special form for U6L0) */ \
        { \
            HuffmanNode<1, 25>*& node = (HuffmanNode<1, 25>*&) tree[LA32_OPCODE_U6_##name]; \
            if (node == nullptr) \
                node = new HuffmanNode<1, 25>; \
            \
            cpmap_leaf(node->next[LA32_OPCODE_L1_##name], name, U6L1); \
        }

    #define cpmap_U6L2(name) /* 6 -> (2     ) */ \
        { \
            HuffmanNode<4, 22>*& node = (HuffmanNode<4, 22>*&) tree[LA32_OPCODE_U6_##name]; \
            if (node == nullptr) \
                node = new HuffmanNode<4, 22>; \
            \
            cpmap_leaf(node->next[(LA32_OPCODE_L2_##name << 2) | 0], name, U6L2); \
            cpmap_leaf(node->next[(LA32_OPCODE_L2_##name << 2) | 1], name, U6L2); \
            cpmap_leaf(node->next[(LA32_OPCODE_L2_##name << 2) | 2], name, U6L2); \
            cpmap_leaf(node->next[(LA32_OPCODE_L2_##name << 2) | 3], name, U6L2); \
        }

    #define cpmap_U6L4(name) /* 6 -> (2 -> 2) */ \
        { \
            HuffmanNode<4, 22>*& node = (HuffmanNode<4, 22>*&) tree[LA32_OPCODE_U6_##name]; \
            if (node == nullptr) \
                node = new HuffmanNode<4, 22>; \
            \
            cpmap_leaf(node->next[LA32_OPCODE_L4_##name], name, U6L4); \
        }

    #define cpmap_U6L6(name) /* 6 -> (2 -> 2) -> (2     ) */ \
        { \
            HuffmanNode<4, 22>*& node1 = (HuffmanNode<4, 22>*&) tree[LA32_OPCODE_U6_##name]; \
            if (node1 == nullptr) \
                node1 = new HuffmanNode<4, 22>; \
            \
            HuffmanNode<4, 18>*& node = (HuffmanNode<4, 18>*&) node1->next[LA32_OPCODE_L6_##name >> 2]; \
            if (node == nullptr) \
                node = new HuffmanNode<4, 18>; \
            \
            cpmap_leaf(node->next[((LA32_OPCODE_L6_##name << 2) & 0x0C) | 0], name, U6L6); \
            cpmap_leaf(node->next[((LA32_OPCODE_L6_##name << 2) & 0x0C) | 1], name, U6L6); \
            cpmap_leaf(node->next[((LA32_OPCODE_L6_##name << 2) & 0x0C) | 2], name, U6L6); \
            cpmap_leaf(node->next[((LA32_OPCODE_L6_##name << 2) & 0x0C) | 3], name, U6L6); \
        }

    #define cpmap_U6L8(name) /* 6 -> (2 -> 2) -> (2 -> 2) */ \
        { \
            HuffmanNode<4, 22>*& node1 = (HuffmanNode<4, 22>*&) tree[LA32_OPCODE_U6_##name]; \
            if (node1 == nullptr) \
                node1 = new HuffmanNode<4, 22>; \
            \
            HuffmanNode<4, 18>*& node = (HuffmanNode<4, 18>*&) node1->next[LA32_OPCODE_L8_##name >> 4]; \
            if (node == nullptr) \
                node = new HuffmanNode<4, 18>; \
            \
            cpmap_leaf(node->next[LA32_OPCODE_L8_##name & 0x0F], name, U6L8); \
        }

    #define cpmap_U6L11(name) /*6 -> (2 -> 2) -> (2 -> 2) -> 3 */ \
        { \
            HuffmanNode<4, 22>*& node1 = (HuffmanNode<4, 22>*&) tree[LA32_OPCODE_U6_##name]; \
            if (node1 == nullptr) \
                node1 = new HuffmanNode<4, 22>; \
            \
            HuffmanNode<4, 18>*& node2 = (HuffmanNode<4, 18>*&) node1->next[LA32_OPCODE_L11_##name >> 7]; \
            if (node2 == nullptr) \
                node2 = new HuffmanNode<4, 18>; \
            \
            HuffmanNode<3, 15>*& node = (HuffmanNode<3, 15>*&) node2->next[(LA32_OPCODE_L11_##name >> 3) & 0x0F]; \
            if (node == nullptr) \
                node = new HuffmanNode<3, 15>; \
            \
            cpmap_leaf(node->next[LA32_OPCODE_L11_##name & 0x07], name, U6L11); \
        }

    #define cpmap_U6L16(name) /*6 -> (2 -> 2) -> (2 -> 2) -> 3 -> 5*/ \
        { \
            HuffmanNode<4, 22>*& node1 = (HuffmanNode<4, 22>*&) tree[LA32_OPCODE_U6_##name]; \
            if (node1 == nullptr) \
                node1 = new HuffmanNode<4, 22>; \
            \
            HuffmanNode<4, 18>*& node2 = (HuffmanNode<4, 18>*&) node1->next[LA32_OPCODE_L16_##name >> 12]; \
            if (node2 == nullptr) \
                node2 = new HuffmanNode<4, 18>; \
            \
            HuffmanNode<3, 15>*& node3 = (HuffmanNode<3, 15>*&) node2->next[(LA32_OPCODE_L16_##name >> 8) & 0x0F]; \
            if (node3 == nullptr) \
                node3 = new HuffmanNode<3, 15>; \
            \
            HuffmanNode<5, 10>*& node = (HuffmanNode<5, 10>*&) node3->next[(LA32_OPCODE_L16_##name >> 5) & 0x07]; \
            if (node == nullptr) \
                node = new HuffmanNode<5, 10>; \
            \
            cpmap_leaf(node->next[LA32_OPCODE_L16_##name & 0x1F], name, U6L16); \
        }


    inline Decoder::Decoder() noexcept
        : LA32Decoder   ("LA32R-NSCSCC", "la32r")
        , tree          (new LA32DecodeCapable*[64])
    {
        for (int i = 0; i < 64; i = i + 1)
            tree[i] = nullptr;

        //
        cpmap_U6L11(  ADD_W     );
        cpmap_U6L11(  SUB_W     );

        cpmap_U6L4(   ADDI_W    );

        cpmap_U6L1(   LU12I_W   );

        cpmap_U6L11(  SLT       );
        cpmap_U6L11(  SLTU      );

        cpmap_U6L4(   SLTI      );
        cpmap_U6L4(   SLTUI     ); 

        cpmap_U6L1(   PCADDU12I );

        cpmap_U6L11(  AND       );
        cpmap_U6L11(  OR        );
        cpmap_U6L11(  NOR       );
        cpmap_U6L11(  XOR       );

        cpmap_U6L4(   ANDI      );
        cpmap_U6L4(   ORI       );
        cpmap_U6L4(   XORI      );

        //
        cpmap_U6L11(  MUL_W     );
        cpmap_U6L11(  MULH_W    );
        cpmap_U6L11(  MULH_WU   );

        cpmap_U6L11(  DIV_W     );
        cpmap_U6L11(  DIV_WU    );
        cpmap_U6L11(  MOD_W     );
        cpmap_U6L11(  MOD_WU    );

        //
        cpmap_U6L11(  SLL_W     );
        cpmap_U6L11(  SRL_W     );
        cpmap_U6L11(  SRA_W     );

        cpmap_U6L11(  SLLI_W    );
        cpmap_U6L11(  SRLI_W    );
        cpmap_U6L11(  SRAI_W    );

        //
        cpmap_U6L0(   BEQ       );
        cpmap_U6L0(   BNE       );
        cpmap_U6L0(   BLT       );
        cpmap_U6L0(   BGE       );
        cpmap_U6L0(   BLTU      );
        cpmap_U6L0(   BGEU      );

        cpmap_U6L0(   B         );
        cpmap_U6L0(   BL        );
        cpmap_U6L0(   JIRL      );

        //
        cpmap_U6L4(   LD_B      );
        cpmap_U6L4(   LD_H      );
        cpmap_U6L4(   LD_W      );
        cpmap_U6L4(   LD_BU     );
        cpmap_U6L4(   LD_HU     );

        cpmap_U6L4(   ST_B      );
        cpmap_U6L4(   ST_H      );
        cpmap_U6L4(   ST_W      );
    }

    inline Decoder::~Decoder() noexcept
    { 
        for (int i = 0; i < 64; ++i)
            if (tree[i] != nullptr)
                delete tree[i];
        delete[] tree;
    }

    inline bool Decoder::Decode(LA32Instruction& insn) const noexcept
    {
        LA32DecodeCapable* nextNode = tree[GET_LA32_STD_OPERAND(insn.GetRaw(), LA32_OPCODE_U6)];

        if (nextNode != nullptr)
            return nextNode->Decode(insn);

        return false;
    }


    #undef cpmap_leaftype
    #undef cpmap_leaf

    #undef cpmap_U6L0
    #undef cpmap_U6L1
    #undef cpmap_U6L2
    #undef cpmap_U6L4
    #undef cpmap_U6L6
    #undef cpmap_U6L8
    #undef cpmap_U6L11
    #undef cpmap_U6L16
}


#undef impldec_stub_U6L0
#undef impldec_stub_U6L1
#undef impldec_stub_U6L2
#undef impldec_stub_U6L4
#undef impldec_stub_U6L8
#undef impldec_stub_U6L6
#undef impldec_stub_U6L11
#undef impldec_stub_U6L16
