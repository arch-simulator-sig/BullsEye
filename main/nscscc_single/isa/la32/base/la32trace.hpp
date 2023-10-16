#pragma once
//
// LA32 (NSCSCC) ISA Emulator (Jasse)
//
// Trace Subsystem Infrastructures
//

#ifndef __HEADER_JASSE_LA32__BASE_TRACE
#define __HEADER_JASSE_LA32__BASE_TRACE

#include <string_view>
#include <concepts>
#include <memory>
#include <algorithm>
#include <bitset>
#include <optional>
#include <functional>
#include <utility>
#include <limits>
#include <stdexcept>
#include <cstdint>

#include "la32def.hpp"
#include "la32decode.hpp"

#include "common/util.hpp"
#include "common/objpool.hpp"


#define CERR_JE3001             "JE-3001: The dedicated type _TContent is too large for LA32TraceEntity to hold"


// Trace Base
namespace Jasse {

    // LA32 Trace Entity
    class LA32TraceEntity {
    public:
        typedef struct {
            uint32_t    dword0;
            uint32_t    dword1;
            uint32_t    dword2;
            uint32_t    dword3;
            uint32_t    dword4;
            uint32_t    dword5;
        } Content;

        template<class _TContent>
        class ContentTypeBase {
        public:
            using TContent              = _TContent;

        private:
            const std::string_view  name;

        private:
            static void                 __STATIC_ASSERT_PLACEHOLDER()
            { static_assert(sizeof(_TContent) <= sizeof(Content), CERR_JE3001); }

        public:
            ContentTypeBase(const char* name) noexcept;

            const std::string_view&     GetName() const noexcept;

            virtual void                Finalize(LA32TraceEntity& entity) const noexcept;
        };

    public:
        struct Initializer {
            void operator()(LA32TraceEntity& entity) const noexcept;
        };

        struct Finalizer {
            void operator()(LA32TraceEntity& entity) const noexcept;
        };

    public:
        using Pool              = BullsEye::RoundRobinObjectPool<LA32TraceEntity, Initializer, Finalizer>;
        using Reference         = BullsEye::RoundRobinObjectPool<LA32TraceEntity, Initializer, Finalizer>::Reference;

        template<class _T>
        using ContentType       = ContentTypeBase<_T>*;

    private:
        ContentType<Content>    contentType;
        Content                 content;

        Reference               parent0;
        Reference               parent1;
        Reference               parent2;

    public:
        LA32TraceEntity() noexcept;
        LA32TraceEntity(const LA32TraceEntity& obj) noexcept;
        LA32TraceEntity(LA32TraceEntity&& obj) noexcept;

        ~LA32TraceEntity() noexcept;

        ContentType<Content>        GetContentType() const noexcept;
        Content&                    GetContent() noexcept;
        const Content&              GetContent() const noexcept;

        template<class _TContent>
        _TContent&                  ReinterpretContent() noexcept;

        template<class _TContent>
        const _TContent&            ReinterpretContent() const noexcept;

        template<class _TContent>
        std::optional<std::reference_wrapper<_TContent>> 
                                    GetContent(ContentType<_TContent> type) noexcept;

        template<class _TContent>
        std::optional<std::reference_wrapper<const _TContent>>
                                    GetContent(ContentType<_TContent> type) const noexcept;

        template<class _TContent>
        void                        SetContent(ContentType<_TContent> type, const _TContent& content) noexcept;

        template<class _TContent>
        _TContent&                  SetContentType(ContentType<_TContent> type) noexcept;

        void                        SetFirstParent(const Reference& trace) noexcept;
        void                        SetSecondParent(const Reference& trace) noexcept;
        void                        SetThirdParent(const Reference& trace) noexcept;

        Reference&                  GetFirstParent() noexcept;
        const Reference&            GetFirstParent() const noexcept;
        Reference&                  GetSecondParent() noexcept;
        const Reference&            GetSecondParent() const noexcept;
        Reference&                  GetThirdParent() noexcept;
        const Reference&            GetThirdParent() const noexcept;
    };


    // LA32 Trace Content - Instruction Execution
    struct LA32TracedInstructionExecution {
    public:
        pc_t                pc;
        arch32_t            value;

        LA32Instruction     insn;
        

    public:
        static void                                 SetTracedFetch(LA32TraceEntity& entity, const LA32TraceEntity::Reference& trace) noexcept;
        static LA32TraceEntity::Reference&          GetTracedFetch(LA32TraceEntity& entity) noexcept;
        static const LA32TraceEntity::Reference&    GetTracedFetch(const LA32TraceEntity& entity) noexcept;

        static void                                 SetTracedFirstOperand(LA32TraceEntity& entity, const LA32TraceEntity::Reference& trace) noexcept;
        static LA32TraceEntity::Reference&          GetTracedFirstOperand(LA32TraceEntity& entity) noexcept;
        static const LA32TraceEntity::Reference&    GetTracedFirstOperand(const LA32TraceEntity& entity) noexcept;

        static void                                 SetTracedSecondOperand(LA32TraceEntity& entity, const LA32TraceEntity::Reference& trace) noexcept;
        static LA32TraceEntity::Reference&          GetTracedSecondOperand(LA32TraceEntity& entity) noexcept;
        static const LA32TraceEntity::Reference&    GetTracedSecondOperand(const LA32TraceEntity& entity) noexcept;
    };

    using LA32TracedInstructionExecutionTypeInstance    = LA32TraceEntity::ContentTypeBase<LA32TracedInstructionExecution>;
    using LA32TracedInstructionExecutionType            = LA32TraceEntity::ContentType<LA32TracedInstructionExecution>;


    // LA32 Trace Content - Instruction Fetch
    struct LA32TracedInstructionFetch {
    public:
        pc_t                pc;
        insnraw_t           insn;

    public:
        static void                                 SetTracedAddressSource(LA32TraceEntity& entity, const LA32TraceEntity::Reference& trace) noexcept;
        static LA32TraceEntity::Reference&          GetTracedAddressSource(LA32TraceEntity& entity) noexcept;
        static const LA32TraceEntity::Reference&    GetTracedAddressSource(const LA32TraceEntity& entity) noexcept;

        static void                                 SetTracedMemorySource(LA32TraceEntity& entity, const LA32TraceEntity::Reference& trace) noexcept;
        static LA32TraceEntity::Reference&          GetTracedMemorySource(LA32TraceEntity& entity) noexcept;
        static const LA32TraceEntity::Reference&    GetTracedMemorySource(const LA32TraceEntity& entity) noexcept;
    };

    using LA32TracedInstructionFetchTypeInstance        = LA32TraceEntity::ContentTypeBase<LA32TracedInstructionFetch>;
    using LA32TracedInstructionFetchType                = LA32TraceEntity::ContentType<LA32TracedInstructionFetch>;

    
    // LA32 Trace Content - Normal Event Modification
    class LA32TracedNormalEventModification {
    public:
        arch32_t            value;
    
    private:
        char*               eventName;
        char*               message;

    public:
        LA32TracedNormalEventModification() noexcept;
        LA32TracedNormalEventModification(const LA32TracedNormalEventModification& obj) noexcept;
        LA32TracedNormalEventModification(LA32TracedNormalEventModification&& obj) noexcept;
        ~LA32TracedNormalEventModification() noexcept;

        char*               GetEventName() noexcept;
        const char*         GetEventName() const noexcept;
        char*               GetMessage() noexcept;
        const char*         GetMessage() const noexcept;

        void                SetEventName(const char* eventName) noexcept;
        void                SetMessage(const char* message) noexcept;
    };

    class LA32TracedNormalEventModificationTypeInstance
        : public LA32TraceEntity::ContentTypeBase<LA32TracedNormalEventModification> {
    public:
        LA32TracedNormalEventModificationTypeInstance(const char* name) noexcept;

        virtual void        Finalize(LA32TraceEntity& entity) const noexcept override;
    };

    using LA32TracedNormalEventModificationType     = LA32TracedNormalEventModificationTypeInstance*;


    // LA32 Trace Content - Normal Attached Message
    class LA32TracedNormalAttachedMessage {
    private:
        char*               messageAbstract;
        char*               messageDetail;

    public:
        LA32TracedNormalAttachedMessage() noexcept;
        LA32TracedNormalAttachedMessage(const LA32TracedNormalAttachedMessage& obj) noexcept;
        LA32TracedNormalAttachedMessage(LA32TracedNormalAttachedMessage&& obj) noexcept;
        ~LA32TracedNormalAttachedMessage() noexcept;

        char*               GetMessageAbstract() noexcept;
        const char*         GetMessageAbstract() const noexcept;
        char*               GetMessageDetail() noexcept;
        const char*         GetMessageDetail() const noexcept;

        void                SetMessageAbstract(const char* messageAbstract) noexcept;
        void                SetMessageDetail(const char* messageDetail) noexcept;
    };

    class LA32TracedNormalAttachedMessageTypeInstance 
        : public LA32TraceEntity::ContentTypeBase<LA32TracedNormalAttachedMessage> {
    public:
        LA32TracedNormalAttachedMessageTypeInstance(const char* name) noexcept;

        virtual void        Finalize(LA32TraceEntity& entity) const noexcept override;
    };

    using LA32TracedNormalAttachedMessageType       = LA32TracedNormalAttachedMessageTypeInstance;


    // LA32 Legacy Trace Content Type
    struct LA32TraceContentLegacyType {
    public:
        static const LA32TraceEntity::ContentType<LA32TracedInstructionExecution>       INSTRUCTION_EXECUTION;

        static const LA32TraceEntity::ContentType<LA32TracedInstructionFetch>           INSTRUCTION_FETCH;

        static const LA32TraceEntity::ContentType<LA32TracedNormalEventModification>    NORMAL_EVENT_MODIFICATION;

        static const LA32TraceEntity::ContentType<LA32TracedNormalAttachedMessage>      NORMAL_ATTACHED_MESSAGE;
    };


    // LA32 Trace Entity History Collection
    class LA32TraceHistory {
    private:       
        size_t                          history_depth;

        size_t                          capacity;
        size_t                          count;
        size_t                          round_pointer;

        LA32TraceEntity::Reference*     traces;

    private:
        static LA32TraceEntity::Reference*  _ModifyDepth(LA32TraceEntity::Reference* const  src,
                                                         size_t                             src_capacity,
                                                         size_t                             src_count,
                                                         size_t                             src_round_pointer,
                                                         size_t                             new_history_depth,
                                                         size_t&                            new_capacity,
                                                         size_t&                            new_count) noexcept;

        void                                _Clear() noexcept;

    public:
        LA32TraceHistory(size_t history_depth = 1) noexcept;
        LA32TraceHistory(const LA32TraceHistory& obj) noexcept;
        LA32TraceHistory(const LA32TraceHistory& obj, size_t new_history_depth) noexcept;
        LA32TraceHistory(LA32TraceHistory&& obj) noexcept;
        ~LA32TraceHistory() noexcept;

        size_t                              GetDepth() const noexcept;
        size_t                              GetCount() const noexcept;

        void                                SetDepth(size_t new_history_depth) noexcept;

        LA32TraceEntity::Reference          Get(size_t index = 0) noexcept;
        const LA32TraceEntity::Reference    Get(size_t index = 0) const noexcept;

        void                                Append(const LA32TraceEntity::Reference& trace) noexcept;

        void                                Clear() noexcept;

        LA32TraceEntity::Reference          operator[](size_t index) noexcept;
        const LA32TraceEntity::Reference    operator[](size_t index) const noexcept;

        LA32TraceHistory&                   operator=(const LA32TraceHistory& obj) noexcept;
        LA32TraceHistory&                   operator=(LA32TraceHistory&& obj) noexcept;
    };
}


// Trace Memory Management (manager concepts)
namespace Jasse {

    template<class T>
    concept LA32TraceHistoryManager = requires (T x, const T c,
        size_t                  size,
        size_t                  default_depth,
        size_t                  address,
        LA32TraceHistory&       robj,
        const LA32TraceHistory& crobj,
        LA32TraceHistory&&      rrobj) 
    {
        // ::(size_t size, size_t default_depth)
        { T(size, default_depth) } noexcept;

        // ::GetDefaultDepth()
        { x.GetDefaultDepth() } noexcept -> std::convertible_to<size_t>;
        { c.GetDefaultDepth() } noexcept -> std::convertible_to<size_t>;

        // ::SetDefaultDepth(size_t)
        { x.SetDefaultDepth(default_depth) } noexcept;

        // ::Get(size_t)
        { (bool) x.Get(address) } noexcept;
        { (bool) c.Get(address) } noexcept;
        { *(x.Get(address)) } noexcept -> std::convertible_to<LA32TraceHistory&>;
        { *(c.Get(address)) } noexcept -> std::convertible_to<const LA32TraceHistory&>;

        // ::Set(size_t, &&...)
        { x.Set(address, crobj) } noexcept;
        { x.Set(address, rrobj) } noexcept;

        // ::SetIfExists(size_t, &&...)
        { x.SetIfExists(address, crobj) } noexcept -> std::convertible_to<bool>;
        { x.SetIfExists(address, rrobj) } noexcept -> std::convertible_to<bool>;

        // ::SetIfAbsent(size_t, &&...)
        { x.SetIfAbsent(address, crobj) } noexcept -> std::convertible_to<bool>;
        { x.SetIfAbsent(address, rrobj) } noexcept -> std::convertible_to<bool>;

        // ::SwapIfExists(size_t, LA32TraceHistory&)
        { x.SwapIfExists(address, robj) } noexcept -> std::convertible_to<bool>;

        // ::Acquire(size_t)
        { x.Acquire(address) } noexcept -> std::convertible_to<LA32TraceHistory&>;
    };
}

// Trace Memory Management
namespace Jasse::LA32TraceHistoryManagement {

    class Pretouch
    {
    private:
        const size_t        size;

        LA32TraceHistory*   vector;

        size_t              default_depth;

    public:
        Pretouch(const Pretouch& obj) = delete;
        Pretouch(Pretouch&& obj) = delete;
        Pretouch(size_t size, size_t default_depth = 1) noexcept;
        ~Pretouch() noexcept;

        size_t                      GetDefaultDepth() const noexcept;
        void                        SetDefaultDepth(size_t val) noexcept;

        std::optional<std::reference_wrapper<LA32TraceHistory>>         Get(size_t address) noexcept;
        std::optional<std::reference_wrapper<const LA32TraceHistory>>   Get(size_t address) const noexcept;

        void                        Set(size_t address, const LA32TraceHistory& obj) noexcept;
        void                        Set(size_t address, LA32TraceHistory&& obj) noexcept;
        bool                        SetIfExists(size_t address, const LA32TraceHistory& obj) noexcept;
        bool                        SetIfExists(size_t address, LA32TraceHistory&& obj) noexcept;
        constexpr bool              SetIfAbsent(size_t address, const LA32TraceHistory& obj) noexcept;
        constexpr bool              SetIfAbsent(size_t address, LA32TraceHistory&& obj) noexcept;

        bool                        SwapIfExists(size_t address, LA32TraceHistory& obj) noexcept;

        LA32TraceHistory&           Acquire(size_t address) noexcept;

        void                        operator=(const Pretouch& obj) = delete;
        void                        operator=(Pretouch&& obj) = delete;
    };


    template<unsigned int _CompressRatio = 6>
    class CompressedIncremental
    {
    private:
        class Chunk {
        private:
            LA32TraceHistory*       vector;
            size_t*                 address_table;

            size_t                  capacity_exponent;
            size_t                  count;

        private:
            std::optional<size_t>       _Find(size_t address, size_t* slot_hint = nullptr) const noexcept;
            size_t                      _FindSlot(size_t address, size_t slot_hint = 0) const noexcept;
           
            void                        _Initialize() noexcept;
            void                        _Expand(size_t reserved_slot) noexcept;

            LA32TraceHistory&           _NewSlot(size_t address, size_t slot_hint) noexcept;

            template<bool _EnableOnExists, bool _EnableOnAbsent, class _T>
            bool                        _Set(size_t address, _T&& obj) noexcept;

        public: 
            Chunk();
            ~Chunk();

            std::optional<std::reference_wrapper<LA32TraceHistory>>         Get(size_t address) noexcept;
            std::optional<std::reference_wrapper<const LA32TraceHistory>>   Get(size_t address) const noexcept;

            void                        Set(size_t address, const LA32TraceHistory& obj) noexcept;
            void                        Set(size_t address, LA32TraceHistory&& obj) noexcept;
            bool                        SetIfExists(size_t address, const LA32TraceHistory& obj) noexcept;
            bool                        SetIfExists(size_t address, LA32TraceHistory&& obj) noexcept;
            bool                        SetIfAbsent(size_t address, const LA32TraceHistory& obj) noexcept;
            bool                        SetIfAbsent(size_t address, LA32TraceHistory&& obj) noexcept;

            bool                        SwapIfExists(size_t address, LA32TraceHistory& obj) noexcept;

            LA32TraceHistory&           Acquire(size_t address, size_t default_depth) noexcept;
        };

    private:
        const size_t    max_size;

        const size_t    chunk_count;
        Chunk*          chunks;

        size_t          default_depth;

    private:
        static constexpr size_t     _ToChunkAddress(size_t address) noexcept;
        static constexpr size_t     _ToAddressInChunk(size_t address) noexcept;

    public:
        CompressedIncremental(const CompressedIncremental& obj) = delete;
        CompressedIncremental(CompressedIncremental&& obj) = delete;
        CompressedIncremental(size_t max_size, size_t default_depth = 1) noexcept;
        ~CompressedIncremental() noexcept;

        size_t                      GetDefaultDepth() const noexcept;
        void                        SetDefaultDepth(size_t val) noexcept;

        std::optional<std::reference_wrapper<LA32TraceHistory>>         Get(size_t address) noexcept;
        std::optional<std::reference_wrapper<const LA32TraceHistory>>   Get(size_t address) const noexcept;

        void                        Set(size_t address, const LA32TraceHistory& obj) noexcept;
        void                        Set(size_t address, LA32TraceHistory&& obj) noexcept;
        bool                        SetIfExists(size_t address, const LA32TraceHistory& obj) noexcept;
        bool                        SetIfExists(size_t address, LA32TraceHistory&& obj) noexcept;
        bool                        SetIfAbsent(size_t address, const LA32TraceHistory& obj) noexcept;
        bool                        SetIfAbsent(size_t address, LA32TraceHistory&& obj) noexcept;

        bool                        SwapIfExists(size_t address, LA32TraceHistory& obj) noexcept;

        LA32TraceHistory&           Acquire(size_t address) noexcept;

        void                        operator=(const CompressedIncremental& obj) = delete;
        void                        operator=(CompressedIncremental&& obj) = delete;
    };
}


// Specialized Tracers
namespace Jasse {

    // LA32 PC Tracer
    class LA32PCTracerSubtrate {
    private:
        LA32TraceHistory            traces;

    public:
        LA32PCTracerSubtrate(const LA32PCTracerSubtrate& obj) = delete;
        LA32PCTracerSubtrate(LA32PCTracerSubtrate&& obj) = delete;
        LA32PCTracerSubtrate(size_t default_depth) noexcept;
        ~LA32PCTracerSubtrate() noexcept;

        size_t                      GetDefaultDepth() const noexcept;
        void                        SetDefaultDepth(size_t depth) noexcept;

        LA32TraceHistory&           Get() noexcept;
        const LA32TraceHistory&     Get() const noexcept;

        void                        Set(const LA32TraceHistory& obj) noexcept;
        void                        Set(LA32TraceHistory&& obj) noexcept;

        void                        Swap(LA32TraceHistory& obj) noexcept;

        //
        LA32PCTracerSubtrate&       operator=(const LA32PCTracerSubtrate& obj) = delete;
        LA32PCTracerSubtrate&       operator=(LA32PCTracerSubtrate&& obj) = delete;;
    };


    // LA32 GPR Tracer
    template<LA32TraceHistoryManager _HistoryManager 
        = LA32TraceHistoryManagement::Pretouch>
    class LA32GPRTracerSubtrate {
    private:
        static constexpr size_t SIZE    = LA32_ARCH_REG_COUNT;

    private:
        mutable _HistoryManager manager;

    public:
        LA32GPRTracerSubtrate(const LA32GPRTracerSubtrate& obj) = delete;
        LA32GPRTracerSubtrate(LA32GPRTracerSubtrate&& obj) = delete;
        LA32GPRTracerSubtrate(size_t default_depth) noexcept;
        ~LA32GPRTracerSubtrate() noexcept;

        size_t                      GetDefaultDepth() const noexcept;
        void                        SetDefaultDepth(size_t depth) noexcept;

        constexpr size_t            GetSize() const noexcept;
        constexpr bool              CheckBound(size_t index) const noexcept;

        LA32TraceHistory&           Get(size_t index) noexcept;
        const LA32TraceHistory&     Get(size_t index) const noexcept;

        void                        Set(size_t index, const LA32TraceHistory& obj) noexcept;
        void                        Set(size_t index, LA32TraceHistory&& obj) noexcept;

        void                        Swap(size_t index, LA32TraceHistory& obj) noexcept;

        LA32TraceHistory&           operator[](size_t index) noexcept;
        const LA32TraceHistory&     operator[](size_t index) const noexcept;

        LA32GPRTracerSubtrate&      operator=(const LA32GPRTracerSubtrate& obj) = delete;
        LA32GPRTracerSubtrate&      operator=(LA32GPRTracerSubtrate&& obj) = delete;
    };
    

    // LA32 Memory Tracer
    template<LA32TraceHistoryManager _HistoryManager
        = LA32TraceHistoryManagement::CompressedIncremental<>>
    class LA32MemoryTracerSubtrate {
    public:
        using AddressRangeMapper    = std::function<bool(const LA32MemoryTracerSubtrate<_HistoryManager>&, size_t&)>;
    
    private:
        const size_t            size;

        mutable _HistoryManager manager;

        AddressRangeMapper      address_range_mapper;

    private:
        static bool                 _DefaultAddressRangeMapper(const LA32MemoryTracerSubtrate<_HistoryManager>&, size_t& address) noexcept;

    public:
        LA32MemoryTracerSubtrate(const LA32MemoryTracerSubtrate& obj) = delete;
        LA32MemoryTracerSubtrate(LA32MemoryTracerSubtrate&& obj) = delete;
        LA32MemoryTracerSubtrate(size_t size, size_t default_depth) noexcept;
        ~LA32MemoryTracerSubtrate() noexcept;

        size_t                      GetDefaultDepth() const noexcept;
        void                        SetDefaultDepth(size_t depth) noexcept;

        size_t                      GetSize() const noexcept;
        bool                        CheckBound(size_t address) const noexcept;

        std::optional<std::reference_wrapper<LA32TraceHistory>>         Get(size_t address) noexcept;
        std::optional<std::reference_wrapper<const LA32TraceHistory>>   Get(size_t address) const noexcept;

        LA32TraceHistory&           Acquire(size_t address) noexcept;
        const LA32TraceHistory&     Acquire(size_t address) const noexcept;

        std::optional<std::reference_wrapper<LA32TraceHistory>>         AcquireInBound(size_t address) noexcept;
        std::optional<std::reference_wrapper<const LA32TraceHistory>>   AcquireInBound(size_t address) const noexcept;

        bool                        Set(size_t address, const LA32TraceHistory& obj) noexcept;
        bool                        Set(size_t address, LA32TraceHistory&& obj) noexcept;
        bool                        SetIfExists(size_t address, const LA32TraceHistory& obj) noexcept;
        bool                        SetIfExists(size_t address, LA32TraceHistory&& obj) noexcept;
        bool                        SetIfAbsent(size_t address, const LA32TraceHistory& obj) noexcept;
        bool                        SetIfAbsent(size_t address, LA32TraceHistory&& obj) noexcept;

        bool                        SwapIfExists(size_t address, LA32TraceHistory& obj) noexcept;

        AddressRangeMapper&         GetAddressRangeMapper() noexcept;
        const AddressRangeMapper&   GetAddressRangeMapper() const noexcept;
        void                        SetAddressRangeMapper(const AddressRangeMapper& mapper) noexcept;

        LA32MemoryTracerSubtrate&   operator=(const LA32MemoryTracerSubtrate& obj) = delete;
        LA32MemoryTracerSubtrate&   operator=(LA32MemoryTracerSubtrate&& obj) = delete;
    };
}


#endif
