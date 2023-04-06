#pragma once
//
// MIPS32 ISA Definitions
//
// MIPS32 Release 5
//


#define __HEADER_MIPS32_R5_DEINITIONS


// MIPS32-R5 opcode
#define MIPS32_OPCODE_SPECIAL                       0b000000 
#define MIPS32_OPCODE_SPECIAL2                      0b011100
#define MIPS32_OPCODE_SPECIAL3                      0b011111

#define MIPS32_OPCODE_REGIMM                        0b000001

#define MIPS32_OPCODE_COP0                          0b010000
#define MIPS32_OPCODE_COP1                          0b010001
#define MIPS32_OPCODE_COP1X                         0b010011
#define MIPS32_OPCODE_COP2                          0b010010

#define MIPS32_OPCODE_ADDI                          0b001000
#define MIPS32_OPCODE_ADDIU                         0b001001

#define MIPS32_OPCODE_ANDI                          0b001100
#define MIPS32_OPCODE_ORI                           0b001101
#define MIPS32_OPCODE_XORI                          0b001110

#define MIPS32_OPCODE_SLTI                          0b001010
#define MIPS32_OPCODE_SLTIU                         0b001011

#define MIPS32_OPCODE_LUI                           0b001111

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

#define MIPS32_OPCODE_LB                            0b100000
#define MIPS32_OPCODE_LBU                           0b100100
#define MIPS32_OPCODE_LH                            0b100001
#define MIPS32_OPCODE_LHU                           0b100101
#define MIPS32_OPCODE_LW                            0b100011

#define MIPS32_OPCODE_LWL                           0b100010
#define MIPS32_OPCODE_LWR                           0b100110

#define MIPS32_OPCODE_SB                            0b101000
#define MIPS32_OPCODE_SH                            0b101001
#define MIPS32_OPCODE_SW                            0b101011

#define MIPS32_OPCODE_SWL                           0b101010
#define MIPS32_OPCODE_SWR                           0b101110

#define MIPS32_OPCODE_LL                            0b110000
#define MIPS32_OPCODE_SC                            0b111000

#define MIPS32_OPCODE_LDC1                          0b110101
#define MIPS32_OPCODE_LDC2                          0b110110
#define MIPS32_OPCODE_LWC1                          0b110001
#define MIPS32_OPCODE_LWC2                          0b110010

#define MIPS32_OPCODE_SDC1                          0b111101
#define MIPS32_OPCODE_SDC2                          0b111110
#define MIPS32_OPCODE_SWC1                          0b111001
#define MIPS32_OPCODE_SWC2                          0b111010

#define MIPS32_OPCODE_PREF                          0b110011

#define MIPS32_OPCODE_CACHE                         0b101111



// MIPS32-R5 function bits (Funct-6) for opcode range SPECIAL
#define MIPS32_FUNCT_SPECIAL_ADD                    0b100000
#define MIPS32_FUNCT_SPECIAL_ADDU                   0b100001
#define MIPS32_FUNCT_SPECIAL_AND                    0b100100
#define MIPS32_FUNCT_SPECIAL_BREAK                  0b001101
#define MIPS32_FUNCT_SPECIAL_DIV                    0b011010
#define MIPS32_FUNCT_SPECIAL_DIVU                   0b011011
#define MIPS32_FUNCT_SPECIAL_JALR                   0b001001
#define MIPS32_FUNCT_SPECIAL_JR                     0b001000
#define MIPS32_FUNCT_SPECIAL_MFHI                   0b010000
#define MIPS32_FUNCT_SPECIAL_MFLO                   0b010010
#define MIPS32_FUNCT_SPECIAL_MOVF                   0b000001
#define MIPS32_FUNCT_SPECIAL_MOVN                   0b001011
#define MIPS32_FUNCT_SPECIAL_MOVCI                  0b000001
#define MIPS32_FUNCT_SPECIAL_MOVZ                   0b001010
#define MIPS32_FUNCT_SPECIAL_MTHI                   0b010001
#define MIPS32_FUNCT_SPECIAL_MTLO                   0b010011
#define MIPS32_FUNCT_SPECIAL_MULT                   0b011000
#define MIPS32_FUNCT_SPECIAL_MULTU                  0b011001
#define MIPS32_FUNCT_SPECIAL_NOR                    0b100111
#define MIPS32_FUNCT_SPECIAL_OR                     0b100101
#define MIPS32_FUNCT_SPECIAL_SRL                    0b000010
#define MIPS32_FUNCT_SPECIAL_SRLV                   0b000110
#define MIPS32_FUNCT_SPECIAL_SLL                    0b000000
#define MIPS32_FUNCT_SPECIAL_SLLV                   0b000100
#define MIPS32_FUNCT_SPECIAL_SLT                    0b101010
#define MIPS32_FUNCT_SPECIAL_SLTU                   0b101011
#define MIPS32_FUNCT_SPECIAL_SRA                    0b000011
#define MIPS32_FUNCT_SPECIAL_SRAV                   0b000111
#define MIPS32_FUNCT_SPECIAL_SUB                    0b100010
#define MIPS32_FUNCT_SPECIAL_SUBU                   0b100011
#define MIPS32_FUNCT_SPECIAL_SYNC                   0b001111
#define MIPS32_FUNCT_SPECIAL_SYSCALL                0b001100
#define MIPS32_FUNCT_SPECIAL_TEQ                    0b110100
#define MIPS32_FUNCT_SPECIAL_TGE                    0b110000
#define MIPS32_FUNCT_SPECIAL_TGEU                   0b110001
#define MIPS32_FUNCT_SPECIAL_TLT                    0b110010
#define MIPS32_FUNCT_SPECIAL_TLTU                   0b110011
#define MIPS32_FUNCT_SPECIAL_TNE                    0b110110
#define MIPS32_FUNCT_SPECIAL_XOR                    0b100110

// MIPS32-R5 function bits (Funct-6) for opcode range SPECIAL2
#define MIPS32_FUNCT_SPECIAL2_CLO                   0b100001
#define MIPS32_FUNCT_SPECIAL2_CLZ                   0b100000
#define MIPS32_FUNCT_SPECIAL2_MADD                  0b000000
#define MIPS32_FUNCT_SPECIAL2_MADDU                 0b000001
#define MIPS32_FUNCT_SPECIAL2_MSUB                  0b000100
#define MIPS32_FUNCT_SPECIAL2_MSUBU                 0b000101
#define MIPS32_FUNCT_SPECIAL2_MUL                   0b000010
#define MIPS32_FUNCT_SPECIAL2_SDBBP                 0b111111

// MIPS32-R5 function bits (Funct-6) for opcode range SPECIAL3
#define MIPS32_FUNCT_SPECIAL3_BSHFL                 0b100000
#define MIPS32_FUNCT_SPECIAL3_CACHEE                0b011011
#define MIPS32_FUNCT_SPECIAL3_EXT                   0b000000
#define MIPS32_FUNCT_SPECIAL3_INS                   0b000100
#define MIPS32_FUNCT_SPECIAL3_LBE                   0b101100 
#define MIPS32_FUNCT_SPECIAL3_LBUE                  0b101000
#define MIPS32_FUNCT_SPECIAL3_LHE                   0b101101
#define MIPS32_FUNCT_SPECIAL3_LHUE                  0b101001
#define MIPS32_FUNCT_SPECIAL3_LLE                   0b101110
#define MIPS32_FUNCT_SPECIAL3_LWE                   0b101111
#define MIPS32_FUNCT_SPECIAL3_LWLE                  0b011001
#define MIPS32_FUNCT_SPECIAL3_LWRE                  0b011010
#define MIPS32_FUNCT_SPECIAL3_PREFE                 0b100011
#define MIPS32_FUNCT_SPECIAL3_RDHWR                 0b111011
#define MIPS32_FUNCT_SPECIAL3_SBE                   0b011100
#define MIPS32_FUNCT_SPECIAL3_SCE                   0b011110
#define MIPS32_FUNCT_SPECIAL3_SHE                   0b011101
#define MIPS32_FUNCT_SPEICAL3_SWE                   0b011111
#define MIPS32_FUNCT_SPECIAL3_SWLE                  0b100001
#define MIPS32_FUNCT_SPECIAL3_SWRE                  0b100010

// MIPS32-R5 function bits (Funct-6) for opcode range COP0
#define MIPS32_FUNCT_COP0_DERET                     0b011111
#define MIPS32_FUNCT_COP0_ERET                      0b011000
#define MIPS32_FUNCT_COP0_TLBINV                    0b000011
#define MIPS32_FUNCT_COP0_TLBINVF                   0b000100
#define MIPS32_FUNCT_COP0_TLBP                      0b001000
#define MIPS32_FUNCT_COP0_TLBR                      0b000001
#define MIPS32_FUNCT_COP0_TLBWI                     0b000010
#define MIPS32_FUNCT_COP0_TLBWR                     0b000110
#define MIPS32_FUNCT_COP0_WAIT                      0b100000

// MIPS32-R5 function bits (Funct-6) for opcode range COP1
#define MIPS32_FUNCT_COP1_ABS                       0b000101
#define MIPS32_FUNCT_COP1_ADD                       0b000000
#define MIPS32_FUNCT_COP1_CEIL_L                    0b001010
#define MIPS32_FUNCT_COP1_CEIL_W                    0b001110
#define MIPS32_FUNCT_COP1_CVT_D                     0b100001
#define MIPS32_FUNCT_COP1_CVT_L                     0b100101
#define MIPS32_FUNCT_COP1_CVT_PS                    0b100110
#define MIPS32_FUNCT_COP1_CVT_S                     0b100000
#define MIPS32_FUNCT_COP1_CVT_S_PL                  0b101000
#define MIPS32_FUNCT_COP1_CVT_S_PU                  0b100000
#define MIPS32_FUNCT_COP1_CVT_W                     0b100100
#define MIPS32_FUNCT_COP1_DIV                       0b000011
#define MIPS32_FUNCT_COP1_FLOOR_L                   0b001011
#define MIPS32_FUNCT_COP1_FLOOR_W                   0b001111
#define MIPS32_FUNCT_COP1_MOV                       0b000110
#define MIPS32_FUNCT_COP1_MOVF                      0b010001
#define MIPS32_FUNCT_COP1_MOVN                      0b010011
#define MIPS32_FUNCT_COP1_MOVZ                      0b010010
#define MIPS32_FUNCT_COP1_MUL                       0b000010
#define MIPS32_FUNCT_COP1_NEG                       0b000111
#define MIPS32_FUNCT_COP1_PLL                       0b101100
#define MIPS32_FUNCT_COP1_PLU                       0b101101
#define MIPS32_FUNCT_COP1_PUL                       0b101110
#define MIPS32_FUNCT_COP1_PUU                       0b101111
#define MIPS32_FUNCT_COP1_RECIP                     0b010101
#define MIPS32_FUNCT_COP1_ROUND_L                   0b001000
#define MIPS32_FUNCT_COP1_ROUND_W                   0b001100
#define MIPS32_FUCNT_COP1_RSQRT                     0b010110
#define MIPS32_FUNCT_COP1_SQRT                      0b000100
#define MIPS32_FUNCT_COP1_SUB                       0b000001
#define MIPS32_FUNCT_COP1_TRUNC_L                   0b001001
#define MIPS32_FUNCT_COP1_TRUNC_W                   0b001101

// MIPS32-R5 function bits (Funct-6) for opcode range COP1X
#define MIPS32_FUNCT_COP1X_ALNV_PS                  0b011110
#define MIPS32_FUNCT_COP1X_LDXC1                    0b000001 
#define MIPS32_FUNCT_COP1X_LUXC1                    0b000101
#define MIPS32_FUNCT_COP1X_LWXC1                    0b000000
#define MIPS32_FUNCT_COP1X_PREFX                    0b001111
#define MIPS32_FUNCT_COP1X_SDXC1                    0b001001
#define MIPS32_FUNCT_COP1X_SUXC1                    0b001101
#define MIPS32_FUNCT_COP1X_SWXC1                    0b001000


// MIPS32-R5 rt bits (RT-Funct-5) for opcode range REGIMM
#define MIPS32_RT_REGIMM_BLTZ                       0b00000
#define MIPS32_RT_REGIMM_BGEZ                       0b00001
#define MIPS32_RT_REGIMM_BLTZL                      0b00010
#define MIPS32_RT_REGIMM_BGEZL                      0b00011
#define MIPS32_RT_REGIMM_TGEI                       0b01000
#define MIPS32_RT_REGIMM_TGEIU                      0b01001
#define MIPS32_RT_REGIMM_TLTI                       0b01010
#define MIPS32_RT_REGIMM_TLTIU                      0b01011
#define MIPS32_RT_REGIMM_TEQI                       0b01100
#define MIPS32_RT_REGIMM_TNEI                       0b01110
#define MIPS32_RT_REGIMM_BLTZAL                     0b10000
#define MIPS32_RT_REGIMM_BGEZAL                     0b10001
#define MIPS32_RT_REGIMM_BLTZALL                    0b10010
#define MIPS32_RT_REGIMM_BGEZALL                    0b10011
#define MIPS32_RT_REGIMM_SYNCI                      0b11111
