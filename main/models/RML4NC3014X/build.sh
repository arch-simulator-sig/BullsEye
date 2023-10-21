#
if [[ "$K221_BE_GLOBALCONFIG" != "true" ]]; then
    echo "%Error: You need to run BullsEye global config script first."
    exit 1
fi

source "$K221_BE_GLOBALSCRIPTS"

#
LD="ld"
CC="g++"
AR="ar"

CFLAG="-O3 -std=c++20 -flto -fwhole-program -pthread -lpthread -latomic"

BUILD_PATH=".build"
BUILD_TARGET="$BUILD_PATH/app"


#
SCRIPT_DIR="$(dirname $(readlink -f "$BASH_SOURCE"))"

CAPP_TOTAL_DIR="$SCRIPT_DIR/capp"


# Log folder
LOG_FOLDER=".log"

eval "test -d $LOG_FOLDER || mkdir $LOG_FOLDER"


#
USAGE="\
Usage: build.sh [-c] [-r] [-j <count>] [-v <path>] [-t <target>] [-R] [-a <params>] [-s <options>]\n\
-c: Clean the verilated build path before build.\n\
-v: Specify the Verilog Project path.\n\
-r: Clean and rebuild the C-app and dependencies output.\n\
-j: Specify the number of jobs to run simultaneously on build.\n\
-t: Specify the C-app target.\n\
-T: Re-specify the C-app LD archive target.\n\
-R: Run the specified C-app.\n\
-a: Specify the arguments to pass to the C-app. Example: -a \"1 2 3 ...\"\n\
-s: Skip specified procedure in overall build.\n\
    \"D\": dependencies\n\
    \"P\": peripherals\n\
    \"V\": verilate\n\
    \"M\": c-app main\n\
    \"E\": c-app executable\n\
    \"A\": all above"

SKIP_BUILD_DEPS="D"
SKIP_BUILD_PERPH="P"
SKIP_BUILD_VERILATE="V"
SKIP_BUILD_CAPP_MAIN="M"
SKIP_BUILD_CAPP_EXE="E"

SKIP_BUILD_ALL="A"

SKIP_BUILD=

VERILATE_ARG_C=
VERILATE_ARG_V=

BUILD_ARG_C=
BUILD_ARG_J=

CAPP_DIR=
CAPP_TARGET=
CAPP_RUN=

CAPP_DEP_FILE=
CAPP_DEPS=

CAPP_LD_TARGET=".build/appmain.a"
CAPP_LD_FILE=

CAPP_RUN_ARGS=

OPTIND=
while getopts 'hcv:rj:t:T:Ra:s:' OPT; do
    case $OPT in
        h) echo -e "$USAGE"; exit 0;;
        c) VERILATE_ARG_C="-c";;
        v) VERILATE_ARG_V="-v \"$OPTARG\"";;
        r) BUILD_ARG_C="-c";;
        j) BUILD_ARG_J="-j $OPTARG";;
        t) CAPP_TARGET="$OPTARG";;
        T) CAPP_LD_TARGET="$OPTARG";;
        R) CAPP_RUN="true";;
        a) CAPP_RUN_ARGS="$OPTARG";;
        s) SKIP_BUILD="$OPTARG";;
        ?) echo -e "$USAGE"; exit 1;;
    esac
done


#
CAPP_SPECIFIED=

specify_target () {

    if [[ "$CAPP_SPECIFIED" == "true" ]]; then
        return 0
    fi

    if [[ ! -n "$CAPP_TARGET" ]]; then
        echo "%Error: Please specify the C-app target by parameter \"-t\""
        exit 1
    fi

    CAPP_DIR="$CAPP_TOTAL_DIR/$CAPP_TARGET"

    CAPP_DEP_FILE="$CAPP_DIR/.app.depconfig.sh"
    CAPP_LD_FILE="$CAPP_DIR/$CAPP_LD_TARGET"

    #
    test -d "$CAPP_DIR"
    if [[ $? -ne 0 ]]; then
        echo "%Error: C-app target \"$CAPP_TARGET\" directory not found."
        exit 1
    fi

    #
    CAPP_SPECIFIED="true"

    return 0
}


#
LD_LIBRARY=


# Discover dependencies
discover_dependencies() {

    local CAPP_DEP_SET=

    #
    if test -f "$CAPP_DEP_FILE" 
    then
        CAPP_DEP_SET=$(source "$CAPP_DEP_FILE")
    else
        echo "No dependency discovered."
        return 0
    fi

    if [[ ! -n "$CAPP_DEP_SET" ]]; then
        echo "No dependency discovered."
        return 0
    fi

    #
    CAPP_DEPS=($CAPP_DEP_SET)
    CAPP_DEPS=($(awk -v RS=' ' '!a[$1]++' <<< "${CAPP_DEPS[@]}"))

    echo "Discovered dependencies: ${CAPP_DEPS[@]}"

    return 0
}


# Build dependencies
build_dependencies () {

    # check routines
    local CAPP_DEP=
    for CAPP_DEP in ${CAPP_DEPS[@]}
    do
        if [[ "$(type -t build_library_$CAPP_DEP)" != function ]]; then
            echo "%Error: Build routine for dependency \"$CAPP_DEP\" (build_library_$CAPP_DEP) not defined."
            exit 1
        fi
    done


    # build
    for CAPP_DEP in ${CAPP_DEPS[@]}
    do
        echo -e "\033[33m[dependency build] Discovered dependency \"$CAPP_DEP\".\033[0m"
        eval "build_library_$CAPP_DEP $BUILD_ARG_C $BUILD_ARG_J"
        if [ $? -ne 0 ]; then
            echo -e "%Error: \033[1;31mFailed at build for \"$CAPP_DEP\".\033[0m"
            exit 1
        fi
    done

    return 0
}

link_dependencies () {

    # check routines
    local CAPP_DEP=
    for CAPP_DEP in ${CAPP_DEPS[@]}
    do
        if [[ "$(type -t link_library_$CAPP_DEP)" != function ]]; then
            echo "%Error: Link configuration routine for dependency \"$CAPP_DEP\" (link_library_$CAPP_DEP) not defined."
            exit 1
        fi
    done

    # link
    for CAPP_DEP in ${CAPP_DEPS[@]}
    do
        CAPP_DEP_LD_FILE= 

        echo -e "\033[33m[dependency link] Discovered dependency \"$CAPP_DEP\".\033[0m"
        eval "link_library_$CAPP_DEP -l CAPP_DEP_LD_FILE"
        if [ $? -ne 0 ]; then
            echo -e "%Error: \033[1;31mFailed at link configuration for \"$CAPP_DEP\".\033[0m"
            exit 1
        fi

        CAPP_DEP_LD_FILE=${CAPP_DEP_LD_FILE//" "/""}

        if test -f "$CAPP_DEP_LD_FILE"
        then
            LD_LIBRARY="$CAPP_DEP_LD_FILE $LD_LIBRARY"
        else
            echo -e "%Error: Linkage file of \"$CAPP_DEP\" not found or not built yet."
            exit 1
        fi
    done

    return 0
}


# Build core peripherals
build_peripherals () {

    echo -e "\033[33m[dependency build] Core peripherals\033[0m"

    eval "make -C csrc"
    if [ $? -ne 0 ]; then
        echo -e "%Error: \033[1;31mFailed at core peripherals make task.\033[0m"
        exit 1
    fi

    return 0
}

link_peripherials () {

    PERIPH_LD_FILE="csrc/.build/libds232.a"

    if test -f "$PERIPH_LD_FILE"
    then
        LD_LIBRARY="$PERIPH_LD_FILE $LD_LIBRARY"
    else
        echo -e "%Error: Linkage file of core peripherals not found or not built yet."
        exit 1
    fi

    return 0
}


# Build C-app main
build_capp_main () {

    echo -e "\033[33mEntering C-app main build task.\033[0m"

    if [[ -n "$BUILD_ARG_C" ]]; then
        eval "make -C $CAPP_DIR clean"
        if [ $? -ne 0 ]; then
            echo -e "%Error: \033[1;31mFailed at C-app main clean task.\033[0m"
            exit 1
        fi
    fi

    eval "make -C $CAPP_DIR $BUILD_ARG_J"
    if [ $? -ne 0 ]; then
        echo -e "%Error: \033[1;31mFailed at C-app main build task.\033[0m"
        exit 1
    fi

    echo -e "\033[0m..."
    eval "cat $CAPP_DIR/.build/build.out.log | tail -n 2"
    echo -e "\033[1;30mC-app main build logs saved to $CAPP_DIR/.build/build.log\033[0m"

    echo -e "\033[1;30mLeaving C-app main build task.\033[0m"

    return 0
}

link_capp_main () {

    if test -f "$CAPP_LD_FILE"
    then
        LD_LIBRARY="$CAPP_LD_FILE $LD_LIBRARY"
    else
        echo -e "%Error: Linkage file of C-app main not found or not built yet."
        exit 1
    fi

    return 0
}


# Verilate
verilate () {

    echo -e "\033[33mEntering verilator make task.\033[0m"

    eval "./verilate.sh $VERILATE_ARG_C >.log/verilate.out.log 2>.log/verilate.err.log"

    if [ $? -ne 0 ]; then
        echo -e "%Error: \033[1;31mFailed at verilator make task.\033[0m"
        eval "cat .log/verilate.err.log | head -n 5"
        echo "..."
        echo -e "\033[1;30mVerilator error logs saved to .log/verilate.err.log\033[0m"
        exit 1
    fi

    echo -e "\033[0m..."
    eval "cat .log/verilate.out.log | tail -n 2"
    echo -e "\033[1;30mVerilator logs saved to .log/verilate.log\033[0m"

    echo -e "\033[1;30mLeaving verilator make task.\033[0m"

    return 0
}

link_verilated () {

    VERILATED_LD_FILE=".verilated/libvltdm.a"

    if test -f "$VERILATED_LD_FILE"
    then
        LD_LIBRARY="$LD_LIBRARY $VERILATED_LD_FILE"
    else
        echo -e "%Error: Linkage file of verilated not found or not built yet."
        exit 1
    fi

    return 0
}


# Build overall C-app
build_capp () {

    echo -e "\033[33mEntering main build task.\033[0m"

    eval "rm -rf $BUILD_PATH"
    eval "mkdir -p $BUILD_PATH"

    eval "$CC $CFLAG -o $BUILD_TARGET $LD_LIBRARY"

    echo -e "\033[1;30mLeaving main build task.\033[0m"

    return 0
}


#
run_capp () {
    
    if test -f "$BUILD_TARGET"
    then
        echo "Ready to run C-app \"$BUILD_TARGET\"."
        echo "------------------------------------------------"
        eval "$BUILD_TARGET $CAPP_RUN_ARGS"
    else
        echo "%Error: C-app target \"$BUILD_TARGET\" not found or not built yet."
        exit 1
    fi
    
    return 0
}


#
test_build_skip () {

    if [[ $SKIP_BUILD =~ $SKIP_BUILD_ALL ]]; then
        echo "true"
    else
        if [[ $SKIP_BUILD =~ $1 ]]; then
            echo "true"
        else
            echo "false"
        fi
    fi

    return 0
}


# Build script main procedure
## Build : dependencies
if [[ -n "$CAPP_TARGET" ]]; then

    specify_target

    discover_dependencies

    if [[ $(test_build_skip $SKIP_BUILD_DEPS) == "false" ]]; then
        build_dependencies
    fi

    link_dependencies
fi


## Build : peripherals
if [[ $(test_build_skip $SKIP_BUILD_PERPH) == "false" ]]; then
    build_peripherals
fi

link_peripherials


## Build : verilate
if [[ $(test_build_skip $SKIP_BUILD_VERILATE) == "false" ]]; then
    verilate
fi

link_verilated

## Build : C-app main
if [[ -n "$CAPP_TARGET" ]]; then

    specify_target

    if [[ $(test_build_skip $SKIP_BUILD_CAPP_MAIN) == "false" ]]; then
        build_capp_main
    fi

    link_capp_main
fi

## Build : C-app binary
if [[ -n "$CAPP_TARGET" ]]; then

    specify_target

    if [[ $(test_build_skip $SKIP_BUILD_CAPP_EXE) == "false" ]]; then
        build_capp
    fi
fi


# Run
if [[ "$CAPP_RUN" == "true" ]]; then

    specify_target

    run_capp
fi
