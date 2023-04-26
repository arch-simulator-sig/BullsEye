#pragma once
//
// Fetch Stage models for RMM4NC30F2X (Gemini 30F2)
//
//
//

#include <cstdint>
#include <tuple>

#include "common/nonstdint.hpp"

#include "models/common/dff.hpp"
#include "models/common/sram.hpp"
#include "models/common/axi.hpp"

#include "models/util/mips32helper.hpp"


#include "def_global.hpp"


namespace BullsEye::Gemini30F2::Fetch {

    // AXI-4 Channel Definition
    using FetchAXI4ReadAddressChannelM2S    = AXI4::ReadAddressChannelM2S<uint4_t, uint32_t, bool>;

    using FetchAXI4ReadAddressChannelS2M    = AXI4::ReadAddressChannelS2M;

    using FetchAXI4ReadDataChannelM2S       = AXI4::ReadDataChannelM2S;

    using FetchAXI4ReadDataChannelS2M       = AXI4::ReadDataChannelS2M<uint4_t, uint32_t>;


    // GHR (Global History Register)
    using GHRValue  = uint4_t;
    using GHR       = SteppingDFF<GHRValue>;


    // Uncached Fetch Buffer (Instruction Fetch Buffer)
    class UncachedBuffer {
    public:
        using Address   = uint30_t;

        using Data      = uint36_t;

    private:
        SteppingDFF<bool>       buffer_valid;

        SteppingDFF<Address>    buffer_addr;

        SteppingDFF<Data>       buffer_data;

    public:
        struct CombQueryResult {
            bool    hit;
            Data    data;
        };

    public:
        UncachedBuffer() noexcept;
        ~UncachedBuffer() noexcept;

        void                Next(uint32_t address, Data data) noexcept;
        void                Next(bool enable, uint32_t address, Data data) noexcept;
        void                Next() noexcept;
        
        void                NextReset() noexcept;

        CombQueryResult     CombQuery(uint32_t address) const noexcept;

        void                Reset() noexcept;
        void                Eval() noexcept;
    };


    // Cached Refill Fetch Buffer (Instruction Fetch Buffer)
    class CachedRefillBuffer {
    public:
        using Address   = uint26_t;
        
        using Data      = uint36_t;

    private:
        SteppingDFF<Address>    refill_addr;

        SteppingDFF<bool>       refilled_valid[16];

        SteppingDFF<Data>       refilled_data[16];

    public:
        struct CombQueryResult {
            bool    hit;
            Data    data;
        };

    public:
        CachedRefillBuffer() noexcept;
        ~CachedRefillBuffer() noexcept;

        void                NextAddress(uint32_t address) noexcept;
        void                NextAddress(bool enable, uint32_t address) noexcept;
        void                NextAddress() noexcept;

        void                NextRefill(uint32_t index, Data data) noexcept;
        void                NextRefill(bool enable, uint32_t index, Data data) noexcept;
        void                NextRefill() noexcept;

        void                NextReset() noexcept;

        CombQueryResult     CombQuery(uint32_t address) const noexcept;

        void                Reset() noexcept;
        void                Eval() noexcept;
    };


    // L1 (attached) Instruction Cache
    class L1InstructionCache {
    public:
        using InstructionData   = uint36_t;

    private:
        class Tags {
        public:
            using TagValid  = bool;

            using TagValue  = uint19_t;

        private:
            TagValid    tag_valid[128];
            TagValue    tag_value[128];

            bool        next_enable;
            size_t      next_index;
            TagValid    next_valid;
            TagValue    next_value;

            bool        next_reset;

        public:
            Tags() noexcept;
            ~Tags() noexcept;

            void            Next(uint32_t address, bool valid) noexcept;
            void            Next(size_t index, TagValid valid, TagValue value) noexcept;
            void            Next();

            void            NextReset() noexcept;

            bool            CombQuery(uint32_t address) const noexcept;

            void            Reset() noexcept;
            void            Eval() noexcept;
        };

    private:
        DualPortRAM<InstructionData, 2048>  cache_ram;

        Tags                                cache_tags;

        SteppingDFF<bool>                   cache_tag_hit;

    public:
        struct CacheQueryResult {
            bool            hit;
            InstructionData data;
        };

    public:
        L1InstructionCache() noexcept;
        ~L1InstructionCache() noexcept;

        void                NextTagUpdate(uint32_t address, bool valid) noexcept;
        void                NextTagUpdate(bool enable, uint32_t address, bool valid) noexcept;
        void                NextTagUpdate() noexcept;

        void                NextDataUpdate(uint32_t address, InstructionData data) noexcept;
        void                NextDataUpdate(bool enable, uint32_t address, InstructionData data) noexcept;
        void                NextDataUpdate() noexcept;

        void                NextQuery(uint32_t address) noexcept;

        void                NextReset() noexcept;

        CacheQueryResult    GetLastQuery() const noexcept;

        void                Reset() noexcept;
        void                Eval() noexcept;
    };


    // Instruction Pre-decode
    class Predecoder {
    public:
        using RawInstructionData        = uint32_t;

        using PredecodedInstructionData = uint36_t;

    public:
        Predecoder() noexcept;
        ~Predecoder() noexcept;

        PredecodedInstructionData   Comb(RawInstructionData raw) const noexcept;
    };


    // Branch Predicition
    class BranchPredictor {
    public:
        static constexpr uint8_t    PHT_STATE_STRONG_TAKEN      = 0b01;
        static constexpr uint8_t    PHT_STATE_WEAK_TAKEN        = 0b00;
        static constexpr uint8_t    PHT_STATE_WEAK_NOT_TAKEN    = 0b10;
        static constexpr uint8_t    PHT_STATE_STRONG_NOT_TAKEN  = 0b11;

    public:
        using PHTEntry      = uint2_t;

        using BTBEntry      = uint36_t;

    private:
        DualPortRAM<PHTEntry, 8192>     pht_ram;

        DualPortRAM<BTBEntry, 1024>     btb_ram;

        GHR                             ghr;

        SteppingDFF<pc_t>               last_pc;

    public:
        struct BPQueryResult {
            bool        taken;
            PHTEntry    pattern;
            bool        target_valid;
            pc_t        target;
        };

    private:
        size_t              _GetPHTLineIndex(pc_t pc) const noexcept;
        size_t              _GetBTBLineIndex(pc_t pc) const noexcept;

        PHTEntry            _GetPHTNextState(PHTEntry oldpattern, bool taken) const noexcept;

        constexpr uint64_t  _GetBTBTag(pc_t pc) const noexcept;

        constexpr uint64_t  _GetBTBTag(BTBEntry line) const noexcept;
        constexpr bool      _GetBTBValid(BTBEntry line) const noexcept;
        constexpr pc_t      _GetBTBValue(BTBEntry line) const noexcept;

        constexpr BTBEntry  _NewBTBLine(pc_t pc, pc_t target) const noexcept;
    
    public:
        BranchPredictor() noexcept;
        ~BranchPredictor() noexcept;

        void                NextPC(pc_t pc) noexcept;

        void                NextPHTUpdate(pc_t pc, PHTEntry oldpattern, bool taken) noexcept;
        void                NextPHTUpdate(bool enable, pc_t pc, PHTEntry oldpattern, bool taken) noexcept;
        void                NextPHTUpdate() noexcept;

        void                NextBTBUpdate(pc_t pc, pc_t target) noexcept;
        void                NextBTBUpdate(bool enable, pc_t pc, pc_t target) noexcept;
        void                NextBTBUpdate() noexcept;

        void                NextReset() noexcept;
        
        BPQueryResult       GetLastQuery() const noexcept;

        void                Reset() noexcept;
        void                Eval() noexcept;
    };


    // AXI-4 Bus Controller
    class AXI4Controller {
    public:
        static constexpr uint8_t    FETCH_STATE_IDLE                = 0b000;

        static constexpr uint8_t    FETCH_STATE_UNCACHED_AXI_ADDR   = 0b100;
        static constexpr uint8_t    FETCH_STATE_UNCACHED_AXI_DATA   = 0b101;

        static constexpr uint8_t    FETCH_STATE_REFILL_AXI_ADDR     = 0b010;
        static constexpr uint8_t    FETCH_STATE_REFILL_AXI_DATA     = 0b011;

    public:
        using CacheLine     = uint36_t;

        using CacheAddress  = uint32_t;

        struct CacheUpdateData {
            bool            enable;
            CacheAddress    addr;
            CacheLine       data;
        };

        struct CacheUpdateTag {
            bool            enable;
            bool            valid;
            CacheAddress    addr;
        };


        using BufferLine    = uint36_t;

        using BufferAddress = uint32_t;

        using BufferOffset  = uint4_t;

        struct UncachedBufferUpdate {
            bool            enable;
            BufferAddress   addr;
            BufferLine      data;
        };
        
        struct RefillBufferUpdateAddress {
            bool            enable;
            BufferAddress   addr;
        };

        struct RefillBufferUpdateData {
            bool            enable;
            BufferOffset    addr;
            BufferLine      data;
        };

        struct RefillBufferUpdateControl {
            bool            reset;
        };

    private:
        //
        Predecoder          predecoder;

        uint3_t             state;
        uint5_t             axi_counter;

        uint4_t             raddr;
        uint32_t            curaddr;

        //
        bool                next_reset;

        //
        pc_t                next_pc;

        bool                next_cctrl_miss;
        bool                next_cctrl_uncached;

        //
        CacheUpdateData                 last_cache_update_data;
        CacheUpdateTag                  last_cache_update_tag;

        UncachedBufferUpdate            last_uncached_buffer_update;

        RefillBufferUpdateAddress       last_refill_buffer_update_address;
        RefillBufferUpdateData          last_refill_buffer_update_data;
        RefillBufferUpdateControl       last_refill_buffer_update_control;

        //
        FetchAXI4ReadAddressChannelS2M  axi_read_address;
        FetchAXI4ReadDataChannelS2M     axi_read_data;

        FetchAXI4ReadAddressChannelM2S  last_axi_read_address;
        FetchAXI4ReadDataChannelM2S     last_axi_read_data;


    public:
        AXI4Controller() noexcept;
        ~AXI4Controller() noexcept;

        void                        NextPC(pc_t pc) noexcept;

        void                        NextCacheControl(bool miss, bool uncached) noexcept;

        void                        NextReset() noexcept;

        CacheUpdateData             GetLastCacheUpdateData() const noexcept;
        CacheUpdateTag              GetLastCacheUpdateTag() const noexcept;

        UncachedBufferUpdate        GetLastUncachedBufferUpdate() const noexcept;

        RefillBufferUpdateAddress   GetLastRefillBufferUpdateAddress() const noexcept;
        RefillBufferUpdateData      GetLastRefillBufferUpdateData() const noexcept;
        RefillBufferUpdateControl   GetLastRefillBufferUpdateControl() const noexcept;

        // AXI interface
        FetchAXI4ReadAddressChannelM2S  GetLastAXI4ReadAddress() const noexcept;
        void                            NextAXI4ReadAddress(FetchAXI4ReadAddressChannelS2M bundle) noexcept;

        FetchAXI4ReadDataChannelM2S     GetLastAXI4ReadData() const noexcept;
        void                            NextAXI4ReadData(FetchAXI4ReadDataChannelS2M bundle) noexcept;

        //
        void                        Reset() noexcept;
        void                        Eval() noexcept;
    };

    
    // TODO
}



// Implementation of: class Fetch::UncachedBuffer
namespace BullsEye::Gemini30F2::Fetch {
    //
    // SteppingDFF<bool>       buffer_valid;
    //
    // SteppingDFF<Address>    buffer_addr;
    //
    // SteppingDFF<Data>       buffer_data;
    //

    UncachedBuffer::UncachedBuffer() noexcept
        : buffer_valid  ()
        , buffer_addr   ()
        , buffer_data   ()
    { }

    UncachedBuffer::~UncachedBuffer() noexcept
    { }

    inline void UncachedBuffer::Next(uint32_t address, Data data) noexcept
    {
        buffer_valid.Next   (true);
        buffer_addr.Next    (address >> 2);
        buffer_data.Next    (data);
    }

    inline void UncachedBuffer::Next(bool enable, uint32_t address, Data data) noexcept
    {
        if (enable)
            Next(address, data);
    }

    inline void UncachedBuffer::Next() noexcept
    {
        buffer_valid.Next(false);
    }

    inline void UncachedBuffer::NextReset() noexcept
    {
        buffer_valid.NextReset();
    }

    inline UncachedBuffer::CombQueryResult UncachedBuffer::CombQuery(uint32_t address) const noexcept
    {
        return CombQueryResult {
            .hit    = buffer_valid.Get() && buffer_addr.Get() == (address >> 2), 
            .data   = buffer_data.Get() 
        };
    }

    inline void UncachedBuffer::Reset() noexcept
    {
        buffer_valid.Reset();
        buffer_addr.Reset();
        buffer_data.Reset();
    }

    inline void UncachedBuffer::Eval() noexcept
    {
        buffer_valid.Eval();
        buffer_addr.Eval();
        buffer_data.Eval();

        buffer_valid.Next(false);
    }
}


// Implementation of: class Fetch::CachedRefillBuffer
namespace BullsEye::Gemini30F2::Fetch {
    //
    // SteppingDFF<Address>    refill_addr;
    //
    // SteppingDFF<bool>       refilled_valid[16];
    //
    // SteppingDFF<Data>       refilled_data[16];
    //

    CachedRefillBuffer::CachedRefillBuffer() noexcept
        : refill_addr       ()
        , refilled_valid    ()
        , refilled_data     ()
    { }

    CachedRefillBuffer::~CachedRefillBuffer() noexcept
    { }

    inline void CachedRefillBuffer::NextAddress(uint32_t address) noexcept
    {
        refill_addr.Next(address >> 6);
    }

    inline void CachedRefillBuffer::NextAddress(bool enable, uint32_t address) noexcept
    {
        if (enable)
            NextAddress(address);
    }

    inline void CachedRefillBuffer::NextAddress() noexcept
    {
        refill_addr.Next();
    }

    inline void CachedRefillBuffer::NextRefill(uint32_t index, Data data) noexcept
    {
        refilled_valid[index].Next(true);
        refilled_data[index].Next(data);
    }

    inline void CachedRefillBuffer::NextRefill(bool enable, uint32_t index, Data data) noexcept
    {
        if (enable)
            NextRefill(index, data);
    }

    void CachedRefillBuffer::NextRefill() noexcept
    {
        for (int i = 0; i < 16; i++)
        {
            refilled_valid[i].Next();
            refilled_data[i].Next();
        }
    }

    void CachedRefillBuffer::NextReset() noexcept
    {
        for (auto& valid : refilled_valid)
            valid.NextReset();
    }

    inline CachedRefillBuffer::CombQueryResult CachedRefillBuffer::CombQuery(uint32_t address) const noexcept
    {
        uint32_t index = (address >> 2) & 0xF;

        return CombQueryResult {
            .hit    = refilled_valid[index].Get() && refill_addr.Get() == (address >> 6), 
            .data   = refilled_data[index].Get() 
        };
    }

    void CachedRefillBuffer::Reset() noexcept
    {
        for (auto& valid : refilled_valid)
            valid.Reset();
    }

    void CachedRefillBuffer::Eval() noexcept
    {
        refill_addr.Eval();

        for (auto& valid : refilled_valid)
            valid.Eval();

        for (auto& data : refilled_data)
            data.Eval();
    }
}


// Implementation of: class Fetch::L1InstructionCache::Tags
namespace BullsEye::Gemini30F2::Fetch {
    //
    // TagValid    tag_valid[128];
    // TagValue    tag_value[128];
    //
    // bool        next_enable;
    // size_t      next_index;
    // TagValid    next_valid;
    // TagValue    next_value;
    //
    // bool        next_reset;
    //

    L1InstructionCache::Tags::Tags() noexcept
        : tag_valid     ()
        , tag_value     ()
        , next_enable   (false)
        , next_index    (0)
        , next_valid    (false)
        , next_value    (0)
        , next_reset    (false)
    { }

    L1InstructionCache::Tags::~Tags() noexcept
    { }

    inline void L1InstructionCache::Tags::Next(uint32_t address, bool valid) noexcept
    {
        Next((address >> 6) & 0x7F, valid, address >> 13);
    }

    inline void L1InstructionCache::Tags::Next(size_t index, TagValid valid, TagValue value) noexcept
    {
        next_enable = true;
        next_index  = index;
        next_valid  = valid;
        next_value  = value;
    }

    inline void L1InstructionCache::Tags::Next() noexcept
    {
        next_enable = false;
        next_reset  = false;
    }

    inline void L1InstructionCache::Tags::NextReset() noexcept
    {
        next_reset = true;
    }

    inline bool L1InstructionCache::Tags::CombQuery(uint32_t address) const noexcept
    {
        size_t index = (address >> 6) & 0x7F;

        return tag_valid[index] && tag_value[index] == (address >> 13);
    }

    void L1InstructionCache::Tags::Reset() noexcept
    {
        for (auto& valid : tag_valid)
            valid = false;
    }

    inline void L1InstructionCache::Tags::Eval() noexcept
    {
        if (next_enable)
        {
            tag_valid[next_index] = next_valid;
            tag_value[next_index] = next_value;
            
            next_enable = false;
        }

        if (next_reset)
        {
            Reset();
            next_reset = false;
        }
    }
}


// Implementation of: class Fetch::L1InstructionCache
namespace BullsEye::Gemini30F2::Fetch {
    //
    // DualPortRAM<InstructionData, 2048>  cache_ram;
    //
    // Tags                                cache_tags;
    //
    // SteppingDFF<bool>                   cache_tag_hit;
    //

    L1InstructionCache::L1InstructionCache() noexcept
        : cache_ram      ()
        , cache_tags     ()
        , cache_tag_hit  ()
    { }

    L1InstructionCache::~L1InstructionCache() noexcept
    { }

    inline void L1InstructionCache::NextTagUpdate(uint32_t address, bool valid) noexcept
    {
        cache_tags.Next(address, valid);
    }

    inline void L1InstructionCache::NextTagUpdate(bool enable, uint32_t address, bool valid) noexcept
    {
        if (enable)
            NextTagUpdate(address, valid);
    }

    inline void L1InstructionCache::NextTagUpdate() noexcept
    {
        cache_tags.Next();
    }

    inline void L1InstructionCache::NextDataUpdate(uint32_t address, InstructionData data) noexcept
    {
        cache_ram.NextWriteA((address >> 2) & 0x7FF, data);
    }

    inline void L1InstructionCache::NextDataUpdate(bool enable, uint32_t address, InstructionData data) noexcept
    {
        if (enable)
            NextDataUpdate(address, data);
    }

    inline void L1InstructionCache::NextDataUpdate() noexcept
    {
        cache_ram.NextWriteA();
    }

    inline void L1InstructionCache::NextQuery(uint32_t address) noexcept
    {
        cache_ram.NextReadB((address >> 2) & 0x7FF);
        cache_tag_hit.Next(cache_tags.CombQuery(address));
    }

    inline void L1InstructionCache::NextReset() noexcept
    {
        cache_tags.NextReset();
        cache_tag_hit.NextReset();
    }

    inline L1InstructionCache::CacheQueryResult L1InstructionCache::GetLastQuery() const noexcept
    {
        return CacheQueryResult {
            .hit    = cache_tag_hit.Get(), 
            .data   = cache_ram.GetLastReadB()
        };
    }

    inline void L1InstructionCache::Reset() noexcept
    {
        cache_tags.Reset();
        cache_tag_hit.Reset();
    }

    inline void L1InstructionCache::Eval() noexcept
    {
        cache_ram.Eval();
        cache_tags.Eval();
        cache_tag_hit.Eval();
    }
}


// Implementation of: class Fetch::Predecoder
namespace BullsEye::Gemini30F2::Fetch {

    Predecoder::Predecoder() noexcept
    { }

    Predecoder::~Predecoder() noexcept
    { }

    Predecoder::PredecodedInstructionData Predecoder::Comb(RawInstructionData raw) const noexcept
    {
        PredecodedInstructionData predecoded((uint64_t) raw);

        unsigned int opcode = MIPS32::GetOpcode(raw);
        unsigned int rt     = MIPS32::GetOpcode(raw);

        if (opcode == MIPS32_OPCODE_BEQ
        || (opcode == MIPS32_OPCODE_BNE)
        || (opcode == MIPS32_OPCODE_REGIMM && rt == MIPS32_RT_REGIMM_BGEZ)
        || (opcode == MIPS32_OPCODE_BGTZ && !rt)
        || (opcode == MIPS32_OPCODE_BLEZ && !rt)
        || (opcode == MIPS32_OPCODE_REGIMM && rt == MIPS32_RT_REGIMM_BLTZ))
        {
            predecoded |= (uint64_t(FETCH_PREDECODED_BRANCH) << 32);
        }
        else if (opcode == MIPS32_OPCODE_J
        ||      (opcode == MIPS32_OPCODE_SPECIAL && MIPS32::GetFunct(raw) == MIPS32_FUNCT_SPECIAL_JR 
                                                 && !rt 
                                                 && !MIPS32::GetRD(raw) 
                                                 && !MIPS32::GetShamt(raw)))
        {
            predecoded |= (uint64_t(FETCH_PREDECODED_JUMP) << 32);
        }
        else if (opcode == MIPS32_OPCODE_JAL
        ||      (opcode == MIPS32_OPCODE_SPECIAL && MIPS32::GetFunct(raw) == MIPS32_FUNCT_SPECIAL_JALR
                                                 && !rt
                                                 && !MIPS32::GetShamt(raw)))
        {
            predecoded |= (uint64_t(FETCH_PREDECODED_JUMP_LINK) << 32);
        }
        else
        {
            predecoded |= (uint64_t(FETCH_PREDECODED_NORMAL) << 32);
        }

        return predecoded;
    }
}


// Implementation of: class Fetch::BranchPredictor
namespace BullsEye::Gemini30F2::Fetch {
    //
    // DualPortRAM<PHTEntry, 8192>     pht_ram;
    //
    // DualPortRAM<BTBEntry, 1024>     btb_ram;
    //
    // GHR                             ghr;
    //
    // SteppingDFF<pc_t>               last_pc;
    //

    BranchPredictor::BranchPredictor() noexcept
        : pht_ram   ()
        , btb_ram   ()
        , ghr       ()
        , last_pc   ()
    { }

    BranchPredictor::~BranchPredictor() noexcept
    { }

    inline size_t BranchPredictor::_GetPHTLineIndex(pc_t pc) const noexcept
    {
        GHRValue ghr_value = ghr.Get();

        return ((pc ^ (((uint32_t) (uint8_t) ghr_value) << 9)) & 0x1800)
             |  (pc & 0x03FC)
             |  ((uint8_t) ghr_value & 0x03);
    }

    inline size_t BranchPredictor::_GetBTBLineIndex(pc_t pc) const noexcept
    {
        return (pc >> 2) & 0x3FF;
    }

    inline BranchPredictor::PHTEntry BranchPredictor::_GetPHTNextState(PHTEntry oldpattern, bool taken) const noexcept
    {
        if (taken)
        {
            switch ((uint8_t) oldpattern)
            {
                PHT_STATE_STRONG_TAKEN:     return PHT_STATE_STRONG_TAKEN;
                PHT_STATE_WEAK_TAKEN:       return PHT_STATE_STRONG_TAKEN;
                PHT_STATE_WEAK_NOT_TAKEN:   return PHT_STATE_WEAK_TAKEN;
                PHT_STATE_STRONG_NOT_TAKEN: return PHT_STATE_WEAK_NOT_TAKEN;
                [[unlikely]] default:       break;
            }
        }
        else
        {
            switch ((uint8_t) oldpattern)
            {
                PHT_STATE_STRONG_TAKEN:     return PHT_STATE_WEAK_TAKEN;
                PHT_STATE_WEAK_TAKEN:       return PHT_STATE_WEAK_NOT_TAKEN;
                PHT_STATE_WEAK_NOT_TAKEN:   return PHT_STATE_STRONG_NOT_TAKEN;
                PHT_STATE_STRONG_NOT_TAKEN: return PHT_STATE_STRONG_NOT_TAKEN;
                [[unlikely]] default:       break;
            }
        }

        return PHT_STATE_WEAK_NOT_TAKEN;
    }

    inline constexpr uint64_t BranchPredictor::_GetBTBTag(pc_t pc) const noexcept
    {
        return (pc >> 12) & 0x1F;
    }

    inline constexpr uint64_t BranchPredictor::_GetBTBTag(BTBEntry line) const noexcept
    {
        return (line >> 30) & 0x1F;
    }

    inline constexpr bool BranchPredictor::_GetBTBValid(BTBEntry line) const noexcept
    {
        return (line & 0x8'0000'0000UL);
    }

    inline constexpr pc_t BranchPredictor::_GetBTBValue(BTBEntry line) const noexcept
    {
        return (line & 0x3FFF'FFFF) << 2;
    }

    inline constexpr BranchPredictor::BTBEntry BranchPredictor::_NewBTBLine(pc_t pc, pc_t target) const noexcept
    {
        return (uint64_t) (0x8'0000'0000UL | (_GetBTBTag(pc) << 30) | (target >> 2));
    }

    inline void BranchPredictor::NextPC(pc_t pc) noexcept
    {
        pht_ram.NextReadB(_GetPHTLineIndex(pc));
        btb_ram.NextReadB(_GetBTBLineIndex(pc));

        last_pc.Next(pc);
    }

    inline void BranchPredictor::NextPHTUpdate(pc_t pc, PHTEntry oldpattern, bool taken) noexcept
    {
        pht_ram.NextWriteA(_GetPHTLineIndex(pc), _GetPHTNextState(oldpattern, taken));
    }

    inline void BranchPredictor::NextPHTUpdate(bool enable, pc_t pc, PHTEntry oldpattern, bool taken) noexcept
    {
        if (enable)
            NextPHTUpdate(pc, oldpattern, taken);
    }

    inline void BranchPredictor::NextPHTUpdate() noexcept
    {
        pht_ram.NextWriteA();
    }

    inline void BranchPredictor::NextBTBUpdate(pc_t pc, pc_t target) noexcept
    {
        btb_ram.NextWriteA(_GetBTBLineIndex(pc), _NewBTBLine(pc, target));
    }

    inline void BranchPredictor::NextBTBUpdate(bool enable, pc_t pc, pc_t target) noexcept
    {
        if (enable)
            NextBTBUpdate(pc, target);
    }

    inline void BranchPredictor::NextBTBUpdate() noexcept
    {
        btb_ram.NextWriteA();
    }

    inline void BranchPredictor::NextReset() noexcept
    {
        ghr.NextReset();
    }

    inline BranchPredictor::BPQueryResult BranchPredictor::GetLastQuery() const noexcept
    {
        PHTEntry pht_line = pht_ram.GetLastReadB();
        BTBEntry btb_line = btb_ram.GetLastReadB();

        return BPQueryResult {
            .taken          = (pht_line == PHT_STATE_STRONG_TAKEN) || (pht_line == PHT_STATE_WEAK_TAKEN),
            .pattern        = pht_line,
            .target_valid   = _GetBTBValid(btb_line) && (_GetBTBTag(btb_line) == _GetBTBTag(last_pc.Get())),
            .target         = _GetBTBValue(btb_line)
        };
    }

    inline void BranchPredictor::Reset() noexcept
    {
        ghr.Reset();
        last_pc.Reset();
    }

    inline void BranchPredictor::Eval() noexcept
    {
        pht_ram.Eval();
        btb_ram.Eval();
        ghr.Eval();
        last_pc.Eval();
    }
}


// Implementation of: class Fetch::AXI4Controller
namespace BullsEye::Gemini30F2::Fetch {
    //
    // //
    // Predecoder          predecoder;
    //
    // uint3_t             state;
    // uint5_t             axi_counter;
    //
    // uint4_t             raddr;
    // uint32_t            curaddr;
    //
    // //
    // bool                next_reset;
    //
    // //
    // pc_t                next_pc;
    //
    // bool                next_cctrl_miss;
    // bool                next_cctrl_uncached;
    //
    // //
    // FetchAXI4ReadAddressChannelS2M  axi_read_address;
    // FetchAXI4ReadDataChannelS2M     axi_read_data;
    //
    // FetchAXI4ReadAddressChannelM2S  last_axi_read_address;
    // FetchAXI4ReadDataChannelM2S     last_axi_read_data;
    //

    AXI4Controller::AXI4Controller()
        : predecoder                        ()
        , state                             (FETCH_STATE_IDLE)
        , axi_counter                       (0)
        , raddr                             (0)
        , curaddr                           (0)
        , next_reset                        (false)
        , next_pc                           (0)
        , next_cctrl_miss                   (false)
        , next_cctrl_uncached               (false)
        , last_cache_update_data            { .enable = false }
        , last_cache_update_tag             { .enable = false }
        , last_uncached_buffer_update       { .enable = false }
        , last_refill_buffer_update_address { .enable = false }
        , last_refill_buffer_update_data    { .enable = false }
        , last_refill_buffer_update_control { .reset = false }
        , axi_read_address                  { .arready = false }
        , axi_read_data                     { .rvalid = false }
        , last_axi_read_address             { .arvalid = false }
        , last_axi_read_data                { .rready = false }
    { }

    AXI4Controller::~AXI4Controller()
    { }

    inline void AXI4Controller::NextPC(pc_t pc) noexcept
    {
        next_pc = pc;
    }

    inline void AXI4Controller::NextCacheControl(bool miss, bool uncached) noexcept
    {
        next_cctrl_miss     = miss;
        next_cctrl_uncached = uncached;
    }

    inline void AXI4Controller::NextReset() noexcept
    {
        next_reset = true;
    }

    inline AXI4Controller::CacheUpdateData AXI4Controller::GetLastCacheUpdateData() const noexcept
    {
        return last_cache_update_data;
    }

    inline AXI4Controller::CacheUpdateTag AXI4Controller::GetLastCacheUpdateTag() const noexcept
    {
        return last_cache_update_tag;
    }

    inline AXI4Controller::UncachedBufferUpdate AXI4Controller::GetLastUncachedBufferUpdate() const noexcept
    {
        return last_uncached_buffer_update;
    }

    inline AXI4Controller::RefillBufferUpdateAddress AXI4Controller::GetLastRefillBufferUpdateAddress() const noexcept
    {
        return last_refill_buffer_update_address;
    }

    inline AXI4Controller::RefillBufferUpdateData AXI4Controller::GetLastRefillBufferUpdateData() const noexcept
    {
        return last_refill_buffer_update_data;
    }

    inline AXI4Controller::RefillBufferUpdateControl AXI4Controller::GetLastRefillBufferUpdateControl() const noexcept
    {
        return last_refill_buffer_update_control;
    }

    inline FetchAXI4ReadAddressChannelM2S AXI4Controller::GetLastAXI4ReadAddress() const noexcept
    {
        return last_axi_read_address;
    }

    inline void AXI4Controller::NextAXI4ReadAddress(FetchAXI4ReadAddressChannelS2M bundle) noexcept
    {
        axi_read_address = bundle;
    }

    inline FetchAXI4ReadDataChannelM2S AXI4Controller::GetLastAXI4ReadData() const noexcept
    {
        return last_axi_read_data;
    }

    inline void AXI4Controller::NextAXI4ReadData(FetchAXI4ReadDataChannelS2M bundle) noexcept
    {
        axi_read_data = bundle;
    }

    void AXI4Controller::Reset() noexcept
    {
        state = FETCH_STATE_IDLE;

        axi_counter = 0;
        raddr       = 0;
        curaddr     = 0;

        next_reset = false;

        next_pc = 0;

        next_cctrl_miss     = false;
        next_cctrl_uncached = false;

        last_cache_update_data  = { .enable = false };
        last_cache_update_tag   = { .enable = false };

        last_uncached_buffer_update = { .enable = false };

        last_refill_buffer_update_address   = { .enable = false };
        last_refill_buffer_update_data      = { .enable = false };
        last_refill_buffer_update_control   = { .reset = false };

        axi_read_address        = { .arready = false };
        axi_read_data           = { .rvalid = false };
        last_axi_read_address   = { .arvalid = false };
        last_axi_read_data      = { .rready = false };
    }

    void AXI4Controller::Eval() noexcept
    {
        // State transition
        uint3_t     state_next          = state;
        uint5_t     axi_counter_next    = axi_counter;

        uint4_t     raddr_next          = raddr;
        uint32_t    curaddr_next        = curaddr;

        bool    refill_read_comb    = false;
        bool    refill_done_comb    = false;
        bool    uncached_read_comb  = false;

        switch (state)
        {
            //
            case FETCH_STATE_IDLE:

                if (next_cctrl_uncached)
                {
                    curaddr_next = next_pc;
                    raddr_next   = next_pc >> 2;

                    state_next = FETCH_STATE_UNCACHED_AXI_ADDR;
                }
                else if (next_cctrl_miss)
                {
                    curaddr_next = next_pc;
                    raddr_next   = next_pc >> 2;

                    axi_counter_next = 0;

                    state_next = FETCH_STATE_REFILL_AXI_ADDR;
                }

                break;

            //
            case FETCH_STATE_UNCACHED_AXI_ADDR:

                if (axi_read_address.arready)
                    state_next = FETCH_STATE_UNCACHED_AXI_DATA;

                break;

            //
            case FETCH_STATE_UNCACHED_AXI_DATA:

                if (axi_read_data.rvalid)
                {
                    uncached_read_comb = true;

                    state_next = FETCH_STATE_IDLE;
                }

                break;

            //
            case FETCH_STATE_REFILL_AXI_ADDR:

                if (axi_read_address.arready)
                    state_next = FETCH_STATE_REFILL_AXI_DATA;

                break;

            //
            case FETCH_STATE_REFILL_AXI_DATA:

                if (axi_counter & 0x10)
                {
                    refill_done_comb = true;

                    state_next = FETCH_STATE_IDLE;
                }
                else if (axi_read_data.rvalid)
                {
                    axi_counter_next++;
                    raddr_next++;

                    refill_read_comb = true;

                    state_next = FETCH_STATE_REFILL_AXI_DATA;
                }

                break;

            //
            default:
                break;
        }

        // AXI interface logics
        switch (state)
        {
            //
            case FETCH_STATE_IDLE:

                if (state_next == FETCH_STATE_UNCACHED_AXI_ADDR)
                {
                    last_axi_read_address.araddr    = next_pc;
                    last_axi_read_address.arlen     = AXI4::Attributes::AXLEN<1>;
                    last_axi_read_address.arsize    = AXI4::Attributes::AXSIZE<4>;
                    last_axi_read_address.arburst   = AXI4::Attributes::AXBURST_INCR;
                    last_axi_read_address.aruser    = true;
                    last_axi_read_address.arvalid   = true;
                }
                else if (state_next == FETCH_STATE_REFILL_AXI_ADDR)
                {
                    last_axi_read_address.araddr    = next_pc;
                    last_axi_read_address.arlen     = AXI4::Attributes::AXLEN<16>;
                    last_axi_read_address.arsize    = AXI4::Attributes::AXSIZE<4>;
                    last_axi_read_address.arburst   = AXI4::Attributes::AXBURST_WRAP;
                    last_axi_read_address.aruser    = false;
                    last_axi_read_address.arvalid   = true;
                }

                break;

            //
            case FETCH_STATE_UNCACHED_AXI_ADDR:

                if (state_next == FETCH_STATE_IDLE)
                    last_axi_read_address.arvalid = false;
                else if (state_next == FETCH_STATE_UNCACHED_AXI_DATA)
                    last_axi_read_address.arvalid = false;

                break;

            //
            case FETCH_STATE_UNCACHED_AXI_DATA:
                break;

            //
            case FETCH_STATE_REFILL_AXI_ADDR:

                if (state_next = FETCH_STATE_IDLE)
                    last_axi_read_address.arvalid = false;
                else if (state_next == FETCH_STATE_REFILL_AXI_DATA)
                    last_axi_read_address.arvalid = false;

                break;

            //
            case FETCH_STATE_REFILL_AXI_DATA:
                break;

            //
            default:
                break;
        }

        //
        state       = state_next;
        axi_counter = axi_counter_next;

        raddr       = raddr_next;
        curaddr     = curaddr_next;

        //
        Predecoder::PredecodedInstructionData predecoded =
            predecoder.Comb(axi_read_data.rdata);

        //
        last_cache_update_data.enable   = refill_read_comb;
        last_cache_update_data.addr     = ( curaddr & 0xFFFFFFC0 ) | ( ((uint32_t) raddr) << 4 );
        last_cache_update_data.data     = predecoded;

        last_cache_update_tag.enable    = refill_read_comb || refill_done_comb;
        last_cache_update_tag.addr      = curaddr;
        last_cache_update_tag.valid     = refill_done_comb;

        //
        last_uncached_buffer_update.enable  = uncached_read_comb;
        last_uncached_buffer_update.addr    = curaddr;
        last_uncached_buffer_update.data    = predecoded;

        //
        last_refill_buffer_update_address.enable    = refill_read_comb;
        last_refill_buffer_update_address.addr      = curaddr;

        last_refill_buffer_update_data.enable       = refill_read_comb;
        last_refill_buffer_update_data.addr         = raddr;
        last_refill_buffer_update_data.data         = predecoded;

        last_refill_buffer_update_control.reset     = refill_done_comb;

        //
        last_axi_read_address.arid = 0;

        //
        last_axi_read_data.rready = true;
    }
}
