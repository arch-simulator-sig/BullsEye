#pragma once
//
// Execute Stage models for RMM4NC30F2X (Gemini 30F2)
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


namespace BullsEye::Gemini30F2::Execute {

    using RegisterValue     = Global::ArchitecturalRegisterValue;

    using RegisterIndex     = Global::ArchitecturalRegisterIndex;

    using Immediate         = Decode::Immediate;

    using ROBIndex          = Decode::ReOrderBuffer::Index;

    using CommitDelay       = Decode::ReOrderBuffer::CommitDelay;

    using ALUCommand        = Decode::ALUCommand;

    using MULCommand        = Decode::MULCommand;

    using BRUCommand        = Decode::BRUCommand;

    using BAGUCommand       = Decode::BAGUCommand;

    using MEMCommand        = Decode::MEMCommand;

    using BranchPrediction  = Issue::Issue::BranchPrediction;

    using PhysicalAddress   = Global::PhysicalAddress;

    using VirtualAddress    = Global::VirtualAddress;
}


namespace BullsEye::Gemini30F2::Execute {


    // ALU
    class ALU {
    public:
        using RegisterValue         = RegisterValue;

        using ROBIndex              = ROBIndex;

        using Immediate             = Immediate;

        using CommitDelay           = CommitDelay;

        using ALUCommand            = ALUCommand;

    public:
        struct ToALU {
            bool            valid;

            RegisterValue   src0_value;
            bool            src0_forward;

            RegisterValue   src1_value;
            bool            src1_forward;

            ROBIndex        dst_rob;

            Immediate       imm;

            Global::FID     fid;

            ALUCommand      alu_cmd;
        };

        struct FromALU {
            bool            valid;
            ROBIndex        dst_rob;
            Global::FID     fid;

            RegisterValue   result;
            CommitDelay     cmtdelay;
        };

    private:
        SteppingDFF<RegisterValue>  forward;

        bool                        next_reset;

    public:
        ALU() noexcept;
        ~ALU() noexcept;

        void        NextReset() noexcept;

        FromALU     Comb(const ToALU& bundle) noexcept;

        void        Reset() noexcept;
        void        Eval() noexcept;
    };


    // DFFs before ALU
    class DFFsBeforeALU {
    public:
        using ToALU             = ALU::ToALU;

    private:
        SteppingDFF<ToALU, decltype([] (ToALU& bundle) {
            bundle.valid = false;
        })>                             dff;
    
    public:
        DFFsBeforeALU() noexcept;
        ~DFFsBeforeALU() noexcept;

        void        NextToALU(const ToALU& bundle) noexcept;

        void        NextReset() noexcept;

        ToALU       GetLastToALU() const noexcept;

        void        Reset() noexcept;
        void        Eval() noexcept;
    };


    // DFFs after ALU
    class DFFsAfterALU {
    public:
        using FromALU           = ALU::FromALU;

    private:
        SteppingDFF<FromALU, decltype([] (FromALU& bundle) {
            bundle.valid = false;
        })>                             dff;

    public:
        DFFsAfterALU() noexcept;
        ~DFFsAfterALU() noexcept;

        void        NextFromALU(const FromALU& bundle) noexcept;

        void        NextReset() noexcept;

        FromALU     GetLastFromALU() const noexcept;

        void        Reset() noexcept;
        void        Eval() noexcept;
    };
    


    // MUL
    class MUL {
    public:
        using RegisterValue         = RegisterValue;

        using ROBIndex              = ROBIndex;

        using CommitDelay           = CommitDelay;

        using MULCommand            = MULCommand;

    public:
        struct ToMUL {
            bool            valid;

            RegisterValue   src0_value;
            RegisterValue   src1_value;

            ROBIndex        dst_rob;

            Global::FID     fid;

            MULCommand      mul_cmd;
        };

        struct FromMUL {
            bool            valid;
            ROBIndex        dst_rob;
            Global::FID     fid;

            RegisterValue   result;
            CommitDelay     cmtdelay;  
        };

    private:
        struct StageSync {
            bool            valid;
            ROBIndex        dst_rob;
            Global::FID     fid;
            RegisterValue   value;
        };

        SteppingDFF<StageSync, decltype([] (StageSync& bundle) {
            bundle.valid = false;
        })>                             sync_dffs[3];

    public:
        MUL() noexcept;
        ~MUL() noexcept;

        void        NextToMUL(const ToMUL& bundle) noexcept;

        void        NextReset() noexcept;

        FromMUL     GetLastFromMUL() const noexcept;

        void        Reset() noexcept;
        void        Eval() noexcept;
    };


    // DFFs before MUL
    class DFFsBeforeMUL {
    public:
        using ToMUL             = MUL::ToMUL;

    private:
        SteppingDFF<ToMUL, decltype([] (ToMUL& bundle) {
            bundle.valid = false;
        })>                             dff;

    public:
        DFFsBeforeMUL() noexcept;
        ~DFFsBeforeMUL() noexcept;

        void        NextToMUL(const ToMUL& bundle) noexcept;

        void        NextReset() noexcept;

        ToMUL       GetLastToMUL() const noexcept;

        void        Reset() noexcept;
        void        Eval() noexcept;
    };



    // Branch Address Generation Unit
    class BranchAddressGenerationUnit {
    public:
        using RegisterValue         = RegisterValue;

        using Immediate             = Immediate;

        using BAGUCommand           = BAGUCommand;

    public:
        struct ToBAGU {
            Global::PC      pc;

            RegisterValue   src0_value;
            RegisterValue   src1_value;

            Immediate       imm;

            BAGUCommand     bagu_cmd;
        };

        struct FromBAGU {
            Global::PC      target;
            Global::PC      wavefront;
        };

    private:
        Global::PC              _PCRelative(const ToBAGU& bundle) const noexcept;
        Global::PC              _PCFromImmedate(const ToBAGU& bundle) const noexcept;
        Global::PC              _PCFromRegister(const ToBAGU& bundle) const noexcept;
        Global::PC              _PCWavefront(const ToBAGU& bundle) const noexcept;

    public:
        BranchAddressGenerationUnit() noexcept;
        ~BranchAddressGenerationUnit() noexcept;

        FromBAGU                Comb(const ToBAGU& bundle) const noexcept;
    };


    // Branch Condition
    class BranchCondition {
    public:
        using RegisterValue         = RegisterValue;

        using BRUCommand            = BRUCommand;

    public:
        struct ToBranchCondition {
            RegisterValue   src0_value;
            RegisterValue   src1_value;

            BRUCommand      bru_cmd;
        };

        struct FromBranchCondition {
            bool            taken;
        };

    private:
        bool                    _SignalGreaterThanZero(const ToBranchCondition& bundle) const noexcept;
        bool                    _SignalEqualsZero(const ToBranchCondition& bundle) const noexcept;
        bool                    _SignalLessThanZero(const ToBranchCondition& bundle) const noexcept;
        bool                    _SignalEquals(const ToBranchCondition& bundle) const noexcept;

    public:
        BranchCondition() noexcept;
        ~BranchCondition() noexcept;

        FromBranchCondition     Comb(const ToBranchCondition& bundle) const noexcept;
    };


    // BRU
    class BRU {
    public:
        using RegisterValue         = RegisterValue;

        using ROBIndex              = ROBIndex;

        using Immediate             = Immediate;

        using BRUCommand            = BRUCommand;

        using BAGUCommand           = BAGUCommand;

        using BranchPrediction      = BranchPrediction;

        using PatternHistory        = Fetch::BranchPredictor::PHTEntry;

    public:
        struct ToBRU {
            bool                    valid;

            Global::PC              pc;

            RegisterValue           src0_value;
            RegisterValue           src1_value;

            ROBIndex                dst_rob;

            Immediate               imm;

            Global::FID             fid;

            BRUCommand              bru_cmd;
            BAGUCommand             bagu_cmd;

            BranchPrediction        bp;
        };

        struct BranchCommitOverride {
            bool                    valid;
            Global::PC              pc;
            PatternHistory          oldpattern;
            bool                    taken;
            Global::PC              target;
        };

        struct FromBRU {
            bool                    valid;
            ROBIndex                dst_rob;
            Global::FID             fid;

            RegisterValue           result;

            BranchCommitOverride    bco;
        };

    private:
        BranchAddressGenerationUnit     module_agu;
        BranchCondition                 module_cond;

    public:
        BRU() noexcept;
        ~BRU() noexcept;

        FromBRU                 Comb(const ToBRU& bundle) const noexcept;
    };


    // DFFs before BRU
    class DFFsBeforeBRU {
    public:
        using ToBRU             = BRU::ToBRU;

    private:
        SteppingDFF<ToBRU, decltype([] (ToBRU& bundle) {
            bundle.valid = false;
        })>                             dff;

    public:
        DFFsBeforeBRU() noexcept;
        ~DFFsBeforeBRU() noexcept;

        void        NextToBRU(const ToBRU& bundle) noexcept;

        void        NextReset() noexcept;

        ToBRU       GetLastToBRU() const noexcept;

        void        Reset() noexcept;
        void        Eval() noexcept;
    };


    // DFFs after BRU
    class DFFsAfterBRU {
    public:
        using FromBRU           = BRU::FromBRU;

    private:
        SteppingDFF<FromBRU, decltype([] (FromBRU& bundle) {
            bundle.valid = false;
        })>                             dff;

    public:
        DFFsAfterBRU() noexcept;
        ~DFFsAfterBRU() noexcept;

        void        NextFromBRU(const FromBRU& bundle) noexcept;

        void        NextReset() noexcept;

        FromBRU     GetLastFromBRU() const noexcept;

        void        Reset() noexcept;
        void        Eval() noexcept;
    };



    // MEM Address Generation Unit
    class MemoryAddressGenerationUnit {
    public:
        using RegisterValue             = RegisterValue;

        using Immediate                 = Immediate;

        using VirtualAddress            = VirtualAddress;

        using PhysicalAddress           = PhysicalAddress;

    public:
        struct ToMEMAGU {
            RegisterValue       src0_value;
            RegisterValue       src1_value;

            Immediate           imm;
        };

        struct FromMEMAGU {
            VirtualAddress      vaddr;
            PhysicalAddress     paddr;
            bool                uncached;
        };

    private:
        Global::VPAddressConvertion     module_vpaddr;
        
    public:
        MemoryAddressGenerationUnit() noexcept;
        ~MemoryAddressGenerationUnit() noexcept;

        FromMEMAGU                      Comb(const ToMEMAGU& bundle) const noexcept;
    };


    // L1 Data Cache Tag
    class L1DataCacheTag {
    public:
        using TagValid                  = bool;

        using TagValue                  = uint19_t;

        using TagAddress                = uint8_t;

    public:
        struct TagWrite {
            bool            enable;
            TagAddress      address;
            TagValid        valid;
            TagValue        value;
        };

        struct TagReadResult {
            TagValid        valid;
            TagValue        value;
        };
    
    private:
        TagValid    valid[256];
        TagValue    value[256];

        TagWrite    next_write;

        bool        next_reset;

    public:
        L1DataCacheTag() noexcept;
        ~L1DataCacheTag() noexcept;

        void                NextWrite(const TagWrite& bundle) noexcept;

        void                NextReset() noexcept;

        TagReadResult       CombReadPortA(TagAddress address) const noexcept;
        TagReadResult       CombReadPortB(TagAddress address) const noexcept;

        void                Reset() noexcept;
        void                Eval() noexcept;
    };


    // L1 Data Cache
    class L1DataCache {
    public:
        using PhysicalAddress           = PhysicalAddress;

        using CacheData                 = uint32_t;

        using DataStrobe                = std::bitset<4>;

        using TagAddress                = L1DataCacheTag::TagAddress;

        using TagValid                  = L1DataCacheTag::TagValid;

        using TagValue                  = L1DataCacheTag::TagValue;

        using TagReadResult             = L1DataCacheTag::TagReadResult;

    private:
        using CacheDataStrobeRoutine    = decltype([] (uint32_t& dst, uint32_t src, std::bitset<4> strobe) {
            dst = (dst & (strobe[0] ? 0x000000FF : 0x00000000))
                | (dst & (strobe[1] ? 0x0000FF00 : 0x00000000))
                | (dst & (strobe[2] ? 0x00FF0000 : 0x00000000))
                | (dst & (strobe[3] ? 0xFF000000 : 0x00000000))
                | (src & (strobe[0] ? 0x00000000 : 0x000000FF))
                | (src & (strobe[1] ? 0x00000000 : 0x0000FF00))
                | (src & (strobe[2] ? 0x00000000 : 0x00FF0000))
                | (src & (strobe[3] ? 0x00000000 : 0xFF000000));
        });

    public:
        struct CacheUpdateTag {
            bool                enable;
            PhysicalAddress     address;
            bool                valid;
        };

        struct CacheUpdateData {
            bool                valid;
            PhysicalAddress     address;
            DataStrobe          strobe;
            CacheData           data;
        };

        struct CacheStore {
            bool                enable;
            PhysicalAddress     address;
            DataStrobe          strobe;
            CacheData           data;
        };

        struct CacheQueryResult {
            bool                hit;
            CacheData           data;
        };

        struct TagQueryResult {
            bool                hit;
        };

    private:
        L1DataCacheTag                              module_cache_tag;
        DualPortRAM<CacheData, 2048, std::bitset<4>, CacheDataStrobeRoutine>                
                                                    module_cache_ram;

        SteppingDFF<CacheUpdateData, decltype([] (CacheUpdateData& bundle) {
            bundle.valid    = false;
        })>                                         dff_ram_update_data;

        SteppingDFF<PhysicalAddress, DFFNoReset>    dff_tag_read_address0;
        SteppingDFF<TagReadResult, decltype([] (TagReadResult& bundle) {
            bundle.valid    = false;
        })>                                         dff_tag_read_result0;

        SteppingDFF<PhysicalAddress, DFFNoReset>    dff_tag_read_address1;
        SteppingDFF<TagReadResult, decltype([] (TagReadResult& bundle) {
            bundle.valid    = false;
        })>                                         dff_tag_read_result1;

        CacheStore                                  next_store;

        bool                                        next_reset;

    private:
        static TagAddress   _ToTagAddress(PhysicalAddress address) noexcept;
        static TagValue     _ToTagValue(PhysicalAddress address) noexcept;

        static size_t       _ToRAMAddress(PhysicalAddress address) noexcept;

    public:
        L1DataCache() noexcept;
        ~L1DataCache() noexcept;

        void                NextUpdateTag(const CacheUpdateTag& bundle) noexcept;
        void                NextUpdateData(const CacheUpdateData& bundle) noexcept;

        void                NextStore(const CacheStore& bundle);

        void                NextQueryCache(PhysicalAddress address) noexcept;
        void                NextQueryTag(PhysicalAddress address) noexcept;

        void                NextReset() noexcept;

        bool                CombUpdateDataReady() const noexcept;

        CacheQueryResult    GetLastQueryCache() const noexcept;
        TagQueryResult      GetLastQueryTag() const noexcept;

        void                Reset() noexcept;
        void                Eval() noexcept;
    };


    // Store Buffer
    class StoreBuffer {
    public:
        using Data                  = L1DataCache::CacheData;

        using DataStrobe            = L1DataCache::DataStrobe;

        using LoadStoreWidth        = Decode::LoadStoreWidth;

        using PhysicalAddress       = PhysicalAddress;

    public:
        struct WriteOnStore {
            bool                enable;
            DataStrobe          strobe;
            LoadStoreWidth      lswidth;
            PhysicalAddress     address;
            Data                data;
            bool                uncached;
        };

        struct CommitCandidate {
            bool                valid;
            PhysicalAddress     address;
            DataStrobe          strobe;
            LoadStoreWidth      lswidth;
            Data                data;
            bool                uncached;
        };

        struct QueryResult {
            DataStrobe          strobe;
            Data                data;
        };

    private:
        using FIFOPosition          = std::bitset<7>;

        struct Entry {
            PhysicalAddress     address;

            bool                uncached;
            LoadStoreWidth      lswidth;

            bool                b0_strobe;
            uint8_t             b0_data;

            bool                b1_strobe;
            uint8_t             b1_data;

            bool                b2_strobe;
            uint8_t             b2_data;

            bool                b3_strobe;
            uint8_t             b3_data;
        };

    private:
        SteppingDFF<FIFOPosition, DFFResetValue<1>> fifo_pos;
        
        Entry           storebuffer[6];

        WriteOnStore    next_write_on_store;

        bool            next_commit_enable;

        bool            next_bco_valid;

        bool            next_reset;

    private:
        bool                _SignalEmpty() const noexcept;
        bool                _SignalFull() const noexcept;

        bool                _SignalFunctionallyPop() const noexcept;
        bool                _SignalFunctionallyPush() const noexcept;

        bool                _SignalPositionHold() const noexcept;
        bool                _SignalPositionPop() const noexcept;
        bool                _SignalPositionPush() const noexcept;

        bool                _SignalPositionShiftRight() const noexcept;

        std::bitset<6>      _SignalPositionValid() const noexcept;

    public:
        StoreBuffer() noexcept;
        ~StoreBuffer() noexcept;

        void                NextWriteOnStore(const WriteOnStore& bundle) noexcept;

        void                NextCommitEnable(bool enable) noexcept;

        void                NextBranchCommitOverride(bool bco_valid) noexcept;

        void                NextReset() noexcept;

        QueryResult         CombQuery(PhysicalAddress address) const noexcept;

        CommitCandidate     GetLastCommitCandidate() const noexcept;

        void                Reset() noexcept;
        void                Eval() noexcept;
    };


    // Post-commit Buffer
    class PostCommitBuffer {
    public:
        using Data                  = L1DataCache::CacheData;

        using DataStrobe            = L1DataCache::DataStrobe;

        using LoadStoreWidth        = Decode::LoadStoreWidth;

        using PhysicalAddress       = PhysicalAddress;

    public:
        struct WriteOnCommit {
            bool                enable;
            PhysicalAddress     address;
            DataStrobe          strobe;
            LoadStoreWidth      lswidth;
            Data                data;
            bool                uncached;
        };

        struct MemoryWritebackCandidate {
            bool                valid;
            PhysicalAddress     address;
            DataStrobe          strobe;
            LoadStoreWidth      lswidth;
            Data                data;
            bool                uncached;
        };

        struct CacheStore {
            bool                enable;
            PhysicalAddress     address;
            DataStrobe          strobe;
            Data                data;
        };

        struct CacheStoreCandidate {
            bool                enable;

            bool                valid;
            PhysicalAddress     address;
            DataStrobe          strobe;
            Data                data;
            bool                uncached;
        };

        struct QueryResult {
            DataStrobe          strobe;
            Data                data;
        };

    private:
        using FIFOPosition          = std::bitset<7>;

        struct Entry {
            PhysicalAddress     address;

            bool                uncached;
            LoadStoreWidth      lswidth;

            bool                b0_strobe;
            uint8_t             b0_data;

            bool                b1_strobe;
            uint8_t             b1_data;

            bool                b2_strobe;
            uint8_t             b2_data;

            bool                b3_strobe;
            uint8_t             b3_data;
        };

        struct CompensationEntry {
            bool                valid;

            PhysicalAddress     address;

            bool                b0_strobe;
            uint8_t             b0_data;

            bool                b1_strobe;
            uint8_t             b1_data;

            bool                b2_strobe;
            uint8_t             b2_data;

            bool                b3_strobe;
            uint8_t             b3_data;
        };

    private:
        SteppingDFF<FIFOPosition, DFFResetValue<1>> fifo_pos;

        SteppingDFF<CacheStoreCandidate, decltype([] (CacheStoreCandidate& bundle) {
            bundle.enable   = false;
        })>                                         dff_store;

        SteppingDFF<CompensationEntry, decltype([] (CompensationEntry& bundle) {
            bundle.valid    = false;
        })>                                         dff_compensation;

        Entry           buffer[6];

        WriteOnCommit   next_write_on_commit;

        bool            next_memory_writeback_enable;

        bool            next_memory_writeback_cache_hit;

        bool            next_loadbuffer_busy_hit;

        bool            next_reset;

    private:
        bool                _SignalEmpty() const noexcept;
        bool                _SignalFull() const noexcept;

        bool                _SignalFunctionallyPop() const noexcept;
        bool                _SignalFunctionallyPush() const noexcept;

        bool                _SignalPositionHold() const noexcept;
        bool                _SignalPositionPop() const noexcept;
        bool                _SignalPositionPush() const noexcept;

        bool                _SignalPositionShiftRight() const noexcept;

        std::bitset<6>      _SignalPositionValid() const noexcept;

    public:
        PostCommitBuffer() noexcept;
        ~PostCommitBuffer() noexcept;

        void                        NextWriteOnCommit(const WriteOnCommit& bundle) noexcept;

        void                        NextMemoryWritebackEnable(bool enable) noexcept;
        void                        NextMemoryWritebackCacheHit(bool cache_hit) noexcept;

        void                        NextLoadBufferBusyHit(bool busy_hit) noexcept;

        void                        NextReset() noexcept;

        QueryResult                 CombQuery(PhysicalAddress address) const noexcept;

        MemoryWritebackCandidate    GetLastMemoryWritebackCandidate() const noexcept;

        CacheStore                  GetLastCacheStore() const noexcept;
        
        PhysicalAddress             GetLastLoadBufferQuery() const noexcept;

        bool                        GetLastBusyOnUncached() const noexcept;
        bool                        GetLastCommitNotReady() const noexcept;

        void                        Reset() noexcept;
        void                        Eval() noexcept;
    };


    // MEM
    class MEM {
    public:
        using RegisterValue         = RegisterValue;

        using ROBIndex              = ROBIndex;

        using Immediate             = Immediate;

        using MEMCommand            = MEMCommand;

    public:
        struct ToMEM {
            bool                valid;

            RegisterValue       src0_value;
            RegisterValue       src1_value;

            ROBIndex            dst_rob;

            Immediate           imm;

            Global::FID         fid;

            MEMCommand          mem_cmd;
        };

    };


    // DFFs before MEM
    class DFFsBeforeMEM {
    public:
        using ToMEM             = MEM::ToMEM;

    private:
        SteppingDFF<ToMEM, decltype([] (ToMEM& bundle){
            bundle.valid = false;
        })>                             dff;

        bool                            bco_valid;

    public:
        DFFsBeforeMEM() noexcept;
        ~DFFsBeforeMEM() noexcept;

        void        NextToMEM(const ToMEM& bundle) noexcept;

        void        NextBranchCommitOverride(bool bco_valid) noexcept;

        void        NextReset() noexcept;

        ToMEM       GetLastToMEM() const noexcept;

        void        Reset() noexcept;
        void        Eval() noexcept;
    };
}


// Implementation of: class ALU
namespace BullsEye::Gemini30F2::Execute {
    //
    // SteppingDFF<RegisterValue>  forward;
    //
    // bool                        next_reset;
    //

    ALU::ALU() noexcept
        : forward       ()
        , next_reset    (false)
    { } 

    ALU::~ALU() noexcept
    { }

    inline void ALU::NextReset() noexcept
    {
        forward.NextReset();
    }

    ALU::FromALU ALU::Comb(const ToALU& bundle) noexcept
    {
        //
        RegisterValue src0 = bundle.src0_forward ? forward.Get() : bundle.src0_value;
        RegisterValue src1 = bundle.src1_forward ? forward.Get() : bundle.src1_value;

        RegisterValue   result;

        switch (bundle.alu_cmd)
        {
            case Decode::ALU_NOP:
                break;

            case Decode::ALU_ADD:
                result = src0 + src1;
                break;

            case Decode::ALU_ADDI:
                result = src0 + SEXT32_IMM16(bundle.imm);
                break;

            case Decode::ALU_SUB:
                result = src0 - src1;
                break;

            case Decode::ALU_SUBI:
                result = src0 - SEXT32_IMM16(bundle.imm);
                break;

            case Decode::ALU_AND:
                result = src0 & src1;
                break;

            case Decode::ALU_ANDI:
                result = src0 & ZEXT32_IMM16(bundle.imm);
                break;

            case Decode::ALU_OR:
                result = src0 | src1;
                break;

            case Decode::ALU_ORI:
                result = src0 | ZEXT32_IMM16(bundle.imm);
                break;

            case Decode::ALU_XOR:
                result = src0 ^ src1;
                break;

            case Decode::ALU_XORI:
                result = src0 ^ ZEXT32_IMM16(bundle.imm);
                break;

            case Decode::ALU_SLT:
                result = (signed) src0 < (signed) src1;
                break;

            case Decode::ALU_SLTU:
                result = (unsigned) src0 < (unsigned) src1;
                break;

            case Decode::ALU_SLL:
                result = src0 << (bundle.imm & 0x1F);
                break;

            case Decode::ALU_SLLV:
                result = src0 << (src1 & 0x1F);
                break;

            case Decode::ALU_SRL:
                result = src0 >> (bundle.imm & 0x1F);
                break;

            case Decode::ALU_SRLV:
                result = src0 >> (src1 & 0x1F);
                break;

            case Decode::ALU_SRA:
                result = (signed) src0 >> (bundle.imm & 0x1F);
                break;

            case Decode::ALU_SRAV:
                result = (signed) src0 >> (src1 & 0x1F);
                break;

            case Decode::ALU_LUI:
                result = ZEXT32_IMM16(bundle.imm) << 16;
                break;

            default:
                break;
        }

        //
        FromALU out;

        out.valid       = bundle.valid;
        out.dst_rob     = bundle.valid ? bundle.dst_rob : ROBIndex(0);
        out.fid         = bundle.valid ? bundle.fid     : Global::FID(0);
        out.result      = bundle.valid ? result         : RegisterValue(0);

        out.cmtdelay    = 0;

        return out;
    }

    inline void ALU::Reset() noexcept
    {
        forward.Reset();
    }

    inline void ALU::Eval() noexcept
    {
        forward.Eval();
    }
}


// Implementation of: class DFFsBeforeALU
namespace BullsEye::Gemini30F2::Execute {
    //
    // SteppingDFF<ToALU, decltype([] (ToALU& bundle) {
    //     bundle.valid = false;
    // })>                             dff;
    //

    DFFsBeforeALU::DFFsBeforeALU() noexcept
        : dff    ()
    { }

    DFFsBeforeALU::~DFFsBeforeALU() noexcept
    { }

    inline void DFFsBeforeALU::NextToALU(const ToALU& bundle) noexcept
    {
        dff.Next(bundle);
    }

    inline void DFFsBeforeALU::NextReset() noexcept
    {
        dff.NextReset();
    }

    inline DFFsBeforeALU::ToALU DFFsBeforeALU::GetLastToALU() const noexcept
    {
        return dff.Get();
    }

    inline void DFFsBeforeALU::Reset() noexcept
    {
        dff.Reset();
    }

    inline void DFFsBeforeALU::Eval() noexcept
    {
        dff.Eval();
    }
}


// Implementation of: class DFFsAfterALU
namespace BullsEye::Gemini30F2::Execute {
    //
    // SteppingDFF<FromALU, decltype([] (FromALU& bundle) {
    //     bundle.valid = false;
    // })>                             dff;
    //

    DFFsAfterALU::DFFsAfterALU() noexcept
        : dff    ()
    { }

    DFFsAfterALU::~DFFsAfterALU() noexcept
    { }

    inline void DFFsAfterALU::NextFromALU(const FromALU& bundle) noexcept
    {
        dff.Next(bundle);
    }

    inline void DFFsAfterALU::NextReset() noexcept
    {
        dff.NextReset();
    }

    inline DFFsAfterALU::FromALU DFFsAfterALU::GetLastFromALU() const noexcept
    {
        return dff.Get();
    }

    inline void DFFsAfterALU::Reset() noexcept
    {
        dff.Reset();
    }

    inline void DFFsAfterALU::Eval() noexcept
    {
        dff.Eval();
    }
}


// Implementation of: class MUL
namespace BullsEye::Gemini30F2::Execute {
    //
    // SteppingDFF<StageSync, decltype([] (StageSync& bundle) {
    //     bundle.valid = false;
    // })>                             sync_dffs[3];
    //

    MUL::MUL() noexcept
        : sync_dffs ()
    { }

    MUL::~MUL() noexcept
    { }

    inline void MUL::NextToMUL(const ToMUL& bundle) noexcept
    {
        sync_dffs[0].Next({
            .valid      = bundle.valid,
            .dst_rob    = bundle.dst_rob,
            .fid        = bundle.fid,
            .value      = bundle.src0_value * bundle.src1_value
        });
    }

    inline void MUL::NextReset() noexcept
    {
        sync_dffs[0].NextReset();
        sync_dffs[1].NextReset();
        sync_dffs[2].NextReset();
    }

    inline MUL::FromMUL MUL::GetLastFromMUL() const noexcept
    {
        StageSync sync = sync_dffs[2].Get();

        return FromMUL {
            .valid      = sync.valid,
            .dst_rob    = sync.valid ? sync.dst_rob : ROBIndex(0),
            .fid        = sync.valid ? sync.fid     : Global::FID(0),
            .result     = sync.valid ? sync.value   : RegisterValue(0),
            .cmtdelay   = 0
        };
    }

    inline void MUL::Reset() noexcept
    {
        sync_dffs[0].Reset();
        sync_dffs[1].Reset();
        sync_dffs[2].Reset();
    }

    inline void MUL::Eval() noexcept
    {
        //
        sync_dffs[1].Next(sync_dffs[0].Get());
        sync_dffs[2].Next(sync_dffs[1].Get());

        //
        sync_dffs[0].Eval();
        sync_dffs[1].Eval();
        sync_dffs[2].Eval();
    }
}


// Implementation of: class DFFsBeforeMUL
namespace BullsEye::Gemini30F2::Execute {
    //
    // SteppingDFF<ToMUL, decltype([] (ToMUL& bundle) {
    //     bundle.valid = false;
    // })>                             dff;
    //

    DFFsBeforeMUL::DFFsBeforeMUL() noexcept
        : dff    ()
    { }

    DFFsBeforeMUL::~DFFsBeforeMUL() noexcept
    { }

    inline void DFFsBeforeMUL::NextToMUL(const ToMUL& bundle) noexcept
    {
        dff.Next(bundle);
    }

    inline void DFFsBeforeMUL::NextReset() noexcept
    {
        dff.NextReset();
    }

    inline DFFsBeforeMUL::ToMUL DFFsBeforeMUL::GetLastToMUL() const noexcept
    {
        return dff.Get();
    }

    inline void DFFsBeforeMUL::Reset() noexcept
    {
        dff.Reset();
    }

    inline void DFFsBeforeMUL::Eval() noexcept
    {
        dff.Eval();
    }
}


// Implementation of: class BranchAddressGenerationUnit
namespace BullsEye::Gemini30F2::Execute {

    BranchAddressGenerationUnit::BranchAddressGenerationUnit() noexcept
    { }

    BranchAddressGenerationUnit::~BranchAddressGenerationUnit() noexcept
    { }

    inline Global::PC BranchAddressGenerationUnit::_PCRelative(const ToBAGU& bundle) const noexcept
    {
        return bundle.pc + 4 + (ZEXT32_IMM16(bundle.imm) << 2);
    }

    inline Global::PC BranchAddressGenerationUnit::_PCFromImmedate(const ToBAGU& bundle) const noexcept
    {
        return ((bundle.pc + 4) & 0xF0000000) | (ZEXT32_IMM26(bundle.imm) << 2);
    }

    inline Global::PC BranchAddressGenerationUnit::_PCFromRegister(const ToBAGU& bundle) const noexcept
    {
        return bundle.src0_value;
    }
    
    inline Global::PC BranchAddressGenerationUnit::_PCWavefront(const ToBAGU& bundle) const noexcept
    {
        return bundle.pc + 8;
    }

    BranchAddressGenerationUnit::FromBAGU BranchAddressGenerationUnit::Comb(const ToBAGU& bundle) const noexcept
    {
        FromBAGU result;

        switch (bundle.bagu_cmd)
        {
            case Decode::BAGU_IMM:
                result.target = _PCFromImmedate(bundle);
                break;

            case Decode::BAGU_REG:
                result.target = _PCFromRegister(bundle);
                break;

            default:
                result.target = _PCRelative(bundle);
                break;
        }

        result.wavefront = _PCWavefront(bundle);

        return result;
    }
}


// Implementation of: class BranchCondition 
namespace BullsEye::Gemini30F2::Execute {

    BranchCondition::BranchCondition() noexcept
    { }

    BranchCondition::~BranchCondition() noexcept
    { }

    inline bool BranchCondition::_SignalGreaterThanZero(const ToBranchCondition& bundle) const noexcept
    {
        return (signed) bundle.src0_value > 0;
    }

    inline bool BranchCondition::_SignalEqualsZero(const ToBranchCondition& bundle) const noexcept
    {
        return bundle.src0_value == 0;
    }

    inline bool BranchCondition::_SignalLessThanZero(const ToBranchCondition& bundle) const noexcept
    {
        return (signed) bundle.src0_value < 0;
    }

    inline bool BranchCondition::_SignalEquals(const ToBranchCondition& bundle) const noexcept
    {
        return bundle.src0_value == bundle.src1_value;
    }

    BranchCondition::FromBranchCondition BranchCondition::Comb(const ToBranchCondition& bundle) const noexcept
    {
        std::bitset<7> bru_cmd = (uint8_t) bundle.bru_cmd;

        FromBranchCondition result;

        result.taken = (bru_cmd[6])
                    || (bru_cmd[4] &&  _SignalGreaterThanZero(bundle))
                    || (bru_cmd[3] &&  _SignalEqualsZero(bundle))
                    || (bru_cmd[2] &&  _SignalLessThanZero(bundle))
                    || (bru_cmd[1] &&  _SignalEquals(bundle))
                    || (bru_cmd[0] && !_SignalEquals(bundle));

        return result;
    }
}


// Implementation of: class BRU
namespace BullsEye::Gemini30F2::Execute {
    //
    // BranchAddressGenerationUnit     module_agu;
    // BranchCondition                 module_cond;
    //

    BRU::BRU() noexcept
        : module_agu    ()
        , module_cond   ()
    { }

    BRU::~BRU() noexcept
    { }

    BRU::FromBRU BRU::Comb(const ToBRU& bundle) const noexcept
    {
        //
        BranchAddressGenerationUnit::FromBAGU agu = module_agu.Comb({
            .pc         = bundle.pc,
            .src0_value = bundle.src0_value,
            .src1_value = bundle.src1_value,
            .imm        = bundle.imm,
            .bagu_cmd   = bundle.bagu_cmd
        });

        //
        BranchCondition::FromBranchCondition cond = module_cond.Comb({
            .src0_value = bundle.src0_value,
            .src1_value = bundle.src1_value,
            .bru_cmd    = bundle.bru_cmd
        });

        //
        FromBRU result;

        result.valid    = bundle.valid;
        result.dst_rob  = bundle.valid ? bundle.dst_rob : ROBIndex(0);
        result.fid      = bundle.valid ? bundle.fid     : Global::FID(0);
        result.result   = bundle.valid ? agu.wavefront  : RegisterValue(0);

        result.bco = {
            .valid      = false,
            .pc         = bundle.pc,
            .oldpattern = bundle.bp.pattern,
            .taken      = cond.taken,
            .target     = cond.taken ? agu.target : agu.wavefront
        };

        if (cond.taken)
        {
            if (bundle.bp.taken && bundle.bp.hit)
                result.bco.valid = agu.target != bundle.bp.target;
            else
                result.bco.valid = true;
        }
        else
        {
            if (bundle.bp.taken && bundle.bp.hit)
                result.bco.valid = true;
            else
                result.bco.valid = false;
        }

        return result;
    }
}


// Implementation of: class DFFsBeforeBRU
namespace BullsEye::Gemini30F2::Execute {
    //
    // SteppingDFF<ToBRU, decltype([] (ToBRU& bundle) {
    //     bundle.valid = false;
    // })>                             dff;
    //

    DFFsBeforeBRU::DFFsBeforeBRU() noexcept
        : dff    ()
    { }

    DFFsBeforeBRU::~DFFsBeforeBRU() noexcept
    { }

    inline void DFFsBeforeBRU::NextToBRU(const ToBRU& bundle) noexcept
    {
        dff.Next(bundle);
    }

    inline void DFFsBeforeBRU::NextReset() noexcept
    {
        dff.NextReset();
    }

    inline DFFsBeforeBRU::ToBRU DFFsBeforeBRU::GetLastToBRU() const noexcept
    {
        return dff.Get();
    }

    inline void DFFsBeforeBRU::Reset() noexcept
    {
        dff.Reset();
    }

    inline void DFFsBeforeBRU::Eval() noexcept
    {
        dff.Eval();
    }
}


// Implementation of: class DFFsAfterBRU
namespace BullsEye::Gemini30F2::Execute {
    //
    // SteppingDFF<BRU::FromBRU, decltype([] (BRU::FromBRU& bundle) {
    //     bundle.valid = false;
    // })>                             dff;
    //

    DFFsAfterBRU::DFFsAfterBRU() noexcept
        : dff    ()
    { }

    DFFsAfterBRU::~DFFsAfterBRU() noexcept
    { }

    inline void DFFsAfterBRU::NextFromBRU(const BRU::FromBRU& bundle) noexcept
    {
        dff.Next(bundle);
    }

    inline void DFFsAfterBRU::NextReset() noexcept
    {
        dff.NextReset();
    }

    inline DFFsAfterBRU::FromBRU DFFsAfterBRU::GetLastFromBRU() const noexcept
    {
        return dff.Get();
    }

    inline void DFFsAfterBRU::Reset() noexcept
    {
        dff.Reset();
    }

    inline void DFFsAfterBRU::Eval() noexcept
    {
        dff.Eval();
    }
}


// Implementation of: class MemoryAddressGenerationUnit
namespace BullsEye::Gemini30F2::Execute {
    //
    // Global::VPAddressConvertion     module_vpaddr;
    //

    MemoryAddressGenerationUnit::MemoryAddressGenerationUnit() noexcept
        : module_vpaddr ()
    { }

    MemoryAddressGenerationUnit::~MemoryAddressGenerationUnit() noexcept
    { }

    MemoryAddressGenerationUnit::FromMEMAGU MemoryAddressGenerationUnit::Comb(const ToMEMAGU& bundle) const noexcept
    {
        FromMEMAGU result;

        //
        result.vaddr = bundle.src0_value + SEXT32_IMM16(bundle.imm);

        //
        Global::VPAddressConvertion::PhysicalAddressBundle vpaddr = module_vpaddr.Comb(result.vaddr);

        result.paddr    = vpaddr.paddr;
        result.uncached = vpaddr.kseg1;

        //
        return result;
    }
}


// Implementation of: class L1DataCacheTag
namespace BullsEye::Gemini30F2::Execute {
    //
    // TagValid    valid[256];
    // TagValue    value[256];
    //
    // TagWrite    next_write;
    //
    // bool        next_reset;
    //

    L1DataCacheTag::L1DataCacheTag() noexcept
        : valid         ()
        , value         ()
        , next_write    ()
        , next_reset    (false)
    { }

    L1DataCacheTag::~L1DataCacheTag() noexcept
    { }

    inline void L1DataCacheTag::NextWrite(const TagWrite& bundle) noexcept
    {
        next_write = bundle;
    }

    inline void L1DataCacheTag::NextReset() noexcept
    {
        next_reset = true;
    }

    inline L1DataCacheTag::TagReadResult L1DataCacheTag::CombReadPortA(TagAddress address) const noexcept
    {
        return TagReadResult {
            .valid  = valid[address],
            .value  = value[address]  
        };
    }

    inline L1DataCacheTag::TagReadResult L1DataCacheTag::CombReadPortB(TagAddress address) const noexcept
    {
        return TagReadResult {
            .valid  = valid[address],
            .value  = value[address]  
        };
    }

    void L1DataCacheTag::Reset() noexcept
    {
        for (unsigned i = 0; i < 256; i++)
            valid[i] = false;        
    }
    
    void L1DataCacheTag::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }

        //
        if (next_write.enable)
        {
            valid[next_write.address] = next_write.valid;
            value[next_write.address] = next_write.value;
        }
    }
}


// Implementation of: class L1DataCache
namespace BullsEye::Gemini30F2::Execute {
    //
    // L1DataCacheTag                              module_cache_tag;
    // DualPortRAM<CacheData, 2048>                module_cache_ram;
    //
    // SteppingDFF<CacheUpdateData, decltype([] (CacheUpdateData& bundle) {
    //     bundle.valid    = false;
    // })>                                         dff_ram_update_data;
    //
    // SteppingDFF<PhysicalAddress, DFFNoReset>    dff_tag_read_address0;
    // SteppingDFF<TagReadResult, decltype([] (TagReadResult& bundle) {
    //     bundle.valid    = false;
    // })>                                         dff_tag_read_result0;
    //
    // SteppingDFF<PhysicalAddress, DFFNoReset>    dff_tag_read_address1;
    // SteppingDFF<TagReadResult, decltype([] (TagReadResult& bundle) {
    //     bundle.valid    = false;
    // })>                                         dff_tag_read_result1;
    //
    // CacheStore                                  next_store;
    //
    // bool                                        next_reset;
    //

    L1DataCache::L1DataCache() noexcept
        : module_cache_tag        ()
        , module_cache_ram        ()
        , dff_ram_update_data     ()
        , dff_tag_read_address0   ()
        , dff_tag_read_result0    ()
        , dff_tag_read_address1   ()
        , dff_tag_read_result1    ()
        , next_store              ()
        , next_reset              (false)
    { }

    L1DataCache::~L1DataCache() noexcept
    { }

    inline L1DataCache::TagAddress L1DataCache::_ToTagAddress(PhysicalAddress address) noexcept
    {
        return TagAddress((address >> 5) & 0xFF);
    }

    inline L1DataCache::TagValue L1DataCache::_ToTagValue(PhysicalAddress address) noexcept
    {
        return TagValue((address >> 13) & 0x0007FFFF);
    }

    inline size_t L1DataCache::_ToRAMAddress(PhysicalAddress address) noexcept
    {
        return size_t((address >> 2) & 0x000007FF);
    }

    inline void L1DataCache::NextUpdateTag(const CacheUpdateTag& bundle) noexcept
    {
        module_cache_tag.NextWrite({
            .enable     = bundle.enable,
            .address    = _ToTagAddress(bundle.address),
            .valid      = bundle.valid,
            .value      = _ToTagValue(bundle.address)
        });
    }

    inline void L1DataCache::NextUpdateData(const CacheUpdateData& bundle) noexcept
    {
        dff_ram_update_data.Next(bundle);
    }

    inline void L1DataCache::NextStore(const CacheStore& bundle) noexcept
    {
        next_store = bundle;
    }

    inline void L1DataCache::NextQueryCache(PhysicalAddress address) noexcept
    {
        dff_tag_read_address0.Next(address);

        dff_tag_read_result0.Next(module_cache_tag.CombReadPortA(_ToTagAddress(address)));

        module_cache_ram.NextReadB(_ToRAMAddress(address));
    }

    inline void L1DataCache::NextQueryTag(PhysicalAddress address) noexcept
    {
        dff_tag_read_address1.Next(address);

        dff_tag_read_result1.Next(module_cache_tag.CombReadPortB(_ToTagAddress(address)));
    }

    inline void L1DataCache::NextReset() noexcept
    {
        next_reset = true;
    }

    inline bool L1DataCache::CombUpdateDataReady() const noexcept
    {
        return !next_store.enable;
    }

    inline L1DataCache::CacheQueryResult L1DataCache::GetLastQueryCache() const noexcept
    {
        return CacheQueryResult {
            .hit    = dff_tag_read_result0.Get().valid 
                && (dff_tag_read_result0.Get().value == _ToTagValue(dff_tag_read_address0.Get())),
            .data   = module_cache_ram.GetLastReadB()
        };
    }

    inline L1DataCache::TagQueryResult L1DataCache::GetLastQueryTag() const noexcept
    {
        return TagQueryResult {
            .hit    = dff_tag_read_result1.Get().valid 
                && (dff_tag_read_result1.Get().value == _ToTagValue(dff_tag_read_address1.Get()))
        };
    }

    void L1DataCache::Reset() noexcept
    {
        module_cache_tag.Reset();

        dff_ram_update_data.Reset();

        dff_tag_read_address0.Reset();
        dff_tag_read_result0.Reset();
        dff_tag_read_address1.Reset();
        dff_tag_read_result1.Reset();
    }

    void L1DataCache::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }

        //
        module_cache_ram.NextWriteA(
            next_store.enable ? true                : dff_ram_update_data.Get().valid,
            next_store.enable ? next_store.address  : dff_ram_update_data.Get().address,
            next_store.enable ? next_store.data     : dff_ram_update_data.Get().data,
            next_store.enable ? next_store.strobe   : dff_ram_update_data.Get().strobe
        );

        //
        if (next_store.enable)
            dff_ram_update_data.Next(dff_ram_update_data.Get());

        //
        module_cache_tag.Eval();
        module_cache_ram.Eval();

        dff_ram_update_data.Eval();

        dff_tag_read_address0.Eval();
        dff_tag_read_result0.Eval();
        dff_tag_read_address1.Eval();
        dff_tag_read_result1.Eval();
    }
}


// Implementation of: class StoreBuffer
namespace BullsEye::Gemini30F2::Execute {
    //
    // SteppingDFF<FIFOPosition, DFFResetValue<1>> fifo_pos;
    // 
    // Entry           storebuffer[6];
    //
    // WriteOnStore    next_write_on_store;
    //
    // bool            next_commit_enable;
    //
    // bool            next_bco_valid;
    //
    // bool            next_reset;
    //

    StoreBuffer::StoreBuffer() noexcept
        : fifo_pos              ()
        , storebuffer           ()
        , next_write_on_store   ()
        , next_commit_enable    ()
        , next_bco_valid        ()
        , next_reset            (false)
    { }

    StoreBuffer::~StoreBuffer() noexcept
    { }

    inline bool StoreBuffer::_SignalEmpty() const noexcept
    {
        return fifo_pos.Get()[0];
    }

    inline bool StoreBuffer::_SignalFull() const noexcept
    {
        return fifo_pos.Get()[6];
    }

    inline bool StoreBuffer::_SignalFunctionallyPop() const noexcept
    {
        return next_commit_enable && !_SignalEmpty();
    }

    inline bool StoreBuffer::_SignalFunctionallyPush() const noexcept
    {
        return (next_write_on_store.enable && !next_bco_valid) && !_SignalFull();
    }

    inline bool StoreBuffer::_SignalPositionHold() const noexcept
    {
        return _SignalFunctionallyPop() && (next_write_on_store.enable && !next_bco_valid);
    }

    inline bool StoreBuffer::_SignalPositionPop() const noexcept
    {
        return !_SignalPositionHold() && _SignalFunctionallyPop();
    }

    inline bool StoreBuffer::_SignalPositionPush() const noexcept
    {
        return !_SignalPositionHold() && _SignalFunctionallyPush();
    }

    inline bool StoreBuffer::_SignalPositionShiftRight() const noexcept
    {
        return _SignalFunctionallyPop();
    }

    inline std::bitset<6> StoreBuffer::_SignalPositionValid() const noexcept
    {
        std::bitset<6> p_valid;
        std::bitset<6> p_valid_carrier;

        p_valid         [5] = fifo_pos.Get()[6];
        p_valid_carrier [5] = p_valid[5];

        for (int i = 4; i >= 0; i--)
        {
            p_valid         [i] = fifo_pos.Get()[i + 1] || p_valid_carrier[i + 1];
            p_valid_carrier [i] = p_valid[i];
        }

        return p_valid;
    }

    inline void StoreBuffer::NextWriteOnStore(const WriteOnStore& bundle) noexcept
    {
        next_write_on_store = bundle;
    }

    inline void StoreBuffer::NextCommitEnable(bool enable) noexcept
    {
        next_commit_enable = enable;
    }

    inline void StoreBuffer::NextBranchCommitOverride(bool bco_valid) noexcept
    {
        next_bco_valid = bco_valid;
    }

    inline void StoreBuffer::NextReset() noexcept
    {
        next_reset = true;
    }

    StoreBuffer::QueryResult StoreBuffer::CombQuery(PhysicalAddress address) const noexcept
    {
        //
        std::bitset<6> p_valid = _SignalPositionValid();

        //
        std::bitset<4> sel_comb[4];

        sel_comb[0] = 0b1000;
        sel_comb[1] = 0b1000;
        sel_comb[2] = 0b1000;
        sel_comb[3] = 0b1000;

        for (int i = 0; i < 6; i++)
        {
            if (p_valid[i] && ((address >> 2) == (storebuffer[i].address >> 2)) && !storebuffer[i].uncached)
            {
                if (storebuffer[i].b0_strobe)
                    sel_comb[0] = i;

                if (storebuffer[i].b1_strobe)
                    sel_comb[1] = i;

                if (storebuffer[i].b2_strobe)
                    sel_comb[2] = i;

                if (storebuffer[i].b3_strobe)
                    sel_comb[3] = i;
            }
        }

        //
        QueryResult result;

        //
        result.strobe[3] = sel_comb[3][3] ? 0 : (p_valid[0] ? storebuffer[sel_comb[3].to_ulong() & 0x07].b3_strobe : 0);
        result.strobe[2] = sel_comb[2][3] ? 0 : (p_valid[0] ? storebuffer[sel_comb[2].to_ulong() & 0x07].b2_strobe : 0);
        result.strobe[1] = sel_comb[1][3] ? 0 : (p_valid[0] ? storebuffer[sel_comb[1].to_ulong() & 0x07].b1_strobe : 0);
        result.strobe[0] = sel_comb[0][3] ? 0 : (p_valid[0] ? storebuffer[sel_comb[0].to_ulong() & 0x07].b0_strobe : 0);

        result.data = ((storebuffer[sel_comb[3].to_ulong() & 0x07].b3_data) << 24)
                    | ((storebuffer[sel_comb[2].to_ulong() & 0x07].b2_data) << 16)
                    | ((storebuffer[sel_comb[1].to_ulong() & 0x07].b1_data) <<  8)
                    | ((storebuffer[sel_comb[0].to_ulong() & 0x07].b0_data) <<  0);

        return result;
    }

    StoreBuffer::CommitCandidate StoreBuffer::GetLastCommitCandidate() const noexcept
    {
        CommitCandidate result;

        result.valid        = _SignalPositionValid()[0];
        result.address      = storebuffer[0].address;

        result.strobe[3]    = storebuffer[0].b3_strobe;
        result.strobe[2]    = storebuffer[0].b2_strobe;
        result.strobe[1]    = storebuffer[0].b1_strobe;
        result.strobe[0]    = storebuffer[0].b0_strobe;

        result.lswidth      = storebuffer[0].lswidth;

        result.data         = (storebuffer[0].b3_data << 24)
                            | (storebuffer[0].b2_data << 16)
                            | (storebuffer[0].b1_data <<  8)
                            | (storebuffer[0].b0_data <<  0);
        
        result.uncached     = storebuffer[0].uncached;

        return result;
    }

    void StoreBuffer::Reset() noexcept
    {
        fifo_pos.Reset();

        next_reset = false;
    }
    
    void StoreBuffer::Eval() noexcept
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
        bool en_x = next_write_on_store.enable && !next_bco_valid;

        for (int i = 0; i < 6; i++)
        {
            if (_SignalPositionShiftRight())
            {
                if (en_x && fifo_pos.Get()[i + 1])
                {
                    storebuffer[i].address      = next_write_on_store.address;

                    storebuffer[i].uncached     = next_write_on_store.uncached;
                    storebuffer[i].lswidth      = next_write_on_store.lswidth;

                    storebuffer[i].b0_strobe    = next_write_on_store.strobe[0];
                    storebuffer[i].b0_data      = (next_write_on_store.data & 0x000000FF) >> 0;

                    storebuffer[i].b1_strobe    = next_write_on_store.strobe[1];
                    storebuffer[i].b1_data      = (next_write_on_store.data & 0x0000FF00) >> 8;

                    storebuffer[i].b2_strobe    = next_write_on_store.strobe[2];
                    storebuffer[i].b2_data      = (next_write_on_store.data & 0x00FF0000) >> 16;

                    storebuffer[i].b3_strobe    = next_write_on_store.strobe[3];
                    storebuffer[i].b3_data      = (next_write_on_store.data & 0xFF000000) >> 24;
                }
                else if (i < 5)
                    storebuffer[i]  = storebuffer[i + 1];
            }
            else if (en_x && fifo_pos.Get()[i])
            {
                storebuffer[i].address      = next_write_on_store.address;

                storebuffer[i].uncached     = next_write_on_store.uncached;
                storebuffer[i].lswidth      = next_write_on_store.lswidth;

                storebuffer[i].b0_strobe    = next_write_on_store.strobe[0];
                storebuffer[i].b0_data      = (next_write_on_store.data & 0x000000FF) >> 0;

                storebuffer[i].b1_strobe    = next_write_on_store.strobe[1];
                storebuffer[i].b1_data      = (next_write_on_store.data & 0x0000FF00) >> 8;

                storebuffer[i].b2_strobe    = next_write_on_store.strobe[2];
                storebuffer[i].b2_data      = (next_write_on_store.data & 0x00FF0000) >> 16;

                storebuffer[i].b3_strobe    = next_write_on_store.strobe[3];
                storebuffer[i].b3_data      = (next_write_on_store.data & 0xFF000000) >> 24;
            }
        }

        //
        fifo_pos.Eval();
    }
}


// Implementation of: class PostCommitBuffer
namespace BullsEye::Gemini30F2::Execute {
    //
    // SteppingDFF<FIFOPosition, DFFResetValue<1>> fifo_pos;
    //
    // SteppingDFF<CacheStoreCandidate, decltype([] (CacheStoreCandidate& bundle) {
    //     bundle.enable = false;
    // })>                                         dff_store;
    //
    // SteppingDFF<CompensationEntry, decltype([] (CompensationEntry& bundle) {
    //     bundle.valid    = false;
    // })>                                         dff_compensation;
    //
    // Entry           buffer[6];
    //
    // WriteOnCommit   next_write_on_commit;
    //
    // bool            next_memory_writeback_enable;
    //
    // bool            next_memory_writeback_cache_hit;
    //
    // bool            next_loadbuffer_busy_hit;
    //
    // bool            next_reset;
    //

    PostCommitBuffer::PostCommitBuffer() noexcept
        : fifo_pos                          ()
        , dff_store                         ()
        , dff_compensation                  ()
        , buffer                            ()
        , next_write_on_commit              ()
        , next_memory_writeback_enable      ()
        , next_memory_writeback_cache_hit   ()
        , next_loadbuffer_busy_hit          ()
        , next_reset                        (false)
    { }

    PostCommitBuffer::~PostCommitBuffer() noexcept
    { }

    inline bool PostCommitBuffer::_SignalEmpty() const noexcept
    {
        return fifo_pos.Get()[0];
    }

    inline bool PostCommitBuffer::_SignalFull() const noexcept
    {
        return fifo_pos.Get()[6];
    }

    inline bool PostCommitBuffer::_SignalFunctionallyPop() const noexcept
    {
        return next_memory_writeback_enable && !_SignalEmpty();
    }

    inline bool PostCommitBuffer::_SignalFunctionallyPush() const noexcept
    {
        return next_write_on_commit.enable && !_SignalFull();
    }

    inline bool PostCommitBuffer::_SignalPositionHold() const noexcept
    {
        return _SignalFunctionallyPop() && next_write_on_commit.enable;
    }

    inline bool PostCommitBuffer::_SignalPositionPop() const noexcept
    {
        return !_SignalPositionHold() && _SignalFunctionallyPop();
    }

    inline bool PostCommitBuffer::_SignalPositionPush() const noexcept
    {
        return !_SignalPositionHold() && _SignalFunctionallyPush();
    }

    inline bool PostCommitBuffer::_SignalPositionShiftRight() const noexcept
    {
        return _SignalFunctionallyPop();
    }

    inline std::bitset<6> PostCommitBuffer::_SignalPositionValid() const noexcept
    {
        std::bitset<6> p_valid;
        std::bitset<6> p_valid_carrier;

        p_valid         [5] = fifo_pos.Get()[6];
        p_valid_carrier [5] = p_valid[5];

        for (int i = 4; i >= 0; i--)
        {
            p_valid         [i] = fifo_pos.Get()[i + 1] || p_valid_carrier[i + 1];
            p_valid_carrier [i] = p_valid[i];
        }

        return p_valid;
    }

    inline void PostCommitBuffer::NextWriteOnCommit(const WriteOnCommit& bundle) noexcept
    {
        next_write_on_commit = bundle;
    }

    inline void PostCommitBuffer::NextMemoryWritebackEnable(bool enable) noexcept
    {
        next_memory_writeback_enable = enable;
    }

    inline void PostCommitBuffer::NextMemoryWritebackCacheHit(bool cache_hit) noexcept
    {
        next_memory_writeback_cache_hit = cache_hit;
    }

    inline void PostCommitBuffer::NextLoadBufferBusyHit(bool busy_hit) noexcept
    {
        next_loadbuffer_busy_hit = busy_hit;
    }

    inline void PostCommitBuffer::NextReset() noexcept
    {
        next_reset = true;
    }

    PostCommitBuffer::QueryResult PostCommitBuffer::CombQuery(PhysicalAddress address) const noexcept
    {
        //
        std::bitset<6> p_valid = _SignalPositionValid();

        //
        const CompensationEntry& comp = dff_compensation.Get();

        bool comp_hit = comp.valid && ((address >> 2) == (comp.address >> 2));

        //
        std::bitset<5> sel_comb[4];

        sel_comb[0] = 0b00000;
        sel_comb[1] = 0b00000;
        sel_comb[2] = 0b00000;
        sel_comb[3] = 0b00000;
        
        sel_comb[0][3] =  comp_hit;
        sel_comb[1][3] =  comp_hit;
        sel_comb[2][3] =  comp_hit;
        sel_comb[3][3] =  comp_hit;

        sel_comb[0][4] = !comp_hit;
        sel_comb[1][4] = !comp_hit;
        sel_comb[2][4] = !comp_hit;
        sel_comb[3][4] = !comp_hit;

        for (int i = 0; i < 6; i++)
        {
            if (p_valid[i] && ((address >> 2) == (buffer[i].address >> 2)) && !buffer[i].uncached)
            {
                if (buffer[i].b0_strobe)
                    sel_comb[0] = i;

                if (buffer[i].b1_strobe)
                    sel_comb[1] = i;

                if (buffer[i].b2_strobe)
                    sel_comb[2] = i;

                if (buffer[i].b3_strobe)
                    sel_comb[3] = i;
            }
        }

        //
        QueryResult result;

        //
        result.strobe[3] = sel_comb[3][4] ? 0 : (sel_comb[3][3] ? comp.b3_strobe : (p_valid[0] && buffer[sel_comb[3].to_ulong() & 0x07].b3_strobe));
        result.strobe[2] = sel_comb[2][4] ? 0 : (sel_comb[2][3] ? comp.b2_strobe : (p_valid[0] && buffer[sel_comb[2].to_ulong() & 0x07].b2_strobe));
        result.strobe[1] = sel_comb[1][4] ? 0 : (sel_comb[1][3] ? comp.b1_strobe : (p_valid[0] && buffer[sel_comb[1].to_ulong() & 0x07].b1_strobe));
        result.strobe[0] = sel_comb[0][4] ? 0 : (sel_comb[0][3] ? comp.b0_strobe : (p_valid[0] && buffer[sel_comb[0].to_ulong() & 0x07].b0_strobe));

        result.data = ((sel_comb[3][3] ? comp.b3_data : buffer[sel_comb[3].to_ulong() & 0x07].b3_data) << 24)
                    | ((sel_comb[2][3] ? comp.b2_data : buffer[sel_comb[2].to_ulong() & 0x07].b2_data) << 16)
                    | ((sel_comb[1][3] ? comp.b1_data : buffer[sel_comb[1].to_ulong() & 0x07].b1_data) <<  8)
                    | ((sel_comb[0][3] ? comp.b0_data : buffer[sel_comb[0].to_ulong() & 0x07].b0_data) <<  0);

        return result;
    }

    PostCommitBuffer::MemoryWritebackCandidate PostCommitBuffer::GetLastMemoryWritebackCandidate() const noexcept
    {
        MemoryWritebackCandidate result;

        result.valid        = _SignalPositionValid()[0] && !next_loadbuffer_busy_hit;
        result.address      = buffer[0].address;

        result.strobe[3]    = buffer[0].b3_strobe;
        result.strobe[2]    = buffer[0].b2_strobe;
        result.strobe[1]    = buffer[0].b1_strobe;
        result.strobe[0]    = buffer[0].b0_strobe;

        result.lswidth      = buffer[0].lswidth;

        result.data         = (buffer[0].b3_data << 24)
                            | (buffer[0].b2_data << 16)
                            | (buffer[0].b1_data <<  8)
                            | (buffer[0].b0_data <<  0);
        
        result.uncached     = buffer[0].uncached;

        return result;
    }

    inline PostCommitBuffer::CacheStore PostCommitBuffer::GetLastCacheStore() const noexcept
    {
        const CacheStoreCandidate& store = dff_store.Get();

        return CacheStore {
            .enable     = store.valid && !store.uncached && store.enable && next_memory_writeback_cache_hit,
            .address    = store.address,
            .strobe     = store.strobe,
            .data       = store.data
        };
    }

    inline PostCommitBuffer::PhysicalAddress PostCommitBuffer::GetLastLoadBufferQuery() const noexcept
    {
        return buffer[0].address;
    }

    bool PostCommitBuffer::GetLastBusyOnUncached() const noexcept
    {
        std::bitset<6> p_valid = _SignalPositionValid();

        for (int i = 0; i < 6; i++)
            if (p_valid[i] && buffer[i].uncached)
                return true;

        return false;
    }

    inline bool PostCommitBuffer::GetLastCommitNotReady() const noexcept
    {
        return fifo_pos.Get()[6] || fifo_pos.Get()[5];
    }

    void PostCommitBuffer::Reset() noexcept
    {
        fifo_pos.Reset();

        dff_store.Reset();

        dff_compensation.Reset();

        next_reset = false;
    }

    void PostCommitBuffer::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }


        //
        if (next_memory_writeback_enable && !buffer[0].uncached)
        {
            dff_compensation.Next({
                .valid      = true,

                .address    = buffer[0].address,

                .b0_strobe  = buffer[0].b0_strobe,
                .b0_data    = buffer[0].b0_data,

                .b1_strobe  = buffer[0].b1_strobe,
                .b1_data    = buffer[0].b1_data,

                .b2_strobe  = buffer[0].b2_strobe,
                .b2_data    = buffer[0].b2_data,

                .b3_strobe  = buffer[0].b3_strobe,
                .b3_data    = buffer[0].b3_data
            });
        }
        else
            dff_compensation.GetNext().valid = false;


        //
        MemoryWritebackCandidate doutc = GetLastMemoryWritebackCandidate();

        dff_store.Next({
            .enable     = next_memory_writeback_enable,

            .valid      = doutc.valid,
            .address    = doutc.address,
            .strobe     = doutc.strobe,
            .data       = doutc.data,
            .uncached   = doutc.uncached
        });


        //
        if (_SignalPositionPop())
            fifo_pos.Next(fifo_pos.Get() >> 1);
        else if (_SignalPositionPush())
            fifo_pos.Next(fifo_pos.Get() << 1);

        //
        bool en_c = next_write_on_commit.enable;

        for (int i = 0; i < 6; i++)
        {
            if (_SignalPositionShiftRight())
            {
                if (en_c && fifo_pos.Get()[i + 1])
                {
                    buffer[i].address      = next_write_on_commit.address;

                    buffer[i].uncached     = next_write_on_commit.uncached;
                    buffer[i].lswidth      = next_write_on_commit.lswidth;

                    buffer[i].b0_strobe    = next_write_on_commit.strobe[0];
                    buffer[i].b0_data      = (next_write_on_commit.data & 0x000000FF) >> 0;

                    buffer[i].b1_strobe    = next_write_on_commit.strobe[1];
                    buffer[i].b1_data      = (next_write_on_commit.data & 0x0000FF00) >> 8;

                    buffer[i].b2_strobe    = next_write_on_commit.strobe[2];
                    buffer[i].b2_data      = (next_write_on_commit.data & 0x00FF0000) >> 16;

                    buffer[i].b3_strobe    = next_write_on_commit.strobe[3];
                    buffer[i].b3_data      = (next_write_on_commit.data & 0xFF000000) >> 24;
                }
                else if (i < 5)
                    buffer[i]  = buffer[i + 1];
            }
            else if (en_c && fifo_pos.Get()[i])
            {
                buffer[i].address      = next_write_on_commit.address;

                buffer[i].uncached     = next_write_on_commit.uncached;
                buffer[i].lswidth      = next_write_on_commit.lswidth;

                buffer[i].b0_strobe    = next_write_on_commit.strobe[0];
                buffer[i].b0_data      = (next_write_on_commit.data & 0x000000FF) >> 0;

                buffer[i].b1_strobe    = next_write_on_commit.strobe[1];
                buffer[i].b1_data      = (next_write_on_commit.data & 0x0000FF00) >> 8;

                buffer[i].b2_strobe    = next_write_on_commit.strobe[2];
                buffer[i].b2_data      = (next_write_on_commit.data & 0x00FF0000) >> 16;

                buffer[i].b3_strobe    = next_write_on_commit.strobe[3];
                buffer[i].b3_data      = (next_write_on_commit.data & 0xFF000000) >> 24;
            }
        }


        //
        fifo_pos.Eval();

        dff_store.Eval();

        dff_compensation.Eval();
    }
}


// Implementation of: class MEM
namespace BullsEye::Gemini30F2::Execute {

}


// Implementation of: class DFFsBeforeMEM
namespace BullsEye::Gemini30F2::Execute {
    //
    // SteppingDFF<ToMEM, decltype([] (ToMEM& bundle){
    //     bundle.valid = false;
    // })>                             dff;
    //
    // bool                            bco_valid;
    //

    DFFsBeforeMEM::DFFsBeforeMEM() noexcept
        : dff        ()
        , bco_valid  (false)
    { }

    DFFsBeforeMEM::~DFFsBeforeMEM() noexcept
    { }

    inline void DFFsBeforeMEM::NextToMEM(const ToMEM& bundle) noexcept
    {
        dff.Next(bundle);
    }

    inline void DFFsBeforeMEM::NextBranchCommitOverride(bool bco_valid) noexcept
    {
        bco_valid = true;
    }

    inline void DFFsBeforeMEM::NextReset() noexcept
    {
        dff.NextReset();
    }

    inline DFFsBeforeMEM::ToMEM DFFsBeforeMEM::GetLastToMEM() const noexcept
    {
        return dff.Get();
    }

    inline void DFFsBeforeMEM::Reset() noexcept
    {
        dff.Reset();
    }

    inline void DFFsBeforeMEM::Eval() noexcept
    {
        //
        if (bco_valid)
            dff.GetNext().valid = false;

        //
        dff.Eval();
    }
}
