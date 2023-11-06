#
if [[ "$K221_BE_GLOBALCONFIG" != "true" ]]; then
    echo "You need to run BullsEye global config script first."
    exit 1
fi

#
source "$K221_BE_N1_SOC_LA32_DEPCONFIG"
source "$K221_BE_JASSE2_LA32_DEPCONFIG"
