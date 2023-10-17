#include "serial.hpp"
//
// Serial Port infrastructures
//
//
//


// Implementation of: class SerialWriteOnlyConsole
namespace BullsEye {

    SerialWriteOnlyConsole::SerialWriteOnlyConsole()
    { }

    SerialWriteOnlyConsole::~SerialWriteOnlyConsole()
    { }

    void SerialWriteOnlyConsole::Write(uint8_t data) noexcept
    {
        std::cout << (char) data << std::flush;
    }

    bool SerialWriteOnlyConsole::IsWriteAvailable() const noexcept
    {
        return true;
    }

    uint8_t SerialWriteOnlyConsole::Read() noexcept
    {
        return 0;
    }

    bool SerialWriteOnlyConsole::IsReadAvailable() const noexcept
    {
        return false;
    }
}


// Implementation of: class SerialTCPServer
namespace BullsEye {
    //
    // yasio::xxsocket     tcp_server;
    //

    SerialTCPServer::SerialTCPServer() noexcept
        : tcp_server            ()
        , accepted              (false)
        , accepted_connection   ()
    { }

    SerialTCPServer::~SerialTCPServer() noexcept
    { }

    bool SerialTCPServer::OpenServer(const char* addr, uint16_t port) noexcept
    {
        return tcp_server.pserve(addr, port) == 0;
    }

    void SerialTCPServer::CloseServer() noexcept
    {
        accepted_connection.close();
        accepted = false;
        
        tcp_server.close();
    }

    void SerialTCPServer::AcceptConnection() noexcept
    {
        std::thread([&]() {
            this->accepted_connection = this->tcp_server.accept();
            this->accepted = true;
        }).detach();
    }

    void SerialTCPServer::Write(uint8_t data) noexcept
    {
        // TODO: Currently blocking, concurrent in future

        if (IsWriteAvailable())
            accepted_connection.send(&data, 1);
    }

    bool SerialTCPServer::IsWriteAvailable() const noexcept
    {
        return accepted && accepted_connection.is_open();
    }

    uint8_t SerialTCPServer::Read() noexcept
    {
        // TODO: Currently blocking, concurrent in future

        if (IsReadAvailable())
        {
            uint8_t data;
            accepted_connection.recv(&data, 1);
            return data;
        }
        else
            return 0;
    }

    bool SerialTCPServer::IsReadAvailable() const noexcept
    {
        return accepted && accepted_connection.is_open();
    }
}
