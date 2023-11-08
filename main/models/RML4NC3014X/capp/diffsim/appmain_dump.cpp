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


#include "autoinclude.h"

#include AUTOINC_BE_JASSE2_LA32(la32_nscscc.hpp)    // IWYU pragma: keep


//
static constexpr const char* _COLOR_CORRECT  = "\033[1;32m";

static constexpr const char* _COLOR_ERROR    = "\033[1;31m";

static constexpr const char* _COLOR_RESET    = "\033[0m";


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

    for (int i = 0; i < glbl.cfg.dump0.upperCount; i++)
    {
        if ((glbl.ctx.commitCount - glbl.cfg.dump0.upperCount + i) > 0)
        {
        //  std::cout << _COLOR_CORRECT;
            std::cout << "    ";
            std::cout << dump_at(glbl.ctx.lastPC - ((glbl.cfg.dump0.upperCount - i) << 2));
            std::cout << _COLOR_RESET << std::endl;
        }
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

    for (int i = 0; i < glbl.cfg.dump1.upperCount; i++)
    {
        if ((glbl.ctx.commitCount - glbl.cfg.dump1.upperCount + i) > 0)
        {
            std::cout << _COLOR_CORRECT;
            std::cout << "    ";
            std::cout << dump_at(glbl.ctx.tracePC.Get(glbl.cfg.dump1.upperCount - i));
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
