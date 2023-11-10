#pragma once
//
// LA32 Instruction Set Architecture 
//
// Instruction disassemble utilities
//

#ifndef __HEADER_JASSE_LA32__BASE_DISASM
#define __HEADER_JASSE_LA32__BASE_DISASM


#include <string>

#include "la32decode.hpp"


// Implementation of Instruction Textualizers
namespace Jasse {

    std::string TextualizeLA32GPR(int GPR) noexcept;
    std::string TextualizeLA32Name(const std::string& name) noexcept;

    std::string TextualizeLA32Type2R(const LA32Instruction& insn) noexcept;
    std::string TextualizeLA32Type3R(const LA32Instruction& insn) noexcept;
    std::string TextualizeLA32Type4R(const LA32Instruction& insn) noexcept;
    std::string TextualizeLA32Type2RI8(const LA32Instruction& insn) noexcept;
    std::string TextualizeLA32Type2RI12(const LA32Instruction& insn) noexcept;
    std::string TextualizeLA32Type2RI14(const LA32Instruction& insn) noexcept;
    std::string TextualizeLA32Type2RI16(const LA32Instruction& insn) noexcept;
    std::string TextualizeLA32Type1RI21(const LA32Instruction& insn) noexcept;
    std::string TextualizeLA32TypeI26(const LA32Instruction& insn) noexcept;

    std::string TextualizeLA32Type2ROffs16(const LA32Instruction& insn) noexcept;
    std::string TextualizeLA32TypeOffs26(const LA32Instruction& insn) noexcept;

    std::string TextualizeLA32TypeX2RI5(const LA32Instruction& insn) noexcept;
    std::string TextualizeLA32TypeX1RI20(const LA32Instruction& insn) noexcept;
}


#endif
