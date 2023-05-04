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
        SteppingDFF<Entry, decltype([] (Entry& obj) {
            obj.valid = false;
        })>         wht0;

        SteppingDFF<Entry, decltype([] (Entry& obj) {
            obj.valid = false;
        })>         wht1;

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
        SteppingDFF<FIFOPosition, DFFResetValue<1>> fifo_pos;

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
    public:
        using ForwardOnehotEnable       = std::bitset<4>;

        using PickOnehotEnable          = IssueQueue::PickOnehotEnable;

        using PickIndex                 = uint2_t;

        struct PickInfo {
            PickOnehotEnable        pick_enable;
            PickIndex               pick_index;

            ForwardOnehotEnable     forward_src0_enable;
            ForwardOnehotEnable     forward_src1_enable;
        };

        struct PostPick {
            bool                    valid;

            ROBIndex                dst_rob;

            bool                    pipe_alu;
            bool                    pipe_mul;
            bool                    pipe_mem;
            bool                    pipe_bru;
        };
    
    private:
        struct ALUForward {
            bool                valid;
            ROBIndex            rob;
        };

        using APHD      = std::bitset<4>;

    private:
        SteppingDFF<ALUForward>     alu_forward;
        SteppingDFF<APHD>           aphd;

        PickInfo                    comb_pick_info;
        PostPick                    comb_post_pick;

        IssueQueue::PickWindow      next_pick_window;

        bool                        next_bco_valid;

        bool                        next_reset;

    private:
        std::bitset<4>  _FenceNormal() const noexcept;
        std::bitset<4>  _FenceBranch() const noexcept;
        std::bitset<4>  _FenceLoadStore() const noexcept;

        std::bitset<4>  _APHDTest() const noexcept;

        std::bitset<4>  _PrepickForwardSrc0() const noexcept;
        std::bitset<4>  _PrepickForwardSrc1() const noexcept;

        std::bitset<4>  _PrepickReadySrc0(std::bitset<4> prepick_forward_src0) const noexcept;
        std::bitset<4>  _PrepickReadySrc1(std::bitset<4> prepick_forward_src1) const noexcept;
        std::bitset<4>  _PrepickReady(std::bitset<4> prepick_forward_src0, std::bitset<4> prepick_forward_src1) const noexcept;

        std::bitset<4>  _PickReady(std::bitset<4> prepick_forward_src0, std::bitset<4> prepick_forward_src1) const noexcept;

    public:
        Pick4Core() noexcept;
        ~Pick4Core() noexcept;

        void            NextPickWindow(IssueQueue::PickWindow bundle) noexcept;

        void            NextBranchCommitOverride(bool bco_valid) noexcept;

        void            NextReset() noexcept;

        PickInfo        GetCombPickInfo() const noexcept;
        PostPick        GetCombPostPick() const noexcept;

        void            Comb() noexcept;

        void            Reset() noexcept;
        void            Eval() noexcept;
    };


    // Issue Pick (MicroCode) Control Mux
    class Pick4MuxControl {
    public:
        using PickInfo          = Pick4Core::PickInfo;

        struct PostPick {
            bool                    valid;

            Global::PC              pc;

            ROBIndex                dst_rob;

            Decode::Immediate       imm;

            Global::FID             fid;

            bool                    pipe_alu;
            bool                    pipe_mul;
            bool                    pipe_mem;
            bool                    pipe_bru;

            Decode::ALUCommand      alu_cmd;
            Decode::MULCommand      mul_cmd;
            Decode::MEMCommand      mem_cmd;
            Decode::BRUCommand      bru_cmd;
            Decode::BAGUCommand     bagu_cmd;
        };

    private:
        Pick4Core               module_pick_core;

        PostPick                comb_post_pick;

        IssueQueue::PickWindow  next_pick_window;

        bool                    next_reset;

    public:
        Pick4MuxControl() noexcept;
        ~Pick4MuxControl() noexcept;

        void            NextPickWindow(IssueQueue::PickWindow bundle) noexcept;

        void            NextBranchCommitOverride(bool bco_valid) noexcept;

        void            NextReset() noexcept;

        PostPick        GetCombPostPick() const noexcept;
        PickInfo        GetCombPickInfo() const noexcept;

        void            Comb() noexcept;

        void            Reset() noexcept;
        void            Eval() noexcept;
    };


    // Issue Pick (MicroCode) Data Mux
    class Pick4MuxData {
    public:
        using PickInfo          = Pick4Core::PickInfo;

        struct PostPick {
            RegisterValue       src0_value;
            bool                src0_forward_alu;

            RegisterValue       src1_value;
            bool                src1_forward_alu;

            BranchPrediction    branch_prediction;
        };

    private:
        Pick4Core               module_pick_core;

        PostPick                comb_post_pick;

        IssueQueue::PickWindow  next_pick_window;

        bool                    next_reset;

    public:
        Pick4MuxData() noexcept;
        ~Pick4MuxData() noexcept;

        void            NextPickWindow(IssueQueue::PickWindow bundle) noexcept;

        void            NextBranchCommitOverride(bool bco_valid) noexcept;

        void            NextReset() noexcept;

        PostPick        GetCombPostPick() const noexcept;
        PickInfo        GetCombPickInfo() const noexcept;

        void            Comb() noexcept;

        void            Reset() noexcept;
        void            Eval() noexcept;
    };


    // Issue Pick-4
    class Pick4 {
    public:
        using PickInfo =        Pick4Core::PickInfo;

        struct PostPick {
            bool                valid;

            Global::PC          pc;

            RegisterValue       src0_value;
            bool                src0_forward_alu;

            RegisterValue       src1_value;
            bool                src1_forward_alu;

            ROBIndex            dst_rob;

            Decode::Immediate   imm;

            Global::FID         fid;

            bool                pipe_alu;
            bool                pipe_mul;
            bool                pipe_mem;
            bool                pipe_bru;

            Decode::ALUCommand  alu_cmd;
            Decode::MULCommand  mul_cmd;
            Decode::MEMCommand  mem_cmd;
            Decode::BRUCommand  bru_cmd;
            Decode::BAGUCommand bagu_cmd;

            BranchPrediction    branch_prediction;
        };

    private:
        Pick4MuxControl     module_mux_control;
        Pick4MuxData        module_mux_data;

        PostPick            comb_post_pick;

        bool                next_reset;

    public:
        Pick4() noexcept;
        ~Pick4() noexcept;

        void            NextPickWindow(IssueQueue::PickWindow bundle) noexcept;

        void            NextBranchCommitOverride(bool bco_valid) noexcept;

        void            NextReset() noexcept;

        PostPick        GetCombPostPick() const noexcept;
        PickInfo        GetCombPickInfo() const noexcept;

        void            Comb() noexcept;

        void            Reset() noexcept;
        void            Eval() noexcept;
    };



    // Before-Stage DFFs
    class BeforeStageDFFs {
    public:
        using BranchPrediction      = BranchPrediction;

        using FromDecode            = BeforeIssue;

        struct Writeback {
            bool                enable;
            ROBIndex            dst_rob;
            RegisterValue       value;
            bool                lsmiss;
        };
        
    private:
        SteppingDFF<BranchPrediction>   dff_branch_prediction;

        SteppingDFF<FromDecode, decltype([] (FromDecode& obj) {
            obj.valid   = false;
        })>                             dff_from_decode;

        SteppingDFF<Writeback, decltype([] (Writeback& obj) {
            obj.enable  = false;
        })>                             dff_writeback;

        bool                            next_bco_valid;

    public:
        BeforeStageDFFs() noexcept;
        ~BeforeStageDFFs() noexcept;

        void                NextBranchPrediction(BranchPrediction bundle) noexcept;
        void                NextFromDecode(FromDecode bundle) noexcept;
        void                NextWriteback(Writeback bundle) noexcept;

        void                NextBranchCommitOverride(bool bco_valid) noexcept;

        void                NextReset() noexcept;

        BranchPrediction    GetLastBranchPrediction() const noexcept;
        FromDecode          GetLastFromDecode() const noexcept;
        Writeback           GetLastWriteback() const noexcept;

        void                Reset();
        void                Eval();
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
    //
    // SteppingDFF<ALUForward>     forward;
    // SteppingDFF<APHD>           aphd;
    //
    // PickInfo                    last_pick_info;
    // PostPick                    last_post_pick;
    //
    // IssueQueue::PickWindow      next_pick_window;
    //
    // bool                        next_bco_valid;
    //
    // bool                        next_reset;
    //

    Pick4Core::Pick4Core() noexcept
        : alu_forward       ()
        , aphd              ()
        , comb_pick_info    { .pick_enable  = false }
        , comb_post_pick    { .valid        = false }
        , next_pick_window  ()
        , next_bco_valid    ()
        , next_reset        (false)
    { }

    Pick4Core::~Pick4Core() noexcept
    { }

    inline std::bitset<4> Pick4Core::_FenceNormal() const noexcept
    {
        return std::bitset<4>();
    }

    std::bitset<4> Pick4Core::_FenceBranch() const noexcept
    {
        std::bitset<4> fence_b;
        std::bitset<4> fence_b_carrier;

        fence_b         [0] = false;
        fence_b_carrier [0] = false;

        for (int i = 1; i < 4; i++)
        {
            fence_b_carrier [i] = next_pick_window.port[i - 1].microcode.branch || fence_b_carrier[i - 1];
            fence_b         [i] = next_pick_window.port[i].microcode.branch && fence_b_carrier[i];
        }

        return fence_b;
    }

    std::bitset<4> Pick4Core::_FenceLoadStore() const noexcept
    {
        std::bitset<4> fence_ls;
        std::bitset<4> fence_ls_carrier;

        fence_ls        [0] = false;
        fence_ls_carrier[0] = false;

        for (int i = 1; i < 4; i++)
        {
            fence_ls_carrier[i] = next_pick_window.port[i - 1].microcode.store || fence_ls_carrier[i - 1];
            fence_ls        [i] = (next_pick_window.port[i].microcode.store || next_pick_window.port[i].microcode.load) && fence_ls_carrier[i];
        }

        return fence_ls;
    }

    std::bitset<4> Pick4Core::_APHDTest() const noexcept
    {
        std::bitset<4> aphd = this->aphd.Get();

        std::bitset<4> aphd_hit;

        for (int i = 0; i < 4; i++)
        {
            aphd_hit[i] = next_pick_window.port[i].microcode.pipe_alu ? aphd[1 - 1]
                        : next_pick_window.port[i].microcode.pipe_mul ? aphd[3 - 1]
                        : next_pick_window.port[i].microcode.pipe_mem ? aphd[3 - 1]
                        : next_pick_window.port[i].microcode.pipe_bru ? aphd[1 - 1]
                        : false;
        }

        return aphd_hit;
    }

    std::bitset<4> Pick4Core::_PrepickForwardSrc0() const noexcept
    {
        std::bitset<4>  prepick_forward_src0;

        for (int i = 0; i < 4; i++)
        {
            prepick_forward_src0[i] = !next_pick_window.port[i].microcode.src0_ready
                                   &&  alu_forward.Get().valid
                                   && (next_pick_window.port[i].microcode.src0_rob == alu_forward.Get().rob);
        }

        return prepick_forward_src0;
    }

    std::bitset<4> Pick4Core::_PrepickForwardSrc1() const noexcept
    {
        std::bitset<4>  prepick_forward_src1;

        for (int i = 0; i < 4; i++)
        {
            prepick_forward_src1[i] = !next_pick_window.port[i].microcode.src1_ready
                                   &&  alu_forward.Get().valid
                                   && (next_pick_window.port[i].microcode.src1_rob == alu_forward.Get().rob);
        }

        return prepick_forward_src1;
    }

    std::bitset<4> Pick4Core::_PrepickReadySrc0(std::bitset<4> prepick_forward_src0) const noexcept
    {
        std::bitset<4> prepick_ready_src0;

        for (int i = 0; i < 4; i++)
        {
            prepick_ready_src0[i] = next_pick_window.port[i].microcode.src0_ready
                                 || prepick_forward_src0[i];
        }

        return prepick_ready_src0;
    }

    std::bitset<4> Pick4Core::_PrepickReadySrc1(std::bitset<4> prepick_forward_src1) const noexcept
    {
        std::bitset<4> prepick_ready_src1;

        for (int i = 0; i < 4; i++)
        {
            prepick_ready_src1[i] = next_pick_window.port[i].microcode.src1_ready
                                 || prepick_forward_src1[i];
        }

        return prepick_ready_src1;
    }

    std::bitset<4> Pick4Core::_PrepickReady(std::bitset<4> prepick_forward_src0, std::bitset<4> prepick_forward_src1) const noexcept
    {
        std::bitset<4> prepick_ready;

        for (int i = 0; i < 4; i++)
            prepick_ready[i] = next_pick_window.port[i].valid;

        return prepick_ready & _PrepickReadySrc0(prepick_forward_src0) & _PrepickReadySrc1(prepick_forward_src1);
    }

    inline std::bitset<4> Pick4Core::_PickReady(std::bitset<4> prepick_forward_src0, std::bitset<4> prepick_forward_src1) const noexcept
    {
        return _PrepickReady(prepick_forward_src0, prepick_forward_src1) & _FenceNormal() & _FenceBranch() & _FenceLoadStore() & _APHDTest();
    }

    inline void Pick4Core::NextPickWindow(IssueQueue::PickWindow bundle) noexcept
    {
        next_pick_window = bundle;
    }

    inline void Pick4Core::NextBranchCommitOverride(bool bco_valid) noexcept
    {
        next_bco_valid = bco_valid;
    }

    inline void Pick4Core::NextReset() noexcept
    {
        next_reset = true;
    }

    inline Pick4Core::PickInfo Pick4Core::GetCombPickInfo() const noexcept
    {
        return comb_pick_info;
    }

    inline Pick4Core::PostPick Pick4Core::GetCombPostPick() const noexcept
    {
        return comb_post_pick;
    }

    void Pick4Core::Comb() noexcept
    {
        //
        std::bitset<4> prepick_forward_src0 = _PrepickForwardSrc0();
        std::bitset<4> prepick_forward_src1 = _PrepickForwardSrc1();

        std::bitset<4> pick_ready = _PickReady(prepick_forward_src0, prepick_forward_src1);

        //
        comb_pick_info.pick_enable = pick_ready;

        comb_pick_info.pick_index = pick_ready[0] ? 0
                                  : pick_ready[1] ? 1
                                  : pick_ready[2] ? 2
                                  : pick_ready[3] ? 3
                                  :                 0;

        comb_pick_info.forward_src0_enable = prepick_forward_src0;
        comb_pick_info.forward_src1_enable = prepick_forward_src1;

        //
        comb_post_pick.valid = pick_ready.any();

        comb_post_pick.dst_rob  = next_pick_window.port[comb_pick_info.pick_index].microcode.dst_rob;

        comb_post_pick.pipe_alu = next_pick_window.port[comb_pick_info.pick_index].microcode.pipe_alu;
        comb_post_pick.pipe_mul = next_pick_window.port[comb_pick_info.pick_index].microcode.pipe_mul;
        comb_post_pick.pipe_mem = next_pick_window.port[comb_pick_info.pick_index].microcode.pipe_mem;
        comb_post_pick.pipe_bru = next_pick_window.port[comb_pick_info.pick_index].microcode.pipe_bru;
    }

    void Pick4Core::Reset() noexcept
    {
        alu_forward.Reset();
        aphd.Reset();

        comb_pick_info.pick_enable = false;
        comb_post_pick.valid       = false;

        next_reset = false;
    }

    void Pick4Core::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }

        
        //
        alu_forward.Next({
            .valid = comb_post_pick.valid && comb_post_pick.pipe_alu,
            .rob   = comb_post_pick.dst_rob
        });


        //
        std::bitset<4> aphd_next = aphd.Get();

        aphd_next >>= 1;

        if (comb_post_pick.valid)
        {
            if (comb_post_pick.pipe_alu)
                ;
            else if (comb_post_pick.pipe_mul)
                aphd_next[3 - 2] = true;
            else if (comb_post_pick.pipe_mem)
                aphd_next[3 - 2] = true;
            else if (comb_post_pick.pipe_bru)
                ;
        }

        aphd.Next(aphd_next);


        //
        alu_forward.Eval();
        aphd.Eval();
    }
}


// Implementation of: class Pick4MuxControl
namespace BullsEye::Gemini30F2::Issue {
    //
    // Pick4Core               module_pick_core;
    //
    // PostPick                last_post_pick;
    //
    // IssueQueue::PickWindow  next_pick_window;
    //
    // bool                    next_reset;
    //

    Pick4MuxControl::Pick4MuxControl() noexcept
        : module_pick_core  ()
        , comb_post_pick    { .valid    = false }
        , next_pick_window  ()
        , next_reset        (false)
    { }

    Pick4MuxControl::~Pick4MuxControl() noexcept
    { }

    inline void Pick4MuxControl::NextPickWindow(IssueQueue::PickWindow bundle) noexcept
    {
        next_pick_window = bundle;

        module_pick_core.NextPickWindow(bundle);
    }

    inline void Pick4MuxControl::NextBranchCommitOverride(bool bco_valid) noexcept
    {
        module_pick_core.NextBranchCommitOverride(bco_valid);
    }

    inline void Pick4MuxControl::NextReset() noexcept
    {
        next_reset = true;
    }

    inline Pick4MuxControl::PostPick Pick4MuxControl::GetCombPostPick() const noexcept
    {
        return comb_post_pick;
    }

    inline Pick4MuxControl::PickInfo Pick4MuxControl::GetCombPickInfo() const noexcept
    {
        return module_pick_core.GetCombPickInfo();
    }

    void Pick4MuxControl::Comb() noexcept
    {
        Pick4Core::PickInfo pick_info = module_pick_core.GetCombPickInfo();
        Pick4Core::PostPick post_pick = module_pick_core.GetCombPostPick();

        //
        comb_post_pick.pc       = next_pick_window.port[pick_info.pick_index].microcode.pc;

        comb_post_pick.imm      = next_pick_window.port[pick_info.pick_index].microcode.imm;

        comb_post_pick.fid      = next_pick_window.port[pick_info.pick_index].microcode.fid;

        comb_post_pick.alu_cmd  = next_pick_window.port[pick_info.pick_index].microcode.alu_cmd;
        comb_post_pick.mul_cmd  = next_pick_window.port[pick_info.pick_index].microcode.mul_cmd;
        comb_post_pick.mem_cmd  = next_pick_window.port[pick_info.pick_index].microcode.mem_cmd;
        comb_post_pick.bru_cmd  = next_pick_window.port[pick_info.pick_index].microcode.bru_cmd;
        comb_post_pick.bagu_cmd = next_pick_window.port[pick_info.pick_index].microcode.bagu_cmd;

        //
        comb_post_pick.valid    = post_pick.valid;

        comb_post_pick.dst_rob  = post_pick.dst_rob;

        comb_post_pick.pipe_alu = post_pick.pipe_alu;
        comb_post_pick.pipe_mul = post_pick.pipe_mul;
        comb_post_pick.pipe_mem = post_pick.pipe_mem;
        comb_post_pick.pipe_bru = post_pick.pipe_bru;
    }

    void Pick4MuxControl::Reset() noexcept
    {
        module_pick_core.Reset();

        comb_post_pick.valid = false;

        next_reset = false;
    }

    void Pick4MuxControl::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }

        //
        module_pick_core.Eval();
    }
}


// Implementation of: class Pick4MuxData 
namespace BullsEye::Gemini30F2::Issue {
    //
    // Pick4Core               module_pick_core;
    //
    // PostPick                comb_post_pick;
    //
    // IssueQueue::PickWindow  next_pick_window;
    //
    // bool                    next_reset;
    //

    Pick4MuxData::Pick4MuxData() noexcept
        : module_pick_core  ()
        , comb_post_pick    ()
        , next_pick_window  ()
        , next_reset        ()
    { }

    Pick4MuxData::~Pick4MuxData() noexcept
    { }

    inline void Pick4MuxData::NextPickWindow(IssueQueue::PickWindow bundle) noexcept
    {
        next_pick_window = bundle;

        module_pick_core.NextPickWindow(bundle);
    }

    inline void Pick4MuxData::NextBranchCommitOverride(bool bco_valid) noexcept
    {
        module_pick_core.NextBranchCommitOverride(bco_valid);
    }

    inline void Pick4MuxData::NextReset() noexcept
    {
        next_reset = true;
    }

    inline Pick4MuxData::PostPick Pick4MuxData::GetCombPostPick() const noexcept
    {
        return comb_post_pick;
    }

    inline Pick4MuxData::PickInfo Pick4MuxData::GetCombPickInfo() const noexcept
    {
        return module_pick_core.GetCombPickInfo();
    }

    void Pick4MuxData::Comb() noexcept
    {
        Pick4Core::PickInfo pick_info = module_pick_core.GetCombPickInfo();
        Pick4Core::PostPick post_pick = module_pick_core.GetCombPostPick();

        //
        comb_post_pick.src0_value           = next_pick_window.port[pick_info.pick_index].microcode.src0_value;
        comb_post_pick.src0_forward_alu     = pick_info.forward_src0_enable[pick_info.pick_index];

        comb_post_pick.src1_value           = next_pick_window.port[pick_info.pick_index].microcode.src1_value;
        comb_post_pick.src1_forward_alu     = pick_info.forward_src1_enable[pick_info.pick_index];

        comb_post_pick.branch_prediction    = next_pick_window.port[pick_info.pick_index].bp;
    }

    void Pick4MuxData::Reset() noexcept
    {
        module_pick_core.Reset();

        next_reset = false;
    }

    void Pick4MuxData::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }

        //
        module_pick_core.Eval();
    }
}


// Implementation of: class Pick4
namespace BullsEye::Gemini30F2::Issue {
    //
    // Pick4MuxControl     module_mux_control;
    // Pick4MuxData        module_mux_data;
    //
    // PostPick            comb_post_pick;
    //
    // bool                next_reset;
    //

    Pick4::Pick4() noexcept
        : module_mux_control    ()
        , module_mux_data       ()
        , comb_post_pick        { .valid = false }
        , next_reset            (false)
    { }

    Pick4::~Pick4() noexcept
    { }

    inline void Pick4::NextPickWindow(IssueQueue::PickWindow bundle) noexcept
    {
        module_mux_control  .NextPickWindow(bundle);
        module_mux_data     .NextPickWindow(bundle);
    }

    inline void Pick4::NextBranchCommitOverride(bool bco_valid) noexcept
    {
        module_mux_control  .NextBranchCommitOverride(bco_valid);
        module_mux_data     .NextBranchCommitOverride(bco_valid);
    }

    inline void Pick4::NextReset() noexcept
    {
        next_reset = true;
    }

    inline Pick4::PostPick Pick4::GetCombPostPick() const noexcept
    {
        return comb_post_pick;
    }

    inline Pick4::PickInfo Pick4::GetCombPickInfo() const noexcept
    {
        return module_mux_control.GetCombPickInfo();
    }

    void Pick4::Comb() noexcept
    {
        module_mux_control.Comb();
        module_mux_data   .Comb();

        //
        Pick4MuxControl::PostPick   post_pick_control   = module_mux_control.GetCombPostPick();
        Pick4MuxData::PostPick      post_pick_data      = module_mux_data   .GetCombPostPick();

        //
        comb_post_pick.valid        = post_pick_control.valid;

        comb_post_pick.pc           = post_pick_control.pc;

        comb_post_pick.dst_rob      = post_pick_control.dst_rob;

        comb_post_pick.imm          = post_pick_control.imm;

        comb_post_pick.fid          = post_pick_control.fid;

        comb_post_pick.pipe_alu     = post_pick_control.pipe_alu;
        comb_post_pick.pipe_mul     = post_pick_control.pipe_mul;
        comb_post_pick.pipe_mem     = post_pick_control.pipe_mem;
        comb_post_pick.pipe_bru     = post_pick_control.pipe_bru;
        
        comb_post_pick.alu_cmd      = post_pick_control.alu_cmd;
        comb_post_pick.mul_cmd      = post_pick_control.mul_cmd;
        comb_post_pick.mem_cmd      = post_pick_control.mem_cmd;
        comb_post_pick.bru_cmd      = post_pick_control.bru_cmd;
        comb_post_pick.bagu_cmd     = post_pick_control.bagu_cmd;

        //
        comb_post_pick.src0_value           = post_pick_data.src0_value;
        comb_post_pick.src0_forward_alu     = post_pick_data.src0_forward_alu;

        comb_post_pick.src1_value           = post_pick_data.src1_value;
        comb_post_pick.src1_forward_alu     = post_pick_data.src1_forward_alu;

        //
        comb_post_pick.branch_prediction    = post_pick_data.branch_prediction;
    }

    void Pick4::Reset() noexcept
    {
        module_mux_control.Reset();
        module_mux_data   .Reset();

        comb_post_pick.valid = false;
    }

    void Pick4::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }

        //
        module_mux_control.Eval();
        module_mux_data   .Eval();
    }
}


// Implementation of: class BeforeStageDFFs
namespace BullsEye::Gemini30F2::Issue {
    //
    // SteppingDFF<BranchPrediction>   dff_branch_prediction;
    //
    // SteppingDFF<FromDecode, decltype([] (FromDecode& obj) {
    //     obj.valid   = false;
    // })>                             dff_from_decode;
    //
    // SteppingDFF<Writeback, decltype([] (Writeback& obj) {
    //     obj.enable  = false;
    // })>                             dff_writeback;
    //

    BeforeStageDFFs::BeforeStageDFFs() noexcept
        : dff_branch_prediction ()
        , dff_from_decode       ()
        , dff_writeback         ()
        , next_bco_valid        (false)
    { }

    BeforeStageDFFs::~BeforeStageDFFs() noexcept
    { }

    inline void BeforeStageDFFs::NextBranchPrediction(BranchPrediction bp) noexcept
    {
        dff_branch_prediction.Next(bp);
    }

    inline void BeforeStageDFFs::NextFromDecode(FromDecode fd) noexcept
    {
        dff_from_decode.Next(fd);
    }

    inline void BeforeStageDFFs::NextWriteback(Writeback wb) noexcept
    {
        dff_writeback.Next(wb);
    }

    inline void BeforeStageDFFs::NextBranchCommitOverride(bool bco_valid)
    {
        next_bco_valid = bco_valid;
    }

    inline void BeforeStageDFFs::NextReset() noexcept
    {
        dff_branch_prediction.NextReset();
        dff_from_decode      .NextReset();
        dff_writeback        .NextReset();
    }

    inline BeforeStageDFFs::BranchPrediction BeforeStageDFFs::GetLastBranchPrediction() const noexcept
    {
        return dff_branch_prediction.Get();
    }

    inline BeforeStageDFFs::FromDecode BeforeStageDFFs::GetLastFromDecode() const noexcept
    {
        return dff_from_decode.Get();
    }

    inline BeforeStageDFFs::Writeback BeforeStageDFFs::GetLastWriteback() const noexcept
    {
        return dff_writeback.Get();
    }

    void BeforeStageDFFs::Reset() noexcept
    {
        dff_branch_prediction   .Reset();
        dff_from_decode         .Reset();
        dff_writeback           .Reset();
    }

    void BeforeStageDFFs::Eval() noexcept
    {
        //
        if (next_bco_valid)
            dff_from_decode.GetNext().valid = false;

        //
        dff_branch_prediction   .Eval();
        dff_from_decode         .Eval();
        dff_writeback           .Eval();
    }
}
