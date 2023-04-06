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

#include "models/util/mips32helper.hpp"


#include "def_global.hpp"


namespace BullsEye::Gemini30F2::Fetch {

    // GHR (Global History Register)
    using GHRValue  = truncated_uint8_t<4>;
    using GHR       = SteppingDFF<GHRValue>;


    // Uncached Fetch Buffer (Instruction Fetch Buffer)
    class UncachedBuffer {
    public:
        using Address   = truncated_uint32_t<30>;

        using Data      = truncated_uint64_t<36>;

    private:
        SteppingDFF<bool>       buffer_valid;

        SteppingDFF<Address>    buffer_addr;

        SteppingDFF<Data>       buffer_data;

    public:
        class CombQueryResult {
        private:
            bool    hit;
            Data    data;

        public:
            CombQueryResult(bool hit, Data data) noexcept;

            bool    Hit() const noexcept;
            Data    Data() const noexcept;
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
        using Address   = truncated_uint32_t<26>;
        
        using Data      = truncated_uint64_t<36>;

    private:
        SteppingDFF<Address>    refill_addr;

        SteppingDFF<bool>       refilled_valid[16];

        SteppingDFF<Data>       refilled_data[16];

    public:
        class CombQueryResult {
        private:
            bool    hit;
            Data    data;

        public:
            CombQueryResult(bool hit, Data data) noexcept;

            bool    Hit() const noexcept;
            Data    Data() const noexcept;
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
        using InstructionData   = truncated_uint64_t<36>;

    private:
        class Tags {
        public:
            using TagValid  = bool;

            using TagValue  = truncated_uint32_t<19>;

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
        class CacheQueryResult {
        private:
            bool            hit;
            InstructionData data;

        public:
            CacheQueryResult(bool hit, InstructionData data) noexcept;

            bool            Hit() const noexcept;
            InstructionData Data() const noexcept;
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

        using PredecodedInstructionData = truncated_uint32_t<36>;

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
        using PHTEntry      = truncated_uint8_t<2>;

        using BTBEntry      = truncated_uint64_t<36>;

    private:
        DualPortRAM<PHTEntry, 8192>     pht_ram;

        DualPortRAM<BTBEntry, 1024>     btb_ram;

        GHR                             ghr;

        SteppingDFF<pc_t>               last_pc;

    public:
        class BPQueryResult {
        private:
            bool        taken;
            PHTEntry    pattern;
            bool        target_valid;
            pc_t        target;

        public:
            BPQueryResult(bool taken, PHTEntry pattern, bool target_valid, pc_t target) noexcept;

            bool        Taken() const noexcept;
            PHTEntry    Pattern() const noexcept;
            bool        TargetValid() const noexcept;
            pc_t        Target() const noexcept;
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



    // TODO
}


// Implementation of: class Fetch::UncachedBuffer::CombQueryResult
namespace BullsEye::Gemini30F2::Fetch {
    //
    // bool    hit;
    // Data    data;
    //

    UncachedBuffer::CombQueryResult::CombQueryResult(bool hit, UncachedBuffer::Data data) noexcept
        : hit    (hit)
        , data   (data)
    { }

    bool UncachedBuffer::CombQueryResult::Hit() const noexcept
    {
        return hit;
    }

    UncachedBuffer::Data UncachedBuffer::CombQueryResult::Data() const noexcept
    {
        return data;
    }
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
        return CombQueryResult(
            buffer_valid.Get() && buffer_addr.Get() == (address >> 2), 
            buffer_data.Get());
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



// Implementation of: class Fetch::CachedRefillBuffer::CombQueryResult
namespace BullsEye::Gemini30F2::Fetch {
    //
    // bool    hit;
    // Data    data;
    //

    CachedRefillBuffer::CombQueryResult::CombQueryResult(bool hit, CachedRefillBuffer::Data data) noexcept
        : hit    (hit)
        , data   (data)
    { }

    bool CachedRefillBuffer::CombQueryResult::Hit() const noexcept
    {
        return hit;
    }

    CachedRefillBuffer::Data CachedRefillBuffer::CombQueryResult::Data() const noexcept
    {
        return data;
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

        return CombQueryResult(
            refilled_valid[index].Get() && refill_addr.Get() == (address >> 6), 
            refilled_data[index].Get());
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


// Implementation of: class Fetch::L1InstructionCache::CacheQueryResult
namespace BullsEye::Gemini30F2::Fetch {
    //
    // bool             hit;
    // InstructionData  data;
    //

    L1InstructionCache::CacheQueryResult::CacheQueryResult(bool hit, L1InstructionCache::InstructionData data) noexcept
        : hit    (hit)
        , data   (data)
    { }

    bool L1InstructionCache::CacheQueryResult::Hit() const noexcept
    {
        return hit;
    }

    L1InstructionCache::InstructionData L1InstructionCache::CacheQueryResult::Data() const noexcept
    {
        return data;
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
        return CacheQueryResult(cache_tag_hit.Get(), cache_ram.GetLastReadB());
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
        PredecodedInstructionData predecoded(raw);

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



// Implementation of: class Fetch::BranchPredictor::BPQueryResult
namespace BullsEye::Gemini30F2::Fetch {
    //
    // bool        taken;
    // PHTEntry    pattern;
    // bool        target_valid;
    // pc_t        target;

    BranchPredictor::BPQueryResult::BPQueryResult(bool taken, PHTEntry pattern, bool target_valid, pc_t target) noexcept
        : taken         (taken)
        , pattern       (pattern)
        , target_valid  (target_valid)
        , target        (target)
    { }

    inline bool BranchPredictor::BPQueryResult::Taken() const noexcept
    {
        return taken;
    }

    inline BranchPredictor::PHTEntry BranchPredictor::BPQueryResult::Pattern() const noexcept
    {
        return pattern;
    }

    inline bool BranchPredictor::BPQueryResult::TargetValid() const noexcept
    {
        return target_valid;
    }

    inline pc_t BranchPredictor::BPQueryResult::Target() const noexcept
    {
        return target;
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

        return BPQueryResult(
            (pht_line == PHT_STATE_STRONG_TAKEN) || (pht_line == PHT_STATE_WEAK_TAKEN),
            pht_line,
            _GetBTBValid(btb_line) && (_GetBTBTag(btb_line) == _GetBTBTag(last_pc.Get())),
            _GetBTBValue(btb_line)
        );
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
