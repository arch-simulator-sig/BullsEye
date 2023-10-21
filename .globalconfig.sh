#
# To initialize BullsEye global variables
#

# Convert WSL path into Windows for WSL env better performance
convert_wsl_path() {

    local DISK_SYMBOL_TO_CONVERT=(\
        "a" "b" "c" "d" "e" "f" "g" "h" "i" "j" "k" "l" "m" "n" "o" "p" "q" "r" "s" "t" "u" "v" "w" "x" "y" "z")

    local CONV=$1

    for SYMBOL in ${DISK_SYMBOL_TO_CONVERT[@]}
    do
        if [[ "$1" =~ ^\/mnt\/$SYMBOL\/.* ]]; then
            CONV=${CONV//\//\\}
            CONV=${CONV//\\mnt\\$SYMBOL\\/${SYMBOL^^}:\\}
            CONV=${CONV//\\/\\\\}
            break
        fi
    done

    echo $CONV

    return 0
}


# Auto Include header generation 
gen_autoinclude() {

    local DESCRIPTION="$1"

    local WINPATH=

    if [[ -n "$3" ]]; then
        DESCRIPTION="$3"
    fi

    echo "// Auto include macro for $DESCRIPTION"                                   >> $K221_BE_AUTOINCLUDE
    echo "#ifdef _WIN32"                                                            >> $K221_BE_AUTOINCLUDE

    if [[ "$K221_BE_WSLCONV_ENABLED" == "true" ]]; then
        WINPATH=$(convert_wsl_path "$2")
        echo "#define __AUTOINC_$1(file) $WINPATH\\\\file"                          >> $K221_BE_AUTOINCLUDE
    fi

    echo "#else"                                                                    >> $K221_BE_AUTOINCLUDE
    echo "#define __AUTOINC_$1(file) $2/file"                                       >> $K221_BE_AUTOINCLUDE
    echo "#endif"                                                                   >> $K221_BE_AUTOINCLUDE
    echo ""                                                                         >> $K221_BE_AUTOINCLUDE
    echo "#define AUTOINC_$1(file) __STR1(__AUTOINC_$1(file))"                      >> $K221_BE_AUTOINCLUDE
    echo ""                                                                         >> $K221_BE_AUTOINCLUDE
}

pregen_autoinclude() {
    eval "rm -f \"$K221_BE_AUTOINCLUDE\""

    echo "#pragma once"                                                             >> $K221_BE_AUTOINCLUDE
    echo ""                                                                         >> $K221_BE_AUTOINCLUDE
    echo "#ifndef __HEADER_AUTO_C_INCLUDE"                                          >> $K221_BE_AUTOINCLUDE
    echo "#define __HEADER_AUTO_C_INCLUDE"                                          >> $K221_BE_AUTOINCLUDE
    echo ""                                                                         >> $K221_BE_AUTOINCLUDE
    echo "#define __STR0(x) #x"                                                     >> $K221_BE_AUTOINCLUDE
    echo "#define __STR1(x) __STR0(x)"                                              >> $K221_BE_AUTOINCLUDE
    echo ""                                                                         >> $K221_BE_AUTOINCLUDE
}

postgen_autoinclude() {
    echo "#endif"                                                                   >> $K221_BE_AUTOINCLUDE
}


#
export K221_BE_GLOBALCONFIG="true"

export K221_BE_WSLCONV_ENABLED="true"


#
export K221_BE_ROOT="$(dirname $(readlink -f "$BASH_SOURCE"))"

export K221_BE_GLOBALSCRIPTS="$K221_BE_ROOT/.globalscripts.sh"

export K221_BE_AUTOINCLUDE="$K221_BE_ROOT/autoinclude.h"

pregen_autoinclude

gen_autoinclude "BE_ROOT" "$K221_BE_ROOT" "BullsEye root"


# user specific configuration
export K221_DS232_VPROJECT_PATH=

source "$K221_BE_ROOT/.globalconfig.user.sh"



# Configure YASIO variables
export K221_YASIO_ROOT="$K221_BE_ROOT/yasio"
export K221_YASIO_MAIN="$K221_BE_ROOT/yasio"

export K221_CFLAGS_INC_YASIO="-I$K221_BE_ROOT -I$K221_YASIO_ROOT"

gen_autoinclude "YASIO" "$K221_YASIO_ROOT" "YASIO"

source "$K221_YASIO_ROOT/.globalconfig.sh"


# Configure BullsEye main variables
export K221_BE_MAIN_ROOT="$K221_BE_ROOT/main"
export K221_BE_MAIN_MAIN="$K221_BE_ROOT/main"

export K221_CFLAGS_INC_BE_MAIN="-I$K221_BE_MAIN_ROOT"

gen_autoinclude "BE_MAIN" "$K221_BE_MAIN_ROOT" "BullsEye main"


# Configure BullsEye main C-infrastructure variables
export K221_BE_COMMON_ROOT="$K221_BE_MAIN_ROOT/common"
export K221_BE_COMMON_MAIN="$K221_BE_MAIN_ROOT/common"

export K221_CFLAGS_INC_BE_COMMON="-I$K221_BE_COMMON_ROOT"

gen_autoinclude "BE_COMMON" "$K221_BE_COMMON_ROOT" "BullsEye main C-infrastructure"

source "$K221_BE_COMMON_ROOT/.globalconfig.sh"


# Configure BullsEye Jasse kit
export K221_BE_JASSE_ROOT="$K221_BE_MAIN_ROOT/isa"
export K221_BE_JASSE_MAIN="$K221_BE_MAIN_ROOT/isa"

export K221_CFLAGS_INC_BE_JASSE="-I$K221_BE_JASSE_ROOT"

gen_autoinclude "BE_JASSE" "$K221_BE_JASSE_ROOT" "BullsEye Jasse"

source "$K221_BE_JASSE_ROOT/.globalconfig.sh"


# Configure BullsEye NSCSCC-Single kit variables
export K221_BE_N1_ROOT="$K221_BE_MAIN_ROOT/nscscc_single"
export K221_BE_N1_MAIN="$K221_BE_MAIN_ROOT/nscscc_single"

export K221_CFLAGS_INC_BE_N1="-I$K221_BE_N1_ROOT"

gen_autoinclude "BE_N1" "$K221_BE_N1_ROOT" "BullsEye NSCSCC-Single kit root"

source "$K221_BE_N1_ROOT/.globalconfig.sh"


#
export K221_BE_N1_COREMARK_ROOT="$K221_BE_MAIN_ROOT/nscscc_single/coremark"
export K221_BE_N1_COREMARK_LA32R_BUILD_SCRIPT="$K221_BE_N1_COREMARK_ROOT/build-la32r.sh"
export K221_BE_N1_COREMARK_LA32R_BUILD_OUTPUT="$K221_BE_N1_COREMARK_ROOT/build-la32r"
export K221_BE_N1_COREMARK_LA32R_BINARY="$K221_BE_N1_COREMARK_LA32_BUILD_OUTPUT/coremark.bin"
export K221_BE_N1_COREMARK_LA32R_ELF="$K221_BE_N1_COREMARK_LA32_BUILD_OUTPUT/coremark.elf"


#
export K221_CFLAGS_INC_VERILATOR="-I/usr/local/share/verilator/include -I/usr/local/share/verilator/include/vltstd"


#
postgen_autoinclude
