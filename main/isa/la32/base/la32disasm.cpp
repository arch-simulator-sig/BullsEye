#include "la32disasm.hpp"
//
// LA32 Instruction Set Architecture 
//
// Miscs and utilities
//

#include <sstream>
#include <iomanip>


// Implementation of Instruction Textualizers
namespace Jasse {

//#define LA32_TEXTUALIZE_GPR_AS_ABI
#define LA32_TEXTUALIZE_GPR_WITH_PREFIX

#define LA32_TEXTUALIZE_NAME_ALIGNMENT              8

#ifdef LA32_TEXTUALIZE_GPR_AS_ABI
    std::string TextualizeLA32GPR(int GPR) noexcept
    {
        // ABI form

        static const std::string ABI_NAMES[] = {
            "zero", 
            "ra  ", 
            "tp  ", 
            "sp  ",
            "a0  ", "a1  ",
            "a2  ", "a3  ", "a4  ", "a5  ", "a6  ", "a7  ",
            "t0  ", "t1  ", "t2  ", "t3  ", "t4  ", "t5  ", "t6  ", "t7  ", "t8  ",
            "r21 ",
            "fp  ",
            "s0  ", "s1  ", "s2  ", "s3  ", "s4  ", "s5  ", "s6  ", "s7  ", "s8  "
        };

        if (GPR < 0 || GPR > 31)
        {
            std::ostringstream oss;

#ifdef LA32_TEXTUALIZE_GPR_WITH_PREFIX
            oss << "$";
#else
            oss << "x";
#endif

            oss << GPR;

            return oss.str();
        }

#ifdef LA32_TEXTUALIZE_GPR_WITH_PREFIX
        std::ostringstream oss;

        oss << "$";
        oss << ABI_NAMES[GPR];

        return oss.str();
#else
        return ABI_NAMES[GPR];
#endif
    }

#else
    std::string TextualizeLA32GPR(int GPR) noexcept
    {
        std::ostringstream oss;

#ifdef LA32_TEXTUALIZE_GPR_WITH_PREFIX
        oss << "$r";
#else
        oss << "r";
#endif

        oss << std::left << std::setw(2) << GPR;

        return oss.str();
    }
#endif

    std::string TextualizeLA32Name(const std::string& name) noexcept
    {
        int alignment = LA32_TEXTUALIZE_NAME_ALIGNMENT - (name.length() % LA32_TEXTUALIZE_NAME_ALIGNMENT);

        std::ostringstream oss;

        oss << name;

        for (int i = 0; i < alignment; i++)
            oss << " ";

        return oss.str();
    }

    std::string TextualizeLA32Type2R(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ());

        return oss.str();
    }
    
    std::string TextualizeLA32Type3R(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRK());

        return oss.str();
    }

    std::string TextualizeLA32Type4R(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRK()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRA());

        return oss.str();
    }

    std::string TextualizeLA32Type2RI8(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << "0x" << std::hex << std::setw(2) << std::setfill('0') << insn.GetImm8();

        return oss.str();
    }

    std::string TextualizeLA32Type2RI12(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << "0x" << std::hex << std::setw(3) << std::setfill('0') << insn.GetImm12();

        return oss.str();
    }

    std::string TextualizeLA32Type2RI14(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << "0x" << std::hex << std::setw(4) << std::setfill('0') << insn.GetImm14();

        return oss.str();
    }

    std::string TextualizeLA32Type2RI16(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << "0x" << std::hex << std::setw(4) << std::setfill('0') << insn.GetImm16();

        return oss.str();
    }

    std::string TextualizeLA32TypeX2RI5(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << insn.GetExImm5();

        return oss.str();
    }

    std::string TextualizeLA32Type1RI21(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << "0x" << std::hex << std::setw(6) << std::setfill('0') << insn.GetImm21();

        return oss.str();
    }

    std::string TextualizeLA32Type2ROffs16(const LA32Instruction &insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << TextualizeLA32GPR(insn.GetRJ()) << ", ";
        oss << "0x" << std::hex << std::setw(5) << std::setfill('0') << (insn.GetImm16() << 2);

        return oss.str();
    }

    std::string TextualizeLA32TypeOffs26(const LA32Instruction &insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << "0x" << std::hex << std::setw(7) << std::setfill('0') << (insn.GetImm26() << 2);

        return oss.str();
    }

    std::string TextualizeLA32TypeX1RI20(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << TextualizeLA32GPR(insn.GetRD()) << ", ";
        oss << "0x" << std::hex << std::setw(5) << std::setfill('0') << insn.GetExImm20();

        return oss.str();
    }

    std::string TextualizeLA32TypeI26(const LA32Instruction& insn) noexcept
    {
        std::ostringstream oss;

        oss << TextualizeLA32Name(insn.GetName());
        oss << "0x" << std::hex << std::setw(7) << std::setfill('0') << insn.GetImm26();

        return oss.str();
    }
}
