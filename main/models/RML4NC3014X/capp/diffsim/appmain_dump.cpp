#include "appmain_dump.hpp"
//
//
//
//

#include "appmain_glbl.hpp"


#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>


#include "autoinclude.h"

#include AUTOINC_BE_JASSE2_LA32(la32_nscscc.hpp)    // IWYU pragma: keep


//
static constexpr const char* _COLOR_CORRECT     = "\033[1;32m";

static constexpr const char* _COLOR_ERROR       = "\033[1;31m";

static constexpr const char* _COLOR_PAUSE       = "\033[33m";

static constexpr const char* _COLOR_SPECIAL     = "\033[1;33m";

static constexpr const char* _COLOR_COMMENT     = "\033[1;30m";

static constexpr const char* _COLOR_RESET       = "\033[0m";


//
static inline std::string dump_at(Jasse::addr_t address)
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');

    //
    oss << std::setw(8) << address << ":   ";

    //
    Jasse::memdata_t data;
    Jasse::LA32MOPOutcome mopoutcome 
        = glbl.ctx.ref.soc->MMU().ReadInsn(address, Jasse::MOPW_WORD, &data);

    if (mopoutcome.status != Jasse::LA32MOPStatus::MOP_SUCCESS)
    {
        if (glbl.cfg.dump0.muteUnread)
            return "";
        else
        {
            oss << "<unreadable>";
        }
    }
    else 
    {
        oss << std::setw(8) << data.data32 << "    ";

        //
        Jasse::LA32Instruction insn(data.data32);

        if (Jasse::Decoder::LA32R_NSCSCC->Decode(insn))
            oss << insn.ToString();
        else
            oss << "0x" << std::setw(8) << data.data32;
    }

    return oss.str();
}


//
static inline std::string dump_trace_at(Jasse::addr_t address, int traceOffset)
{
    //
    auto& tracers = glbl.ctx.ref.emu->Tracers();
    
    if (!tracers.HasExecutionTracer())
        return "<out-of-trace>";

    auto executionTracer = tracers.GetExecutionTracer();

    if (executionTracer->Get().GetCount() <= traceOffset)
        return "<out-of-trace>";

    //
    auto executionTrace = executionTracer->Get().Get(traceOffset);

    if (!executionTrace.IsValid())
        return "<out-of-trace>";

    //
    auto traceContentOpt = executionTrace->GetContent(Jasse::LA32TraceContentLegacyType::INSTRUCTION_EXECUTION);

    if (!traceContentOpt)
        return "<unrecognized-trace>";

    //
    auto& traceContent = traceContentOpt->get();

    //
    const Jasse::LA32Trait* trait = traceContent.insn.GetCodepoint()->GetTrait();

    if (!trait)
        return "<unrecognized-trace>";

    //
    std::ostringstream oss;

    // display destination traces
    for (int i = 0; i < trait->GetDestinationCount(); i++)
    {
        if (i)
            oss << ", ";

        const Jasse::LA32Trait::Destination* dst = trait->GetDestination(i);

        switch (dst->GetType())
        {
            case Jasse::LA32Trait::Destination::Type::GPR: {

                const Jasse::LA32Trait::Destination::GPR* dst_gpr = 
                    static_cast<const Jasse::LA32Trait::Destination::GPR*>(dst);

                unsigned int gpr_index = dst_gpr->GetGPRIndex(traceContent.insn);

                oss << Jasse::TextualizeLA32GPR(gpr_index) << " <= ";

                switch (i)
                {
                    case 0:
                        oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << traceContent.value;
                        break;

                    case 1:
                        oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << traceContent.value_second;
                        break;

                    default:
                        oss << "<malformed-trait>";
                        break;
                }

                break;
            }

            case Jasse::LA32Trait::Destination::Type::PC: {

                oss << "PC   <= ";

                switch (i)
                {
                    case 0:
                        oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << traceContent.value;
                        break;

                    case 1:
                        oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << traceContent.value_second;
                        break;

                    default:
                        oss << "<malformed-trait>";
                }

                break;
            }

            case Jasse::LA32Trait::Destination::Type::Memory: {

                const Jasse::LA32Trait::Destination::Memory* dst_mem = 
                    static_cast<const Jasse::LA32Trait::Destination::Memory*>(dst);

                switch (dst_mem->GetMemoryType())
                {
                    case Jasse::LA32Trait::Destination::Memory::MemoryType::NormalStore: {

                        if (trait->GetDestinationCount() <= ++i)
                        {
                            oss << "<malformed-trait>";
                            break;
                        }

                        if (trait->GetDestination(i)->GetType() !=
                            Jasse::LA32Trait::Destination::Type::Memory)
                        {
                            oss << "<malformed-trait>";
                            break;
                        }

                        const Jasse::LA32Trait::Destination::Memory* dst_mem2 = 
                            static_cast<const Jasse::LA32Trait::Destination::Memory*>(trait->GetDestination(i));

                        if (dst_mem2->GetMemoryType() != 
                            Jasse::LA32Trait::Destination::Memory::MemoryType::NormalStoreAddress)
                        {
                            oss << "<malformed-trait>";
                            break;
                        }

                        oss << "*(0x";
                        oss << std::hex << std::setw(8) << std::setfill('0') << traceContent.value_second;
                        oss << ") <= ";
                        oss << std::hex << std::setw(8) << std::setfill('0') << traceContent.value;

                        break;
                    }

                    case Jasse::LA32Trait::Destination::Memory::MemoryType::NormalLoadAddress: {

                        switch (i)
                        {
                            case 0:
                                oss << "*(0x";
                                oss << std::hex << std::setw(8) << std::setfill('0') << traceContent.value;
                                oss << ")";
                                break;

                            case 1:
                                oss << "*(0x";
                                oss << std::hex << std::setw(8) << std::setfill('0') << traceContent.value_second;
                                oss << ")";
                                break;

                            default:
                                oss << "<malformed-trait>";
                                break;
                        }

                        break;
                    }

                    default:
                        oss << "<malformed-trait>";
                        break;
                }

                break;
            };

            default:
                oss << "<malformed-trait>";
                break;
        }
    }

    //
    oss << "; ";

    //
    int padding = 40 - oss.view().length();

    for (int i = 0; i < padding; i++)
        oss << " ";

    // display operand traces
    for (int i = 0; i < trait->GetOperandCount(); i++)
    {
        if (i)
            oss << ", ";

        const Jasse::LA32Trait::Operand* opd = trait->GetOperand(i);

        switch (opd->GetType())
        {
            case Jasse::LA32Trait::Operand::Type::GPR: {

                const Jasse::LA32Trait::Operand::GPR* opd_gpr = 
                    static_cast<const Jasse::LA32Trait::Operand::GPR*>(opd);

                unsigned int gpr_index = opd_gpr->GetGPRIndex(traceContent.insn);

                oss << Jasse::TextualizeLA32GPR(gpr_index) << " = ";

                if (!gpr_index)
                {
                    oss << "0x00000000";
                    break;
                }

                //
                Jasse::LA32TraceEntity::Reference operandTrace;
                if (i == 0)
                    operandTrace = traceContent.GetTracedFirstOperand(*executionTrace);
                else if (i == 1)
                    operandTrace = traceContent.GetTracedSecondOperand(*executionTrace);
                else
                {
                    oss << "<malformed-trait>";
                    break;
                }

                if (!operandTrace.IsValid())
                {
                    oss << "<out-of-trace>";
                    break;
                }

                if (!operandTrace->GetContentType()->HasTracedArch32Value())
                {
                    oss << "<unrecognized-trace>";
                    break;
                }

                oss << "0x";
                oss << std::hex << std::setw(8) << std::setfill('0') 
                    << operandTrace->GetContentType()->GetTracedArch32Value(operandTrace->GetContent());

                break;
            }

            default:
                oss << "<malformed-trait>";
                break;
        }
    }


    //
    return oss.str();
}


static inline std::string dump_trace_incomplete_at(Jasse::addr_t address)
{
    //
    Jasse::memdata_t data;
    Jasse::LA32MOPOutcome mopoutcome 
        = glbl.ctx.ref.soc->MMU().ReadInsn(address, Jasse::MOPW_WORD, &data);

    if (mopoutcome.status != Jasse::LA32MOPStatus::MOP_SUCCESS)
        return "";

    //
    Jasse::LA32Instruction insn(data.data32);
    
    if (!Jasse::Decoder::LA32R_NSCSCC->Decode(insn))
        return "";

    //
    const Jasse::LA32Trait* trait = insn.GetCodepoint()->GetTrait();

    if (!trait)
        return "<unrecognized-trait>";

    //
    std::ostringstream oss;

    // display destination traces
    for (int i = 0; i < trait->GetDestinationCount(); i++)
    {
        if (i)
            oss << ", ";

        const Jasse::LA32Trait::Destination* dst = trait->GetDestination(i);

        switch (dst->GetType())
        {
            case Jasse::LA32Trait::Destination::Type::GPR: {

                const Jasse::LA32Trait::Destination::GPR* dst_gpr = 
                    static_cast<const Jasse::LA32Trait::Destination::GPR*>(dst);

                unsigned int gpr_index = dst_gpr->GetGPRIndex(insn);

                oss << Jasse::TextualizeLA32GPR(gpr_index) << " <= ";
                oss << "<incomplete>";

                break;
            }

            case Jasse::LA32Trait::Destination::Type::PC: {

                oss << "PC   <= <incomplete>";
                break;
            }

            case Jasse::LA32Trait::Destination::Type::Memory: {

                oss << "<incomplete>";
                break;
            }

            default:
                oss << "<malformed-trait>";
                break;
        }
    }


    //
    oss << "; ";

    //
    int padding = 40 - oss.view().length();

    for (int i = 0; i < padding; i++)
        oss << " ";

    
    // display operand traces
    for (int i = 0; i < trait->GetOperandCount(); i++)
    {
        if (i)
            oss << ", ";

        const Jasse::LA32Trait::Operand* opd = trait->GetOperand(i);

        switch (opd->GetType())
        {
            case Jasse::LA32Trait::Operand::Type::GPR: {

                const Jasse::LA32Trait::Operand::GPR* opd_gpr = 
                    static_cast<const Jasse::LA32Trait::Operand::GPR*>(opd);

                unsigned int gpr_index = opd_gpr->GetGPRIndex(insn);

                oss << Jasse::TextualizeLA32GPR(gpr_index) << " = ";

                if (!gpr_index)
                {
                    oss << "0x00000000";
                    break;
                }

                //
                if (!glbl.ctx.ref.emu->Tracers().HasGPRTracer())
                {
                    oss << "<out-of-trace>";
                    break;
                }

                auto gprTracer = glbl.ctx.ref.emu->Tracers().GetGPRTracer();

                //
                Jasse::LA32TraceEntity::Reference operandTrace;

                // *NOTICE: Instruction itself is already commited in EMU side at this time.
                //          Search trait of destination to uncover the source operand value.
                //
                int traceOffset = 0;
                for (int i = 0; i < trait->GetDestinationCount(); i++)
                {
                    const Jasse::LA32Trait::Destination* dst = trait->GetDestination(i);

                    if (dst->GetType() == Jasse::LA32Trait::Destination::Type::GPR)
                    {
                        const Jasse::LA32Trait::Destination::GPR* dst_gpr = 
                                static_cast<const Jasse::LA32Trait::Destination::GPR*>(dst);

                        if (dst_gpr->GetGPRIndex(insn) == gpr_index)
                            traceOffset++;
                    }
                }

                if (traceOffset >= gprTracer->Get(gpr_index).GetCount())
                {
                    oss << "<out-of-trace>";
                    break;
                }

                operandTrace = gprTracer->Get(gpr_index).Get(traceOffset);

                if (!operandTrace.IsValid())
                {
                    oss << "<out-of-trace>";
                    break;
                }

                if (!operandTrace->GetContentType()->HasTracedArch32Value())
                {
                    oss << "<unrecognized-trace>";
                    break;
                }

                oss << "0x";
                oss << std::hex << std::setw(8) << std::setfill('0') 
                    << operandTrace->GetContentType()->GetTracedArch32Value(operandTrace->GetContent());

                break;

                break;
            }

            default:
                oss << "<malformed-trait>";
                break;
        }
    }

    return oss.str();
}


//
static inline std::string dump_mmio_target(Jasse::LA32MOPPath path, Jasse::addr_t address)
{
    switch (path)
    {
        case Jasse::LA32MOPPath::MOP_DATA: {

            if (BullsEye::NSCSCCSingle::NSCSCC2023MMU::IsBaseRAM(address))
                return "BaseRAM";

            if (BullsEye::NSCSCCSingle::NSCSCC2023MMU::IsExtRAM(address))
                return "ExtRAM";

            if (BullsEye::NSCSCCSingle::NSCSCC2023MMU::IsSerial(address))
            {
                if (BullsEye::NSCSCCSingle::NSCSCC2023MMU::IsSerialData(address))
                    return "SerialData";

                if (BullsEye::NSCSCCSingle::NSCSCC2023MMU::IsSerialStat(address))
                    return "SerialStat";
            }

            if (BullsEye::NSCSCCSingle::NSCSCC2023MMU::IsClockCounter(address))
                return "ClockCounter";

            break;
        }

        case Jasse::LA32MOPPath::MOP_INSN: {

            if (BullsEye::NSCSCCSingle::NSCSCC2023MMU::IsBaseRAM(address))
                return "BaseRAM";

            if (BullsEye::NSCSCCSingle::NSCSCC2023MMU::IsExtRAM(address))
                return "ExtRAM";

            break;
        }

        default:
            break;
    }

    std::ostringstream unkoss;
    unkoss << "<unknown(path=";
    unkoss << std::dec << uint64_t(path);
    unkoss << ",address=0x";
    unkoss << std::hex << std::setw(8) << std::setfill('0') << address;
    unkoss << ")>";
    return unkoss.str();
}


//
void dump(bool pause)
{
    dump0(pause);
    dump1(pause);
    dump2();
    dump3();
    dump4();
}


//
void dump0(bool pause)
{
    if (!glbl.cfg.dump0.enabled)
        return;

    std::cout << "\033[1;33mEmulation dumped\033[0m from reference (dump #0: program memory)" << std::endl;
    std::cout << "Program stopped at: " << std::endl;

    int j = std::min(int32_t(glbl.ctx.commitCount) - 1, int32_t(glbl.cfg.dump0.upperCount));
    for (; j > 0; j--)
    {
    //  std::cout << _COLOR_CORRECT;
        std::cout << "    ";
        std::cout << dump_at(glbl.ctx.lastPC - (j << 2));
        std::cout << _COLOR_RESET << std::endl;
    }

    std::cout << (pause ? _COLOR_PAUSE : _COLOR_ERROR);
    std::cout << "--> ";
    std::cout << dump_at(glbl.ctx.lastPC);
    std::cout << _COLOR_RESET << std::endl;

    for (int i = 0; i < glbl.cfg.dump0.lowerCount; i++)
    {
        std::cout << "    ";
        std::cout << dump_at(glbl.ctx.lastPC + ((i + 1) << 2));
        std::cout << std::endl;
    }

    std::cout << "--------------------------------" << std::endl;
}


//
void dump1(bool pause)
{
    if (!glbl.cfg.dump1.enabled)
        return;

    std::cout << "\033[1;33mEmulation dumped\033[0m from reference (dump #1: program execution trace)" << std::endl;
    std::cout << "Program stopped at: " << std::endl;

    int j = std::min(int32_t(glbl.ctx.commitCount) - 1, int32_t(glbl.cfg.dump1.upperCount));
    for (; j > 0; j--)
    {
        std::cout << _COLOR_CORRECT;
        std::cout << "    ";
        std::cout << dump_at(glbl.ctx.dut.history.PC->Get(j));
        std::cout << _COLOR_RESET << std::endl;

        if (glbl.cfg.dump1.displayTrace)
        {
            std::cout << _COLOR_COMMENT;
            std::cout << "  # ";
            std::cout << dump_trace_at(glbl.ctx.dut.history.PC->Get(j), j);
            std::cout << _COLOR_RESET << std::endl;
        }
    }

    std::cout << (pause ? _COLOR_PAUSE : _COLOR_ERROR);
    std::cout << "--> ";
    std::cout << dump_at(glbl.ctx.dut.history.PC->Get(0));
    std::cout << _COLOR_RESET << std::endl;

    if (glbl.cfg.dump1.displayTrace)
    {
        std::cout << _COLOR_COMMENT;
        std::cout << "  # ";
        std::cout << dump_trace_at(glbl.ctx.dut.history.PC->Get(0), 0);
        std::cout << _COLOR_RESET << std::endl;
    }

    for (int i = 0; i < glbl.cfg.dump1.lowerCount; i++)
    {
        std::cout << "    ";
        std::cout << dump_at(glbl.ctx.lastPC + ((i + 1) << 2));
        std::cout << std::endl;
    }

    std::cout << "--------------------------------" << std::endl;
}


//
void dump2()
{
    if (!glbl.cfg.dump2.enabled)
        return;

    std::cout << "\033[1;33mEmulation dumped\033[0m from reference (dump #2: DUT memory access)" << std::endl;

    int j = std::min(int32_t(glbl.ctx.dut.history.MMIOReadWrite->GetCount()), int32_t(glbl.cfg.dump2.depth)) - 1;
    for (; j >= 0; j--)
    {
        std::ostringstream oss;

        //
        const MMIOHistory::Entry& entry = glbl.ctx.dut.history.MMIOReadWrite->Get(j);

        if (entry.GetOutcome().status == Jasse::LA32MOPStatus::MOP_SUCCESS)
            oss << _COLOR_CORRECT;
        else
            oss << _COLOR_ERROR;

        //
        oss << "  [MMU ";
        if (entry.GetType() == MMIOHistory::Entry::Type::READ)
            oss << "<- ";
        else
            oss << "-> ";

        std::string target = dump_mmio_target(entry.GetPath(), entry.GetAddress());
        oss << target;
        for (int i = target.length(); i < 12; i++)
            oss << " ";
        oss << "] ";

        //
        if (entry.GetType() == MMIOHistory::Entry::Type::READ)
            oss << "Read  ";
        else
            oss << "Write ";
        oss << "at ";

        //
        oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << entry.GetAddress() << " ";

        //
        if (entry.GetType() == MMIOHistory::Entry::Type::READ)
            oss << "=> ";
        else
            oss << "<= ";

        oss << _COLOR_COMMENT;
        oss << "(" << std::dec << entry.GetWidth().length << " byte(s)) ";

        if (entry.GetOutcome().status == Jasse::LA32MOPStatus::MOP_SUCCESS)
        {
            switch (entry.GetWidth().length)
            {
                case 1:
                    oss << _COLOR_COMMENT;
                    oss << "000000";
                    oss << _COLOR_CORRECT;
                    oss << std::hex << std::setw(2) << std::setfill('0') << uint32_t(entry.GetData().data8);
                    break;

                case 2:
                    oss << _COLOR_COMMENT;
                    oss << "0000";
                    oss << _COLOR_CORRECT;
                    oss << std::hex << std::setw(4) << std::setfill('0') << uint32_t(entry.GetData().data16);
                    break;

                case 4:
                    oss << _COLOR_CORRECT;
                    oss << std::hex << std::setw(8) << std::setfill('0') << uint32_t(entry.GetData().data32);
                    break;

                default:
                    oss << std::hex << std::setw(8) << std::setfill('0') << uint32_t(entry.GetData().data32);
            }
        }
        else
            oss << "00000000";


        //
        oss << _COLOR_RESET << std::endl;

        //
        std::cout << oss.str();
    }

    std::cout << "--------------------------------" << std::endl;
}


// 
void dump3()
{
    if (!glbl.cfg.dump3.enabled)
        return;

    std::cout << "\033[1;33mEmulation dumped\033[0m from reference (dump #3: Reference memory access)" << std::endl;

    int j = std::min(int32_t(glbl.ctx.dut.history.MMIOReadWrite->GetCount()), int32_t(glbl.cfg.dump2.depth)) - 1;
    for (; j >= 0; j--)
    {
        std::ostringstream oss;

        //
        const MMIOHistory::Entry& entry = glbl.ctx.dut.history.MMIOReadWrite->Get(j);

        if (entry.GetOutcome().status == Jasse::LA32MOPStatus::MOP_SUCCESS)
            oss << _COLOR_CORRECT;
        else
            oss << _COLOR_ERROR;

        //
        oss << "  [MMU ";
        if (entry.GetType() == MMIOHistory::Entry::Type::READ)
            oss << "<- ";
        else
            oss << "-> ";

        std::string target = dump_mmio_target(entry.GetPath(), entry.GetAddress());
        oss << target;
        for (int i = target.length(); i < 12; i++)
            oss << " ";
        oss << "] ";

        //
        if (entry.GetType() == MMIOHistory::Entry::Type::READ)
            oss << "Read  ";
        else
            oss << "Write ";
        oss << "at ";

        //
        oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << entry.GetAddress() << " ";

        //
        if (entry.GetType() == MMIOHistory::Entry::Type::READ)
            oss << "=> ";
        else
            oss << "<= ";

        oss << _COLOR_COMMENT;
        oss << "(" << std::dec << entry.GetWidth().length << " byte(s)) ";

        if (entry.GetOutcome().status == Jasse::LA32MOPStatus::MOP_SUCCESS)
        {
            switch (entry.GetWidth().length)
            {
                case 1:
                    oss << _COLOR_COMMENT;
                    oss << "000000";
                    oss << _COLOR_CORRECT;
                    oss << std::hex << std::setw(2) << std::setfill('0') << uint32_t(entry.GetData().data8);
                    break;

                case 2:
                    oss << _COLOR_COMMENT;
                    oss << "0000";
                    oss << _COLOR_CORRECT;
                    oss << std::hex << std::setw(4) << std::setfill('0') << uint32_t(entry.GetData().data16);
                    break;

                case 4:
                    oss << _COLOR_CORRECT;
                    oss << std::hex << std::setw(8) << std::setfill('0') << uint32_t(entry.GetData().data32);
                    break;

                default:
                    oss << std::hex << std::setw(8) << std::setfill('0') << uint32_t(entry.GetData().data32);
            }
        }
        else
            oss << "00000000";


        //
        oss << _COLOR_RESET << std::endl;

        //
        std::cout << oss.str();
    }

    std::cout << "--------------------------------" << std::endl;
}


//
void dump4()
{
    if (!glbl.cfg.dump4.enabled)
        return;

    std::cout << "\033[1;33mEmulation dumped\033[0m from reference (dump #4: DUT AXI transactions)" << std::endl;

    int j = std::min(int32_t(glbl.ctx.dut.history.busAXI->GetCount()), int32_t(glbl.cfg.dump4.depth));

    for (; j >= 0; j--)
    {
        auto& transaction = glbl.ctx.dut.history.busAXI->Get(j);
        auto& transmissions = transaction.GetTransmissions();

        //
        std::ostringstream oss;
        
        //
        oss << "  ";

        if (transaction.GetType() == AXIBusHistory::Transaction::Type::READ)
        {
            if ((uint32_t(transaction.GetLength()) + 1) != transmissions.size())
                oss << _COLOR_PAUSE;
            else
            {
                auto& last_trans = transmissions.back();

                if (last_trans.GetType() != AXIBusHistory::Transmission::Type::DATA_READ)
                    oss << _COLOR_ERROR;
                else if (!last_trans.GetLast())
                    oss << _COLOR_ERROR;
                else if (last_trans.GetReadResponse() != BullsEye::AXI4::Attributes::RRESP_OKAY)
                    oss << _COLOR_ERROR;
                else
                    oss << _COLOR_CORRECT;
            }
        }
        else if (transaction.GetType() == AXIBusHistory::Transaction::Type::WRITE)
        {
            if ((uint32_t(transaction.GetLength()) + 2) != transmissions.size())
                oss << _COLOR_PAUSE;
            else
            {
                auto& last_trans = transmissions.back();

                if (last_trans.GetType() != AXIBusHistory::Transmission::Type::RESPONSE_WRITE)
                    oss <<  _COLOR_ERROR;
                else if (last_trans.GetWriteResponse() != BullsEye::AXI4::Attributes::BRESP_OKAY)
                    oss << _COLOR_ERROR;
                else
                    oss << _COLOR_CORRECT;
            }
        }
        else
            oss << _COLOR_COMMENT;

        oss << "[";
        switch (transaction.GetPath())
        {
            case AXIBusHistory::Transaction::Path::INSN:
                oss << "Fetch";
                break;

            case AXIBusHistory::Transaction::Path::DATA:
                oss << "Data";
                break;

            default:
                oss << "Unknown";
                break;
        }

        oss << " ";
        switch (transaction.GetType())
        {
            case AXIBusHistory::Transaction::Type::READ:
                oss << "Read ";
                break;

            case AXIBusHistory::Transaction::Type::WRITE:
                oss << "Write";
                break;

            default:
                oss << "Action";
                break;
        }
        oss << "] ";

        oss << "[id = ";
        oss <<  std::dec << std::setw(2) << uint32_t(transaction.GetId());
        oss << "] ";

        oss << "Address = 0x";
        oss << std::hex << std::setw(8) << std::setfill('0') << transaction.GetAddress();
        oss << ", ";

        oss << "Burst = ";
        switch (transaction.GetBurst())
        {
            case BullsEye::AXI4::Attributes::AXBURST_FIXED: oss << "FIXED";     break;
            case BullsEye::AXI4::Attributes::AXBURST_INCR:  oss << "INCR ";      break;
            case BullsEye::AXI4::Attributes::AXBURST_WRAP:  oss << "WRAP ";      break;

            default:
                oss << "<unknown(burst=";
                oss << uint32_t(transaction.GetBurst());
                oss << ")>";
        }
        oss << ", ";

        oss << "Size = ";
        switch (transaction.GetSize())
        {
            case BullsEye::AXI4::Attributes::AXSIZE_1B:     oss << "1B  ";    break;
            case BullsEye::AXI4::Attributes::AXSIZE_2B:     oss << "2B  ";    break;
            case BullsEye::AXI4::Attributes::AXSIZE_4B:     oss << "4B  ";    break;
            case BullsEye::AXI4::Attributes::AXSIZE_8B:     oss << "8B  ";    break;
            case BullsEye::AXI4::Attributes::AXSIZE_16B:    oss << "16B ";   break;
            case BullsEye::AXI4::Attributes::AXSIZE_32B:    oss << "32B ";   break;
            case BullsEye::AXI4::Attributes::AXSIZE_64B:    oss << "64B ";   break;
            case BullsEye::AXI4::Attributes::AXSIZE_128B:   oss << "128B";  break;

            default:
                oss << "<unknown(size=";
                oss << uint32_t(transaction.GetSize());
                oss << ")>";
        }
        oss << ", ";

        oss << "Length = ";
        oss << std::dec << (uint32_t(transaction.GetLength()) + 1);
        oss << " ";

        oss << _COLOR_COMMENT;
        oss << "(";
        oss << std::dec << uint32_t(transmissions.size());
        oss << " of ";
        switch (transaction.GetType())
        {
            case AXIBusHistory::Transaction::Type::WRITE:
                oss << std::dec << uint32_t(uint32_t(transaction.GetLength()) + 2);
                break;

            default:
                oss << std::dec << uint32_t(uint32_t(transaction.GetLength()) + 1);
                break;
        }
        oss << ")";
        
        std::cout << oss.str() << _COLOR_RESET << std::endl;

        //
        for (auto& transmission : transmissions)
        {
            //
            oss = std::ostringstream();
            oss << "    ";

            //
            oss << "[";
            switch (transmission.GetType())
            {
                case AXIBusHistory::Transmission::Type::DATA_READ:
                    oss << "M <- S] [R] ";
                    
                    oss << "Data = 0x";
                    switch (transaction.GetSize())
                    {
                        case BullsEye::AXI4::Attributes::AXSIZE_1B:
                            switch (transaction.GetAddress() & 0x00000003)
                            {
                                case 0:
                                    oss << _COLOR_COMMENT << std::hex << std::setw(6) << std::setfill('0') << ((transmission.GetData() & 0xFFFFFF00) >> 8 );
                                    oss << _COLOR_RESET   << std::hex << std::setw(2) << std::setfill('0') << ((transmission.GetData() & 0x000000FF));
                                    break;

                                case 1:
                                    oss << _COLOR_COMMENT << std::hex << std::setw(4) << std::setfill('0') << ((transmission.GetData() & 0xFFFF0000) >> 16);
                                    oss << _COLOR_RESET   << std::hex << std::setw(2) << std::setfill('0') << ((transmission.GetData() & 0x0000FF00) >> 8 );
                                    oss << _COLOR_COMMENT << std::hex << std::setw(2) << std::setfill('0') << ((transmission.GetData() & 0x000000FF));
                                    break;

                                case 2:
                                    oss << _COLOR_COMMENT << std::hex << std::setw(2) << std::setfill('0') << ((transmission.GetData() & 0xFF000000) >> 24);
                                    oss << _COLOR_RESET   << std::hex << std::setw(2) << std::setfill('0') << ((transmission.GetData() & 0x00FF0000) >> 16);
                                    oss << _COLOR_COMMENT << std::hex << std::setw(4) << std::setfill('0') << ((transmission.GetData() & 0x0000FFFF));
                                    break;

                                case 3:
                                    oss << _COLOR_RESET   << std::hex << std::setw(2) << std::setfill('0') << ((transmission.GetData() & 0xFF000000) >> 24);
                                    oss << _COLOR_COMMENT << std::hex << std::setw(6) << std::setfill('0') << ((transmission.GetData() & 0x00FFFFFF));
                                    break;

                                default:
                                    break;
                            }

                            break;

                        case BullsEye::AXI4::Attributes::AXSIZE_2B:
                            switch (transaction.GetAddress() & 0x00000002)
                            {
                                case 0:
                                    oss << _COLOR_COMMENT << std::hex << std::setw(4) << std::setfill('0') << ((transmission.GetData() & 0xFFFF0000) >> 16);
                                    oss << _COLOR_RESET   << std::hex << std::setw(4) << std::setfill('0') << ((transmission.GetData() & 0x0000FFFF));
                                    break;

                                case 2:
                                    oss << _COLOR_RESET   << std::hex << std::setw(4) << std::setfill('0') << ((transmission.GetData() & 0xFFFF0000) >> 16);
                                    oss << _COLOR_COMMENT << std::hex << std::setw(4) << std::setfill('0') << ((transmission.GetData() & 0x0000FFFF));

                                default:
                                    break;
                            }

                            break;

                        default:
                            oss << std::hex << std::setw(8) << std::setfill('0') << transmission.GetData();
                            break;
                    }


                    if (transmission.GetLast())
                    {
                        oss << ", " << _COLOR_SPECIAL << "Last" << _COLOR_RESET;

                        oss << ", " << "Resp = ";
                        switch (transmission.GetReadResponse())
                        {
                            case BullsEye::AXI4::Attributes::RRESP_OKAY:        oss << _COLOR_CORRECT << "OKAY";     break;
                            case BullsEye::AXI4::Attributes::RRESP_EXOKAY:      oss << _COLOR_SPECIAL << "EXOKAY";   break;
                            case BullsEye::AXI4::Attributes::RRESP_SLVERR:      oss << _COLOR_ERROR   << "SLVERR";   break;
                            case BullsEye::AXI4::Attributes::RRESP_DECERR:      oss << _COLOR_ERROR   << "DECERR";   break;
                            case BullsEye::AXI4::Attributes::RRESP_PREFETCHED:  oss << _COLOR_SPECIAL << "PREFETCHED"; break;
                            case BullsEye::AXI4::Attributes::RRESP_TRANSFAULT:  oss << _COLOR_ERROR   << "TRANSFAULT"; break;
                            case BullsEye::AXI4::Attributes::RRESP_OKAYDIRTY:   oss << _COLOR_SPECIAL << "OKAYDIRTY"; break;

                            default:
                                oss << "<unknown(rresp=0x";
                                oss << std::hex << transmission.GetReadResponse();
                                oss << ")>";
                        }
                    }

                    break;

                case AXIBusHistory::Transmission::Type::DATA_WRITE:
                    oss << "M -> S] [W] ";

                    oss << "Data = 0x";
                    for (int i = 3; i >= 0; i--)
                    {
                        oss << (transmission.GetWriteStrobe()[i] ? _COLOR_RESET : _COLOR_COMMENT);
                        oss << std::hex << std::setw(2) << std::setfill('0') << (transmission.GetData() >> (8 * i));
                    }
                    /*
                    oss << ", ";

                    oss << "Strobe = 0b";
                    for (int i = 3; i >= 0; i--)
                    {
                        oss << (transmission.GetWriteStrobe()[i] ? "1" : "0");
                    }
                    */
                    
                    if (transmission.GetLast())
                    {
                        oss << ", " << _COLOR_SPECIAL << "Last" << _COLOR_RESET;
                    }

                    break;

                case AXIBusHistory::Transmission::Type::RESPONSE_WRITE:
                    oss << "M <- S] [B] ";

                    oss << "Resp = ";
                    switch (transmission.GetWriteResponse())
                    {
                        case BullsEye::AXI4::Attributes::BRESP_OKAY:        oss << _COLOR_CORRECT << "OKAY";        break;
                        case BullsEye::AXI4::Attributes::BRESP_EXOKAY:      oss << _COLOR_SPECIAL << "EXOKAY";      break;
                        case BullsEye::AXI4::Attributes::BRESP_SLVERR:      oss << _COLOR_ERROR   << "SLVERR";      break;
                        case BullsEye::AXI4::Attributes::BRESP_DECERR:      oss << _COLOR_ERROR   << "DECERR";      break;
                        case BullsEye::AXI4::Attributes::BRESP_DEFER:       oss << _COLOR_SPECIAL << "DEFER";       break;
                        case BullsEye::AXI4::Attributes::BRESP_TRANSFAULT:  oss << _COLOR_ERROR   << "TRANSFAULT";  break;
                        case BullsEye::AXI4::Attributes::BRESP_UNSUPPORTED: oss << _COLOR_ERROR   << "UNSUPPORTED"; break;

                        default:
                            oss << "<unknown(rresp=0x";
                            oss << std::hex << transmission.GetWriteResponse();
                            oss << ")>";
                    }

                    break;

                default:
                    oss << "? -> ?] unknown";
                    break;
            }

            //
            std::cout << oss.str() << _COLOR_RESET << std::endl;
        }
    }

    std::cout << "--------------------------------" << std::endl;
}
