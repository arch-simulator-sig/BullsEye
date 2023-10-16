#pragma once
//
// Commit Stage models for RMM4NC30F2X (Gemini 30F2)
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
#include "stage_issue.hpp"
#include "stage_dispatch.hpp"
#include "stage_execute.hpp"


namespace BullsEye::Gemini30F2::Commit {

    using PhysicalAddress                   = Global::PhysicalAddress;

    using Data                              = uint32_t;

    // AXI-4 Channel Definition
    using DataAXI4ReadAddressChannelM2S     = AXI4::ReadAddressChannelM2S<uint4_t, uint32_t, bool>;

    using DataAXI4ReadAddressChannelS2M     = AXI4::ReadAddressChannelS2M;

    using DataAXI4ReadDataChannelM2S        = AXI4::ReadDataChannelM2S;

    using DataAXI4ReadDataChannelS2M        = AXI4::ReadDataChannelS2M<uint4_t, uint32_t>;

    using DataAXI4WriteAddressChannelM2S    = AXI4::WriteAddressChannelM2S<uint4_t, uint32_t, bool>;

    using DataAXI4WriteAddressChannelS2M    = AXI4::WriteAddressChannelS2M;

    using DataAXI4WriteDataChannelM2S       = AXI4::WriteDataChannelM2S<uint32_t, std::bitset<4>>;

    using DataAXI4WriteDataChannelS2M       = AXI4::WriteDataChannelS2M;

    using DataAXI4WriteResponseChannelM2S   = AXI4::WriteResponseChannelM2S;

    using DataAXI4WriteResponseChannelS2M   = AXI4::WriteResponseChannelS2M<uint4_t>;
}


namespace BullsEye::Gemini30F2::Commit {

    // Memory Load Buffer
    class MemoryLoadBuffer {
    public:
        using PhysicalAddress           = PhysicalAddress;

        using Data                      = Data;

    public:
        struct UncachedWrite {
            bool                enable;
            PhysicalAddress     address;
            Data                data;
        };

        struct CachedWrite {
            bool                enable;
            PhysicalAddress     address;
            Data                data;
        };

        struct QueryResult {
            bool                hit;
            Data                data;
        };

    private:
        SteppingDFF<bool, DFFResetValue<false>>     uncached_valid;
        SteppingDFF<PhysicalAddress, DFFNoReset>    uncached_address;
        SteppingDFF<Data, DFFNoReset>               uncached_data;

        SteppingDFF<bool, DFFResetValue<false>>     fetched_valid   [8];
        SteppingDFF<PhysicalAddress, DFFNoReset>    fetched_address;
        SteppingDFF<Data, DFFNoReset>               fetched_data    [8];

        bool                next_cache_buffer_invalidation;

        bool                next_reset;

    private:
        size_t          _ToIndex(PhysicalAddress address) const noexcept;

        bool            _UncachedHit(PhysicalAddress address) const noexcept;
        bool            _FetchedHit(PhysicalAddress address) const noexcept;

    public:
        MemoryLoadBuffer() noexcept;
        ~MemoryLoadBuffer() noexcept;

        void            NextUncachedWrite(const UncachedWrite& bundle) noexcept;
        void            NextCachedWrite(const CachedWrite& bundle) noexcept;

        void            NextCacheBufferInvalidation(bool enable) noexcept;

        void            NextReset() noexcept;
        
        bool            CombQueryStateBusy(PhysicalAddress address) const noexcept;

        QueryResult     CombQuery(PhysicalAddress address) const noexcept;

        void            Reset() noexcept;
        void            Eval() noexcept;
    };


    // Memory Write AXI4-Controller
    class MemoryWriteAXI4Controller {
    public:
        using MemoryWritebackCandidate          = Execute::Execute::MemoryWritebackCandidate;

        using DataAXI4WriteAddressChannelS2M    = DataAXI4WriteAddressChannelS2M;
        using DataAXI4WriteDataChannelS2M       = DataAXI4WriteDataChannelS2M;
        using DataAXI4WriteResponseChannelS2M   = DataAXI4WriteResponseChannelS2M;

        using DataAXI4WriteAddressChannelM2S    = DataAXI4WriteAddressChannelM2S;
        using DataAXI4WriteDataChannelM2S       = DataAXI4WriteDataChannelM2S;
        using DataAXI4WriteResponseChannelM2S   = DataAXI4WriteResponseChannelM2S;

    private:
        SteppingDFF<bool, DFFResetValue<false>> dff_accepted_aw;
        SteppingDFF<bool, DFFResetValue<false>> dff_accepted_w;

        MemoryWritebackCandidate                next_memory_writeback_candidate;

        DataAXI4WriteAddressChannelS2M          next_write_address;
        DataAXI4WriteDataChannelS2M             next_write_data;
        DataAXI4WriteResponseChannelS2M         next_write_response;
        
        bool                                    next_reset;

    private:
        bool            _SignalAccepted() const noexcept;

    public:
        MemoryWriteAXI4Controller() noexcept;
        ~MemoryWriteAXI4Controller() noexcept;

        void            NextMemoryWritebackCandidate(const MemoryWritebackCandidate& bundle) noexcept;

        void            NextAXI4WriteAddress(const DataAXI4WriteAddressChannelS2M& bundle) noexcept;
        void            NextAXI4WriteData(const DataAXI4WriteDataChannelS2M& bundle) noexcept;
        void            NextAXI4WriteResponse(const DataAXI4WriteResponseChannelS2M& bundle) noexcept;

        void            NextReset() noexcept;

        bool            CombMemoryWritebackEnable() const noexcept;

        DataAXI4WriteAddressChannelM2S      CombAXI4WriteAddress() const noexcept;
        DataAXI4WriteDataChannelM2S         CombAXI4WriteData() const noexcept;
        DataAXI4WriteResponseChannelM2S     CombAXI4WriteResponse() const noexcept;

        void            Reset() noexcept;
        void            Eval() noexcept;
    };


    // Memory Read Data Update Buffer
    class MemoryReadDataUpdateBuffer {
    public:
        using PhysicalAddress               = PhysicalAddress;

        using Data                          = Data;

        using FIFOPosition                  = std::bitset<9>;

    public:
        struct Write {
            bool                enable;

            PhysicalAddress     address;
            Data                data;
        };

        struct Read {
            PhysicalAddress     address;
            Data                data;
        };

    private:
        struct Entry {
            uint3_t             offset;
            Data                data;
        };

    private:
        SteppingDFF<FIFOPosition, DFFResetValue<1>> fifo_pos;

        SteppingDFF<PhysicalAddress, DFFNoReset>    dff_address;

        Entry               buffer[8];

        Write               next_write;
        bool                next_read_enable;

        bool                next_reset;

    private:
        PhysicalAddress _ToAddress(PhysicalAddress address, uint3_t offset) const noexcept;
        uint3_t         _ToOffset(PhysicalAddress address) const noexcept;

        bool            _SignalFull() const noexcept;
        bool            _SignalEmpty() const noexcept;

        bool            _SignalFunctionallyPop() const noexcept;
        bool            _SignalFunctionallyPush() const noexcept;

        bool            _SignalPositionHold() const noexcept;
        bool            _SignalPositionPop() const noexcept;
        bool            _SignalPositionPush() const noexcept;

        bool            _SignalPositionShiftRight() const noexcept;

    public:
        MemoryReadDataUpdateBuffer() noexcept;
        ~MemoryReadDataUpdateBuffer() noexcept;

        void            NextWrite(const Write& bundle) noexcept;
        void            NextReadEnable(bool enable) noexcept;

        void            NextReset() noexcept;

        Read            GetLastRead() const noexcept;

        bool            GetLastFull() const noexcept;
        bool            GetLastEmpty() const noexcept;
        
        void            Reset() noexcept;
        void            Eval() noexcept;
    };


    // Memory Read AXI4-Controller
    class MemoryReadAXI4Controller {
    public:
        using DataAXI4ReadAddressChannelM2S     = DataAXI4ReadAddressChannelM2S;

        using DataAXI4ReadAddressChannelS2M     = DataAXI4ReadAddressChannelS2M;

        using DataAXI4ReadDataChannelM2S        = DataAXI4ReadDataChannelM2S;

        using DataAXI4ReadDataChannelS2M        = DataAXI4ReadDataChannelS2M;

        using PhysicalAddress                   = PhysicalAddress;

        using LoadStoreWidth                    = Decode::LoadStoreWidth;

        using Data                              = Data;

    public:
        struct ReadControl {
            bool                enable;

            Global::FID         fid;
            PhysicalAddress     address;
            bool                uncached;
            LoadStoreWidth      lswidth;
            Data                data;
        };

        struct ToLoadBuffer {
            bool                uncached_enable;
            PhysicalAddress     uncached_address;
            Data                uncached_data;

            bool                cached_enable;
            PhysicalAddress     cached_address;
            Data                cached_data;

            bool                cached_clear;
        };

        using CacheUpdateTag                    = Execute::L1DataCache::CacheUpdateTag;

        using CacheUpdateData                   = Execute::L1DataCache::CacheUpdateData;

    private:
        static constexpr uint8_t    MEMR_STATE_IDLE                     = 0b0000;

        static constexpr uint8_t    MEMR_STATE_LOAD_UNCACHED_AXI_ADDR   = 0b0100;
        static constexpr uint8_t    MEMR_STATE_LOAD_UNCACHED_AXI_DATA   = 0b0101;

        static constexpr uint8_t    MEMR_STATE_LOAD_REFILL_AXI_ADDR     = 0b1000;
        static constexpr uint8_t    MEMR_STATE_LOAD_REFILL_AXI_DATA     = 0b1001;
        static constexpr uint8_t    MEMR_STATE_LOAD_REFILL_FIFO_WAIT    = 0b1010;

        using State                             = uint4_t;

    private:
        MemoryReadDataUpdateBuffer      module_update_buffer;

        SteppingDFF<State, DFFResetValue<MEMR_STATE_IDLE>>  dff_state;

        SteppingDFF<bool, DFFResetZero>                     dff_curfid_valid;
        SteppingDFF<Global::FID, DFFResetZero>              dff_curfid;

        SteppingDFF<PhysicalAddress, DFFResetZero>          dff_curaddr;
        SteppingDFF<uint3_t, DFFResetZero>                  dff_raddr;

        SteppingDFF<PhysicalAddress, DFFResetZero>          dff_araddr;
        SteppingDFF<uint8_t, DFFResetZero>                  dff_arlen;
        SteppingDFF<uint3_t, DFFResetZero>                  dff_arsize;
        SteppingDFF<uint2_t, DFFResetZero>                  dff_arburst;
        SteppingDFF<bool, DFFResetZero>                     dff_aruser;
        SteppingDFF<bool, DFFResetZero>                     dff_arvalid;

        bool                            comb_uncached_read;
        bool                            comb_cached_read;
        bool                            comb_cached_done;

        ReadControl                     next_read_control;

        bool                            next_cache_update_data_ready;

        DataAXI4ReadAddressChannelS2M   next_axi_read_address;
        DataAXI4ReadDataChannelS2M      next_axi_read_data;

        bool                            next_reset;

    private:
        PhysicalAddress     _FullCurrentAddress() const noexcept;

    public:
        MemoryReadAXI4Controller() noexcept;
        ~MemoryReadAXI4Controller() noexcept;

        void                NextReadControl(const ReadControl& bundle) noexcept;

        void                NextCacheUpdateDataReady(bool ready) noexcept;

        void                NextAXIReadAddress(const DataAXI4ReadAddressChannelS2M& bundle) noexcept;
        void                NextAXIReadData(const DataAXI4ReadDataChannelS2M& bundle) noexcept;

        void                NextReset() noexcept;

        void                Comb() noexcept;

        ToLoadBuffer        GetCombToLoadBuffer() const noexcept;

        CacheUpdateTag      GetCombCacheUpdateTag() const noexcept;
        CacheUpdateData     GetCombCacheUpdateData() const noexcept;

        bool                GetLastBusy() const noexcept;

        DataAXI4ReadAddressChannelM2S   GetLastAXIReadAddress() const noexcept;
        DataAXI4ReadDataChannelM2S      GetLastAXIReadData() const noexcept;

        void                Reset() noexcept;
        void                Eval() noexcept;
    };


    // Commit Logic
    class CommitLogic {
    public:
        using RegisterIndex                 = Global::ArchitecturalRegisterIndex;

        using RegisterValue                 = Global::ArchitecturalRegisterValue;

        using PatternHistory                = Fetch::BranchPredictor::PHTEntry;

        using ROBIndex                      = Decode::ReOrderBuffer::Index;

        using FromROB                       = Decode::ReOrderBuffer::CommitCandidate;

        using MemoryWritebackCandidate      = Execute::Execute::MemoryWritebackCandidate;

    public:
        struct FromCommit {
            bool                enable;
            bool                store;
            Global::FID         fid;
            RegisterIndex       dst;
            RegisterValue       result;

            bool                bco_valid;
            Global::PC          bco_pc;
            PatternHistory      bco_pattern;
            bool                bco_taken;
            Global::PC          bco_target;
        };

        struct NoWriteback {
            bool                enable;
            ROBIndex            dst_rob;
            RegisterValue       value;
        };

        using ReadControl                   = MemoryReadAXI4Controller::ReadControl;

    private:
        bool        next_busy_uncached_store;

        FromROB     next_from_rob;

        bool        next_memory_commit_not_ready;

        FromCommit  comb_from_commit;

        NoWriteback comb_no_writeback;

        ReadControl comb_read_control;

        bool        comb_store_commit_enable;

    public:

    };

}


// Implementation of: class MemoryLoadBuffer
namespace BullsEye::Gemini30F2::Commit {
    //
    // SteppingDFF<bool, DFFResetValue<false>>     uncached_valid;
    // SteppingDFF<PhysicalAddress, DFFNoReset>    uncached_address;
    // SteppingDFF<Data, DFFNoReset>               uncached_data;
    //
    // SteppingDFF<bool, DFFResetValue<false>>     fetched_valid   [8];
    // SteppingDFF<PhysicalAddress, DFFNoReset>    fetched_address;
    // SteppingDFF<Data, DFFNoReset>               fetched_data    [8];
    //
    // bool                next_cache_buffer_invalidation;
    //
    // bool                next_reset;
    //

    MemoryLoadBuffer::MemoryLoadBuffer() noexcept
        : uncached_valid                    ()
        , uncached_address                  ()
        , uncached_data                     ()
        , fetched_valid                     ()
        , fetched_address                   ()
        , fetched_data                      ()
        , next_cache_buffer_invalidation    ()
        , next_reset                        (false)
    { }

    MemoryLoadBuffer::~MemoryLoadBuffer() noexcept
    { }

    inline size_t MemoryLoadBuffer::_ToIndex(PhysicalAddress address) const noexcept
    {
        return (address >> 2) & 0x07;
    }

    inline bool MemoryLoadBuffer::_UncachedHit(PhysicalAddress address) const noexcept
    {
        return uncached_valid.Get() && (uncached_address.Get() == address);   
    }

    inline bool MemoryLoadBuffer::_FetchedHit(PhysicalAddress address) const noexcept
    {
        return fetched_valid[_ToIndex(address)].Get() && ((fetched_address.Get() >> 5) == (address >> 5));
    }

    inline void MemoryLoadBuffer::NextUncachedWrite(const UncachedWrite& bundle) noexcept
    {
        uncached_valid  .Next(bundle.enable);
        uncached_address.Next(bundle.address);
        uncached_data   .Next(bundle.data);
    }

    inline void MemoryLoadBuffer::NextCachedWrite(const CachedWrite& bundle) noexcept
    {
        size_t index = _ToIndex(bundle.address);

        if (bundle.enable)
        {
            fetched_valid   [index] .Next(true);
            fetched_address         .Next(bundle.address);
            fetched_data    [index] .Next(bundle.data);
        }
    }

    inline void MemoryLoadBuffer::NextCacheBufferInvalidation(bool enable) noexcept
    {
        next_cache_buffer_invalidation = enable;
    }

    inline void MemoryLoadBuffer::NextReset() noexcept
    {
        next_reset = true;
    }

    bool MemoryLoadBuffer::CombQueryStateBusy(PhysicalAddress address) const noexcept
    {
        for (int i = 0; i < 8; i++)
            if (fetched_valid[i].Get())
                return true;

        return false;
    }

    inline MemoryLoadBuffer::QueryResult MemoryLoadBuffer::CombQuery(PhysicalAddress address) const noexcept
    {
        bool uncached_hit   = _UncachedHit(address);
        bool fetched_hit    = _FetchedHit(address);

        return QueryResult {
            .hit    = uncached_hit || fetched_hit,
            .data   = uncached_hit ? uncached_data.Get() : fetched_data[_ToIndex(address)].Get()
        };
    }

    void MemoryLoadBuffer::Reset() noexcept
    {
        uncached_valid  .Reset();
        uncached_data   .Reset();
        uncached_address.Reset();

        for (int i = 0; i < 8; i++)
        {
            fetched_valid[i].Reset();
            fetched_data [i].Reset();
        }
        fetched_address     .Reset();

        next_reset = false;
    }

    void MemoryLoadBuffer::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }

        //
        if (next_cache_buffer_invalidation)
        {
            for (int i = 0; i < 8; i++)
                fetched_valid[i].Next(false);
        }

        //
        uncached_valid  .Eval();
        uncached_data   .Eval();
        uncached_address.Eval();

        for (int i = 0; i < 8; i++)
        {
            fetched_valid[i].Eval();
            fetched_data [i].Eval();
        }
        fetched_address.Eval();
    }
}


// Implementation of: class MemoryWriteAXI4Controller
namespace BullsEye::Gemini30F2::Commit {
    //
    // SteppingDFF<bool, DFFResetValue<false>> dff_accepted_aw;
    // SteppingDFF<bool, DFFResetValue<false>> dff_accepted_w;
    //
    // MemoryWritebackCandidate                next_memory_writeback_candidate;
    //
    // DataAXI4WriteAddressChannelS2M          next_write_address;
    // DataAXI4WriteDataChannelS2M             next_write_data;
    // DataAXI4WriteResponseChannelS2M         next_write_response;
    //
    // bool                                    next_reset;
    //

    MemoryWriteAXI4Controller::MemoryWriteAXI4Controller() noexcept
        : dff_accepted_aw                   ()
        , dff_accepted_w                    ()
        , next_memory_writeback_candidate   ()
        , next_write_address                ()
        , next_write_data                   ()
        , next_write_response               ()
        , next_reset                        (false)
    { }

    MemoryWriteAXI4Controller::~MemoryWriteAXI4Controller() noexcept
    { }

    inline bool MemoryWriteAXI4Controller::_SignalAccepted() const noexcept
    {
        return (next_write_address.awready  && next_write_data.wready)
            || (next_write_address.awready  && dff_accepted_w.Get()  )
            || (dff_accepted_aw.Get()       && next_write_data.wready);
    }

    inline void MemoryWriteAXI4Controller::NextMemoryWritebackCandidate(const MemoryWritebackCandidate& bundle) noexcept
    {
        next_memory_writeback_candidate = bundle;
    }

    inline void MemoryWriteAXI4Controller::NextAXI4WriteAddress(const DataAXI4WriteAddressChannelS2M& bundle) noexcept
    {
        next_write_address = bundle;
    }

    inline void MemoryWriteAXI4Controller::NextAXI4WriteData(const DataAXI4WriteDataChannelS2M& bundle) noexcept
    {
        next_write_data = bundle;
    }

    inline void MemoryWriteAXI4Controller::NextAXI4WriteResponse(const DataAXI4WriteResponseChannelS2M& bundle) noexcept
    {
        next_write_response = bundle;
    }

    inline void MemoryWriteAXI4Controller::NextReset() noexcept
    {
        next_reset = true;
    }

    inline bool MemoryWriteAXI4Controller::CombMemoryWritebackEnable() const noexcept
    {
        return _SignalAccepted();
    }

    inline DataAXI4WriteAddressChannelM2S MemoryWriteAXI4Controller::CombAXI4WriteAddress() const noexcept
    {
        return DataAXI4WriteAddressChannelM2S {
            .awid       = 0,
            .awaddr     = next_memory_writeback_candidate.address,
            .awlen      = AXI4::Attributes::AXLEN<1>,
            .awsize     = next_memory_writeback_candidate.lswidth == Decode::LSWIDTH_BYTE ? AXI4::Attributes::AXSIZE<1> : AXI4::Attributes::AXSIZE<4>,
            .awburst    = AXI4::Attributes::AXBURST_INCR,
            .awuser     = next_memory_writeback_candidate.uncached,
            .awvalid    = next_memory_writeback_candidate.valid && !dff_accepted_aw.Get()
        };
    }

    inline DataAXI4WriteDataChannelM2S MemoryWriteAXI4Controller::CombAXI4WriteData() const noexcept
    {
        return DataAXI4WriteDataChannelM2S {
            .wdata      = next_memory_writeback_candidate.data,
            .wstrb      = next_memory_writeback_candidate.strobe,
            .wlast      = true,
            .wvalid     = next_memory_writeback_candidate.valid && !dff_accepted_w.Get()
        };
    }

    inline DataAXI4WriteResponseChannelM2S MemoryWriteAXI4Controller::CombAXI4WriteResponse() const noexcept
    {
        return DataAXI4WriteResponseChannelM2S {
            .bready     = true,
        };
    }

    void MemoryWriteAXI4Controller::Reset() noexcept
    {
        dff_accepted_aw .Reset();
        dff_accepted_w  .Reset();

        next_reset = false;
    }

    void MemoryWriteAXI4Controller::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }

        //
        if (dff_accepted_aw.Get())
        {
            if (next_write_data.wready)
                dff_accepted_aw.Next(false);
        }
        else if (next_memory_writeback_candidate.valid && next_write_address.awready)
        {
            if (dff_accepted_w.Get())
                dff_accepted_aw.Next(false);
            else if (next_write_data.wready)
                dff_accepted_aw.Next(false);
            else
                dff_accepted_aw.Next(true);
        }

        //
        if (dff_accepted_w.Get())
        {
            if (next_write_address.awready)
                dff_accepted_w.Next(false);
        }
        else if (next_memory_writeback_candidate.valid && next_write_data.wready)
        {
            if (dff_accepted_aw.Get())
                dff_accepted_aw.Next(false);
            else if (next_write_address.awready)
                dff_accepted_aw.Next(false);
            else
                dff_accepted_aw.Next(true);
        }

        //
        dff_accepted_aw .Eval();
        dff_accepted_w  .Eval();
    }
}


// Implementation of: class MemoryReadDataUpdateBuffer
namespace BullsEye::Gemini30F2::Commit {
    //
    // SteppingDFF<FIFOPosition, DFFResetValue<1>> fifo_pos;
    //
    // SteppingDFF<PhysicalAddress, DFFNoReset>    dff_address;
    //
    // Write               next_write;
    // bool                next_read_enable;
    //
    // bool                next_reset;
    //

    MemoryReadDataUpdateBuffer::MemoryReadDataUpdateBuffer() noexcept
        : fifo_pos          ()
        , dff_address       ()
        , buffer            ()
        , next_write        ()
        , next_read_enable  (false)
        , next_reset        (false)
    { }

    MemoryReadDataUpdateBuffer::~MemoryReadDataUpdateBuffer() noexcept
    { }

    inline PhysicalAddress MemoryReadDataUpdateBuffer::_ToAddress(PhysicalAddress address, uint3_t offset) const noexcept
    {
        return (address & 0xFFFFFFE0) | ((uint32_t) offset << 2);
    }

    inline uint3_t MemoryReadDataUpdateBuffer::_ToOffset(PhysicalAddress address) const noexcept
    {
        return (address >> 2) & 0x1C;
    }

    inline bool MemoryReadDataUpdateBuffer::_SignalFull() const noexcept
    {
        return fifo_pos.Get()[8];
    }

    inline bool MemoryReadDataUpdateBuffer::_SignalEmpty() const noexcept
    {
        return fifo_pos.Get()[0];
    }

    inline bool MemoryReadDataUpdateBuffer::_SignalFunctionallyPop() const noexcept
    {
        return next_read_enable && !_SignalEmpty();
    }

    inline bool MemoryReadDataUpdateBuffer::_SignalFunctionallyPush() const noexcept
    {
        return next_write.enable && !_SignalFull();
    }

    inline bool MemoryReadDataUpdateBuffer::_SignalPositionHold() const noexcept
    {
        return _SignalFunctionallyPop() && next_write.enable;
    }

    inline bool MemoryReadDataUpdateBuffer::_SignalPositionPop() const noexcept
    {
        return !_SignalPositionHold() && _SignalFunctionallyPop();
    }

    inline bool MemoryReadDataUpdateBuffer::_SignalPositionPush() const noexcept
    {
        return !_SignalPositionHold() && _SignalFunctionallyPush();
    }

    inline bool MemoryReadDataUpdateBuffer::_SignalPositionShiftRight() const noexcept
    {
        return _SignalFunctionallyPop();
    }

    inline void MemoryReadDataUpdateBuffer::NextWrite(const Write& bundle) noexcept
    {
        if (bundle.enable)
            dff_address.Next(bundle.address);

        next_write = bundle;
    }

    inline void MemoryReadDataUpdateBuffer::NextReadEnable(bool enable) noexcept
    {
        next_read_enable = enable;
    }

    inline void MemoryReadDataUpdateBuffer::NextReset() noexcept
    {
        next_reset = true;
    }

    inline MemoryReadDataUpdateBuffer::Read MemoryReadDataUpdateBuffer::GetLastRead() const noexcept
    {
        return Read {
            .address    = _ToAddress(dff_address.Get(), buffer[0].offset),
            .data       = buffer[0].data
        };
    }

    inline bool MemoryReadDataUpdateBuffer::GetLastFull() const noexcept
    {
        return _SignalFull();
    }

    inline bool MemoryReadDataUpdateBuffer::GetLastEmpty() const noexcept
    {
        return _SignalEmpty();
    }

    void MemoryReadDataUpdateBuffer::Reset() noexcept
    {
        fifo_pos.Reset();

        next_reset = false;
    }

    void MemoryReadDataUpdateBuffer::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }

        //
        if (_SignalPositionPop())
            fifo_pos.Next(fifo_pos.Get() >> 1);
        else if (_SignalPositionPush())
            fifo_pos.Next(fifo_pos.Get() << 1);

        //
        for (int i = 0; i < 8; i++)
        {
            if (_SignalPositionShiftRight())
            {
                if (next_write.enable && fifo_pos.Get()[i + 1])
                {
                    buffer[i].offset    = _ToOffset(next_write.address);
                    buffer[i].data      = next_write.data;
                }
                else if (i < 7)
                    buffer[i] = buffer[i + 1];
            }
            else if (next_write.enable && fifo_pos.Get()[i])
            {
                buffer[i].offset    = _ToOffset(next_write.address);
                buffer[i].data      = next_write.data;
            }
        }

        //
        fifo_pos.Eval();
        dff_address.Eval();
    }
}


// Implementation of: class MemoryReadAXI4Controller
namespace BullsEye::Gemini30F2::Commit {
    //
    // MemoryReadDataUpdateBuffer      module_update_buffer;
    //
    // SteppingDFF<State, DFFResetValue<MEMR_STATE_IDLE>>  dff_state;
    //
    // SteppingDFF<bool, DFFResetZero>                     dff_curfid_valid;
    // SteppingDFF<Global::FID, DFFResetZero>              dff_curfid;
    //
    // SteppingDFF<PhysicalAddress, DFFResetZero>          dff_curaddr;
    // SteppingDFF<uint3_t, DFFResetZero>                  dff_raddr;
    //
    // SteppingDFF<PhysicalAddress, DFFResetZero>          dff_araddr;
    // SteppingDFF<uint8_t, DFFResetZero>                  dff_arlen;
    // SteppingDFF<uint3_t, DFFResetZero>                  dff_arsize;
    // SteppingDFF<uint2_t, DFFResetZero>                  dff_arburst;
    // SteppingDFF<bool, DFFResetZero>                     dff_aruser;
    // SteppingDFF<bool, DFFResetZero>                     dff_arvalid;
    //
    // bool                            comb_uncached_read;
    // bool                            comb_cached_read;
    // bool                            comb_cached_done;
    // 
    // ReadControl                     next_read_control;
    //
    // bool                            next_cache_update_data_ready;
    //
    // DataAXI4ReadAddressChannelS2M   next_axi_read_address;
    // DataAXI4ReadDataChannelS2M      next_axi_read_data;
    //
    // bool                            next_reset;
    //

    MemoryReadAXI4Controller::MemoryReadAXI4Controller() noexcept
        : module_update_buffer          ()
        , dff_state                     ()
        , dff_curfid_valid              ()
        , dff_curfid                    ()
        , dff_curaddr                   ()
        , dff_raddr                     ()
        , dff_araddr                    ()
        , dff_arlen                     ()
        , dff_arsize                    ()
        , dff_arburst                   ()
        , dff_aruser                    ()
        , dff_arvalid                   ()
        , comb_uncached_read            ()
        , comb_cached_read              ()
        , comb_cached_done              ()
        , next_read_control             ()
        , next_cache_update_data_ready  ()
        , next_axi_read_address         ()
        , next_axi_read_data            ()
        , next_reset                    (false)
    { }

    MemoryReadAXI4Controller::~MemoryReadAXI4Controller() noexcept
    { }

    inline MemoryReadAXI4Controller::PhysicalAddress MemoryReadAXI4Controller::_FullCurrentAddress() const noexcept
    {
        return (dff_curaddr.Get() & 0xFFFFFFE0) | ((uint32_t) dff_raddr.Get() << 2);
    }

    inline void MemoryReadAXI4Controller::NextReadControl(const ReadControl& bundle) noexcept
    {
        next_read_control = bundle;
    }

    inline void MemoryReadAXI4Controller::NextCacheUpdateDataReady(bool ready) noexcept
    {
        next_cache_update_data_ready = ready;
    }

    inline void MemoryReadAXI4Controller::NextAXIReadAddress(const DataAXI4ReadAddressChannelS2M& bundle) noexcept
    {
        next_axi_read_address = bundle;
    }

    inline void MemoryReadAXI4Controller::NextAXIReadData(const DataAXI4ReadDataChannelS2M& bundle) noexcept
    {
        next_axi_read_data = bundle;
    }

    inline void MemoryReadAXI4Controller::NextReset() noexcept
    {
        next_reset = true;
    }

    inline bool MemoryReadAXI4Controller::GetLastBusy() const noexcept
    {
        return !module_update_buffer.GetLastEmpty();
    }

    void MemoryReadAXI4Controller::Comb() noexcept
    {
        //
        comb_uncached_read = false;
        comb_cached_read   = false;
        comb_cached_done   = false;

        switch (dff_state.Get())
        {
            //
            case MEMR_STATE_IDLE:

                if (next_read_control.enable)
                {
                    dff_curaddr .Next(next_read_control.address);
                    dff_raddr   .Next(next_read_control.address >> 2);

                    dff_curfid_valid.Next(false);

                    if (dff_curfid_valid.Get() && (dff_curfid.Get() == next_read_control.fid))
                        dff_state.Next(MEMR_STATE_IDLE);
                    else
                    {
                        dff_curfid      .Next(next_read_control.fid);
                        dff_curfid_valid.Next(true);

                        if (next_read_control.uncached)
                            dff_state.Next(MEMR_STATE_LOAD_UNCACHED_AXI_ADDR);
                        else
                            dff_state.Next(MEMR_STATE_LOAD_REFILL_AXI_ADDR);
                    }
                }

                break;

            //
            case MEMR_STATE_LOAD_UNCACHED_AXI_ADDR:

                if (next_axi_read_address.arready)
                    dff_state.Next(MEMR_STATE_LOAD_UNCACHED_AXI_DATA);

                break;

            //
            case MEMR_STATE_LOAD_UNCACHED_AXI_DATA:

                if (next_axi_read_data.rvalid)
                {
                    comb_uncached_read = true;

                    dff_state.Next(MEMR_STATE_IDLE);
                }

                break;

            //
            case MEMR_STATE_LOAD_REFILL_AXI_ADDR:

                if (next_axi_read_address.arready)
                    dff_state.Next(MEMR_STATE_LOAD_REFILL_AXI_DATA);

                break;

            //
            case MEMR_STATE_LOAD_REFILL_AXI_DATA:

                if (next_axi_read_data.rvalid)
                {
                    comb_cached_read = true;

                    if (next_axi_read_data.rlast)
                        dff_state.Next(MEMR_STATE_LOAD_REFILL_FIFO_WAIT);
                    else
                    {
                        dff_raddr.Next(dff_raddr.Get() + 1);

                        dff_state.Next(MEMR_STATE_LOAD_REFILL_AXI_DATA);
                    }
                }

                break;

            //
            case MEMR_STATE_LOAD_REFILL_FIFO_WAIT:

                if (module_update_buffer.GetLastEmpty())
                {
                    comb_cached_done = true;

                    dff_state.Next(MEMR_STATE_IDLE);
                }

                break;

            //
            default:
                break;
        }


        //
        switch (dff_state.Get())
        {
            //
            case MEMR_STATE_IDLE:

                if (dff_state.GetNext() == MEMR_STATE_LOAD_UNCACHED_AXI_ADDR)
                {
                    dff_araddr  .Next(next_read_control.address);
                    dff_arlen   .Next(AXI4::Attributes::AXLEN<1>);
                    dff_arburst .Next(AXI4::Attributes::AXBURST_FIXED);
                    dff_aruser  .Next(true);
                    dff_arvalid .Next(true);

                    switch (next_read_control.lswidth)
                    {
                        case Decode::LSWIDTH_BYTE:
                            dff_arsize.Next(AXI4::Attributes::AXSIZE<1>);
                            break;

                        default:
                            dff_arsize.Next(AXI4::Attributes::AXSIZE<4>);
                            break;
                    }
                }
                else if (dff_state.GetNext() == MEMR_STATE_LOAD_REFILL_AXI_ADDR)
                {
                    dff_araddr  .Next(next_read_control.address);
                    dff_arlen   .Next(AXI4::Attributes::AXLEN<8>);
                    dff_arsize  .Next(AXI4::Attributes::AXSIZE<4>);
                    dff_arburst .Next(AXI4::Attributes::AXBURST_WRAP);
                    dff_aruser  .Next(false);
                    dff_arvalid .Next(true);
                }

                break;

            //
            case MEMR_STATE_LOAD_UNCACHED_AXI_ADDR:

                if (dff_state.GetNext() == MEMR_STATE_LOAD_UNCACHED_AXI_DATA)
                    dff_arvalid.Next(false);

                break;

            //
            case MEMR_STATE_LOAD_UNCACHED_AXI_DATA:
                break;

            //
            case MEMR_STATE_LOAD_REFILL_AXI_ADDR:

                if (dff_state.GetNext() == MEMR_STATE_LOAD_REFILL_AXI_DATA)
                    dff_arvalid.Next(false);

                break;

            //
            case MEMR_STATE_LOAD_REFILL_AXI_DATA:
                break;

            //
            case MEMR_STATE_LOAD_REFILL_FIFO_WAIT:
                break;

            //
            default:
                break;
        }


        //
        module_update_buffer.NextWrite({
            .enable     = comb_cached_read,
            .address    = _FullCurrentAddress(),
            .data       = next_axi_read_data.rdata
        });

        module_update_buffer.NextReadEnable(next_cache_update_data_ready);
    }

    inline MemoryReadAXI4Controller::ToLoadBuffer MemoryReadAXI4Controller::GetCombToLoadBuffer() const noexcept
    {
        return ToLoadBuffer {
            .uncached_enable    = comb_uncached_read,
            .uncached_address   = dff_curaddr.Get(),
            .uncached_data      = next_axi_read_data.rdata,

            .cached_enable      = comb_cached_read,
            .cached_address     = _FullCurrentAddress(),
            .cached_data        = next_axi_read_data.rdata,

            .cached_clear       = comb_cached_done
        };
    }

    inline MemoryReadAXI4Controller::CacheUpdateTag MemoryReadAXI4Controller::GetCombCacheUpdateTag() const noexcept
    {
        return CacheUpdateTag {
            .enable     = comb_cached_read || comb_cached_done,
            .address    = dff_curaddr.Get(),
            .valid      = comb_cached_done
        };
    }

    inline MemoryReadAXI4Controller::CacheUpdateData MemoryReadAXI4Controller::GetCombCacheUpdateData() const noexcept
    {
        MemoryReadDataUpdateBuffer::Read dupd = module_update_buffer.GetLastRead();

        return CacheUpdateData {
            .valid      = !module_update_buffer.GetLastEmpty(),
            .address    = dupd.address,
            .strobe     = 0b1111,
            .data       = dupd.data
        };
    }

    inline MemoryReadAXI4Controller::DataAXI4ReadAddressChannelM2S MemoryReadAXI4Controller::GetLastAXIReadAddress() const noexcept
    {
        return DataAXI4ReadAddressChannelM2S {
            .arid       = 0,
            .araddr     = dff_araddr.Get(),
            .arlen      = dff_arlen.Get(),
            .arsize     = dff_arsize.Get(),
            .arburst    = dff_arburst.Get(),
            .aruser     = dff_aruser.Get(),
            .arvalid    = dff_arvalid.Get()
        };
    }

    inline MemoryReadAXI4Controller::DataAXI4ReadDataChannelM2S MemoryReadAXI4Controller::GetLastAXIReadData() const noexcept
    {
        return DataAXI4ReadDataChannelM2S {
            .rready     = true
        };
    }

    void MemoryReadAXI4Controller::Reset() noexcept
    {
        module_update_buffer.Reset();

        dff_state       .Reset();

        dff_curfid      .Reset();
        dff_curfid_valid.Reset();

        dff_curaddr     .Reset();
        dff_raddr       .Reset();

        dff_araddr      .Reset();
        dff_arlen       .Reset();
        dff_arsize      .Reset();
        dff_arburst     .Reset();
        dff_aruser      .Reset();
        dff_arvalid     .Reset();

        next_reset  = false;
    }

    void MemoryReadAXI4Controller::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }

        //
        module_update_buffer.Eval();

        dff_state.Eval();

        dff_curfid_valid.Eval();
        dff_curfid      .Eval();

        dff_curaddr .Eval();
        dff_raddr   .Eval();

        dff_araddr  .Eval();
        dff_arlen   .Eval();
        dff_arsize  .Eval();
        dff_arburst .Eval();
        dff_aruser  .Eval();
        dff_arvalid .Eval();
    }
}
