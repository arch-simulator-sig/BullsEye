#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// Trace Subsystem Infrastructures
//

#include <concepts>
#include <memory>
#include <algorithm>
#include <bitset>
#include <optional>
#include <functional>
#include <utility>
#include <limits>
#include <stdexcept>

#include "mips32def.hpp"
#include "mips32decode.hpp"

#include "common/objpool.hpp"


// Trace Base
namespace Jasse {

    // MIPS32 Trace Entity
    class MIPS32TraceEntity {
    public:
        using Pool      = BullsEye::RoundRobinObjectPool<MIPS32TraceEntity>;
        using Reference = BullsEye::RoundRobinObjectPool<MIPS32TraceEntity>::Reference;

    private:
        MIPS32Instruction   insn;
        pc_t                pc;

        arch32_t            value;

        Reference           op0;
        Reference           op1;

    public:
        MIPS32TraceEntity(pc_t pc, const MIPS32Instruction& insn, arch32_t value) noexcept;
        MIPS32TraceEntity(pc_t pc, const MIPS32Instruction& insn, arch32_t value, const Reference& op0) noexcept;
        MIPS32TraceEntity(pc_t pc, const MIPS32Instruction& insn, arch32_t value, const Reference& op0, const Reference& op1) noexcept;

        void                        SetInstruction(const MIPS32Instruction& insn) noexcept;
        void                        SetPC(pc_t pc) noexcept;
        void                        SetValue(arch32_t value) noexcept;

        void                        SetFirstOperand(const Reference& trace) noexcept;
        void                        SetSecondOperand(const Reference& trace) noexcept;

        MIPS32Instruction&          GetInstruction() noexcept;
        const MIPS32Instruction&    GetInstruction() const noexcept;
        pc_t                        GetPC() const noexcept;
        arch32_t                    GetValue() const noexcept;

        Reference&                  GetFirstOperand() noexcept;
        const Reference&            GetFirstOperand() const noexcept;
        Reference&                  GetSecondOperand() noexcept;
        const Reference&            GetSecondOperand() const noexcept;
    };

    // MIPS32 Trace Entity History Collection
    class MIPS32TraceHistory {
    private:       
        size_t                          history_depth;

        size_t                          capacity;
        size_t                          count;
        size_t                          round_pointer;

        MIPS32TraceEntity::Reference*   traces;

    private:
        static MIPS32TraceEntity::Reference*  _ModifyDepth(MIPS32TraceEntity::Reference* const  src,
                                                           size_t                               src_capacity,
                                                           size_t                               src_count,
                                                           size_t                               src_round_pointer,
                                                           size_t                               new_history_depth,
                                                           size_t&                              new_capacity,
                                                           size_t&                              new_count) noexcept;

        void                                _Clear() noexcept;

    public:
        MIPS32TraceHistory(size_t history_depth = 1) noexcept;
        MIPS32TraceHistory(const MIPS32TraceHistory& obj) noexcept;
        MIPS32TraceHistory(const MIPS32TraceHistory& obj, size_t new_history_depth) noexcept;
        MIPS32TraceHistory(MIPS32TraceHistory&& obj) noexcept;
        ~MIPS32TraceHistory() noexcept;

        size_t                              GetDepth() const noexcept;
        size_t                              GetCount() const noexcept;

        void                                SetDepth(size_t new_history_depth) noexcept;

        MIPS32TraceEntity::Reference        Get(size_t index = 0) noexcept;
        const MIPS32TraceEntity::Reference  Get(size_t index = 0) const noexcept;

        void                                Append(const MIPS32TraceEntity::Reference& trace) noexcept;

        void                                Clear() noexcept;

        MIPS32TraceEntity::Reference        operator[](size_t index) noexcept;
        const MIPS32TraceEntity::Reference  operator[](size_t index) const noexcept;

        MIPS32TraceHistory&                 operator=(const MIPS32TraceHistory& obj) noexcept;
        MIPS32TraceHistory&                 operator=(MIPS32TraceHistory&& obj) noexcept;
    };
}


// Trace Memory Management (manager concepts)
namespace Jasse {

    template<class T>
    concept MIPS32TraceHistoryManager = requires (T x, const T c,
        size_t  size,
        size_t  default_depth,
        size_t  address,
        MIPS32TraceHistory&         robj,
        const MIPS32TraceHistory&   crobj,
        MIPS32TraceHistory&&        rrobj) 
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
        { *(x.Get(address)) } noexcept -> std::convertible_to<MIPS32TraceHistory&>;
        { *(c.Get(address)) } noexcept -> std::convertible_to<const MIPS32TraceHistory&>;

        // ::Set(size_t, &&...)
        { x.Set(address, crobj) } noexcept;
        { x.Set(address, rrobj) } noexcept;

        // ::SetIfExists(size_t, &&...)
        { x.SetIfExists(address, crobj) } noexcept -> std::convertible_to<bool>;
        { x.SetIfExists(address, rrobj) } noexcept -> std::convertible_to<bool>;

        // ::SetIfAbsent(size_t, &&...)
        { x.SetIfAbsent(address, crobj) } noexcept -> std::convertible_to<bool>;
        { x.SetIfAbsent(address, rrobj) } noexcept -> std::convertible_to<bool>;

        // ::SwapIfExists(size_t, MIPS32TraceHistory&)
        { x.SwapIfExists(address, robj) } noexcept -> std::convertible_to<bool>;

        // ::Acquire(size_t)
        { x.Acquire(address) } noexcept -> std::convertible_to<MIPS32TraceHistory&>;
    };
}

// Trace Memory Management
namespace Jasse::MIPS32TraceHistoryManagement {

    class Pretouch
    {
    private:
        const size_t        size;

        MIPS32TraceHistory* vector;

        size_t              default_depth;

    public:
        Pretouch(const Pretouch& obj) = delete;
        Pretouch(Pretouch&& obj) = delete;
        Pretouch(size_t size, size_t default_depth = 1) noexcept;
        ~Pretouch() noexcept;

        size_t                      GetDefaultDepth() const noexcept;
        void                        SetDefaultDepth(size_t val) noexcept;

        std::optional<std::reference_wrapper<MIPS32TraceHistory>>       Get(size_t address) noexcept;
        std::optional<std::reference_wrapper<const MIPS32TraceHistory>> Get(size_t address) const noexcept;

        void                        Set(size_t address, const MIPS32TraceHistory& obj) noexcept;
        void                        Set(size_t address, MIPS32TraceHistory&& obj) noexcept;
        bool                        SetIfExists(size_t address, const MIPS32TraceHistory& obj) noexcept;
        bool                        SetIfExists(size_t address, MIPS32TraceHistory&& obj) noexcept;
        constexpr bool              SetIfAbsent(size_t address, const MIPS32TraceHistory& obj) noexcept;
        constexpr bool              SetIfAbsent(size_t address, MIPS32TraceHistory&& obj) noexcept;

        bool                        SwapIfExists(size_t address, MIPS32TraceHistory& obj) noexcept;

        MIPS32TraceHistory&         Acquire(size_t address) noexcept;

        void                        operator=(const Pretouch& obj) = delete;
        void                        operator=(Pretouch&& obj) = delete;
    };


    template<unsigned int _CompressRatio = 6>
    class CompressedIncremental
    {
    private:
        class Chunk {
        private:
            MIPS32TraceHistory*     vector;
            size_t*                 address_table;

            size_t                  capacity_exponent;
            size_t                  count;

        private:
            std::optional<size_t>       _Find(size_t address, size_t* slot_hint = nullptr) const noexcept;
            size_t                      _FindSlot(size_t address, size_t slot_hint = 0) const noexcept;
           
            void                        _Initialize() noexcept;
            void                        _Expand(size_t reserved_slot) noexcept;

            MIPS32TraceHistory&         _NewSlot(size_t address, size_t slot_hint) noexcept;

            template<bool _EnableOnExists, bool _EnableOnAbsent, class _T>
            bool                        _Set(size_t address, _T&& obj) noexcept;

        public: 
            Chunk();
            ~Chunk();

            std::optional<std::reference_wrapper<MIPS32TraceHistory>>       Get(size_t address) noexcept;
            std::optional<std::reference_wrapper<const MIPS32TraceHistory>> Get(size_t address) const noexcept;

            void                        Set(size_t address, const MIPS32TraceHistory& obj) noexcept;
            void                        Set(size_t address, MIPS32TraceHistory&& obj) noexcept;
            bool                        SetIfExists(size_t address, const MIPS32TraceHistory& obj) noexcept;
            bool                        SetIfExists(size_t address, MIPS32TraceHistory&& obj) noexcept;
            bool                        SetIfAbsent(size_t address, const MIPS32TraceHistory& obj) noexcept;
            bool                        SetIfAbsent(size_t address, MIPS32TraceHistory&& obj) noexcept;

            bool                        SwapIfExists(size_t address, MIPS32TraceHistory& obj) noexcept;

            MIPS32TraceHistory&         Acquire(size_t address, size_t default_depth) noexcept;
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

        std::optional<std::reference_wrapper<MIPS32TraceHistory>>       Get(size_t address) noexcept;
        std::optional<std::reference_wrapper<const MIPS32TraceHistory>> Get(size_t address) const noexcept;

        void                        Set(size_t address, const MIPS32TraceHistory& obj) noexcept;
        void                        Set(size_t address, MIPS32TraceHistory&& obj) noexcept;
        bool                        SetIfExists(size_t address, const MIPS32TraceHistory& obj) noexcept;
        bool                        SetIfExists(size_t address, MIPS32TraceHistory&& obj) noexcept;
        bool                        SetIfAbsent(size_t address, const MIPS32TraceHistory& obj) noexcept;
        bool                        SetIfAbsent(size_t address, MIPS32TraceHistory&& obj) noexcept;

        bool                        SwapIfExists(size_t address, MIPS32TraceHistory& obj) noexcept;

        MIPS32TraceHistory&         Acquire(size_t address) noexcept;

        void                        operator=(const CompressedIncremental& obj) = delete;
        void                        operator=(CompressedIncremental&& obj) = delete;
    };
}


// Specialized Tracers
namespace Jasse {

    //
    template<MIPS32TraceHistoryManager _HistoryManager 
        = MIPS32TraceHistoryManagement::Pretouch>
    class MIPS32GPRTracerSubtrate {
    private:
        static constexpr size_t SIZE    = MIPS32_ARCH_REG_COUNT;

    private:
        mutable _HistoryManager manager;

    public:
        MIPS32GPRTracerSubtrate(const MIPS32GPRTracerSubtrate& obj) = delete;
        MIPS32GPRTracerSubtrate(MIPS32GPRTracerSubtrate&& obj) = delete;
        MIPS32GPRTracerSubtrate(size_t default_depth) noexcept;
        ~MIPS32GPRTracerSubtrate() noexcept;

        size_t                      GetDefaultDepth() const noexcept;
        void                        SetDefaultDepth(size_t depth) noexcept;

        constexpr size_t            GetSize() const noexcept;
        constexpr bool              CheckBound(size_t index) const noexcept;

        MIPS32TraceHistory&         Get(size_t index) noexcept;
        const MIPS32TraceHistory&   Get(size_t index) const noexcept;

        void                        Set(size_t index, const MIPS32TraceHistory& obj) noexcept;
        void                        Set(size_t index, MIPS32TraceHistory&& obj) noexcept;

        void                        Swap(size_t index, MIPS32TraceHistory& obj) noexcept;

        MIPS32TraceHistory&         operator[](size_t index) noexcept;
        const MIPS32TraceHistory&   operator[](size_t index) const noexcept;

        MIPS32GPRTracerSubtrate&            operator=(const MIPS32GPRTracerSubtrate& obj) = delete;
        MIPS32GPRTracerSubtrate&            operator=(MIPS32GPRTracerSubtrate&& obj) = delete;
    };
    

    // MIPS32 Memory Tracer
    template<MIPS32TraceHistoryManager _HistoryManager
        = MIPS32TraceHistoryManagement::CompressedIncremental<>>
    class MIPS32MemoryTracerSubtrate {
    private:
        const size_t            size;

        mutable _HistoryManager manager;

    public:
        MIPS32MemoryTracerSubtrate(const MIPS32MemoryTracerSubtrate& obj) = delete;
        MIPS32MemoryTracerSubtrate(MIPS32MemoryTracerSubtrate&& obj) = delete;
        MIPS32MemoryTracerSubtrate(size_t size, size_t default_depth) noexcept;
        ~MIPS32MemoryTracerSubtrate() noexcept;

        size_t                      GetDefaultDepth() const noexcept;
        void                        SetDefaultDepth(size_t depth) noexcept;

        size_t                      GetSize() const noexcept;
        bool                        CheckBound(size_t address) const noexcept;

        std::optional<std::reference_wrapper<MIPS32TraceHistory>>       Get(size_t address) noexcept;
        std::optional<std::reference_wrapper<const MIPS32TraceHistory>> Get(size_t address) const noexcept;

        MIPS32TraceHistory&         Acquire(size_t address) noexcept;
        const MIPS32TraceHistory&   Acquire(size_t address) const noexcept;

        void                        Set(size_t address, const MIPS32TraceHistory& obj) noexcept;
        void                        Set(size_t address, MIPS32TraceHistory&& obj) noexcept;
        bool                        SetIfExists(size_t address, const MIPS32TraceHistory& obj) noexcept;
        bool                        SetIfExists(size_t address, MIPS32TraceHistory&& obj) noexcept;
        bool                        SetIfAbsent(size_t address, const MIPS32TraceHistory& obj) noexcept;
        bool                        SetIfAbsent(size_t address, MIPS32TraceHistory&& obj) noexcept;

        bool                        SwapIfExists(size_t address, MIPS32TraceHistory& obj) noexcept;

        MIPS32MemoryTracerSubtrate&         operator=(const MIPS32MemoryTracerSubtrate& obj) = delete;
        MIPS32MemoryTracerSubtrate&         operator=(MIPS32MemoryTracerSubtrate&& obj) = delete;
    };
}


// Implementation of: class MIPS32TraceEntity
namespace Jasse {
    //
    // MIPS32Instruction   insn;
    // pc_t                pc;
    //
    // arch32_t            value;
    //
    // Reference           op0;
    // Reference           op1;
    //

    MIPS32TraceEntity::MIPS32TraceEntity(
            pc_t                        pc, 
            const MIPS32Instruction&    insn, 
            arch32_t                    value) noexcept
        : pc    (pc)
        , insn  (insn)
        , value (value)
        , op0   ()
        , op1   ()
    { }

    MIPS32TraceEntity::MIPS32TraceEntity(
            pc_t                        pc,
            const MIPS32Instruction&    insn,
            arch32_t                    value,
            const Reference&            op0) noexcept
        : pc    (pc)
        , insn  (insn)
        , value (value)
        , op0   (op0)
        , op1   ()
    { }

    MIPS32TraceEntity::MIPS32TraceEntity(
            pc_t pc,
            const MIPS32Instruction&    insn,
            arch32_t                    value,
            const Reference&            op0,
            const Reference&            op1) noexcept
        : pc    (pc)
        , insn  (insn)
        , value (value)
        , op0   (op0)
        , op1   (op1)
    { }

    inline void MIPS32TraceEntity::SetInstruction(const MIPS32Instruction& insn) noexcept
    {
        this->insn = insn;
    }

    inline void MIPS32TraceEntity::SetPC(pc_t pc) noexcept
    {
        this->pc = pc;
    }

    inline void MIPS32TraceEntity::SetValue(arch32_t value) noexcept
    {
        this->value = value;
    }

    inline void MIPS32TraceEntity::SetFirstOperand(const Reference& op0) noexcept
    {
        this->op0 = op0;
    }

    inline void MIPS32TraceEntity::SetSecondOperand(const Reference& op1) noexcept
    {
        this->op1 = op1;
    }

    inline MIPS32Instruction& MIPS32TraceEntity::GetInstruction() noexcept
    {
        return insn;
    }

    inline const MIPS32Instruction& MIPS32TraceEntity::GetInstruction() const noexcept
    {
        return insn;
    }

    inline pc_t MIPS32TraceEntity::GetPC() const noexcept
    {
        return pc;
    }

    inline arch32_t MIPS32TraceEntity::GetValue() const noexcept
    {
        return value;
    }

    inline MIPS32TraceEntity::Reference& MIPS32TraceEntity::GetFirstOperand() noexcept
    {
        return op0;
    }

    inline const MIPS32TraceEntity::Reference& MIPS32TraceEntity::GetFirstOperand() const noexcept
    {
        return op0;
    }

    inline MIPS32TraceEntity::Reference& MIPS32TraceEntity::GetSecondOperand() noexcept
    {
        return op1;
    }

    inline const MIPS32TraceEntity::Reference& MIPS32TraceEntity::GetSecondOperand() const noexcept
    {
        return op1;
    }
}


// Implementation of: class MIPS32TraceHistory
namespace Jasse {
    //
    // size_t                          history_depth;
    //
    // size_t                          capacity;
    // size_t                          count;
    // size_t                          round_pointer;
    //
    // MIPS32TraceEntity::Reference*   traces;
    //

    MIPS32TraceHistory::MIPS32TraceHistory(size_t history_depth) noexcept
        : history_depth (history_depth)
        , capacity      (0)
        , count         (0)
        , round_pointer (0)
        , traces        (nullptr)
    { }

    MIPS32TraceHistory::MIPS32TraceHistory(const MIPS32TraceHistory& obj) noexcept
        : history_depth (obj.history_depth)
        , capacity      (obj.capacity)
        , count         (obj.count)
        , round_pointer (obj.round_pointer)
        , traces        (nullptr)
    { 
        if (obj.traces)
        {
            traces = new MIPS32TraceEntity::Reference[obj.capacity];

            std::copy(obj.traces, obj.traces + obj.capacity, traces);
        }
    }

    MIPS32TraceHistory::MIPS32TraceHistory(const MIPS32TraceHistory& obj, size_t new_history_depth) noexcept
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

    MIPS32TraceHistory::MIPS32TraceHistory(MIPS32TraceHistory&& obj) noexcept
        : history_depth (obj.history_depth)
        , capacity      (obj.capacity)
        , count         (obj.count)
        , round_pointer (obj.round_pointer)
        , traces        (obj.traces)
    {
        obj._Clear();
    }

    MIPS32TraceHistory::~MIPS32TraceHistory() noexcept
    {
        if (traces)
            delete[] traces;
    }

    inline MIPS32TraceEntity::Reference* MIPS32TraceHistory::_ModifyDepth(
        MIPS32TraceEntity::Reference* const src,
        size_t                              src_capacity,
        size_t                              src_count,
        size_t                              src_round_pointer,
        size_t                              new_history_depth,
        size_t&                             new_capacity,
        size_t&                             new_count) noexcept
    {
        if (src)
        {
            auto newArray = new MIPS32TraceEntity::Reference[
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

    inline size_t MIPS32TraceHistory::GetDepth() const noexcept
    {
        return history_depth;
    }

    inline size_t MIPS32TraceHistory::GetCount() const noexcept
    {
        return count;
    }

    void MIPS32TraceHistory::SetDepth(size_t new_history_depth) noexcept
    {
        if (new_history_depth == history_depth)
            return;

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

    inline MIPS32TraceEntity::Reference MIPS32TraceHistory::Get(size_t index) noexcept
    {
        return traces[(round_pointer + count - 1 - index) % capacity];
    }

    inline const MIPS32TraceEntity::Reference MIPS32TraceHistory::Get(size_t index) const noexcept
    {
        return traces[(round_pointer + count - 1 - index) % capacity];
    }

    void MIPS32TraceHistory::Append(const MIPS32TraceEntity::Reference& trace) noexcept
    {
        if (!traces)
            traces = new MIPS32TraceEntity::Reference[capacity = 1];
        else if (count == history_depth)
            traces[round_pointer++] = trace;
        else
        {
            if (count == capacity)
            {
                MIPS32TraceEntity::Reference* newArray = new MIPS32TraceEntity::Reference[
                    std::min(capacity << 1, history_depth)];
                
                std::copy(traces, traces + capacity, newArray);

                traces = newArray;
            }

            traces[count++] = trace;
        }
    }

    inline void MIPS32TraceHistory::_Clear() noexcept
    {
        capacity        = 0;
        count           = 0;
        round_pointer   = 0;

        traces = nullptr;
    }

    inline void MIPS32TraceHistory::Clear() noexcept
    {
        if (traces)
            delete[] traces;

        _Clear();
    }

    inline MIPS32TraceEntity::Reference MIPS32TraceHistory::operator[](size_t index) noexcept
    {
        return Get(index);
    }

    inline const MIPS32TraceEntity::Reference MIPS32TraceHistory::operator[](size_t index) const noexcept
    {
        return Get(index);
    }

    inline MIPS32TraceHistory& MIPS32TraceHistory::operator=(const MIPS32TraceHistory& obj) noexcept
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
                traces = new MIPS32TraceEntity::Reference[capacity];

                std::copy(obj.traces, obj.traces + capacity, traces);
            }
            else
                traces = nullptr;
        }

        return *this;
    }

    inline MIPS32TraceHistory& MIPS32TraceHistory::operator=(MIPS32TraceHistory&& obj) noexcept
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



// Implementation of: class MIPS32TraceHistoryManagement::Pretouch
namespace Jasse::MIPS32TraceHistoryManagement {
    //
    // const size_t        size;
    //
    // MIPS32TraceHistory* vector;
    //
    // size_t              default_depth;
    //

    Pretouch::Pretouch(size_t size, size_t default_depth) noexcept
        : size          (size)
        , vector        (new MIPS32TraceHistory[size])
        , default_depth (default_depth)
    {
        for (int i = 0; i < size; i++)
            vector[i].SetDepth(default_depth);
    }

    Pretouch::~Pretouch() noexcept
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
        //          operation because all the default history depth of MIPS32TraceHistory instances were 
        //          set on construction time for Pretouch Management.
    }
    
    inline std::optional<std::reference_wrapper<MIPS32TraceHistory>> Pretouch::Get(size_t address) noexcept
    {
        return { std::ref(vector[address]) };
    }

    inline std::optional<std::reference_wrapper<const MIPS32TraceHistory>> Pretouch::Get(size_t address) const noexcept
    {
        return { std::cref(vector[address]) };
    }

    inline void Pretouch::Set(size_t address, const MIPS32TraceHistory& obj) noexcept
    {
        vector[address] = obj;
    }

    inline void Pretouch::Set(size_t address, MIPS32TraceHistory&& obj) noexcept
    {
        vector[address] = std::move(obj);
    }

    inline bool Pretouch::SetIfExists(size_t address, const MIPS32TraceHistory& obj) noexcept
    {
        Set(address, obj);
        return true;
    }

    inline bool Pretouch::SetIfExists(size_t address, MIPS32TraceHistory&& obj) noexcept
    {
        Set(address, std::move(obj));
        return true;
    }

    constexpr bool Pretouch::SetIfAbsent(size_t address, const MIPS32TraceHistory& obj) noexcept
    {
        return false;
    }

    constexpr bool Pretouch::SetIfAbsent(size_t address, MIPS32TraceHistory&& obj) noexcept
    {
        return false;
    }

    inline bool Pretouch::SwapIfExists(size_t address, MIPS32TraceHistory& obj) noexcept
    {
        std::swap(vector[address], obj);
        return true;
    }

    inline MIPS32TraceHistory& Pretouch::Acquire(size_t address) noexcept
    {
        return vector[address];
    }
}



// Implementation of: class MIPS32TraceHistoryManagement::CompressedIncremental::Chunk
namespace Jasse::MIPS32TraceHistoryManagement {
    //
    // MIPS32TraceHistory* vector;
    // size_t*             address_table;
    //
    // size_t              capacity_exponent;
    // size_t              count;
    //

    template<unsigned int _CompressRatio>
    CompressedIncremental<_CompressRatio>::Chunk::Chunk()
        : vector            (nullptr)
        , address_table     (nullptr)
        , capacity_exponent (0)
        , count             (0)
    { }

    template<unsigned int _CompressRatio>
    CompressedIncremental<_CompressRatio>::Chunk::~Chunk()
    {
        if (vector)
            delete[] vector;

        if (address_table)
            delete[] address_table;
    }

    template<unsigned int _CompressRatio>
    std::optional<size_t> CompressedIncremental<_CompressRatio>::Chunk::_Find(size_t address, size_t* slot_hint) const noexcept
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
    size_t CompressedIncremental<_CompressRatio>::Chunk::_FindSlot(size_t address, size_t slot_hint) const noexcept
    {
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
        vector        = new MIPS32TraceHistory[1];
        address_table = new size_t[1];
    }

    template<unsigned int _CompressRatio>
    void CompressedIncremental<_CompressRatio>::Chunk::_Expand(size_t reserved_slot) noexcept
    {
        size_t capacity = 1 << capacity_exponent;

        // construct & move vector
        MIPS32TraceHistory* newVector = new MIPS32TraceHistory[capacity << 1];

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
    }

    template<unsigned int _CompressRatio>
    inline MIPS32TraceHistory& CompressedIncremental<_CompressRatio>::Chunk::_NewSlot(size_t address, size_t slot_hint) noexcept
    {
        size_t new_slot_index = _FindSlot(address, slot_hint);

        if (count == (1 << capacity_exponent))
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
    inline std::optional<std::reference_wrapper<MIPS32TraceHistory>> CompressedIncremental<_CompressRatio>::Chunk::Get(size_t address) noexcept
    {
        std::optional<size_t> index = _Find(address);

        if (index)
            return { std::ref(vector[*index]) };
        
        return std::nullopt;
    }

    template<unsigned int _CompressRatio>
    inline std::optional<std::reference_wrapper<const MIPS32TraceHistory>> CompressedIncremental<_CompressRatio>::Chunk::Get(size_t address) const noexcept
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
        size_t slot_hint;

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
    inline void CompressedIncremental<_CompressRatio>::Chunk::Set(size_t address, const MIPS32TraceHistory& obj) noexcept
    {
        _Set<true, true>(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline void CompressedIncremental<_CompressRatio>::Chunk::Set(size_t address, MIPS32TraceHistory&& obj) noexcept
    {
        _Set<true, true>(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::SetIfExists(size_t address, const MIPS32TraceHistory& obj) noexcept
    {
        return _Set<true, false>(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::SetIfExists(size_t address, MIPS32TraceHistory&& obj) noexcept
    {
        return _Set<true, false>(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::SetIfAbsent(size_t address, const MIPS32TraceHistory& obj) noexcept
    {
        return _Set<false, true>(address, obj);
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::SetIfAbsent(size_t address, MIPS32TraceHistory&& obj) noexcept
    {
        return _Set<false, true>(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    inline bool CompressedIncremental<_CompressRatio>::Chunk::SwapIfExists(size_t address, MIPS32TraceHistory& obj) noexcept
    {
        std::optional<size_t> index = _Find(address);

        if (!index)
            return false;

        std::swap(vector[*index], obj);
        return true;
    }

    template<unsigned int _CompressRatio>
    inline MIPS32TraceHistory& CompressedIncremental<_CompressRatio>::Chunk::Acquire(size_t address, size_t default_depth) noexcept
    {
        size_t slot_hint;

        std::optional<size_t> index = _Find(address, &slot_hint);

        if (index)
            return vector[*index];
        else
        {
            MIPS32TraceHistory& obj = _NewSlot(address, slot_hint);

            obj.SetDepth(default_depth);
            return obj;
        }
    }
}


// Implementation of: class MIPS32TraceHistoryManagement::CompressIncremental
namespace Jasse::MIPS32TraceHistoryManagement {
    //
    // const size_t    max_size;
    //
    // const size_t    chunk_count;
    // Chunk*          chunks;
    //
    // size_t          default_depth;
    //

    template<unsigned int _CompressRatio>
    CompressedIncremental<_CompressRatio>::CompressedIncremental(size_t max_size, size_t default_depth) noexcept
        : max_size      (max_size)
        , chunk_count   ((max_size >> _CompressRatio) + 1)
        , chunks        (new Chunk[chunk_count])
        , default_depth (default_depth)
    { }

    template<unsigned int _CompressRatio>
    CompressedIncremental<_CompressRatio>::~CompressedIncremental() noexcept
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
    std::optional<std::reference_wrapper<MIPS32TraceHistory>> CompressedIncremental<_CompressRatio>::Get(size_t address) noexcept
    {
        return chunks[_ToChunkAddress(address)].Get(_ToAddressInChunk(address));
    }

    template<unsigned int _CompressRatio>
    std::optional<std::reference_wrapper<const MIPS32TraceHistory>> CompressedIncremental<_CompressRatio>::Get(size_t address) const noexcept
    {
        return chunks[_ToChunkAddress(address)].Get(_ToAddressInChunk(address));
    }

    template<unsigned int _CompressRatio>
    void CompressedIncremental<_CompressRatio>::Set(size_t address, const MIPS32TraceHistory& obj) noexcept
    {
        chunks[_ToChunkAddress(address)].Set(address, obj);
    }

    template<unsigned int _CompressRatio>
    void CompressedIncremental<_CompressRatio>::Set(size_t address, MIPS32TraceHistory&& obj) noexcept
    {
        chunks[_ToChunkAddress(address)].Set(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    bool CompressedIncremental<_CompressRatio>::SetIfExists(size_t address, const MIPS32TraceHistory& obj) noexcept
    {
        return chunks[_ToChunkAddress(address)].SetIfExists(address, obj);
    }

    template<unsigned int _CompressRatio>
    bool CompressedIncremental<_CompressRatio>::SetIfExists(size_t address, MIPS32TraceHistory&& obj) noexcept
    {
        return chunks[_ToChunkAddress(address)].SetIfExists(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    bool CompressedIncremental<_CompressRatio>::SetIfAbsent(size_t address, const MIPS32TraceHistory& obj) noexcept
    {
        return chunks[_ToChunkAddress(address)].SetIfAbsent(address, obj);
    }

    template<unsigned int _CompressRatio>
    bool CompressedIncremental<_CompressRatio>::SetIfAbsent(size_t address, MIPS32TraceHistory&& obj) noexcept
    {
        return chunks[_ToChunkAddress(address)].SetIfAbsent(address, std::move(obj));
    }

    template<unsigned int _CompressRatio>
    bool CompressedIncremental<_CompressRatio>::SwapIfExists(size_t address, MIPS32TraceHistory& obj) noexcept
    {
        return chunks[_ToChunkAddress(address)].SwapIfExists(address, obj);
    }

    template<unsigned int _CompressRatio>
    MIPS32TraceHistory& CompressedIncremental<_CompressRatio>::Acquire(size_t address) noexcept
    {
        return chunks[_ToChunkAddress(address)].Acquire(address, default_depth);
    }
}



// Implementation of: class MIPS32GPRTracerSubtrate
namespace Jasse {
    //
    // mutable _HistoryManager  manager;
    //

    template<MIPS32TraceHistoryManager _HistoryManager>
    MIPS32GPRTracerSubtrate<_HistoryManager>::MIPS32GPRTracerSubtrate(size_t default_depth) noexcept
        : manager   (SIZE, default_depth)
    { }

    template<MIPS32TraceHistoryManager _HistoryManager>
    MIPS32GPRTracerSubtrate<_HistoryManager>::~MIPS32GPRTracerSubtrate() noexcept
    { }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline size_t MIPS32GPRTracerSubtrate<_HistoryManager>::GetDefaultDepth() const noexcept
    {
        return manager.GetDefaultDepth();
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline void MIPS32GPRTracerSubtrate<_HistoryManager>::SetDefaultDepth(size_t depth) noexcept
    {
        manager.SetDefaultDepth(depth);
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline constexpr size_t MIPS32GPRTracerSubtrate<_HistoryManager>::GetSize() const noexcept
    {
        return SIZE;
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline constexpr bool MIPS32GPRTracerSubtrate<_HistoryManager>::CheckBound(size_t index) const noexcept
    {
        return index >= 0 && index < SIZE;
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline MIPS32TraceHistory& MIPS32GPRTracerSubtrate<_HistoryManager>::Get(size_t index) noexcept
    {
        return manager.Acquire(index);
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline const MIPS32TraceHistory& MIPS32GPRTracerSubtrate<_HistoryManager>::Get(size_t index) const noexcept
    {
        return manager.Acquire(index);
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline void MIPS32GPRTracerSubtrate<_HistoryManager>::Set(size_t index, const MIPS32TraceHistory& obj) noexcept
    {
        manager.Set(index, obj);
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline void MIPS32GPRTracerSubtrate<_HistoryManager>::Set(size_t index, MIPS32TraceHistory&& obj) noexcept
    {
        manager.Set(index, std::move(obj));
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline void MIPS32GPRTracerSubtrate<_HistoryManager>::Swap(size_t index, MIPS32TraceHistory& obj) noexcept
    {
        if (!manager.SwapIfExists(index, obj))
            std::swap(manager.Acquire(index), obj);
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline MIPS32TraceHistory& MIPS32GPRTracerSubtrate<_HistoryManager>::operator[](size_t index) noexcept
    {
        return Get(index);
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline const MIPS32TraceHistory& MIPS32GPRTracerSubtrate<_HistoryManager>::operator[](size_t index) const noexcept
    {
        return Get(index);
    }
}


// Implementation of: class MIPS32MemoryTracerSubtrate
namespace Jasse {
    //
    // const size_t            size;
    //
    // mutable _HistoryManager manager;
    //

    template<MIPS32TraceHistoryManager _HistoryManager>
    MIPS32MemoryTracerSubtrate<_HistoryManager>::MIPS32MemoryTracerSubtrate(size_t size, size_t default_depth) noexcept
        : size      (size)
        , manager   (size, default_depth)
    { }

    template<MIPS32TraceHistoryManager _HistoryManager>
    MIPS32MemoryTracerSubtrate<_HistoryManager>::~MIPS32MemoryTracerSubtrate() noexcept
    { }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline size_t MIPS32MemoryTracerSubtrate<_HistoryManager>::GetDefaultDepth() const noexcept
    {
        return manager.GetDefaultDepth();
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline void MIPS32MemoryTracerSubtrate<_HistoryManager>::SetDefaultDepth(size_t depth) noexcept
    {
        manager.SetDefaultDepth(depth);
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline size_t MIPS32MemoryTracerSubtrate<_HistoryManager>::GetSize() const noexcept
    {
        return size;
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline bool MIPS32MemoryTracerSubtrate<_HistoryManager>::CheckBound(size_t address) const noexcept
    {
        return address >= 0 && address < size;
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline std::optional<std::reference_wrapper<MIPS32TraceHistory>> MIPS32MemoryTracerSubtrate<_HistoryManager>::Get(size_t address) noexcept
    {
        auto __from_get = manager.Get(address);
        return __from_get ? std::optional<std::reference_wrapper<MIPS32TraceHistory>>(std::ref(*__from_get)) : std::nullopt;
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline std::optional<std::reference_wrapper<const MIPS32TraceHistory>> MIPS32MemoryTracerSubtrate<_HistoryManager>::Get(size_t address) const noexcept
    {
        auto __from_const_get = std::as_const(manager).Get(address);
        return __from_const_get ? std::optional<std::reference_wrapper<const MIPS32TraceHistory>>(std::cref(*__from_const_get)) : std::nullopt;
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline MIPS32TraceHistory& MIPS32MemoryTracerSubtrate<_HistoryManager>::Acquire(size_t address) noexcept
    {
        return manager.Acquire(address);
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline const MIPS32TraceHistory& MIPS32MemoryTracerSubtrate<_HistoryManager>::Acquire(size_t address) const noexcept
    {
        return manager.Acquire(address);
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline void MIPS32MemoryTracerSubtrate<_HistoryManager>::Set(size_t address, const MIPS32TraceHistory& obj) noexcept
    {
        manager.Set(address, obj);
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline void MIPS32MemoryTracerSubtrate<_HistoryManager>::Set(size_t address, MIPS32TraceHistory&& obj) noexcept
    {
        manager.Set(address, std::move(obj));
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline bool MIPS32MemoryTracerSubtrate<_HistoryManager>::SetIfExists(size_t address, const MIPS32TraceHistory& obj) noexcept
    {
        return manager.SetIfExists(address, obj);
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline bool MIPS32MemoryTracerSubtrate<_HistoryManager>::SetIfExists(size_t address, MIPS32TraceHistory&& obj) noexcept
    {
        return manager.SetIfExists(address, std::move(obj));
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline bool MIPS32MemoryTracerSubtrate<_HistoryManager>::SetIfAbsent(size_t address, const MIPS32TraceHistory& obj) noexcept
    {
        return manager.SetIfAbsent(address, obj);
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline bool MIPS32MemoryTracerSubtrate<_HistoryManager>::SetIfAbsent(size_t address, MIPS32TraceHistory&& obj) noexcept
    {
        return manager.SetIfAbsent(address, std::move(obj));
    }

    template<MIPS32TraceHistoryManager _HistoryManager>
    inline bool MIPS32MemoryTracerSubtrate<_HistoryManager>::SwapIfExists(size_t address, MIPS32TraceHistory& obj) noexcept
    {
        return manager.SwapIfExists(address, obj);
    }
}
