#
if [[ "$K221_BE_GLOBALCONFIG" != "true" ]]; then
    echo "You need to run BullsEye global config script first."
    exit 1
fi


# Configure BullsEye Jasse2 for LA32 variables
export K221_BE_JASSE2_LA32_ROOT="$K221_BE_JASSE_ROOT/la32"
export K221_BE_JASSE2_LA32_MAIN="$K221_BE_JASSE_ROOT/la32"

export K221_CFLAGS_INC_BE_JASSE2_LA32="-I$K221_BE_JASSE2_LA32_ROOT"

gen_autoinclude "BE_JASSE2_LA32" "$K221_BE_JASSE2_LA32_ROOT" "BullsEye Jasse2 for LA32"

source "$K221_BE_JASSE2_LA32_ROOT/.globalconfig.sh"


# Configure BullsEye Jasse for MIPS32 variables
export K221_BE_JASSE_MIPS32_ROOT="$K221_BE_JASSE_ROOT/mips32"
export K221_BE_JASSE_MIPS32_MAIN="$K221_BE_JASSE_ROOT/mips32"

export K221_CFLAGS_INC_BE_JASSE_MIPS32="-I$K221_BE_JASSE_MIPS32_ROOT"

gen_autoinclude "BE_JASSE_MIPS32" "$K221_BE_JASSE_MIPS32_ROOT" "BullsEye Jasse for MIPS32"

source "$K221_BE_JASSE_MIPS32_ROOT/.globalconfig.sh"
