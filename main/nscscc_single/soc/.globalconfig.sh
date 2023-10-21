#
if [[ "$K221_BE_GLOBALCONFIG" != "true" ]]; then
    echo "You need to run BullsEye global config script first."
    exit 1
fi


# Configure BullsEye NSCSCC-Single LA32 SoC variables
export K221_BE_N1_SOC_LA32_ROOT="$K221_BE_N1_SOC_ROOT/la32"
export K221_BE_N1_SOC_LA32_MAIN="$K221_BE_N1_SOC_ROOT/la32"

export K221_CFLAGS_INC_BE_N1_SOC_LA32="-I$K221_BE_N1_SOC_LA32_ROOT"

gen_autoinclude "BE_N1_SOC_LA32" "$K221_BE_N1_SOC_LA32_ROOT" "BullsEye NSCSCC-Single LA32 SoC kit"

source "$K221_BE_N1_SOC_LA32_ROOT/.globalconfig.sh"


# Configure BullsEye NSCSCC-Single MIPS32 SoC variables
export K221_BE_N1_SOC_MIPS32_ROOT="$K221_BE_N1_SOC_ROOT/mips32"
export K221_BE_N1_SOC_MIPS32_MAIN="$K221_BE_N1_SOC_ROOT/mips32"

export K221_CFLAGS_INC_BE_N1_SOC_MIPS32="-I$K221_BE_N1_SOC_MIPS32_ROOT"

gen_autoinclude "BE_N1_SOC_MIPS32" "$K221_BE_N1_SOC_MIPS32_ROOT" "BullsEye NSCSCC-Single MIPS32 SoC kit"

source "$K221_BE_N1_SOC_MIPS32_ROOT/.globalconfig.sh"

