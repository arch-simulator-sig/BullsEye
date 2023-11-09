#include "la32trace.hpp"
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
// Trace Subsystem Infrastructures
//

#include AUTOINC_BE_COMMON(util.hpp)


// explicit instantiation
namespace Jasse {

    template<> class LA32GPRTracerSubtrate<LA32TraceHistoryManagement::Pretouch>;
    template<> class LA32GPRTracerSubtrate<LA32TraceHistoryManagement::CompressedIncremental<>>;

    template<> class LA32MemoryTracerSubtrate<LA32TraceHistoryManagement::Pretouch>;
    template<> class LA32MemoryTracerSubtrate<LA32TraceHistoryManagement::CompressedIncremental<>>;
}


// Implementation of: class LA32TraceEntity
namespace Jasse {
    /*
    ContentType<Content>    contentType;
    Content                 content;

    Reference               parent0;
    Reference               parent1;
    Reference               parent2;
    */

    LA32TraceEntity::LA32TraceEntity() noexcept
        : contentType   (nullptr)
        , content       ()
        , parent0       ()
        , parent1       ()
        , parent2       ()
    { }

    LA32TraceEntity::LA32TraceEntity(const LA32TraceEntity& obj) noexcept
        : contentType   (obj.contentType)
        , content       (obj.content)
        , parent0       (obj.parent0)
        , parent1       (obj.parent1)
        , parent2       (obj.parent2)
    { }

    LA32TraceEntity::LA32TraceEntity(LA32TraceEntity&& obj) noexcept
        : contentType   (obj.contentType)
        , content       (obj.content)
        , parent0       (obj.parent0)
        , parent1       (obj.parent1)
        , parent2       (obj.parent2)
    { }

    LA32TraceEntity::~LA32TraceEntity() noexcept
    { }

    LA32TraceEntity::ContentType<LA32TraceEntity::Content> LA32TraceEntity::GetContentType() const noexcept
    {
        return this->contentType;        
    }

    LA32TraceEntity::Content& LA32TraceEntity::GetContent() noexcept
    {
        return this->content;
    }

    const LA32TraceEntity::Content& LA32TraceEntity::GetContent() const noexcept
    {
        return this->content;
    }

    void LA32TraceEntity::SetFirstParent(const Reference& parent0) noexcept
    {
        this->parent0 = parent0;
    }

    void LA32TraceEntity::SetSecondParent(const Reference& parent1) noexcept
    {
        this->parent1 = parent1;
    }

    void LA32TraceEntity::SetThirdParent(const Reference& parent2) noexcept
    {
        this->parent2 = parent2;
    }

    LA32TraceEntity::Reference& LA32TraceEntity::GetFirstParent() noexcept
    {
        return parent0;
    }

    const LA32TraceEntity::Reference& LA32TraceEntity::GetFirstParent() const noexcept
    {
        return parent0;
    }

    LA32TraceEntity::Reference& LA32TraceEntity::GetSecondParent() noexcept
    {
        return parent1;
    }

    const LA32TraceEntity::Reference& LA32TraceEntity::GetSecondParent() const noexcept
    {
        return parent1;
    }

    LA32TraceEntity::Reference& LA32TraceEntity::GetThirdParent() noexcept
    {
        return parent2;
    }

    const LA32TraceEntity::Reference& LA32TraceEntity::GetThirdParent() const noexcept
    {
        return parent2;
    }
}


// Implementation of: struct LA32TraceEntity::Initializer
namespace Jasse {
    /*
    void operator()(LA32TraceEntity& entity) const noexcept;
    */

    void LA32TraceEntity::Initializer::operator()(LA32TraceEntity& entity) const noexcept
    { }
}


// Implementation of: struct LA32TraceEntity::Finalizer
namespace Jasse {
    /*
    void operator()(LA32TraceEntity& entity) const noexcept;
    */

    void LA32TraceEntity::Finalizer::operator()(LA32TraceEntity& entity) const noexcept
    { 
        entity.GetContentType()->Finalize(entity);
    }
}



// Implementation of: struct LA32TracedInstructionExecution
namespace Jasse {

    void LA32TracedInstructionExecution::SetTracedFetch(LA32TraceEntity& entity, const LA32TraceEntity::Reference& trace) noexcept
    {
        entity.SetFirstParent(trace);
    }

    LA32TraceEntity::Reference& LA32TracedInstructionExecution::GetTracedFetch(LA32TraceEntity& entity) noexcept
    {
        return entity.GetFirstParent();
    }

    const LA32TraceEntity::Reference& LA32TracedInstructionExecution::GetTracedFetch(const LA32TraceEntity& entity) noexcept
    {
        return entity.GetFirstParent();
    }

    void LA32TracedInstructionExecution::SetTracedFirstOperand(LA32TraceEntity& entity, const LA32TraceEntity::Reference& trace) noexcept
    {
        entity.SetSecondParent(trace);
    }

    LA32TraceEntity::Reference& LA32TracedInstructionExecution::GetTracedFirstOperand(LA32TraceEntity& entity) noexcept
    {
        return entity.GetSecondParent();
    }

    const LA32TraceEntity::Reference& LA32TracedInstructionExecution::GetTracedFirstOperand(const LA32TraceEntity& entity) noexcept
    {
        return entity.GetSecondParent();
    }

    void LA32TracedInstructionExecution::SetTracedSecondOperand(LA32TraceEntity& entity, const LA32TraceEntity::Reference& trace) noexcept
    {
        entity.SetThirdParent(trace);
    }

    LA32TraceEntity::Reference& LA32TracedInstructionExecution::GetTracedSecondOperand(LA32TraceEntity& entity) noexcept
    {
        return entity.GetThirdParent();
    }

    const LA32TraceEntity::Reference& LA32TracedInstructionExecution::GetTracedSecondOperand(const LA32TraceEntity& entity) noexcept
    {
        return entity.GetThirdParent();
    }
}



// Implementation of: struct LA32TracedInstructionFetch
namespace Jasse {

    void LA32TracedInstructionFetch::SetTracedAddressSource(LA32TraceEntity& entity, const LA32TraceEntity::Reference& trace) noexcept
    {
        entity.SetFirstParent(trace);
    }

    LA32TraceEntity::Reference& LA32TracedInstructionFetch::GetTracedAddressSource(LA32TraceEntity& entity) noexcept
    {
        return entity.GetFirstParent();
    }

    const LA32TraceEntity::Reference& LA32TracedInstructionFetch::GetTracedAddressSource(const LA32TraceEntity& entity) noexcept
    {
        return entity.GetFirstParent();
    }

    void LA32TracedInstructionFetch::SetTracedMemorySource(LA32TraceEntity& entity, const LA32TraceEntity::Reference& trace) noexcept
    {
        entity.SetSecondParent(trace);
    }

    LA32TraceEntity::Reference& LA32TracedInstructionFetch::GetTracedMemorySource(LA32TraceEntity& entity) noexcept
    {
        return entity.GetSecondParent();
    }

    const LA32TraceEntity::Reference& LA32TracedInstructionFetch::GetTracedMemorySource(const LA32TraceEntity& entity) noexcept
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

    LA32TracedNormalEventModification::LA32TracedNormalEventModification() noexcept
        : value         ()
        , eventName     (nullptr)
        , message       (nullptr)
    { }

    LA32TracedNormalEventModification::LA32TracedNormalEventModification(const LA32TracedNormalEventModification& obj) noexcept
        : value         (obj.value)
        , eventName     (obj.eventName  ? BullsEye::NewStringAndCopy(obj.eventName) : nullptr)
        , message       (obj.message    ? BullsEye::NewStringAndCopy(obj.message)   : nullptr)
    { }

    LA32TracedNormalEventModification::LA32TracedNormalEventModification(LA32TracedNormalEventModification&& obj) noexcept
        : value         (obj.value)
        , eventName     (obj.eventName)
        , message       (obj.message)
    {
        obj.eventName   = nullptr;
        obj.message     = nullptr;
    }

    LA32TracedNormalEventModification::~LA32TracedNormalEventModification() noexcept
    {
        if (eventName)
            delete[] eventName;

        if (message)
            delete[] message;
    }

    char* LA32TracedNormalEventModification::GetEventName() noexcept
    {
        return eventName;
    }

    const char* LA32TracedNormalEventModification::GetEventName() const noexcept
    {
        return eventName;
    }

    char* LA32TracedNormalEventModification::GetMessage() noexcept
    {
        return message;
    }

    const char* LA32TracedNormalEventModification::GetMessage() const noexcept
    {
        return message;
    }

    void LA32TracedNormalEventModification::SetEventName(const char* eventName) noexcept
    {
        if (this->eventName)
            delete[] this->eventName;

        this->eventName = eventName ? BullsEye::NewStringAndCopy(eventName) : nullptr;
    }

    void LA32TracedNormalEventModification::SetMessage(const char* message) noexcept
    {
        if (this->message)
            delete[] this->message;

        this->message = message ? BullsEye::NewStringAndCopy(message) : nullptr;
    }
}



// Implementation of: class LA32TracedNormalEventModificationTypeInstance
namespace Jasse {
    
    LA32TracedNormalEventModificationTypeInstance::LA32TracedNormalEventModificationTypeInstance(const char* name) noexcept
        : LA32TraceEntity::ContentTypeBase<LA32TracedNormalEventModification>(name)
    { }
    
    void LA32TracedNormalEventModificationTypeInstance::Finalize(LA32TraceEntity& entity) const noexcept
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

    LA32TracedNormalAttachedMessage::LA32TracedNormalAttachedMessage() noexcept
        : messageAbstract   (nullptr)
        , messageDetail     (nullptr)
    { }

    LA32TracedNormalAttachedMessage::LA32TracedNormalAttachedMessage(const LA32TracedNormalAttachedMessage& obj) noexcept
        : messageAbstract   (obj.messageAbstract ? BullsEye::NewStringAndCopy(obj.messageAbstract) : nullptr)
        , messageDetail     (obj.messageDetail   ? BullsEye::NewStringAndCopy(obj.messageDetail)   : nullptr)
    { }

    LA32TracedNormalAttachedMessage::LA32TracedNormalAttachedMessage(LA32TracedNormalAttachedMessage&& obj) noexcept
        : messageAbstract   (obj.messageAbstract)
        , messageDetail     (obj.messageDetail)
    {
        obj.messageAbstract = nullptr;
        obj.messageDetail   = nullptr;
    }

    LA32TracedNormalAttachedMessage::~LA32TracedNormalAttachedMessage() noexcept
    {
        if (messageAbstract)
            delete[] messageAbstract;

        if (messageDetail)
            delete[] messageDetail;
    }

    char* LA32TracedNormalAttachedMessage::GetMessageAbstract() noexcept
    {
        return messageAbstract;
    }

    const char* LA32TracedNormalAttachedMessage::GetMessageAbstract() const noexcept
    {
        return messageAbstract;
    }

    char* LA32TracedNormalAttachedMessage::GetMessageDetail() noexcept
    {
        return messageDetail;
    }

    const char* LA32TracedNormalAttachedMessage::GetMessageDetail() const noexcept
    {
        return messageDetail;
    }

    void LA32TracedNormalAttachedMessage::SetMessageAbstract(const char* messageAbstract) noexcept
    {
        if (this->messageAbstract)
            delete[] this->messageAbstract;

        this->messageAbstract = messageAbstract ? BullsEye::NewStringAndCopy(messageAbstract) : nullptr;
    }

    void LA32TracedNormalAttachedMessage::SetMessageDetail(const char* messageDetail) noexcept
    {
        if (this->messageDetail)
            delete[] this->messageDetail;

        this->messageDetail = messageDetail ? BullsEye::NewStringAndCopy(messageDetail) : nullptr;
    }
}


// Implementation of: class LA32TracedNormalAttachedMessageTypeInstance
namespace Jasse {

    LA32TracedNormalAttachedMessageTypeInstance::LA32TracedNormalAttachedMessageTypeInstance(const char* name) noexcept
        : LA32TraceEntity::ContentTypeBase<LA32TracedNormalAttachedMessage>(name)
    { }

    void LA32TracedNormalAttachedMessageTypeInstance::Finalize(LA32TraceEntity& entity) const noexcept
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

    LA32TraceHistory::LA32TraceHistory(size_t history_depth) noexcept
        : history_depth (history_depth)
        , capacity      (0)
        , count         (0)
        , round_pointer (0)
        , traces        (nullptr)
    { }

    LA32TraceHistory::LA32TraceHistory(const LA32TraceHistory& obj) noexcept
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

    LA32TraceHistory::LA32TraceHistory(const LA32TraceHistory& obj, size_t new_history_depth) noexcept
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

    LA32TraceHistory::LA32TraceHistory(LA32TraceHistory&& obj) noexcept
        : history_depth (obj.history_depth)
        , capacity      (obj.capacity)
        , count         (obj.count)
        , round_pointer (obj.round_pointer)
        , traces        (obj.traces)
    {
        obj._Clear();
    }

    LA32TraceHistory::~LA32TraceHistory() noexcept
    {
        if (traces)
            delete[] traces;
    }

    LA32TraceEntity::Reference* LA32TraceHistory::_ModifyDepth(
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

    size_t LA32TraceHistory::GetDepth() const noexcept
    {
        return history_depth;
    }

    size_t LA32TraceHistory::GetCount() const noexcept
    {
        return count;
    }

    void LA32TraceHistory::SetDepth(size_t new_history_depth) noexcept
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

    LA32TraceEntity::Reference LA32TraceHistory::Get(size_t index) noexcept
    {
        if (capacity)
            return traces[(round_pointer + count - 1 - index) % capacity];
        else
            return LA32TraceEntity::Reference();
    }

    const LA32TraceEntity::Reference LA32TraceHistory::Get(size_t index) const noexcept
    {
        if (capacity)
            return traces[(round_pointer + count - 1 - index) % capacity];
        else
            return LA32TraceEntity::Reference();
    }

    void LA32TraceHistory::Append(const LA32TraceEntity::Reference& trace) noexcept
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

    void LA32TraceHistory::_Clear() noexcept
    {
        capacity        = 0;
        count           = 0;
        round_pointer   = 0;

        traces = nullptr;
    }

    void LA32TraceHistory::Clear() noexcept
    {
        if (traces)
            delete[] traces;

        _Clear();
    }

    LA32TraceEntity::Reference LA32TraceHistory::operator[](size_t index) noexcept
    {
        return Get(index);
    }

    const LA32TraceEntity::Reference LA32TraceHistory::operator[](size_t index) const noexcept
    {
        return Get(index);
    }

    LA32TraceHistory& LA32TraceHistory::operator=(const LA32TraceHistory& obj) noexcept
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

    LA32TraceHistory& LA32TraceHistory::operator=(LA32TraceHistory&& obj) noexcept
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

    Pretouch::Pretouch(size_t size, size_t default_depth) noexcept
        : size          (size)
        , vector        (new LA32TraceHistory[size])
        , default_depth (default_depth)
    {
        for (int i = 0; i < size; i++)
            vector[i].SetDepth(default_depth);
    }

    Pretouch::~Pretouch() noexcept
    {
        delete[] vector;
    }

    size_t Pretouch::GetDefaultDepth() const noexcept
    {
        return default_depth;
    }

    void Pretouch::SetDefaultDepth(size_t val) noexcept
    {
        default_depth = val;

        // *NOTICE: In fact, nothing other than the field 'default_depth' would be effected after this 
        //          operation because all the default history depth of LA32TraceHistory instances were 
        //          set on construction time for Pretouch Management.
    }
    
    std::optional<std::reference_wrapper<LA32TraceHistory>> Pretouch::Get(size_t address) noexcept
    {
        return { std::ref(vector[address]) };
    }

    std::optional<std::reference_wrapper<const LA32TraceHistory>> Pretouch::Get(size_t address) const noexcept
    {
        return { std::cref(vector[address]) };
    }

    void Pretouch::Set(size_t address, const LA32TraceHistory& obj) noexcept
    {
        vector[address] = obj;
    }

    void Pretouch::Set(size_t address, LA32TraceHistory&& obj) noexcept
    {
        vector[address] = std::move(obj);
    }

    bool Pretouch::SetIfExists(size_t address, const LA32TraceHistory& obj) noexcept
    {
        Set(address, obj);
        return true;
    }

    bool Pretouch::SetIfExists(size_t address, LA32TraceHistory&& obj) noexcept
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

    bool Pretouch::SwapIfExists(size_t address, LA32TraceHistory& obj) noexcept
    {
        std::swap(vector[address], obj);
        return true;
    }

    LA32TraceHistory& Pretouch::Acquire(size_t address) noexcept
    {
        return vector[address];
    }
}



// Implementation of: class LA32PCTraceSubtrate
namespace Jasse {
    // 
    // LA32TraceHistory              traces;
    //

    LA32PCTracerSubtrate::LA32PCTracerSubtrate(size_t default_depth) noexcept
        : traces        (default_depth)
    { }

    LA32PCTracerSubtrate::~LA32PCTracerSubtrate() noexcept
    { }

    size_t LA32PCTracerSubtrate::GetDefaultDepth() const noexcept
    {
        return traces.GetDepth();
    }

    void LA32PCTracerSubtrate::SetDefaultDepth(size_t depth) noexcept
    {
        traces.SetDepth(depth);
    }

    LA32TraceHistory& LA32PCTracerSubtrate::Get() noexcept
    {
        return traces;
    }

    const LA32TraceHistory& LA32PCTracerSubtrate::Get() const noexcept
    {
        return traces;
    }

    void LA32PCTracerSubtrate::Set(const LA32TraceHistory& obj) noexcept
    {
        traces = obj;
    }

    void LA32PCTracerSubtrate::Set(LA32TraceHistory&& obj) noexcept
    {
        traces = std::move(obj);
    }

    void LA32PCTracerSubtrate::Swap(LA32TraceHistory& obj) noexcept
    {
        std::swap(traces, obj);
    }
}


// Implementation of: class LA32ExecutionTracerSubtrate
namespace Jasse {
    // 
    // LA32TraceHistory              traces;
    //

    LA32ExecutionTracerSubtrate::LA32ExecutionTracerSubtrate(size_t default_depth) noexcept
        : traces        (default_depth)
    { }

    LA32ExecutionTracerSubtrate::~LA32ExecutionTracerSubtrate() noexcept
    { }

    size_t LA32ExecutionTracerSubtrate::GetDefaultDepth() const noexcept
    {
        return traces.GetDepth();
    }

    void LA32ExecutionTracerSubtrate::SetDefaultDepth(size_t depth) noexcept
    {
        traces.SetDepth(depth);
    }

    LA32TraceHistory& LA32ExecutionTracerSubtrate::Get() noexcept
    {
        return traces;
    }

    const LA32TraceHistory& LA32ExecutionTracerSubtrate::Get() const noexcept
    {
        return traces;
    }

    void LA32ExecutionTracerSubtrate::Set(const LA32TraceHistory& obj) noexcept
    {
        traces = obj;
    }

    void LA32ExecutionTracerSubtrate::Set(LA32TraceHistory&& obj) noexcept
    {
        traces = std::move(obj);
    }

    void LA32ExecutionTracerSubtrate::Swap(LA32TraceHistory& obj) noexcept
    {
        std::swap(traces, obj);
    }
}
