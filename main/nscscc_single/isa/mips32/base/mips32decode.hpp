#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// Instruction decoding infrastructure
//

#include <list>
#include <string>
#include <initializer_list>

#include "mips32def.hpp"
#include "mips32code.hpp"


namespace Jasse {
    // MIPS32 Decode Instruction
    class MIPS32Instruction {
    private:
        insnraw_t               insn;

        const MIPS32Codepoint*  codepoint;

    public:
        MIPS32Instruction(insnraw_t insn = 0) noexcept;
        MIPS32Instruction(insnraw_t insn, const MIPS32Codepoint* codepoint) noexcept;
        MIPS32Instruction(const MIPS32Instruction& obj) noexcept;
        ~MIPS32Instruction() noexcept;

        insnraw_t               GetRaw() const noexcept;
        imm_t                   GetImmediate() const noexcept;
        imm_t                   GetJumpIndex() const noexcept;
        unsigned int            GetOpcode() const noexcept;
        unsigned int            GetRS() const noexcept;
        unsigned int            GetRT() const noexcept;
        unsigned int            GetRD() const noexcept;
        unsigned int            GetShamt() const noexcept;
        unsigned int            GetFunct() const noexcept;

        bool                    IsDecoded() const noexcept;
        const MIPS32Codepoint*  GetCodepoint() const noexcept;

        std::string                         GetName() const noexcept;
        MIPS32CodepointType                 GetType() const noexcept;
        const MIPS32Codepoint::Executor     GetExecutor() const noexcept;
        const MIPS32Codepoint::Textualizer  GetTextualizer() const noexcept;

        // *NOTICE: Modifying instruction would reset decoded codepoint result.

        void                    SetRaw(insnraw_t insn) noexcept;
        void                    SetImmediate(imm_t imm) noexcept;
        void                    SetJumpIndex(imm_t imm) noexcept;
        void                    SetOpcode(unsigned int opcode) noexcept;
        void                    SetRS(unsigned int rs) noexcept;
        void                    SetRT(unsigned int rt) noexcept;
        void                    SetRD(unsigned int rd) noexcept;
        void                    SetShamt(unsigned int shamt) noexcept;
        void                    SetFunct(unsigned int funct) noexcept;

        void                    SetCodepoint(const MIPS32Codepoint* codepoint) noexcept;

        // *NOTICE: Execution from instruction instance would take no direct effect on PC sequence 
        //          of the underlying MIPS32Instance.
        //          For branch instructions, PC would be redirected after delayslot (if returning
        //          EXEC_DELAYSLOT). But on any instruction execution from this path, PC wouldn't
        //          be increased for this instruction after execution.
        //          PC increment is handled by MIPS32Instance or other user EEI components.
        //          @see MIPS32Instance::Eval()
        MIPS32ExecOutcome       Execute(MIPS32Instance& instance) noexcept;

        std::string             ToString() const noexcept;
    };


    // MIPS32 Instruction Decoder Interface
    class MIPS32DecodeCapable {
    public:
        virtual bool        Decode(MIPS32Instruction& insn) const noexcept = 0;
    };

    // MIPS32 Instruction Decoder
    class MIPS32Decoder : public MIPS32DecodeCapable {
    private:
        // *NOTICE: The name and canonical name is the only identifier of a decoder.
        //          The name indicates the description and source module/author/version of a decoder.
        //          The canonical name indicates the standard/extension name or the official 
        //          name/abbreviation of a decoder.

        const std::string   name;
        const std::string   name_canonical;

    public:
        MIPS32Decoder(const char* name, const char* name_canonical) noexcept;
        MIPS32Decoder(const std::string& name, const std::string& name_canonical) noexcept;
        ~MIPS32Decoder() noexcept;

        const std::string&  GetName() const noexcept;
        const std::string&  GetCanonicalName() const noexcept;

        virtual bool        Decode(MIPS32Instruction& insn) const noexcept override = 0;

        void                operator=(const MIPS32Decoder& obj) = delete;
    };


    // MIPS32 Instruction Decoder Collection Iterator
    typedef std::list<const MIPS32Decoder*>::iterator           MIPS32DecoderIterator;
    typedef std::list<const MIPS32Decoder*>::const_iterator     MIPS32DecoderConstIterator;

    // MIPS32 Instruction Decoder Collection
    class MIPS32DecoderCollection : public MIPS32DecodeCapable {
    private:
        // *NOTICE: "MIPS32Decoder" are stored as constant pointers in the collection.
        //          This means that any modification of any copy of MIPS32Decoder instance would not 
        //          take effect in this collection.
        //          This is based on the principle that any MIPS32Decoder instance should have its own
        //          static constant instance. And any global modification of MIPS32Decoder definition
        //          should be done by modifying the source code in header files.
        std::list<const MIPS32Decoder*>     decoders;

    public:
        MIPS32DecoderCollection() noexcept;
        MIPS32DecoderCollection(std::initializer_list<const MIPS32Decoder*> decoders) noexcept;
        MIPS32DecoderCollection(const MIPS32DecoderCollection& obj) noexcept;
        ~MIPS32DecoderCollection();

        int                         GetSize() const noexcept;
        void                        Clear() noexcept;

        MIPS32DecoderIterator       Begin() noexcept;
        MIPS32DecoderConstIterator  Begin() const noexcept;
        MIPS32DecoderIterator       End() noexcept;
        MIPS32DecoderConstIterator  End() const noexcept;

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

        bool                        Add(const MIPS32Decoder* decoder) noexcept;
        void                        AddAll(const MIPS32DecoderCollection& collection) noexcept;

        bool                        ForceAdd(const MIPS32Decoder* decoder) noexcept;
        void                        ForceAddAll(const MIPS32DecoderCollection& collection) noexcept;

        bool                        Remove(const std::string& name) noexcept;
        bool                        Remove(const char* name) noexcept;
        bool                        RemoveCanonical(const std::string& name_canonical) noexcept;
        bool                        RemoveCanonical(const char* name_canonical) noexcept;

        //
        bool                        Decode(MIPS32Instruction& insn) const noexcept override;

        // Declarations for C++ specified foreach expression

        MIPS32DecoderIterator       begin() noexcept;
        MIPS32DecoderConstIterator  begin() const noexcept;
        MIPS32DecoderIterator       end() noexcept;
        MIPS32DecoderConstIterator  end() const noexcept;
    };
}



// Implementation of: class MIPS32Instruction
namespace Jasse {
    //
    // insnraw_t               insn;
    //
    // const MIPS32Codepoint*  codepoint;
    //

    MIPS32Instruction::MIPS32Instruction(insnraw_t insn) noexcept
        : insn      (insn)
        , codepoint (nullptr)
    { }

    MIPS32Instruction::MIPS32Instruction(insnraw_t insn, const MIPS32Codepoint* codepoint) noexcept
        : insn      (insn)
        , codepoint (codepoint)
    { }

    MIPS32Instruction::MIPS32Instruction(const MIPS32Instruction& obj) noexcept
        : insn      (obj.insn)
        , codepoint (obj.codepoint)
    { }

    MIPS32Instruction::~MIPS32Instruction() noexcept
    { }

    inline insnraw_t MIPS32Instruction::GetRaw() const noexcept
    {
        return insn;
    }

    inline imm_t MIPS32Instruction::GetImmediate() const noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_IMM16);
    }

    inline imm_t MIPS32Instruction::GetJumpIndex() const noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_IMM26);
    }

    inline unsigned int MIPS32Instruction::GetOpcode() const noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_OPCODE);
    }

    inline unsigned int MIPS32Instruction::GetRS() const noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_RS);
    }

    inline unsigned int MIPS32Instruction::GetRT() const noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_RT);
    }

    inline unsigned int MIPS32Instruction::GetRD() const noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_RD);
    }

    inline unsigned int MIPS32Instruction::GetShamt() const noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_SHAMT);
    }

    inline unsigned int MIPS32Instruction::GetFunct() const noexcept
    {
        return GET_MIPS32_STD_OPERAND(insn, MIPS32_FUNCT);
    }

    inline bool MIPS32Instruction::IsDecoded() const noexcept
    {
        return codepoint != nullptr;
    }

    inline const MIPS32Codepoint* MIPS32Instruction::GetCodepoint() const noexcept
    {
        return codepoint;
    }

    inline std::string MIPS32Instruction::GetName() const noexcept
    {
        return codepoint ? codepoint->GetName() : std::string();
    }

    inline MIPS32CodepointType MIPS32Instruction::GetType() const noexcept
    {
        return codepoint ? codepoint->GetType() : MIPS32_TYPE_R;
    }

    inline const MIPS32Codepoint::Executor MIPS32Instruction::GetExecutor() const noexcept
    {
        return codepoint ? codepoint->GetExecutor() : nullptr;
    }

    inline const MIPS32Codepoint::Textualizer MIPS32Instruction::GetTextualizer() const noexcept
    {
        return codepoint ? codepoint->GetTextualizer() : nullptr;
    }

    inline void MIPS32Instruction::SetRaw(insnraw_t insn) noexcept
    {
        this->insn = insn;
        SetCodepoint(nullptr);
    }

    inline void MIPS32Instruction::SetImmediate(imm_t imm) noexcept
    {
        SET_MIPS32_STD_OPERAND(this->insn, MIPS32_IMM16, imm);
        SetCodepoint(nullptr);
    }

    inline void MIPS32Instruction::SetJumpIndex(imm_t imm) noexcept
    {
        SET_MIPS32_STD_OPERAND(this->insn, MIPS32_IMM26, imm);
        SetCodepoint(nullptr);
    }

    inline void MIPS32Instruction::SetOpcode(unsigned int opcode) noexcept
    {
        SET_MIPS32_STD_OPERAND(this->insn, MIPS32_OPCODE, opcode);
        SetCodepoint(nullptr);
    }

    inline void MIPS32Instruction::SetRS(unsigned int rs) noexcept
    {
        SET_MIPS32_STD_OPERAND(this->insn, MIPS32_RS, rs);
        SetCodepoint(nullptr);
    }

    inline void MIPS32Instruction::SetRT(unsigned int rt) noexcept
    {
        SET_MIPS32_STD_OPERAND(this->insn, MIPS32_RT, rt);
        SetCodepoint(nullptr);
    }

    inline void MIPS32Instruction::SetRD(unsigned int rd) noexcept
    {
        SET_MIPS32_STD_OPERAND(this->insn, MIPS32_RD, rd);
        SetCodepoint(nullptr);
    }

    inline void MIPS32Instruction::SetShamt(unsigned int shamt) noexcept
    {
        SET_MIPS32_STD_OPERAND(this->insn, MIPS32_SHAMT, shamt);
        SetCodepoint(nullptr);
    }

    inline void MIPS32Instruction::SetFunct(unsigned int funct) noexcept
    {
        SET_MIPS32_STD_OPERAND(this->insn, MIPS32_FUNCT, funct);
        SetCodepoint(nullptr);
    }

    inline void MIPS32Instruction::SetCodepoint(const MIPS32Codepoint* codepoint) noexcept
    {
        this->codepoint = codepoint;
    }

    inline MIPS32ExecOutcome MIPS32Instruction::Execute(MIPS32Instance& instance) noexcept
    {
        return codepoint ? (codepoint->GetExecutor() ? codepoint->GetExecutor()(*this, instance) 
                                                     : MIPS32ExecOutcome{EXEC_NOT_IMPLEMENTED, ECANCELED}) 
                         : MIPS32ExecOutcome{EXEC_NOT_DECODED, ECANCELED};
    }

    inline std::string MIPS32Instruction::ToString() const noexcept
    {
        return codepoint ? (codepoint->GetTextualizer() ? codepoint->GetTextualizer()(*this) 
                                                        : std::string()) 
                         : std::string();
    }
}


// Implementation of: class MIPS32Decoder
namespace Jasse {
    //
    // const std::string   name;
    // const std::string   name_canonical;
    //

    MIPS32Decoder::MIPS32Decoder(const std::string& name, const std::string& name_canonical) noexcept
        : name              (name)
        , name_canonical    (name_canonical)
    { }

    MIPS32Decoder::MIPS32Decoder(const char* name, const char* name_canonical) noexcept
        : name              (std::string(name))
        , name_canonical    (std::string(name_canonical))
    { }

    MIPS32Decoder::~MIPS32Decoder()
    { }

    inline const std::string& MIPS32Decoder::GetName() const noexcept
    {
        return name;
    }

    inline const std::string& MIPS32Decoder::GetCanonicalName() const noexcept
    {
        return name_canonical;
    }
}


// Implementation of: class MIPS32DecoderCollection
namespace Jasse {
    //
    // std::list<const MIPS32Decoder*>     decoders;
    //

    MIPS32DecoderCollection::MIPS32DecoderCollection() noexcept
        : decoders  ()
    { }

    MIPS32DecoderCollection::MIPS32DecoderCollection(std::initializer_list<const MIPS32Decoder*> decoders) noexcept
        : decoders  (decoders)
    { }

    MIPS32DecoderCollection::MIPS32DecoderCollection(const MIPS32DecoderCollection& obj) noexcept
        : decoders  (obj.decoders)
    { }

    MIPS32DecoderCollection::~MIPS32DecoderCollection()
    { }

    inline int MIPS32DecoderCollection::GetSize() const noexcept
    {
        return decoders.size();
    }

    inline void MIPS32DecoderCollection::Clear() noexcept
    {
        decoders.clear();
    }

    inline MIPS32DecoderIterator MIPS32DecoderCollection::Begin() noexcept
    {
        return decoders.begin();
    }

    inline MIPS32DecoderConstIterator MIPS32DecoderCollection::Begin() const noexcept
    {
        return decoders.begin();
    }

    inline MIPS32DecoderIterator MIPS32DecoderCollection::End() noexcept
    {
        return decoders.end();
    }

    inline MIPS32DecoderConstIterator MIPS32DecoderCollection::End() const noexcept
    {
        return decoders.end();
    }

    inline MIPS32DecoderIterator MIPS32DecoderCollection::begin() noexcept
    {
        return Begin();
    }

    inline MIPS32DecoderConstIterator MIPS32DecoderCollection::begin() const noexcept
    {
        return Begin();
    }

    inline MIPS32DecoderIterator MIPS32DecoderCollection::end() noexcept
    {
        return End();
    }

    inline MIPS32DecoderConstIterator MIPS32DecoderCollection::end() const noexcept
    {
        return End();
    }

    inline bool MIPS32DecoderCollection::Has(const std::string& name) const noexcept
    {
        return Has(name.c_str());
    }

    bool MIPS32DecoderCollection::Has(const char* name) const noexcept
    {
        for (const MIPS32Decoder* exist_decoder : decoders)
            if (exist_decoder->GetName().compare(name) == 0)
                return true;

        return false;
    }

    inline bool MIPS32DecoderCollection::HasCanonical(const std::string& name_canonical) const noexcept
    {
        return Has(name_canonical.c_str());
    }

    bool MIPS32DecoderCollection::HasCanonical(const char* name_canonical) const noexcept
    {
        for (const MIPS32Decoder* exist_decoder : decoders)
            if (exist_decoder->GetCanonicalName().compare(name_canonical) == 0)
                return true;

        return false;
    }

    bool MIPS32DecoderCollection::Add(const MIPS32Decoder* decoder) noexcept
    {
        for (const MIPS32Decoder* exist_decoder : decoders)
            if (exist_decoder->GetName().compare(decoder->GetName()) == 0
            ||  exist_decoder->GetCanonicalName().compare(decoder->GetCanonicalName()) == 0)
                return false;

        decoders.push_back(decoder);

        return true;
    }

    void MIPS32DecoderCollection::AddAll(const MIPS32DecoderCollection& collection) noexcept
    {
        for (const MIPS32Decoder* decoder : collection)
            Add(decoder);
    }

    bool MIPS32DecoderCollection::ForceAdd(const MIPS32Decoder* decoder) noexcept
    {
        for (auto iter = decoders.begin(); iter != decoders.end(); iter++)
            if ((*iter)->GetName().compare(decoder->GetName()) == 0
            ||  (*iter)->GetCanonicalName().compare(decoder->GetCanonicalName()) == 0)
            {
                *iter = decoder;
                return false;
            }

        decoders.push_back(decoder);

        return true;
    }

    void MIPS32DecoderCollection::ForceAddAll(const MIPS32DecoderCollection& collection) noexcept
    {
        for (const MIPS32Decoder* decoder : collection)
            ForceAdd(decoder);
    }

    inline bool MIPS32DecoderCollection::Remove(const std::string& name) noexcept
    {
        return Remove(name.c_str());
    }

    bool MIPS32DecoderCollection::Remove(const char* name) noexcept
    {
        for (auto iter = decoders.begin(); iter != decoders.end(); iter++)
            if ((*iter)->GetName().compare(name) == 0)
            {
                decoders.erase(iter);
                return true;
            }
        
        return false;
    }

    inline bool MIPS32DecoderCollection::RemoveCanonical(const std::string& name_canonical) noexcept
    {
        return RemoveCanonical(name_canonical.c_str());
    }

    bool MIPS32DecoderCollection::RemoveCanonical(const char* name_canonical) noexcept
    {
        for (auto iter = decoders.begin(); iter != decoders.end(); iter++)
            if ((*iter)->GetCanonicalName().compare(name_canonical) == 0)
            {
                decoders.erase(iter);
                return true;
            }

        return false;
    }

    bool MIPS32DecoderCollection::Decode(MIPS32Instruction& insn) const noexcept
    {
        for (const MIPS32Decoder* decoder : decoders)
            if (decoder->Decode(insn))
                return true;

        return false;
    }
}
