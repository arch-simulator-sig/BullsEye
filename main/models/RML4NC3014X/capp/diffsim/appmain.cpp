#include "appmain.hpp"              // IWYU pragma: keep

#include <iostream>
#include <sstream>
#include <iomanip>

#include "appmain_glbl.hpp"
#include "appmain_config.hpp"
#include "appmain_startup.hpp"
#include "appmain_dump.hpp"


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

    bool coninfo_first_time = true;

    auto last_time = std::chrono::system_clock::now();
    unsigned long long cps = 0;

    pc_t last_pc;

    uint64_t    counter_cycle       = 0;
    uint64_t    counter_commit      = 0;

    uint64_t    counter_dualcommit  = 0;

    uint64_t    counter_interval_commit = 0;

    int counter_interval = 0;
    while (1)
    {
        glbl.ctx.dut.dut->Eval();

        counter_cycle++;

        // update reference
        {
            Draconids3014::DS232IncrementVectorPC& incr = glbl.ctx.dut.diff->GetIncrementPC();

            // commit watchdog
            if (incr.IsEmpty())
                counter_interval_commit++;
            else
                counter_interval_commit = 0;

            // commit counter
            counter_commit += incr.GetCount();

            // dual commit counter
            if (incr.GetCount() == 2)
                counter_dualcommit++;

            // reference
            for (size_t i = 0; i < incr.GetCount(); i++)
            {
                glbl.ctx.ref.emu->Eval();

                if (!incr.IsEmpty())
                {
                    glbl.ctx.lastPC = last_pc = incr.Get(i).GetPC();
                    glbl.ctx.dut.history.PC->Push(last_pc);
                    glbl.ctx.commitCount++;
                }

                // difftest
                glbl.ctx.verifier->Verify(i);

                // check error
                if (!glbl.err.captured.empty())
                {
                    std::ostringstream oss;

                    std::cout << "--------------------------------" << std::endl;
                    std::cout << "\033[1;31mEmulation stopped\033[0m due to error(s)." << std::endl;
                    std::cout << "Captured " << glbl.err.captured.size() << " error(s) in total." << std::endl;
                    std::cout << "Error reported in detail in follow-up." << std::endl;

                    oss << "\nLast commit PC: \033[1;33m0x" << std::hex << std::setw(8) << std::setfill(' ') << last_pc << "\033[0m" << std::endl;
                    std::cout << oss.str();

                    std::cout << "--------------------------------" << std::endl;
                    for (size_t j = 0; j < glbl.err.captured.size(); j++)
                    {
                        std::cout << "(\033[1;31mError\033[0m #" << j << ")" << std::endl;
                        std::cout << "Source                : \033[1;33m" << glbl.err.captured[j].GetSource() << "\033[0m" << std::endl;
                        std::cout << "Type                  : \033[1;33m" << glbl.err.captured[j].GetType() << "\033[0m" << std::endl; 
                        std::cout << "Further information   :" << std::endl;
                        for (const std::string& info : glbl.err.captured[j].GetMessages())
                            std::cout << "  " << info << std::endl;
                        std::cout << "--------------------------------" << std::endl;
                    }

                    dump();

                    shutdown();

                    return 1;
                }
            }
        }


        if (counter_interval_commit == 512) // commit watchdog
        {
            std::ostringstream oss;

            std::cout << "--------------------------------" << std::endl;
            std::cout << "\033[1;31mEmulation stopped\033[0m due to WATCH DOG." << std::endl;
            std::cout << "Nothing commited in past 512 clocks." << std::endl;

            oss << "\nLast commit PC: \033[1;33m0x" << std::hex << std::setw(8) << std::setfill(' ') << last_pc << "\033[0m" << std::endl;
            std::cout << oss.str();
            std::cout << "--------------------------------" << std::endl;

            dump(true);

            shutdown();

            return 1;
        }


        // update console

        if (counter_interval == 6000 
        ||  counter_interval == 12000 
        ||  counter_interval == 18000)
        {
            std::ostringstream oss;

            if (coninfo_first_time)
                coninfo_first_time = false;
            else
                oss << "\033[1A\033[K\033[1A\033[K\033[1A\033[K\033[1A\033[K";

            oss << "Emulation speed   : \033[1;33m";
            oss << std::setw(12) << std::setfill(' ') << cps;
            oss << "\033[0m cycles/second";
            oss << "  ";
            oss << ANIMATE_INF_PROGRESS_BAR[counter_progressbar] << std::endl;
            oss << "Dual-commit ratio : \033[1;33m" << (double(counter_dualcommit) / counter_commit) << "\033[0m" << std::endl;
            oss << "Overall IPC       : \033[1;33m" << (double(counter_commit) / counter_cycle) << "\033[0m" << std::endl;
            oss << "Last commit PC    : \033[1;33m0x" << std::hex << std::setw(8) << std::setfill(' ') << last_pc << "\033[0m" << std::endl;

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


