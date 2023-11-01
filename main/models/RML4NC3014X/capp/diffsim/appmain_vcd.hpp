#pragma once
//
// VCD waveform operations
//
//

#include <verilated_vcd_c.h>


extern VerilatedVcdC* fp;      // to form *.vcd file


void init_vcd();
void open_vcd();
void finalize_vcd();
