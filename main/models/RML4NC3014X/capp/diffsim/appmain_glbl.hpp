#pragma once
//
// Global context definitions
//
//

#include <string>


#include "appmain_periph.hpp"
#include "appmain_verifier.hpp"
#include "appmain_err.hpp"
#include "appmain_errcapt.hpp"

#include "appmain_historypc.hpp"
#include "appmain_historymem.hpp"


#include "../../csrc/core/ds232_verilated.hpp"
#include "../../csrc/core/ds232_diff.hpp"


#include "autoinclude.h"

#include AUTOINC_BE_COMMON(eventbus.hpp)

#include AUTOINC_BE_N1_SOC_LA32(soc.hpp)

#include AUTOINC_BE_JASSE2_LA32(la32.hpp)

#include AUTOINC_BE_JASSE2_LA32(addon/la32diff.hpp)


//
struct GlobalContextRM {

    unsigned int                                eventBusId;

    BullsEye::NSCSCCSingle::BaseRAM*            baseRAM;
    BullsEye::NSCSCCSingle::ExtRAM*             extRAM;

    BullsEye::SerialInterface*                  serial;

    BullsEye::NSCSCCSingle::NSCSCC2023SoC*      soc;

    Jasse::LA32Instance*                        emu;

    Jasse::LA32Differential*                    diff;
};


struct GlobalContextDUTHistory {

    PCHistory*                                  PC;    

    MMIOReadHistory*                            MMIORead;

    MMIOWriteHistory*                           MMIOWrite;
};

struct GlobalContextDUT {

    unsigned int                                eventBusId;

    BullsEye::NSCSCCSingle::BaseRAM*            baseRAM;
    BullsEye::NSCSCCSingle::ExtRAM*             extRAM;

    BullsEye::SerialInterface*                  serial;

    BullsEye::NSCSCCSingle::NSCSCC2023SoC*      soc;

    BullsEye::Draconids3014::Thinpad*           dut;

    BullsEye::Draconids3014::DS232Differential* diff;

    //
    GlobalContextDUTHistory                     history;
};


struct GlobalContext {

    // global shared
    BullsEye::EventBusDispatchment          eventBusDispatchment;

    PeripheralInjector*                     peripheralInjector;

    DifferentialVerifier*                   verifier;

    //
    Jasse::pc_t                             lastPC;

    uint64_t                                commitCount;

    //
    GlobalContextRM                         ref;
    GlobalContextDUT                        dut;
};


//
struct GlobalConfigDump0 {

    bool                                    enabled;

    unsigned int                            upperCount;
    unsigned int                            lowerCount;

    bool                                    muteUnread;
};

struct GlobalConfigDump1 {

    bool                                    enabled;

    unsigned int                            upperCount;
    unsigned int                            lowerCount;

    bool                                    displayTrace;

    bool                                    muteUnread;
};


struct GlobalConfig {

    //
    std::string                             binaryFileName;

    //
    GlobalConfigDump0                       dump0;
    GlobalConfigDump1                       dump1;
};


//
struct GlobalError {

    //
    CapturedErrors                          captured;
};


//
struct GlobalErrorCapture {

    //
    PeripheralErrorCapture*                 peripheral;

    DifferentialVerifierErrorCapture*       verifier;
};


//
struct Global {

    GlobalContext       ctx;

    GlobalConfig        cfg;

    GlobalError         err;

    GlobalErrorCapture  errcapt;
};

extern Global glbl;
