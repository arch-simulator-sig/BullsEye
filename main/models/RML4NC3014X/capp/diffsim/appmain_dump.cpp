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
            return std::string();
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
    int padding = 36 - oss.view().length();

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


//
void dump()
{
    dump0();
    dump1();
}


//
void dump0()
{
    std::cout << "\033[1;33mEmulation dumped\033[0m (dump #0: program memory)" << std::endl;
    std::cout << "Program stopped at: " << std::endl;

    int j = (uint32_t) std::min(glbl.ctx.commitCount, uint64_t(glbl.cfg.dump0.upperCount));
    for (; j > 0; j--)
    {
    //  std::cout << _COLOR_CORRECT;
        std::cout << "    ";
        std::cout << dump_at(glbl.ctx.lastPC - (j << 2));
        std::cout << _COLOR_RESET << std::endl;
    }

    std::cout << _COLOR_ERROR;
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
void dump1()
{
    std::cout << "\033[1;33mEmulation dumped\033[0m (dump #1: program execution trace)" << std::endl;
    std::cout << "Program stopped at: " << std::endl;

    int j = (uint32_t) std::min(glbl.ctx.commitCount, uint64_t(glbl.cfg.dump1.upperCount));
    for (; j > 0; j--)
    {
        std::cout << _COLOR_CORRECT;
        std::cout << "    ";
        std::cout << dump_at(glbl.ctx.tracePC.Get(j));
        std::cout << _COLOR_RESET << std::endl;

        if (glbl.cfg.dump1.displayTrace)
        {
            std::cout << _COLOR_COMMENT;
            std::cout << "  # ";
            std::cout << dump_trace_at(glbl.ctx.tracePC.Get(j), j);
            std::cout << _COLOR_RESET << std::endl;
        }
    }

    std::cout << _COLOR_ERROR;
    std::cout << "--> ";
    std::cout << dump_at(glbl.ctx.tracePC.Get(0));
    std::cout << _COLOR_RESET << std::endl;

    for (int i = 0; i < glbl.cfg.dump1.lowerCount; i++)
    {
        std::cout << "    ";
        std::cout << dump_at(glbl.ctx.lastPC + ((i + 1) << 2));
        std::cout << std::endl;
    }

    std::cout << "--------------------------------" << std::endl;
}
