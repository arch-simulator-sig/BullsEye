#pragma once
//
// Serial Port infrastructures
//
//
//

#include <iostream>

#include "yasio/xxsocket.hpp"
#include "yasio/xxsocket.cpp"     // not formal, just for compilation convenience :\


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

    public:
        SerialTCPServer() noexcept;
        virtual ~SerialTCPServer() noexcept;

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
        std::cout << (char) data;
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
