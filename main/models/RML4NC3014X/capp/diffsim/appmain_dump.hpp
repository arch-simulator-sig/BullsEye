#pragma once
//
//
//
//


// Dump all
void dump(bool pause = false);


// Dump #0: program memory
// - Dumping surrounding program memory sequence on execution error
void dump0(bool pause = false);

// Dump #1: program execution
// - Dumping history program execution sequence on execution error
void dump1(bool pause = false);
