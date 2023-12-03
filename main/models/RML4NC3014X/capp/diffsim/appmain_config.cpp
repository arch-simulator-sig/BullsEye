#include "appmain_config.hpp"
//
// Configuration procedures
//
//

#include "appmain_glbl.hpp"


#include <unistd.h>

#include <iostream>


#define ERROR_PREFIX    "\033[1;31merror\033[0m: "



void usage()
{
    std::cout << "Usage: <-B <binaryfile>> [-T <interval>] [-t <address[:port]>] [-S <address>] [-F <address>] [-h]" << std::endl;
    std::cout << " -B <binaryfile>      - Specify binary file to load" << std::endl;
    std::cout << " -T <interval>        - Specify system tick interval (tuned for 1M tick/s clock counter)" << std::endl;
    std::cout << " -t [address[:port]]  - Enable serial server and specify TCP address" << std::endl;
    std::cout << " -S <address>         - Set start-up PC address" << std::endl;
    std::cout << " -F <address>         - Set finish trap PC address" << std::endl;
    std::cout << " -h                   - Show this help" << std::endl;
}


int config(int argc, char* argv[])
{
    // input parameters
    std::string binaryfilename;

    bool        serial_server = false;
    std::string serial_server_address = "127.0.0.1";

    uint32_t    start_pc    = 0x00000000;
    uint32_t    finish_pc   = 0xFFFFFFFF;

    uint32_t    systick_interval = 50;

    char* endptr = NULL;

    int o;
    while ((o = getopt(argc, argv, "B:T:t::S:F:h")) != -1)
    {
        switch (o)
        {
            case 'B':
                binaryfilename = optarg;
                break;

            case 'T':
                systick_interval = strtoul(optarg, &endptr, 0);
                if (errno == ERANGE)
                {
                    std::cout << ERROR_PREFIX << "system tick interval out of range" << std::endl;
                    return 1;
                }
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



    // binary file name
    if (binaryfilename.empty())
    {
        std::cout << ERROR_PREFIX << "binary file path required." << std::endl;
        return 1;
    }

    glbl.cfg.binaryFileName = binaryfilename;


    // serial
    glbl.cfg.serial.serverEnabled = serial_server;

    if (serial_server)
    {
        std::string serial_ip;
        uint16_t    serial_port = 5001;

        auto spos = serial_server_address.find(':');
        if (spos != std::string::npos)
        {
            serial_ip  = serial_server_address.substr(0, spos);
            serial_port = strtoul(serial_server_address.substr(spos + 1).c_str(), &endptr, 0);
            if (errno == ERANGE)
            {
                std::cout << ERROR_PREFIX << "serial server port out of range" << std::endl;
                return 1;
            }
        }
        else
            serial_ip = serial_server_address;

        glbl.cfg.serial.serverAddress   = serial_ip;
        glbl.cfg.serial.serverPort      = serial_port;
    }


    // startup 
    glbl.cfg.startupPC          = start_pc;


    // finish trap
    glbl.cfg.finishTrapPC       = finish_pc;
    glbl.cfg.finishTrapMargin   = 50000;


    // dump 0
    glbl.cfg.dump0.enabled = true;

    glbl.cfg.dump0.upperCount = 3;
    glbl.cfg.dump0.lowerCount = 3;

    glbl.cfg.dump0.muteUnread = true;


    // dump 1
    glbl.cfg.dump1.enabled = true;

    glbl.cfg.dump1.upperCount = 8;
    glbl.cfg.dump1.lowerCount = 1;

    glbl.cfg.dump1.displayTrace = true;

    glbl.cfg.dump1.muteUnread = true;


    // dump 2
    glbl.cfg.dump2.enabled = true;

    glbl.cfg.dump2.depth = 7;


    // dump 3
    glbl.cfg.dump3.enabled = false;

    glbl.cfg.dump3.depth = 7;


    // dump 4
    glbl.cfg.dump4.enabled = true;

    glbl.cfg.dump4.depth = 7;


    //

    return 0;
}
