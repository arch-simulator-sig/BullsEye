#include "appmain_errcapt.hpp"
//
//
//
//

#include <string>
#include <sstream>
#include <iomanip>


//
static constexpr const char* _COLOR_CORRECT  = "\033[1;32m";

static constexpr const char* _COLOR_ERROR    = "\033[1;31m";

static constexpr const char* _COLOR_RESET    = "\033[0m";



//
static inline Jasse::LA32MOPWidth __Width(BullsEye::Draconids3014::lswidth_t width) noexcept
{
    switch (width)
    {
        case BullsEye::Draconids3014::LSWIDTH_BYTE:
            return Jasse::MOPW_BYTE;

        case BullsEye::Draconids3014::LSWIDTH_HALF_WORD:
            return Jasse::MOPW_HALF_WORD;

        case BullsEye::Draconids3014::LSWIDTH_WORD:
            return Jasse::MOPW_WORD;

        [[unlikely]] default:
            return Jasse::MOPW_WORD;
    }
}

static inline Jasse::LA32MOPWidth __Width(Jasse::LA32MOPWidth width) noexcept
{
    return width;
}

static inline uint32_t __Data(uint32_t data, BullsEye::Draconids3014::lswidth_t width) noexcept
{
    return data & __Width(width).mask;
}

static inline uint32_t __Data(Jasse::memdata_t data, Jasse::LA32MOPWidth width) noexcept
{
    return data.As(width);
}


//
static inline std::string __PCToString(Jasse::pc_t pc) noexcept
{
    std::ostringstream oss;
    oss << "0x" << std::hex << std::setw(16) << std::setfill('0') << pc;
    return oss.str();
}

static inline std::string __InsnToString(Jasse::insnraw_t insn) noexcept
{
    std::ostringstream oss;
    oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << insn;
    return oss.str();
}

static inline std::string __InsnToString(const Jasse::LA32Instruction& insn) noexcept
{
    return insn.ToString();
}

static inline std::string __GPRIndexToString(unsigned gpr_index) noexcept
{
    std::ostringstream oss;
    oss << "$r" << std::dec << std::setw(2) << std::setiosflags(std::ios::left) << gpr_index;
    return oss.str();
}

static inline std::string __GPRValueToString(Jasse::arch32_t gpr_value) noexcept
{
    std::ostringstream oss;
    oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << gpr_value;
    return oss.str();
}

static inline std::string __MOPWidthToString(Jasse::LA32MOPWidth width) noexcept
{
    switch (width.length)
    {
        case Jasse::MOPW_BYTE.length:
            return "BYTE      (1 Byte) ";

        case Jasse::MOPW_HALF_WORD.length:
            return "HALF_WORD (2 Bytes)";

        case Jasse::MOPW_WORD.length:
            return "WORD      (4 Bytes)";

        [[unlikely]] default:
            std::ostringstream unkoss;
            unkoss << "<unknown(";
            unkoss << std::hex;
            unkoss << "length=0x" << uint64_t(width.length) << ",";
            unkoss << "alignment=0x" << uint64_t(width.alignment) << ",";
            unkoss << "mask=0x" << uint64_t(width.mask);
            unkoss << ")>";
            return unkoss.str();
    }
}

static inline std::string __LSWidthToString(BullsEye::Draconids3014::lswidth_t width) noexcept
{
    switch (width)
    {
        case BullsEye::Draconids3014::LSWIDTH_BYTE:
            return "BYTE      (1 Byte)";

        case BullsEye::Draconids3014::LSWIDTH_HALF_WORD:
            return "HALF_WORD (2 Bytes)";

        case BullsEye::Draconids3014::LSWIDTH_WORD:
            return "WORD      (4 Bytes)";

        [[unlikely]] default:
            std::ostringstream unkoss;
            unkoss << "<unknown(";
            unkoss << "width=" << uint64_t(width);
            unkoss << ")>";
            return unkoss.str();
    }
}

static inline std::string __LSStrobeToString(BullsEye::Draconids3014::lsstrb_t strb) noexcept
{
    std::ostringstream oss;

    for (size_t i = 0; i < strb.size(); i++)
    {
        if (strb[i])
            oss << "1";
        else
            oss << "0";
    }

    return oss.str();
}

static inline std::string __AddressToString(Jasse::addr_t address) noexcept
{
    std::ostringstream oss;
    oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << address;
    return oss.str();
}

static inline std::string __DataToString(BullsEye::Draconids3014::lswidth_t width, uint32_t data) noexcept
{
    std::ostringstream oss;

    switch (width)
    {
        case BullsEye::Draconids3014::LSWIDTH_BYTE:
            oss << "0x" << std::hex << std::setw(2) << std::setfill('0') << uint32_t(data);
            return oss.str();

        case BullsEye::Draconids3014::LSWIDTH_HALF_WORD:
            oss << "0x" << std::hex << std::setw(4) << std::setfill('0') << uint32_t(data);
            return oss.str();

        case BullsEye::Draconids3014::LSWIDTH_WORD:
            oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << uint32_t(data);
            return oss.str();

        [[unlikely]] default:
            std::ostringstream unkoss;
            unkoss << "<unknown(";
            unkoss << "width=" << uint64_t(width);
            unkoss << ")>";
            return unkoss.str();
    }
}

static inline std::string __DataToString(Jasse::LA32MOPWidth width, Jasse::memdata_t data) noexcept
{
    std::ostringstream oss;

    switch (width.length)
    {
        case Jasse::MOPW_BYTE.length:
            oss << "0x" << std::hex << std::setw(2) << std::setfill('0') << uint32_t(data.data8);
            return oss.str();

        case Jasse::MOPW_HALF_WORD.length:
            oss << "0x" << std::hex << std::setw(4) << std::setfill('0') << uint32_t(data.data16);
            return oss.str();

        case Jasse::MOPW_WORD.length:
            oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << uint32_t(data.data32);
            return oss.str();

        [[unlikely]] default:
            std::ostringstream oss;
            oss << "<unknown(";
            oss << std::hex;
            oss << "length=0x" << uint64_t(width.length) << ",";
            oss << "alignment=0x" << uint64_t(width.alignment) << ",";
            oss << "mask=0x" << uint64_t(width.mask) << ",";
            oss << "data=0x" << uint32_t(data);
            oss << ")>";
            return oss.str();
    }
}

static inline std::string __UncachedToString(bool uncached) noexcept
{
    if (uncached)
        return "UNCACHED";
    else
        return "CACHED";
}



// Implementation of: class DifferentialVerifierErrorCapture
void DifferentialVerifierErrorCapture::RegisterListeners() noexcept
{
    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnMismatchedPC"),
            errorEventPriority,
            &DifferentialVerifierErrorCapture::OnMismatchedPC,
            this
        ),
        errorEventBusId
    );

    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnMismatchedInstruction"),
            errorEventPriority,
            &DifferentialVerifierErrorCapture::OnMismatchedInstruction,
            this
        ),
        errorEventBusId
    );

    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnMismatchedGPR"),
            errorEventPriority,
            &DifferentialVerifierErrorCapture::OnMismatchedGPR,
            this
        ),
        errorEventBusId
    );

    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnMismatchedMemoryStore"),
            errorEventPriority,
            &DifferentialVerifierErrorCapture::OnMismatchedMemoryStore,
            this
        ),
        errorEventBusId
    );
}

void DifferentialVerifierErrorCapture::UnregisterListeners() noexcept
{
    BullsEye::UnregisterListener(
        GetListenerName("OnMismatchedPC"),
        &DifferentialVerifierErrorCapture::OnMismatchedPC,
        errorEventBusId
    );

    BullsEye::UnregisterListener(
        GetListenerName("OnMismatchedInstruction"),
        &DifferentialVerifierErrorCapture::OnMismatchedInstruction,
        errorEventBusId
    );

    BullsEye::UnregisterListener(
        GetListenerName("OnMismatchedGPR"),
        &DifferentialVerifierErrorCapture::OnMismatchedGPR,
        errorEventBusId
    );

    BullsEye::UnregisterListener(
        GetListenerName("OnMismatchedMemoryStore"),
        &DifferentialVerifierErrorCapture::OnMismatchedMemoryStore,
        errorEventBusId
    );
}

void DifferentialVerifierErrorCapture::OnMismatchedPC(DifferentialVerifier::MismatchedPCEvent& event) noexcept
{
    std::ostringstream oss;

    //
    auto& ref = event.GetIncrementRef();
    auto& dut = event.GetIncrementDUT();

    //
    CapturedError error("DifferentialVerifier", "MismatchedPC");

    error.AppendMessage("Reference model performed differently on PC iteration.");
    error.AppendMessage("DUT didn't iterate PC as expected.");

    //
    error.AppendMessage("Errored PC increment (from reference):");

    if (ref.GetTermCount())
    {
    //  oss = std::ostringstream();
        oss << "[R] pc      : ";
        oss << __PCToString(ref.GetPC());
        error.AppendMessage(oss.str());
    }
    else 
    {
    //  oss = std::ostringstream();
        oss << "[R] pc      : <none>";
        error.AppendMessage(oss.str());
    }

    //
    error.AppendMessage("Errored PC increment (from DUT):");

    if (dut.GetTermCount())
    {
        if (ref.GetTermCount())
        {
            oss = std::ostringstream();
            oss << "[D] pc      : ";
            oss << (dut.GetPC() != ref.GetPC() ? _COLOR_ERROR : _COLOR_CORRECT);
            oss << __PCToString(dut.GetPC());
            oss << _COLOR_RESET;
            error.AppendMessage(oss.str());
        }
        else
        {
            oss = std::ostringstream();
            oss << "[D] pc      : ";
            oss << _COLOR_ERROR;
            oss << __PCToString(dut.GetPC());
            oss << _COLOR_RESET;
            error.AppendMessage(oss.str());
        }
    }
    else 
    {
        oss = std::ostringstream();
        oss << "[D] pc      : ";
        oss << (ref.GetTermCount() ? _COLOR_ERROR : _COLOR_CORRECT);
        oss << "<none>";
        oss << _COLOR_RESET;
        error.AppendMessage(oss.str());
    }

    //
    capturedTo->push_back(error);
}

void DifferentialVerifierErrorCapture::OnMismatchedInstruction(DifferentialVerifier::MismatchedInstructionEvent& event) noexcept
{
    std::ostringstream oss;

    //
    auto& ref = event.GetIncrementRef();
    auto& dut = event.GetIncrementDUT();

    //
    CapturedError error("DifferentialVerifier", "MismatchedInstruction");

    error.AppendMessage("Reference model performed differently on instruction iteration.");
    error.AppendMessage("DUT didn't iterate instruction as expected.");

    //
    error.AppendMessage("Error instruction increment (from reference):");

    if (ref.GetTermCount())
    {
    //  oss = std::ostringstream();
        oss << "[R] raw     : ";
        oss << __InsnToString(ref.GetInstruction().GetRaw());
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[R] decoded : ";
        if (ref.GetInstruction().IsDecoded())
            oss << __InsnToString(ref.GetInstruction());
        else
            oss << "<undecoded>";

        error.AppendMessage(oss.str());
    }
    else
    {
    //  oss = std::ostringstream();
        oss << "[R] raw     : <none>";
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[R] decoded : <none>";
        error.AppendMessage(oss.str());
    }

    //
    error.AppendMessage("Error instruction increment (from DUT):");

    if (dut.GetTermCount())
    {
        if (ref.GetTermCount())
        {
            oss = std::ostringstream();
            oss << "[D] raw     : ";
            oss << (dut.GetInstruction() != ref.GetInstruction().GetRaw() ? _COLOR_ERROR : _COLOR_CORRECT);
            oss << __InsnToString(dut.GetInstruction());
            oss << _COLOR_RESET;
            error.AppendMessage(oss.str());
        }
        else
        {
            oss = std::ostringstream();
            oss << "[D] raw     : ";
            oss << _COLOR_ERROR;
            oss << __InsnToString(dut.GetInstruction());
            oss << _COLOR_RESET;
            error.AppendMessage(oss.str());
        }
    }
    else
    {
        oss = std::ostringstream();
        oss << "[D] raw     : ";
        oss << (ref.GetTermCount() ? _COLOR_ERROR : _COLOR_CORRECT);
        oss << "<none>";
        oss << _COLOR_RESET;
        error.AppendMessage(oss.str());
    }

    //
    capturedTo->push_back(error);
}

void DifferentialVerifierErrorCapture::OnMismatchedGPR(DifferentialVerifier::MismatchedGPREvent& event) noexcept
{
    std::ostringstream oss;

    //
    auto& ref = event.GetIncrementRef();
    auto& dut = event.GetIncrementDUT();

    //
    CapturedError error("DifferentialVerifier", "MismatchedGPR");

    error.AppendMessage("Reference model performed differently on GPR increment.");
    error.AppendMessage("DUT didn't commit GPR as expected.");

    //
    error.AppendMessage("Errored GPR increment (from reference):");

    if (ref.GetTermCount())
    {
    //  oss = std::ostringstream();
        oss << "[R] index   : ";
        oss << __GPRIndexToString(ref.GetGPRIndex());
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[R] value   : ";
        oss << __GPRValueToString(ref.GetGPRValue());
        error.AppendMessage(oss.str());
    }
    else
    {
    //  oss = std::ostringstream();
        oss << "[R] index   : <none>";
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[R] value   : <none>";
        error.AppendMessage(oss.str());
    }

    //
    error.AppendMessage("Errored GPR increment (from DUT):");

    if (dut.GetTermCount())
    {
        if (ref.GetTermCount())
        {
            oss = std::ostringstream();
            oss << "[D] index   : ";
            oss << (dut.GetGPRIndex() != ref.GetGPRIndex() ? _COLOR_ERROR : _COLOR_CORRECT);
            oss << __GPRIndexToString(dut.GetGPRIndex());
            oss << _COLOR_RESET;
            error.AppendMessage(oss.str());

            oss = std::ostringstream();
            oss << "[D] value   : ";
            oss << (dut.GetGPRValue() != ref.GetGPRValue() ? _COLOR_ERROR : _COLOR_CORRECT);
            oss << __GPRValueToString(dut.GetGPRValue());
            oss << _COLOR_RESET;
            error.AppendMessage(oss.str());
        }
        else
        {
            oss = std::ostringstream();
            oss << "[D] index   : ";
            oss << (dut.GetGPRIndex() != 0 ? _COLOR_ERROR : _COLOR_CORRECT);
            oss << __GPRIndexToString(dut.GetGPRIndex());
            oss << _COLOR_RESET;
            error.AppendMessage(oss.str());

            oss = std::ostringstream();
            oss << "[D] value   : ";
            oss << __GPRValueToString(dut.GetGPRValue());
            oss << _COLOR_RESET;
            error.AppendMessage(oss.str());
        }
    }
    else
    {
        oss = std::ostringstream();
        oss << "[D] index   : ";
        oss << (ref.GetTermCount() ? _COLOR_ERROR : _COLOR_CORRECT);
        oss << "<none>";
        oss << _COLOR_RESET;
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[D] value   : ";
        oss << (ref.GetTermCount() ? _COLOR_ERROR : _COLOR_CORRECT);
        oss << _COLOR_RESET;
        oss << "<none>";
        error.AppendMessage(oss.str());
    }

    //
    capturedTo->push_back(error);
}

void DifferentialVerifierErrorCapture::OnMismatchedMemoryStore(DifferentialVerifier::MismatchedMemoryStoreEvent& event) noexcept
{
    std::ostringstream oss;

    //
    auto& ref = event.GetIncrementRef();
    auto& dut = event.GetIncrementDUT();

    //
    CapturedError error("DifferentialVerifier", "MismatchedMemoryStore");

    error.AppendMessage("Reference model performed differently on memory store.");
    error.AppendMessage("DUT didn't perform memory store as expected.");

    //
    error.AppendMessage("Errored memory store increment (from reference):");

    if (ref.GetTermCount())
    {
    //  oss = std::ostringstream();
        oss << "[R] width   : ";
        oss << __MOPWidthToString(ref.GetWidth());
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[R] address : ";
        oss << __AddressToString(ref.GetAddress());
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[R] data    : ";
        oss << __DataToString(ref.GetWidth(), ref.GetData());
        error.AppendMessage(oss.str());
    }
    else
    {
    //  oss = std::ostringstream();
        oss << "[R] width   : <none>";
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[R] address : <none>";
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[R] data    : <none>";
        error.AppendMessage(oss.str());
    }

    //
    error.AppendMessage("Errored memory store increment (from DUT):");

    if (dut.GetTermCount())
    {
        if (ref.GetTermCount())
        {
            oss = std::ostringstream();
            oss << "[D] width   : ";
            oss << (__Width(dut.GetWidth()) != __Width(ref.GetWidth()) ? _COLOR_ERROR : _COLOR_CORRECT);
            oss << __LSWidthToString(dut.GetWidth());
            oss << _COLOR_RESET;
            error.AppendMessage(oss.str());

            oss = std::ostringstream();
            oss << "[D] strobe  : ";
            oss << __LSStrobeToString(dut.GetStrobe());
            error.AppendMessage(oss.str());

            oss = std::ostringstream();
            oss << "[D] unmapped: ";
            oss << __AddressToString(dut.GetAddress());
            error.AppendMessage(oss.str());

            oss = std::ostringstream();
            oss << "[D] address : ";
            oss << (PeripheralInjector::ConvertBusAddress(dut.GetAddress(), dut.IsUncached()) != ref.GetAddress() ? _COLOR_ERROR : _COLOR_CORRECT);
            oss << __AddressToString(PeripheralInjector::ConvertBusAddress(dut.GetAddress(), dut.IsUncached()));
            oss << _COLOR_RESET;
            error.AppendMessage(oss.str());

            oss = std::ostringstream();
            oss << "[D] data    : ";
            oss << (__Data(dut.GetData(), dut.GetWidth()) != __Data(ref.GetData(), ref.GetWidth()) ? _COLOR_ERROR : _COLOR_CORRECT);
            oss << __DataToString(dut.GetWidth(), dut.GetData());
            oss << _COLOR_RESET;
            error.AppendMessage(oss.str());

            oss = std::ostringstream();
            oss << "[D] uncached: ";
            oss << __UncachedToString(dut.IsUncached());
            error.AppendMessage(oss.str());
        }
        else
        {
            oss = std::ostringstream();
            oss << "[D] width   : ";
            oss << _COLOR_ERROR;
            oss << __LSWidthToString(dut.GetWidth());
            oss << _COLOR_RESET;
            error.AppendMessage(oss.str());

            oss = std::ostringstream();
            oss << "[D] strobe  : ";
            oss << __LSStrobeToString(dut.GetStrobe());
            error.AppendMessage(oss.str());

            oss = std::ostringstream();
            oss << "[D] unmapped: ";
            oss << __AddressToString(dut.GetAddress());
            error.AppendMessage(oss.str());

            oss = std::ostringstream();
            oss << "[D] address : ";
            oss << _COLOR_ERROR;
            oss << __AddressToString(PeripheralInjector::ConvertBusAddress(dut.GetAddress(), dut.IsUncached()));
            oss << _COLOR_RESET;
            error.AppendMessage(oss.str());

            oss = std::ostringstream();
            oss << "[D] data    : ";
            oss << _COLOR_ERROR;
            oss << __DataToString(dut.GetWidth(), dut.GetData());
            oss << _COLOR_RESET;
            error.AppendMessage(oss.str());

            oss = std::ostringstream();
            oss << "[D] uncached: ";
            oss << __UncachedToString(dut.IsUncached());
            error.AppendMessage(oss.str());
        }
    }
    else
    {
        oss = std::ostringstream();
        oss << "[D] width   : ";
        oss << (ref.GetTermCount() ? _COLOR_ERROR : _COLOR_CORRECT);
        oss << "<none>";
        oss << _COLOR_RESET;
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[D] strobe  : ";
        oss << "<none>";
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[D] unmapped: ";
        oss << "<none>";
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[D] address : ";
        oss << (ref.GetTermCount() ? _COLOR_ERROR : _COLOR_CORRECT);
        oss << "<none>";
        oss << _COLOR_RESET;
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[D] data    : ";
        oss << (ref.GetTermCount() ? _COLOR_ERROR : _COLOR_CORRECT);
        oss << "<none>";
        oss << _COLOR_RESET;
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[D] uncached: ";
        oss << "<none>";
        error.AppendMessage(oss.str());
    }

    //
    capturedTo->push_back(error);
}
