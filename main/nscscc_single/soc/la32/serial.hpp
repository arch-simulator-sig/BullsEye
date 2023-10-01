#pragma once
//
// Serial Port infrastructures
//
//
//

#include <iostream>
#include <thread>

#include "xxsocket.hpp"
#include "xxsocket.cpp"     // not formal, just for compilation convenience :\


namespace BullsEye {

    // Serial Interface
    class SerialInterface {
    public:
        virtual ~SerialInterface() noexcept { };

        virtual void        Write(uint8_t data) noexcept = 0;
        virtual bool        IsWriteAvailable() const noexcept = 0;

        virtual uint8_t     Read() noexcept = 0;
        virtual bool        IsReadAvailable() const noexcept = 0;
    };


    // Serial Console
    class SerialConsole : public SerialInterface {
    public:
        SerialConsole() noexcept;
        virtual ~SerialConsole() noexcept;

        virtual void        Write(uint8_t data) noexcept override;
        virtual bool        IsWriteAvailable() const noexcept override;

        virtual uint8_t     Read() noexcept override;
        virtual bool        IsReadAvailable() const noexcept override;
    };


    // Write-only Serial Console
    class SerialWriteOnlyConsole : public SerialInterface {
    public:
        SerialWriteOnlyConsole();
        virtual ~SerialWriteOnlyConsole();

        virtual void        Write(uint8_t data) noexcept override;
        virtual bool        IsWriteAvailable() const noexcept override;

        virtual uint8_t     Read() noexcept override;
        virtual bool        IsReadAvailable() const noexcept override;
    };


    // Serial TCP Server
    class SerialTCPServer : public SerialInterface {
    private:
        yasio::xxsocket     tcp_server;

        bool                accepted;
        yasio::xxsocket     accepted_connection;


    public:
        SerialTCPServer() noexcept;
        virtual ~SerialTCPServer() noexcept;

        bool                OpenServer(const char* addr, uint16_t port) noexcept;
        void                AcceptConnection() noexcept;
        void                CloseServer() noexcept;

        virtual void        Write(uint8_t data) noexcept override;
        virtual bool        IsWriteAvailable() const noexcept override;

        virtual uint8_t     Read() noexcept override;
        virtual bool        IsReadAvailable() const noexcept override;
    };
}


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

    inline bool SerialTCPServer::OpenServer(const char* addr, uint16_t port) noexcept
    {
        return tcp_server.pserve(addr, port) == 0;
    }

    inline void SerialTCPServer::CloseServer() noexcept
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

    inline void SerialTCPServer::Write(uint8_t data) noexcept
    {
        // TODO: Currently blocking, concurrent in future

        if (IsWriteAvailable())
            accepted_connection.send(&data, 1);
    }

    inline bool SerialTCPServer::IsWriteAvailable() const noexcept
    {
        return accepted && accepted_connection.is_open();
    }

    inline uint8_t SerialTCPServer::Read() noexcept
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

    inline bool SerialTCPServer::IsReadAvailable() const noexcept
    {
        return accepted && accepted_connection.is_open();
    }
}
