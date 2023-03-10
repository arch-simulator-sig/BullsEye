#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// Trace Subsystem Infrastructures
//

#include <memory>
#include <algorithm>
#include <optional>
#include <functional>
#include <utility>

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


// Trace Memory Management
namespace Jasse::MIPS32TraceHistoryManagement {

    class Pretouch
    {
    private:
        const size_t        size;

        MIPS32TraceHistory* vector;

    public:
        Pretouch(const Pretouch& obj) = delete;
        Pretouch(Pretouch&& obj) = delete;
        Pretouch(size_t size) noexcept;
        ~Pretouch() noexcept;

        std::optional<std::reference_wrapper<MIPS32TraceHistory>>       Get(size_t address) noexcept;
        std::optional<std::reference_wrapper<const MIPS32TraceHistory>> Get(size_t address) const noexcept;

        void                        Set(size_t address, const MIPS32TraceHistory& obj) noexcept;
        bool                        SetIfExists(size_t address, const MIPS32TraceHistory& obj) noexcept;

        void                        Emplace(size_t address, MIPS32TraceHistory&& obj) noexcept;
        bool                        EmplaceIfExists(size_t address, MIPS32TraceHistory&& obj) noexcept;

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
            MIPS32TraceHistory* vector;

            size_t              capacity;
            size_t              count;

        public: 
            Chunk();
            ~Chunk();

            MIPS32TraceHistory*         Get(size_t address) noexcept;
            MIPS32TraceHistory* const   Get(size_t address) const noexcept;

            void                        Set(size_t address, const MIPS32TraceHistory& obj) noexcept;
            bool                        SetIfExists(size_t address, const MIPS32TraceHistory& obj) noexcept;

            void                        Emplace(size_t address, MIPS32TraceHistory&& obj) noexcept;
            bool                        EmplaceIfExists(size_t address, MIPS32TraceHistory&& obj) noexcept;

            bool                        SwapIfExists(size_t address, MIPS32TraceHistory& obj) noexcept;

            MIPS32TraceHistory&         Acquire(size_t address) noexcept;
        };

    private:
        const size_t    max_size;

        Chunk*          chunks;

    public:
        CompressedIncremental(const CompressedIncremental& obj) = delete;
        CompressedIncremental(CompressedIncremental&& obj) = delete;
        CompressedIncremental(size_t max_size) noexcept;
        ~CompressedIncremental() noexcept;

        Pretouch(size_t size) noexcept;
        ~Pretouch() noexcept;

        std::optional<std::reference_wrapper<MIPS32TraceHistory>>       Get(size_t address) noexcept;
        std::optional<std::reference_wrapper<const MIPS32TraceHistory>> Get(size_t address) const noexcept;

        void                        Set(size_t address, const MIPS32TraceHistory& obj) noexcept;
        bool                        SetIfExists(size_t address, const MIPS32TraceHistory& obj) noexcept;

        void                        Emplace(size_t address, MIPS32TraceHistory&& obj) noexcept;
        bool                        EmplaceIfExists(size_t address, MIPS32TraceHistory&& obj) noexcept;

        bool                        SwapIfExists(size_t address, MIPS32TraceHistory& obj) noexcept;

        MIPS32TraceHistory&         Acquire(size_t address) noexcept;

        void                        operator=(const CompressedIncremental& obj) = delete;
        void                        operator=(CompressedIncremental&& obj) = delete;
    };
}


// Specialized Tracers
namespace Jasse {
    // MIPS32 GPR Tracer
    class MIPS32GPRTracer {
    private:
        static constexpr int    SIZE   = MIPS32_ARCH_REG_COUNT;

        const size_t            history_depth;

        MIPS32TraceHistory*     gpr_traces[SIZE];

    public:
        MIPS32GPRTracer(size_t history_depth) noexcept;
        MIPS32GPRTracer(const MIPS32GPRTracer& obj) noexcept;
        MIPS32GPRTracer(const MIPS32GPRTracer& obj, size_t new_history_depth) noexcept;
        ~MIPS32GPRTracer() noexcept;

        size_t                      GetDepth() const noexcept;
        size_t                      GetSize() const noexcept;
        bool                        CheckBound(size_t index) const noexcept;

        MIPS32TraceHistory&         Get(size_t index) noexcept;
        const MIPS32TraceHistory&   Get(size_t index) const noexcept;

        [[nodiscard("potential memory leak : caller swap object management")]]
        MIPS32TraceHistory*         Swap(size_t index, MIPS32TraceHistory* obj) noexcept;

        MIPS32TraceHistory&         operator[](size_t index) noexcept;
        const MIPS32TraceHistory&   operator[](size_t index) const noexcept;

        MIPS32GPRTracer&            operator=(const MIPS32GPRTracer& obj) = delete;
    };
    

    // MIPS32 Memory Tracer
    class MIPS32MemoryTracer {
    private:
        const size_t            size;

        const size_t            history_depth;
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

            std::copy(src + src_round_pointer, src + src_round_pointer + seg1copy, newArray);
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

    Pretouch::Pretouch(size_t size) noexcept
        : size      (size)
        , vector    (new MIPS32TraceHistory[size])
    { }

    Pretouch::~Pretouch() noexcept
    {
        delete[] vector;
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

    inline bool Pretouch::SetIfExists(size_t address, const MIPS32TraceHistory& obj) noexcept
    {
        Set(address, obj);
        return true;
    }

    inline void Pretouch::Emplace(size_t address, MIPS32TraceHistory&& obj) noexcept
    {
        vector[address] = obj;
    }

    inline bool Pretouch::EmplaceIfExists(size_t address, MIPS32TraceHistory&& obj) noexcept
    {
        Emplace(address, std::move(obj));
        return true;
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



// Implementation of: class MIPS32GPRTracer
namespace Jasse {
    //
    // static constexpr int    SIZE;
    //
    // const size_t            history_depth;
    //
    // MIPS32TraceHistory*     gpr_traces[SIZE];
    //

    MIPS32GPRTracer::MIPS32GPRTracer(size_t history_depth) noexcept
        : history_depth (history_depth)
        , gpr_traces    ()
    {
        for (MIPS32TraceHistory*& trace : gpr_traces)
            trace = new MIPS32TraceHistory(history_depth);
    }

    MIPS32GPRTracer::MIPS32GPRTracer(const MIPS32GPRTracer& obj) noexcept
        : history_depth (obj.history_depth)
        , gpr_traces    ()
    {
        for (size_t i = 0; i < SIZE; i++)
            gpr_traces[i] = new MIPS32TraceHistory(*(obj.gpr_traces[i]));
    }

    MIPS32GPRTracer::MIPS32GPRTracer(const MIPS32GPRTracer& obj, size_t new_history_depth) noexcept
        : history_depth (new_history_depth)
        , gpr_traces    ()
    {
        for (size_t i = 0; i < SIZE; i++)
            gpr_traces[i] = new MIPS32TraceHistory(*(obj.gpr_traces[i]), new_history_depth);
    }

    MIPS32GPRTracer::~MIPS32GPRTracer() noexcept
    {
        for (MIPS32TraceHistory*& trace : gpr_traces)
            delete trace;
    }

    inline size_t MIPS32GPRTracer::GetDepth() const noexcept
    {
        return history_depth;
    }
    
    inline size_t MIPS32GPRTracer::GetSize() const noexcept
    {
        return SIZE;
    }

    inline bool MIPS32GPRTracer::CheckBound(size_t index) const noexcept
    {
        return index >= 0 && index < SIZE;
    }

    inline MIPS32TraceHistory& MIPS32GPRTracer::Get(size_t index) noexcept
    {
        return *(gpr_traces[index]);
    }

    inline const MIPS32TraceHistory& MIPS32GPRTracer::Get(size_t index) const noexcept
    {
        return *(gpr_traces[index]);
    }

    inline MIPS32TraceHistory* MIPS32GPRTracer::Swap(size_t index, MIPS32TraceHistory* obj) noexcept
    {
        std::swap(gpr_traces[index], obj);
        return obj;
    }

    inline MIPS32TraceHistory& MIPS32GPRTracer::operator[](size_t index) noexcept
    {
        return Get(index);
    }

    inline const MIPS32TraceHistory& MIPS32GPRTracer::operator[](size_t index) const noexcept
    {
        return Get(index);
    }
}


