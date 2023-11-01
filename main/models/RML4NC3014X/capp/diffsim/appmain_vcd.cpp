#include "appmain_vcd.hpp"


#include <iostream>


#ifndef VCD_DUMP_FILE
#define VCD_DUMP_FILE "trace.vcd"
#endif


VerilatedVcdC* fp;


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
    std::cout << "Opening VCD waveform dump file: " << VCD_DUMP_FILE << std::endl;
    fp->open(VCD_DUMP_FILE);      //open the dump file
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
