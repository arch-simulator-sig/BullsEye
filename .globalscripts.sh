#
if [[ "$K221_BE_GLOBALCONFIG" != "true" ]]; then
    echo "You need to run BullsEye global config script first."
    exit 1
fi


# link library
link_library() {

    local USAGE="\
Usage: link_library [-L <filename>] [-l <var>]\n\
-L: Specify the library file path to export.\n\
-l: Specify the variable name to export the library file path. File path would be appended."

    local OPT_LDLIB=
    local OPT_LDLIB_VAR=

    local OPTIND=
    while getopts 'hL:l:' OPT; do
        case $OPT in
            h) echo -e "$USAGE"; return 0;;
            L) OPT_LDLIB="$OPTARG";;
            l) OPT_LDLIB_VAR="$OPTARG";;
            ?) echo -e "$USAGE"; return 1;;
        esac
    done

    #
    if [[ -n "$OPT_LDLIB_VAR" ]]; then

        if [[ -n "$OPT_LDLIB" ]]; then
            eval "$OPT_LDLIB_VAR=\"\$$OPT_LDLIB_VAR $OPT_LDLIB\""
        else
            echo "Please specify the library file by parameter \"-L\" while using \"-l\""
            return 1
        fi
    fi

    return 0
}

# make library
make_library () {

    local USAGE="\
Usage: make_library [-t <directory>] [-c] [-j <count>] [-L <filename>] [-l <var>]\n\
-t: Specify the task directory to make.\n\
-c: Clean the task directory before make.\n\
-j: Specify the number of jobs to run in parallel.\n\
-L: Specify the library file path to export.\n\
-l: Specify the variable name to export the library file path. File path would be appended."

    local MAKE_DIRECTORY=
    local MAKE_CLEAN=
    local MAKE_JOB_COUNT=1

    local OPT_LDLIB=
    local OPT_LDLIB_VAR=

    local OPTIND=
    while getopts 'ht:cj:L:l:' OPT; do
        case $OPT in
            h) echo -e "$USAGE"; return 0;;
            t) MAKE_DIRECTORY="$OPTARG";;
            c) MAKE_CLEAN="true";;
            j) MAKE_JOB_COUNT="$OPTARG";;
            L) OPT_LDLIB="-L $OPTARG";;
            l) OPT_LDLIB_VAR="-l $OPTARG";;
            ?) echo -e "$USAGE"; return 1;;
        esac
    done

    # check necessary arguments
    if [[ ! -n "$MAKE_DIRECTORY" ]]; then
        echo "Please specify the task directory by parameter \"-t\""
        return 1
    fi

    # make & clean
    echo -e "\033[33m[library make] $MAKE_DIRECTORY\033[0m"

    test -d "$MAKE_DIRECTORY"
    if [ $? -ne 0 ]; then
        echo "Cannot enter make path: $MAKE_DIRECTORY"
        echo -e "\033[1;31mFailed at make task.\033[0m"
        return 1
    fi

    if [[ "$MAKE_CLEAN" == "true" ]]; then

        eval "make -C \"$MAKE_DIRECTORY\" clean"
        if [ $? -ne 0 ]; then
            echo "Cannot perform make clean at: $MAKE_DIRECTORY"
            echo -e "\033[1;31mFailed at make task.\033[0m"
            return 1
        fi
    fi

    eval "make -C \"$MAKE_DIRECTORY\" -j $MAKE_JOB_COUNT"
    if [ $? -ne 0 ]; then
        echo -e "\033[1;31mFailed at make task.\033[0m"
        return 1
    fi

    # post make
    link_library $OPT_LDLIB $OPT_LDLIB_VAR

    #
    return 0
}

# include library
include_library () {

    local USAGE="\
Usage: include_library [-I <directory>] [-i <var>]\n\
-I: Specify the library include path to export.\n\
-i: Specify the variable name to export the library include path. GNU CFLAGS would be appended."

    local OPT_INCLUDE=
    local OPT_INCLUDE_VAR=

    local OPTIND=
    while getopts 'hI:i:' OPT; do
        case $OPT in
            h) echo -e "$USAGE"; return 0;;
            I) OPT_INCLUDE="$OPTARG";;
            i) OPT_INCLUDE_VAR="$OPTARG";;
            ?) echo -e "$USAGE"; return 1;;
        esac
    done

    #
    if [[ -n "$OPT_INCLUDE_VAR" ]]; then

        if [[ -n "$OPT_INCLUDE" ]]; then
            eval "$OPT_INCLUDE_VAR=\"\$$OPT_INCLUDE_VAR -I$OPT_INCLUDE\""
        else
            echo "Please specify the library include path by parameter \"-I\" while using \"-i\""
            return 1
        fi
    fi

    return 0
}


#
make_library_yasio () {
    make_library $* -t "$K221_YASIO_MAIN" -L "$K221_YASIO_LD_LIBRARY"
    return $?
}

#
make_library_jasse2_la32() {
    make_library $* -t "$K221_BE_JASSE2_LA32_MAIN" -L "$K221_BE_JASSE2_LA32_LD_LIBRARY"
    return $?
}

#
make_library_nscscc2023_la32_soc() {
    make_library $* -t "$K221_BE_N1_SOC_LA32_MAIN" -L "$K221_BE_N1_SOC_LA32_LD_LIBRARY"
    return $?
}


#
include_library_yasio () {
    include_library $* -I "$K221_BE_ROOT"
    include_library $* -I "$K221_YASIO_ROOT"
    return $?
}

#
include_library_jasse2_la32 () {
    include_library $* -I "$K221_BE_JASSE2_LA32_ROOT"
    return $?
}

#
include_library_nscscc2023_la32_soc () {
    include_library $* -I "$K221_BE_N1_SOC_LA32_ROOT"
    return $?
}
