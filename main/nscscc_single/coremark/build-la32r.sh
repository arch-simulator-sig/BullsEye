COMPILER="loongarch32r-linux-gnusf-gcc"
LINKER="loongarch32r-linux-gnusf-ld"
ASSEMBLER="loongarch32r-linux-gnusf-as"
OBJCOPY="loongarch32r-linux-gnusf-objcopy"
OBJDUMP="loongarch32r-linux-gnusf-objdump"

BUILD_PATH="build-la32r"
BUILD_FILE="coremark"
BUILD_ARGS="-nostdlib -fno-builtin -mabi=ilp32s -g -O2 -DCOMPILER_LA32R_LINUX_GNUSF -DPERFORMANCE_RUN=1"

#
eval "mkdir $BUILD_PATH"

# Compile objects
eval "$COMPILER $BUILD_ARGS -c la_init.S        -o $BUILD_PATH/la_init.o"
eval "$COMPILER $BUILD_ARGS -c core_list_join.c -o $BUILD_PATH/core_list_join.o"
eval "$COMPILER $BUILD_ARGS -c core_main.c      -o $BUILD_PATH/core_main.o"
eval "$COMPILER $BUILD_ARGS -c core_matrix.c    -o $BUILD_PATH/core_matrix.o"
eval "$COMPILER $BUILD_ARGS -c core_portme.c    -o $BUILD_PATH/core_portme.o"
eval "$COMPILER $BUILD_ARGS -c core_state.c     -o $BUILD_PATH/core_state.o"
eval "$COMPILER $BUILD_ARGS -c core_util.c      -o $BUILD_PATH/core_util.o"
eval "$COMPILER $BUILD_ARGS -c ee_printf.c      -o $BUILD_PATH/ee_printf.o"

# Link
FILES_TO_LINK="$FILES_TO_LINK $BUILD_PATH/la_init.o"
FILES_TO_LINK="$FILES_TO_LINK $BUILD_PATH/core_main.o"
FILES_TO_LINK="$FILES_TO_LINK $BUILD_PATH/core_list_join.o"
FILES_TO_LINK="$FILES_TO_LINK $BUILD_PATH/core_matrix.o"
FILES_TO_LINK="$FILES_TO_LINK $BUILD_PATH/core_portme.o"
FILES_TO_LINK="$FILES_TO_LINK $BUILD_PATH/core_state.o"
FILES_TO_LINK="$FILES_TO_LINK $BUILD_PATH/core_util.o"
FILES_TO_LINK="$FILES_TO_LINK $BUILD_PATH/ee_printf.o"

eval "$LINKER -Ttext 0x0 -N -T la_init.ld -Map $BUILD_PATH/memmap.txt -o $BUILD_PATH/coremark.elf $FILES_TO_LINK"

# Generate binary file
eval "$OBJCOPY -O binary $BUILD_PATH/coremark.elf $BUILD_PATH/coremark.bin"

# Disassemble
eval "$OBJDUMP -D $BUILD_PATH/coremark.elf > $BUILD_PATH/coremark.txt"
