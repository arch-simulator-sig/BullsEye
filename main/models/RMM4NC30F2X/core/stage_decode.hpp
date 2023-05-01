#pragma once
//
// Decode Stage models for RMM4NC30F2X (Gemini 30F2)
//
//
//

#include <cstdint>

#include "common/nonstdint.hpp"

#include "models/common/dff.hpp"
#include "models/common/sram.hpp"
#include "models/common/axi.hpp"

#include "models/util/mips32helper.hpp"


#include "def_global.hpp"
#include "stage_global.hpp"

#include "stage_fetch.hpp"


namespace BullsEye::Gemini30F2::Decode {

    // Register File (32b x 32)
    class RegisterFile {
    public:
        using Index         = Global::ArchitecturalRegisterIndex;

        using Value         = Global::ArchitecturalRegisterValue;

    private:
        Value   regfile[31];

        bool    next_write_enable;
        Index   next_write_index;
        Value   next_write_value;

    public:
        RegisterFile() noexcept;
        ~RegisterFile() noexcept;

        void            NextWrite(Index index, Value value) noexcept;
        void            NextWrite(bool enable, Index index, Value value) noexcept;
        void            NextWrite() noexcept;

        Value           CombReadPortA(Index index) const noexcept;
        Value           CombReadPortB(Index index) const noexcept;

        void            Eval();
    };


    // Re-Order Buffer
    class ReOrderBuffer {
    public:
        using Index             = uint4_t;

        using LoadStoreWidth    = uint2_t;

        using CommitDelay       = uint4_t;

        struct Entry {
            bool                                ready;
            Global::PC                          pc;
            RegisterFile::Index                 dst;
            RegisterFile::Value                 value;
            Global::FID                         fid;

            bool                                load;
            bool                                store;
            bool                                lsmiss;
            LoadStoreWidth                      lswidth;
            CommitDelay                         cmtdelay;

            bool                                bco_valid;
            Fetch::BranchPredictor::PHTEntry    bco_pattern;
            bool                                bco_taken;
            Global::PC                          bco_target;
        };

        struct Allocation {
            bool                                enable;

            Global::PC                          pc;
            RegisterFile::Index                 dst;
            Global::FID                         fid;
            bool                                load;
            bool                                store;
            LoadStoreWidth                      lswidth;  
        };

        struct Writeback {
            bool                                enable;
            Index                               addr;
            
            Global::FID                         fid;
            RegisterFile::Value                 value;
            bool                                lsmiss;
            CommitDelay                         cmtdelay;

            bool                                bco_valid;
            Fetch::BranchPredictor::PHTEntry    bco_pattern;
            bool                                bco_taken;
            Global::PC                          bco_target;
        };

        struct ReadValueResult {
            bool                                ready;
            RegisterFile::Value                 value;
        };

        struct CommitCandidate {
            bool                                valid;
            Index                               rob;
            Entry                               entry;
        };

    public:
        static constexpr LoadStoreWidth     LSWIDTH_BYTE        = 0b00;
        static constexpr LoadStoreWidth     LSWIDTH_HALF_WORD   = 0b01;
        static constexpr LoadStoreWidth     LSWIDTH_WORD        = 0b10;
        static constexpr LoadStoreWidth     LSWIDTH_DOUBLE_WORD = 0b11;

    private:
        Entry                   rob[16];

        SteppingDFF<uint5_t>    wptr;
        SteppingDFF<uint5_t>    cptr;

        Allocation              next_allocation;
        Writeback               next_writeback;

        bool                    next_commit_enable;

        bool                    next_bco_valid;

        bool                    next_reset;

        CommitCandidate         last_commit;

    private:
        ReadValueResult _ReadValue(Index index) const noexcept;

        bool            _CommitPointerOverlap() const noexcept;
        bool            _CommitPointerToured() const noexcept;

        bool            _SignalEmpty() const noexcept;

        bool            _SignalCommitable() const noexcept;

    public:
        ReOrderBuffer() noexcept;
        ~ReOrderBuffer() noexcept;

        void            NextAllocation(Allocation allocation) noexcept;
        void            NextWriteback(Writeback writeback) noexcept;

        void            NextCommitEnable(bool enable) noexcept;

        void            NextBranchCommitOverride(bool valid) noexcept;

        void            NextReset() noexcept;

        ReadValueResult CombReadValuePortA(Index index) const noexcept;
        ReadValueResult CombReadValuePortB(Index index) const noexcept;

        CommitCandidate GetLastCommit() const noexcept;

        void            Reset() noexcept;
        void            Eval() noexcept;
    };


    // Register Alias Table
    class RegisterAliasTable {
    public:
        using Index     = Global::ArchitecturalRegisterIndex;

        struct ReadResult {
            bool                    valid;
            ReOrderBuffer::Index    rob;
        };

        struct Allocation {
            bool                    enable;
            Index                   addr;
            Global::FID             fid;
            ReOrderBuffer::Index    rob;
        };

        struct Writeback {
            bool                    enable;
            Index                   addr;
            Global::FID             fid;
        };

    private:
        struct Entry {
            bool                    valid;
            Global::FID             fid;
            ReOrderBuffer::Index    rob;
        };

        Entry       rat[31];

        Allocation  next_allocation;
        Writeback   next_writeback;

        bool        next_bco_valid;

        bool        next_reset;

    private:
        ReadResult      _Read(Index index) const noexcept;
    
    public:
        RegisterAliasTable() noexcept;
        ~RegisterAliasTable() noexcept;

        void            NextAllocation(Allocation allocation) noexcept;
        void            NextWriteback(Writeback writeback) noexcept;

        void            NextBranchCommitOverride(bool valid) noexcept;

        void            NextReset() noexcept;

        ReadResult      CombReadPortA(Index index) const noexcept;
        ReadResult      CombReadPortB(Index index) const noexcept;

        void            Reset() noexcept;
        void            Eval() noexcept;
    };



    // Pre-Allocator of ROB
    class PreAllocatorROB {
    private:
        SteppingDFF<uint5_t>    wptr;
        SteppingDFF<uint5_t>    cptr;

        SteppingDFF<bool>       alloc_sync;

        bool                    next_allocation_enable;
        bool                    next_commit_enable;

        bool                    next_bco_valid;

        bool                    next_reset;

    private:
        template<unsigned _Val>
        bool            _PointerIncrementOverlap() const noexcept;

        template<unsigned _Val>
        bool            _PointerIncrementToured() const noexcept;

        bool            _SignalNotReady() const noexcept;
        bool            _SignalEmpty() const noexcept;

    public:
        PreAllocatorROB() noexcept;
        ~PreAllocatorROB() noexcept;

        void            NextAllocationEnable(bool enable) noexcept;
        void            NextCommitEnable(bool enable) noexcept;

        void            NextBranchCommitOverride(bool valid) noexcept;

        void            NextReset() noexcept;

        bool            CombNotReady() const noexcept;

        void            Reset() noexcept;
        void            Eval() noexcept;
    };


    // Pre-Allocator of StoreBuffer
    class PreAllocatorStoreBuffer {
    private:
        SteppingDFF<uint7_t, DFFResetValue<uint7_t, 0b0000001>> fifo_pos;

        bool        next_allocation_enable;
        bool        next_allocation_enable_store;

        bool        next_commit_enable;
        bool        next_commit_enable_store;

        bool        next_bco_valid;

        bool        next_reset;

    private:
        bool        _SignalFunctionallyPop() const noexcept;
        bool        _SignalFunctionallyPush() const noexcept;

        bool        _SignalPositionHold() const noexcept;
        bool        _SignalPositionPop() const noexcept;
        bool        _SignalPositionPush() const noexcept;

        bool        _SignalFull() const noexcept;
        bool        _SignalEmpty() const noexcept;

        bool        _SignalNotReady() const noexcept;

    public:
        PreAllocatorStoreBuffer() noexcept;
        ~PreAllocatorStoreBuffer() noexcept;

        void        NextAllocationEnable(bool enable, bool enable_store) noexcept;
        void        NextCommitEnable(bool enable, bool enable_store) noexcept;

        void        NextBranchCommitOverride(bool valid) noexcept;

        void        NextReset() noexcept;

        bool        CombNotReady() const noexcept;

        void        Reset() noexcept;
        void        Eval() noexcept;
    };


    // Pre-Allocator
    class PreAllocator {

    };



    // InstructionDecoder
    class InstructionDecoder {

    };
}


// Implementation of: class RegisterFile
namespace BullsEye::Gemini30F2::Decode {
    //
    // Value   regfile[31];
    //
    // bool    next_write_enable;
    // Index   next_write_index;
    // Value   next_write_value;
    //

    RegisterFile::RegisterFile() noexcept
        : regfile           ()
        , next_write_enable (false)
        , next_write_index  ()
        , next_write_value  ()
    { }

    RegisterFile::~RegisterFile() noexcept
    { }

    inline void RegisterFile::NextWrite(Index index, Value value) noexcept
    {
        if (!index)
            return;

        next_write_enable   = true;
        next_write_index    = index;
        next_write_value    = value;
    }

    inline void RegisterFile::NextWrite(bool enable, Index index, Value value) noexcept
    {
        if (enable)
            NextWrite(index, value);
    }

    inline void RegisterFile::NextWrite() noexcept
    {
        next_write_enable = false;
    }

    inline RegisterFile::Value RegisterFile::CombReadPortA(Index index) const noexcept
    {
        if (!index)
            return 0;

        return regfile[index];
    }

    inline RegisterFile::Value RegisterFile::CombReadPortB(Index index) const noexcept
    {
        if (!index)
            return 0;

        return regfile[index];
    }

    void RegisterFile::Eval() noexcept
    {
        if (next_write_enable)
            regfile[next_write_index - 1] = next_write_value;
    }
}


// Implementation of: class ReOrderBuffer
namespace BullsEye::Gemini30F2::Decode {
    //
    // Entry                   rob[16];
    //
    // SteppingDFF<uint5_t>    wptr;
    // SteppingDFF<uint5_t>    cptr;
    //
    // Allocation              next_allocation;
    // Writeback               next_writeback;
    //
    // bool                    next_commit_enable;
    //
    // bool                    next_bco_valid;
    //
    // bool                    next_reset;
    //
    // CommitCandidate         last_commit;
    //

    ReOrderBuffer::ReOrderBuffer() noexcept
        : rob                   ()
        , wptr                  ()
        , cptr                  ()
        , next_allocation       { .enable = false }
        , next_writeback        { .enable = false }
        , next_commit_enable    (false)
        , next_bco_valid        (false)
        , next_reset            (false)
        , last_commit           ()
    { }

    ReOrderBuffer::~ReOrderBuffer() noexcept
    { }

    inline ReOrderBuffer::ReadValueResult ReOrderBuffer::_ReadValue(Index index) const noexcept
    {
        return ReadValueResult {
            .ready  = rob[index].ready && !rob[index].lsmiss,
            .value  = rob[index].value
        };
    }

    inline bool ReOrderBuffer::_CommitPointerOverlap() const noexcept
    {
        return (wptr.Get() & 0x0F) == (cptr.Get() & 0x0F);
    }

    inline bool ReOrderBuffer::_CommitPointerToured() const noexcept
    {
        return (wptr.Get() & 0x10) != (cptr.Get() & 0x10);
    }

    inline bool ReOrderBuffer::_SignalEmpty() const noexcept
    {
        return _CommitPointerOverlap() && !_CommitPointerToured();
    }

    inline bool ReOrderBuffer::_SignalCommitable() const noexcept
    {
        return !_SignalEmpty() && (rob[cptr.Get() & 0x0F].ready && !rob[cptr.Get() & 0x0F].cmtdelay);
    }

    inline void ReOrderBuffer::NextAllocation(Allocation allocation) noexcept
    {
        next_allocation = allocation;
    }

    inline void ReOrderBuffer::NextWriteback(Writeback writeback) noexcept
    {
        next_writeback = writeback;
    }

    inline void ReOrderBuffer::NextCommitEnable(bool enable) noexcept
    {
        next_commit_enable = enable;
    }

    inline void ReOrderBuffer::NextBranchCommitOverride(bool valid) noexcept
    {
        next_bco_valid = valid;
    }

    inline void ReOrderBuffer::NextReset() noexcept
    {
        next_reset = true;
    }

    inline ReOrderBuffer::ReadValueResult ReOrderBuffer::CombReadValuePortA(Index index) const noexcept
    {
        return _ReadValue(index);
    }

    inline ReOrderBuffer::ReadValueResult ReOrderBuffer::CombReadValuePortB(Index index) const noexcept
    {
        return _ReadValue(index);
    }

    inline ReOrderBuffer::CommitCandidate ReOrderBuffer::GetLastCommit() const noexcept
    {
        return last_commit;
    }

    void ReOrderBuffer::Reset() noexcept
    {
        for (auto& entry : rob)
            entry.ready = false;

        wptr.Reset();
        cptr.Reset();

        next_allocation .enable = false;
        next_writeback  .enable = false;

        next_commit_enable = false;

        next_bco_valid = false;

        next_reset = false;

        last_commit.valid = false;
    }

    void ReOrderBuffer::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        } 

        //
        Index wptr_to_index = Index(wptr.Get() & 0x0F);
        Index cptr_to_index = Index(cptr.Get() & 0x0F);

        bool  s_commitable = _SignalCommitable();

        // Dual Pointer of FIFO logic
        if (next_bco_valid)
        {
            wptr.Next(0);
            cptr.Next(0);
        }
        else 
        {
            if ((!last_commit.valid || next_commit_enable) && s_commitable)
                cptr.Next(cptr.Get() + 1);

            if (next_allocation.enable)
                wptr.Next(wptr.Get() + 1);
        }

        // Commit output logic
        if (next_bco_valid)
            last_commit.valid = false;
        else if (!last_commit.valid || next_commit_enable)
            last_commit.valid = s_commitable;

        if ((!last_commit.valid || next_commit_enable) && s_commitable)
        {
            last_commit.rob             = cptr_to_index;

            last_commit.entry.ready     = rob[cptr_to_index].ready;
            last_commit.entry.pc        = rob[cptr_to_index].pc;
            last_commit.entry.dst       = rob[cptr_to_index].dst;
            last_commit.entry.value     = rob[cptr_to_index].value;
            last_commit.entry.fid       = rob[cptr_to_index].fid;
            last_commit.entry.load      = rob[cptr_to_index].load;
            last_commit.entry.store     = rob[cptr_to_index].store;
            last_commit.entry.lsmiss    = rob[cptr_to_index].lsmiss;
            last_commit.entry.lswidth   = rob[cptr_to_index].lswidth;
            last_commit.entry.cmtdelay  = rob[cptr_to_index].cmtdelay;

            last_commit.entry.bco_valid     = rob[cptr_to_index].bco_valid;
            last_commit.entry.bco_pattern   = rob[cptr_to_index].bco_pattern;
            last_commit.entry.bco_taken     = rob[cptr_to_index].bco_taken;
            last_commit.entry.bco_target    = rob[cptr_to_index].bco_target;
        }

        // Writeback logic
        bool fid_hit = next_writeback.fid == rob[next_writeback.addr].fid;

        if (next_writeback.enable && fid_hit)
        {
            rob[next_writeback.addr].ready  = true;

            rob[next_writeback.addr].value  = next_writeback.value;
            rob[next_writeback.addr].lsmiss = next_writeback.lsmiss;

            rob[next_writeback.addr].bco_valid      = next_writeback.bco_valid;
            rob[next_writeback.addr].bco_pattern    = next_writeback.bco_pattern;
            rob[next_writeback.addr].bco_taken      = next_writeback.bco_taken;
            rob[next_writeback.addr].bco_target     = next_writeback.bco_target;
        }

        // Delayed-commit logic
        for (unsigned i = 0; i < 16; i++)
        {
            if (next_writeback.enable && fid_hit && next_writeback.addr == i)
                rob[i].cmtdelay = next_writeback.cmtdelay;
            else if (rob[i].cmtdelay)
                rob[i].cmtdelay--;
        }

        // Allocation logic
        if (next_allocation.enable)
            rob[wptr_to_index].ready = false;

        if (next_allocation.enable)
        {
            rob[wptr_to_index].pc       = next_allocation.pc;
            rob[wptr_to_index].dst      = next_allocation.dst;
            rob[wptr_to_index].fid      = next_allocation.fid;
            rob[wptr_to_index].load     = next_allocation.load;
            rob[wptr_to_index].store    = next_allocation.store;
            rob[wptr_to_index].lswidth  = next_allocation.lswidth;
        }

        //
        wptr.Eval();
        cptr.Eval();
    }
}


// Implementation of: class RegisterAliasTable
namespace BullsEye::Gemini30F2::Decode {
    //
    // Entry       rat[31];
    //
    // Allocation  next_allocation;
    // Writeback   next_writeback;
    //
    // bool        next_bco_valid;
    //
    // bool        next_reset;
    //

    RegisterAliasTable::RegisterAliasTable() noexcept
        : rat               ()
        , next_allocation   { .enable = false }
        , next_writeback    { .enable = false }
        , next_bco_valid    (false)
        , next_reset        (false)
    { }

    RegisterAliasTable::~RegisterAliasTable() noexcept
    { }

    inline RegisterAliasTable::ReadResult RegisterAliasTable::_Read(Index index) const noexcept
    {
        if (!index)
            return ReadResult { .valid = false };

        return ReadResult {
            .valid  = rat[index - 1].valid,
            .rob    = rat[index - 1].rob
        };
    }

    inline void RegisterAliasTable::NextAllocation(Allocation allocation) noexcept
    {
        next_allocation = allocation;
    }

    inline void RegisterAliasTable::NextWriteback(Writeback writeback) noexcept
    {
        next_writeback = writeback;
    }

    inline void RegisterAliasTable::NextBranchCommitOverride(bool bco_valid) noexcept
    {
        next_bco_valid = bco_valid;
    }

    inline void RegisterAliasTable::NextReset() noexcept
    {
        next_reset = true;
    }

    inline RegisterAliasTable::ReadResult RegisterAliasTable::CombReadPortA(Index index) const noexcept
    {
        return _Read(index);
    }

    inline RegisterAliasTable::ReadResult RegisterAliasTable::CombReadPortB(Index index) const noexcept
    {
        return _Read(index);
    }

    void RegisterAliasTable::Reset() noexcept
    {
        for (unsigned i = 0; i < 31; i++)
            rat[i].valid = false;

        next_allocation.enable  = false;
        next_writeback.enable   = false;

        next_bco_valid  = false;

        next_reset      = false;
    }

    void RegisterAliasTable::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }

        //
        if (next_bco_valid)
        {
            for (unsigned i = 0; i < 31; i++)
                rat[i].valid = false;
        }
        else
        {
            if (next_writeback.enable && next_writeback.addr && (rat[next_writeback.addr - 1].fid == next_writeback.fid))
                rat[next_writeback.addr - 1].valid = false;

            if (next_allocation.enable && next_allocation.addr)
            {
                rat[next_allocation.addr - 1].valid = true;
                rat[next_allocation.addr - 1].fid   = next_allocation.fid;
                rat[next_allocation.addr - 1].rob   = next_allocation.rob; 
            }
        }
    }
}


// Implementation of: class PreAllocatorROB
namespace BullsEye::Gemini30F2::Decode {
    //
    // SteppingDFF<uint5_t>    wptr;
    // SteppingDFF<uint5_t>    cptr;
    // 
    // SteppingDFF<bool>       alloc_sync;
    //
    // bool                    next_allocation_enable;
    // bool                    next_commit_enable;
    //
    // bool                    next_bco_valid;
    //
    // bool                    next_reset;
    //

    PreAllocatorROB::PreAllocatorROB() noexcept
        : wptr                      ()
        , cptr                      ()
        , alloc_sync                ()
        , next_allocation_enable    (false)
        , next_commit_enable        (false)
        , next_bco_valid            (false)
        , next_reset                (false)
    { }

    PreAllocatorROB::~PreAllocatorROB() noexcept
    { }

    template<unsigned _Val>
    inline bool PreAllocatorROB::_PointerIncrementOverlap() const noexcept
    {
        return ((wptr.Get() + _Val) & 0x0F) == (cptr.Get() & 0x0F);
    }

    template<unsigned _Val>
    inline bool PreAllocatorROB::_PointerIncrementToured() const noexcept
    {
        return ((wptr.Get() + _Val) & 0x10) != (cptr.Get() & 0x10);
    }

    inline bool PreAllocatorROB::_SignalNotReady() const noexcept
    {
        return (_PointerIncrementOverlap<0>() && _PointerIncrementToured<0>())
            || (_PointerIncrementOverlap<1>() && _PointerIncrementToured<1>())
            || (_PointerIncrementOverlap<2>() && _PointerIncrementToured<2>())
            || (_PointerIncrementOverlap<3>() && _PointerIncrementToured<3>())
            || (_PointerIncrementOverlap<4>() && _PointerIncrementToured<4>());
    }

    inline bool PreAllocatorROB::_SignalEmpty() const noexcept
    {
        return _PointerIncrementOverlap<0>() && !_PointerIncrementToured<0>();
    }

    inline void PreAllocatorROB::NextAllocationEnable(bool enable)
    {
        next_allocation_enable = enable;
    }

    inline void PreAllocatorROB::NextCommitEnable(bool enable)
    {
        next_commit_enable = enable;
    }

    inline void PreAllocatorROB::NextBranchCommitOverride(bool bco_valid)
    {
        next_bco_valid = bco_valid;
    }

    inline void PreAllocatorROB::NextReset()
    {
        next_reset = true;
    }

    inline bool PreAllocatorROB::CombNotReady() const noexcept
    {
        return _SignalNotReady();
    }

    void PreAllocatorROB::Reset() noexcept
    {
        wptr.Reset();
        cptr.Reset();

        alloc_sync.Reset();

        next_allocation_enable  = false;
        next_commit_enable      = false;

        next_bco_valid = false;

        next_reset = false;
    }

    void PreAllocatorROB::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }

        //
        alloc_sync.Next(next_allocation_enable);

        //
        if (next_bco_valid)
        {
            wptr.Next(0);
            cptr.Next(0);
        }
        else
        {
            if (next_commit_enable && !_SignalEmpty())
                cptr.Next(cptr.Get() + 1);

            if (alloc_sync.Get())
                wptr.Next(wptr.Get() + 1);
        }

        //
        wptr.Eval();
        cptr.Eval();

        alloc_sync.Eval();
    }
}


// Implementation of: class PreAllocatorStoreBuffer
namespace BullsEye::Gemini30F2::Decode {
    //
    // SteppingDFF<uint7_t, DFFResetValue<uint7_t, 0b0000001>> fifo_pos;
    //
    // bool        next_allocation_enable;
    // bool        next_allocation_enable_store;
    //
    // bool        next_commit_enable;
    // bool        next_commit_enable_store;
    //
    // bool        next_bco_valid;
    //
    // bool        next_reset;
    //

    PreAllocatorStoreBuffer::PreAllocatorStoreBuffer() noexcept
        : fifo_pos                      ()
        , next_allocation_enable        (false)
        , next_allocation_enable_store  (false)
        , next_commit_enable            (false)
        , next_commit_enable_store      (false)
        , next_bco_valid                (false)
        , next_reset                    (false)
    { }

    PreAllocatorStoreBuffer::~PreAllocatorStoreBuffer() noexcept
    { }

    inline bool PreAllocatorStoreBuffer::_SignalFunctionallyPop() const noexcept
    {
        return (next_commit_enable && next_commit_enable_store) && !_SignalEmpty();
    }

    inline bool PreAllocatorStoreBuffer::_SignalFunctionallyPush() const noexcept
    {
        return (next_allocation_enable && next_allocation_enable_store) && !_SignalFull();
    }

    inline bool PreAllocatorStoreBuffer::_SignalPositionHold() const noexcept
    {
        return _SignalFunctionallyPop() && (next_commit_enable && next_commit_enable_store);
    }

    inline bool PreAllocatorStoreBuffer::_SignalPositionPop() const noexcept
    {
        return !_SignalPositionHold() && _SignalFunctionallyPop();
    }

    inline bool PreAllocatorStoreBuffer::_SignalPositionPush() const noexcept
    {
        return !_SignalPositionHold() && _SignalFunctionallyPush();
    }

    inline bool PreAllocatorStoreBuffer::_SignalFull() const noexcept
    {
        return fifo_pos.Get() & 0x40;
    }

    inline bool PreAllocatorStoreBuffer::_SignalEmpty() const noexcept
    {
        return fifo_pos.Get() & 0x01;
    }

    inline void PreAllocatorStoreBuffer::NextAllocationEnable(bool enable, bool enable_store) noexcept
    {
        next_allocation_enable          = enable;
        next_allocation_enable_store    = enable_store;
    }

    inline void PreAllocatorStoreBuffer::NextCommitEnable(bool enable, bool enable_store) noexcept
    {
        next_commit_enable              = enable;
        next_commit_enable_store        = enable_store;
    }

    inline void PreAllocatorStoreBuffer::NextBranchCommitOverride(bool bco_valid) noexcept
    {
        next_bco_valid = bco_valid;
    }

    inline void PreAllocatorStoreBuffer::NextReset() noexcept
    {
        next_reset = true;
    }

    inline bool PreAllocatorStoreBuffer::CombNotReady() const noexcept
    {
        return fifo_pos.Get() & 0x7C;
    }

    void PreAllocatorStoreBuffer::Reset() noexcept
    {
        fifo_pos.Reset();

        next_allocation_enable          = false;
        next_allocation_enable_store    = false;

        next_commit_enable              = false;
        next_commit_enable_store        = false;

        next_bco_valid = false;

        next_reset = false;
    }

    void PreAllocatorStoreBuffer::Eval() noexcept
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
        fifo_pos.Eval();
    }
}
