#pragma once
//
//
//
//


// Dump all
void dump(bool pause = false);


// Dump #0: program memory
// - Dumping surrounding program memory sequence on execution error or emulation pause
void dump0(bool pause = false);

// Dump #1: program execution
// - Dumping history program execution sequence on execution error or emulation pause
void dump1(bool pause = false);

// Dump #2: DUT MMU access history
// - Dumping MMU memory access history from DUT
void dump2();

// Dump #3: Ref MMU access history
// - Dumping MMU memory access history from reference
void dump3();

// Dump #4: DUT AXI bus history
// - Dumping AXI bus operation history from DUT
void Dump4();
