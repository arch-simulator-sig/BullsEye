#include "appmain.hpp"              // IWYU pragma: keep

#include <iostream>
#include <sstream>
#include <iomanip>

#include "appmain_glbl.hpp"
#include "appmain_config.hpp"
#include "appmain_startup.hpp"


#include "../../csrc/core/ds232_diff.hpp"

#include "autoinclude.h"

#include AUTOINC_BE_JASSE2_LA32(base/la32def.hpp)


int main(int argc, char* argv[])
{
    using namespace BullsEye;
    using namespace BullsEye::NSCSCCSingle;

    int stage_return;

    // config stage
    if ((stage_return = config(argc, argv)))
        return stage_return;

    // startup stage
    if ((stage_return = startup()))
        return stage_return;
    


    std::cout << "--------------------------------" << std::endl;

    // Emulation cycles
    std::cout << "\033[1;33mStarted verilated emulation of DS232 on NSCSCC2023 AXI SoC.\033[0m" << std::endl;

    std::cout << "Reset cycle (1) elapsed." << std::endl;
    glbl.ctx.dut.dut->NextReset();
    glbl.ctx.dut.dut->Eval();

    int counter_progressbar = 0;

    auto last_time = std::chrono::system_clock::now();
    unsigned long long cps = 0;

    pc_t last_pc;

    int counter_interval = 0;
    while (1)
    {
        glbl.ctx.dut.dut->Eval();

        // update pc
        {
            Draconids3014::DS232IncrementVectorPC& incr = glbl.ctx.dut.diff->GetIncrementPC();

            if (!incr.IsEmpty())
                last_pc = incr.GetLast().GetPC();
        }


        // update reference
        {
            Draconids3014::DS232IncrementVectorPC& incr = glbl.ctx.dut.diff->GetIncrementPC();

            for (int i = 0; i < incr.GetCount(); i++)
            {
                glbl.ctx.ref.emu->Eval();
            }
        }


        // update console
        if (counter_interval == 6000 
        ||  counter_interval == 12000 
        ||  counter_interval == 18000)
        {
            std::ostringstream oss;
            oss << "\033[K";
            oss << "Emulation speed: \033[1;33m";
            oss << std::setw(12) << std::setfill(' ') << cps;
            oss << "\033[0m cycles/second";
            oss << "  ";
            oss << ANIMATE_INF_PROGRESS_BAR[counter_progressbar];
            oss << "\nLast commit PC: \033[1;33m0x" << std::hex << std::setw(8) << std::setfill(' ') << last_pc << "\033[0m" << std::endl;
            oss << "\033[1A\033[1A";

            counter_progressbar = ++counter_progressbar % ANIMATE_INF_PROGRESS_BAR_SIZE;

            std::cout << oss.str();
        }

        if (counter_interval == 18000)
        {
            counter_interval = 0;

            auto now_time = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now_time - last_time);

            last_time = now_time;

            cps = (18000ULL * 1000ULL) / duration.count();
        }
        else
            counter_interval++;
    }
    
    //

    // TODO


    shutdown();

    return 0;
}


