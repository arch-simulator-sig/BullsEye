#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// Instruction decoding infrastructure
//

#include <string>
#include <vector>
#include <initializer_list>
#include <algorithm>

#include "mips32def.hpp"


namespace Jasse {
    // MIPS32 Codepoint Decode Path
    typedef bool    (*MIPS32DecodePath)(MIPS32Instruction& insn);

    // MIPS32 Codepoint
    class MIPS32Codepoint {
    public:
        // MIPS32 Instruction Textualizer
        typedef std::string         (*Textualizer)(const MIPS32Instruction&);

        // MIPS32 Instruction Executor
        typedef MIPS32ExecOutcome   (*Executor)(const MIPS32Instruction&, MIPS32Instance&);

    private:
        const std::string           name;
        const MIPS32CodepointType   type;

        const MIPS32DecodePath      decodePath;

        const Executor              executor;
        const Textualizer           textualizer;

    public:
        MIPS32Codepoint(const char*                 name,
                        const MIPS32CodepointType   type,
                        const MIPS32DecodePath      decodePath,
                        const Executor              executor,
                        const Textualizer           textualizer) noexcept;
        
        MIPS32Codepoint(const std::string&          name,
                        const MIPS32CodepointType   type,
                        const MIPS32DecodePath      decodePath,
                        const Executor              executor,
                        const Textualizer           textuailzer) noexcept;

        MIPS32Codepoint(const MIPS32Codepoint& obj) noexcept;
        ~MIPS32Codepoint() noexcept;

        const std::string&      GetName() const noexcept;
        MIPS32CodepointType     GetType() const noexcept;
        const Executor          GetExecutor() const noexcept;
        const Textualizer       GetTextualizer() const noexcept;

        const MIPS32DecodePath  GetDecodePath() const noexcept;

        bool                    CompareCanonical(const MIPS32Codepoint& obj) const noexcept;
        bool                    Compare(const MIPS32Codepoint& obj) const noexcept;

        bool                    operator==(const MIPS32Codepoint& obj) const noexcept;
        bool                    operator!=(const MIPS32Codepoint& obj) const noexcept;
    };


    // MIPS32 Codepoint Colection Iterator
    using MIPS32CodepointIterator       = std::vector<const MIPS32Codepoint*>::iterator;
    using MIPS32CodepointConstIterator  = std::vector<const MIPS32Codepoint*>::const_iterator;

    // MIPS32 Codepoint Collection
    class MIPS32CodepointCollection {
    private:
        // *NOTICE: "MIPS32Codepoint" are stored as constant pointers in the collection.
        //          This means that any modification of any copy of MIPS32Codepoint instance would not 
        //          take effect in this collection.
        //          This is based on the principle that any MIPS32Codepoint instance should have its own
        //          static constant instance. And any global modification of MIPS32Codepoint definition
        //          should be done by modifying the source code in header files.
        std::vector<const MIPS32Codepoint*> codepoints;

    public:
        MIPS32CodepointCollection() noexcept;
        MIPS32CodepointCollection(std::initializer_list<const MIPS32Codepoint*> codepoints) noexcept;
        MIPS32CodepointCollection(std::initializer_list<MIPS32CodepointCollection> collections) noexcept;
        MIPS32CodepointCollection(const MIPS32CodepointCollection& obj) noexcept;
        ~MIPS32CodepointCollection();

        size_t                          GetSize() const noexcept;

        const MIPS32Codepoint*          Get(int index) const noexcept;
        void                            Set(int index, const MIPS32Codepoint* codepoint) noexcept;
        void                            Add(const MIPS32Codepoint* codepoint) noexcept;
        void                            AddAll(const MIPS32CodepointCollection& collection) noexcept;
        void                            Erase(const MIPS32Codepoint* codepoint) noexcept;
        void                            Erase(MIPS32CodepointConstIterator pos) noexcept;
        void                            Erase(MIPS32CodepointConstIterator first, MIPS32CodepointConstIterator last) noexcept;
        void                            Clear() noexcept;

        MIPS32CodepointIterator         Begin() noexcept;
        MIPS32CodepointConstIterator    Begin() const noexcept;
        MIPS32CodepointIterator         End() noexcept;
        MIPS32CodepointConstIterator    End() const noexcept;

        const MIPS32Codepoint*&         operator[](int index) noexcept;
        const MIPS32Codepoint*          operator[](int index) const noexcept;

        // Declarations for C++ specified foreach expression
        MIPS32CodepointIterator         begin() noexcept;
        MIPS32CodepointConstIterator    begin() const noexcept;
        MIPS32CodepointIterator         end() noexcept;
        MIPS32CodepointConstIterator    end() const noexcept;
    };
}



// Implementation of: class MIPS32Codepoint
namespace Jasse {
    /*
    const std::string           name;
    const MIPS32CodepointType   type;

    const MIPS32DecodePath      decodePath;

    const Executor              executor;
    const Textualizer           textualizer;
    */

    MIPS32Codepoint::MIPS32Codepoint(const char*                name,
                                     const MIPS32CodepointType  type,
                                     const MIPS32DecodePath     decodePath,
                                     const Executor             executor,
                                     const Textualizer          textualizer) noexcept
        : name          (std::string(name))
        , type          (type)
        , decodePath    (decodePath)
        , executor      (executor)
        , textualizer   (textualizer)
    { }

    MIPS32Codepoint::MIPS32Codepoint(const std::string&         name,
                                     const MIPS32CodepointType  type,
                                     const MIPS32DecodePath     decodePath,
                                     const Executor             executor,
                                     const Textualizer          textualizer) noexcept
        : name          (name)
        , type          (type)
        , decodePath    (decodePath)
        , executor      (executor)
        , textualizer   (textualizer)
    { }

    MIPS32Codepoint::MIPS32Codepoint(const MIPS32Codepoint& obj) noexcept
        : name          (obj.name)
        , type          (obj.type)
        , decodePath    (obj.decodePath)
        , executor      (obj.executor)
        , textualizer   (obj.textualizer)
    { }

    MIPS32Codepoint::~MIPS32Codepoint() noexcept
    { }

    inline const std::string& MIPS32Codepoint::GetName() const noexcept
    {
        return name;
    }

    inline MIPS32CodepointType MIPS32Codepoint::GetType() const noexcept
    {
        return type;
    }

    inline const MIPS32Codepoint::Executor MIPS32Codepoint::GetExecutor() const noexcept
    {
        return executor;
    }

    inline const MIPS32Codepoint::Textualizer MIPS32Codepoint::GetTextualizer() const noexcept
    {
        return textualizer;
    }

    inline const MIPS32DecodePath MIPS32Codepoint::GetDecodePath() const noexcept
    {
        return decodePath;
    }

    inline bool MIPS32Codepoint::CompareCanonical(const MIPS32Codepoint& obj) const noexcept
    {
        if (name != obj.name)
            return false;

        if (type != obj.type)
            return false;
        
        return true;
    }

    inline bool MIPS32Codepoint::Compare(const MIPS32Codepoint& obj) const noexcept
    {
        if (!CompareCanonical(obj))
            return false;

        if (executor != obj.executor)
            return false;

        if (textualizer != obj.textualizer)
            return false;

        return true;
    }

    inline bool MIPS32Codepoint::operator==(const MIPS32Codepoint& obj) const noexcept
    {
        return this->Compare(obj);
    }

    inline bool MIPS32Codepoint::operator!=(const MIPS32Codepoint& obj) const noexcept
    {
        return !this->Compare(obj);
    }
}


// Implementation of: class MIPS32CodepointCollection
namespace Jasse {
    //
    // std::vector<const MIPS32Codepoint*> codepoints;
    //

    MIPS32CodepointCollection::MIPS32CodepointCollection() noexcept
        : codepoints    ()
    { }

    MIPS32CodepointCollection::MIPS32CodepointCollection(std::initializer_list<const MIPS32Codepoint*> codepoints) noexcept
        : codepoints    (codepoints)
    { }

    MIPS32CodepointCollection::MIPS32CodepointCollection(std::initializer_list<MIPS32CodepointCollection> collections) noexcept
        : codepoints    ()
    { 
        for (auto& collection : collections)
            this->AddAll(collection);
    }

    MIPS32CodepointCollection::MIPS32CodepointCollection(const MIPS32CodepointCollection& obj) noexcept
        : codepoints    (obj.codepoints)
    { }

    MIPS32CodepointCollection::~MIPS32CodepointCollection()
    { }

    inline size_t MIPS32CodepointCollection::GetSize() const noexcept
    {
        return codepoints.size();
    }

    inline const MIPS32Codepoint* MIPS32CodepointCollection::Get(int index) const noexcept
    {
        return codepoints[index];
    }

    inline void MIPS32CodepointCollection::Set(int index, const MIPS32Codepoint* codepoint) noexcept
    {
        codepoints[index] = codepoint;
    }

    inline void MIPS32CodepointCollection::Add(const MIPS32Codepoint* codepoint) noexcept
    {
        codepoints.push_back(codepoint);
    }

    inline void MIPS32CodepointCollection::AddAll(const MIPS32CodepointCollection& collection) noexcept
    {
        codepoints.insert(codepoints.end(), collection.Begin(), collection.End());
    }

    inline void MIPS32CodepointCollection::Erase(const MIPS32Codepoint* codepoint) noexcept
    {
        codepoints.erase(std::remove(codepoints.begin(), codepoints.end(), codepoint), codepoints.end());
    }

    inline void MIPS32CodepointCollection::Erase(MIPS32CodepointConstIterator pos) noexcept
    {
        codepoints.erase(pos);
    }

    inline void MIPS32CodepointCollection::Erase(MIPS32CodepointConstIterator first, MIPS32CodepointConstIterator last) noexcept
    {
        codepoints.erase(first, last);
    }

    inline void MIPS32CodepointCollection::Clear() noexcept
    {
        codepoints.clear();
    }

    inline MIPS32CodepointIterator MIPS32CodepointCollection::Begin() noexcept
    {
        return codepoints.begin();
    }

    inline MIPS32CodepointConstIterator MIPS32CodepointCollection::Begin() const noexcept
    {
        return codepoints.begin();
    }

    inline MIPS32CodepointIterator MIPS32CodepointCollection::End() noexcept
    {
        return codepoints.end();
    }

    inline MIPS32CodepointConstIterator MIPS32CodepointCollection::End() const noexcept
    {
        return codepoints.end();
    }

    inline MIPS32CodepointIterator MIPS32CodepointCollection::begin() noexcept
    {
        return Begin();
    }

    inline MIPS32CodepointConstIterator MIPS32CodepointCollection::begin() const noexcept
    {
        return Begin();
    }

    inline MIPS32CodepointIterator MIPS32CodepointCollection::end() noexcept
    {
        return End();
    }

    inline MIPS32CodepointConstIterator MIPS32CodepointCollection::end() const noexcept
    {
        return End();
    }

    inline const MIPS32Codepoint*& MIPS32CodepointCollection::operator[](int index) noexcept
    {
        return codepoints[index];
    }

    inline const MIPS32Codepoint* MIPS32CodepointCollection::operator[](int index) const noexcept
    {
        return codepoints[index];
    }
}
