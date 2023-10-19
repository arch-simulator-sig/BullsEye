#
if [[ "$K221_BE_GLOBALCONFIG" != "true" ]]; then
    echo "You need to run BullsEye global config script first."
    exit 1
fi

#
export K221_YASIO_LD_LIBRARY_PATH="$K221_YASIO_MAIN/.build"

export K221_YASIO_LD_LIBRARY_NAME="yasio"
export K221_YASIO_LD_LIBRARY_FILE="lib$K221_YASIO_LD_LIBRARY_NAME.a"

#
export K221_YASIO_LD_LIBRARY="$K221_YASIO_LD_LIBRARY_PATH/$K221_YASIO_LD_LIBRARY_FILE"
