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

    using BranchPrediction  = Issue::Issue::BranchPrediction;
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


    // Branch Recovery Table
    class BranchRecoveryTable {

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

    public:
        struct ToBRU {
            bool                valid;

            Global::PC          pc;

            RegisterValue       src0_value;
            RegisterValue       src1_value;

            ROBIndex            dst_rob;

            Immediate           imm;

            Global::FID         fid;

            BRUCommand          bru_cmd;
            BAGUCommand         bagu_cmd;

            BranchPrediction    bp;
        };



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
