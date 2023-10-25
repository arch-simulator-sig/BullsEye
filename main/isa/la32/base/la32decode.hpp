#pragma once
//
// LA32R (NSCSCC) ISA Emulator (Jasse)
//
// Instruction decoding infrastructure
//

#ifndef __HEADER_JASSE_LA32__BASE_DECODE
#define __HEADER_JASSE_LA32__BASE_DECODE


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


#endif
