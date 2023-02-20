#pragma once
//
// MIPS32 ISA Definitions
//
// MIPS32 Release 6
//


// MIPS32-R6 opcode
#define MIPS32_OPCODE_SPECIAL                       0b000000
#define MIPS32_OPCODE_SPECIAL2                      0b011100
#define MIPS32_OPCODE_SPECIAL3                      0b011111

#define MIPS32_OPCODE_COP0                          0b010000
#define MIPS32_OPCODE_COP1                          0b010001
#define MIPS32_OPCODE_COP1X                         0b010011
#define MIPS32_OPCODE_COP2                          0b010010

#define MIPS32_OPCODE_PCREL                         0b111011

#define MIPS32_OPCODE_REGIMM                        0b000001

#define MIPS32_OPCODE_ADDI                          0b001000
#define MIPS32_OPCODE_ADDIU                         0b001001

#define MIPS32_OPCODE_ANDI                          0b001100
#define MIPS32_OPCODE_ORI                           0b001101
#define MIPS32_OPCODE_XORI                          0b001110

#define MIPS32_OPCODE_AUI                           0b001111    // LUI

#define MIPS32_OPCODE_SLTI                          0b001010
#define MIPS32_OPCODE_SLTIU                         0b001011

#define MIPS32_OPCODE_BEQ                           0b000100
#define MIPS32_OPCODE_BEQL                          0b010100
#define MIPS32_OPCODE_BGTZ                          0b000111
#define MIPS32_OPCODE_BGTZL                         0b010111
#define MIPS32_OPCODE_BLEZ                          0b000110
#define MIPS32_OPCODE_BLEZL                         0b010110
#define MIPS32_OPCODE_BNE                           0b000101
#define MIPS32_OPCODE_BNEL                          0b010101

#define MIPS32_OPCODE_J                             0b000010
#define MIPS32_OPCODE_JAL                           0b000011
#define MIPS32_OPCODE_JALX                          0b011101

#define MIPS32_OPCODE_BALC                          0b111010
#define MIPS32_OPCODE_BC                            0b110010

#define MIPS32_OPCODE_LB                            0b100000
#define MIPS32_OPCODE_LBU                           0b100100
#define MIPS32_OPCODE_LH                            0b100001
#define MIPS32_OPCODE_LHU                           0b100101
#define MIPS32_OPCODE_LW                            0b100011

#define MIPS32_OPCODE_SB                            0b101000
#define MIPS32_OPCODE_SH                            0b101001
#define MIPS32_OPCODE_SW                            0b101011

#define MIPS32_OPCODE_LDC1                          0b110101
#define MIPS32_OPCODE_LWC1                          0b110001

#define MIPS32_OPCODE_SDC1                          0b111101
#define MIPS32_OPCODE_SWC1                          0b111001

#define MIPS32_OPCODE_POP06                         0b000110
#define MIPS32_OPCODE_POP07                         0b000111
#define MIPS32_OPCODE_POP10                         0b001000
#define MIPS32_OPCODE_POP26                         0b010110
#define MIPS32_OPCODE_POP27                         0b010111
#define MIPS32_OPCODE_POP30                         0b011000
#define MIPS32_OPCODE_POP66                         0b110110
#define MIPS32_OPCODE_POP76                         0b111110


// MIPS32-R6 function (Funct-6) bits
#define MIPS32_FUNCT_ADD                            0b100000
#define MIPS32_FUNCT_ADDU                           0b100001
#define MIPS32_FUNCT_SUB                            0b100010
#define MIPS32_FUNCT_SUBU                           0b100011

#define MIPS32_FUNCT_SLL                            0b000000
#define MIPS32_FUNCT_SLLV                           0b000100
#define MIPS32_FUNCT_SRL                            0b000010
#define MIPS32_FUNCT_SRLV                           0b000110
#define MIPS32_FUNCT_SRA                            0b000011
#define MIPS32_FUNCT_SRAV                           0b000111

#define MIPS32_FUNCT_AND                            0b100100
#define MIPS32_FUNCT_NOR                            0b100111
#define MIPS32_FUNCT_OR                             0b100101
#define MIPS32_FUNCT_XOR                            0b100110

#define MIPS32_FUNCT_SLT                            0b101010
#define MIPS32_FUNCT_SLTU                           0b101011

#define MIPS32_FUNCT_SELEQZ                         0b110101
#define MIPS32_FUNCT_SELNEZ                         0b110111

#define MIPS32_FUNCT_SOP30                          0b011000
#define MIPS32_FUNCT_SOP31                          0b011001
#define MIPS32_FUNCT_SOP32                          0b011010

#define MIPS32_FUNCT_JALR                           0b001001
#define MIPS32_FUNCT_JR                             0b001000

#define MIPS32_FUNCT_LBE                            0b101100
#define MIPS32_FUNCT_LBUE                           0b101000
#define MIPS32_FUNCT_LHE                            0b101101
#define MIPS32_FUNCT_LHUE                           0b101001
#define MIPS32_FUNCT_LWE                            0b101111

#define MIPS32_FUNCT_SBE                            0b011100
#define MIPS32_FUNCT_SHE                            0b011101
#define MIPS32_FUNCT_SWE                            0b011111

#define MIPS32_FUNCT_LL                             0b110110
#define MIPS32_FUNCT_LLE                            0b101110
#define MIPS32_FUNCT_SC                             0b100110
#define MIPS32_FUNCT_SCE                            0b011110

#define MIPS32_FUNCT_LSA                            0b000101

#define MIPS32_FUNCT_CLO                            0b010001
#define MIPS32_FUNCT_CLZ                            0b010000

#define MIPS32_FUNCT_EXT                            0b000000
#define MIPS32_FUNCT_INS                            0b000100

#define MIPS32_FUNCT_SYSCALL                        0b001100
#define MIPS32_FUNCT_BREAK                          0b001101
#define MIPS32_FUNCT_DERET                          0b011111
#define MIPS32_FUCNT_ERET                           0b011000
#define MIPS32_FUNCT_SDBBP                          0b001110
#define MIPS32_FUNCT_WAIT                           0b100000

#define MIPS32_FUNCT_TEQ                            0b110100
#define MIPS32_FUNCT_TGE                            0b110000
#define MIPS32_FUNCT_TGEU                           0b110001
#define MIPS32_FUNCT_TLT                            0b110010
#define MIPS32_FUNCT_TLTU                           0b110011
#define MIPS32_FUNCT_TNE                            0b110110

#define MIPS32_FUNCT_MOV                            0b000110

#define MIPS32_FUNCT_ABS                            0b000101
#define MIPS32_FUNCT_BSHFL                          0b100000
#define MIPS32_FUNCT_CEIL_L                         0b001010
#define MIPS32_FUNCT_CEIL_W                         0b001110
#define MIPS32_FUNCT_ROUND_L                        0b001000
#define MIPS32_FUNCT_ROUND_W                        0b001100
#define MIPS32_FUNCT_TRUNC_L                        0b001001
#define MIPS32_FUNCT_TRUNC_W                        0b001101

#define MIPS32_FUNCT_FSEL                           0b010000
#define MIPS32_FUNCT_FSELEQZ                        0b010100
#define MIPS32_FUNCT_FSELNEZ                        0b010111
#define MIPS32_FUNCT_FADD                           0b000000
#define MIPS32_FUNCT_FSUB                           0b000001

#define MIPS32_FUNCT_CLASS                          0b011011
#define MIPS32_FUNCT_RSQRT                          0b010110
#define MIPS32_FUNCT_SQRT                           0b000100

#define MIPS32_FUNCT_MADDF                          0b011000
#define MIPS32_FUNCT_MSUBF                          0b011001
#define MIPS32_FUNCT_MAX                            0b011110
#define MIPS32_FUNCT_MAXA                           0b011111
#define MIPS32_FUNCT_MIN                            0b011100
#define MIPS32_FUNCT_MINA                           0b011101
#define MIPS32_FUNCT_MUL                            0b000010
#define MIPS32_FUNCT_NEG                            0b000111

#define MIPS32_FUNCT_RECIP                          0b010101
#define MIPS32_FUNCT_RINT                           0b011010

#define MIPS32_FUNCT_LDXC1                          0b000001
#define MIPS32_FUNCT_LUXC1                          0b000101

#define MIPS32_FUNCT_FLOOR_L                        0b001011
#define MIPS32_FUNCT_FLOOR_W                        0b001111

#define MIPS32_FUNCT_FPDIV                          0b000011

#define MIPS32_FUNCT_ALNV_PS                        0b011110

#define MIPS32_FUNCT_CVT_D                          0b100001
#define MIPS32_FUNCT_CVT_L                          0b100101
#define MIPS32_FUNCT_CVT_S                          0b100000
#define MIPS32_FUNCT_CVT_W                          0b100100

#define MIPS32_FUNCT_RDHWR                          0b111011

#define MIPS32_FUNCT_SYNC                           0b001111

#define MIPS32_FUNCT_CACHE                          0b100101
#define MIPS32_FUNCT_CACHEE                         0b011011

#define MIPS32_FUNCT_PREF                           0b110101
#define MIPS32_FUNCT_PREFE                          0b100011

#define MIPS32_FUNCT_GINV                           0b111101

#define MIPS32_FUNCT_TLBINV                         0b000011
#define MIPS32_FUNCT_TLBINVF                        0b000100
#define MIPS32_FUNCT_TLBP                           0b001000
#define MIPS32_FUNCT_TLBR                           0b000001
#define MIPS32_FUNCT_TLBWI                          0b000010
#define MIPS32_FUNCT_TLBWR                          0b000110

#define MIPS32_FUNCT_CRC                            0b001111
