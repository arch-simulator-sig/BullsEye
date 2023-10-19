#
if [[ "$K221_BE_GLOBALCONFIG" != "true" ]]; then
    echo "You need to run BullsEye global config script first."
    exit 1
fi

#
export K221_BE_N1_SOC_LA32_LD_LIBRARY_PATH="$K221_BE_N1_SOC_LA32_MAIN/.build"

export K221_BE_N1_SOC_LA32_LD_LIBRARY_NAME="nscscc2023-la32-soc"
export K221_BE_N1_SOC_LA32_LD_LIBRARY_FILE="lib$K221_BE_N1_SOC_LA32_LD_LIBRARY_NAME.a"

#
export K221_BE_N1_SOC_LA32_LD_LIBRARY="$K221_BE_N1_SOC_LA32_LD_LIBRARY_PATH/$K221_BE_N1_SOC_LA32_LD_LIBRARY_FILE"

