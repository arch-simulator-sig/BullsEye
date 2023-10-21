#pragma once
//
// Serial Port infrastructures
//
//
//

#ifndef __HEADER_BULLSEYE_NSCSCC2023_LA32_SOC__SERIAL
#define __HEADER_BULLSEYE_NSCSCC2023_LA32_SOC__SERIAL


#include "autoinclude.h"


#include <iostream>
#include <thread>

#include AUTOINC_YASIO(xxsocket.hpp)


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


#endif
