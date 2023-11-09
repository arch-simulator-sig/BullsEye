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
    const LA32Trait*        trait;

    const LA32DecodePath    decodePath;

    const Executor          executor;
    const Textualizer       textualizer;
    */

    LA32Codepoint::LA32Codepoint(const char*                name,
                                 const LA32CodepointType    type,
                                 const LA32Trait*           trait,
                                 const LA32DecodePath       decodePath,
                                 const Executor             executor,
                                 const Textualizer          textualizer) noexcept
        : name          (std::string(name))
        , type          (type)
        , trait         (trait)
        , decodePath    (decodePath)
        , executor      (executor)
        , textualizer   (textualizer) 
    { }

    LA32Codepoint::LA32Codepoint(const std::string&         name,
                                 const LA32CodepointType    type,
                                 const LA32Trait*           trait,
                                 const LA32DecodePath       decodePath,
                                 const Executor             executor,
                                 const Textualizer          textualizer) noexcept
        : name          (name)
        , type          (type)
        , trait         (trait)
        , decodePath    (decodePath)
        , executor      (executor)
        , textualizer   (textualizer)
    { }

    LA32Codepoint::LA32Codepoint(const LA32Codepoint& obj) noexcept
        : name          (obj.name)
        , type          (obj.type)
        , trait         (obj.trait)
        , decodePath    (obj.decodePath)
        , executor      (obj.executor)
        , textualizer   (obj.textualizer)
    { }

    LA32Codepoint::~LA32Codepoint() noexcept
    { }

    const std::string& LA32Codepoint::GetName() const noexcept
    {
        return this->name;
    }

    LA32CodepointType LA32Codepoint::GetType() const noexcept
    {
        return this->type;
    }

    const LA32Trait* LA32Codepoint::GetTrait() const noexcept
    {
        return this->trait;
    }

    const LA32Codepoint::Executor LA32Codepoint::GetExecutor() const noexcept
    {
        return this->executor;
    }

    const LA32Codepoint::Textualizer LA32Codepoint::GetTextualizer() const noexcept
    {
        return this->textualizer;
    }

    const LA32DecodePath LA32Codepoint::GetDecodePath() const noexcept
    {
        return this->decodePath;
    }

    bool LA32Codepoint::CompareCanonical(const LA32Codepoint& obj) const noexcept
    {
        if (this->name != obj.name)
            return false;

        if (this->type != obj.type)
            return false;

        return true;
    }

    bool LA32Codepoint::Compare(const LA32Codepoint& obj) const noexcept
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

    bool LA32Codepoint::operator==(const LA32Codepoint& obj) const noexcept
    {
        return this->Compare(obj);
    }

    bool LA32Codepoint::operator!=(const LA32Codepoint& obj) const noexcept
    {
        return !this->Compare(obj);
    }
}


// Implementation of: class LA32CodepointCollection
namespace Jasse {
    /*
    std::vector<const LA32Codepoint*> codepoints;
    */

    LA32CodepointCollection::LA32CodepointCollection() noexcept
        : codepoints    ()
    { }

    LA32CodepointCollection::LA32CodepointCollection(std::initializer_list<const LA32Codepoint*> codepoints) noexcept
        : codepoints    (codepoints)
    { }

    LA32CodepointCollection::LA32CodepointCollection(std::initializer_list<LA32CodepointCollection> collections) noexcept
        : codepoints    ()
    {
        for (auto& collection : collections)
            this->AddAll(collection);
    }

    LA32CodepointCollection::LA32CodepointCollection(const LA32CodepointCollection& obj) noexcept
        : codepoints    (obj.codepoints)
    { }

    LA32CodepointCollection::~LA32CodepointCollection()
    { }

    size_t LA32CodepointCollection::GetSize() const noexcept
    {
        return this->codepoints.size();
    }

    void LA32CodepointCollection::Add(const LA32Codepoint* codepoint) noexcept
    {
        this->codepoints.push_back(codepoint);
    }

    void LA32CodepointCollection::AddAll(const LA32CodepointCollection& collection) noexcept
    {
        this->codepoints.insert(this->codepoints.end(), collection.codepoints.begin(), collection.codepoints.end());
    }

    void LA32CodepointCollection::Erase(const LA32Codepoint* codepoint) noexcept
    {
        this->codepoints.erase(std::remove(this->codepoints.begin(), this->codepoints.end(), codepoint), this->codepoints.end());
    }

    void LA32CodepointCollection::Erase(LA32CodepointConstIterator pos) noexcept
    {
        this->codepoints.erase(pos);
    }

    void LA32CodepointCollection::Clear() noexcept
    {
        this->codepoints.clear();
    }

    LA32CodepointIterator LA32CodepointCollection::begin() noexcept
    {
        return this->codepoints.begin();
    }

    LA32CodepointConstIterator LA32CodepointCollection::begin() const noexcept
    {
        return this->codepoints.begin();
    }

    LA32CodepointIterator LA32CodepointCollection::end() noexcept
    {
        return this->codepoints.end();
    }

    LA32CodepointConstIterator LA32CodepointCollection::end() const noexcept
    {
        return this->codepoints.end();
    }
}
