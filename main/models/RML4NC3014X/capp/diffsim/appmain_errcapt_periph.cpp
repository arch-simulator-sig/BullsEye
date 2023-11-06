#include "appmain_errcapt.hpp"
//
//
//
//

#include <string>
#include <sstream>
#include <iomanip>


#include "autoinclude.h"

#include AUTOINC_BE_JASSE2_LA32(base/la32mem.hpp)


//
static constexpr const char* _COLOR_CORRECT  = "\033[1;32m";

static constexpr const char* _COLOR_ERROR    = "\033[1;31m";

static constexpr const char* _COLOR_RESET    = "\033[0m";



//
static inline std::string __ToString(PeripheralInjector::Element::Source source)
{
    switch (source)
    {
        case PeripheralInjector::Element::Source::REF:
            return "REF";

        case PeripheralInjector::Element::Source::DUT:
            return "DUT";

        [[unlikely]] default:
            std::ostringstream unkoss;
            unkoss << "<unknown(";
            unkoss << "source=" << uint64_t(source);
            unkoss << ")>";
            return unkoss.str();
    }
}

static inline std::string __ToString(PeripheralInjector::Element::Type type)
{
    switch (type)
    {
        case PeripheralInjector::Element::Type::LOAD:
            return "LOAD";

        case PeripheralInjector::Element::Type::STORE:
            return "STORE";

        [[unlikely]] default:
            std::ostringstream unkoss;
            unkoss << "<unknown(";
            unkoss << "type=" << uint64_t(type);
            unkoss << ")>";
            return unkoss.str();
    }
}

static inline std::string __ToString(Jasse::addr_t address) noexcept
{
    std::ostringstream oss;

    oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << address;

    return oss.str();
}

static inline std::string __ToString(Jasse::LA32MOPWidth width) noexcept
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

static inline std::string __ToString(Jasse::LA32MOPWidth width, Jasse::memdata_t data) noexcept
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



// Implementation of: class PeripheralErrorCapture
void PeripheralErrorCapture::RegisterListeners() noexcept
{
    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnPeripheralInjectorRejected"),
            errorEventPriority,
            &PeripheralErrorCapture::OnPeripheralInjectorRejected,
            this
        ),
        errorEventBusId
    );

    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnPeripheralInjectorNojected"),
            errorEventPriority,
            &PeripheralErrorCapture::OnPeripheralInjectorNojected,
            this
        ),
        errorEventBusId
    );
}

void PeripheralErrorCapture::UnregisterListeners() noexcept
{
    BullsEye::UnregisterListener(
        GetListenerName("OnPeripheralInjectorRejected"),
        &PeripheralErrorCapture::OnPeripheralInjectorRejected,
        errorEventBusId
    );

    BullsEye::UnregisterListener(
        GetListenerName("OnPeripheralInjectorNojected"),
        &PeripheralErrorCapture::OnPeripheralInjectorNojected,
        errorEventBusId
    );
}


void PeripheralErrorCapture::OnPeripheralInjectorRejected(PeripheralInjector::RejectedEvent& event) noexcept
{
    std::ostringstream oss;

    //
    CapturedError error("PeripheralInjector", "InjectionMismatch(rejected)");

    error.AppendMessage("Reference model performed differently on peripheral access.");
    error.AppendMessage("DUT didn't accessed peripheral as expected.");

    //
    error.AppendMessage("Errored peripheral access (from injector):");

//  oss = std::ostringstream();
    oss << "[R] source  : ";
    oss << __ToString(event.GetRejection().GetSource());
    error.AppendMessage(oss.str());

    oss = std::ostringstream();
    oss << "[R] type    : ";
    oss << __ToString(event.GetRejection().GetType());
    error.AppendMessage(oss.str());

    oss = std::ostringstream();
    oss << "[R] address : ";
    oss << __ToString(event.GetRejection().GetAddress());
    error.AppendMessage(oss.str());

    oss = std::ostringstream();
    oss << "[R] width   : ";
    oss << __ToString(event.GetRejection().GetWidth());
    error.AppendMessage(oss.str());

    if (event.GetRejection().GetType() == PeripheralInjector::Element::Type::STORE)
    {
        oss = std::ostringstream();
        oss << "[R] data    : ";
        oss << __ToString(event.GetRejection().GetWidth(), event.GetRejection().GetData());
        error.AppendMessage(oss.str());
    }

    //
    error.AppendMessage("Errored peripheral access (from rejector):");

    oss = std::ostringstream();
    oss << "[D] source  : ";
    oss << __ToString(event.GetInjection().GetSource());
    error.AppendMessage(oss.str());

    oss = std::ostringstream();
    oss << "[D] type    : ";
    oss << ((event.GetInjection().GetType() != event.GetRejection().GetType())
        ? _COLOR_ERROR : _COLOR_CORRECT);
    oss << __ToString(event.GetInjection().GetType());
    oss << _COLOR_RESET;
    error.AppendMessage(oss.str());

    oss = std::ostringstream();
    oss << "[D] address : ";
    oss << ((event.GetInjection().GetAddress() != event.GetRejection().GetAddress())
        ? _COLOR_ERROR : _COLOR_CORRECT);
    oss << __ToString(event.GetInjection().GetAddress());
    oss << _COLOR_RESET;
    error.AppendMessage(oss.str());

    oss = std::ostringstream();
    oss << "[D] width   : ";
    oss << ((event.GetInjection().GetWidth() != event.GetRejection().GetWidth())
        ? _COLOR_ERROR : _COLOR_CORRECT);
    oss << __ToString(event.GetInjection().GetWidth());
    oss << _COLOR_RESET;
    error.AppendMessage(oss.str());

    oss = std::ostringstream();
    oss << "[D] data    : ";
    if (event.GetRejection().GetType() == PeripheralInjector::Element::Type::STORE)
        oss << ((event.GetInjection().GetWidth() != event.GetRejection().GetWidth())
            ? _COLOR_ERROR : _COLOR_CORRECT);
    oss << __ToString(event.GetInjection().GetWidth(), event.GetInjection().GetData());
    oss << _COLOR_RESET;
    error.AppendMessage(oss.str());

    //
    capturedTo->push_back(error);
}


void PeripheralErrorCapture::OnPeripheralInjectorNojected(PeripheralInjector::NojectedEvent& event) noexcept
{
    std::ostringstream oss;

    //
    CapturedError error("PeripheralInjector", "InjectionMismatch(underflow)");

    error.AppendMessage("Reference model performed differently on peripheral access.");
    error.AppendMessage("DUT accessed peripheral less times than expected.");

    //
    error.AppendMessage("Errored peripheral access (from rejector):");

//  oss = std::ostringstream();
    oss << "[R] source  : ";
    oss << __ToString(event.GetRejection().GetSource());
    error.AppendMessage(oss.str());

    oss = std::ostringstream();
    oss << "[R] type    : ";
    oss << __ToString(event.GetRejection().GetType());
    error.AppendMessage(oss.str());

    oss = std::ostringstream();
    oss << "[R] address : ";
    oss << __ToString(event.GetRejection().GetAddress());
    error.AppendMessage(oss.str());

    oss = std::ostringstream();
    oss << "[R] width   : ";
    oss << __ToString(event.GetRejection().GetWidth());
    error.AppendMessage(oss.str());

    if (event.GetRejection().GetType() == PeripheralInjector::Element::Type::STORE)
    {
        oss = std::ostringstream();
        oss << "[R] data    : ";
        oss << __ToString(event.GetRejection().GetWidth(), event.GetRejection().GetData());
        error.AppendMessage(oss.str());
    }

    //
    capturedTo->push_back(error);
}
