#include "la32decode.hpp"
//
// LA32R (NSCSCC) ISA Emulator (Jasse)
//
// Instruction decoding infrastructure
//


// Implementation of: class LA32Instruction
namespace Jasse {
    /*
    insnraw_t               insn;

    const LA32Codepoint*    codepoint;
    */

    LA32Instruction::LA32Instruction(insnraw_t insn) noexcept
        : insn      (insn)
        , codepoint (nullptr)
    { }

    LA32Instruction::LA32Instruction(insnraw_t insn, const LA32Codepoint* codepoint) noexcept
        : insn      (insn)
        , codepoint (codepoint)
    { }

    LA32Instruction::LA32Instruction(const LA32Instruction& obj) noexcept
        : insn      (obj.insn)
        , codepoint (obj.codepoint)
    { }

    LA32Instruction::~LA32Instruction() noexcept
    { }

    insnraw_t LA32Instruction::GetRaw() const noexcept
    {
        return this->insn;
    }

    imm_t LA32Instruction::GetImm8() const noexcept
    {
        return GET_LA32_IMM8(this->insn);
    }

    imm_t LA32Instruction::GetImm12() const noexcept
    {
        return GET_LA32_IMM12(this->insn);
    }

    imm_t LA32Instruction::GetImm14() const noexcept
    {
        return GET_LA32_IMM14(this->insn);
    }

    imm_t LA32Instruction::GetImm16() const noexcept
    {
        return GET_LA32_IMM16(this->insn);
    }

    imm_t LA32Instruction::GetImm21() const noexcept
    {
        return GET_LA32_IMM21(this->insn);
    }

    imm_t LA32Instruction::GetImm26() const noexcept
    {
        return GET_LA32_IMM26(this->insn);
    }

    imm_t LA32Instruction::GetExImm20() const noexcept
    {
        return GET_LA32_X_IMM20(this->insn);
    }

    imm_t LA32Instruction::GetExImm5() const noexcept
    {
        return GET_LA32_X_IMM5(this->insn);
    }

    unsigned int LA32Instruction::GetOpcodeUpper6() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_U6);
    }

    unsigned int LA32Instruction::GetOpcodeLower2() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L2);
    }

    unsigned int LA32Instruction::GetOpcodeLower4() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L4);
    }

    unsigned int LA32Instruction::GetOpcodeLower8() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L8);
    }

    unsigned int LA32Instruction::GetOpcodeLower6() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L6);
    }

    unsigned int LA32Instruction::GetOpcodeLower11() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L11);
    }

    unsigned int LA32Instruction::GetOpcodeLower16() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L16);
    }

    unsigned int LA32Instruction::GetRD() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_RD);
    }

    unsigned int LA32Instruction::GetRJ() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_RJ);
    }

    unsigned int LA32Instruction::GetRK() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_RK);
    }

    unsigned int LA32Instruction::GetRA() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_RA);
    }

    bool LA32Instruction::IsDecoded() const noexcept
    {
        return this->codepoint != nullptr;
    }

    const LA32Codepoint* LA32Instruction::GetCodepoint() const noexcept
    {
        return this->codepoint;
    }

    std::string LA32Instruction::GetName() const noexcept
    {
        if (this->codepoint == nullptr)
            return std::string();

        return this->codepoint->GetName();
    }

    LA32CodepointType LA32Instruction::GetType() const noexcept
    {
        if (this->codepoint == nullptr)
            return LA32CodepointType(0);

        return this->codepoint->GetType();
    }

    const LA32Codepoint::Executor LA32Instruction::GetExecutor() const noexcept
    {
        if (this->codepoint == nullptr)
            return nullptr;

        return this->codepoint->GetExecutor();
    }

    const LA32Codepoint::Textualizer LA32Instruction::GetTextualizer() const noexcept
    {
        if (this->codepoint == nullptr)
            return nullptr;

        return this->codepoint->GetTextualizer();
    }

    std::optional<std::string> LA32Instruction::GetNameIfDecoded() const noexcept
    {
        if (this->codepoint == nullptr)
            return std::nullopt;

        return { this->codepoint->GetName() };
    }

    std::optional<LA32CodepointType> LA32Instruction::GetTypeIfDecoded() const noexcept
    {
        if (this->codepoint == nullptr)
            return std::nullopt;

        return { this->codepoint->GetType() };
    }

    std::optional<const LA32Codepoint::Executor> LA32Instruction::GetExecutorIfDecoded() const noexcept
    {
        if (this->codepoint == nullptr)
            return std::nullopt;

        return { this->codepoint->GetExecutor() };
    }

    std::optional<const LA32Codepoint::Textualizer> LA32Instruction::GetTextualizerIfDecoded() const noexcept
    {
        if (this->codepoint == nullptr)
            return std::nullopt;

        return { this->codepoint->GetTextualizer() };
    }

    void LA32Instruction::SetRaw(insnraw_t insn) noexcept
    {
        this->insn = insn;
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetImm8(imm_t imm) noexcept
    {
        SET_LA32_IMM8(this->insn, imm);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetImm12(imm_t imm) noexcept
    {
        SET_LA32_IMM12(this->insn, imm);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetImm14(imm_t imm) noexcept
    {
        SET_LA32_IMM14(this->insn, imm);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetImm16(imm_t imm) noexcept
    {
        SET_LA32_IMM16(this->insn, imm);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetImm21(imm_t imm) noexcept
    {
        SET_LA32_IMM21(this->insn, imm);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetImm26(imm_t imm) noexcept
    {
        SET_LA32_IMM26(this->insn, imm);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetExImm20(imm_t imm) noexcept
    {
        SET_LA32_X_IMM20(this->insn, imm);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetExImm5(imm_t imm) noexcept
    {
        SET_LA32_X_IMM5(this->insn, imm);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetOpcodeUpper6(unsigned int opcode_u6) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_U6, opcode_u6);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetOpcodeLower2(unsigned int opcode_l2) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L2, opcode_l2);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetOpcodeLower4(unsigned int opcode_l4) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L4, opcode_l4);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetOpcodeLower8(unsigned int opcode_l8) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L8, opcode_l8);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetOpcodeLower6(unsigned int opcode_l6) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L6, opcode_l6);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetOpcodeLower11(unsigned int opcode_l11) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L11, opcode_l11);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetOpcodeLower16(unsigned int opcode_l16) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L16, opcode_l16);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetRD(unsigned int rd) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_RD, rd);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetRJ(unsigned int rj) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_RJ, rj);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetRK(unsigned int rk) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_RK, rk);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetRA(unsigned int ra) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_RA, ra);
        SetCodepoint(nullptr);
    }

    void LA32Instruction::SetCodepoint(const LA32Codepoint* codepoint) noexcept
    {
        this->codepoint = codepoint;
    }

    std::string LA32Instruction::ToString() const noexcept
    {
        if (this->codepoint == nullptr)
            return std::string();

        if (this->codepoint->GetTextualizer() == nullptr)
            return std::string();

        return this->codepoint->GetTextualizer()(*this);
    }

    std::optional<std::string> LA32Instruction::ToStringIfDecoded() const noexcept
    {
        if (this->codepoint == nullptr)
            return std::nullopt;

        if (this->codepoint->GetTextualizer() == nullptr)
            return std::nullopt;

        return { this->codepoint->GetTextualizer()(*this) };
    }
}


// Implementation of: class LA32Decoder
namespace Jasse {
    /*
    const std::string   name;
    const std::string   name_canonical;
    */

    LA32Decoder::LA32Decoder(const char* name, const char* name_canonical) noexcept
        : name              (std::string(name))
        , name_canonical    (std::string(name_canonical))
    { }

    LA32Decoder::LA32Decoder(const std::string& name, const std::string& name_canonical) noexcept
        : name              (name)
        , name_canonical    (name_canonical)
    { }
    
    LA32Decoder::~LA32Decoder() noexcept
    { }

    const std::string& LA32Decoder::GetName() const noexcept
    {
        return this->name;
    }

    const std::string& LA32Decoder::GetCanonicalName() const noexcept
    {
        return this->name_canonical;
    }
}


// Implementation of: class LA32DecoderCollection
namespace Jasse {
    /*
    std::vector<const LA32Decoder*> decoders;
    */

    LA32DecoderCollection::LA32DecoderCollection() noexcept
        : decoders  ()
    { }

    LA32DecoderCollection::LA32DecoderCollection(std::initializer_list<const LA32Decoder*> decoders) noexcept
        : decoders  (decoders)
    { }

    LA32DecoderCollection::LA32DecoderCollection(const LA32DecoderCollection& obj) noexcept
        : decoders  (obj.decoders)
    { }

    LA32DecoderCollection::~LA32DecoderCollection()
    { }

    int LA32DecoderCollection::GetSize() const noexcept
    {
        return this->decoders.size();
    }

    void LA32DecoderCollection::Clear() noexcept
    {
        this->decoders.clear();
    }

    bool LA32DecoderCollection::Has(const char* name) const noexcept
    {
        for (auto decoder : this->decoders)
            if (decoder->GetName().compare(name) == 0)
                return true;

        return false;
    }

    bool LA32DecoderCollection::Has(const std::string& name) const noexcept
    {
        return Has(name.c_str());
    }

    bool LA32DecoderCollection::HasCanonical(const char* name_canonical) const noexcept
    {
        for (auto decoder : this->decoders)
            if (decoder->GetCanonicalName().compare(name_canonical) == 0)
                return true;

        return false;
    }

    bool LA32DecoderCollection::HasCanonical(const std::string& name_canonical) const noexcept
    {
        return HasCanonical(name_canonical.c_str());
    }

    bool LA32DecoderCollection::Add(const LA32Decoder* decoder) noexcept
    {
        for (auto exist_decoder : this->decoders)
            if (exist_decoder->GetName().compare(decoder->GetName()) == 0
            ||  exist_decoder->GetCanonicalName().compare(decoder->GetCanonicalName()) == 0)
                return false;

        this->decoders.push_back(decoder);

        return true;
    }

    void LA32DecoderCollection::AddAll(const LA32DecoderCollection& collection) noexcept
    {
        for (auto decoder : collection)
            Add(decoder);
    }

    bool LA32DecoderCollection::ForceAdd(const LA32Decoder* decoder) noexcept
    {
        for (auto iter = this->decoders.begin(); iter != this->decoders.end(); iter++)
            if ((*iter)->GetName().compare(decoder->GetName()) == 0
            ||  (*iter)->GetCanonicalName().compare(decoder->GetCanonicalName()) == 0)
            {
                *iter = decoder;
                return false;
            }

        this->decoders.push_back(decoder);

        return true;
    }

    void LA32DecoderCollection::ForceAddAll(const LA32DecoderCollection& collection) noexcept
    {
        for (auto decoder : collection)
            ForceAdd(decoder);
    }

    bool LA32DecoderCollection::Remove(const char* name) noexcept
    {
        for (auto iter = this->decoders.begin(); iter != this->decoders.end(); iter++)
            if ((*iter)->GetName().compare(name) == 0)
            {
                this->decoders.erase(iter);
                return true;
            }

        return false;
    }

    bool LA32DecoderCollection::Remove(const std::string& name) noexcept
    {
        return Remove(name.c_str());
    }

    bool LA32DecoderCollection::RemoveCanonical(const char* name_canonical) noexcept
    {
        for (auto iter = this->decoders.begin(); iter != this->decoders.end(); iter++)
            if ((*iter)->GetCanonicalName().compare(name_canonical) == 0)
            {
                this->decoders.erase(iter);
                return true;
            }

        return false;
    }

    bool LA32DecoderCollection::RemoveCanonical(const std::string& name_canonical) noexcept
    {
        return RemoveCanonical(name_canonical.c_str());
    }

    bool LA32DecoderCollection::Decode(LA32Instruction& insn) const noexcept
    {
        for (auto decoder : this->decoders)
            if (decoder->Decode(insn))
                return true;

        return false;
    }

    LA32DecoderIterator LA32DecoderCollection::begin() noexcept
    {
        return this->decoders.begin();
    }

    LA32DecoderConstIterator LA32DecoderCollection::begin() const noexcept
    {
        return this->decoders.begin();
    }

    LA32DecoderIterator LA32DecoderCollection::end() noexcept
    {
        return this->decoders.end();
    }

    LA32DecoderConstIterator LA32DecoderCollection::end() const noexcept
    {
        return this->decoders.end();
    }
}
