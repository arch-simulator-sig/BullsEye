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

    using RegisterIndex     = Global::ArchitecturalRegisterIndex;

    using RegisterValue     = Global::ArchitecturalRegisterValue;

    using Immediate         = uint26_t;

    using LoadStoreWidth    = uint2_t;

    using ALUCommand        = uint5_t;

    using MULCommand        = uint2_t;

    using MEMCommand        = uint5_t;

    using BRUCommand        = uint7_t;

    using BAGUCommand       = uint2_t;
}


namespace BullsEye::Gemini30F2::Decode {

    //
    static constexpr LoadStoreWidth     LSWIDTH_BYTE        = 0b00;
    static constexpr LoadStoreWidth     LSWIDTH_HALF_WORD   = 0b01;
    static constexpr LoadStoreWidth     LSWIDTH_WORD        = 0b10;
    static constexpr LoadStoreWidth     LSWIDTH_DOUBLE_WORD = 0b11;

    //
    static constexpr ALUCommand         ALU_NOP             = 0x00;
    static constexpr ALUCommand         ALU_ADD             = 0x01;
    static constexpr ALUCommand         ALU_ADDI            = 0x11;
    static constexpr ALUCommand         ALU_SUB             = 0x02;
    static constexpr ALUCommand         ALU_SUBI            = 0x12;
    static constexpr ALUCommand         ALU_AND             = 0x03;
    static constexpr ALUCommand         ALU_ANDI            = 0x13;
    static constexpr ALUCommand         ALU_OR              = 0x04;
    static constexpr ALUCommand         ALU_ORI             = 0x14;
    static constexpr ALUCommand         ALU_XOR             = 0x05;
    static constexpr ALUCommand         ALU_XORI            = 0x15;
    static constexpr ALUCommand         ALU_SLT             = 0x06;
    static constexpr ALUCommand         ALU_SLTU            = 0x0B;
    static constexpr ALUCommand         ALU_SLL             = 0x07;
    static constexpr ALUCommand         ALU_SLLV            = 0x17;
    static constexpr ALUCommand         ALU_SRL             = 0x08;
    static constexpr ALUCommand         ALU_SRLV            = 0x18;
    static constexpr ALUCommand         ALU_SRA             = 0x09;
    static constexpr ALUCommand         ALU_SRAV            = 0x19;
    static constexpr ALUCommand         ALU_LUI             = 0x0A;

    static constexpr MULCommand         MUL_NOP             = 0x00;
    static constexpr MULCommand         MUL_EN              = 0x01;

    static constexpr MEMCommand         MEM_NOP             = 0x00;
    static constexpr MEMCommand         MEM_LB              = 0x06;
    static constexpr MEMCommand         MEM_LW              = 0x02;
    static constexpr MEMCommand         MEM_SB              = 0x05;
    static constexpr MEMCommand         MEM_SW              = 0x01;
    static constexpr MEMCommand         MEM_BITMASK_STORE   = 0x01;
    static constexpr MEMCommand         MEM_BITMASK_LOAD    = 0x02;
    static constexpr MEMCommand         MEM_BITMASK_LSBYTE  = 0x04;

    static constexpr BRUCommand         BRU_NOP             = 0x00;
    static constexpr BRUCommand         BRU_JUMP            = 0x40;
    static constexpr BRUCommand         BRU_JCALL           = 0x60;
    static constexpr BRUCommand         BRU_BRANCH_EQ       = 0x02;
    static constexpr BRUCommand         BRU_BRANCH_NEQ      = 0x01;
    static constexpr BRUCommand         BRU_BRANCH_GEZ      = 0x18;
    static constexpr BRUCommand         BRU_BRANCH_GTZ      = 0x10;
    static constexpr BRUCommand         BRU_BRANCH_LEZ      = 0x0C;
    static constexpr BRUCommand         BRU_BRANCH_LTZ      = 0x04;

    static constexpr BAGUCommand        BAGU_NOP            = 0x00;
    static constexpr BAGUCommand        BAGU_RLT            = 0x01;
    static constexpr BAGUCommand        BAGU_IMM            = 0x02;
    static constexpr BAGUCommand        BAGU_REG            = 0x03;
}


namespace BullsEye::Gemini30F2::Decode {

    // Instruction Decoder
    class InstructionDecoder {
    public:
        struct Decoded {
            RegisterIndex   src0;
            RegisterIndex   src1;
            RegisterIndex   dst;

            Immediate       imm;

            bool            branch;
            bool            load;
            bool            store;
            LoadStoreWidth  lswidth;
            
            bool            pipe_alu;
            bool            pipe_mul;
            bool            pipe_mem;
            bool            pipe_bru;

            ALUCommand      alu_cmd;
            MULCommand      mul_cmd;
            MEMCommand      mem_cmd;
            BRUCommand      bru_cmd;
            BAGUCommand     bagu_cmd;
        };

    public:
        InstructionDecoder() noexcept;
        ~InstructionDecoder() noexcept;
        
        Decoded     CombDecode(Global::RawInstruction insn, bool valid) const noexcept;
    };


    // Instruction Decoder output DFFs
    class InstructionDecoderDFFs {
    private:
        Global::PC                      last_pc;
        Global::FID                     last_fid;
        InstructionDecoder::Decoded     last_decoded;
        Fetch::Fetch::BranchPrediction  last_branch_prediction;
        bool                            last_allocation_enable;

        Global::PC                      next_pc;
        Global::FID                     next_fid;
        InstructionDecoder::Decoded     next_decoded;
        Fetch::Fetch::BranchPrediction  next_branch_prediction;
        bool                            next_allocation_enable;

        bool                            next_bco_valid;

        bool                            next_reset;

    public:
        InstructionDecoderDFFs() noexcept;
        ~InstructionDecoderDFFs() noexcept;

        void                            NextPC(Global::PC pc) noexcept;
        void                            NextFID(Global::FID fid) noexcept;
        void                            NextDecoded(InstructionDecoder::Decoded bundle) noexcept;
        void                            NextBranchPrediction(Fetch::Fetch::BranchPrediction bundle) noexcept;
        void                            NextAllocationEnable(bool enable) noexcept;

        void                            NextBranchCommitOverride(bool bco_valid) noexcept;

        void                            NextReset() noexcept;

        Global::PC                      GetLastPC() const noexcept;
        Global::FID                     GetLastFID() const noexcept;
        InstructionDecoder::Decoded     GetLastDecoded() const noexcept;
        Fetch::Fetch::BranchPrediction  GetLastBranchPrediction() const noexcept;
        bool                            GetLastAllocationEnable() const noexcept;

        void                            Reset() noexcept;
        void                            Eval() noexcept;
    };



    // Register File (32b x 32)
    class RegisterFile {
    public:
        using Index         = RegisterIndex;

        using Value         = RegisterValue;

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
        Index           GetLastROBNext() const noexcept;

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

        struct ROBCommit {
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
        ROBCommit   next_writeback;

        bool        next_bco_valid;

        bool        next_reset;

    private:
        ReadResult      _Read(Index index) const noexcept;
    
    public:
        RegisterAliasTable() noexcept;
        ~RegisterAliasTable() noexcept;

        void            NextAllocation(Allocation bundle) noexcept;
        void            NextROBCommit(ROBCommit bundle) noexcept;

        void            NextBranchCommitOverride(bool valid) noexcept;

        void            NextReset() noexcept;

        ReadResult      CombReadPortA(Index index) const noexcept;
        ReadResult      CombReadPortB(Index index) const noexcept;

        void            Reset() noexcept;
        void            Eval() noexcept;
    };


    // Register And Rename
    class RegisterAndRename {
    public:
        struct RenameAndAllocation {
            bool                    enable;         // allocation enable

            Global::FID             fid;
            ReOrderBuffer::Index    rob;

            RegisterIndex           src0;
            RegisterIndex           src1;
            RegisterIndex           dst;
        };

        struct RenameResult {
            ReOrderBuffer::Index    src0_rob;
            bool                    src0_ready;
            RegisterValue           src0_value;

            ReOrderBuffer::Index    src1_rob;
            bool                    src1_ready;
            RegisterValue           src1_value;  
        };

        struct ROBRead {
            RegisterValue           value;
            bool                    ready;
        };

        struct ROBCommit {
            bool                    enable;
            RegisterIndex           addr;
            Global::FID             fid;
            RegisterValue           data;
        };
        
    private:
        RegisterFile            module_regfile;

        RegisterAliasTable      module_rat;

        ReOrderBuffer&          module_rob;

        RenameAndAllocation     next_rename_and_allocation;

        ROBCommit               next_rob_commit;

        bool                    next_bco_valid;

        bool                    next_reset;

    public:
        RegisterAndRename(ReOrderBuffer& rob) noexcept;
        ~RegisterAndRename() noexcept;

        void            NextRenameAndAllocation(RenameAndAllocation bundle) noexcept;

        void            NextROBCommit(ROBCommit bundle) noexcept;

        void            NextBranchCommitOverride(bool bco_valid) noexcept;

        void            NextReset() noexcept;

        RenameResult    CombReadAndRename() const noexcept;

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
        SteppingDFF<uint7_t, DFFResetValue<0b0000001U>> fifo_pos;

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
    private:
        PreAllocatorROB         model_allocator_rob;
        PreAllocatorStoreBuffer model_allocator_storebuffer;

        SteppingDFF<bool>       readyn_sync1;
        SteppingDFF<bool>       readyn_sync2;

        bool                    next_allocation_enable;

        bool                    next_readyn;

        bool                    next_reset;

    private:
        bool        _SignalNotReady() const noexcept;

    public:
        PreAllocator() noexcept;
        ~PreAllocator() noexcept;
        
        void        NextAllocationEnable(bool enable, bool enable_store) noexcept;
        void        NextCommitEnable(bool enable, bool enable_store) noexcept;

        void        NextBranchCommitOverride(bool bco_valid) noexcept;

        void        NextNotReady(bool readyn) noexcept;

        void        NextReset() noexcept;

        bool        CombAllocationEnable() const noexcept;

        bool        CombNotReady() const noexcept;

        void        Reset() noexcept;
        void        Eval() noexcept;
    };



    // Before-Stage DFFs
    class BeforeStageDFFs {
    public:
        using Writeback         = ReOrderBuffer::Writeback;

        using FetchResult       = Fetch::Fetch::FetchResult;

        using BranchPrediction  = Fetch::Fetch::BranchPrediction;

    private:
        SteppingDFF<Writeback, decltype([] (Writeback& obj) {
            obj.enable  = false;
        })>                                         dff_writeback;

        SteppingDFF<FetchResult, decltype([] (FetchResult& obj) {
            obj.valid   = false;
        })>                                         dff_fetch;

        SteppingDFF<BranchPrediction, DFFNoReset>   dff_branch_prediction;

        bool                                        next_bco_valid;

    public:
        BeforeStageDFFs() noexcept;
        ~BeforeStageDFFs() noexcept;

        void                            NextWriteback(Writeback bundle) noexcept;
        void                            NextFetch(Fetch::Fetch::FetchResult bundle) noexcept;
        void                            NextBranchPrediction(Fetch::Fetch::BranchPrediction bundle) noexcept;

        void                            NextBranchCommitOverride(bool bco_valid) noexcept;

        void                            NextReset() noexcept;

        Writeback                       GetLastWriteback() const noexcept;
        Fetch::Fetch::FetchResult       GetLastFetch() const noexcept;
        Fetch::Fetch::BranchPrediction  GetLastBranchPrediction() const noexcept;

        void                            Reset() noexcept;
        void                            Eval() noexcept;
    };



    // Decode AIO
    class Decode {
    public:
        using Writeback     = BeforeStageDFFs::Writeback;

        struct PreIssueMicroCode {
            Global::PC                          pc;

            ReOrderBuffer::Index                src0_rob;
            bool                                src0_ready;
            RegisterValue                       src0_value;

            ReOrderBuffer::Index                src1_rob;
            bool                                src1_ready;
            RegisterValue                       src1_value;

            ReOrderBuffer::Index                dst_rob;

            Immediate                           imm;

            Global::FID                         fid;

            bool                                branch;
            bool                                load;
            bool                                store;

            bool                                pipe_alu;
            bool                                pipe_mul;
            bool                                pipe_mem;
            bool                                pipe_bru;

            ALUCommand                          alu_cmd;
            MULCommand                          mul_cmd;
            MEMCommand                          mem_cmd;
            BRUCommand                          bru_cmd;
            BAGUCommand                         bagu_cmd;
        };

        struct BeforeIssue {
            bool                                valid;

            PreIssueMicroCode                   microcode;
        };

        using ToCommit      = ReOrderBuffer::CommitCandidate;

        struct FromCommit {
            bool                                enable;
            bool                                store;
            Global::FID                         fid;
            RegisterIndex                       dst;
            RegisterValue                       result;
        };

        struct BranchPrediction {
            Fetch::BranchPredictor::PHTEntry    pattern;
            bool                                taken;
            bool                                hit;
            Global::PC                          target;
        };

    private:
        BeforeStageDFFs                 module_input_dffs;

        PreAllocator                    module_preallocator;

        InstructionDecoder              module_idecode;

        InstructionDecoderDFFs          module_idecdffs;

        ReOrderBuffer                   module_rob;

        RegisterAndRename               module_regnrename;

        BeforeIssue                     last_before_issue;
        BranchPrediction                last_branch_prediction;

        bool                            next_reset;

    public:
        Decode() noexcept;
        ~Decode() noexcept;

        void                NextIssueNotReady(bool readyn) noexcept;

        void                NextBranchCommitOverride(bool bco_valid);

        void                NextFetch(Fetch::Fetch::FetchResult bundle) noexcept;
        void                NextBranchPrediction(Fetch::Fetch::BranchPrediction bundle) noexcept;

        void                NextFromCommit(FromCommit bundle) noexcept;

        void                NextWriteback(Writeback bundle) noexcept;

        void                NextReset() noexcept;

        bool                CombNotReady() const noexcept;

        ToCommit            GetLastToCommit() const noexcept;

        BeforeIssue         GetLastBeforeIssue() const noexcept;

        BranchPrediction    GetLastBranchPrediction() const noexcept;

        void                Reset() noexcept;
        void                Eval() noexcept;
    };
}


// Implementation of: class InstructionDecoder
namespace BullsEye::Gemini30F2::Decode {

    InstructionDecoder::InstructionDecoder() noexcept
    { }

    InstructionDecoder::~InstructionDecoder() noexcept
    { }

    InstructionDecoder::Decoded InstructionDecoder::CombDecode(Global::RawInstruction insn, bool valid) const noexcept
    {
        // *NOTICE: Temporary implementation. Further optimzation is required.

        //
        if (!valid)
            return {};

        //
        MIPS32::MIPS32Instruction mips32_insn = insn;

        uint6_t     opcode  = mips32_insn.GetOpcode();
        uint5_t     rs      = mips32_insn.GetRS();
        uint5_t     rt      = mips32_insn.GetRT();
        uint5_t     rd      = mips32_insn.GetRD();
        uint5_t     sa      = mips32_insn.GetShamt();
        uint6_t     func    = mips32_insn.GetFunct();
        uint16_t    iimm    = mips32_insn.GetImmediate();
        uint26_t    jindex  = mips32_insn.GetJumpIndex();

        //
        Decoded decoded;

        //
        bool i_add, i_addi, i_addu, i_addiu, i_sub,  i_slt,  i_sltu,  i_mul;
        bool i_and, i_andi, i_lui,  i_or,    i_ori,  i_xor,  i_xori;
        bool i_sll, i_sllv, i_sra,  i_srav,  i_srl,  i_srlv;
        bool i_beq, i_bne,  i_bgez, i_bgtz,  i_blez, i_bltz;
        bool i_j,   i_jal,  i_jr,   i_jalr;
        bool i_lb,  i_lw,   i_sb,   i_sw;

        //  insn |          opcode   |          func     |         sa      |         rs     |         rt      |       rd      |
        //
        i_add    = opcode == 0b000000 && func == 0b100000 && sa == 0b00000;
        i_addi   = opcode == 0b001000;
        i_addu   = opcode == 0b000000 && func == 0b100001 && sa == 0b00000;
        i_addiu  = opcode == 0b001001;
        i_sub    = opcode == 0b000000 && func == 0b100010 && sa == 0b00000;
        i_slt    = opcode == 0b000000 && func == 0b101010 && sa == 0b00000;
        i_sltu   = opcode == 0b000000 && func == 0b101011 && sa == 0b00000;
        i_mul    = opcode == 0b011100 && func == 0b000010 && sa == 0b00000;

        i_and    = opcode == 0b000000 && func == 0b100100 && sa == 0b00000;
        i_andi   = opcode == 0b001100;
        i_lui    = opcode == 0b001111                                       && rs == 0b00000;
        i_or     = opcode == 0b000000 && func == 0b100101 && sa == 0b00000;
        i_ori    = opcode == 0b001101;
        i_xor    = opcode == 0b000000 && func == 0b100110 && sa == 0b00000;
        i_xori   = opcode == 0b001110;

        i_sllv   = opcode == 0b000000 && func == 0b000100 && sa == 0b00000;
        i_sll    = opcode == 0b000000 && func == 0b000000                   && rs == 0b00000;
        i_srav   = opcode == 0b000000 && func == 0b000111 && sa == 0b00000;
        i_sra    = opcode == 0b000000 && func == 0b000011                   && rs == 0b00000;
        i_srlv   = opcode == 0b000000 && func == 0b000110 && sa == 0b00000;
        i_srl    = opcode == 0b000000 && func == 0b000010                   && rs == 0b00000;

        i_beq    = opcode == 0b000100;
        i_bne    = opcode == 0b000101;
        i_bgez   = opcode == 0b000001                                                        && rt == 0b00001;
        i_bgtz   = opcode == 0b000111                                                        && rt == 0b00000;
        i_blez   = opcode == 0b000110                                                        && rt == 0b00000;
        i_bltz   = opcode == 0b000001                                                        && rt == 0b00000;

        i_j      = opcode == 0b000010;
        i_jal    = opcode == 0b000011;
        i_jr     = opcode == 0b000000 && func == 0b001000 && sa == 0b00000                   && rt == 0b00000 && rd == 0b00000;
        i_jalr   = opcode == 0b000000 && func == 0b001001 && sa == 0b00000                   && rt == 0b00000;

        i_lb     = opcode == 0b100000;
        i_lw     = opcode == 0b100011;
        i_sb     = opcode == 0b101000;
        i_sw     = opcode == 0b101011;

        //
        bool iform_i_1op;
        bool iform_i_1opn;
        bool iform_i_2opn;
        bool iform_r;
        bool iform_j_n;
        bool iform_j_r31;

        iform_i_1op      = i_addi  | i_addiu | i_andi  | i_lui   | i_ori   | i_xori  | i_lb    | i_lw;
        iform_i_1opn     = i_bgez  | i_bgtz  | i_blez  | i_bltz;
        iform_i_2opn     = i_beq   | i_bne   | i_sb    | i_sw;

        iform_r          = i_add   | i_addu  | i_sub   | i_slt   | i_sltu  | i_mul   | i_and   | i_or    | i_xor
                         | i_sllv  | i_sll   | i_srav  | i_sra   | i_srlv  | i_srl   | i_jr    | i_jalr;

        iform_j_n        = i_j;
        iform_j_r31      = i_jal;

        //
        bool iattr_branch;
        bool iattr_load;
        bool iattr_store;

        iattr_branch     = i_beq   | i_bne   | i_bgez  | i_bgtz  | i_blez  | i_bltz
                         | i_j     | i_jal   | i_jr    | i_jalr;
        iattr_load       = i_lb    | i_lw;
        iattr_store      = i_sb    | i_sw;

        //
        decoded.lswidth  = i_lb       ? LSWIDTH_BYTE
                         : i_sb       ? LSWIDTH_BYTE
                         : i_lw       ? LSWIDTH_WORD
                         : i_sw       ? LSWIDTH_WORD
                         :              LSWIDTH_WORD;

        //
        decoded.alu_cmd  = i_add      ? ALU_ADD
                         : i_addi     ? ALU_ADDI
                         : i_addu     ? ALU_ADD
                         : i_addiu    ? ALU_ADDI
                         : i_sub      ? ALU_SUB
                         : i_slt      ? ALU_SLT
                         : i_sltu     ? ALU_SLTU
                         : i_and      ? ALU_AND
                         : i_andi     ? ALU_ANDI
                         : i_or       ? ALU_OR
                         : i_ori      ? ALU_ORI
                         : i_xor      ? ALU_XOR
                         : i_xori     ? ALU_XORI
                         : i_sll      ? ALU_SLL
                         : i_sllv     ? ALU_SLLV
                         : i_sra      ? ALU_SRA
                         : i_srav     ? ALU_SRAV
                         : i_srl      ? ALU_SRL
                         : i_srlv     ? ALU_SRLV
                         : i_lui      ? ALU_LUI
                         :              ALU_NOP;

        //
        decoded.mul_cmd  = i_mul      ? MUL_EN
                         :              MUL_NOP;

        //
        decoded.mem_cmd  = i_lb       ? MEM_LB
                         : i_lw       ? MEM_LW
                         : i_sb       ? MEM_SB
                         : i_sw       ? MEM_SW
                         :              MEM_NOP;

        //
        decoded.bru_cmd  = i_beq      ? BRU_BRANCH_EQ
                         : i_bne      ? BRU_BRANCH_NEQ
                         : i_bgez     ? BRU_BRANCH_GEZ
                         : i_bgtz     ? BRU_BRANCH_GTZ
                         : i_blez     ? BRU_BRANCH_LEZ
                         : i_bltz     ? BRU_BRANCH_LTZ
                         : i_j        ? BRU_JUMP
                         : i_jal      ? BRU_JCALL
                         : i_jr       ? BRU_JUMP
                         : i_jalr     ? BRU_JCALL
                         :              BRU_NOP;

        //
        decoded.bagu_cmd = i_beq     ? BAGU_RLT
                         : i_bne     ? BAGU_RLT
                         : i_bgez    ? BAGU_RLT
                         : i_bgtz    ? BAGU_RLT
                         : i_blez    ? BAGU_RLT
                         : i_bltz    ? BAGU_RLT
                         : i_j       ? BAGU_IMM
                         : i_jal     ? BAGU_IMM
                         : i_jr      ? BAGU_REG
                         : i_jalr    ? BAGU_REG
                         :             BAGU_NOP;

        //
        decoded.pipe_alu = decoded.alu_cmd != ALU_NOP;
        decoded.pipe_mul = decoded.mul_cmd != MUL_NOP;
        decoded.pipe_mem = decoded.mem_cmd != MEM_NOP;
        decoded.pipe_bru = decoded.bru_cmd != BRU_NOP;

        //
        decoded.src0 = iform_i_1op   ? rs
                     : iform_i_1opn  ? rs
                     : iform_i_2opn  ? rs
                     : iform_r       ? rs
                     : iform_j_n     ? uint5_t(0)
                     : iform_j_r31   ? uint5_t(0)
                     :                 uint5_t(0);

        decoded.src1 = iform_i_1op   ? uint5_t(0)
                     : iform_i_1opn  ? uint5_t(0)
                     : iform_i_2opn  ? rt
                     : iform_r       ? rt
                     : iform_j_n     ? uint5_t(0)
                     : iform_j_r31   ? uint5_t(0)
                     :                 uint5_t(0);

        decoded.dst  = iform_i_1op   ? rt
                     : iform_i_1opn  ? uint5_t(0)
                     : iform_i_2opn  ? uint5_t(0)
                     : iform_r       ? rd
                     : iform_j_n     ? uint5_t(0)
                     : iform_j_r31   ? uint5_t(31)
                     :                 uint5_t(0);

        decoded.imm  = iform_i_1op   ? uint26_t(iimm )
                     : iform_i_1opn  ? uint26_t(iimm )
                     : iform_i_2opn  ? uint26_t(iimm )
                     : iform_r       ? uint26_t(sa   )
                     : iform_j_n     ? jindex
                     : iform_j_r31   ? jindex
                     :                 uint26_t(0);

        //
        decoded.branch  = iattr_branch;
        decoded.load    = iattr_load;
        decoded.store   = iattr_store;

        //
        return decoded;
    }
}


// Implementation of: class InstructionDecoderDFFs
namespace BullsEye::Gemini30F2::Decode {
    //
    // Global::PC                      last_pc;
    // Global::FID                     last_fid;
    // InstructionDecoder::Decoded     last_decoded;
    // Fetch::Fetch::BranchPrediction  last_branch_prediction;
    // bool                            last_allocation_enable;
    //
    // Global::PC                      next_pc;
    // Global::FID                     next_fid;
    // InstructionDecoder::Decoded     next_decoded;
    // Fetch::Fetch::BranchPrediction  next_branch_prediction;
    // bool                            next_allocation_enable;
    //
    // bool                            next_bco_valid;
    //
    // bool                            next_reset;
    //

    InstructionDecoderDFFs::InstructionDecoderDFFs() noexcept
        : last_pc                   ()
        , last_fid                  ()
        , last_decoded              ()
        , last_branch_prediction    ()
        , last_allocation_enable    (false)
        , next_pc                   ()
        , next_fid                  ()
        , next_decoded              ()
        , next_branch_prediction    ()
        , next_allocation_enable    (false)
        , next_bco_valid            (false)
        , next_reset                (false)
    { }

    InstructionDecoderDFFs::~InstructionDecoderDFFs() noexcept
    { }

    inline void InstructionDecoderDFFs::NextPC(Global::PC pc) noexcept
    {
        next_pc = pc;
    }

    inline void InstructionDecoderDFFs::NextFID(Global::FID fid) noexcept
    {
        next_fid = fid;
    }

    inline void InstructionDecoderDFFs::NextDecoded(InstructionDecoder::Decoded bundle) noexcept
    {
        next_decoded = bundle;
    }

    inline void InstructionDecoderDFFs::NextBranchPrediction(Fetch::Fetch::BranchPrediction bundle) noexcept
    {
        next_branch_prediction = bundle;
    }

    inline void InstructionDecoderDFFs::NextAllocationEnable(bool enable) noexcept
    {
        next_allocation_enable = enable;
    }

    inline void InstructionDecoderDFFs::NextBranchCommitOverride(bool bco_valid) noexcept
    {
        next_bco_valid = bco_valid;
    }

    inline void InstructionDecoderDFFs::NextReset() noexcept
    {
        next_reset = true;
    }

    inline Global::PC InstructionDecoderDFFs::GetLastPC() const noexcept
    {
        return last_pc;
    }

    inline Global::FID InstructionDecoderDFFs::GetLastFID() const noexcept
    {
        return last_fid;
    }

    inline InstructionDecoder::Decoded InstructionDecoderDFFs::GetLastDecoded() const noexcept
    {
        return last_decoded;
    }

    inline Fetch::Fetch::BranchPrediction InstructionDecoderDFFs::GetLastBranchPrediction() const noexcept
    {
        return last_branch_prediction;
    }

    inline bool InstructionDecoderDFFs::GetLastAllocationEnable() const noexcept
    {
        return last_allocation_enable;
    }

    void InstructionDecoderDFFs::Reset() noexcept
    {
        last_allocation_enable = false;

        next_reset             = false;
    }

    void InstructionDecoderDFFs::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }

        //
        last_pc                 = next_pc;
        last_fid                = next_fid;
        last_decoded            = next_decoded;
        last_branch_prediction  = next_branch_prediction;

        last_allocation_enable  = next_bco_valid ? false : next_allocation_enable;
    }
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

    inline ReOrderBuffer::Index ReOrderBuffer::GetLastROBNext() const noexcept
    {
        return Index(wptr.Get() & 0x0F);
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

    inline void RegisterAliasTable::NextROBCommit(ROBCommit writeback) noexcept
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


// Implementation of: class RegisterAndRename
namespace BullsEye::Gemini30F2::Decode {
    //
    // RegisterFile            module_regfile;
    //
    // RegisterAliasTable      module_rat;
    //
    // ReOrderBuffer&          module_rob;
    //
    // RenameAndAllocation     next_rename_and_allocation;
    //
    // ROBCommit               next_rob_commit;
    //
    // bool                    next_bco_valid;
    //
    // bool                    next_reset;
    //

    RegisterAndRename::RegisterAndRename(ReOrderBuffer& rob) noexcept
        : module_regfile            ()
        , module_rat                ()
        , module_rob                (rob)
        , next_rename_and_allocation{ .enable = false }
        , next_rob_commit           { .enable = false }
        , next_bco_valid            (false)
        , next_reset                (false)
    { }

    RegisterAndRename::~RegisterAndRename() noexcept
    { }

    inline void RegisterAndRename::NextRenameAndAllocation(RenameAndAllocation bundle) noexcept
    {
        next_rename_and_allocation = bundle;
    }

    inline void RegisterAndRename::NextROBCommit(ROBCommit bundle) noexcept
    {
        next_rob_commit = bundle;
    }

    inline void RegisterAndRename::NextBranchCommitOverride(bool bco_valid) noexcept
    {
        next_bco_valid = bco_valid;
    }

    inline void RegisterAndRename::NextReset() noexcept
    {
        next_reset = true;
    }

    RegisterAndRename::RenameResult RegisterAndRename::CombReadAndRename() const noexcept
    {
        RegisterValue regfs_data0 = module_regfile.CombReadPortA(next_rename_and_allocation.src0);
        RegisterValue regfs_data1 = module_regfile.CombReadPortB(next_rename_and_allocation.src1);

        RegisterAliasTable::ReadResult rat_src0 = module_rat.CombReadPortA(next_rename_and_allocation.src0);
        RegisterAliasTable::ReadResult rat_src1 = module_rat.CombReadPortB(next_rename_and_allocation.src1);

        ReOrderBuffer::ReadValueResult rob_src0 = module_rob.CombReadValuePortA(rat_src0.rob);
        ReOrderBuffer::ReadValueResult rob_src1 = module_rob.CombReadValuePortB(rat_src1.rob);

        return RenameResult {
            .src0_rob   = rat_src0.rob,
            .src0_ready = rat_src0.valid ? rob_src0.ready : true,
            .src0_value = rat_src0.valid ? rob_src0.value : regfs_data0,

            .src1_rob   = rat_src1.rob,
            .src1_ready = rat_src1.valid ? rob_src1.ready : true,
            .src1_value = rat_src1.valid ? rob_src1.value : regfs_data1
        };
    }

    void RegisterAndRename::Reset() noexcept
    {
        module_rat.Reset();

        next_rename_and_allocation.enable = false;
        next_rob_commit.enable            = false;

        next_bco_valid  = false;

        next_reset      = false;
    }

    void RegisterAndRename::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }

        //
        module_rat.NextAllocation({
            .enable = next_rename_and_allocation.enable,
            .addr   = next_rename_and_allocation.dst,
            .fid    = next_rename_and_allocation.fid,
            .rob    = next_rename_and_allocation.rob
        });

        //
        module_regfile.NextWrite(
            next_rob_commit.enable,
            next_rob_commit.addr,
            next_rob_commit.data
        );

        module_rat.NextROBCommit({
            .enable = next_rob_commit.enable,
            .addr   = next_rob_commit.addr,
            .fid    = next_rob_commit.fid
        });

        //
        module_rat.NextBranchCommitOverride(next_bco_valid);

        //
        module_regfile.Eval();
        module_rat.Eval();
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

    inline bool PreAllocatorStoreBuffer::_SignalNotReady() const noexcept
    {
        return fifo_pos.Get() & 0x7C;
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
        return _SignalNotReady();
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


// Implementation of: class PreAllocator
namespace BullsEye::Gemini30F2::Decode {
    //
    // PreAllocatorROB         model_allocator_rob;
    // PreAllocatorStoreBuffer model_allocator_storebuffer;
    //
    // SteppingDFF<bool>       readyn_sync1;
    // SteppingDFF<bool>       readyn_sync2;
    //
    // bool                    next_allocation_enable;
    //
    // bool                    next_readyn;
    //
    // bool                    next_reset;
    //

    PreAllocator::PreAllocator() noexcept
        : model_allocator_rob           ()
        , model_allocator_storebuffer   ()
        , readyn_sync1                  ()
        , readyn_sync2                  ()
        , next_allocation_enable        (false)
        , next_readyn                   (false)
        , next_reset                    (false)
    { }

    PreAllocator::~PreAllocator() noexcept
    { }

    inline bool PreAllocator::_SignalNotReady() const noexcept
    {
        return model_allocator_rob.CombNotReady() || model_allocator_storebuffer.CombNotReady() || next_readyn;
    }

    inline void PreAllocator::NextAllocationEnable(bool enable, bool enable_store) noexcept
    {
        model_allocator_rob         .NextAllocationEnable(enable);
        model_allocator_storebuffer .NextAllocationEnable(enable, enable_store);
    }

    inline void PreAllocator::NextCommitEnable(bool enable, bool enable_store) noexcept
    {
        model_allocator_rob         .NextCommitEnable(enable);
        model_allocator_storebuffer .NextCommitEnable(enable, enable_store);
    }

    inline void PreAllocator::NextBranchCommitOverride(bool bco_valid) noexcept
    {
        model_allocator_rob         .NextBranchCommitOverride(bco_valid);
        model_allocator_storebuffer .NextBranchCommitOverride(bco_valid);
    }

    inline void PreAllocator::NextNotReady(bool readyn) noexcept
    {
        next_readyn = readyn;
    }

    inline void PreAllocator::NextReset() noexcept
    {
        next_reset = true;
    }

    inline bool PreAllocator::CombAllocationEnable() const noexcept
    {
        return next_allocation_enable && !readyn_sync2.Get();
    }

    inline bool PreAllocator::CombNotReady() const noexcept
    {
        return _SignalNotReady();
    }

    void PreAllocator::Reset() noexcept
    {
        model_allocator_rob         .Reset();
        model_allocator_storebuffer .Reset();

        readyn_sync1.Reset();
        readyn_sync2.Reset();

        next_allocation_enable  = false;

        next_readyn = false;

        next_reset = false;
    }

    void PreAllocator::Eval() noexcept
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

        //
        model_allocator_rob.Eval();
        model_allocator_storebuffer.Eval();

        readyn_sync1.Eval();
        readyn_sync2.Eval();
    }
}


// Implementation of: class BeforeStageDFFs
namespace BullsEye::Gemini30F2::Decode {
    //
    // SteppingDFF<Writeback, decltype([] (Writeback& obj) {
    //     obj.enable  = false;
    // })>                                         dff_writeback;
    //
    // SteppingDFF<FetchResult, decltype([] (FetchResult& obj) {
    //     obj.valid   = false;
    // })>                                         dff_fetch;
    //
    // SteppingDFF<BranchPrediction, DFFNoReset>   dff_branch_prediction;
    //
    // bool                                        next_bco_valid;
    //

    BeforeStageDFFs::BeforeStageDFFs() noexcept
        : dff_writeback             ()
        , dff_fetch                 ()
        , dff_branch_prediction     ()
        , next_bco_valid            (false)
    { }

    BeforeStageDFFs::~BeforeStageDFFs() noexcept
    { }

    inline void BeforeStageDFFs::NextWriteback(Writeback bundle) noexcept
    {
        dff_writeback.Next(bundle);
    }

    inline void BeforeStageDFFs::NextFetch(Fetch::Fetch::FetchResult bundle) noexcept
    {
        dff_fetch.Next(bundle);
    }

    inline void BeforeStageDFFs::NextBranchPrediction(Fetch::Fetch::BranchPrediction bundle) noexcept
    {
        dff_branch_prediction.Next(bundle);
    }

    inline void BeforeStageDFFs::NextBranchCommitOverride(bool bco_valid) noexcept
    {
        next_bco_valid = bco_valid;
    }

    inline void BeforeStageDFFs::NextReset() noexcept
    {
        dff_writeback           .NextReset();
        dff_fetch               .NextReset();
        dff_branch_prediction   .NextReset();
    }

    inline BeforeStageDFFs::Writeback BeforeStageDFFs::GetLastWriteback() const noexcept
    {
        return dff_writeback.Get();
    }

    inline Fetch::Fetch::FetchResult BeforeStageDFFs::GetLastFetch() const noexcept
    {
        return dff_fetch.Get();
    }

    inline Fetch::Fetch::BranchPrediction BeforeStageDFFs::GetLastBranchPrediction() const noexcept
    {
        return dff_branch_prediction.Get();
    }

    void BeforeStageDFFs::Reset() noexcept
    {
        dff_writeback           .Reset();
        dff_fetch               .Reset();
        dff_branch_prediction   .Reset();
    }

    void BeforeStageDFFs::Eval() noexcept
    {
        //
        if (next_bco_valid)
            dff_fetch.GetNext().valid = false;

        //
        dff_writeback           .Eval();
        dff_fetch               .Eval();
        dff_branch_prediction   .Eval();
    }
}


// Implementation of: class Decode
namespace BullsEye::Gemini30F2::Decode {
    //
    // BeforeStageDFFs                 module_input_dffs;
    //
    // PreAllocator                    module_preallocator;
    //
    // InstructionDecoder              module_idecode;
    //
    // InstructionDecoderDFFs          module_idecdffs;
    //
    // ReOrderBuffer                   module_rob;
    //
    // RegisterAndRename               module_regnrename;
    //
    // bool                            next_reset;
    //

    Decode::Decode() noexcept
        : module_input_dffs         ()
        , module_preallocator       ()
        , module_idecode            ()
        , module_idecdffs           ()
        , module_rob                ()
        , module_regnrename         (module_rob)
        , last_before_issue         ()
        , last_branch_prediction    ()
        , next_reset                (false)
    { }

    Decode::~Decode() noexcept
    { }

    inline void Decode::NextIssueNotReady(bool issue_readyn) noexcept
    {
        module_preallocator.NextNotReady(issue_readyn);
    }

    inline void Decode::NextBranchCommitOverride(bool bco_valid) noexcept
    {
        module_input_dffs   .NextBranchCommitOverride(bco_valid);
        module_preallocator .NextBranchCommitOverride(bco_valid);
        module_idecdffs     .NextBranchCommitOverride(bco_valid);
        module_rob          .NextBranchCommitOverride(bco_valid);
        module_regnrename   .NextBranchCommitOverride(bco_valid);
    }

    inline void Decode::NextFetch(Fetch::Fetch::FetchResult bundle) noexcept
    {
        //
        module_input_dffs.NextFetch(bundle);

        //
        
    }

    inline void Decode::NextBranchPrediction(Fetch::Fetch::BranchPrediction bundle) noexcept
    {
        module_input_dffs.NextBranchPrediction(bundle);
    }

    inline void Decode::NextFromCommit(FromCommit bundle) noexcept
    {
        module_preallocator.NextCommitEnable(
            bundle.enable, 
            bundle.store
        );

        module_rob.NextCommitEnable(
            bundle.enable
        );

        module_regnrename.NextROBCommit({
            .enable = bundle.enable,
            .addr   = bundle.dst,
            .fid    = bundle.fid,
            .data   = bundle.result
        });
    }

    inline void Decode::NextWriteback(Writeback bundle) noexcept
    {
        module_input_dffs.NextWriteback(bundle);
    }

    inline void Decode::NextReset() noexcept
    {
        next_reset = true;
    }

    inline bool Decode::CombNotReady() const noexcept
    {
        return module_preallocator.CombNotReady();
    }

    inline Decode::ToCommit Decode::GetLastToCommit() const noexcept
    {
        return module_rob.GetLastCommit();
    }

    inline Decode::BeforeIssue Decode::GetLastBeforeIssue() const noexcept
    {
        // *NOTICE: Do LastBeforeIssue emulations in Eval() function.
        return last_before_issue;
    }

    inline Decode::BranchPrediction Decode::GetLastBranchPrediction() const noexcept
    {
        // *NOTICE: Do LastBranchPrediction emulations in Eval() function.
        return last_branch_prediction;
    }

    void Decode::Reset() noexcept
    {
        module_input_dffs.Reset();
        module_preallocator.Reset();
        module_idecdffs.Reset();
        module_rob.Reset();
        module_regnrename.Reset();

        next_reset = false;
    }

    void Decode::Eval() noexcept
    {
        //
        if (next_reset)
        {
            Reset();
            return;
        }


        //
        Writeback                       idffs_writeback         = module_input_dffs.GetLastWriteback();
        Fetch::Fetch::FetchResult       idffs_fetch             = module_input_dffs.GetLastFetch();
        Fetch::Fetch::BranchPrediction  idffs_branch_prediction = module_input_dffs.GetLastBranchPrediction();

        //
        module_rob.NextWriteback(idffs_writeback);

        //
        InstructionDecoder::Decoded idec = module_idecode.CombDecode(
            idffs_fetch.data,
            idffs_fetch.valid
        );

        module_preallocator.NextAllocationEnable(
            idffs_fetch.valid,
            idec.store
        );

        //
        module_idecdffs.NextPC(idffs_fetch.pc);
        module_idecdffs.NextFID(idffs_fetch.fid);
        module_idecdffs.NextDecoded(idec);
        module_idecdffs.NextBranchPrediction(idffs_branch_prediction);
        module_idecdffs.NextAllocationEnable(module_preallocator.CombAllocationEnable());


        //
        Global::PC                      idecdffs_pc                 = module_idecdffs.GetLastPC();
        Global::FID                     idecdffs_fid                = module_idecdffs.GetLastFID();
        InstructionDecoder::Decoded     idecdffs_decoded            = module_idecdffs.GetLastDecoded();
        Fetch::Fetch::BranchPrediction  idecdffs_branch_prediction  = module_idecdffs.GetLastBranchPrediction();
        bool                            idecdffs_allocation_enable  = module_idecdffs.GetLastAllocationEnable();

        //
        module_rob.NextAllocation({
            .enable     = idecdffs_allocation_enable,
            .pc         = idecdffs_pc,
            .dst        = idecdffs_decoded.dst,
            .fid        = idecdffs_fid,
            .load       = idecdffs_decoded.load,
            .store      = idecdffs_decoded.store,
            .lswidth    = idecdffs_decoded.lswidth
        });

        //
        module_regnrename.NextRenameAndAllocation({
            .enable     = idecdffs_allocation_enable,
            .fid        = idecdffs_fid,
            .rob        = module_rob.GetLastROBNext(),
            .src0       = idecdffs_decoded.src0,
            .src1       = idecdffs_decoded.src1,
            .dst        = idecdffs_decoded.dst
        });


        //
        RegisterAndRename::RenameResult regnrename = module_regnrename.CombReadAndRename();


        //
        last_before_issue.valid         = idecdffs_allocation_enable;

        last_before_issue.microcode.pc          = idecdffs_pc;
        last_before_issue.microcode.fid         = idecdffs_fid;

        last_before_issue.microcode.src0_rob    = regnrename.src0_rob;
        last_before_issue.microcode.src0_ready  = regnrename.src0_ready;
        last_before_issue.microcode.src0_value  = regnrename.src0_value;

        last_before_issue.microcode.src1_rob    = regnrename.src1_rob;
        last_before_issue.microcode.src1_ready  = regnrename.src1_ready;
        last_before_issue.microcode.src1_value  = regnrename.src1_value;

        last_before_issue.microcode.imm         = idecdffs_decoded.imm;
        last_before_issue.microcode.branch      = idecdffs_decoded.branch;
        last_before_issue.microcode.load        = idecdffs_decoded.load;
        last_before_issue.microcode.store       = idecdffs_decoded.store;

        last_before_issue.microcode.pipe_alu    = idecdffs_decoded.pipe_alu;
        last_before_issue.microcode.pipe_mul    = idecdffs_decoded.pipe_mul;
        last_before_issue.microcode.pipe_mem    = idecdffs_decoded.pipe_mem;
        last_before_issue.microcode.pipe_bru    = idecdffs_decoded.pipe_bru;

        last_before_issue.microcode.alu_cmd     = idecdffs_decoded.alu_cmd;
        last_before_issue.microcode.mul_cmd     = idecdffs_decoded.mul_cmd;
        last_before_issue.microcode.mem_cmd     = idecdffs_decoded.mem_cmd;
        last_before_issue.microcode.bru_cmd     = idecdffs_decoded.bru_cmd;
        last_before_issue.microcode.bagu_cmd    = idecdffs_decoded.bagu_cmd;

        //
        last_branch_prediction.pattern  = idecdffs_branch_prediction.pattern;
        last_branch_prediction.taken    = idecdffs_branch_prediction.taken;
        last_branch_prediction.hit      = idecdffs_branch_prediction.hit;
        last_branch_prediction.target   = idecdffs_branch_prediction.target;


        //
        module_input_dffs.Eval();
        module_preallocator.Eval();
        module_idecdffs.Eval();
        module_rob.Eval();
        module_regnrename.Eval();
    }
}
