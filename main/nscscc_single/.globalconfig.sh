#
if [[ "$K221_BE_GLOBALCONFIG" != "true" ]]; then
    echo "You need to run BullsEye global config script first."
    exit 1
fi

# Configure BullsEye NSCSCC-Single SoC kit variables
export K221_BE_N1_SOC_ROOT="$K221_BE_N1_ROOT/soc"
export K221_BE_N1_SOC_MAIN="$K221_BE_N1_ROOT/soc"

export K221_CFLAGS_INC_BE_N1_SOC="-I$K221_BE_N1_SOC_ROOT"

gen_autoinclude "BE_N1_SOC" "$K221_BE_N1_SOC_ROOT" "BullsEye NSCSCC-Single SoC kit"

source "$K221_BE_N1_SOC_ROOT/.globalconfig.sh"
