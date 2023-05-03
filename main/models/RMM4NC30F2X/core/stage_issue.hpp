#pragma once
//
// Issue Stage models for RMM4NC30F2X (Gemini 30F2)
//
//
//

#include <cstdint>
#include <bitset>

#include "common/nonstdint.hpp"

#include "models/common/dff.hpp"
#include "models/common/sram.hpp"
#include "models/common/axi.hpp"

#include "models/util/mips32helper.hpp"


#include "def_global.hpp"
#include "stage_global.hpp"

#include "stage_fetch.hpp"
#include "stage_decode.hpp"


namespace BullsEye::Gemini30F2::Issue {

    using PatternHistory    = Fetch::BranchPredictor::PHTEntry;
    
    using ROBIndex          = Decode::ReOrderBuffer::Index;

    using RegisterIndex     = Decode::RegisterIndex;

    using RegisterValue     = Decode::RegisterValue;

    using BeforeIssue       = Decode::Decode::BeforeIssue;

    using BranchPrediction  = Decode::Decode::BranchPrediction;

    using PreIssueMicroCode = Decode::Decode::PreIssueMicroCode;
}

namespace BullsEye::Gemini30F2::Issue {

    // Wake-up History Table
    class WakeupHistoryTable {
    private:
        struct Entry {
            bool            valid;
            ROBIndex        rob;
            RegisterValue   value;
        };

    public:
        struct Writeback {
            bool            enable;
            ROBIndex        rob;
            RegisterValue   value;
        };

        struct Query {
            ROBIndex        rob;
            bool            ready;
            RegisterValue   value;
        };

        struct QueryResult {
            bool            ready;
            RegisterValue   value;
        };

    private:
        SteppingDFF<Entry, DFFResetValue<Entry, Entry { .valid = false }>>  wht0;
        SteppingDFF<Entry, DFFResetValue<Entry, Entry { .valid = false }>>  wht1;

        bool        next_reset;

    private:
        bool            _QueryHit0(ROBIndex rob) const noexcept;
        bool            _QueryHit1(ROBIndex rob) const noexcept;

        QueryResult     _Query(Query bundle) const noexcept;

    public:
        WakeupHistoryTable() noexcept;
        ~WakeupHistoryTable() noexcept;

        void            NextWritebackPortA(Writeback bundle) noexcept;
        void            NextWritebackPortB(Writeback bundle) noexcept;

        void            NextReset() noexcept;

        QueryResult     CombQueryPortA(Query bundle) const noexcept;
        QueryResult     CombQueryPortB(Query bundle) const noexcept;

        void            Reset() noexcept;
        void            Eval() noexcept;
    };



    // Issue Queue
    class IssueQueue {
    public:
        using FIFOPosition          = std::bitset<9>;

        struct Wakeup {
            bool            enable;
            ROBIndex        rob;
            RegisterValue   value;
        };

        using PickOnehotEnable      = std::bitset<4>;

        struct PickWindowPort {
            bool                valid;
            PreIssueMicroCode   microcode;
            BranchPrediction    bp;
        };

        struct PickWindow {
            PickWindowPort      port[4];
        };

    private:
        struct Entry
        { 
            PreIssueMicroCode   microcode;
            BranchPrediction    bp;
        };

    private:
        SteppingDFF<FIFOPosition, DFFResetValue<uint16_t, 1>>   fifo_pos;

        Entry               queue[8];

        BeforeIssue         next_from_decode;
        BranchPrediction    next_from_decode_bp;

        Wakeup              next_wakeup0;
        Wakeup              next_wakeup1;

        PickOnehotEnable    next_pick_enable;

        bool                next_bco_valid;

        bool                next_reset;
    
    private:
        std::bitset<8>  _ExtendNextPickEnable() const noexcept;

        bool            _SignalEmpty() const noexcept;
        bool            _SignalFull() const noexcept;

        bool            _SignalFunctionallyPop() const noexcept;
        bool            _SignalFunctionallyPush() const noexcept;

        bool            _SignalPositionHold() const noexcept;
        bool            _SignalPositionPop() const noexcept;
        bool            _SignalPositionPush() const noexcept;

        std::bitset<8>  _SignalPositionShiftRight() const noexcept;

        std::bitset<8>  _SignalPositionValid() const noexcept;

        std::bitset<8>  _SignalFIFOShiftRight() const noexcept;
        std::bitset<8>  _SignalFIFOWrite() const noexcept;

        template<unsigned _Index>
        void            _IssueWindowPort(PickWindow& window, std::bitset<8> p_valid) const noexcept;

    public:
        IssueQueue() noexcept;
        ~IssueQueue() noexcept;

        void            NextFromDecode(BeforeIssue bundle, BranchPrediction bundle_bp) noexcept;

        void            NextWakeupPortA(Wakeup bundle) noexcept;
        void            NextWakeupPortB(Wakeup bundle) noexcept;

        void            NextPickEnable(PickOnehotEnable enable) noexcept;

        void            NextBranchCommitOverride(bool bco_valid) noexcept;

        void            NextReset() noexcept;

        FIFOPosition    GetLastFIFOPosition() const noexcept;
        PickWindow      GetLastPickWindow() const noexcept;

        void            Reset() noexcept;
        void            Eval() noexcept;
    };


    // Issue Queue Allocator
    class IssueQueueAllocator {
    private:
        SteppingDFF<bool>           readyn_sync1;
        SteppingDFF<bool>           readyn_sync2;
        SteppingDFF<bool>           readyn_sync3;
        SteppingDFF<bool>           readyn_sync4;

        IssueQueue::FIFOPosition    next_fifo_pos;
        bool                        next_valid;

        bool                        next_reset;

    private:
        bool            _SignalNotReady() const noexcept;

    public:
        IssueQueueAllocator() noexcept;
        ~IssueQueueAllocator() noexcept;

        void            NextFIFOPosition(IssueQueue::FIFOPosition fifo_pos) noexcept;
        void            NextValid(bool valid) noexcept;

        void            NextReset() noexcept;
        
        bool            CombNotReady() const noexcept;
        bool            CombAllocationEnable() const noexcept;

        void            Reset() noexcept;
        void            Eval() noexcept;
    };



    // Issue Pick (MicroCode) Core
    class Pick4Core {
    
    };

    // Issue Pick (MicroCode) Control Mux
    class Pick4MuxControl {

    };

    // Issue Pick (MicroCode) Data Mux
    class Pick4MuxData {

    };
}


// Implementation of: class WakeupHistoryTable
namespace BullsEye::Gemini30F2::Issue {
    //
    // Entry       wht0;
    // Entry       wht1;
    //
    // bool        next_reset;
    //

    WakeupHistoryTable::WakeupHistoryTable() noexcept
        : wht0          ()
        , wht1          ()
        , next_reset    (false)
    { }

    WakeupHistoryTable::~WakeupHistoryTable() noexcept
    { }

    inline bool WakeupHistoryTable::_QueryHit0(ROBIndex rob) const noexcept
    {
        return wht0.Get().valid && (wht0.Get().rob == rob);
    }

    inline bool WakeupHistoryTable::_QueryHit1(ROBIndex rob) const noexcept
    {
        return wht1.Get().valid && (wht1.Get().rob == rob);
    }

    inline WakeupHistoryTable::QueryResult WakeupHistoryTable::_Query(Query bundle) const noexcept
    {
        bool hit0 = _QueryHit0(bundle.rob);
        bool hit1 = _QueryHit1(bundle.rob);

        return QueryResult {
            .ready  = bundle.ready ? true : (hit0 || hit1),
            .value  = bundle.ready ? bundle.value 
                    : hit0         ? wht0.Get().value
                    :                wht1.Get().value
        };
    }

    inline void WakeupHistoryTable::NextWritebackPortA(Writeback bundle) noexcept
    {
        wht0.Next({
            .valid  = bundle.enable,
            .rob    = bundle.rob,
            .value  = bundle.value
        });
    }

    inline void WakeupHistoryTable::NextWritebackPortB(Writeback bundle) noexcept
    {
        wht1.Next({
            .valid  = bundle.enable,
            .rob    = bundle.rob,
            .value  = bundle.value
        });
    }

    inline void WakeupHistoryTable::NextReset() noexcept
    {
        next_reset = true;
    }

    inline WakeupHistoryTable::QueryResult WakeupHistoryTable::CombQueryPortA(Query bundle) const noexcept
    {
        return _Query(bundle);
    }

    inline WakeupHistoryTable::QueryResult WakeupHistoryTable::CombQueryPortB(Query bundle) const noexcept
    {
        return _Query(bundle);
    }

    void WakeupHistoryTable::Reset() noexcept
    {
        wht0.Reset();
        wht1.Reset();

        next_reset = false;
    }

    void WakeupHistoryTable::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }

        //
        wht0.Eval();
        wht1.Eval();
    }
}


// Implementation of: class IssueQueue
namespace BullsEye::Gemini30F2::Issue {
    //
    // SteppingDFF<FIFOPosition, DFFResetValue<uint16_t, 1>>   fifo_pos;
    //
    // Entry               queue[8];
    //
    // BeforeIssue         next_from_decode;
    // BranchPrediction    next_from_decode_bp;
    //
    // Wakeup              next_wakeup0;
    // Wakeup              next_wakeup1;
    //
    // PickOnehotEnable    next_pick_enable;
    //
    // bool                next_bco_valid;
    //
    // bool                next_reset;
    //

    IssueQueue::IssueQueue() noexcept
        : fifo_pos              ()
        , queue                 ()
        , next_from_decode      { .valid    = false }
        , next_from_decode_bp   ()
        , next_wakeup0          { .enable   = false }
        , next_wakeup1          { .enable   = false }
        , next_pick_enable      ()
        , next_bco_valid        (false)
        , next_reset            (false)
    { }

    IssueQueue::~IssueQueue() noexcept
    { }

    inline std::bitset<8> IssueQueue::_ExtendNextPickEnable() const noexcept
    {
        return std::bitset<8>(next_pick_enable.to_ulong());
    }

    inline bool IssueQueue::_SignalEmpty() const noexcept
    {
        return fifo_pos.Get()[0];
    }

    inline bool IssueQueue::_SignalFull() const noexcept
    {
        return fifo_pos.Get()[8];
    }

    inline bool IssueQueue::_SignalFunctionallyPop() const noexcept
    {
        return next_pick_enable.any() && !_SignalEmpty();
    }

    inline bool IssueQueue::_SignalFunctionallyPush() const noexcept
    {
        return next_from_decode.valid && !_SignalFull();
    }

    inline bool IssueQueue::_SignalPositionHold() const noexcept
    {
        return _SignalFunctionallyPop() && next_from_decode.valid;
    }

    inline bool IssueQueue::_SignalPositionPop() const noexcept
    {
        return !_SignalPositionHold() && _SignalFunctionallyPop();
    }

    inline bool IssueQueue::_SignalPositionPush() const noexcept
    {
        return !_SignalPositionHold() && _SignalFunctionallyPush();
    }

    std::bitset<8> IssueQueue::_SignalPositionShiftRight() const noexcept
    {
        std::bitset<8>  pick_en = _ExtendNextPickEnable();

        std::bitset<8>  shr;
        std::bitset<8>  shr_carrier;

        shr         [7] = false;
        shr_carrier [0] = false;

        for (int i = 0; i < 7; i++)
        {
            shr[i]              = pick_en[i] || shr_carrier[i];
            shr_carrier[i + 1]  = shr[i];
        }

        return shr;
    }

    std::bitset<8> IssueQueue::_SignalPositionValid() const noexcept
    {
        std::bitset<9>  fifo_pos = this->fifo_pos.Get();

        std::bitset<8>  valid;
        std::bitset<8>  valid_carrier;

        valid[7]            = fifo_pos[8];
        valid_carrier[7]    = valid[7];

        for (int i = 6; i >= 0; i--)
        {
            valid[i]            = fifo_pos[i + 1] || valid_carrier[i + 1];
            valid_carrier[i]    = valid[i];
        }

        return valid;
    }

    inline std::bitset<8> IssueQueue::_SignalFIFOShiftRight() const noexcept
    {
        return _SignalPositionShiftRight();
    }

    std::bitset<8> IssueQueue::_SignalFIFOWrite() const noexcept
    {
        std::bitset<8> p_shr = _SignalPositionShiftRight();

        std::bitset<8> fifo_write;

        for (int i = 0; i < 8; i++)
        {
            fifo_write[i] = next_from_decode.valid
                         && (p_shr[i] ? fifo_pos.Get()[i + 1] : fifo_pos.Get()[i])
                         && !next_bco_valid;
        }

        return fifo_write;
    }

    template<unsigned _Index>
    inline void IssueQueue::_IssueWindowPort(PickWindow& window, std::bitset<8> p_valid) const noexcept
    {
        //
        window.port[_Index].valid = p_valid[_Index] && !next_bco_valid;

        //
        window.port[_Index].microcode   = queue[_Index].microcode;
        window.port[_Index].bp          = queue[_Index].bp;
    }

    inline void IssueQueue::NextFromDecode(BeforeIssue bundle, BranchPrediction bundle_bp) noexcept
    {
        next_from_decode     = bundle;
        next_from_decode_bp  = bundle_bp;
    }

    inline void IssueQueue::NextWakeupPortA(Wakeup bundle) noexcept
    {
        next_wakeup0 = bundle;
    }

    inline void IssueQueue::NextWakeupPortB(Wakeup bundle) noexcept
    {
        next_wakeup1 = bundle;
    }

    inline void IssueQueue::NextPickEnable(PickOnehotEnable enable) noexcept
    {
        next_pick_enable = enable;
    }

    inline void IssueQueue::NextBranchCommitOverride(bool bco_valid) noexcept
    {
        next_bco_valid = bco_valid;
    }

    inline void IssueQueue::NextReset() noexcept
    {
        next_reset = true;
    }

    inline IssueQueue::FIFOPosition IssueQueue::GetLastFIFOPosition() const noexcept
    {
        return fifo_pos.Get();
    }

    inline IssueQueue::PickWindow IssueQueue::GetLastPickWindow() const noexcept
    {
        PickWindow window;

        std::bitset<8> p_valid = _SignalPositionValid();

        _IssueWindowPort<0>(window, p_valid);
        _IssueWindowPort<1>(window, p_valid);
        _IssueWindowPort<2>(window, p_valid);
        _IssueWindowPort<3>(window, p_valid);

        return window;
    }

    void IssueQueue::Reset() noexcept
    {
        fifo_pos.Reset();

        next_reset = false;
    }

    void IssueQueue::Eval() noexcept
    {
        // 
        if (next_reset)
        {
            Reset();
            return;
        }

        //
        if (next_bco_valid)
            fifo_pos.NextReset();
        else if (_SignalPositionPop())
            fifo_pos.Next(fifo_pos.Get() >> 1);
        else if (_SignalPositionPush())
            fifo_pos.Next(fifo_pos.Get() << 1);

        
        //
        std::bitset<8> p_fifo_shr   = _SignalFIFOShiftRight(); 
        std::bitset<8> p_fifo_write = _SignalFIFOWrite();

        for (int i = 0; i < 8; i++)
        {
            if (p_fifo_write[i])
            {
                bool wakeup0_hit = next_wakeup0.enable && next_wakeup0.rob == next_from_decode.src0_rob;
                bool wakeup1_hit = next_wakeup1.enable && next_wakeup1.rob == next_from_decode.src0_rob;

                queue[i].microcode.src0_rob     = next_from_decode.src0_rob;
                
                queue[i].microcode.src0_ready   = next_from_decode.src0_ready
                                               || (wakeup0_hit)
                                               || (wakeup1_hit);

                queue[i].microcode.src0_value   = (wakeup0_hit && !next_from_decode.src0_ready) ? next_wakeup0.value
                                                : (wakeup1_hit && !next_from_decode.src0_ready) ? next_wakeup1.value
                                                : next_from_decode.src0_value;
            }
            else if (p_fifo_shr[i])
            {
                if (i < 7)
                {
                    queue[i].microcode.src0_rob = queue[i + 1].microcode.src0_rob;

                    if (!queue[i].microcode.src0_ready && next_wakeup0.enable && (next_wakeup0.rob == queue[i].microcode.src0_rob))
                    {
                        queue[i].microcode.src0_ready = true;
                        queue[i].microcode.src0_value = next_wakeup0.value;
                    }
                    else if (!queue[i].microcode.src0_ready && next_wakeup1.enable && (next_wakeup1.rob == queue[i].microcode.src0_rob))
                    {
                        queue[i].microcode.src0_ready = true;
                        queue[i].microcode.src0_value = next_wakeup1.value;
                    }
                    else
                    {
                        queue[i].microcode.src0_ready = queue[i + 1].microcode.src0_ready;
                        queue[i].microcode.src0_value = queue[i + 1].microcode.src0_value;
                    }
                }
            }
            else if (!queue[i].microcode.src0_ready)
            {
                if (next_wakeup0.enable && (next_wakeup0.rob == queue[i].microcode.src0_rob))
                {
                    queue[i].microcode.src0_ready = true;
                    queue[i].microcode.src0_value = next_wakeup0.value;
                }
                else if (next_wakeup1.enable && (next_wakeup1.rob == queue[i].microcode.src0_rob))
                {
                    queue[i].microcode.src0_ready = true;
                    queue[i].microcode.src0_value = next_wakeup1.value;
                }
            }
        }

        for (int i = 0; i < 8; i++)
        {
            if (p_fifo_write[i])
            {
                bool wakeup0_hit = next_wakeup0.enable && next_wakeup0.rob == next_from_decode.src1_rob;
                bool wakeup1_hit = next_wakeup1.enable && next_wakeup1.rob == next_from_decode.src1_rob;

                queue[i].microcode.src1_rob     = next_from_decode.src1_rob;
                
                queue[i].microcode.src1_ready   = next_from_decode.src1_ready
                                               || (wakeup0_hit)
                                               || (wakeup1_hit);

                queue[i].microcode.src1_value   = (wakeup0_hit && !next_from_decode.src1_ready) ? next_wakeup0.value
                                                : (wakeup1_hit && !next_from_decode.src1_ready) ? next_wakeup1.value
                                                : next_from_decode.src1_value;
            }
            else if (p_fifo_shr[i])
            {
                if (i < 7)
                {
                    queue[i].microcode.src1_rob = queue[i + 1].microcode.src1_rob;

                    if (!queue[i].microcode.src1_ready && next_wakeup0.enable && (next_wakeup0.rob == queue[i].microcode.src1_rob))
                    {
                        queue[i].microcode.src1_ready = true;
                        queue[i].microcode.src1_value = next_wakeup0.value;
                    }
                    else if (!queue[i].microcode.src1_ready && next_wakeup1.enable && (next_wakeup1.rob == queue[i].microcode.src1_rob))
                    {
                        queue[i].microcode.src1_ready = true;
                        queue[i].microcode.src1_value = next_wakeup1.value;
                    }
                    else
                    {
                        queue[i].microcode.src1_ready = queue[i + 1].microcode.src1_ready;
                        queue[i].microcode.src1_value = queue[i + 1].microcode.src1_value;
                    }
                }
            }
            else if (!queue[i].microcode.src1_ready)
            {
                if (next_wakeup0.enable && (next_wakeup0.rob == queue[i].microcode.src1_rob))
                {
                    queue[i].microcode.src1_ready = true;
                    queue[i].microcode.src1_value = next_wakeup0.value;
                }
                else if (next_wakeup1.enable && (next_wakeup1.rob == queue[i].microcode.src1_rob))
                {
                    queue[i].microcode.src1_ready = true;
                    queue[i].microcode.src1_value = next_wakeup1.value;
                }
            }
        }


        //
        for (int i = 0; i < 8; i++)
        {
            if (p_fifo_write[i])
            {
                queue[i].microcode.pc       = next_from_decode.pc;
                queue[i].microcode.imm      = next_from_decode.imm;
                queue[i].microcode.dst_rob  = next_from_decode.dst_rob;

                queue[i].microcode.fid      = next_from_decode.fid;

                queue[i].microcode.branch   = next_from_decode.branch;
                queue[i].microcode.load     = next_from_decode.load;
                queue[i].microcode.store    = next_from_decode.store;

                queue[i].microcode.pipe_alu = next_from_decode.pipe_alu;
                queue[i].microcode.pipe_mul = next_from_decode.pipe_mul;
                queue[i].microcode.pipe_mem = next_from_decode.pipe_mem;
                queue[i].microcode.pipe_bru = next_from_decode.pipe_bru;

                queue[i].microcode.alu_cmd  = next_from_decode.alu_cmd;
                queue[i].microcode.mul_cmd  = next_from_decode.mul_cmd;
                queue[i].microcode.mem_cmd  = next_from_decode.mem_cmd;
                queue[i].microcode.bru_cmd  = next_from_decode.bru_cmd;
                queue[i].microcode.bagu_cmd = next_from_decode.bagu_cmd;

                queue[i].bp.pattern = next_from_decode_bp.pattern;
                queue[i].bp.taken   = next_from_decode_bp.taken;
                queue[i].bp.hit     = next_from_decode_bp.hit;
                queue[i].bp.target  = next_from_decode_bp.target;
            }
            else if (p_fifo_shr[i] && i < 7)
            {
                queue[i].microcode.pc       = queue[i + 1].microcode.pc;
                queue[i].microcode.imm      = queue[i + 1].microcode.imm;
                queue[i].microcode.dst_rob  = queue[i + 1].microcode.dst_rob;

                queue[i].microcode.fid      = queue[i + 1].microcode.fid;

                queue[i].microcode.branch   = queue[i + 1].microcode.branch;
                queue[i].microcode.load     = queue[i + 1].microcode.load;
                queue[i].microcode.store    = queue[i + 1].microcode.store;

                queue[i].microcode.pipe_alu = queue[i + 1].microcode.pipe_alu;
                queue[i].microcode.pipe_mul = queue[i + 1].microcode.pipe_mul;
                queue[i].microcode.pipe_mem = queue[i + 1].microcode.pipe_mem;
                queue[i].microcode.pipe_bru = queue[i + 1].microcode.pipe_bru;

                queue[i].microcode.alu_cmd  = queue[i + 1].microcode.alu_cmd;
                queue[i].microcode.mul_cmd  = queue[i + 1].microcode.mul_cmd;
                queue[i].microcode.mem_cmd  = queue[i + 1].microcode.mem_cmd;
                queue[i].microcode.bru_cmd  = queue[i + 1].microcode.bru_cmd;
                queue[i].microcode.bagu_cmd = queue[i + 1].microcode.bagu_cmd;

                queue[i].bp.pattern = queue[i + 1].bp.pattern;
                queue[i].bp.taken   = queue[i + 1].bp.taken;
                queue[i].bp.hit     = queue[i + 1].bp.hit;
                queue[i].bp.target  = queue[i + 1].bp.target;
            }
        }

        //
        fifo_pos.Eval();
    }
}


// Implementation of: class IssueQueueAllocator
namespace BullsEye::Gemini30F2::Issue {
    //
    // SteppingDFF<bool>           readyn_sync1;
    // SteppingDFF<bool>           readyn_sync2;
    // SteppingDFF<bool>           readyn_sync3;
    // SteppingDFF<bool>           readyn_sync4;
    //
    // IssueQueue::FIFOPosition    next_fifo_pos;
    // bool                        next_valid;
    //
    // bool                        next_reset;
    //

    IssueQueueAllocator::IssueQueueAllocator() noexcept
        : readyn_sync1  ()
        , readyn_sync2  ()
        , readyn_sync3  ()
        , readyn_sync4  ()
        , next_fifo_pos ()
        , next_valid    ()
        , next_reset    (false)
    { }

    IssueQueueAllocator::~IssueQueueAllocator() noexcept
    { }

    inline bool IssueQueueAllocator::_SignalNotReady() const noexcept
    {
        return next_fifo_pos.test(8) 
            || next_fifo_pos.test(7) 
            || next_fifo_pos.test(6)
            || next_fifo_pos.test(5)
            || next_fifo_pos.test(4)
            || next_fifo_pos.test(3);
    }

    inline void IssueQueueAllocator::NextFIFOPosition(IssueQueue::FIFOPosition fifo_pos) noexcept
    {
        next_fifo_pos = fifo_pos;
    }
    
    inline void IssueQueueAllocator::NextValid(bool valid) noexcept
    {
        next_valid = valid;
    }

    inline void IssueQueueAllocator::NextReset() noexcept
    {
        next_reset = true;
    }

    inline bool IssueQueueAllocator::CombNotReady() const noexcept
    {
        return _SignalNotReady();
    }

    inline bool IssueQueueAllocator::CombAllocationEnable() const noexcept
    {
        return next_valid && !readyn_sync4.Get();
    }

    void IssueQueueAllocator::Reset() noexcept
    {
        readyn_sync1.Reset();
        readyn_sync2.Reset();
        readyn_sync3.Reset();
        readyn_sync4.Reset();

        next_reset = false;
    }

    void IssueQueueAllocator::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        } 

        //
        readyn_sync1.Next(_SignalNotReady());
        readyn_sync2.Next(readyn_sync1.Get());
        readyn_sync3.Next(readyn_sync2.Get());
        readyn_sync4.Next(readyn_sync3.Get());

        //
        readyn_sync1.Eval();
        readyn_sync2.Eval();
        readyn_sync3.Eval();
        readyn_sync4.Eval();
    }
}


// Implementation of: class Pick4Core
namespace BullsEye::Gemini30F2::Issue {

}
