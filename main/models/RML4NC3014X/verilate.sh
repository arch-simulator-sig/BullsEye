#
if [[ "$K221_BE_GLOBALCONFIG" != "true" ]]; then
    echo "You need to run BullsEye global config script first."
    exit 1
fi

source "$K221_BE_GLOBALSCRIPTS"

#
SCRIPT_DIR="$(dirname $(readlink -f "$BASH_SOURCE"))"

VPROJECT_PATH=$K221_DS232_VPROJECT_PATH
CPROJECT_PATH="$SCRIPT_DIR/csrc/"

VERILATED_PATH="$SCRIPT_DIR/.verilated"

VTOP_FILE="$VPROJECT_PATH/thinpad_verilated.v"

VERILATOR_ARGS="--trace -O3 --threads 4 -j `nproc`"
COMPILE_ARGS="-std=c++20 -flto -fwhole-program"


#
USAGE="\
Usage: verilate.sh [-c] [-v <path>] [-H]\n\
-c: Clean the build path before verilate.\n\
-v: Specify the Verilog Project path.\n\
-H: Generate CPP header files only.\n"


BUILD_HEADER_SWITCH="--build --lib-create vltdm"

OPTIND=
while getopts 'hcv:H' OPT; do
    case $OPT in
        h) echo -e "$USAGE"; return 0;;
        c) CLEAN="true";;
        v) VPROJECT_PATH="$OPTARG";;
        H) BUILD_HEADER_SWITCH="";;
        ?) echo -e "$USAGE"; return 1;;
    esac
done

if [[ ! -n "$VPROJECT_PATH" ]]; then
    echo "Please specify Verilog Project path by parameter \"-v\"" >&2
    exit 1
fi


# clear build path
if [[ "$CLEAN" == "true" ]]; then
    eval "rm -rf $VERILATED_PATH"
fi


# get all C++ source files
CSRC_LIST=`find $CPROJECT_PATH -name "*.cpp"`
for CSRC_FILE in ${CSRC_LIST[@]}
do
    CSRC_FILES="$CSRC_FILES $CSRC_FILE"
done

# get all csrc subfolders
CSRC_SUB_FOLDER=`find $CPROJECT_PATH -type d`
for SUBFOLDER in ${CSRC_SUB_FOLDER[@]}
do
    INCLUDE_CSRC_FOLDERS="$INCLUDE_CSRC_FOLDERS -I$SUBFOLDER"
done

# get all vsrc subfolders
VSRC_SUB_FOLDER=`find $VPROJECT_PATH -type d`
for SUBFOLDER in ${VSRC_SUB_FOLDER[@]}
do
    INCLUDE_VSRC_FOLDERS="$INCLUDE_VSRC_FOLDERS -I$SUBFOLDER"
done


# verilate
test -d $VERILATED_PATH || mkdir $VERILATED_PATH

eval "verilator $VERILATOR_ARGS --cc -CFLAGS \"$COMPILE_ARGS $INCLUDE_CSRC_FOLDERS\" \
-Mdir $VERILATED_PATH $INCLUDE_VSRC_FOLDERS $BUILD_HEADER_SWITCH $VTOP_FILE"

if [ $? -ne 0 ]; then
    echo "Failed to verilate."
    exit 1
fi
