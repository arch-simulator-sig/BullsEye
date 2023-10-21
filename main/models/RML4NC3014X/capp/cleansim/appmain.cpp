#include "appmain.hpp"

#include "autoinclude.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <iomanip>

#include <verilated.h>
#include <verilated_vcd_c.h>

#include "core/ds232.hpp"

#include AUTOINC_BE_N1_SOC_LA32(soc.hpp)
#include AUTOINC_BE_N1_SOC_LA32(serial.hpp)


//#define ENDIAN_SWITCHED

#ifdef ENDIAN_SWITCHED
#define ENDIAN_SWITCH32(val) \
    (((val) & 0x000000FF) << 24) | \
    (((val) & 0x0000FF00) << 8) | \
    (((val) & 0x00FF0000) >> 8) | \
    (((val) & 0xFF000000) >> 24)
#else
#define ENDIAN_SWITCH32(val) val
#endif


//#define SERIAL_SERVER


static VerilatedVcdC* fp;      // to form *.vcd file

void init_vcd()
{
#ifdef VM_TRACE
    ////// !!!  ATTENTION  !!!//////
    //  Call Verilated::traceEverOn(true) first.
    //  Then create a VerilatedVcdC object.    
    Verilated::traceEverOn(true);
    std::cout << "Enabling waves ..." << std::endl;
    fp = new VerilatedVcdC;     //instantiating .vcd object
#else
    fp = nullptr;
#endif
}

void open_vcd()
{
#ifdef VM_TRACE
    fp->open("trace.vcd");      //open the dump file
    std::cout << "\033[1;33mEnabled waves.\033[0m" << std::endl;
#else
    std::cout << "\033[1;33mWaves not enabled.\033[0m" << std::endl;
#endif
}

void finalize_vcd()
{
#ifdef VM_TRACE
    fp->close();
    delete fp;
#endif
}


int main(int argc, char* argv[])
{
    using namespace BullsEye;
    using namespace BullsEye::NSCSCCSingle;


    // Initialize NSCSCC2023 SoC
    BaseRAM* baseRAM = new BaseRAM;
    ExtRAM*  extRAM  = new ExtRAM;


    // Open binary file
    std::ostringstream argoss;
    for (int i = 1; i < argc; i++)
        argoss << argv[i] << " ";

    if (argoss.view().empty())
    {
        std::cout << "[\033[1;31mERROR\033[0m] Binary file path required." << std::endl;
        return 1;
    }
    
    std::string binaryfilename = argoss.str();
    binaryfilename.pop_back();

    std::ifstream binaryfile(binaryfilename, std::ifstream::binary);

    if (!binaryfile)
    {
        std::cout << "[\033[1;31mERROR\033[0m] Cannot open file: " << binaryfilename << std::endl;
        return 1;
    }

    // Load binary file into RAM
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Ready to load binary file: " << binaryfilename << std::endl;

    int counter         = 0;
    int counter_base    = 0;
    int counter_ext     = 0;
    while (!binaryfile.eof())
    {
        memdata_t data;
        binaryfile.read(reinterpret_cast<char*>(&data.data32), sizeof(insnraw_t));

        data.data32 = ENDIAN_SWITCH32(data.data32);

        if (counter == 2048 * 1024)
        {
            std::cout << "[\033[1;31mERROR\033[0m] 8MB binary file max supported. Mounted 4MB BaseRAM and 4MB ExtRAM." << std::endl;
            return 1;
        }
        else if (counter >= 1024 * 1024)
        {
            if (extRAM->WriteInsn((counter << 2) - 0x00400000, MOPW_WORD, data).status != LA32MOPStatus::MOP_SUCCESS)
            {
                std::cout << "[\033[1;31mERROR\033[0m] Failed to write to ExtRAM (0x" 
                    << std::hex << std::setw(8) << std::setfill('0') << (counter << 2) << std::dec << ")." 
                    << std::endl;
                return 1;
            }

            counter_ext++;
        }
        else
        {
            if (baseRAM->WriteInsn(counter << 2, MOPW_WORD, data).status != LA32MOPStatus::MOP_SUCCESS)
            {
                std::cout << "[\033[1;31mERROR\033[0m] Failed to write to BaseRAM (0x" 
                    << std::hex << std::setw(8) << std::setfill('0') << (counter << 2) << std::dec << ")." 
                    << std::endl;
                return 1;
            }

            counter_base++;
        }

        counter++;
    }

    std::cout << "\033[1;33mLoaded program binary file.\033[0m" << std::endl;
    std::cout << "Loaded " << counter_base << " byte(s) to BaseRAM" << std::endl;
    std::cout << "Loaded " << counter_ext << " byte(s) to ExtRAM" << std::endl;
    std::cout << "--------------------------------" << std::endl;


#ifdef SERIAL_SERVER
    // Initialize serial tcp
    std::cout << "Initialize serial TCP server ..." << std::endl;

    SerialTCPServer* serial = new SerialTCPServer;

    const char* ip      = "127.0.0.1";
    uint64_t    port    = 5001;

    if (!serial->OpenServer(ip, port))
    {
        std::cout << "[\033[1;31mERROR\033[0m] Cannot open serial TCP server on " << ip << ":" << port << std::endl;
        return 1;
    }

    serial->AcceptConnection();

    printf("\033[1;33mOpened serial TCP server on %s:%d\033[0m\n", ip, (uint32_t) port);

    //
    printf("Press ENTER to continue...\n");
    std::cin.get();
    std::cout << "--------------------------------" << std::endl;

#else
    // Initialize serial
    SerialWriteOnlyConsole* serial = new SerialWriteOnlyConsole;

#endif

    //
    NSCSCC2023SoC* soc = NSCSCC2023SoC::Builder()
        .BaseDOGGIES(baseRAM)
        .ExtDOGGIES (extRAM)
        .Serial     (serial)
        .Build();


    // Initialize Thinpad & VCD
    init_vcd();

    Draconids3014::Thinpad* thinpad = Draconids3014::Thinpad::Builder()
        .SoC(soc)
        .VCD(fp)
        .Build();

    open_vcd();

    std::cout << "--------------------------------" << std::endl;


    // Emulation cycles
    std::cout << "\033[1;33mStarted verilated emulation of DS232 on NSCSCC2023 AXI SoC.\033[0m" << std::endl;

    std::cout << "Reset cycle (1) elapsed." << std::endl;
    thinpad->NextReset();
    thinpad->Eval();

    int counter_progressbar = 0;

    auto last_time = std::chrono::system_clock::now();
    unsigned long long cps = 0;

    int counter_interval = 0;
    while (1)
    {
        thinpad->Eval();

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
            oss << "\n\033[1A";

            counter_progressbar = ++counter_progressbar % ANIMATE_INF_PROGRESS_BAR_SIZE;

            std::cout << oss.str();
        }

        if (counter_interval == 18000)
        {
            counter_interval = 0;

            // TODO update console information
            auto now_time = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now_time - last_time);

            last_time = now_time;

            cps = (18000ULL * 1000ULL) / duration.count();
        }
        else
            counter_interval++;
    }

    // TODO

    // Finalize
    finalize_vcd();

    delete thinpad;
    delete soc;
    delete serial;
    delete extRAM;
    delete baseRAM;

    return 0;
}
