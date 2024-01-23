#include "appmain_startup.hpp"
//
//
//
//

#include "appmain_glbl.hpp"
#include "appmain_vcd.hpp"


#include <iostream>
#include <fstream>
#include <iomanip>

#include <verilated.h>


#include "../../csrc/core/ds232_diff.hpp"


#include "autoinclude.h"

#include AUTOINC_BE_COMMON(eventbus.hpp)

#include AUTOINC_BE_N1_SOC_LA32(soc.hpp)
#include AUTOINC_BE_N1_SOC_LA32(serial.hpp)

#include AUTOINC_BE_JASSE2_LA32(la32.hpp)
#include AUTOINC_BE_JASSE2_LA32(la32_nscscc.hpp)    // IWYU pragma: keep


//#define ENDIAN_SWITCHED

#ifdef ENDIAN_SWITCHED
#define ENDIAN_SWITCH32(val) \
    (((val) & 0x000000FF) << 24) | \
    (((val) & 0x0000FF00) << 8) | \
    (((val) & 0x00FF0000) >> 8) | \
    (((val) & 0xFF000000) >> 24)
#else
#define ENDIAN_SWITCH32(val) val
#endif


int startup()
{
    using namespace BullsEye;
    using namespace BullsEye::NSCSCCSingle;


    //
    glbl.ctx.lastPC = 0xDEADBEEF;

    glbl.ctx.commitCount = 0;


    // Configure seperate EventBus for reference model and DUT
    EventBusDispatchment eventBusDispatchment;

    glbl.ctx.ref.eventBusId = glbl.ctx.eventBusDispatchment.NextEventBusId();
    glbl.ctx.dut.eventBusId = glbl.ctx.eventBusDispatchment.NextEventBusId();


    // Instantiate RAMs for reference model and DUT
    glbl.ctx.ref.baseRAM    = new BaseRAM;
    glbl.ctx.ref.extRAM     = new ExtRAM;

    glbl.ctx.dut.baseRAM    = new BaseRAM;
    glbl.ctx.dut.extRAM     = new ExtRAM;


    // Open binary file
    std::ifstream binaryfile(glbl.cfg.binaryFileName, std::ifstream::binary);

    if (!binaryfile)
    {
        std::cout << "[\033[1;31mERROR\033[0m] Cannot open file: " << glbl.cfg.binaryFileName << std::endl;
        return 1;
    }


    // Load binary file to RAMs
    std::cout << "--------------------------------" << std::endl;
    std::cout << "Ready to load binary file: " << glbl.cfg.binaryFileName << std::endl;

    int counter         = 0;
    int counter_base    = 0;
    int counter_ext     = 0;
    while (!binaryfile.eof())
    {
        memdata_t data;
        binaryfile.read(reinterpret_cast<char*>(&data.data32), sizeof(insnraw_t));

        data.data32 = ENDIAN_SWITCH32(data.data32);

        if (counter == 2048 * 1024)
        {
            std::cout << "[\033[1;31mERROR\033[0m] 8MB binary file max supported. Mounted 4MB BaseRAM and 4MB ExtRAM." << std::endl;
            return 1;
        }
        else if (counter >= 1024 * 1024)
        {
            if (glbl.ctx.ref.extRAM->WriteInsn((counter << 2) - 0x00400000, MOPW_WORD, data).status != LA32MOPStatus::MOP_SUCCESS)
            {
                std::cout << "[\033[1;31mERROR\033[0m] Failed to write to reference ExtRAM (0x" 
                    << std::hex << std::setw(8) << std::setfill('0') << (counter << 2) << std::dec << ")." 
                    << std::endl;
                return 1;
            }

            if (glbl.ctx.dut.extRAM->WriteInsn((counter << 2) - 0x00400000, MOPW_WORD, data).status != LA32MOPStatus::MOP_SUCCESS)
            {
                std::cout << "[\033[1;31mERROR\033[0m] Failed to write to DUT ExtRAM (0x" 
                    << std::hex << std::setw(8) << std::setfill('0') << (counter << 2) << std::dec << ")." 
                    << std::endl;
                return 1;
            }

            counter_ext++;
        }
        else
        {
            if (glbl.ctx.ref.baseRAM->WriteInsn(counter << 2, MOPW_WORD, data).status != LA32MOPStatus::MOP_SUCCESS)
            {
                std::cout << "[\033[1;31mERROR\033[0m] Failed to write to reference BaseRAM (0x" 
                    << std::hex << std::setw(8) << std::setfill('0') << (counter << 2) << std::dec << ")." 
                    << std::endl;
                return 1;
            }

            if (glbl.ctx.dut.baseRAM->WriteInsn(counter << 2, MOPW_WORD, data).status != LA32MOPStatus::MOP_SUCCESS)
            {
                std::cout << "[\033[1;31mERROR\033[0m] Failed to write to DUT BaseRAM (0x" 
                    << std::hex << std::setw(8) << std::setfill('0') << (counter << 2) << std::dec << ")." 
                    << std::endl;
                return 1;
            }

            counter_base++;
        }

        counter++;
    }

    std::cout << "\033[1;33mLoaded program binary file.\033[0m" << std::endl;
    std::cout << "Loaded " << counter_base << " byte(s) to BaseRAM" << std::endl;
    std::cout << "Loaded " << counter_ext << " byte(s) to ExtRAM" << std::endl;
    std::cout << "--------------------------------" << std::endl;


    // Initialize Serial Interface
    if (glbl.cfg.serial.serverEnabled)
    {
        // Initialize serial tcp
        std::cout << "Initialize serial TCP server ..." << std::endl;

        SerialTCPServer* serial = new SerialTCPServer;

        glbl.ctx.ref.serial = nullptr;
        glbl.ctx.dut.serial = serial;

        const char* ip      = glbl.cfg.serial.serverAddress.c_str();
        uint64_t    port    = glbl.cfg.serial.serverPort;

        if (!serial->OpenServer(ip, port))
        {
            std::cout << "[\033[1;31mERROR\033[0m] Cannot open serial TCP server on " << ip << ":" << port << std::endl;
            return 1;
        }

        serial->AcceptConnection();

        printf("\033[1;33mOpened serial TCP server on %s:%d\033[0m\n", ip, (uint32_t) port);

        //
        printf("Press ENTER to continue...\n");
        std::cin.get();
        std::cout << "--------------------------------" << std::endl;
    }
    else
    {
        // Initialize serial
        glbl.ctx.ref.serial = nullptr;
        glbl.ctx.dut.serial = new SerialWriteOnlyConsole(glbl.oss);

        printf("\033[1;33mOpened serial console (serial write-only).\033[0m\n");
    }

    
    // Instantiate SoC
    glbl.ctx.ref.soc = NSCSCC2023SoC::Builder()
        .BaseDOGGIES    (glbl.ctx.ref.baseRAM)
        .ExtDOGGIES     (glbl.ctx.ref.extRAM)
        .Serial         (glbl.ctx.ref.serial)
        .EventBusId     (glbl.ctx.ref.eventBusId)
        .Build();
    std::cout << "Instantiated SoC for reference model." << std::endl;

    glbl.ctx.dut.soc = NSCSCC2023SoC::Builder()
        .BaseDOGGIES    (glbl.ctx.dut.baseRAM)
        .ExtDOGGIES     (glbl.ctx.dut.extRAM)
        .Serial         (glbl.ctx.dut.serial)
        .EventBusId     (glbl.ctx.dut.eventBusId)
        .Build();
    std::cout << "Instantiated SoC for DUT." << std::endl;


    // Instantiate reference emulator
    std::cout << "Reference model emulator EventBus ID: " << glbl.ctx.ref.eventBusId << std::endl;

    glbl.ctx.ref.emu = LA32Instance::Builder()
        .StartupPC  (glbl.cfg.startupPC)
        .Decoder    (Decoder::LA32R_NSCSCC)
        .Memory     (&glbl.ctx.ref.soc->MMU())
        .EventBusId (glbl.ctx.ref.eventBusId)
        .EnableTrace            (1024, 1024)
        .EnablePCTracer         (256)
        .EnableGPRTracer        (256)
        .EnableFetchTracer      (256)
        .EnableExecutionTracer  (256)
        .Build();
    
    std::cout << "Instantiated reference model emulator." << std::endl;

    
    // Initialize DUT Thinpad & VCD
    std::cout << "DUT EventBus ID: " << glbl.ctx.dut.eventBusId << std::endl;

    init_vcd();

    glbl.ctx.dut.dut = Draconids3014::Thinpad::Builder()
        .SoC        (glbl.ctx.dut.soc)
        .VCD        (fp)
        .EventBusId (glbl.ctx.dut.eventBusId)
        .Build();

    open_vcd();

    std::cout << "Initialized verilated DUT and VCD waveform." << std::endl;


    // Instantiate differential base for reference emulator
    glbl.ctx.ref.diff = LA32Differential::Builder()
        .EnablePC           ()
        .EnableInstruction  ()
        .EnableGPR          ()
        .EnableMemoryStore  ()
        .EventBusId         (glbl.ctx.ref.eventBusId)
        .Build();
    std::cout << "Instantiated reference model differential base." << std::endl;


    // Instantiate differential base for DUT
    glbl.ctx.dut.diff = Draconids3014::DS232Differential::Builder()
        .EnablePC           ()
        .EnableInstruction  ()
        .EnableGPR          ()
        .EnableMemoryStore  ()
        .FIDTracker         (&glbl.ctx.dut.dut->GetFetchIDTracker())
        .EventBusId         (glbl.ctx.dut.eventBusId)
        .Build();
    std::cout << "Instantiated DUT differential base." << std::endl;


    // Enable Peripheral Injector
    glbl.ctx.peripheralInjector = PeripheralInjector::Builder()
        .RefEventBusId  (glbl.ctx.ref.eventBusId)
        .DUTEventBusId  (glbl.ctx.dut.eventBusId)
        .Build();
    std::cout << "Enabled peripheral I/O injector." << std::endl;


    // Enable Differential Verifier
    glbl.ctx.verifier = DifferentialVerifier::Builder()
        .DifferentialRef    (glbl.ctx.ref.diff)
        .DifferentialDUT    (glbl.ctx.dut.diff)
        .Build();
    std::cout << "Enabled differential verifier." << std::endl;


    // Enable Error Capture
    glbl.errcapt.peripheral = PeripheralErrorCapture::Builder()
        .CapturedTo     (&glbl.err.captured)
        .Build();
    std::cout << "Enabled error capture of peripheral I/O." << std::endl;


    glbl.errcapt.verifier = DifferentialVerifierErrorCapture::Builder()
        .CapturedTo     (&glbl.err.captured)
        .Build();
    std::cout << "Enabled error capture of differential verifier." << std::endl;


    glbl.errcapt.axi = AXIBridgeErrorCapture::Builder()
        .CapturedTo     (&glbl.err.captured)
        .ErrorEventBusId(glbl.ctx.dut.eventBusId)
        .Build();
    std::cout << "Enabled error capture of SoC AXI bridge." << std::endl;


    glbl.errcapt.mmu.dut = MMUErrorCapture::Builder()
        .Source         ("DUT")
        .CapturedTo     (&glbl.err.captured)
        .ErrorEventBusId(glbl.ctx.dut.eventBusId)
        .Build();
    std::cout << "Enabled error capture of DUT MMU." << std::endl;

    glbl.errcapt.mmu.ref = MMUErrorCapture::Builder()
        .Source         ("reference")
        .CapturedTo     (&glbl.err.captured)
        .ErrorEventBusId(glbl.ctx.ref.eventBusId)
        .Build();
    std::cout << "Enabled error capture of reference MMU." << std::endl;

    //


    // History collection
    glbl.ctx.dut.history.PC = new PCHistory(256);
    std::cout << "Enabled DUT PC history capture (depth = ";
    std::cout << glbl.ctx.dut.history.PC->GetDepth();
    std::cout << ")." << std::endl;

    glbl.ctx.dut.history.MMIORead = MMIOReadHistory::Builder()
        .Depth(256)
        .EventBusId(glbl.ctx.dut.eventBusId)
        .Build();
    std::cout << "Enabled DUT MMIO Read history capture (depth = ";
    std::cout << glbl.ctx.dut.history.MMIORead->GetDepth();
    std::cout << ")." << std::endl;

    glbl.ctx.dut.history.MMIOWrite = MMIOWriteHistory::Builder()
        .Depth(256)
        .EventBusId(glbl.ctx.dut.eventBusId)
        .Build();
    std::cout << "Enabled DUT MMIO Write history capture (depth = ";
    std::cout << glbl.ctx.dut.history.MMIOWrite->GetDepth();
    std::cout << ")." << std::endl;

    glbl.ctx.dut.history.MMIOReadWrite = MMIOReadWriteHistory::Builder()
        .Depth(256)
        .EventBusId(glbl.ctx.dut.eventBusId)
        .Build();
    std::cout << "Enabled DUT MMIO Read/Write history capture (depth = ";
    std::cout << glbl.ctx.dut.history.MMIOReadWrite->GetDepth();
    std::cout << ")." << std::endl;

    glbl.ctx.dut.history.busAXI = AXIBusHistory::Builder()
        .Depth(256)
        .EventBusId(glbl.ctx.dut.eventBusId)
        .Build();
    std::cout << "Enabled DUT AXI Bus history capture (depth = ";
    std::cout << glbl.ctx.dut.history.busAXI->GetDepth();
    std::cout << ")." << std::endl;

    glbl.ctx.dut.history.commit = CommitHistory::Builder()
        .DUT(glbl.ctx.dut.dut)
        .Depth(256)
        .EventBusId(glbl.ctx.dut.eventBusId)
        .Build();
    std::cout << "Enabled commit history capture (depth = ";
    std::cout << glbl.ctx.dut.history.commit->GetDepth();
    std::cout << ")." << std::endl;

    //
    return 0;
}


int shutdown()
{
    if (glbl.ctx.dut.history.commit)
    {
        delete glbl.ctx.dut.history.commit;
        glbl.ctx.dut.history.commit = nullptr;
    }

    if (glbl.ctx.dut.history.busAXI)
    {
        delete glbl.ctx.dut.history.busAXI;
        glbl.ctx.dut.history.busAXI = nullptr;
    }

    if (glbl.ctx.dut.history.MMIOReadWrite)
    {
        delete glbl.ctx.dut.history.MMIOReadWrite;
        glbl.ctx.dut.history.MMIOReadWrite = nullptr;
    }

    if (glbl.ctx.dut.history.MMIOWrite)
    {
        delete glbl.ctx.dut.history.MMIOWrite;
        glbl.ctx.dut.history.MMIOWrite = nullptr;
    }

    if (glbl.ctx.dut.history.MMIORead)
    {
        delete glbl.ctx.dut.history.MMIORead;
        glbl.ctx.dut.history.MMIORead = nullptr;
    }

    if (glbl.ctx.dut.history.PC)
    {
        delete glbl.ctx.dut.history.PC;
        glbl.ctx.dut.history.PC = nullptr;
    }



    if (glbl.errcapt.mmu.ref)
    {
        delete glbl.errcapt.mmu.ref;
        glbl.errcapt.mmu.ref = nullptr;
    }

    if (glbl.errcapt.mmu.dut)
    {
        delete glbl.errcapt.mmu.dut;
        glbl.errcapt.mmu.dut = nullptr;
    }

    if (glbl.errcapt.axi)
    {
        delete glbl.errcapt.axi;
        glbl.errcapt.axi = nullptr;
    }

    if (glbl.errcapt.verifier)
    {
        delete glbl.errcapt.verifier;
        glbl.errcapt.verifier = nullptr;
    }

    if (glbl.errcapt.peripheral)
    {
        delete glbl.errcapt.peripheral;
        glbl.errcapt.peripheral = nullptr;
    }


    if (glbl.ctx.verifier)
    {
        delete glbl.ctx.verifier;
        glbl.ctx.verifier = nullptr;
    }


    if (glbl.ctx.peripheralInjector)
    {
        delete glbl.ctx.peripheralInjector;
        glbl.ctx.peripheralInjector = nullptr;
    }


    if (glbl.ctx.ref.diff)
    {
        delete glbl.ctx.ref.diff;
        glbl.ctx.ref.diff = nullptr;
    }

    if (glbl.ctx.dut.diff)
    {
        delete glbl.ctx.dut.diff;
        glbl.ctx.dut.diff = nullptr;
    }


    if (glbl.ctx.ref.emu)
    {
        delete glbl.ctx.ref.emu;
        glbl.ctx.ref.emu = nullptr;
    }

    if (glbl.ctx.dut.dut)
    {
        delete glbl.ctx.dut.dut;
        glbl.ctx.dut.dut = nullptr;
    }


    if (glbl.ctx.ref.serial)
    {
        delete glbl.ctx.ref.serial;
        glbl.ctx.ref.serial = nullptr;
    }

    if (glbl.ctx.dut.serial)
    {
        delete glbl.ctx.dut.serial;
        glbl.ctx.dut.serial = nullptr;
    }


    if (glbl.ctx.ref.baseRAM)
    {
        delete glbl.ctx.ref.baseRAM;
        glbl.ctx.ref.baseRAM = nullptr;
    }

    if (glbl.ctx.ref.extRAM)
    {
        delete glbl.ctx.ref.extRAM;
        glbl.ctx.ref.extRAM = nullptr;
    }

    
    if (glbl.ctx.dut.baseRAM)
    {
        delete glbl.ctx.dut.baseRAM;
        glbl.ctx.dut.baseRAM = nullptr;
    }

    if (glbl.ctx.dut.extRAM)
    {
        delete glbl.ctx.dut.extRAM;
        glbl.ctx.dut.extRAM = nullptr;
    }


    finalize_vcd();

    return 0;
}