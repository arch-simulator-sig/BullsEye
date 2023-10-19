#
# To initialize BullsEye global variables
#

#
export K221_BE_GLOBALCONFIG="true"


#
export K221_BE_ROOT="$(dirname $(readlink -f "$BASH_SOURCE"))"

export K221_BE_GLOBALSCRIPTS="$K221_BE_ROOT/.globalscripts.sh"


# user specific configuration
export K221_DS232_VPROJECT_PATH=

source "$K221_BE_ROOT/.globalconfig.user.sh"



# Configure YASIO variables
export K221_YASIO_ROOT="$K221_BE_ROOT/yasio"
export K221_YASIO_MAIN="$K221_BE_ROOT/yasio"

export K221_CFLAGS_INC_YASIO="-I$K221_BE_ROOT -I$K221_YASIO_ROOT"

source "$K221_YASIO_ROOT/.globalconfig.sh"


# Configure BullsEye main variables
export K221_BE_MAIN_ROOT="$K221_BE_ROOT/main"
export K221_BE_MAIN_MAIN="$K221_BE_ROOT/main"

export K221_CFLAGS_INC_BE_MAIN="-I$K221_BE_MAIN_ROOT"


# Configure BullsEye Jasse2 for LA32 variables
export K221_BE_JASSE2_LA32_ROOT="$K221_BE_MAIN_ROOT/isa/la32"
export K221_BE_JASSE2_LA32_MAIN="$K221_BE_MAIN_ROOT/isa/la32"

export K221_CFLAGS_INC_BE_JASSE2_LA32="-I$K221_BE_JASSE2_LA32_ROOT"

source "$K221_BE_JASSE2_LA32_ROOT/.globalconfig.sh"


# Configure BullsEye Jasse for MIPS32 variables
#export K221_BE_JASSE_MIPS32_ROOT="$K221_BE_MAIN_ROOT/isa/mips32"
#
#

# Configure BullsEye NSCSCC-Single LA32 SoC variables
export K221_BE_N1_SOC_LA32_ROOT="$K221_BE_MAIN_ROOT/nscscc_single/soc/la32"
export K221_BE_N1_SOC_LA32_MAIN="$K221_BE_MAIN_ROOT/nscscc_single/soc/la32"

export K221_CFLAGS_INC_BE_N1_SOC_LA32="-I$K221_BE_N1_SOC_LA32_ROOT"

source "$K221_BE_N1_SOC_LA32_ROOT/.globalconfig.sh"


# Configure BullsEye NSCSCC-Single MIPS32 SoC variables
export K221_BE_N1_SOC_MIPS32_ROOT="$K221_BE_MAIN_ROOT/nscscc_single/soc/mips32"


#
export K221_BE_N1_COREMARK_ROOT="$K221_BE_MAIN_ROOT/nscscc_single/coremark"
export K221_BE_N1_COREMARK_LA32R_BUILD_SCRIPT="$K221_BE_N1_COREMARK_ROOT/build-la32r.sh"
export K221_BE_N1_COREMARK_LA32R_BUILD_OUTPUT="$K221_BE_N1_COREMARK_ROOT/build-la32r"
export K221_BE_N1_COREMARK_LA32R_BINARY="$K221_BE_N1_COREMARK_LA32_BUILD_OUTPUT/coremark.bin"
export K221_BE_N1_COREMARK_LA32R_ELF="$K221_BE_N1_COREMARK_LA32_BUILD_OUTPUT/coremark.elf"
