COMPILER="gcc"
LINKER="ld"
ASSEMBLER="as"
OBJCOPY="objcopy"
OBJDUMP="objdump"

BUILD_PATH="build-x86-linux"
BUILD_FILE="coremark"
BUILD_ARGS="" 
# TODO: specify flags to achieve native implementation of CoreMark
#       further modification needed in core_portme.h & core_portme.c

#
eval "mkdir $BUILD_PATH"

# Compile and Link
FILES_TO_COMPILE="$FILES_TO_COMPILE core_main.c"
FILES_TO_COMPILE="$FILES_TO_COMPILE core_list_join.c"
FILES_TO_COMPILE="$FILES_TO_COMPILE core_matrix.c"
FILES_TO_COMPILE="$FILES_TO_COMPILE core_portme.c"
FILES_TO_COMPILE="$FILES_TO_COMPILE core_state.c"
FILES_TO_COMPILE="$FILES_TO_COMPILE core_util.c"
FILES_TO_COMPILE="$FILES_TO_COMPILE ee_printf.c"

eval "$COMPILER -o $BUILD_PATH/coremark $FILES_TO_COMPILE"

# Generate binary file
eval "$OBJCOPY -O binary $BUILD_PATH/coremark $BUILD_PATH/coremark.bin"

# Disassemble
eval "$OBJDUMP -D $BUILD_PATH/coremark > $BUILD_PATH/coremark.txt"
