#pragma once
//
// Global context definitions
//
//


#include "../../csrc/core/ds232_verilated.hpp"
#include "../../csrc/core/ds232_diff.hpp"


#include "autoinclude.h"

#include AUTOINC_BE_COMMON(eventbus.hpp)

#include AUTOINC_BE_N1_SOC_LA32(soc.hpp)

#include AUTOINC_BE_JASSE2_LA32(la32.hpp)

#include AUTOINC_BE_JASSE2_LA32(addon/la32diff.hpp)


struct GlobalContextRM {

    unsigned int                                eventBusId;

    BullsEye::NSCSCCSingle::BaseRAM*            baseRAM;
    BullsEye::NSCSCCSingle::ExtRAM*             extRAM;

    BullsEye::SerialInterface*                  serial;

    BullsEye::NSCSCCSingle::NSCSCC2023SoC*      soc;

    Jasse::LA32Instance*                        emu;

    Jasse::LA32Differential*                    diff;
};

struct GlobalContextDUT {

    unsigned int                                eventBusId;

    BullsEye::NSCSCCSingle::BaseRAM*            baseRAM;
    BullsEye::NSCSCCSingle::ExtRAM*             extRAM;

    BullsEye::SerialInterface*                  serial;

    BullsEye::NSCSCCSingle::NSCSCC2023SoC*      soc;

    BullsEye::Draconids3014::Thinpad*           dut;

    BullsEye::Draconids3014::DS232Differential* diff;
};


struct GlobalContext {

    // global shared
    BullsEye::EventBusDispatchment          eventBusDispatchment;

    //
    GlobalContextRM                         ref;
    GlobalContextDUT                        dut;
};


struct GlobalConfig {

    //
    std::string                             binaryFileName;
};


struct Global {

    GlobalContext ctx;

    GlobalConfig cfg;
};

extern Global glbl;
