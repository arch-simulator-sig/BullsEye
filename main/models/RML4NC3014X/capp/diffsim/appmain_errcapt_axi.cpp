#include "appmain_errcapt.hpp"
//
//
//
//

#include <sstream>
#include <iomanip>
#include <cerrno>


//
static constexpr const char* _COLOR_CORRECT  = "\033[1;32m";

static constexpr const char* _COLOR_ERROR    = "\033[1;31m";

static constexpr const char* _COLOR_COMMENT     = "\033[1;30m";

static constexpr const char* _COLOR_RESET    = "\033[0m";


static inline std::string __AddressToString(uint32_t address) noexcept
{
    std::ostringstream oss;

    oss << "0x";
    oss << std::hex << std::setfill('0') << std::setw(8) << address;

    return oss.str();
}

static inline std::string __ErrorTypeToString(BullsEye::Draconids3014::SoCAXIBridgeErrorEventBase::ErrorType type) noexcept
{
    std::ostringstream oss;

    switch (type)
    {
        case BullsEye::Draconids3014::SoCAXIBridgeFetchErrorEvent::ErrorType::READ_MOP_NOT_SUCCESS:
            oss << "READ_MOP_NOT_SUCCESS";
            oss << _COLOR_COMMENT << " (Read Memory/Device Operation Not Success)";
            break;

        case BullsEye::Draconids3014::SoCAXIBridgeFetchErrorEvent::ErrorType::WRITE_MOP_NOT_SUCCESS:
            oss << "WRITE_MOP_NOT_SUCCESS";
            oss << _COLOR_COMMENT << " (Write Memory/Device Operation Not Success)";
            break;

        case BullsEye::Draconids3014::SoCAXIBridgeFetchErrorEvent::ErrorType::WRITE_OVERFLOW:
            oss << "WRITE_OVERFLOW";
            oss << _COLOR_COMMENT << " (Write Burst Overflow)";
            break;

        case BullsEye::Draconids3014::SoCAXIBridgeFetchErrorEvent::ErrorType::WRITE_UNDERFLOW:
            oss << "WRITE_UNDERFLOW";
            oss << _COLOR_COMMENT << " (Write Burst Underflow)";
            break;

        default:
            oss << "<unknown(type=";
            oss << uint32_t(type);
            oss << ")>";
    }

    return oss.str();
}

static inline std::string __LengthToString(BullsEye::AXI4::attr_len_t length) noexcept
{
    std::ostringstream oss;

    oss << (uint32_t(length) + 1);

    return oss.str();
}

static inline std::string __SizeToString(BullsEye::AXI4::attr_size_t size) noexcept
{
    switch (size)
    {
        case BullsEye::AXI4::Attributes::AXSIZE_1B:
            return "1B";

        case BullsEye::AXI4::Attributes::AXSIZE_2B:
            return "2B";

        case BullsEye::AXI4::Attributes::AXSIZE_4B:
            return "4B";

        case BullsEye::AXI4::Attributes::AXSIZE_8B:
            return "8B";

        case BullsEye::AXI4::Attributes::AXSIZE_16B:
            return "16B";

        case BullsEye::AXI4::Attributes::AXSIZE_32B:
            return "32B";

        case BullsEye::AXI4::Attributes::AXSIZE_64B:
            return "64B";

        case BullsEye::AXI4::Attributes::AXSIZE_128B:
            return "128B";

        default:
            std::ostringstream unkoss;
            unkoss << "<unknown(size=";
            unkoss << uint32_t(size);
            unkoss << ")>";
            return unkoss.str();
    }
}

static inline std::string __BurstToString(BullsEye::AXI4::attr_burst_t burst) noexcept
{
    switch (burst)
    {
        case BullsEye::AXI4::Attributes::AXBURST_FIXED:
            return "FIXED";

        case BullsEye::AXI4::Attributes::AXBURST_INCR:
            return "INCR";

        case BullsEye::AXI4::Attributes::AXBURST_WRAP:
            return "WRAP";

        default:
            std::ostringstream unkoss;
            unkoss << "<unknown(burst=";
            unkoss << uint32_t(burst);
            unkoss << ")>";
            return unkoss.str();
    }
}



// Implementation of: class AXIBridgeErrorCapture
/*
std::string         source;

CapturedErrors*     capturedTo;

unsigned int        errorEventBusId;
int                 errorEventPriority;

unsigned int        traceDepth;
std::deque<Trace>   trace;
*/

void AXIBridgeErrorCapture::RegisterListeners() noexcept
{
    //
    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnFetchReadAccepted"),
            errorEventPriority,
            &AXIBridgeErrorCapture::OnFetchReadAccepted,
            this
        ),
        errorEventBusId
    );

    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnDataReadAccepted"),
            errorEventPriority,
            &AXIBridgeErrorCapture::OnDataReadAccepted,
            this
        ),
        errorEventBusId
    );

    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnDataWriteAccepted"),
            errorEventPriority,
            &AXIBridgeErrorCapture::OnDataWriteAccepted,
            this
        ),
        errorEventBusId
    );

    //
    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnFetchError"),
            errorEventPriority,
            &AXIBridgeErrorCapture::OnFetchError,
            this
        ),
        errorEventBusId
    );

    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnDataError"),
            errorEventPriority,
            &AXIBridgeErrorCapture::OnDataError,
            this
        ),
        errorEventBusId
    );
}

void AXIBridgeErrorCapture::UnregisterListeners() noexcept
{
    //
     BullsEye::UnregisterListener(
        GetListenerName("OnFetchReadAccepted"),
        &AXIBridgeErrorCapture::OnFetchReadAccepted,
        errorEventBusId
    );

    BullsEye::UnregisterListener(
        GetListenerName("OnDataReadAccepted"),
        &AXIBridgeErrorCapture::OnDataReadAccepted,
        errorEventBusId
    );

    BullsEye::UnregisterListener(
        GetListenerName("OnDataWriteAccepted"),
        &AXIBridgeErrorCapture::OnDataWriteAccepted,
        errorEventBusId
    );    

    //
    BullsEye::UnregisterListener(
        GetListenerName("OnFetchError"),
        &AXIBridgeErrorCapture::OnFetchError,
        errorEventBusId
    );

    BullsEye::UnregisterListener(
        GetListenerName("OnDataError"),
        &AXIBridgeErrorCapture::OnDataError,
        errorEventBusId
    );
}

void AXIBridgeErrorCapture::OnFetchReadAccepted(BullsEye::Draconids3014::SoCAXIBridgeFetchReadAddressAcceptedPostEvent& event) noexcept
{
    auto& bundle = event.GetBundle();

    auto& trace = traces.emplace_front();

    trace.type      = Trace::Type::READ;
    trace.path      = Trace::Path::INSN;

    trace.id        = bundle.arid;
    trace.address   = bundle.araddr;
    trace.length    = bundle.arlen;
    trace.size      = bundle.arsize;
    trace.burst     = bundle.arburst;
    trace.uncached  = bundle.aruser;

    while (traces.size() >= traceDepth)
        traces.pop_back();
}

void AXIBridgeErrorCapture::OnDataReadAccepted(BullsEye::Draconids3014::SoCAXIBridgeDataReadAddressAcceptedPostEvent& event) noexcept
{
    auto& bundle = event.GetBundle();

    auto& trace = traces.emplace_front();

    trace.type      = Trace::Type::READ;
    trace.path      = Trace::Path::DATA;

    trace.id        = bundle.arid;
    trace.address   = bundle.araddr;
    trace.length    = bundle.arlen;
    trace.size      = bundle.arsize;
    trace.burst     = bundle.arburst;
    trace.uncached  = bundle.aruser;

    while (traces.size() >= traceDepth)
        traces.pop_back();
}

void AXIBridgeErrorCapture::OnDataWriteAccepted(BullsEye::Draconids3014::SoCAXIBridgeDataWriteAddressAcceptedPostEvent& event) noexcept
{
    auto& bundle = event.GetBundle();

    auto& trace = traces.emplace_front();

    trace.type      = Trace::Type::WRITE;
    trace.path      = Trace::Path::DATA;

    trace.id        = bundle.awid;
    trace.address   = bundle.awaddr;
    trace.length    = bundle.awlen;
    trace.size      = bundle.awsize;
    trace.burst     = bundle.awburst;
    trace.uncached  = bundle.awuser;

    while (traces.size() >= traceDepth)
        traces.pop_back();
}

void AXIBridgeErrorCapture::OnFetchError(BullsEye::Draconids3014::SoCAXIBridgeFetchErrorEvent& event) noexcept
{
    std::ostringstream oss;

    //
    CapturedError error("SoCAXIBridge", "FetchChannelError");

    error.AppendMessage("AXI Bridge detected interaction error on bus.");

    //
//  oss = std::ostringstream();
    oss << "Errored on bus interaction:";
    error.AppendMessage(oss.str());

    //
    oss = std::ostringstream();
    oss << "[-] error   : ";
    oss << _COLOR_ERROR;
    oss << __ErrorTypeToString(event.GetType());
    oss << _COLOR_RESET;

    //
    for (auto& trace : traces)
    {
        if (trace.id != event.GetTransactionID())
            continue;

        if (trace.path != Trace::Path::INSN)
            continue;

        if (trace.type == Trace::Type::READ)
        {
            switch (event.GetType())
            {
                case BullsEye::Draconids3014::SoCAXIBridgeFetchErrorEvent::ErrorType::READ_MOP_NOT_SUCCESS:
                    break;

                default:
                    continue;
            }
        }
        else if (trace.type == Trace::Type::WRITE)
        {
            switch (event.GetType())
            {
                case BullsEye::Draconids3014::SoCAXIBridgeFetchErrorEvent::ErrorType::WRITE_MOP_NOT_SUCCESS:
                    [[fallthrough]];
                case BullsEye::Draconids3014::SoCAXIBridgeFetchErrorEvent::ErrorType::WRITE_OVERFLOW:
                    [[fallthrough]];
                case BullsEye::Draconids3014::SoCAXIBridgeFetchErrorEvent::ErrorType::WRITE_UNDERFLOW:
                    break;

                default:
                    continue;
            }
        }
        else
            continue;

        //
        oss = std::ostringstream();
        oss << "[-] id      : ";
        oss << std::dec << trace.id;
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] address : ";
        oss << __AddressToString(trace.address);
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] length  : ";
        oss << __LengthToString(trace.length);
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] size    : ";
        oss << __SizeToString(trace.size);
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] burst   : ";
        oss << __BurstToString(trace.burst);
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] uncached: ";
        oss << std::dec << trace.uncached;
        error.AppendMessage(oss.str());

        //
        capturedTo->push_back(error);

        return;
    }

    //
    oss = std::ostringstream();
    oss << "[-] ";
    oss << _COLOR_COMMENT << "<out-of-trace>";
    oss << _COLOR_RESET;
    error.AppendMessage(oss.str());

    //
    capturedTo->push_back(error);
}

void AXIBridgeErrorCapture::OnDataError(BullsEye::Draconids3014::SoCAXIBridgeDataErrorEvent& event) noexcept
{
    std::ostringstream oss;

    //
    CapturedError error("SoCAXIBridge", "DataChannelError");

    error.AppendMessage("AXI Bridge detected interaction error on bus.");

    //
//  oss = std::ostringstream();
    oss << "Errored on bus interaction:";
    error.AppendMessage(oss.str());

    //
    oss = std::ostringstream();
    oss << "[-] error   : ";
    oss << _COLOR_ERROR;
    oss << __ErrorTypeToString(event.GetType());
    oss << _COLOR_RESET;
    error.AppendMessage(oss.str());

    //
    for (auto& trace : traces)
    {
        if (trace.id != event.GetTransactionID())
            continue;

        if (trace.path != Trace::Path::DATA)
            continue;

        if (trace.type == Trace::Type::READ)
        {
            switch (event.GetType())
            {
                case BullsEye::Draconids3014::SoCAXIBridgeFetchErrorEvent::ErrorType::READ_MOP_NOT_SUCCESS:
                    break;

                default:
                    continue;
            }
        }
        else if (trace.type == Trace::Type::WRITE)
        {
            switch (event.GetType())
            {
                case BullsEye::Draconids3014::SoCAXIBridgeFetchErrorEvent::ErrorType::WRITE_MOP_NOT_SUCCESS:
                    [[fallthrough]];
                case BullsEye::Draconids3014::SoCAXIBridgeFetchErrorEvent::ErrorType::WRITE_OVERFLOW:
                    [[fallthrough]];
                case BullsEye::Draconids3014::SoCAXIBridgeFetchErrorEvent::ErrorType::WRITE_UNDERFLOW:
                    break;

                default:
                    continue;
            }
        }
        else
            continue;

        //
        oss = std::ostringstream();
        oss << "[-] id      : ";
        oss << std::dec << uint32_t(trace.id);
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] address : ";
        oss << __AddressToString(trace.address);
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] length  : ";
        oss << __LengthToString(trace.length);
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] size    : ";
        oss << __SizeToString(trace.size);
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] burst   : ";
        oss << __BurstToString(trace.burst);
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] uncached: ";
        oss << std::dec << uint32_t(trace.uncached);
        error.AppendMessage(oss.str());

        //
        capturedTo->push_back(error);

        return;
    }

    //
    oss = std::ostringstream();
    oss << "[-] ";
    oss << _COLOR_COMMENT << "<out-of-trace>";
    oss << _COLOR_RESET;
    error.AppendMessage(oss.str());

    //
    capturedTo->push_back(error);
}
