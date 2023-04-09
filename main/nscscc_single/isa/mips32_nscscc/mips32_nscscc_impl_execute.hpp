#pragma once
//
// MIPS32 (NSCSCC) ISA Emulator (Jasse)
//
// MIPS32-NSCSCC, bahaviour functions
//

#include "mips32_nscscc_def_execute.hpp"
#include "mips32_nscscc_def_event.hpp"


#define RSi                         insn.GetRS()
#define RTi                         insn.GetRT()
#define RDi                         insn.GetRD()
#define R31i                        31

#define GPR(i)                      inst.Arch().GPRs()[i]
#define HILO(name)                  inst.Arch().name()


#define RS                          GPR(RSi)
#define RT                          GPR(RTi)
#define RD                          GPR(RDi)
#define R31                         GPR(R31i)

#define SA                          insn.GetShamt()
#define PC                          inst.Arch().PC()
#define IMM16_SEXT                  SEXT32_IMM16(insn.GetImmediate())
#define IMM16_ZEXT                  insn.GetImmediate()
#define IMM26_SEXT                  SEXT32_IMM26(insn.GetJumpIndex())
#define IMM26_ZEXT                  insn.GetJumpIndex()


#define traced_arithmetic_2r(dst, src0, src1, expr) { \
    arch32_t value; \
    value = GPR(dst) = expr; \
    if (inst.IsTraceEnabled() && inst.Tracers().HasGPRTracer()) { \
        MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
        MIPS32TraceEntity::Reference trace_ref = inst.TracePool().Acquire(); \
        if (trace_ref.IsValid()) { \
            trace_ref->SetInstruction(insn); \
            trace_ref->SetPC(PC); \
            trace_ref->SetValue(value); \
            trace_ref->SetFirstOperand  (gpr_tracer->Get(src0).Get()); \
            trace_ref->SetSecondOperand (gpr_tracer->Get(src1).Get()); \
        } \
        gpr_tracer->Get(dst).Append(trace_ref); \
    } \
    return { EXEC_SEQUENTIAL }; \
}

#define traced_arithmetic_norm2r(expr)  traced_arithmetic_2r(RDi, RSi, RTi, expr)

#define traced_arithmetic_shift2r(expr) traced_arithmetic_2r(RDi, RTi, RSi, expr)


#define traced_arithmetic_1r(dst, src0, expr) { \
    arch32_t value; \
    value = GPR(dst) = expr; \
    if (inst.IsTraceEnabled() && inst.Tracers().HasGPRTracer()) { \
        MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
        MIPS32TraceEntity::Reference trace_ref = inst.TracePool().Acquire(); \
        if (trace_ref.IsValid()) { \
            trace_ref->SetInstruction(insn); \
            trace_ref->SetPC(PC); \
            trace_ref->SetValue(value); \
            trace_ref->SetFirstOperand  (gpr_tracer->Get(src0).Get()); \
        } \
        gpr_tracer->Get(dst).Append(trace_ref); \
    } \
    return { EXEC_SEQUENTIAL }; \
}

#define traced_arithmetic_norm1r(expr)  traced_arithmetic_1r(RTi, RSi, expr)

#define traced_arithmetic_shift1r(expr) traced_arithmetic_1r(RDi, RTi, expr)


#define traced_arithmetic_0r(dst, expr) { \
    arch32_t value; \
    value = GPR(dst) = expr; \
    if (inst.IsTraceEnabled() && inst.Tracers().HasGPRTracer()) { \
        MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
        MIPS32TraceEntity::Reference trace_ref = inst.TracePool().Acquire(); \
        if (trace_ref.IsValid()) { \
            trace_ref->SetInstruction(insn); \
            trace_ref->SetPC(PC); \
            trace_ref->SetValue(value); \
        } \
        gpr_tracer->Get(dst).Append(trace_ref); \
    } \
    return { EXEC_SEQUENTIAL }; \
}


#define traced_branch_if_2r(src0, src1, expr) { \
    bool pred = expr; \
    arch32_t target = PC + 4 + (IMM16_SEXT << 2); \
    if (pred && inst.IsTraceEnabled() && inst.Tracers().HasPCTracer()) { \
        MIPS32PCTracer* pc_tracer = inst.Tracers().GetPCTracer(); \
        MIPS32TraceEntity::Reference trace_ref = inst.TracePool().Acquire(); \
        if (trace_ref.IsValid()) { \
            trace_ref->SetInstruction(insn); \
            trace_ref->SetPC(PC); \
            trace_ref->SetValue(target); \
            if (inst.Tracers().HasGPRTracer()) { \
                MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
                trace_ref->SetFirstOperand  (gpr_tracer->Get(src0).Get()); \
                trace_ref->SetSecondOperand (gpr_tracer->Get(src1).Get()); \
            } \
        } \
        pc_tracer->SetDelayedTrace(trace_ref); \
    } \
    inst.SetBranchTarget(pred, target); \
    return { EXEC_DELAYSLOT }; \
}

#define traced_branch_if_norm2r(expr)   traced_branch_if_2r(RSi, RTi, expr)


#define traced_branch_if_1r(src0, expr) { \
    bool pred = expr; \
    arch32_t target = PC + 4 + (IMM16_SEXT << 2); \
    if (pred && inst.IsTraceEnabled() && inst.Tracers().HasPCTracer()) { \
        MIPS32PCTracer* pc_tracer = inst.Tracers().GetPCTracer(); \
        MIPS32TraceEntity::Reference trace_ref = inst.TracePool().Acquire(); \
        if (trace_ref.IsValid()) { \
            trace_ref->SetInstruction(insn); \
            trace_ref->SetPC(PC); \
            trace_ref->SetValue(target); \
            if (inst.Tracers().HasGPRTracer()) { \
                MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
                trace_ref->SetFirstOperand(gpr_tracer->Get(src0).Get()); \
            } \
        } \
        pc_tracer->SetDelayedTrace(trace_ref); \
    } \
    inst.SetBranchTarget(pred, target); \
    return { EXEC_DELAYSLOT }; \
}

#define traced_branch_if_norm1r(expr)   traced_branch_if_1r(RSi, expr)


#define traced_jumplink_1r(dst, src0, expr) { \
    arch32_t target = expr; \
    arch32_t link = GPR(dst) = PC + 8; \
    inst.SetBranchTarget(true, target); \
    if (inst.IsTraceEnabled() && inst.Tracers().HasPCTracer()) { \
        MIPS32PCTracer* pc_tracer = inst.Tracers().GetPCTracer(); \
        MIPS32TraceEntity::Reference trace_ref = inst.TracePool().Acquire(); \
        if (trace_ref.IsValid()) { \
            trace_ref->SetInstruction(insn); \
            trace_ref->SetPC(PC); \
            trace_ref->SetValue(target); \
            if (inst.Tracers().HasGPRTracer()) { \
                MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
                trace_ref->SetFirstOperand(gpr_tracer->Get(src0).Get()); \
            } \
        } \
        pc_tracer->SetDelayedTrace(trace_ref); \
    } \
    if (inst.IsTraceEnabled() && inst.Tracers().HasGPRTracer()) { \
        MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
        MIPS32TraceEntity::Reference trace_ref = inst.TracePool().Acquire(); \
        if (trace_ref.IsValid()) { \
            trace_ref->SetInstruction(insn); \
            trace_ref->SetPC(PC); \
            trace_ref->SetValue(link); \
        } \
        gpr_tracer->Get(dst).Append(trace_ref); \
    } \
    return { EXEC_DELAYSLOT }; \
}


#define traced_jumplink_0r(dst, expr) { \
    arch32_t target = expr; \
    arch32_t link = GPR(dst) = PC + 8; \
    inst.SetBranchTarget(true, target); \
    if (inst.IsTraceEnabled() && inst.Tracers().HasPCTracer()) { \
        MIPS32PCTracer* pc_tracer = inst.Tracers().GetPCTracer(); \
        MIPS32TraceEntity::Reference trace_ref = inst.TracePool().Acquire(); \
        if (trace_ref.IsValid()) { \
            trace_ref->SetInstruction(insn); \
            trace_ref->SetPC(PC); \
            trace_ref->SetValue(target); \
        } \
        pc_tracer->SetDelayedTrace(trace_ref); \
    } \
    if (inst.IsTraceEnabled() && inst.Tracers().HasGPRTracer()) { \
        MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
        MIPS32TraceEntity::Reference trace_ref = inst.TracePool().Acquire(); \
        if (trace_ref.IsValid()) { \
            trace_ref->SetInstruction(insn); \
            trace_ref->SetPC(PC); \
            trace_ref->SetValue(link); \
        } \
        gpr_tracer->Get(dst).Append(trace_ref); \
    } \
    return { EXEC_DELAYSLOT }; \
}


#define traced_jump_1r(src0, expr) { \
    arch32_t target = expr; \
    inst.SetBranchTarget(true, target); \
    if (inst.IsTraceEnabled() && inst.Tracers().HasPCTracer()) { \
        MIPS32PCTracer* pc_tracer = inst.Tracers().GetPCTracer(); \
        MIPS32TraceEntity::Reference trace_ref = inst.TracePool().Acquire(); \
        if (trace_ref.IsValid()) { \
            trace_ref->SetInstruction(insn); \
            trace_ref->SetPC(PC); \
            trace_ref->SetValue(target); \
            if (inst.Tracers().HasGPRTracer()) { \
                MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
                trace_ref->SetFirstOperand(gpr_tracer->Get(src0).Get()); \
            } \
        } \
        pc_tracer->SetDelayedTrace(trace_ref); \
    } \
    return { EXEC_DELAYSLOT }; \
}


#define traced_jump_0r(expr) { \
    arch32_t target = expr; \
    inst.SetBranchTarget(true, target); \
    if (inst.IsTraceEnabled() && inst.Tracers().HasPCTracer()) { \
        MIPS32PCTracer* pc_tracer = inst.Tracers().GetPCTracer(); \
        MIPS32TraceEntity::Reference trace_ref = inst.TracePool().Acquire(); \
        if (trace_ref.IsValid()) { \
            trace_ref->SetInstruction(insn); \
            trace_ref->SetPC(PC); \
            trace_ref->SetValue(target); \
        } \
        pc_tracer->SetDelayedTrace(trace_ref); \
    } \
    return { EXEC_DELAYSLOT }; \
}


#define traced_load(dst, src0, width, ext) { \
    memdata_t memdata; \
    arch32_t address = GPR(src0) + IMM16_SEXT; \
    MIPS32MOPOutcome mopoutcome = inst.MI()->ReadData(address, MOPW_##width, &memdata); \
    switch (mopoutcome.status) { \
        case MOP_SUCCESS:               break; \
        case MOP_ACCESS_FAULT:          return { EXEC_MEMORY_ACCESS_FAULT, mopoutcome.error }; \
        case MOP_ADDRESS_MISALIGNED:    return { EXEC_MEMORY_ADDRESS_MISALIGNED, mopoutcome.error }; \
        case MOP_DEVICE_ERROR:          return { EXEC_MEMORY_DEVICE_ERROR, mopoutcome.error }; \
        [[unlikely]] default:           SHOULD_NOT_REACH_HERE; \
    } \
    arch32_t value = GPR(dst) = ext##32_##width(memdata); \
    if (inst.IsTraceEnabled() && inst.Tracers().HasGPRTracer()) { \
        MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
        MIPS32TraceEntity::Reference trace_ref = inst.TracePool().Acquire(); \
        if (trace_ref.IsValid()) { \
            trace_ref->SetInstruction(insn); \
            trace_ref->SetPC(PC); \
            trace_ref->SetValue(value); \
            trace_ref->SetFirstOperand(gpr_tracer->Get(src0).Get()); \
            if (inst.Tracers().HasMemoryTracer()) { \
                MIPS32MemoryTracer* memory_tracer = inst.Tracers().GetMemoryTracer(); \
                auto memory_trace_history = memory_tracer->Get(address); \
                if (memory_trace_history) \
                    trace_ref->SetSecondOperand(((MIPS32TraceHistory&) *memory_trace_history).Get()); \
            } \
        } \
        gpr_tracer->Get(dst).Append(trace_ref); \
    } \
    return { EXEC_SEQUENTIAL }; \
}

#define traced_load_norm(width, ext)    traced_load(RTi, RSi, width, ext)


#define traced_store(src0, src1, width) { \
    memdata_t memdata; \
    memdata.data32 = GPR(src0); \
    arch32_t address = GPR(src1) + IMM16_SEXT; \
    MIPS32MOPOutcome mopoutcome = inst.MI()->WriteData(address, MOPW_##width, memdata); \
    switch (mopoutcome.status) { \
        case MOP_SUCCESS:               break; \
        case MOP_ACCESS_FAULT:          return { EXEC_MEMORY_ACCESS_FAULT, mopoutcome.error }; \
        case MOP_ADDRESS_MISALIGNED:    return { EXEC_MEMORY_ADDRESS_MISALIGNED, mopoutcome.error }; \
        case MOP_DEVICE_ERROR:          return { EXEC_MEMORY_DEVICE_ERROR, mopoutcome.error }; \
        [[unlikely]] default:           SHOULD_NOT_REACH_HERE; \
    } \
    arch32_t value = memdata.data32 & MOPW_##width.mask; \
    if (inst.IsTraceEnabled() && inst.Tracers().HasMemoryTracer()) { \
        MIPS32MemoryTracer* memory_tracer = inst.Tracers().GetMemoryTracer(); \
        MIPS32TraceEntity::Reference trace_ref = inst.TracePool().Acquire(); \
        if (trace_ref.IsValid()) { \
            trace_ref->SetInstruction(insn); \
            trace_ref->SetPC(PC); \
            trace_ref->SetValue(value); \
            if (inst.Tracers().HasGPRTracer()) { \
                MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
                trace_ref->SetFirstOperand  (gpr_tracer->Get(src0).Get()); \
                trace_ref->SetSecondOperand (gpr_tracer->Get(src1).Get()); \
            } \
        } \
        if (memory_tracer->CheckBound(address)) \
            memory_tracer->Acquire(address).Append(trace_ref); \
    } \
    return { EXEC_SEQUENTIAL }; \
}

#define traced_store_norm(width)    traced_store(RTi, RSi, width)


#define traced_mfhilo(dst, hilo) { \
    arch32_t value = GPR(dst) = HILO(hilo); \
    if (inst.IsTraceEnabled() && inst.Tracers().HasGPRTracer()) { \
        MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
        MIPS32TraceEntity::Reference trace_ref = inst.TracePool().Acquire(); \
        if (trace_ref.IsValid()) { \
            trace_ref->SetInstruction(insn); \
            trace_ref->SetPC(PC); \
            trace_ref->SetValue(value); \
            if (inst.Tracers().HasHiLoTracer()) { \
                MIPS32HiLoTracer* hilo_tracer = inst.Tracers().GetHiLoTracer(); \
                trace_ref->SetFirstOperand(hilo_tracer->Get##hilo().Get()); \
            } \
        } \
        gpr_tracer->Get(dst).Append(trace_ref); \
    } \
    return { EXEC_SEQUENTIAL }; \
}

#define traced_mfhi_norm    traced_mfhilo(RDi, Hi)
#define traced_mflo_norm    traced_mfhilo(RDi, Lo)


#define traced_mthilo(src, hilo) { \
    arch32_t value = HILO(hilo) = GPR(src); \
    if (inst.IsTraceEnabled() && inst.Tracers().HasHiLoTracer()) { \
        MIPS32HiLoTracer* hilo_tracer = inst.Tracers().GetHiLoTracer(); \
        MIPS32TraceEntity::Reference trace_ref = inst.TracePool().Acquire(); \
        if (trace_ref.IsValid()) { \
            trace_ref->SetInstruction(insn); \
            trace_ref->SetPC(PC); \
            trace_ref->SetValue(value); \
            if (inst.Tracers().HasGPRTracer()) { \
                MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
                trace_ref->SetFirstOperand(gpr_tracer->Get(src).Get()); \
            } \
        } \
        hilo_tracer->Get##hilo().Append(trace_ref); \
    } \
    return { EXEC_SEQUENTIAL }; \
} 

#define traced_mthi_norm    traced_mthilo(RSi, Hi)
#define traced_mtlo_norm    traced_mthilo(RSi, Lo)


#define traced_div(src0, src1, sign) { \
    arch32_t q = HILO(Lo) = ((sign) GPR(src0)) / ((sign) GPR(src1)); \
    arch32_t r = HILO(Hi) = ((sign) GPR(src0)) % ((sign) GPR(src1)); \
    if (inst.IsTraceEnabled() && inst.Tracers().HasHiLoTracer()) { \
        MIPS32HiLoTracer* hilo_tracer = inst.Tracers().GetHiLoTracer(); \
        MIPS32TraceEntity::Reference lo_trace_ref = inst.TracePool().Acquire(); \
        if (lo_trace_ref.IsValid()) { \
            lo_trace_ref->SetInstruction(insn); \
            lo_trace_ref->SetPC(PC); \
            lo_trace_ref->SetValue(q); \
            if (inst.Tracers().HasGPRTracer()) { \
                MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
                lo_trace_ref->SetFirstOperand (gpr_tracer->Get(src0).Get()); \
                lo_trace_ref->SetSecondOperand(gpr_tracer->Get(src1).Get()); \
            } \
        } \
        MIPS32TraceEntity::Reference hi_trace_ref = inst.TracePool().Acquire(); \
        if (hi_trace_ref.IsValid()) { \
            hi_trace_ref->SetInstruction(insn); \
            hi_trace_ref->SetPC(PC); \
            hi_trace_ref->SetValue(r); \
            if (inst.Tracers().HasGPRTracer()) { \
                MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
                hi_trace_ref->SetFirstOperand (gpr_tracer->Get(src0).Get()); \
                hi_trace_ref->SetSecondOperand(gpr_tracer->Get(src1).Get()); \
            } \
        } \
        hilo_tracer->GetLo().Append(lo_trace_ref); \
        hilo_tracer->GetHi().Append(hi_trace_ref); \
    } \
    return { EXEC_SEQUENTIAL }; \
}

#define traced_div_norm(sign)       traced_div(RSi, RTi, sign)


#define traced_mult(src0, src1, sign) { \
    uint64_t val = (unsigned) (((int64_t) (sign) GPR(src0)) * ((int64_t) (sign) GPR(src1))); \
    arch32_t lo = HILO(Lo) = (arch32_t) (val); \
    arch32_t hi = HILO(Hi) = (arch32_t) (val >> 32); \
    if (inst.IsTraceEnabled() && inst.Tracers().HasHiLoTracer()) { \
        MIPS32HiLoTracer* hilo_tracer = inst.Tracers().GetHiLoTracer(); \
        MIPS32TraceEntity::Reference lo_trace_ref = inst.TracePool().Acquire(); \
        if (lo_trace_ref.IsValid()) { \
            lo_trace_ref->SetInstruction(insn); \
            lo_trace_ref->SetPC(PC); \
            lo_trace_ref->SetValue(lo); \
            if (inst.Tracers().HasGPRTracer()) { \
                MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
                lo_trace_ref->SetFirstOperand (gpr_tracer->Get(src0).Get()); \
                lo_trace_ref->SetSecondOperand(gpr_tracer->Get(src1).Get()); \
            } \
        } \
        MIPS32TraceEntity::Reference hi_trace_ref = inst.TracePool().Acquire(); \
        if (hi_trace_ref.IsValid()) { \
            hi_trace_ref->SetInstruction(insn); \
            hi_trace_ref->SetPC(PC); \
            hi_trace_ref->SetValue(hi); \
            if (inst.Tracers().HasGPRTracer()) { \
                MIPS32GPRTracer* gpr_tracer = inst.Tracers().GetGPRTracer(); \
                hi_trace_ref->SetFirstOperand (gpr_tracer->Get(src0).Get()); \
                hi_trace_ref->SetSecondOperand(gpr_tracer->Get(src1).Get()); \
            } \
        } \
        hilo_tracer->GetLo().Append(lo_trace_ref); \
        hilo_tracer->GetHi().Append(hi_trace_ref); \
    } \
    return { EXEC_SEQUENTIAL }; \
}

#define traced_mult_norm(sign)      traced_mult(RSi, RTi, sign)


#define event_wrapped(name, expr) \
    { \
        MIPS32Instruction __insn = insn; \
        if (MIPS32PreExecutionEvents::name(inst, PC, __insn).Fire().IsCancelled()) \
            return { EXEC_EMULATION_CANCELLED, ECANCELED }; \
        auto __expr = [&](MIPS32Instruction& insn) -> MIPS32ExecOutcome { expr }; \
        MIPS32ExecOutcome outcome = __expr(__insn); \
        return (MIPS32PostExecutionEvents::name(inst, PC, __insn, outcome).Fire().GetOutcome()); \
    } \


#define implexec(name, expr) \
    MIPS32ExecOutcome MIPS32_EXECUTOR(name)(MIPS32_EXECUTOR_PARAMS) expr


namespace Jasse {

    // ADD rd, rs, rt
    implexec(ADD, 
        noexcept event_wrapped(ADD, traced_arithmetic_norm2r(RS + RT)));

    // ADDI rt, rs, imm
    implexec(ADDI,
        noexcept event_wrapped(ADDI, traced_arithmetic_norm1r(RS + IMM16_SEXT)));

    // ADDU rd, rs, rt
    implexec(ADDU,
        noexcept event_wrapped(ADDU, traced_arithmetic_norm2r(RS + RT)));

    // ADDIU rt, rs, imm
    implexec(ADDIU,
        noexcept event_wrapped(ADDIU, traced_arithmetic_norm1r(RS + IMM16_SEXT)));

    // SUB rd, rs, rt
    implexec(SUB, 
        noexcept event_wrapped(SUB, traced_arithmetic_norm2r(RS - RT)));

    // SUBU rd, rs, rt
    implexec(SUBU,
        noexcept event_wrapped(SUBU, traced_arithmetic_norm2r(RS - RT)));

    // SLT rd, rs, rt
    implexec(SLT,
        noexcept event_wrapped(SLT, traced_arithmetic_norm2r((signed) RS < (signed) RT)));

    // SLTI rt, rs, imm
    implexec(SLTI,
        noexcept event_wrapped(SLTI, traced_arithmetic_norm1r((signed) RS < (signed) IMM16_SEXT)));

    // SLTU rd, rs, rt
    implexec(SLTU,
        noexcept event_wrapped(SLTU, traced_arithmetic_norm2r(RS < RT)));

    // SLTIU rt, rs, imm
    implexec(SLTIU,
        noexcept event_wrapped(SLTIU, traced_arithmetic_norm1r(RS < IMM16_ZEXT)));

    // MUL rd, rs, rt
    implexec(MUL,
        noexcept event_wrapped(MUL, traced_arithmetic_norm2r(RS * RT)));

    
    // DIV rs, rt
    implexec(DIV,
        noexcept event_wrapped(DIV, traced_div_norm(signed)));

    // DIVU rs, rt
    implexec(DIVU,
        noexcept event_wrapped(DIVU, traced_div_norm(unsigned)));

    // MULT rs, rt
    implexec(MULT,
        noexcept event_wrapped(MULT, traced_mult_norm(signed)));

    // MULTU rs, rt
    implexec(MULTU,
        noexcept event_wrapped(MULTU, traced_mult_norm(unsigned)));


    // AND rd, rs, rt
    implexec(AND,
        noexcept event_wrapped(AND, traced_arithmetic_norm2r(RS & RT)));

    // ANDI rt, rs, imm
    implexec(ANDI,
        noexcept event_wrapped(ANDI, traced_arithmetic_norm1r(RS & IMM16_ZEXT)));

    // LUI rt, imm
    implexec(LUI,
        noexcept event_wrapped(LUI, traced_arithmetic_0r(RTi, IMM16_ZEXT << 16)));

    // OR rd, rs, rt
    implexec(OR,
        noexcept event_wrapped(OR, traced_arithmetic_norm2r(RS | RT)));

    // ORI rt, rs, imm
    implexec(ORI,
        noexcept event_wrapped(ORI, traced_arithmetic_norm1r(RS | IMM16_ZEXT)));

    // XOR rd, rs, rt
    implexec(XOR,
        noexcept event_wrapped(XOR, traced_arithmetic_norm2r(RS ^ RT)));

    // XORI rt, rs, imm
    implexec(XORI,
        noexcept event_wrapped(XORI, traced_arithmetic_norm1r(RS ^ IMM16_ZEXT)));


    // SLL rd, rt, sa
    implexec(SLL,
        noexcept event_wrapped(SLL, traced_arithmetic_shift1r(RT << SA)));

    // SLLV rd, rt, rs
    implexec(SLLV,
        noexcept event_wrapped(SLLV, traced_arithmetic_shift2r(RT << RS)));

    // SRA rd, rt, sa
    implexec(SRA,
        noexcept event_wrapped(SRA, traced_arithmetic_shift1r((signed) RT >> SA)));
    
    // SRAV rd, rt, rs
    implexec(SRAV,
        noexcept event_wrapped(SRAV, traced_arithmetic_shift2r((signed) RT >> RS)));

    // SRL rd, rt, sa
    implexec(SRL,
        noexcept event_wrapped(SRL, traced_arithmetic_shift1r(RT >> SA)));

    // SRLV rd, rt, rs
    implexec(SRLV,
        noexcept event_wrapped(SRLV, traced_arithmetic_shift2r(RT >> RS)));


    // BEQ rs, rt, offset
    implexec(BEQ,
        noexcept event_wrapped(BEQ, traced_branch_if_norm2r(RS == RT)));

    // BNE rs, rt, offset
    implexec(BNE,
        noexcept event_wrapped(BNE, traced_branch_if_norm2r(RS != RT)));

    // BGEZ rs, offset
    implexec(BGEZ,
        noexcept event_wrapped(BGEZ, traced_branch_if_norm1r(RS >= 0)));

    // BGTZ rs, offset
    implexec(BGTZ,
        noexcept event_wrapped(BGTZ, traced_branch_if_norm1r(RS > 0)));

    // BLEZ rs, offset
    implexec(BLEZ,
        noexcept event_wrapped(BLEZ, traced_branch_if_norm1r(RS <= 0)));

    // BLTZ rs, offset
    implexec(BLTZ,
        noexcept event_wrapped(BLTZ, traced_branch_if_norm1r(RS < 0)));
    
    // J target
    implexec(J,
        noexcept event_wrapped(J, traced_jump_0r((IMM26_ZEXT << 2) | (PC & 0xF0000000))));

    // JAL target
    implexec(JAL,
        noexcept event_wrapped(JAL, traced_jumplink_0r(R31i, (IMM26_ZEXT << 2) | (PC & 0xF0000000))));

    // JR rs
    implexec(JR,
        noexcept event_wrapped(JR, traced_jump_1r(RSi, RS)));

    // JALR rd, rs
    implexec(JALR,
        noexcept event_wrapped(JALR, traced_jumplink_1r(RDi, RSi, RS)));

    
    // MFHI rd
    implexec(MFHI,
        noexcept event_wrapped(MFHI, traced_mfhi_norm));

    // MFLO rd
    implexec(MFLO,
        noexcept event_wrapped(MFLO, traced_mflo_norm));

    // MTHI rs
    implexec(MTHI,
        noexcept event_wrapped(MTHI, traced_mthi_norm));

    // MTLO rs
    implexec(MTLO,
        noexcept event_wrapped(MTLO, traced_mtlo_norm));


    // LB rt, offset(base)
    implexec(LB,
        noexcept event_wrapped(LB, traced_load_norm(BYTE, SEXT)));

    // LBU rt, offset(base)
    implexec(LBU,
        noexcept event_wrapped(LBU, traced_load_norm(BYTE, ZEXT)));

    // LH rt, offset(base)
    implexec(LH,
        noexcept event_wrapped(LH, traced_load_norm(HALF_WORD, SEXT)));

    // LHU rt, offset(base)
    implexec(LHU,
        noexcept event_wrapped(LHU, traced_load_norm(HALF_WORD, ZEXT)));

    // LW rt, offset(base)
    implexec(LW,
        noexcept event_wrapped(LW, traced_load_norm(WORD, SEXT)));

    // SB rt, offset(base)
    implexec(SB,
        noexcept event_wrapped(SB, traced_store_norm(BYTE)));

    // SH rt, offset(base)
    implexec(SH,
        noexcept event_wrapped(SH, traced_store_norm(HALF_WORD)));

    // SW rt, offset(base)
    implexec(SW,
        noexcept event_wrapped(SW, traced_store_norm(WORD)));

    
    // TEQ rs, rt
    implexec(TEQ,
        noexcept event_wrapped(TEQ, return { EXEC_SEQUENTIAL };))
}


#undef RS
#undef RT
#undef RD
#undef R31
#undef SA
#undef PC
#undef IMM16_SEXT
#undef IMM16_ZEXT
#undef IMM26_SEXT
#undef IMM26_ZEXT

#undef GPR
#undef HILO

#undef RSi
#undef RTi
#undef RDi
#undef R31i

#undef traced_arithmetic_2r
#undef traced_arithmetic_norm2r
#undef traced_arithmetic_shift2r
#undef traced_arithmetic_1r
#undef traced_arithmetic_norm1r
#undef traced_arithmetic_shift1r
#undef traced_arithmetic_0r

#undef traced_branch_if_2r
#undef traced_branch_if_norm2r
#undef traced_branch_if_1r
#undef traced_branch_if_norm1r

#undef traced_jumplink_1r
#undef traced_jumplink_0r

#undef traced_jump_1r
#undef traced_jump_0r

#undef traced_load
#undef traced_load_norm
#undef traced_store
#undef traced_store_norm

#undef event_wrapped

#undef implexec
