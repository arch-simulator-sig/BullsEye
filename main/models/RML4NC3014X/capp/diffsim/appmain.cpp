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

    std::cout << "--------------------------------" << std::endl;


    // 50MHz clock counter (1M tick per sec)
    uint32_t clkcounter_interval = 0;


    //
    int con_linecount = 9; // basic info

    con_linecount += 2; // PPInfo

    if (glbl.cfg.ppinfo.branchPredictionEnabled)
        con_linecount += 2;

    if (glbl.cfg.ppinfo.issueStageEnabled)
        con_linecount += 12;


    //
    int counter_progressbar = 0;

    bool coninfo_first_time = true;

    auto start      = std::chrono::system_clock::now();
    auto last_time  = std::chrono::system_clock::now();
    unsigned long long cps = 0;

    pc_t last_pc;

    uint64_t    counter_cycle       = 0;
    uint64_t    counter_commit      = 0;

    uint64_t    counter_dualcommit  = 0;

    uint64_t    counter_interval_commit = 0;

    uint32_t    finish_aftercount   = 0;
    bool        finish_trapped      = false;


    int counter_interval = 0;
    while (1)
    {
        // Clock Counter
        if (clkcounter_interval < 50)
            clkcounter_interval++;
        else
        {
            glbl.ctx.dut.soc->CounterClock().IncreaseCounter();

            clkcounter_interval = 0;
        }


        // System Eval
        glbl.ctx.dut.dut->Eval();


        //
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

                    if (finish_trapped)
                        finish_aftercount++;
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

                    oss << "\nLast commit PC: \033[1;33m0x" << std::hex << std::setw(8) << std::setfill('0') << last_pc << "\033[0m" << std::endl;
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

                // finish trap
                if (last_pc == glbl.cfg.finishTrapPC)
                {
                    finish_trapped = true;
                }

                if (finish_trapped && (finish_aftercount >= glbl.cfg.finishTrapMargin))
                {
                    //
                    std::cout << "--------------------------------" << std::endl;

                    std::cout << "\033[0;36mHIT FINISH TRAP!\033[0m" << std::endl;

                    //
                    std::cout << "Hit finish trap with margin of " << std::dec << glbl.cfg.finishTrapMargin << " commit(s)." << std::endl;

                    auto end = std::chrono::system_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

                    std::cout << counter_cycle << " cycle(s) emulated in " << duration.count() << "ms (" << (double(counter_cycle) / duration.count()) << " steps/ms)." << std::endl;

                    shutdown();

                    return 0;
                }
            }
        }


        // commit watchdog
        if (counter_interval_commit == 512)
        {
            std::ostringstream oss;

            std::cout << "--------------------------------" << std::endl;
            std::cout << "\033[1;31mEmulation stopped\033[0m due to WATCH DOG." << std::endl;
            std::cout << "Nothing commited in past 512 clocks." << std::endl;

            oss << "\nLast commit PC: \033[1;33m0x" << std::hex << std::setw(8) << std::setfill('0') << last_pc << "\033[0m" << std::endl;
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
                for (int i = 0; i < con_linecount; i++)
                    oss << "\033[1A\033[K";

            if (!glbl.oss.view().empty())
            {
                oss << glbl.oss.view();

                std::size_t pos = glbl.oss.view().find_last_of('\n');
                if (pos != std::string::npos)
                {
                    std::string nexts = glbl.oss.str().substr(pos + 1);

                    glbl.oss = std::ostringstream();
                    glbl.oss << nexts;
                }
            }

            oss << std::endl;
            oss << "--------------------------------" << std::endl;
            oss << "Emulation speed   : \033[1;33m";
            oss << std::setw(12) << std::setfill(' ') << cps;
            oss << "\033[0m cycles/second";
            oss << "  ";
            oss << ANIMATE_INF_PROGRESS_BAR[counter_progressbar] << std::endl;
            oss << "Dual-commit ratio     : \033[1;33m" << (double(counter_dualcommit) / counter_commit) << "\033[0m" << std::endl;
            oss << "Overall IPC           : \033[1;33m" << (double(counter_commit) / counter_cycle) << "\033[0m" << std::endl;
            oss << "Last commit PC        : \033[1;33m0x" << std::hex << std::setw(8) << std::setfill('0') << last_pc << "\033[0m" << std::endl;
            oss << "Instruction commited  : \033[1;33m" << std::dec << counter_commit << "\033[0m" << std::endl;
            oss << "Cycles elapsed        : \033[1;33m" << std::dec << counter_cycle << "\033[0m" << std::endl;
            oss << "Ticks elapsed         : \033[1;33m" << std::dec << glbl.ctx.dut.soc->CounterClock().GetCounter() << "\033[0m" << std::endl;

            counter_progressbar = ++counter_progressbar % ANIMATE_INF_PROGRESS_BAR_SIZE;

            std::cout << oss.str();

            // Performance Profiling Interface information
            oss = std::ostringstream();

            oss << "--------------------------------" << std::endl;
            oss << "Performance Profiling Interface information " << std::endl;

            if (glbl.cfg.ppinfo.branchPredictionEnabled)
            {
                oss << "Branch Prediction:" << std::endl;
                oss << "  - accuracy        : \033[1;33m";
                oss << std::fixed << std::setw(5) << std::setprecision(2);
                oss << (100 - (double(glbl.ctx.dut.dut->GetPPI().fetch_brob_bpmiss_count * 100)
                    / glbl.ctx.dut.dut->GetPPI().fetch_brob_commit_count));
                oss << "\033[0m% " << std::endl;
            }

            if (glbl.cfg.ppinfo.issueStageEnabled)
            {
                oss << "Issue Queue \033[1;33m#0\033[0m (ALU/BRU):" << std::endl;
                oss << "  - occupation rate : ";
                for (int i = 5; i >= 0; i--)
                {
                    oss << "[ \033[1;33m";
                    oss << std::fixed << std::setw(6) << std::setprecision(2);
                    oss << (double(glbl.ctx.dut.dut->GetPPI().issue_iq0_pick_valid_counter[i] * 100) 
                        / (glbl.ctx.dut.dut->GetEvalTime() >> 1));
                    oss << "\033[0m% ] ";
                }
                oss << std::endl;
                oss << "  - pick rate       : ";
                for (int i = 5; i >= 0; i--)
                {
                    oss << "[ \033[1;33m";
                    oss << std::fixed << std::setw(6) << std::setprecision(2);
                    oss << (double(glbl.ctx.dut.dut->GetPPI().issue_iq0_pick_en_counter[i] * 100)
                        / (glbl.ctx.dut.dut->GetEvalTime() >> 1));
                    oss << "\033[0m% ] ";
                }
                oss << std::endl;

                oss << "Issue Queue \033[1;33m#1\033[0m (ALU    ):" << std::endl;
                oss << "  - occupation rate : ";
                for (int i = 5; i >= 0; i--)
                {
                    oss << "[ \033[1;33m";
                    oss << std::fixed << std::setw(6) << std::setprecision(2);
                    oss << (double(glbl.ctx.dut.dut->GetPPI().issue_iq1_pick_valid_counter[i] * 100)
                        / (glbl.ctx.dut.dut->GetEvalTime() >> 1));
                    oss << "\033[0m% ] ";
                }
                oss << std::endl;
                oss << "  - pick rate       : ";
                for (int i = 5; i >= 0; i--)
                {
                    oss << "[ \033[1;33m";
                    oss << std::fixed << std::setw(6) << std::setprecision(2);
                    oss << (double(glbl.ctx.dut.dut->GetPPI().issue_iq1_pick_en_counter[i] * 100)
                        / (glbl.ctx.dut.dut->GetEvalTime() >> 1));
                    oss << "\033[0m% ] ";
                }
                oss << std::endl;

                oss << "Issue Queue \033[1;33m#2\033[0m (MEM    ):" << std::endl;
                oss << "  - occupation rate : ";
                for (int i = 5; i >= 0; i--)
                {
                    oss << "[ \033[1;33m";
                    oss << std::fixed << std::setw(6) << std::setprecision(2);
                    oss << (double(glbl.ctx.dut.dut->GetPPI().issue_iq2_pick_valid_counter[i] * 100)
                        / (glbl.ctx.dut.dut->GetEvalTime() >> 1));
                    oss << "\033[0m% ] ";
                }
                oss << std::endl;
                oss << "  - pick rate       : ";
                for (int i = 5; i >= 0; i--)
                {
                    oss << "[ \033[1;33m";
                    oss << std::fixed << std::setw(6) << std::setprecision(2);
                    oss << (double(glbl.ctx.dut.dut->GetPPI().issue_iq2_pick_en_counter[i] * 100)
                        / (glbl.ctx.dut.dut->GetEvalTime() >> 1));
                    oss << "\033[0m% ] ";
                }
                oss << std::endl;

                oss << "Issue Queue \033[1;33m#3\033[0m (MUL/DIV):" << std::endl;
                oss << "  - occupation rate : ";
                for (int i = 5; i >= 0; i--)
                {
                    oss << "[ \033[1;33m";
                    oss << std::fixed << std::setw(6) << std::setprecision(2);
                    oss << (double(glbl.ctx.dut.dut->GetPPI().issue_iq3_pick_valid_counter[i] * 100)
                        / (glbl.ctx.dut.dut->GetEvalTime() >> 1));
                    oss << "\033[0m% ] ";
                }
                oss << std::endl;
                oss << "  - pick rate       : ";
                for (int i = 5; i >= 0; i--)
                {
                    oss << "[ \033[1;33m";
                    oss << std::fixed << std::setw(6) << std::setprecision(2);
                    oss << (double(glbl.ctx.dut.dut->GetPPI().issue_iq3_pick_en_counter[i] * 100)
                        / (glbl.ctx.dut.dut->GetEvalTime() >> 1));
                    oss << "\033[0m% ] ";
                }
                oss << std::endl;
            }

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

    shutdown();

    return 0;
}


