#include "appmain.hpp"
//
//
//
//

#include <unistd.h>

#include <cstdlib>
#include <cerrno>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>


#include "autoinclude.h"

#include AUTOINC_BE_JASSE2_LA32(la32_nscscc.hpp)    // IWYU pragma: keep

#include AUTOINC_BE_N1_SOC_LA32(serial.hpp)
#include AUTOINC_BE_N1_SOC_LA32(memory.hpp)
#include AUTOINC_BE_N1_SOC_LA32(soc.hpp)


#define ERROR_PREFIX    "\033[1;31merror\033[0m: "

//#define ENDIAN_SWITCHED


void usage()
{
    std::cout << "Usage: <-B <binaryfile>> [-t <address[:port]>] [-S <address>] [-F <address>] [-h]" << std::endl;
    std::cout << " -B <binaryfile>      - Specify binary file to load" << std::endl;
    std::cout << " -t <address[:port]>  - Enable serial server and specify TCP address" << std::endl;
    std::cout << " -S <address>         - Set start-up PC address" << std::endl;
    std::cout << " -F <address>         - Set finish trap PC address" << std::endl;
    std::cout << " -h                   - Show this help" << std::endl;
}


#ifdef ENDIAN_SWITCHED
#define ENDIAN_SWITCH32(val) \
    (((val) & 0x000000FF) << 24) | \
    (((val) & 0x0000FF00) << 8) | \
    (((val) & 0x00FF0000) >> 8) | \
    (((val) & 0xFF000000) >> 24)
#else
#define ENDIAN_SWITCH32(val) val
#endif


int main(int argc, char* argv[])
{
    using namespace BullsEye;
    using namespace BullsEye::NSCSCCSingle;

    // input parameters
    std::string binaryfilename;

    bool        serial_server = false;
    std::string serial_server_address = "127.0.0.1";

    uint32_t    start_pc    = 0x80000000;
    uint32_t    finish_pc   = 0xFFFFFFFF;

    uint32_t    systick_interval = 50000;

    char* endptr = NULL;

    int o;
    while ((o = getopt(argc, argv, "B:t::S:F:h")) != -1)
    {
        switch (o)
        {
            case 'B':
                binaryfilename = optarg;
                break;

            case 't':
                serial_server = true;
                if (optarg)
                    serial_server_address = optarg;
                break;

            case 'S':
                start_pc = strtoul(optarg, &endptr, 0);
                if (errno == ERANGE)
                {
                    std::cout << ERROR_PREFIX << "start-up address out of range" << std::endl;
                    return 1;
                }
                break;

            case 'F':
                finish_pc = strtoul(optarg, &endptr, 0);
                if (errno == ERANGE)
                {
                    std::cout << ERROR_PREFIX << "finish trap address out of range" << std::endl;
                    return 1;
                }
                break;

            case 'h':
                usage();
                return 0;

            case '?':
                std::cout << ERROR_PREFIX << "unknown option: " << char(optopt) << std::endl;
                usage();
                return 1;
        }
    }


    // open binary file
    if (binaryfilename.empty())
    {
        std::cout << ERROR_PREFIX << "no target binary file" << std::endl;
        return 1;
    }

    std::ifstream binaryfile(binaryfilename, std::ifstream::binary);

    if (!binaryfile)
    {
        std::cout << ERROR_PREFIX << "cannot open binary file: " << binaryfilename << std::endl;
        return 1;
    }


    // Initialize serial
    SerialInterface* serial;
    if (serial_server)
    {
        // Initialize serial tcp
        SerialTCPServer* lserial = new SerialTCPServer;

        serial = lserial;

        std::string ip;
        uint16_t    port = 5001;

        
        auto spos = serial_server_address.find(':');
        if (spos != std::string::npos)
        {
            ip  = serial_server_address.substr(0, spos);
            port = strtoul(serial_server_address.substr(spos + 1).c_str(), &endptr, 0);
            if (errno == ERANGE)
            {
                std::cout << ERROR_PREFIX << "serial server port out of range" << std::endl;
                return 1;
            }
        }
        else
            ip = serial_server_address;

        if (!lserial->OpenServer(ip.c_str(), port))
        {
            std::cout << ERROR_PREFIX << "cannot open serial TCP server on " << ip << ":" << port << std::endl;
            return 1;
        }

        lserial->AcceptConnection();

        printf("Opened serial TCP server on %s:%d\n", ip.c_str(), (uint32_t) port);

        //
        printf("Press ANY KEY to continue...\n");
        std::cin.get();
    }
    else
    {
        SerialWriteOnlyConsole* lserial = new SerialWriteOnlyConsole;

        serial = lserial;
    }


    // Initialize NSCSCC2023 SoC
    BaseRAM*    baseRAM = new BaseRAM;
    ExtRAM*     extRAM  = new ExtRAM;

    //
    NSCSCC2023SoC* soc = NSCSCC2023SoC::Builder()
        .BaseDOGGIES(baseRAM)
        .ExtDOGGIES (extRAM)
        .Serial     (serial)
        .Build();

    // Initialize LA32-NSCSCC emulator instance
    LA32Instance* instance = LA32Instance::Builder()
        .StartupPC      (start_pc)
        .Decoder        (Decoder::LA32R_NSCSCC)
        .Memory         (&(soc->MMU()))
        .Build();


    // Load binary file
    int counter = 0;
    while (!binaryfile.eof())
    {
        memdata_t data;
        binaryfile.read(reinterpret_cast<char*>(&data.data32), sizeof(insnraw_t));

        data.data32 = ENDIAN_SWITCH32(data.data32);

        if (counter == 2048 * 1024)
        {
            std::cout << ERROR_PREFIX << "8MB binary file max supported. Mounted 4MB BaseRAM and 4MB ExtRAM." << std::endl;
            return 1;
        }
        else if (counter >= 1024 * 1024)
        {
            if (extRAM->WriteInsn((counter << 2) - 0x00400000, MOPW_WORD, data).status != LA32MOPStatus::MOP_SUCCESS)
            {
                std::cout  << ERROR_PREFIX << "failed to write to ExtRAM (0x" 
                    << std::hex << std::setw(8) << std::setfill('0') << (counter << 2) << std::dec << ")." 
                    << std::endl;
                return 1;
            }
        }else 
        {
            if (baseRAM->WriteInsn(counter << 2, MOPW_WORD, data).status != LA32MOPStatus::MOP_SUCCESS)
            {
                std::cout << ERROR_PREFIX << "failed to write to BaseRAM (0x" 
                    << std::hex << std::setw(8) << std::setfill('0') << (counter << 2) << std::dec << ")." 
                    << std::endl;
                return 1;
            }
        }

        counter++;
    }

    std::cout << "--------------------------------" << std::endl;
    std::cout << "Loaded program binary file: " << binaryfilename << std::endl;
    std::cout << "--------------------------------" << std::endl;


    //
    auto start = std::chrono::system_clock::now();

    int systick_counter = 0;

    unsigned long long step = 0;

    int counter_progressbar = 0;

    auto last_time = std::chrono::system_clock::now();
    unsigned long long cps = 0;

    int counter_interval = 0;

    //
    while (1)
    {
        // update console
        auto update_console_emuinfo = [&]() -> void {
            std::ostringstream oss;

            oss << "\n--------------------------------" << std::endl;
            oss << "Emulation speed   : \033[1;33m";
            oss << std::setw(12) << std::setfill(' ') << cps;
            oss << "\033[0m cycles/second";
            oss << "  ";
            oss << ANIMATE_INF_PROGRESS_BAR[counter_progressbar] << std::endl;
            oss << "Last commit PC    : \033[1;33m0x" << std::hex << std::setw(8) << std::setfill('0') << instance->Arch().PC() << "\033[0m" << std::endl;
            oss << "\033[4A";

            counter_progressbar = ++counter_progressbar % ANIMATE_INF_PROGRESS_BAR_SIZE;

            std::cout << oss.str();
        };

        if (counter_interval == 600000 
        ||  counter_interval == 1200000 
        ||  counter_interval == 1800000)
        {
            update_console_emuinfo();
        }

        if (counter_interval == 1800000)
        {
            counter_interval = 0;

            auto now_time = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now_time - last_time);

            last_time = now_time;

            cps = (1800000ULL * 1000ULL) / duration.count();
        }
        else
            counter_interval++;
            

        // finish trap
        if (instance->Arch().PC() == finish_pc)
        {
            //
            update_console_emuinfo();

            //
            std::cout << "\033[3B" << std::endl;
            std::cout << "--------------------------------" << std::endl;

            std::cout << "\033[0;36mHIT FINISH TRAP!\033[0m" << std::endl;
            std::cout << "System tick elapsed: " << systick_counter << std::endl;

            //
            auto end = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

            std::cout << step << " step(s) emulated in " << duration.count() << "ms (" << (double(step) / duration.count()) << " steps/ms)." << std::endl;
            break;
        }

        LA32ExecOutcome outcome = instance->Eval();
        step++;

        if (++systick_counter == systick_interval)
        {
            systick_counter = 0;
            
            soc->CounterClock().IncreaseCounter();
        }

        switch (outcome.status)
        {
            case LA32ExecStatus::EXEC_SEQUENTIAL:
                continue;

            case LA32ExecStatus::EXEC_BRANCH:
                continue;

            default:
                break;
        }

        std::cout << "\033[3B" << std::endl;
        std::cout << "--------------------------------" << std::endl;

        std::cout << "Emulation exception: ";

        std::ostringstream oss;

        switch (outcome.status)
        {
            case LA32ExecStatus::EXEC_MEMORY_ACCESS_FAULT:
                oss << "MEMORY_ACCESS_FAULT";
                break;

            case LA32ExecStatus::EXEC_MEMORY_ADDRESS_MISALIGNED:
                oss << "MEMORY_ADDRESS_MISALIGNED";
                break;

            case LA32ExecStatus::EXEC_MEMORY_DEVICE_ERROR:
                oss << "MEMORY_DEVICE_ERROR";
                break;

            case LA32ExecStatus::EXEC_NOT_DECODED:
                oss << "NOT_DECODED";
                break;

            case LA32ExecStatus::EXEC_NOT_IMPLEMENTED:
                oss << "NOT_IMPLEMENTED";
                break;

            case LA32ExecStatus::FETCH_ACCESS_FAULT:
                oss << "FETCH_ACCESS_FAULT";
                break;

            case LA32ExecStatus::FETCH_ADDRESS_MISALIGNED:
                oss << "FETCH_ADDRESS_MISALIGNED";
                break;

            case LA32ExecStatus::FETCH_DEVICE_ERROR:
                oss << "FETCH_DEVICE_ERROR";
                break;

            case LA32ExecStatus::DECODE_EMULATION_CANCELLED:
                oss << "DECODE_EMULATION_CANCELLED";
                break;

            case LA32ExecStatus::DECODE_EMULATION_ERROR:
                oss << "DECODE_EMULATION_ERROR";
                break;

            case LA32ExecStatus::EXEC_EMULATION_CANCELLED:
                oss << "EXEC_EMULATION_CANCELLED";
                break;

            case LA32ExecStatus::EXEC_EMULATION_ERROR:
                oss << "EXEC_EMULATION_ERROR";
                break;

            case LA32ExecStatus::FETCH_EMULATION_CANCELLED:
                oss << "FETCH_EMULATION_CANCELLED";
                break;

            case LA32ExecStatus::FETCH_EMULATION_ERROR:
                oss << "FETCH_EMULATION_ERROR";
                break;

            default:
                oss << "UNKNOWN";
                break;
        }

        oss << " " << "0x" << std::hex << std::setw(8) << std::setfill('0') << outcome.error << std::dec << "(" << outcome.error << ")";
        oss << std::endl;

        oss << "\033[1;31mEmulation stopped\033[0m at PC " << "0x" << std::hex << std::setw(8) << std::setfill('0') << instance->Arch().PC();
        oss << std::endl;

        std::cout << oss.view();

        break;
    }


    //
    return 0;
}