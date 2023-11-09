#pragma once
//
// LA32R (NSCSCC) ISA Emulator (Jasse)
//
// Instruction decoding infrastructure
//

#ifndef __HEADER_JASSE_LA32__BASE_CODE
#define __HEADER_JASSE_LA32__BASE_CODE


#include <string>
#include <vector>
#include <initializer_list>

#include "la32def.hpp"


namespace Jasse {
    // LA32 Codepoint Decode Path
    typedef bool    (*LA32DecodePath)(LA32Instruction& insn);

    // LA32 Codepoint
    class LA32Codepoint {
    public:
        // LA32 Instruction Textualizer
        typedef std::string         (*Textualizer)(const LA32Instruction&);

        // LA32 Instruction Executor
        typedef LA32ExecOutcome     (*Executor)(const LA32Instruction&, LA32Instance&);

    private:
        const std::string       name;
        const LA32CodepointType type;

        const LA32Trait*        trait;

        const LA32DecodePath    decodePath;

        const Executor          executor;
        const Textualizer       textualizer;

    public:
        LA32Codepoint(const char*               name,
                      const LA32CodepointType   type,
                      const LA32Trait*          trait,
                      const LA32DecodePath      decodePath,
                      const Executor            executor,
                      const Textualizer         textualizer) noexcept;

        LA32Codepoint(const std::string&        name,
                      const LA32CodepointType   type,
                      const LA32Trait*          trait,
                      const LA32DecodePath      decodePath,
                      const Executor            executor,
                      const Textualizer         textualizer) noexcept;

        LA32Codepoint(const LA32Codepoint& obj) noexcept;
        ~LA32Codepoint() noexcept;

        const std::string&      GetName() const noexcept;
        LA32CodepointType       GetType() const noexcept;
        const LA32Trait*        GetTrait() const noexcept;

        const Executor          GetExecutor() const noexcept;
        const Textualizer       GetTextualizer() const noexcept;

        const LA32DecodePath    GetDecodePath() const noexcept;

        bool                    CompareCanonical(const LA32Codepoint& obj) const noexcept;
        bool                    Compare(const LA32Codepoint& obj) const noexcept;

        bool                    operator==(const LA32Codepoint& obj) const noexcept;
        bool                    operator!=(const LA32Codepoint& obj) const noexcept;
    };


    // LA32 Codepoint Collection Iterator
    using LA32CodepointIterator         = std::vector<const LA32Codepoint*>::iterator;
    using LA32CodepointConstIterator    = std::vector<const LA32Codepoint*>::const_iterator;

    // LA32 Codepoint Collection
    class LA32CodepointCollection {
    private:
        // *NOTICE: "LA32Codepoint" are stored as constant pointers in the collection.
        //          This means that any modification of any copy of LA32Codepoint instance would not 
        //          take effect in this collection.
        //          This is based on the principle that any LA32Codepoint instance should have its own
        //          static constant instance. And any global modification of LA32Codepoint definition
        //          should be done by modifying the source code in header files.
        std::vector<const LA32Codepoint*> codepoints;

    public:
        LA32CodepointCollection() noexcept;
        LA32CodepointCollection(std::initializer_list<const LA32Codepoint*> codepoints) noexcept;
        LA32CodepointCollection(std::initializer_list<LA32CodepointCollection> collections) noexcept;
        LA32CodepointCollection(const LA32CodepointCollection& obj) noexcept;
        ~LA32CodepointCollection();

        size_t                      GetSize() const noexcept;

        void                        Add(const LA32Codepoint* codepoint) noexcept;
        void                        AddAll(const LA32CodepointCollection& collection) noexcept;
        void                        Erase(const LA32Codepoint* codepoint) noexcept;
        void                        Erase(LA32CodepointConstIterator pos) noexcept;
        void                        Clear() noexcept;

        // Declarations for C++ specified foreach expression
        LA32CodepointIterator       begin() noexcept;
        LA32CodepointConstIterator  begin() const noexcept;
        LA32CodepointIterator       end() noexcept;
        LA32CodepointConstIterator  end() const noexcept;
    };
}


#endif
