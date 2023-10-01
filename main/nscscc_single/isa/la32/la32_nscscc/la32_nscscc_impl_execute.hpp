#pragma once
//
// LA32R (NSCSCC) ISA Emulator (Jasse)
//
// LA32R-NSCSCC, bahaviour functions
//

#include "la32_nscscc_def_execute.hpp"
#include "la32_nscscc_def_event.hpp"


#define RDi                     (insn.GetRD())
#define RJi                     (insn.GetRJ())
#define RKi                     (insn.GetRK())
#define RAi                     (insn.GetRA())

#define GPR(i)                  (inst.Arch().GPRs()[i])


#define RD                      (GPR(RDi))
#define RJ                      (GPR(RJi))
#define RK                      (GPR(RKi))
#define RA                      (GPR(RAi))

#define UI8                     (insn.GetImm8())
#define SI8                     SEXT32_IMM8(UI8)

#define UI12                    (insn.GetImm12())
#define SI12                    SEXT32_IMM12(UI12)

#define UI14                    (insn.GetImm14())
#define SI14                    SEXT32_IMM14(UI14)

#define UI16                    (insn.GetImm16())
#define SI16                    SEXT32_IMM16(UI16)

#define UI21                    (insn.GetImm21())
#define SI21                    SEXT32_IMM21(UI21)

#define UI26                    (insn.GetImm26())
#define SI26                    SEXT32_IMM26(UI26)

#define UI20                    (insn.GetExImm20())
#define SI20                    SEXT32_IMM20(UI20)

#define UI5                     (insn.GetExImm5())
#define SI5                     SEXT32_IMM5(UI5)

#define INSTANCE                inst
#define INSTRUCTION             insn

#define PC                      INSTANCE.Arch().PC()


#define GPR_src_value(ordinal)  gpr_src_value##ordinal
#define GPR_src_trace(ordinal)  gpr_src_trace##ordinal

#define GPR_dst_value           gpr_dst_value
#define GPR_dst_trace           gpr_dst_trace

#define MEM_src_trace           memory_src_trace

#define TRACE_REF               trace_ref
#define TRACE_CONTENT           trace_content


#define trace_fetch \
    { \
        TRACE_CONTENT.SetTracedFetch(*TRACE_REF, INSTANCE.GetLastFetchTrace()); \
    }


#define trace_gpr_0src \
    { }

#define trace_gpr_1src \
    { \
        TRACE_CONTENT.SetTracedFirstOperand(*TRACE_REF, GPR_src_trace(0)); \
    }

#define trace_gpr_2src \
    { \
        TRACE_CONTENT.SetTracedFirstOperand (*TRACE_REF, GPR_src_trace(0)); \
        TRACE_CONTENT.SetTracedSecondOperand(*TRACE_REF, GPR_src_trace(1)); \
    }

#define trace_gpr_memload \
    { \
        TRACE_CONTENT.SetTracedFirstOperand (*TRACE_REF, GPR_src_trace(0)); \
        TRACE_CONTENT.SetTracedSecondOperand(*TRACE_REF, MEM_src_trace); \
    }

#define trace_gpr_memstore \
    trace_gpr_2src


#define read_GPR_src(ordinal, last, index) \
    arch32_t                    GPR_src_value(ordinal); \
    LA32TraceEntity::Reference  GPR_src_trace(ordinal); \
    { \
        /*Normal GPR read*/ \
        GPR_src_value(ordinal) = GPR(index); \
        \
        /*Traced Instruction GPR Pre-Read Event*/ \
        LA32TracedInstructionGPRReadEvent preEvent \
            (INSTANCE, PC, INSTRUCTION, index, GPR_src_value(ordinal), ordinal, last); \
        if (preEvent.Fire().IsCancelled()) \
            return { LA32ExecStatus::EXEC_EMULATION_CANCELLED, ECANCELED }; \
        \
        unsigned int real_index = preEvent.GetIndex(); \
        \
        /*GPR redirect on index modified*/ \
        if (preEvent.IsIndexModified() && !preEvent.IsValueModified()) \
            GPR_src_value(ordinal) = GPR(real_index); \
        else \
            GPR_src_value(ordinal) = preEvent.GetValue(); \
        \
        /*Traced Instruction GPR Post-Read Event*/ \
        LA32TracedInstructionGPRPostReadEvent postEvent \
            (INSTANCE, PC, INSTRUCTION, real_index, GPR_src_value(ordinal), ordinal, last); \
        postEvent.Fire(); \
        \
        /*Generate GPR source trace (If GPR tracer enabled)*/ \
        if (INSTANCE.IsTraceEnabled() && INSTANCE.Tracers().HasGPRTracer()) \
        { \
            if (preEvent.IsValueModified()) \
                GPR_src_trace(ordinal) = preEvent.GetValueTrace(); \
            else \
                GPR_src_trace(ordinal) = INSTANCE.Tracers().GetGPRTracer()->Get(real_index).Get(); \
        } \
    }


#define write_GPR_dst(index, trace_action) \
    { \
        /*Traced Instruction GPR Pre-Modify Event*/ \
        LA32TracedInstructionGPRPreModifyEvent preEvent \
            (INSTANCE, PC, INSTRUCTION, index, GPR(index), GPR_dst_value); \
        if (preEvent.Fire().IsCancelled()) \
            return { LA32ExecStatus::EXEC_EMULATION_CANCELLED, ECANCELED }; \
        \
        unsigned int real_index = preEvent.GetIndex(); \
        \
        GPR_dst_value = preEvent.GetNewValue(); \
        \
        /*Traced Instruction GPR Post-Modify Event*/ \
        LA32TracedInstructionGPRPostModifyEvent postEvent \
            (INSTANCE, PC, INSTRUCTION, real_index, preEvent.GetOldValue(), GPR_dst_value); \
        postEvent.Fire(); \
        \
        /*Generate GPR destination trace (If GPR tracer enabled)*/ \
        if (INSTANCE.IsTraceEnabled() && INSTANCE.Tracers().HasGPRTracer()) \
        { \
            if (preEvent.IsNewValueModified()) \
                INSTANCE.Tracers().GetGPRTracer()->Get(real_index).Append(preEvent.GetNewValueTrace()); \
            else \
            { \
                LA32TraceEntity::Reference TRACE_REF = INSTANCE.TracePool().Acquire(); \
                if (TRACE_REF.IsValid()) \
                { \
                    LA32TracedInstructionExecution& TRACE_CONTENT \
                        = TRACE_REF->SetContentType(LA32TraceContentLegacyType::INSTRUCTION_EXECUTION); \
                    TRACE_CONTENT.pc    = PC; \
                    TRACE_CONTENT.value = GPR_dst_value; \
                    TRACE_CONTENT.insn  = INSTRUCTION; \
                    trace_fetch; \
                    trace_action; \
                } \
                INSTANCE.Tracers().GetGPRTracer()->Get(real_index).Append(TRACE_REF); \
            } \
        } \
        \
        /*Write GPR*/ \
        GPR(index) = GPR_dst_value; \
    }



#define traced_memory_load(width, sext) \
    LA32TraceEntity::Reference MEM_src_trace; \
    { \
        addr_t          real_address    = GPR_src_value(0) + SI12; \
        LA32MOPWidth    real_width      = MOPW_##width; \
        \
        /*LA32 Traced Memory Pre-Load Event*/ \
        LA32TracedMemoryPreLoadEvent preEvent \
            (INSTANCE, PC, INSTRUCTION, real_address, real_width); \
        if (preEvent.Fire().IsCancelled()) \
            return { LA32ExecStatus::EXEC_EMULATION_CANCELLED, ECANCELED }; \
        \
        real_address = preEvent.GetAddress(); \
        real_width   = preEvent.GetWidth(); \
        \
        if (preEvent.IsAddressModified()) \
            GPR_src_trace(0) = preEvent.GetAddressTrace(); \
        \
        /*Memory load*/ \
        memdata_t data; \
        LA32MOPOutcome mopoutcome = INSTANCE.Memory()->ReadData(real_address, real_width, &data); \
        switch (mopoutcome.status) \
        { \
            case LA32MOPStatus::MOP_SUCCESS:            break; \
            case LA32MOPStatus::MOP_ACCESS_FAULT:       return { LA32ExecStatus::EXEC_MEMORY_ACCESS_FAULT, mopoutcome.error }; \
            case LA32MOPStatus::MOP_ADDRESS_MISALIGNED: return { LA32ExecStatus::EXEC_MEMORY_ADDRESS_MISALIGNED, mopoutcome.error }; \
            case LA32MOPStatus::MOP_DEVICE_ERROR:       return { LA32ExecStatus::EXEC_MEMORY_DEVICE_ERROR, mopoutcome.error }; \
            [[unlikely]] default:                       SHOULD_NOT_REACH_HERE; \
        } \
        \
        /*LA32 Traced Memory Pre-Post-Load Event Base*/ \
        LA32TracedMemoryPrePostLoadEvent prePostEvent \
            (INSTANCE, PC, INSTRUCTION, real_address, real_width, data); \
        if (prePostEvent.Fire().IsCancelled()) \
            return { LA32ExecStatus::EXEC_EMULATION_CANCELLED, ECANCELED }; \
        \
        data = prePostEvent.GetData(); \
        GPR_dst_value = sext##32_##width(data); \
        \
        /*LA32 Traced Memory Post-Post-Load Event Base*/ \
        LA32TracedMemoryPostPostLoadEvent postPostEvent \
            (INSTANCE, PC, INSTRUCTION, real_address, real_width, GPR_dst_value); \
        postPostEvent.Fire(); \
        \
        /*Trace and redirect memory data source (Traced as second operand)*/ \
        if (INSTANCE.IsTraceEnabled()) \
        { \
            if (prePostEvent.IsDataModified()) \
                MEM_src_trace = prePostEvent.GetDataTrace(); \
            else if (INSTANCE.Tracers().HasMemoryTracer()) \
            { \
                auto mem_trace = INSTANCE.Tracers().GetMemoryTracer()->Get(real_address); \
                if (mem_trace) \
                    MEM_src_trace = mem_trace->get().Get(); \
            } \
        } \
    }


#define traced_memory_store(width) \
    { \
        addr_t          real_address    = GPR_src_value(0) + SI12; \
        LA32MOPWidth    real_width      = MOPW_##width; \
        memdata_t       real_data; \
        \
        real_data.data32 = GPR_src_value(1); \
        \
        /*LA32 Traced Memory Pre-Store Event*/ \
        LA32TracedMemoryPreStoreEvent preEvent \
            (INSTANCE, PC, INSTRUCTION, real_address, real_width, real_data); \
        if (preEvent.Fire().IsCancelled()) \
            return { LA32ExecStatus::EXEC_EMULATION_CANCELLED, ECANCELED }; \
        \
        real_address = preEvent.GetAddress(); \
        real_width   = preEvent.GetWidth(); \
        real_data    = preEvent.GetData(); \
        \
        if (preEvent.IsAddressModified()) \
            GPR_src_trace(0) = preEvent.GetAddressTrace(); \
        \
        if (preEvent.IsDataModified()) \
            GPR_src_trace(1) = preEvent.GetDataTrace(); \
        \
        /*Memory store*/ \
        LA32MOPOutcome mopoutcome = INSTANCE.Memory()->WriteData(real_address, real_width, real_data); \
        switch (mopoutcome.status) \
        { \
            case LA32MOPStatus::MOP_SUCCESS:            break; \
            case LA32MOPStatus::MOP_ACCESS_FAULT:       return { LA32ExecStatus::EXEC_MEMORY_ACCESS_FAULT, mopoutcome.error }; \
            case LA32MOPStatus::MOP_ADDRESS_MISALIGNED: return { LA32ExecStatus::EXEC_MEMORY_ADDRESS_MISALIGNED, mopoutcome.error }; \
            case LA32MOPStatus::MOP_DEVICE_ERROR:       return { LA32ExecStatus::EXEC_MEMORY_DEVICE_ERROR, mopoutcome.error }; \
            [[unlikely]] default:                       SHOULD_NOT_REACH_HERE; \
        } \
        \
        /*LA32 Traced Memory Post-Store Event*/ \
        LA32TracedMemoryPostStoreEvent postEvent \
            (INSTANCE, PC, INSTRUCTION, real_address, real_width, real_data); \
        postEvent.Fire(); \
        \
        /*Generate memory destination trace (If memory tracer enabled)*/ \
        if (INSTANCE.IsTraceEnabled() && INSTANCE.Tracers().HasMemoryTracer()) \
        { \
            LA32TraceEntity::Reference TRACE_REF = INSTANCE.TracePool().Acquire(); \
            if (TRACE_REF.IsValid()) \
            { \
                LA32TracedInstructionExecution& TRACE_CONTENT \
                    = TRACE_REF->SetContentType(LA32TraceContentLegacyType::INSTRUCTION_EXECUTION); \
                TRACE_CONTENT.pc    = PC; \
                TRACE_CONTENT.value = real_data.data32; \
                TRACE_CONTENT.insn  = INSTRUCTION; \
                trace_fetch; \
                trace_gpr_memstore; \
            } \
            if (INSTANCE.Tracers().GetMemoryTracer()->CheckBound(real_address)) \
                INSTANCE.Tracers().GetMemoryTracer()->Acquire(real_address).Append(TRACE_REF); \
        } \
    }



#define traced_memory_load_1r(src0_action, width, sext, dst_action) \
    { \
        src0_action; \
        arch32_t GPR_dst_value; \
        traced_memory_load(width, sext); \
        dst_action; \
        return { LA32ExecStatus::EXEC_SEQUENTIAL }; \
    }

#define traced_memory_load_norm1r(width, sext) \
    traced_memory_load_1r( \
        read_GPR_src(0, true,  RJi), \
        width, \
        sext, \
        write_GPR_dst(RDi, trace_gpr_memload))


#define traced_memory_store_2r(src0_action, src1_action, width) \
    { \
        src0_action; \
        src1_action; \
        traced_memory_store(width); \
        return { LA32ExecStatus::EXEC_SEQUENTIAL }; \
    }

#define traced_memory_store_norm2r(width) \
    traced_memory_store_2r( \
        read_GPR_src(0, false, RJi), \
        read_GPR_src(1, true , RDi), \
        width)


#define traced_arithmetic_2r(src0_action, src1_action, expr, dst_action) \
    { \
        src0_action; \
        src1_action; \
        arch32_t GPR_dst_value; \
        expr; \
        dst_action; \
        return { LA32ExecStatus::EXEC_SEQUENTIAL }; \
    }

#define traced_arithmetic_norm2r(expr) \
    traced_arithmetic_2r( \
        read_GPR_src(0, false, RJi), \
        read_GPR_src(1, true , RKi), \
        expr, \
        write_GPR_dst(RDi, trace_gpr_2src))


#define traced_arithmetic_1r(src0_action, expr, dst_action) \
    { \
        src0_action; \
        arch32_t GPR_dst_value; \
        expr; \
        dst_action; \
        return { LA32ExecStatus::EXEC_SEQUENTIAL }; \
    }

#define traced_arithmetic_norm1r(expr) \
    traced_arithmetic_1r( \
        read_GPR_src(0, true,  RJi), \
        expr, \
        write_GPR_dst(RDi, trace_gpr_1src))


#define traced_arithmetic_0r(expr, dst_action) \
    { \
        arch32_t GPR_dst_value; \
        expr; \
        dst_action; \
        return { LA32ExecStatus::EXEC_SEQUENTIAL }; \
    }

#define traced_arithmetic_norm0r(expr) \
    traced_arithmetic_0r( \
        expr, \
        write_GPR_dst(RDi, trace_gpr_0src))


#define traced_branch_2r(src0_action, src1_action, condition, pc_target) \
    { \
        src0_action; \
        src1_action; \
        INSTANCE.SetBranchTarget(condition, pc_target); \
        return { LA32ExecStatus::EXEC_BRANCH }; \
    }

#define traced_branch_norm2r(condition, pc_target) \
    traced_branch_2r( \
        read_GPR_src(0, false, RJi), \
        read_GPR_src(1, true , RDi), \
        condition, \
        pc_target)


#define traced_branch_0r(condition, pc_target) \
    { \
        INSTANCE.SetBranchTarget(condition, pc_target); \
        return { LA32ExecStatus::EXEC_BRANCH }; \
    }

#define traced_branch_norm0r(condition, pc_target) \
    traced_branch_0r( \
        condition, \
        pc_target)


#define traced_branchlink_1r(src0_action, condition, pc_target, dst_expr, dst_action) \
    { \
        src0_action; \
        INSTANCE.SetBranchTarget(condition, pc_target); \
        arch32_t GPR_dst_value; \
        dst_expr; \
        dst_action; \
        return { LA32ExecStatus::EXEC_BRANCH }; \
    }

#define traced_branchlink_norm1r(condition, pc_target, dst_expr) \
    traced_branchlink_1r( \
        read_GPR_src(0, true, RJi), \
        condition, \
        pc_target, \
        dst_expr, \
        write_GPR_dst(RDi, trace_gpr_1src))


#define traced_branchlink_0r(condition, pc_target, dst_expr, dst_action) \
    { \
        INSTANCE.SetBranchTarget(condition, pc_target); \
        arch32_t GPR_dst_value; \
        dst_expr; \
        dst_action; \
        return { LA32ExecStatus::EXEC_BRANCH }; \
    }

#define traced_branchlink_norm0r_r1(condition, pc_target, dst_expr) \
    traced_branchlink_0r( \
        condition, \
        pc_target, \
        dst_expr, \
        write_GPR_dst(1, trace_gpr_0src))


#define implexec(name, expr) \
    LA32ExecOutcome LA32R_EXECUTOR(name)(LA32R_EXECUTOR_PARAMS) noexcept \
    { \
        LA32Instruction __insn = insn; \
        if (PreExecutionEvent::name(inst, PC, __insn).Fire().IsCancelled()) \
            return { LA32ExecStatus::EXEC_EMULATION_CANCELLED, ECANCELED }; \
        auto __expr = [&](LA32Instruction& insn) -> LA32ExecOutcome { expr }; \
        LA32ExecOutcome outcome = __expr(__insn); \
        return (PostExecutionEvent::name(inst, PC, __insn, outcome).Fire().GetOutcome()); \
    }


namespace Jasse::LA32R_NSCSCC {

    // ADD.W rd, rj, rk
    implexec(ADD_W,
        traced_arithmetic_norm2r(
            GPR_dst_value = GPR_src_value(0) + GPR_src_value(1)
    ));

    // SUB.W rd, rj, rk
    implexec(SUB_W,
        traced_arithmetic_norm2r(
            GPR_dst_value = GPR_src_value(0) - GPR_src_value(1)
    ));

    // ADDI.W rd, rj, si12
    implexec(ADDI_W,
        traced_arithmetic_norm1r(
            GPR_dst_value = GPR_src_value(0) + SI12
    ));

    // LU12I.W rd, si20
    implexec(LU12I_W,
        traced_arithmetic_norm0r(
            GPR_dst_value = SI20 << 12
    ));

    // SLT rd, rj, rk
    implexec(SLT,
        traced_arithmetic_norm2r(
            GPR_dst_value = (signed(GPR_src_value(0)) < signed(GPR_src_value(1))) ? 1 : 0
    ));

    // SLTU rd, rj, rk
    implexec(SLTU,
        traced_arithmetic_norm2r(
            GPR_dst_value = (unsigned(GPR_src_value(0)) < unsigned(GPR_src_value(1))) ? 1 : 0
    ));

    // SLTI rd, rj, si12
    implexec(SLTI,
        traced_arithmetic_norm1r(
            GPR_dst_value = (signed(GPR_src_value(0)) < signed(SI12)) ? 1 : 0
    ));

    // SLTUI rd, rj, si12
    implexec(SLTUI,
        traced_arithmetic_norm1r(
            GPR_dst_value = (unsigned(GPR_src_value(0)) < unsigned(UI12)) ? 1 : 0
    ));

    // PCADDU12I rd, si20
    implexec(PCADDU12I,
        traced_arithmetic_norm0r(
            GPR_dst_value = PC + (SI20 << 12);
    ));

    // AND rd, rj, rk
    implexec(AND,
        traced_arithmetic_norm2r(
            GPR_dst_value = GPR_src_value(0) & GPR_src_value(1)
    ));

    // OR rd, rj, rk
    implexec(OR,
        traced_arithmetic_norm2r(
            GPR_dst_value = GPR_src_value(0) | GPR_src_value(1)
    ));

    // NOR rd, rj, rk
    implexec(NOR,
        traced_arithmetic_norm2r(
            GPR_dst_value = ~(GPR_src_value(0) | GPR_src_value(1))
    ));

    // XOR rd, rj, rk
    implexec(XOR,
        traced_arithmetic_norm2r(
            GPR_dst_value = GPR_src_value(0) ^ GPR_src_value(1)
    ));

    // ANDI rd, rj, ui12
    implexec(ANDI,
        traced_arithmetic_norm1r(
            GPR_dst_value = GPR_src_value(0) & UI12
    ));

    // ORI rd, rj, ui12
    implexec(ORI,
        traced_arithmetic_norm1r(
            GPR_dst_value = GPR_src_value(0) | UI12
    ));

    // XORI rd, rj, ui12
    implexec(XORI,
        traced_arithmetic_norm1r(
            GPR_dst_value = GPR_src_value(0) ^ UI12
    ));

    // MUL.W rd, rj, rk
    implexec(MUL_W,
        traced_arithmetic_norm2r(
            GPR_dst_value = GPR_src_value(0) * GPR_src_value(1)
    ));

    // MULH.W rd, rj, rk
    implexec(MULH_W,
        traced_arithmetic_norm2r(
            GPR_dst_value = (int64_t(GPR_src_value(0)) * int64_t(GPR_src_value(1))) >> 32
    ));

    // MULH.WU rd, rj, rk
    implexec(MULH_WU,
        traced_arithmetic_norm2r(
            GPR_dst_value = (uint64_t(GPR_src_value(0)) * uint64_t(GPR_src_value(1))) >> 32
    ));

    // DIV.W rd, rj, rk
    implexec(DIV_W,
        traced_arithmetic_norm2r(
            GPR_dst_value = signed(GPR_src_value(0)) / signed(GPR_src_value(1))
    ));

    // DIV.WU rd, rj, rk
    implexec(DIV_WU,
        traced_arithmetic_norm2r(
            GPR_dst_value = unsigned(GPR_src_value(0)) / unsigned(GPR_src_value(1))
    ));

    // MOD.W rd, rj, rk
    implexec(MOD_W,
        traced_arithmetic_norm2r(
            GPR_dst_value = signed(GPR_src_value(0)) % signed(GPR_src_value(1))
    ));

    // MOD.WU rd, rj, rk
    implexec(MOD_WU,
        traced_arithmetic_norm2r(
            GPR_dst_value = unsigned(GPR_src_value(0)) % unsigned(GPR_src_value(1))
    ));


    // SLL.W rd, rj, rk
    implexec(SLL_W,
        traced_arithmetic_norm2r(
            GPR_dst_value = GPR_src_value(0) << (GPR_src_value(1) & 0x1F)
    ));

    // SRL.W rd, rj, rk
    implexec(SRL_W,
        traced_arithmetic_norm2r(
            GPR_dst_value = unsigned(GPR_src_value(0)) >> (GPR_src_value(1) & 0x1F)
    ));

    // SRA.W rd, rj, rk
    implexec(SRA_W,
        traced_arithmetic_norm2r(
            GPR_dst_value = signed(GPR_src_value(0)) >> (GPR_src_value(1) & 0x1F)
    ));

    // SLLI.W rd, rj, ui5
    implexec(SLLI_W,
        traced_arithmetic_norm1r(
            GPR_dst_value = GPR_src_value(0) << (UI5 & 0x1F)
    ));

    // SRLI.W rd, rj, ui5
    implexec(SRLI_W,
        traced_arithmetic_norm1r(
            GPR_dst_value = unsigned(GPR_src_value(0)) >> (UI5 & 0x1F)
    ));

    // SRAI.W rd, rj, ui5
    implexec(SRAI_W,
        traced_arithmetic_norm1r(
            GPR_dst_value = signed(GPR_src_value(0)) >> (UI5 & 0x1F)
    ));


    // BEQ rj, rd, offs16
    implexec(BEQ,
        traced_branch_norm2r(
            GPR_src_value(0) == GPR_src_value(1), 
            PC + (SI16 << 2)
    ));

    // BNE rj, rd, offs16
    implexec(BNE,
        traced_branch_norm2r(
            GPR_src_value(0) != GPR_src_value(1),
            PC + (SI16 << 2)
    ));

    // BLT rj, rd, offs16
    implexec(BLT,
        traced_branch_norm2r(
            signed(GPR_src_value(0)) < signed(GPR_src_value(1)),
            PC + (SI16 << 2)
    ));

    // BGE rj, rd, offs16
    implexec(BGE,
        traced_branch_norm2r(
            signed(GPR_src_value(0)) >= signed(GPR_src_value(1)),
            PC + (SI16 << 2)
    ));

    // BLTU rj, rd, offs16
    implexec(BLTU,
        traced_branch_norm2r(
            unsigned(GPR_src_value(0)) < unsigned(GPR_src_value(1)),
            PC + (SI16 << 2)
    ));

    // BGEU rj, rd, offs16
    implexec(BGEU,
        traced_branch_norm2r(
            unsigned(GPR_src_value(0)) >= unsigned(GPR_src_value(1)),
            PC + (SI16 << 2)
    ));

    // B offs26
    implexec(B,
        traced_branch_norm0r(
            true,
            PC + (SI26 << 2)
    ));

    // BL offs26
    implexec(BL,
        traced_branchlink_norm0r_r1(
            true,
            PC + (SI26 << 2),
            GPR_dst_value = PC + 4
    ));

    // JIRL rd, rj, offs16
    implexec(JIRL,
        traced_branchlink_norm1r(
            true,
            GPR_src_value(0) + (SI16 << 2),
            GPR_dst_value = PC + 4
    ));


    // LD.B rd, rj, si12
    implexec(LD_B,
        traced_memory_load_norm1r(BYTE, SEXT));

    // LD.H rd, rj, si12
    implexec(LD_H,
        traced_memory_load_norm1r(HALF_WORD, SEXT));

    // LD.W rd, rj, si12
    implexec(LD_W,
        traced_memory_load_norm1r(WORD, SEXT));

    // LD.BU rd, rj, si12
    implexec(LD_BU,
        traced_memory_load_norm1r(BYTE, ZEXT));

    // LD.HU rd, rj, si12
    implexec(LD_HU,
        traced_memory_load_norm1r(HALF_WORD, ZEXT));

    
    // ST.B rd, rj, si12
    implexec(ST_B,
        traced_memory_store_norm2r(BYTE));

    // ST.H rd, rj, si12
    implexec(ST_H,
        traced_memory_store_norm2r(HALF_WORD));

    // ST.W rd, rj, si12
    implexec(ST_W,
        traced_memory_store_norm2r(WORD));

}


#undef RDi
#undef RJi
#undef RKi
#undef RAi

#undef GPR

#undef RD
#undef RJ
#undef RK
#undef RA

#undef UI8
#undef SI8

#undef UI12
#undef SI12

#undef UI14
#undef SI14

#undef UI16
#undef SI16

#undef UI21
#undef SI21

#undef UI26
#undef SI26

#undef UI20
#undef SI20

#undef UI5
#undef SI5

#undef INSTANCE
#undef INSTRUCTION

#undef PC

#undef GPR_src_value
#undef GPR_src_trace

#undef GPR_dst_value
#undef GPR_dst_trace

#undef MEM_src_trace

#undef TRACE_REF
#undef TRACE_CONTENT

#undef trace_fetch

#undef trace_gpr_0src
#undef trace_gpr_1src
#undef trace_gpr_2src
#undef trace_gpr_memload
#undef trace_gpr_memstore

#undef read_GPR_src
#undef write_GPR_dst

#undef traced_memory_load
#undef traced_memory_store

#undef traced_memory_load_1r
#undef traced_memory_load_norm1r

#undef traced_memory_store_2r
#undef traced_memory_store_norm2r

#undef traced_arithmetic_2r
#undef traced_arithmetic_norm2r

#undef traced_arithmetic_1r
#undef traced_arithmetic_norm1r

#undef traced_arithmetic_0r
#undef traced_arithmetic_norm0r

#undef traced_branch_2r
#undef traced_branch_norm2r

#undef traced_branch_0r
#undef traced_branch_norm0r

#undef traced_branchlink_1r
#undef traced_branchlink_norm1r

#undef traced_branchlink_0r
#undef traced_branchlink_norm0r_r1

#undef event_wrapped

#undef implexec
