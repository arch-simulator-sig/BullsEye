#include "la32trace.hpp"
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
// Trace Subsystem Infrastructures
//


// Implementation of: class LA32TraceEntity
namespace Jasse {
    /*
    ContentType<Content>    contentType;
    Content                 content;

    Reference               parent0;
    Reference               parent1;
    Reference               parent2;
    */

    inline LA32TraceEntity::LA32TraceEntity() noexcept
        : contentType   (nullptr)
        , content       ()
        , parent0       ()
        , parent1       ()
        , parent2       ()
    { }

    inline LA32TraceEntity::LA32TraceEntity(const LA32TraceEntity& obj) noexcept
        : contentType   (obj.contentType)
        , content       (obj.content)
        , parent0       (obj.parent0)
        , parent1       (obj.parent1)
        , parent2       (obj.parent2)
    { }

    inline LA32TraceEntity::LA32TraceEntity(LA32TraceEntity&& obj) noexcept
        : contentType   (obj.contentType)
        , content       (obj.content)
        , parent0       (obj.parent0)
        , parent1       (obj.parent1)
        , parent2       (obj.parent2)
    { }

    inline LA32TraceEntity::~LA32TraceEntity() noexcept
    { }

    inline LA32TraceEntity::ContentType<LA32TraceEntity::Content> LA32TraceEntity::GetContentType() const noexcept
    {
        return this->contentType;        
    }

    inline LA32TraceEntity::Content& LA32TraceEntity::GetContent() noexcept
    {
        return this->content;
    }

    inline const LA32TraceEntity::Content& LA32TraceEntity::GetContent() const noexcept
    {
        return this->content;
    }

    template<class _TContent>
    inline _TContent& LA32TraceEntity::ReinterpretContent() noexcept
    {
        return *reinterpret_cast<_TContent*>(&this->content);
    }

    template<class _TContent>
    inline const _TContent& LA32TraceEntity::ReinterpretContent() const noexcept
    {
        return *reinterpret_cast<const _TContent*>(&this->content);
    }

    template<class _TContent>
    inline std::optional<std::reference_wrapper<_TContent>> LA32TraceEntity::GetContent(ContentType<_TContent> type) noexcept
    {
        if (this->contentType == type)
            return { std::ref(this->ReinterpretContent<_TContent>()) };

        return std::nullopt;
    }

    template<class _TContent>
    inline std::optional<std::reference_wrapper<const _TContent>> LA32TraceEntity::GetContent(ContentType<_TContent> type) const noexcept
    {
        if (this->contentType == type)
            return { std::cref(this->ReinterpretContent<_TContent>()) };

        return std::nullopt;
    }

    template<class _TContent>
    inline void LA32TraceEntity::SetContent(ContentType<_TContent> type, const _TContent& content) noexcept
    {
        this->contentType   = reinterpret_cast<ContentType<Content>>(type);
        this->content       = reinterpret_cast<const LA32TraceEntity::Content&>(content);
    }

    template<class _TContent>
    inline _TContent& LA32TraceEntity::SetContentType(ContentType<_TContent> type) noexcept
    {
        this->contentType   = reinterpret_cast<ContentType<Content>>(type);
        return this->ReinterpretContent<_TContent>();
    }

    inline void LA32TraceEntity::SetFirstParent(const Reference& parent0) noexcept
    {
        this->parent0 = parent0;
    }

    inline void LA32TraceEntity::SetSecondParent(const Reference& parent1) noexcept
    {
        this->parent1 = parent1;
    }

    inline void LA32TraceEntity::SetThirdParent(const Reference& parent2) noexcept
    {
        this->parent2 = parent2;
    }

    inline LA32TraceEntity::Reference& LA32TraceEntity::GetFirstParent() noexcept
    {
        return parent0;
    }

    inline const LA32TraceEntity::Reference& LA32TraceEntity::GetFirstParent() const noexcept
    {
        return parent0;
    }

    inline LA32TraceEntity::Reference& LA32TraceEntity::GetSecondParent() noexcept
    {
        return parent1;
    }

    inline const LA32TraceEntity::Reference& LA32TraceEntity::GetSecondParent() const noexcept
    {
        return parent1;
    }

    inline LA32TraceEntity::Reference& LA32TraceEntity::GetThirdParent() noexcept
    {
        return parent2;
    }

    inline const LA32TraceEntity::Reference& LA32TraceEntity::GetThirdParent() const noexcept
    {
        return parent2;
    }
}


// Implementation of: class LA32TraceEntity::ContentTypeBase
namespace Jasse {
    /*
    const std::string_view  name;
    */

    template<class _TContent>
    inline LA32TraceEntity::ContentTypeBase<_TContent>::ContentTypeBase(const char* name) noexcept
        : name  (name)
    { }

    template<class _TContent>
    inline const std::string_view& LA32TraceEntity::ContentTypeBase<_TContent>::GetName() const noexcept
    {
        return this->name;
    }

    template<class _TContent>
    inline void LA32TraceEntity::ContentTypeBase<_TContent>::Finalize(LA32TraceEntity& entity) const noexcept
    { }
}


// Implementation of: struct LA32TraceEntity::Initializer
namespace Jasse {
    /*
    void operator()(LA32TraceEntity& entity) const noexcept;
    */

    inline void LA32TraceEntity::Initializer::operator()(LA32TraceEntity& entity) const noexcept
    { }
}


// Implementation of: struct LA32TraceEntity::Finalizer
namespace Jasse {
    /*
    void operator()(LA32TraceEntity& entity) const noexcept;
    */

    inline void LA32TraceEntity::Finalizer::operator()(LA32TraceEntity& entity) const noexcept
    { 
        entity.GetContentType()->Finalize(entity);
    }
}



// Implementation of: struct LA32TracedInstructionExecution
namespace Jasse {

    inline void LA32TracedInstructionExecution::SetTracedFetch(LA32TraceEntity& entity, const LA32TraceEntity::Reference& trace) noexcept
    {
        entity.SetFirstParent(trace);
    }

    inline LA32TraceEntity::Reference& LA32TracedInstructionExecution::GetTracedFetch(LA32TraceEntity& entity) noexcept
    {
        return entity.GetFirstParent();
    }

    inline const LA32TraceEntity::Reference& LA32TracedInstructionExecution::GetTracedFetch(const LA32TraceEntity& entity) noexcept
    {
        return entity.GetFirstParent();
    }

    inline void LA32TracedInstructionExecution::SetTracedFirstOperand(LA32TraceEntity& entity, const LA32TraceEntity::Reference& trace) noexcept
    {
        entity.SetSecondParent(trace);
    }

    inline LA32TraceEntity::Reference& LA32TracedInstructionExecution::GetTracedFirstOperand(LA32TraceEntity& entity) noexcept
    {
        return entity.GetSecondParent();
    }

    inline const LA32TraceEntity::Reference& LA32TracedInstructionExecution::GetTracedFirstOperand(const LA32TraceEntity& entity) noexcept
    {
        return entity.GetSecondParent();
    }

    inline void LA32TracedInstructionExecution::SetTracedSecondOperand(LA32TraceEntity& entity, const LA32TraceEntity::Reference& trace) noexcept
    {
        entity.SetThirdParent(trace);
    }

    inline LA32TraceEntity::Reference& LA32TracedInstructionExecution::GetTracedSecondOperand(LA32TraceEntity& entity) noexcept
    {
        return entity.GetThirdParent();
    }

    inline const LA32TraceEntity::Reference& LA32TracedInstructionExecution::GetTracedSecondOperand(const LA32TraceEntity& entity) noexcept
    {
        return entity.GetThirdParent();
    }
}



// Implementation of: struct LA32TracedInstructionFetch
namespace Jasse {

    inline void LA32TracedInstructionFetch::SetTracedAddressSource(LA32TraceEntity& entity, const LA32TraceEntity::Reference& trace) noexcept
    {
        entity.SetFirstParent(trace);
    }

    inline LA32TraceEntity::Reference& LA32TracedInstructionFetch::GetTracedAddressSource(LA32TraceEntity& entity) noexcept
    {
        return entity.GetFirstParent();
    }

    inline const LA32TraceEntity::Reference& LA32TracedInstructionFetch::GetTracedAddressSource(const LA32TraceEntity& entity) noexcept
    {
        return entity.GetFirstParent();
    }

    inline void LA32TracedInstructionFetch::SetTracedMemorySource(LA32TraceEntity& entity, const LA32TraceEntity::Reference& trace) noexcept
    {
        entity.SetSecondParent(trace);
    }

    inline LA32TraceEntity::Reference& LA32TracedInstructionFetch::GetTracedMemorySource(LA32TraceEntity& entity) noexcept
    {
        return entity.GetSecondParent();
    }

    inline const LA32TraceEntity::Reference& LA32TracedInstructionFetch::GetTracedMemorySource(const LA32TraceEntity& entity) noexcept
    {
        return entity.GetSecondParent();
    }
}



// Implementation of: class LA32TracedNormalEventModification
namespace Jasse {
    /*
    char*               eventName;
    char*               message;
    */

    inline LA32TracedNormalEventModification::LA32TracedNormalEventModification() noexcept
        : value         ()
        , eventName     (nullptr)
        , message       (nullptr)
    { }

    inline LA32TracedNormalEventModification::LA32TracedNormalEventModification(const LA32TracedNormalEventModification& obj) noexcept
        : value         (obj.value)
        , eventName     (obj.eventName  ? BullsEye::NewStringAndCopy(obj.eventName) : nullptr)
        , message       (obj.message    ? BullsEye::NewStringAndCopy(obj.message)   : nullptr)
    { }

    inline LA32TracedNormalEventModification::LA32TracedNormalEventModification(LA32TracedNormalEventModification&& obj) noexcept
        : value         (obj.value)
        , eventName     (obj.eventName)
        , message       (obj.message)
    {
        obj.eventName   = nullptr;
        obj.message     = nullptr;
    }

    inline LA32TracedNormalEventModification::~LA32TracedNormalEventModification() noexcept
    {
        if (eventName)
            delete[] eventName;

        if (message)
            delete[] message;
    }

    inline char* LA32TracedNormalEventModification::GetEventName() noexcept
    {
        return eventName;
    }

    inline const char* LA32TracedNormalEventModification::GetEventName() const noexcept
    {
        return eventName;
    }

    inline char* LA32TracedNormalEventModification::GetMessage() noexcept
    {
        return message;
    }

    inline const char* LA32TracedNormalEventModification::GetMessage() const noexcept
    {
        return message;
    }

    inline void LA32TracedNormalEventModification::SetEventName(const char* eventName) noexcept
    {
        if (this->eventName)
            delete[] this->eventName;

        this->eventName = eventName ? BullsEye::NewStringAndCopy(eventName) : nullptr;
    }

    inline void LA32TracedNormalEventModification::SetMessage(const char* message) noexcept
    {
        if (this->message)
            delete[] this->message;

        this->message = message ? BullsEye::NewStringAndCopy(message) : nullptr;
    }
}


// Implementation of: class LA32TracedNormalEventModificationTypeInstance
namespace Jasse {
    
    inline LA32TracedNormalEventModificationTypeInstance::LA32TracedNormalEventModificationTypeInstance(const char* name) noexcept
        : LA32TraceEntity::ContentTypeBase<LA32TracedNormalEventModification>(name)
    { }
    
    inline void LA32TracedNormalEventModificationTypeInstance::Finalize(LA32TraceEntity& entity) const noexcept
    {
        entity.ReinterpretContent<LA32TracedNormalEventModification>()
            .~LA32TracedNormalEventModification();
    }
}



// Implementation of: class LA32TracedNormalAttachedMessage
namespace Jasse {
    /*
    char*               messageAbstract;
    char*               messageDetail;
    */

    inline LA32TracedNormalAttachedMessage::LA32TracedNormalAttachedMessage() noexcept
        : messageAbstract   (nullptr)
        , messageDetail     (nullptr)
    { }

    inline LA32TracedNormalAttachedMessage::LA32TracedNormalAttachedMessage(const LA32TracedNormalAttachedMessage& obj) noexcept
        : messageAbstract   (obj.messageAbstract ? BullsEye::NewStringAndCopy(obj.messageAbstract) : nullptr)
        , messageDetail     (obj.messageDetail   ? BullsEye::NewStringAndCopy(obj.messageDetail)   : nullptr)
    { }

    inline LA32TracedNormalAttachedMessage::LA32TracedNormalAttachedMessage(LA32TracedNormalAttachedMessage&& obj) noexcept
        : messageAbstract   (obj.messageAbstract)
        , messageDetail     (obj.messageDetail)
    {
        obj.messageAbstract = nullptr;
        obj.messageDetail   = nullptr;
    }

    inline LA32TracedNormalAttachedMessage::~LA32TracedNormalAttachedMessage() noexcept
    {
        if (messageAbstract)
            delete[] messageAbstract;

        if (messageDetail)
            delete[] messageDetail;
    }

    inline char* LA32TracedNormalAttachedMessage::GetMessageAbstract() noexcept
    {
        return messageAbstract;
    }

    inline const char* LA32TracedNormalAttachedMessage::GetMessageAbstract() const noexcept
    {
        return messageAbstract;
    }

    inline char* LA32TracedNormalAttachedMessage::GetMessageDetail() noexcept
    {
        return messageDetail;
    }

    inline const char* LA32TracedNormalAttachedMessage::GetMessageDetail() const noexcept
    {
        return messageDetail;
    }

    inline void LA32TracedNormalAttachedMessage::SetMessageAbstract(const char* messageAbstract) noexcept
    {
        if (this->messageAbstract)
            delete[] this->messageAbstract;

        this->messageAbstract = messageAbstract ? BullsEye::NewStringAndCopy(messageAbstract) : nullptr;
    }

    inline void LA32TracedNormalAttachedMessage::SetMessageDetail(const char* messageDetail) noexcept
    {
        if (this->messageDetail)
            delete[] this->messageDetail;

        this->messageDetail = messageDetail ? BullsEye::NewStringAndCopy(messageDetail) : nullptr;
    }
}


// Implementation of: class LA32TracedNormalAttachedMessageTypeInstance
namespace Jasse {

    inline LA32TracedNormalAttachedMessageTypeInstance::LA32TracedNormalAttachedMessageTypeInstance(const char* name) noexcept
        : LA32TraceEntity::ContentTypeBase<LA32TracedNormalAttachedMessage>(name)
    { }

    inline void LA32TracedNormalAttachedMessageTypeInstance::Finalize(LA32TraceEntity& entity) const noexcept
    {
        entity.ReinterpretContent<LA32TracedNormalAttachedMessage>()
            .~LA32TracedNormalAttachedMessage();
    }
}


// Implementation of: class LA32TraceContentLegacyType
namespace Jasse {

    const LA32TraceEntity::ContentType<LA32TracedInstructionExecution>      LA32TraceContentLegacyType::INSTRUCTION_EXECUTION
        = new LA32TracedInstructionExecutionTypeInstance("INSTRUCTION_EXECUTION");

    const LA32TraceEntity::ContentType<LA32TracedInstructionFetch>          LA32TraceContentLegacyType::INSTRUCTION_FETCH
        = new LA32TracedInstructionFetchTypeInstance("INSTRUCTION_FETCH");

    const LA32TraceEntity::ContentType<LA32TracedNormalEventModification>   LA32TraceContentLegacyType::NORMAL_EVENT_MODIFICATION
        = new LA32TracedNormalEventModificationTypeInstance("NORMAL_EVENT_MODIFICATION");

    const LA32TraceEntity::ContentType<LA32TracedNormalAttachedMessage>     LA32TraceContentLegacyType::NORMAL_ATTACHED_MESSAGE
        = new LA32TracedNormalAttachedMessageTypeInstance("NORMAL_ATTACHED_MESSAGE");
}



// Implementation of: class LA32TraceHistory
namespace Jasse {
    //
    // size_t                          history_depth;
    //
    // size_t                          capacity;
    // size_t                          count;
    // size_t                          round_pointer;
    //
    // LA32TraceEntity::Reference*     traces;
    //

    inline LA32TraceHistory::LA32TraceHistory(size_t history_depth) noexcept
        : history_depth (history_depth)
        , capacity      (0)
        , count         (0)
        , round_pointer (0)
        , traces        (nullptr)
    { }

    inline LA32TraceHistory::LA32TraceHistory(const LA32TraceHistory& obj) noexcept
        : history_depth (obj.history_depth)
        , capacity      (obj.capacity)
        , count         (obj.count)
        , round_pointer (obj.round_pointer)
        , traces        (nullptr)
    { 
        if (obj.traces)
        {
            traces = new LA32TraceEntity::Reference[obj.capacity];

            std::copy(obj.traces, obj.traces + obj.capacity, traces);
        }
    }

    inline LA32TraceHistory::LA32TraceHistory(const LA32TraceHistory& obj, size_t new_history_depth) noexcept
        : history_depth (new_history_depth)
        , capacity      (0)
        , count         (0)
        , round_pointer (0)
        , traces        (nullptr)
    {
        traces = _ModifyDepth(obj.traces,
                              obj.capacity,
                              obj.count,
                              obj.round_pointer,
                              new_history_depth,
                              capacity,
                              count);
    }

    inline LA32TraceHistory::LA32TraceHistory(LA32TraceHistory&& obj) noexcept
        : history_depth (obj.history_depth)
        , capacity      (obj.capacity)
        , count         (obj.count)
        , round_pointer (obj.round_pointer)
        , traces        (obj.traces)
    {
        obj._Clear();
    }

    inline LA32TraceHistory::~LA32TraceHistory() noexcept
    {
        if (traces)
            delete[] traces;
    }

    inline LA32TraceEntity::Reference* LA32TraceHistory::_ModifyDepth(
        LA32TraceEntity::Reference* const   src,
        size_t                              src_capacity,
        size_t                              src_count,
        size_t                              src_round_pointer,
        size_t                              new_history_depth,
        size_t&                             new_capacity,
        size_t&                             new_count) noexcept
    {
        if (src)
        {
            auto newArray = new LA32TraceEntity::Reference[
                new_capacity = new_count = std::min(src_count, new_history_depth)];

            size_t seg1copy = std::min(new_capacity, src_capacity - src_round_pointer);
            size_t seg2copy = std::min(new_capacity - seg1copy, src_round_pointer);

            if (seg1copy)
                std::copy(src + src_round_pointer, src + src_round_pointer + seg1copy, newArray);
            
            if (seg2copy)
                std::copy(src, src + seg2copy, newArray + seg1copy);

            return newArray;
        }

        return nullptr;
    }

    inline size_t LA32TraceHistory::GetDepth() const noexcept
    {
        return history_depth;
    }

    inline size_t LA32TraceHistory::GetCount() const noexcept
    {
        return count;
    }

    inline void LA32TraceHistory::SetDepth(size_t new_history_depth) noexcept
    {
        if (new_history_depth == history_depth)
            return;

        history_depth  = new_history_depth;

        auto newArray = _ModifyDepth(traces,
                                     capacity,
                                     count,
                                     round_pointer,
                                     new_history_depth,
                                     capacity,
                                     count);

        delete[] traces;

        traces = newArray;
    }

    inline LA32TraceEntity::Reference LA32TraceHistory::Get(size_t index) noexcept
    {
        if (capacity)
            return traces[(round_pointer + count - 1 - index) % capacity];
        else
            return LA32TraceEntity::Reference();
    }

    inline const LA32TraceEntity::Reference LA32TraceHistory::Get(size_t index) const noexcept
    {
        if (capacity)
            return traces[(round_pointer + count - 1 - index) % capacity];
        else
            return LA32TraceEntity::Reference();
    }

    inline void LA32TraceHistory::Append(const LA32TraceEntity::Reference& trace) noexcept
    {
        if (!traces)
            (traces = new LA32TraceEntity::Reference[count = capacity = 1])[0] = trace;
        else if (count == history_depth)
        {
            traces[round_pointer++] = trace;

            if (round_pointer == history_depth)
                round_pointer = 0;
        }
        else
        {
            if (count == capacity)
            {
                size_t newCapacity = std::min(capacity << 1, history_depth);

                LA32TraceEntity::Reference* newArray = new LA32TraceEntity::Reference[newCapacity];
                
                std::copy(traces, traces + capacity, newArray);
                delete[] traces;

                capacity = newCapacity;
                traces   = newArray;
            }

            traces[count++] = trace;
        }
    }

    inline void LA32TraceHistory::_Clear() noexcept
    {
        capacity        = 0;
        count           = 0;
        round_pointer   = 0;

        traces = nullptr;
    }

    inline void LA32TraceHistory::Clear() noexcept
    {
        if (traces)
            delete[] traces;

        _Clear();
    }

    inline LA32TraceEntity::Reference LA32TraceHistory::operator[](size_t index) noexcept
    {
        return Get(index);
    }

    inline const LA32TraceEntity::Reference LA32TraceHistory::operator[](size_t index) const noexcept
    {
        return Get(index);
    }

    inline LA32TraceHistory& LA32TraceHistory::operator=(const LA32TraceHistory& obj) noexcept
    {
        if (this != &obj)
        {
            if (traces)
                delete[] traces;

            history_depth   = obj.history_depth;
            capacity        = obj.capacity;
            count           = obj.count;
            round_pointer   = obj.round_pointer;

            if (obj.traces)
            {
                traces = new LA32TraceEntity::Reference[capacity];

                std::copy(obj.traces, obj.traces + capacity, traces);
            }
            else
                traces = nullptr;
        }

        return *this;
    }

    inline LA32TraceHistory& LA32TraceHistory::operator=(LA32TraceHistory&& obj) noexcept
    {
        if (this != &obj)
        {
            if (traces)
                delete[] traces;

            history_depth   = obj.history_depth;
            capacity        = obj.capacity;
            count           = obj.count;
            round_pointer   = obj.round_pointer;

            traces = obj.traces;

            obj._Clear();
        }        

        return *this;
    }
}



// Implementation of: class LA32TraceHistoryManagement::Pretouch
namespace Jasse::LA32TraceHistoryManagement {
    //
    // const size_t        size;
    //
    // LA32TraceHistory*   vector;
    //
    // size_t              default_depth;
    //

    inline Pretouch::Pretouch(size_t size, size_t default_depth) noexcept
        : size          (size)
        , vector        (new LA32TraceHistory[size])
        , default_depth (default_depth)
    {
        for (int i = 0; i < size; i++)
            vector[i].SetDepth(default_depth);
    }

    inline Pretouch::~Pretouch() noexcept
    {
        delete[] vector;
    }

    inline size_t Pretouch::GetDefaultDepth() const noexcept
    {
        return default_depth;
    }

    inline void Pretouch::SetDefaultDepth(size_t val) noexcept
    {
        default_depth = val;

        // *NOTICE: In fact, nothing other than the field 'default_depth' would be effected after this 
        //          operation because all the default history depth of LA32TraceHistory instances were 
        //          set on construction time for Pretouch Management.
    }
    
    inline std::optional<std::reference_wrapper<LA32TraceHistory>> Pretouch::Get(size_t address) noexcept
    {
        return { std::ref(vector[address]) };
    }

    inline std::optional<std::reference_wrapper<const LA32TraceHistory>> Pretouch::Get(size_t address) const noexcept
    {
        return { std::cref(vector[address]) };
    }

    inline void Pretouch::Set(size_t address, const LA32TraceHistory& obj) noexcept
    {
        vector[address] = obj;
    }

    inline void Pretouch::Set(size_t address, LA32TraceHistory&& obj) noexcept
    {
        vector[address] = std::move(obj);
    }

    inline bool Pretouch::SetIfExists(size_t address, const LA32TraceHistory& obj) noexcept
    {
        Set(address, obj);
        return true;
    }

    inline bool Pretouch::SetIfExists(size_t address, LA32TraceHistory&& obj) noexcept
    {
        Set(address, std::move(obj));
        return true;
    }

    constexpr bool Pretouch::SetIfAbsent(size_t address, const LA32TraceHistory& obj) noexcept
    {
        return false;
    }

    constexpr bool Pretouch::SetIfAbsent(size_t address, LA32TraceHistory&& obj) noexcept
    {
        return false;
    }

    inline bool Pretouch::SwapIfExists(size_t address, LA32TraceHistory& obj) noexcept
    {
        std::swap(vector[address], obj);
        return true;
    }

    inline LA32TraceHistory& Pretouch::Acquire(size_t address) noexcept
    {
        return vector[address];
    }
}



// Implementation of: class LA32TraceHistoryManagement::CompressedIncremental::Chunk
namespace Jasse::LA32TraceHistoryManagement {
    //
    // LA32TraceHistory*   vector;
    // size_t*             address_table;
    //
    // size_t              capacity_exponent;
    // size_t              count;
    //

    template<unsigned int _CompressRatio>
    inline CompressedIncremental<_CompressRatio>::Chunk::Chunk()
        : vector            (nullptr)
        , address_table     (nullptr)
        , capacity_exponent (0)
        , count             (0)
    { }

    template<unsigned int _CompressRatio>
    inline CompressedIncremental<_CompressRatio>::Chunk::~Chunk()
    {
        if (vector)
            delete[] vector;

        if (address_table)
            delete[] address_table;
    }

    template<unsigned int _CompressRatio>
    inline std::optional<size_t> CompressedIncremental<_CompressRatio>::Chunk::_Find(size_t address, size_t* slot_hint) const noexcept
    {
        if (!address_table)
            return std::nullopt;

        if (!count)
            return std::nullopt;

        // check pivot
        size_t pivot = !capacity_exponent ? 0 
            : (address & (std::numeric_limits<size_t>::max() >> ((sizeof(size_t) << 3) - capacity_exponent)));

        size_t lptr, rptr;

        if (pivot < count)
        {
            if (address_table[pivot] == address)
                return { pivot }; // direct hit

            // select side of pivot
            if (address_table[pivot] < address)
            {
                lptr = pivot + 1;
                rptr = count - 1;
            }
            else if (pivot)
            {
                lptr = 0;
                rptr = pivot - 1;
            }
            else
                return std::nullopt;
        }
        else
        {
            lptr = 0;
            rptr = count - 1;
        }

        // binary search on selected side of pivot
        while (lptr <= rptr)
        {
            pivot = (lptr + rptr) >> 1;

            if (address_table[pivot] == address)
                return { pivot };
            else if (address_table[pivot] < address)
                lptr = pivot + 1;
            else if (pivot)
                rptr = pivot - 1;
            else
                return std::nullopt;
        }

        if (slot_hint)
            *slot_hint = pivot;

        return std::nullopt;
    }

    template<unsigned int _CompressRatio>
    inline size_t CompressedIncremental<_CompressRatio>::Chunk::_FindSlot(size_t address, size_t slot_hint) const noexcept
    {
        if (!address_table)
            return 0;

        if (address_table[slot_hint] < address) // search right
        {
            if (slot_hint == count)
                return slot_hint;

            do { slot_hint++; } while (slot_hint < count && address_table[slot_hint] < address);
        }
        else // search left
        {
            if (slot_hint == 0)
                return slot_hint;

            do { slot_hint--; } while (slot_hint >= 0    && address_table[slot_hint] > address);

            slot_hint++; // compensation for left slot insertion
        }

        return slot_hint;
    }

    template<unsigned int _CompressRatio>
    inline void CompressedIncremental<_CompressRatio>::Chunk::_Initialize() noexcept
    {
        vector        = new LA32TraceHistory[1];
        address_table = new size_t[1];
    }

    template<unsigned int _CompressRatio>
    inline void CompressedIncremental<_CompressRatio>::Chunk::_Expand(size_t reserved_slot) noexcept
    {
        size_t capacity = 1 << capacity_exponent;

        // construct & move vector
        LA32TraceHistory* newVector = new LA32TraceHistory[capacity << 1];

        if (reserved_slot == 0)
            std::move(vector, vector + capacity, newVector + 1);
        else if (reserved_slot == capacity)
            std::move(vector, vector + capacity, newVector);
        else
        {
            std::move(vector, vector + reserved_slot, newVector);
            std::move(vector + reserved_slot, vector + capacity, newVector + reserved_slot + 1);
        }

        delete[] vector;
        vector = newVector;

        // construct & move address table
        size_t* newAddressTable = new size_t[capacity << 1];

        if (reserved_slot == 0)
            std::move(address_table, address_table + capacity, newAddressTable + 1);
        else if (reserved_slot == capacity)
            std::move(address_table, address_table + capacity, newAddressTable);
        else
        {
            std::move(address_table, address_table + reserved_slot, newAddressTable);
            std::move(address_table + reserved_slot, address_table + capacity, newAddressTable + reserved_slot + 1);
        }

        delete[] address_table;
        address_table = newAddressTable;

        capacity_exponent++;
    }

    template<unsigned int _CompressRatio>
    inline LA32TraceHistory& CompressedIncremental<_CompressRatio>::Chunk::_NewSlot(size_t address, size_t slot_hint) noexcept
    {
        size_t new_slot_index = _FindSlot(address, slot_hint);

        if (!address_table)
            _Initialize();
        else if (count == (1 << capacity_exponent))
            _Expand(new_slot_index);
        else if (new_slot_index != count)
        {
            std::move_backward(vector + new_slot_index, vector + count, vector + new_slot_index + 1);
            std::move_backward(address_table + new_slot_index, address_table + count, address_table + new_slot_index + 1);
        }

        address_table[new_slot_index] = address;

        return vector[new_slot_index];
    }

    template<unsigned int _CompressRatio>
    inline std::optional<std::reference_wrapper<LA32TraceHistory>> CompressedIncremental<_CompressRatio>::Chunk::Get(size_t address) noexcept
    {
        std::optional<size_t> index = _Find(address);

        if (index)
            return { std::ref(vector[*index]) };
        
        return std::nullopt;
    }

    template<unsigned int _CompressRatio>
    inline std::optional<std::reference_wrapper<const LA32TraceHistory>> CompressedIncremental<_CompressRatio>::Chunk::Get(size_t address) const noexcept
    {
        std::optional<size_t> index = _Find(address);

        if (index)
            return { std::cref(vector[*index]) };

        return std::nullopt;
    }

    template<unsigned int _CompressRatio>
    template<bool _EnableOnExists, bool _EnableOnAbsent, class _T>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::_Set(size_t address, _T&& obj) noexcept
    {
        size_t slot_hint = 0;

        std::optional<size_t> index = _Find(address, &slot_hint);

        if (!index)
        {
            if constexpr (_EnableOnAbsent)
                _NewSlot(address, slot_hint) = std::forward<_T>(obj);
            else
                return false;
        }
        else
        {
            if constexpr (_EnableOnExists)
                vector[*index] = std::forward<_T>(obj);
            else
                return false;
        }

        return true;
    }

    template<unsigned int _CompressRatio>
    inline void CompressedIncremental<_CompressRatio>::Chunk::Set(size_t address, const LA32TraceHistory& obj) noexcept
    {
        _Set<true, true>(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline void CompressedIncremental<_CompressRatio>::Chunk::Set(size_t address, LA32TraceHistory&& obj) noexcept
    {
        _Set<true, true>(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::SetIfExists(size_t address, const LA32TraceHistory& obj) noexcept
    {
        return _Set<true, false>(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::SetIfExists(size_t address, LA32TraceHistory&& obj) noexcept
    {
        return _Set<true, false>(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::SetIfAbsent(size_t address, const LA32TraceHistory& obj) noexcept
    {
        return _Set<false, true>(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::SetIfAbsent(size_t address, LA32TraceHistory&& obj) noexcept
    {
        return _Set<false, true>(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::SwapIfExists(size_t address, LA32TraceHistory& obj) noexcept
    {
        std::optional<size_t> index = _Find(address);

        if (!index)
            return false;

        std::swap(vector[*index], obj);
        return true;
    }

    template<unsigned int _CompressRatio>
    inline LA32TraceHistory& CompressedIncremental<_CompressRatio>::Chunk::Acquire(size_t address, size_t default_depth) noexcept
    {
        size_t slot_hint = 0;

        std::optional<size_t> index = _Find(address, &slot_hint);

        if (index)
            return vector[*index];
        else
        {
            LA32TraceHistory& obj = _NewSlot(address, slot_hint);

            obj.SetDepth(default_depth);
            return obj;
        }
    }
}


// Implementation of: class LA32TraceHistoryManagement::CompressIncremental
namespace Jasse::LA32TraceHistoryManagement {
    //
    // const size_t    max_size;
    //
    // const size_t    chunk_count;
    // Chunk*          chunks;
    //
    // size_t          default_depth;
    //

    template<unsigned int _CompressRatio>
    inline CompressedIncremental<_CompressRatio>::CompressedIncremental(size_t max_size, size_t default_depth) noexcept
        : max_size      (max_size)
        , chunk_count   ((max_size >> _CompressRatio) + 1)
        , chunks        (new Chunk[chunk_count])
        , default_depth (default_depth)
    { }

    template<unsigned int _CompressRatio>
    inline CompressedIncremental<_CompressRatio>::~CompressedIncremental() noexcept
    {
        delete[] chunks;
    }

    template<unsigned int _CompressRatio>
    inline size_t CompressedIncremental<_CompressRatio>::GetDefaultDepth() const noexcept
    {
        return default_depth;
    }

    template<unsigned int _CompressRatio>
    inline void CompressedIncremental<_CompressRatio>::SetDefaultDepth(size_t val) noexcept
    {
        default_depth = val;
    }

    template<unsigned int _CompressRatio>
    inline constexpr size_t CompressedIncremental<_CompressRatio>::_ToChunkAddress(size_t address) noexcept
    {
        return address >> _CompressRatio;
    }

    template<unsigned int _CompressRatio>
    inline constexpr size_t CompressedIncremental<_CompressRatio>::_ToAddressInChunk(size_t address) noexcept
    {
        return address;
        // return (address & (std::numeric_limits<size_t>::max() >> ((sizeof(size_t) << 3) - _CompressRatio)));
    }

    template<unsigned int _CompressRatio>
    inline std::optional<std::reference_wrapper<LA32TraceHistory>> CompressedIncremental<_CompressRatio>::Get(size_t address) noexcept
    {
        return chunks[_ToChunkAddress(address)].Get(_ToAddressInChunk(address));
    }

    template<unsigned int _CompressRatio>
    inline std::optional<std::reference_wrapper<const LA32TraceHistory>> CompressedIncremental<_CompressRatio>::Get(size_t address) const noexcept
    {
        return chunks[_ToChunkAddress(address)].Get(_ToAddressInChunk(address));
    }

    template<unsigned int _CompressRatio>
    inline void CompressedIncremental<_CompressRatio>::Set(size_t address, const LA32TraceHistory& obj) noexcept
    {
        chunks[_ToChunkAddress(address)].Set(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline void CompressedIncremental<_CompressRatio>::Set(size_t address, LA32TraceHistory&& obj) noexcept
    {
        chunks[_ToChunkAddress(address)].Set(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::SetIfExists(size_t address, const LA32TraceHistory& obj) noexcept
    {
        return chunks[_ToChunkAddress(address)].SetIfExists(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::SetIfExists(size_t address, LA32TraceHistory&& obj) noexcept
    {
        return chunks[_ToChunkAddress(address)].SetIfExists(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::SetIfAbsent(size_t address, const LA32TraceHistory& obj) noexcept
    {
        return chunks[_ToChunkAddress(address)].SetIfAbsent(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::SetIfAbsent(size_t address, LA32TraceHistory&& obj) noexcept
    {
        return chunks[_ToChunkAddress(address)].SetIfAbsent(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::SwapIfExists(size_t address, LA32TraceHistory& obj) noexcept
    {
        return chunks[_ToChunkAddress(address)].SwapIfExists(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline LA32TraceHistory& CompressedIncremental<_CompressRatio>::Acquire(size_t address) noexcept
    {
        return chunks[_ToChunkAddress(address)].Acquire(address, default_depth);
    }
}



// Implementation of: class LA32PCTraceSubtrate
namespace Jasse {
    // 
    // LA32TraceHistory              traces;
    //

    inline LA32PCTracerSubtrate::LA32PCTracerSubtrate(size_t default_depth) noexcept
        : traces        (default_depth)
    { }

    inline LA32PCTracerSubtrate::~LA32PCTracerSubtrate() noexcept
    { }

    inline size_t LA32PCTracerSubtrate::GetDefaultDepth() const noexcept
    {
        return traces.GetDepth();
    }

    inline void LA32PCTracerSubtrate::SetDefaultDepth(size_t depth) noexcept
    {
        traces.SetDepth(depth);
    }

    inline LA32TraceHistory& LA32PCTracerSubtrate::Get() noexcept
    {
        return traces;
    }

    inline const LA32TraceHistory& LA32PCTracerSubtrate::Get() const noexcept
    {
        return traces;
    }

    inline void LA32PCTracerSubtrate::Set(const LA32TraceHistory& obj) noexcept
    {
        traces = obj;
    }

    inline void LA32PCTracerSubtrate::Set(LA32TraceHistory&& obj) noexcept
    {
        traces = std::move(obj);
    }

    inline void LA32PCTracerSubtrate::Swap(LA32TraceHistory& obj) noexcept
    {
        std::swap(traces, obj);
    }
}


// Implementation of: class LA32GPRTracerSubtrate
namespace Jasse {
    //
    // mutable _HistoryManager  manager;
    //

    template<LA32TraceHistoryManager _HistoryManager>
    inline LA32GPRTracerSubtrate<_HistoryManager>::LA32GPRTracerSubtrate(size_t default_depth) noexcept
        : manager   (SIZE, default_depth)
    { }

    template<LA32TraceHistoryManager _HistoryManager>
    inline LA32GPRTracerSubtrate<_HistoryManager>::~LA32GPRTracerSubtrate() noexcept
    { }

    template<LA32TraceHistoryManager _HistoryManager>
    inline size_t LA32GPRTracerSubtrate<_HistoryManager>::GetDefaultDepth() const noexcept
    {
        return manager.GetDefaultDepth();
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline void LA32GPRTracerSubtrate<_HistoryManager>::SetDefaultDepth(size_t depth) noexcept
    {
        manager.SetDefaultDepth(depth);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline constexpr size_t LA32GPRTracerSubtrate<_HistoryManager>::GetSize() const noexcept
    {
        return SIZE;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline constexpr bool LA32GPRTracerSubtrate<_HistoryManager>::CheckBound(size_t index) const noexcept
    {
        return index >= 0 && index < SIZE;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline LA32TraceHistory& LA32GPRTracerSubtrate<_HistoryManager>::Get(size_t index) noexcept
    {
        return manager.Acquire(index);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline const LA32TraceHistory& LA32GPRTracerSubtrate<_HistoryManager>::Get(size_t index) const noexcept
    {
        return manager.Acquire(index);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline void LA32GPRTracerSubtrate<_HistoryManager>::Set(size_t index, const LA32TraceHistory& obj) noexcept
    {
        manager.Set(index, obj);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline void LA32GPRTracerSubtrate<_HistoryManager>::Set(size_t index, LA32TraceHistory&& obj) noexcept
    {
        manager.Set(index, std::move(obj));
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline void LA32GPRTracerSubtrate<_HistoryManager>::Swap(size_t index, LA32TraceHistory& obj) noexcept
    {
        if (!manager.SwapIfExists(index, obj))
            std::swap(manager.Acquire(index), obj);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline LA32TraceHistory& LA32GPRTracerSubtrate<_HistoryManager>::operator[](size_t index) noexcept
    {
        return Get(index);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline const LA32TraceHistory& LA32GPRTracerSubtrate<_HistoryManager>::operator[](size_t index) const noexcept
    {
        return Get(index);
    }
}


// Implementation of: class LA32MemoryTracerSubtrate
namespace Jasse {
    //
    // const size_t            size;
    //
    // mutable _HistoryManager manager;
    //
    // AddressRangeMapper      address_range_mapper;
    //

    template<LA32TraceHistoryManager _HistoryManager>
    inline LA32MemoryTracerSubtrate<_HistoryManager>::LA32MemoryTracerSubtrate(size_t size, size_t default_depth) noexcept
        : size                  (size)
        , manager               (size, default_depth)
        , address_range_mapper  (_DefaultAddressRangeMapper)
    { }

    template<LA32TraceHistoryManager _HistoryManager>
    inline LA32MemoryTracerSubtrate<_HistoryManager>::~LA32MemoryTracerSubtrate() noexcept
    { }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::_DefaultAddressRangeMapper(
        const LA32MemoryTracerSubtrate<_HistoryManager>& obj, size_t& address) noexcept
    {
        return address >= 0 && address <= obj.GetSize();
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline size_t LA32MemoryTracerSubtrate<_HistoryManager>::GetDefaultDepth() const noexcept
    {
        return manager.GetDefaultDepth();
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline void LA32MemoryTracerSubtrate<_HistoryManager>::SetDefaultDepth(size_t depth) noexcept
    {
        manager.SetDefaultDepth(depth);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline size_t LA32MemoryTracerSubtrate<_HistoryManager>::GetSize() const noexcept
    {
        return size;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::CheckBound(size_t address) const noexcept
    {
        return address_range_mapper(*this, address);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline std::optional<std::reference_wrapper<LA32TraceHistory>> LA32MemoryTracerSubtrate<_HistoryManager>::Get(size_t address) noexcept
    {
        if (!address_range_mapper(*this, address))
            return std::nullopt;

        auto __from_get = manager.Get(address);
        return __from_get ? std::optional<std::reference_wrapper<LA32TraceHistory>>(std::ref(*__from_get)) : std::nullopt;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline std::optional<std::reference_wrapper<const LA32TraceHistory>> LA32MemoryTracerSubtrate<_HistoryManager>::Get(size_t address) const noexcept
    {
        if (!address_range_mapper(*this, address))
            return std::nullopt;

        auto __from_const_get = std::as_const(manager).Get(address);
        return __from_const_get ? std::optional<std::reference_wrapper<const LA32TraceHistory>>(std::cref(*__from_const_get)) : std::nullopt;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline LA32TraceHistory& LA32MemoryTracerSubtrate<_HistoryManager>::Acquire(size_t address) noexcept
    {
        address_range_mapper(*this, address);
        return manager.Acquire(address);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline const LA32TraceHistory& LA32MemoryTracerSubtrate<_HistoryManager>::Acquire(size_t address) const noexcept
    {
        address_range_mapper(*this, address);
        return manager.Acquire(address);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline std::optional<std::reference_wrapper<LA32TraceHistory>> LA32MemoryTracerSubtrate<_HistoryManager>::AcquireInBound(size_t address) noexcept
    {
        if (!address_range_mapper(*this, address))
            return std::nullopt;

        return Acquire(address);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline std::optional<std::reference_wrapper<const LA32TraceHistory>> LA32MemoryTracerSubtrate<_HistoryManager>::AcquireInBound(size_t address) const noexcept
    {
        if (!address_range_mapper(*this, address))
            return std::nullopt;

        return Acquire(address);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::Set(size_t address, const LA32TraceHistory& obj) noexcept
    {
        if (!address_range_mapper(*this, address))
            return false;

        manager.Set(address, obj);
        return true;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::Set(size_t address, LA32TraceHistory&& obj) noexcept
    {
        if (!address_range_mapper(*this, address))
            return false;
        
        manager.Set(address, std::move(obj));
        return true;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::SetIfExists(size_t address, const LA32TraceHistory& obj) noexcept
    {
        if (!address_range_mapper(*this, address))
            return false;

        return manager.SetIfExists(address, obj);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::SetIfExists(size_t address, LA32TraceHistory&& obj) noexcept
    {
        if (!address_range_mapper(*this, address))
            return false;

        return manager.SetIfExists(address, std::move(obj));
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::SetIfAbsent(size_t address, const LA32TraceHistory& obj) noexcept
    {
        if (!address_range_mapper(*this, address))
            return false;

        return manager.SetIfAbsent(address, obj);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::SetIfAbsent(size_t address, LA32TraceHistory&& obj) noexcept
    {
        if (!address_range_mapper(*this, address))
            return false;
        
        return manager.SetIfAbsent(address, std::move(obj));
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline bool LA32MemoryTracerSubtrate<_HistoryManager>::SwapIfExists(size_t address, LA32TraceHistory& obj) noexcept
    {
        if (!address_range_mapper(*this, address))
            return false;

        return manager.SwapIfExists(address, obj);
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline LA32MemoryTracerSubtrate<_HistoryManager>::AddressRangeMapper& LA32MemoryTracerSubtrate<_HistoryManager>::GetAddressRangeMapper() noexcept
    {
        return address_range_mapper;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline const LA32MemoryTracerSubtrate<_HistoryManager>::AddressRangeMapper& LA32MemoryTracerSubtrate<_HistoryManager>::GetAddressRangeMapper() const noexcept
    {
        return address_range_mapper;
    }

    template<LA32TraceHistoryManager _HistoryManager>
    inline void LA32MemoryTracerSubtrate<_HistoryManager>::SetAddressRangeMapper(const AddressRangeMapper& mapper) noexcept
    {
        address_range_mapper = mapper;
    }
}
