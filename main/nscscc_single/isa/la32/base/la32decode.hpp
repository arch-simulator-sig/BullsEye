#pragma once
//
// LA32R (NSCSCC) ISA Emulator (Jasse)
//
// Instruction decoding infrastructure
//

#include <list>
#include <string>
#include <initializer_list>
#include <optional>

#include "la32def.hpp"
#include "la32code.hpp"


namespace Jasse {

    // LA32 Instruction
    class LA32Instruction {
    private:
        insnraw_t               insn;

        const LA32Codepoint*    codepoint;

    public:
        LA32Instruction(insnraw_t insn = 0) noexcept;
        LA32Instruction(insnraw_t insn, const LA32Codepoint* codepoint) noexcept;
        LA32Instruction(const LA32Instruction& obj) noexcept;
        ~LA32Instruction() noexcept;

        insnraw_t               GetRaw() const noexcept;
        imm_t                   GetImm8() const noexcept;
        imm_t                   GetImm12() const noexcept;
        imm_t                   GetImm14() const noexcept;
        imm_t                   GetImm16() const noexcept;
        imm_t                   GetImm21() const noexcept;
        imm_t                   GetImm26() const noexcept;
        imm_t                   GetExImm20() const noexcept;
        imm_t                   GetExImm5() const noexcept;
        unsigned int            GetOpcodeUpper6() const noexcept;
        unsigned int            GetOpcodeLower2() const noexcept;
        unsigned int            GetOpcodeLower4() const noexcept;
        unsigned int            GetOpcodeLower8() const noexcept;
        unsigned int            GetOpcodeLower6() const noexcept; 
        unsigned int            GetOpcodeLower11() const noexcept;
        unsigned int            GetOpcodeLower16() const noexcept;
        unsigned int            GetRD() const noexcept;
        unsigned int            GetRJ() const noexcept;
        unsigned int            GetRK() const noexcept;
        unsigned int            GetRA() const noexcept;

        bool                    IsDecoded() const noexcept;
        const LA32Codepoint*    GetCodepoint() const noexcept;

        std::string                                     GetName() const noexcept;
        LA32CodepointType                               GetType() const noexcept;
        const LA32Codepoint::Executor                   GetExecutor() const noexcept;
        const LA32Codepoint::Textualizer                GetTextualizer() const noexcept;

        std::optional<std::string>                      GetNameIfDecoded() const noexcept;
        std::optional<LA32CodepointType>                GetTypeIfDecoded() const noexcept;
        std::optional<const LA32Codepoint::Executor>    GetExecutorIfDecoded() const noexcept;
        std::optional<const LA32Codepoint::Textualizer> GetTextualizerIfDecoded() const noexcept;

        // *NOTICE: Modifying instruction would reset decoded codepoint result.

        void                    SetRaw(insnraw_t insn) noexcept;
        void                    SetImm8(imm_t imm) noexcept;
        void                    SetImm12(imm_t imm) noexcept;
        void                    SetImm14(imm_t imm) noexcept;
        void                    SetImm16(imm_t imm) noexcept;
        void                    SetImm21(imm_t imm) noexcept;
        void                    SetImm26(imm_t imm) noexcept;
        void                    SetExImm20(imm_t imm) noexcept;
        void                    SetExImm5(imm_t imm) noexcept;
        void                    SetOpcodeUpper6(unsigned int opcode_u6) noexcept;
        void                    SetOpcodeLower2(unsigned int opcode_l2) noexcept;
        void                    SetOpcodeLower4(unsigned int opcode_l4) noexcept;
        void                    SetOpcodeLower8(unsigned int opcode_l8) noexcept;
        void                    SetOpcodeLower6(unsigned int opcode_l6) noexcept;
        void                    SetOpcodeLower11(unsigned int opcode_l11) noexcept;
        void                    SetOpcodeLower16(unsigned int opcode_l16) noexcept;
        void                    SetRD(unsigned int rd) noexcept;
        void                    SetRJ(unsigned int rj) noexcept;
        void                    SetRK(unsigned int rk) noexcept;
        void                    SetRA(unsigned int ra) noexcept;

        void                    SetCodepoint(const LA32Codepoint* codepoint) noexcept;

        //

        std::string                 ToString() const noexcept;
        std::optional<std::string>  ToStringIfDecoded() const noexcept;
    };


    // LA32 Instruction Decoder Interface
    class LA32DecodeCapable {
    public:
        virtual ~LA32DecodeCapable() noexcept {};

        virtual bool            Decode(LA32Instruction& insn) const noexcept = 0;
    };

    // LA32 Instruction Decoder
    class LA32Decoder : public LA32DecodeCapable {
    private:
        // *NOTICE: The name and canonical name is the only identifier of a decoder.
        //          The name indicates the description and source module/author/version of a decoder.
        //          The canonical name indicates the standard/extension name or the official 
        //          name/abbreviation of a decoder.

        const std::string   name;
        const std::string   name_canonical;

    public:
        LA32Decoder(const char* name, const char* name_canonical) noexcept;
        LA32Decoder(const std::string& name, const std::string& name_canonical) noexcept;
        ~LA32Decoder() noexcept;

        const std::string&      GetName() const noexcept;
        const std::string&      GetCanonicalName() const noexcept;

        virtual bool            Decode(LA32Instruction& insn) const noexcept override = 0;

        void                    operator=(const LA32Decoder& obj) = delete;
    };


    // LA32 Instruction Decoder Collection Iterator
    using LA32DecoderIterator       = std::vector<const LA32Decoder*>::iterator;
    using LA32DecoderConstIterator  = std::vector<const LA32Decoder*>::const_iterator;

    // LA32 Instruction Decoder Collection
    class LA32DecoderCollection : public LA32DecodeCapable {
    private:
        // *NOTICE: "LA32Decoder" are stored as constant pointers in the collection.
        //          This means that any modification of any copy of LA32Decoder instance would not 
        //          take effect in this collection.
        //          This is based on the principle that any LA32Decoder instance should have its own
        //          static constant instance. And any global modification of LA32Decoder definition
        std::vector<const LA32Decoder*> decoders;

    public:
        LA32DecoderCollection() noexcept;
        LA32DecoderCollection(std::initializer_list<const LA32Decoder*> decoders) noexcept;
        LA32DecoderCollection(const LA32DecoderCollection& obj) noexcept;
        ~LA32DecoderCollection();

        int                         GetSize() const noexcept;
        void                        Clear() noexcept;

        bool                        Has(const std::string& name) const noexcept;
        bool                        Has(const char* name) const noexcept;
        bool                        HasCanonical(const std::string& name_canonical) const noexcept;
        bool                        HasCanonical(const char* name_canonical) const noexcept;

        // *NOTICE: Modifications on decoder collection are designed to be time-costing, so it's
        //          not recommended to modify decoder collections frequently.
        //          Modification operations should mostly be done on initialization stage of your
        //          application.

        // *NOTICE: On adding decoders, the container would check if exsiting decoders with identical
        //          names or identical canonical names exists.
        //          Any decoders with identical names or identical canonical names must be taken extra
        //          attention:
        //          (*1) By calling ::Add(...) or ::AddAll(...), decoders wouldn't be added into the
        //               collection when name or canonical name conflicts.
        //          (*2) By calling ::ForceAdd(...) or ::ForceAddAll(...), the old decoders would be
        //               replaced by the new decoders when name or canonical name conflicts.

        bool                        Add(const LA32Decoder* decoder) noexcept;
        void                        AddAll(const LA32DecoderCollection& collection) noexcept;

        bool                        ForceAdd(const LA32Decoder* decoder) noexcept;
        void                        ForceAddAll(const LA32DecoderCollection& collection) noexcept;

        bool                        Remove(const std::string& name) noexcept;
        bool                        Remove(const char* name) noexcept;
        bool                        RemoveCanonical(const std::string& name_canonical) noexcept;
        bool                        RemoveCanonical(const char* name_canonical) noexcept;

        //
        bool                        Decode(LA32Instruction& insn) const noexcept override;

        // Declarations for C++ specified foreach expression

        LA32DecoderIterator         begin() noexcept;
        LA32DecoderConstIterator    begin() const noexcept;
        LA32DecoderIterator         end() noexcept;
        LA32DecoderConstIterator    end() const noexcept;
    };
}


// Implementation of: class LA32Instruction
namespace Jasse {
    /*
    insnraw_t               insn;

    const LA32Codepoint*    codepoint;
    */

    inline LA32Instruction::LA32Instruction(insnraw_t insn) noexcept
        : insn      (insn)
        , codepoint (nullptr)
    { }

    inline LA32Instruction::LA32Instruction(insnraw_t insn, const LA32Codepoint* codepoint) noexcept
        : insn      (insn)
        , codepoint (codepoint)
    { }

    inline LA32Instruction::LA32Instruction(const LA32Instruction& obj) noexcept
        : insn      (obj.insn)
        , codepoint (obj.codepoint)
    { }

    inline LA32Instruction::~LA32Instruction() noexcept
    { }

    inline insnraw_t LA32Instruction::GetRaw() const noexcept
    {
        return this->insn;
    }

    inline imm_t LA32Instruction::GetImm8() const noexcept
    {
        return GET_LA32_IMM8(this->insn);
    }

    inline imm_t LA32Instruction::GetImm12() const noexcept
    {
        return GET_LA32_IMM12(this->insn);
    }

    inline imm_t LA32Instruction::GetImm14() const noexcept
    {
        return GET_LA32_IMM14(this->insn);
    }

    inline imm_t LA32Instruction::GetImm16() const noexcept
    {
        return GET_LA32_IMM16(this->insn);
    }

    inline imm_t LA32Instruction::GetImm21() const noexcept
    {
        return GET_LA32_IMM21(this->insn);
    }

    inline imm_t LA32Instruction::GetImm26() const noexcept
    {
        return GET_LA32_IMM26(this->insn);
    }

    inline imm_t LA32Instruction::GetExImm20() const noexcept
    {
        return GET_LA32_X_IMM20(this->insn);
    }

    inline imm_t LA32Instruction::GetExImm5() const noexcept
    {
        return GET_LA32_X_IMM5(this->insn);
    }

    inline unsigned int LA32Instruction::GetOpcodeUpper6() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_U6);
    }

    inline unsigned int LA32Instruction::GetOpcodeLower2() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L2);
    }

    inline unsigned int LA32Instruction::GetOpcodeLower4() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L4);
    }

    inline unsigned int LA32Instruction::GetOpcodeLower8() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L8);
    }

    inline unsigned int LA32Instruction::GetOpcodeLower6() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L6);
    }

    inline unsigned int LA32Instruction::GetOpcodeLower11() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L11);
    }

    inline unsigned int LA32Instruction::GetOpcodeLower16() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L16);
    }

    inline unsigned int LA32Instruction::GetRD() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_RD);
    }

    inline unsigned int LA32Instruction::GetRJ() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_RJ);
    }

    inline unsigned int LA32Instruction::GetRK() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_RK);
    }

    inline unsigned int LA32Instruction::GetRA() const noexcept
    {
        return GET_LA32_STD_OPERAND(this->insn, LA32_RA);
    }

    inline bool LA32Instruction::IsDecoded() const noexcept
    {
        return this->codepoint != nullptr;
    }

    inline const LA32Codepoint* LA32Instruction::GetCodepoint() const noexcept
    {
        return this->codepoint;
    }

    inline std::string LA32Instruction::GetName() const noexcept
    {
        if (this->codepoint == nullptr)
            return std::string();

        return this->codepoint->GetName();
    }

    inline LA32CodepointType LA32Instruction::GetType() const noexcept
    {
        if (this->codepoint == nullptr)
            return LA32CodepointType(0);

        return this->codepoint->GetType();
    }

    inline const LA32Codepoint::Executor LA32Instruction::GetExecutor() const noexcept
    {
        if (this->codepoint == nullptr)
            return nullptr;

        return this->codepoint->GetExecutor();
    }

    inline const LA32Codepoint::Textualizer LA32Instruction::GetTextualizer() const noexcept
    {
        if (this->codepoint == nullptr)
            return nullptr;

        return this->codepoint->GetTextualizer();
    }

    inline std::optional<std::string> LA32Instruction::GetNameIfDecoded() const noexcept
    {
        if (this->codepoint == nullptr)
            return std::nullopt;

        return { this->codepoint->GetName() };
    }

    inline std::optional<LA32CodepointType> LA32Instruction::GetTypeIfDecoded() const noexcept
    {
        if (this->codepoint == nullptr)
            return std::nullopt;

        return { this->codepoint->GetType() };
    }

    inline std::optional<const LA32Codepoint::Executor> LA32Instruction::GetExecutorIfDecoded() const noexcept
    {
        if (this->codepoint == nullptr)
            return std::nullopt;

        return { this->codepoint->GetExecutor() };
    }

    inline std::optional<const LA32Codepoint::Textualizer> LA32Instruction::GetTextualizerIfDecoded() const noexcept
    {
        if (this->codepoint == nullptr)
            return std::nullopt;

        return { this->codepoint->GetTextualizer() };
    }

    inline void LA32Instruction::SetRaw(insnraw_t insn) noexcept
    {
        this->insn = insn;
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetImm8(imm_t imm) noexcept
    {
        SET_LA32_IMM8(this->insn, imm);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetImm12(imm_t imm) noexcept
    {
        SET_LA32_IMM12(this->insn, imm);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetImm14(imm_t imm) noexcept
    {
        SET_LA32_IMM14(this->insn, imm);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetImm16(imm_t imm) noexcept
    {
        SET_LA32_IMM16(this->insn, imm);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetImm21(imm_t imm) noexcept
    {
        SET_LA32_IMM21(this->insn, imm);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetImm26(imm_t imm) noexcept
    {
        SET_LA32_IMM26(this->insn, imm);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetExImm20(imm_t imm) noexcept
    {
        SET_LA32_X_IMM20(this->insn, imm);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetExImm5(imm_t imm) noexcept
    {
        SET_LA32_X_IMM5(this->insn, imm);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetOpcodeUpper6(unsigned int opcode_u6) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_U6, opcode_u6);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetOpcodeLower2(unsigned int opcode_l2) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L2, opcode_l2);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetOpcodeLower4(unsigned int opcode_l4) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L4, opcode_l4);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetOpcodeLower8(unsigned int opcode_l8) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L8, opcode_l8);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetOpcodeLower6(unsigned int opcode_l6) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L6, opcode_l6);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetOpcodeLower11(unsigned int opcode_l11) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L11, opcode_l11);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetOpcodeLower16(unsigned int opcode_l16) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_OPCODE_L16, opcode_l16);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetRD(unsigned int rd) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_RD, rd);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetRJ(unsigned int rj) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_RJ, rj);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetRK(unsigned int rk) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_RK, rk);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetRA(unsigned int ra) noexcept
    {
        SET_LA32_STD_OPERAND(this->insn, LA32_RA, ra);
        SetCodepoint(nullptr);
    }

    inline void LA32Instruction::SetCodepoint(const LA32Codepoint* codepoint) noexcept
    {
        this->codepoint = codepoint;
    }

    inline std::string LA32Instruction::ToString() const noexcept
    {
        if (this->codepoint == nullptr)
            return std::string();

        if (this->codepoint->GetTextualizer() == nullptr)
            return std::string();

        return this->codepoint->GetTextualizer()(*this);
    }

    inline std::optional<std::string> LA32Instruction::ToStringIfDecoded() const noexcept
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

    inline LA32Decoder::LA32Decoder(const char* name, const char* name_canonical) noexcept
        : name              (std::string(name))
        , name_canonical    (std::string(name_canonical))
    { }

    inline LA32Decoder::LA32Decoder(const std::string& name, const std::string& name_canonical) noexcept
        : name              (name)
        , name_canonical    (name_canonical)
    { }
    
    inline LA32Decoder::~LA32Decoder() noexcept
    { }

    inline const std::string& LA32Decoder::GetName() const noexcept
    {
        return this->name;
    }

    inline const std::string& LA32Decoder::GetCanonicalName() const noexcept
    {
        return this->name_canonical;
    }
}


// Implementation of: class LA32DecoderCollection
namespace Jasse {
    /*
    std::vector<const LA32Decoder*> decoders;
    */

    inline LA32DecoderCollection::LA32DecoderCollection() noexcept
        : decoders  ()
    { }

    inline LA32DecoderCollection::LA32DecoderCollection(std::initializer_list<const LA32Decoder*> decoders) noexcept
        : decoders  (decoders)
    { }

    inline LA32DecoderCollection::LA32DecoderCollection(const LA32DecoderCollection& obj) noexcept
        : decoders  (obj.decoders)
    { }

    inline LA32DecoderCollection::~LA32DecoderCollection()
    { }

    inline int LA32DecoderCollection::GetSize() const noexcept
    {
        return this->decoders.size();
    }

    inline void LA32DecoderCollection::Clear() noexcept
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

    inline bool LA32DecoderCollection::Has(const std::string& name) const noexcept
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

    inline bool LA32DecoderCollection::HasCanonical(const std::string& name_canonical) const noexcept
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

    inline bool LA32DecoderCollection::Remove(const std::string& name) noexcept
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

    inline bool LA32DecoderCollection::RemoveCanonical(const std::string& name_canonical) noexcept
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

    inline LA32DecoderIterator LA32DecoderCollection::begin() noexcept
    {
        return this->decoders.begin();
    }

    inline LA32DecoderConstIterator LA32DecoderCollection::begin() const noexcept
    {
        return this->decoders.begin();
    }

    inline LA32DecoderIterator LA32DecoderCollection::end() noexcept
    {
        return this->decoders.end();
    }

    inline LA32DecoderConstIterator LA32DecoderCollection::end() const noexcept
    {
        return this->decoders.end();
    }
}
