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

static constexpr const char* _COLOR_RESET    = "\033[0m";


//
static inline std::string __ErrnoToString(Jasse::errno_t err)
{
    switch (err)
    {
        case E2BIG:             return "E2BIG";
        case EACCES:            return "EACCES";
        case EADDRINUSE:        return "EADDRINUSE";
        case EADDRNOTAVAIL:     return "EADDRNOTAVAIL";
        case EAFNOSUPPORT:      return "EAFNOSUPPORT";
        case EAGAIN:            return "EAGAIN";
        case EALREADY:          return "EALREADY";
        case EBADF:             return "EBADF";
        case EBADMSG:           return "EBADMSG";
        case EBUSY:             return "EBUSY";
        case ECANCELED:         return "ECANCELED";
        case ECHILD:            return "ECHILD";
        case ECONNABORTED:      return "ECONNABORTED";
        case ECONNREFUSED:      return "ECONNREFUSED";
        case ECONNRESET:        return "ECONNRESET";
        case EDEADLK:           return "EDEADLK";
        case EDESTADDRREQ:      return "EDESTADDRREQ";
        case EDOM:              return "EDOM";
        case EDQUOT:            return "EDQUOT";
        case EEXIST:            return "EEXIST";
        case EFAULT:            return "EFAULT";
        case EFBIG:             return "EFBIG";
        case EHOSTUNREACH:      return "EHOSTUNREACH";
        case EIDRM:             return "EIDRM";
        case EILSEQ:            return "EILSEQ";
        case EINPROGRESS:       return "EINPROGRESS";
        case EINTR:             return "EINTR";
        case EINVAL:            return "EINVAL";
        case EIO:               return "EIO";
        case EISCONN:           return "EISCONN";
        case EISDIR:            return "EISDIR";
        case ELOOP:             return "ELOOP";
        case EMFILE:            return "EMFILE";
        case EMLINK:            return "EMLINK";
        case EMSGSIZE:          return "EMSGSIZE";
        case ENAMETOOLONG:      return "ENAMETOOLONG";
        case ENETDOWN:          return "ENETDOWN";
        case ENETRESET:         return "ENETRESET";
        case ENETUNREACH:       return "ENETUNREACH";
        case ENFILE:            return "ENFILE";
        case ENOBUFS:           return "ENOBUFS";
        case ENODATA:           return "ENODATA";
        case ENODEV:            return "ENODEV";
        case ENOENT:            return "ENOENT";
        case ENOEXEC:           return "ENOEXEC";
        case ENOLCK:            return "ENOLCK";
        case ENOLINK:           return "ENOLINK";
        case ENOMEM:            return "ENOMEM";
        case ENOMSG:            return "ENOMSG";
        case ENOPROTOOPT:       return "ENOPROTOOPT";
        case ENOSPC:            return "ENOSPC";
        case ENOSR:             return "ENOSR";
        case ENOSTR:            return "ENOSTR";
        case ENOSYS:            return "ENOSYS";
        case ENOTCONN:          return "ENOTCONN";
        case ENOTDIR:           return "ENOTDIR";
        case ENOTEMPTY:         return "ENOTEMPTY";
        case ENOTRECOVERABLE:   return "ENOTRECOVERABLE";
        case ENOTSOCK:          return "ENOTSOCK";
        case ENOTSUP:           return "ENOTSUP";
        case ENOTTY:            return "ENOTTY";
        case ENXIO:             return "ENXIO";
    //  case EOPNOTSUPP:        return "EOPNOTSUPP";
        case EOVERFLOW:         return "EOVERFLOW";
        case EOWNERDEAD:        return "EOWNERDEAD";
        case EPERM:             return "EPERM";
        case EPIPE:             return "EPIPE";
        case EPROTO:            return "EPROTO";
        case EPROTONOSUPPORT:   return "EPROTONOSUPPORT";
        case EPROTOTYPE:        return "EPROTOTYPE";
        case ERANGE:            return "ERANGE";
        case EROFS:             return "EROFS";
        case ESPIPE:            return "ESPIPE";
        case ESRCH:             return "ESRCH";
        case ESTALE:            return "ESTALE";
        case ETIME:             return "ETIME";
        case ETIMEDOUT:         return "ETIMEDOUT";
        case ETXTBSY:           return "ETXTBSY";
    //  case EWOULDBLOCK:       return "EWOULDBLOCK";
        case EXDEV:             return "EXDEV";

        default:
            std::ostringstream unkoss;
            unkoss << "<unknown(errno=";
            unkoss << std::dec << uint32_t(err);
            unkoss << ")>";
            return unkoss.str();
    }
}

static inline std::string __MOPStatusToString(Jasse::LA32MOPStatus status)
{
    switch (status)
    {
        case Jasse::LA32MOPStatus::MOP_SUCCESS:
            return "MOP_SUCCESS";

        case Jasse::LA32MOPStatus::MOP_ADDRESS_MISALIGNED:
            return "MOP_ADDRESS_MISALIGNED";

        case Jasse::LA32MOPStatus::MOP_ACCESS_FAULT:
            return "MOP_ACCESS_FAULT";

        case Jasse::LA32MOPStatus::MOP_EMULATION_FAULT:
            return "MOP_EMULATION_FAULT";

        case Jasse::LA32MOPStatus::MOP_SYSTEM_ERROR:
            return "MOP_SYSTEM_ERROR";

        case Jasse::LA32MOPStatus::MOP_DEVICE_ERROR:
            return "MOP_DEVICE_ERROR";

        case Jasse::LA32MOPStatus::MOP_INVALID_PATH:
            return "MOP_INVALID_PATH";

        default:
            std::ostringstream unkoss;
            unkoss << "<unknown(status=";
            unkoss << std::dec << uint32_t(status);
            unkoss << ")>";
            return unkoss.str();
    }
}

static inline std::string __MOPPathToString(Jasse::LA32MOPPath path)
{
    switch (path)
    {
        case Jasse::LA32MOPPath::MOP_DATA:
            return "MOP_DATA";

        case Jasse::LA32MOPPath::MOP_INSN:
            return "MOP_INSN";

        default:
            std::ostringstream unkoss;
            unkoss << "<unknown(path=";
            unkoss << std::dec << uint32_t(path);
            unkoss << ")>";
            return unkoss.str();
    }
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


// Implementation of: class MMUErrorCapture
/*
std::string     source;

CapturedErrors* capturedTo;

unsigned int    errorEventBusId;
int             errorEventPriority;
*/

void MMUErrorCapture::RegisterListeners() noexcept
{
    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnMMUPostReadPostEvent"),
            errorEventPriority,
            &MMUErrorCapture::OnMMUPostReadPostEvent,
            this
        ),
        errorEventBusId
    );

    BullsEye::RegisterListener(
        BullsEye::MakeListener(
            GetListenerName("OnMMUPostWritePostEvent"),
            errorEventPriority,
            &MMUErrorCapture::OnMMUPostWritePostEvent,
            this
        ),
        errorEventBusId
    );
}

void MMUErrorCapture::UnregisterListeners() noexcept
{
    BullsEye::UnregisterListener(
        GetListenerName("OnMMUPostReadPostEvent"),
        &MMUErrorCapture::OnMMUPostReadPostEvent,
        errorEventBusId
    );

    BullsEye::UnregisterListener(
        GetListenerName("OnMMUPostWritePostEvent"),
        &MMUErrorCapture::OnMMUPostWritePostEvent,
        errorEventBusId
    );
}

void MMUErrorCapture::OnMMUPostReadPostEvent(BullsEye::NSCSCCSingle::NSCSCC2023MMUPostReadPostEvent& event) noexcept
{
    if (event.GetOutcome().status != Jasse::LA32MOPStatus::MOP_SUCCESS)
    {
        std::ostringstream oss;

        //
        CapturedError error("NSCSCC2023SoC::MMU", "MMUReadNotSuccess");

        error.AppendMessage("Memory READ operation performed on SoC MMU.");
        error.AppendMessage("But the outcome status of the operation was not success.");

        // 
    //  oss = std::ostringstream();
        oss << "Errored MMU memory operation (from ";
        oss << source;
        oss << "):";
        error.AppendMessage(oss.str());

        //
        oss = std::ostringstream();
        oss << "[-] address : ";
        oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << event.GetAddress();
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] width   : ";
        oss << __MOPWidthToString(event.GetWidth());
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] path    : ";
        oss << __MOPPathToString(event.GetPath());
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] status  : ";
        oss << _COLOR_ERROR;
        oss << __MOPStatusToString(event.GetOutcome().status);
        oss << _COLOR_RESET;
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] error   : ";
        oss << _COLOR_ERROR;
        oss << __ErrnoToString(event.GetOutcome().error);
        oss << _COLOR_RESET;
        error.AppendMessage(oss.str());

        //
        capturedTo->push_back(error);
    }
}

void MMUErrorCapture::OnMMUPostWritePostEvent(BullsEye::NSCSCCSingle::NSCSCC2023MMUPostWritePostEvent& event) noexcept
{
    if (event.GetOutcome().status != Jasse::LA32MOPStatus::MOP_SUCCESS)
    {
        std::ostringstream oss;

        //
        CapturedError error("NSCSCC2023SoC::MMU", "MMUWriteNotSuccess");

        error.AppendMessage("Memory WRITE operation performed on SoC MMU.");
        error.AppendMessage("But the outcome status of the operation was not success.");

        // 
    //  oss = std::ostringstream();
        oss << "Errored MMU memory operation (from ";
        oss << source;
        oss << "):";
        error.AppendMessage(oss.str());

        //
        oss = std::ostringstream();
        oss << "[-] address : ";
        oss << "0x" << std::hex << std::setw(8) << std::setfill('0') << event.GetAddress();
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] width   : ";
        oss << __MOPWidthToString(event.GetWidth());
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] path    : ";
        oss << __MOPPathToString(event.GetPath());
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] status  : ";
        oss << _COLOR_ERROR;
        oss << __MOPStatusToString(event.GetOutcome().status);
        oss << _COLOR_RESET;
        error.AppendMessage(oss.str());

        oss = std::ostringstream();
        oss << "[-] error   : ";
        oss << _COLOR_ERROR;
        oss << __ErrnoToString(event.GetOutcome().error);
        oss << _COLOR_RESET;
        error.AppendMessage(oss.str());

        //
        capturedTo->push_back(error);
    }
}

