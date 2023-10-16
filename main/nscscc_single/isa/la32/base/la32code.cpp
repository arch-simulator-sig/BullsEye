#include "la32code.hpp"
//
// LA32R (NSCSCC) ISA Emulator (Jasse)
//
// Instruction decoding infrastructure
//

#include <algorithm>


// Implementation of: class LA32Codepoint
namespace Jasse {
    /*
    const std::string       name;
    const LA32CodepointType type;

    const LA32DecodePath    decodePath;

    const Executor          executor;
    const Textualizer       textualizer;
    */

    inline LA32Codepoint::LA32Codepoint(const char*               name,
                                 const LA32CodepointType   type,
                                 const LA32DecodePath      decodePath,
                                 const Executor            executor,
                                 const Textualizer         textualizer) noexcept
        : name          (std::string(name))
        , type          (type)
        , decodePath    (decodePath)
        , executor      (executor)
        , textualizer   (textualizer) 
    { }

    inline LA32Codepoint::LA32Codepoint(const std::string&        name,
                                 const LA32CodepointType   type,
                                 const LA32DecodePath      decodePath,
                                 const Executor            executor,
                                 const Textualizer         textualizer) noexcept
        : name          (name)
        , type          (type)
        , decodePath    (decodePath)
        , executor      (executor)
        , textualizer   (textualizer)
    { }

    inline LA32Codepoint::LA32Codepoint(const LA32Codepoint& obj) noexcept
        : name          (obj.name)
        , type          (obj.type)
        , decodePath    (obj.decodePath)
        , executor      (obj.executor)
        , textualizer   (obj.textualizer)
    { }

    inline LA32Codepoint::~LA32Codepoint() noexcept
    { }

    inline const std::string& LA32Codepoint::GetName() const noexcept
    {
        return this->name;
    }

    inline LA32CodepointType LA32Codepoint::GetType() const noexcept
    {
        return this->type;
    }

    inline const LA32Codepoint::Executor LA32Codepoint::GetExecutor() const noexcept
    {
        return this->executor;
    }

    inline const LA32Codepoint::Textualizer LA32Codepoint::GetTextualizer() const noexcept
    {
        return this->textualizer;
    }

    inline const LA32DecodePath LA32Codepoint::GetDecodePath() const noexcept
    {
        return this->decodePath;
    }

    inline bool LA32Codepoint::CompareCanonical(const LA32Codepoint& obj) const noexcept
    {
        if (this->name != obj.name)
            return false;

        if (this->type != obj.type)
            return false;

        return true;
    }

    inline bool LA32Codepoint::Compare(const LA32Codepoint& obj) const noexcept
    {
        if (!this->CompareCanonical(obj))
            return false;

        if (this->decodePath != obj.decodePath)
            return false;

        if (this->executor != obj.executor)
            return false;

        if (this->textualizer != obj.textualizer)
            return false;

        return true;
    }

    inline bool LA32Codepoint::operator==(const LA32Codepoint& obj) const noexcept
    {
        return this->Compare(obj);
    }

    inline bool LA32Codepoint::operator!=(const LA32Codepoint& obj) const noexcept
    {
        return !this->Compare(obj);
    }
}


// Implementation of: class LA32CodepointCollection
namespace Jasse {
    /*
    std::vector<const LA32Codepoint*> codepoints;
    */

    inline LA32CodepointCollection::LA32CodepointCollection() noexcept
        : codepoints    ()
    { }

    inline LA32CodepointCollection::LA32CodepointCollection(std::initializer_list<const LA32Codepoint*> codepoints) noexcept
        : codepoints    (codepoints)
    { }

    inline LA32CodepointCollection::LA32CodepointCollection(std::initializer_list<LA32CodepointCollection> collections) noexcept
        : codepoints    ()
    {
        for (auto& collection : collections)
            this->AddAll(collection);
    }

    inline LA32CodepointCollection::LA32CodepointCollection(const LA32CodepointCollection& obj) noexcept
        : codepoints    (obj.codepoints)
    { }

    inline LA32CodepointCollection::~LA32CodepointCollection()
    { }

    inline size_t LA32CodepointCollection::GetSize() const noexcept
    {
        return this->codepoints.size();
    }

    inline void LA32CodepointCollection::Add(const LA32Codepoint* codepoint) noexcept
    {
        this->codepoints.push_back(codepoint);
    }

    inline void LA32CodepointCollection::AddAll(const LA32CodepointCollection& collection) noexcept
    {
        this->codepoints.insert(this->codepoints.end(), collection.codepoints.begin(), collection.codepoints.end());
    }

    inline void LA32CodepointCollection::Erase(const LA32Codepoint* codepoint) noexcept
    {
        this->codepoints.erase(std::remove(this->codepoints.begin(), this->codepoints.end(), codepoint), this->codepoints.end());
    }

    inline void LA32CodepointCollection::Erase(LA32CodepointConstIterator pos) noexcept
    {
        this->codepoints.erase(pos);
    }

    inline void LA32CodepointCollection::Clear() noexcept
    {
        this->codepoints.clear();
    }

    inline LA32CodepointIterator LA32CodepointCollection::begin() noexcept
    {
        return this->codepoints.begin();
    }

    inline LA32CodepointConstIterator LA32CodepointCollection::begin() const noexcept
    {
        return this->codepoints.begin();
    }

    inline LA32CodepointIterator LA32CodepointCollection::end() noexcept
    {
        return this->codepoints.end();
    }

    inline LA32CodepointConstIterator LA32CodepointCollection::end() const noexcept
    {
        return this->codepoints.end();
    }
}
