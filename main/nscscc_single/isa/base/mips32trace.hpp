#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// Trace Subsystem Infrastructures
//

#include <memory>
#include <algorithm>

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
        const size_t                    history_depth;

        size_t                          capacity;
        size_t                          count;
        size_t                          round_pointer;

        MIPS32TraceEntity::Reference*   traces;

    public:
        MIPS32TraceHistory(size_t history_depth) noexcept;
        MIPS32TraceHistory(const MIPS32TraceHistory& obj) noexcept;
        MIPS32TraceHistory(const MIPS32TraceHistory& obj, size_t new_history_depth) noexcept;
        ~MIPS32TraceHistory() noexcept;

        size_t                              GetDepth() const noexcept;
        size_t                              GetCount() const noexcept;

        MIPS32TraceEntity::Reference        Get(size_t index) noexcept;
        const MIPS32TraceEntity::Reference  Get(size_t index) const noexcept;

        void                                Append(const MIPS32TraceEntity::Reference& trace) noexcept;

        MIPS32TraceEntity::Reference        operator[](size_t index) noexcept;
        const MIPS32TraceEntity::Reference  operator[](size_t index) const noexcept;

        MIPS32TraceHistory&                 operator=(const MIPS32TraceHistory& obj) = delete;
    };
}


// Trace Memory Management
namespace Jasse::MIPS32TraceHistoryManagement {

    class Pretouch
    {

    };

    class CompressedIncremental
    {

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
    // const size_t                    history_depth;
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
        , capacity      (obj.capacity)
        , count         (obj.count)
        , round_pointer (0)
        , traces        (nullptr)
    {
        if (obj.traces)
        {
            traces = new MIPS32TraceEntity::Reference[new_history_depth];

            if (new_history_depth >= obj.history_depth) // fully copied
            {
                std::copy(obj.traces + obj.round_pointer, obj.traces + obj.capacity, traces);
                std::copy(obj.traces, obj.traces + obj.round_pointer, traces + obj.capacity - obj.round_pointer);
            }
            else if (new_history_depth <= (obj.capacity - obj.round_pointer)) // truncated on first segment
            {
                std::copy(obj.traces + obj.round_pointer, obj.traces + obj.round_pointer + new_history_depth, traces);
            }
            else // truncated on second segment
            {
                std::copy(obj.traces + obj.round_pointer, obj.traces + obj.capacity, traces);
                std::copy(obj.traces, obj.traces + new_history_depth - (obj.capacity - obj.round_pointer), traces + obj.capacity - obj.round_pointer);
            }
        }
    }

    MIPS32TraceHistory::~MIPS32TraceHistory() noexcept
    {
        if (traces)
            delete[] traces;
    }

    inline size_t MIPS32TraceHistory::GetDepth() const noexcept
    {
        return history_depth;
    }

    inline size_t MIPS32TraceHistory::GetCount() const noexcept
    {
        return count;
    }

    inline MIPS32TraceEntity::Reference MIPS32TraceHistory::Get(size_t index) noexcept
    {
        return traces[index];
    }

    inline const MIPS32TraceEntity::Reference MIPS32TraceHistory::Get(size_t index) const noexcept
    {
        return traces[index];
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
                MIPS32TraceEntity::Reference* newArray 
                    = new MIPS32TraceEntity::Reference[std::min(capacity << 1, history_depth)];
                
                std::copy(traces, traces + capacity, newArray);

                traces = newArray;
            }

            traces[count++] = trace;
        }
    }

    inline MIPS32TraceEntity::Reference MIPS32TraceHistory::operator[](size_t index) noexcept
    {
        return Get(index);
    }

    inline const MIPS32TraceEntity::Reference MIPS32TraceHistory::operator[](size_t index) const noexcept
    {
        return Get(index);
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
