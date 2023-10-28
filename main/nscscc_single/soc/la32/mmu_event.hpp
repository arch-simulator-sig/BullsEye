#pragma once
//
//

#ifndef __HEADER_BULLSEYE_NSCSCC2023_LA32_SOC__MMU_EVENT
#define __HEADER_BULLSEYE_NSCSCC2023_LA32_SOC__MMU_EVENT

#include <functional>


#include "autoinclude.h"

#include AUTOINC_BE_COMMON(eventbus.hpp)

#include AUTOINC_BE_JASSE2_LA32(base/la32mem.hpp)


#include "mmu.hpp"


namespace BullsEye::NSCSCCSingle {

    // NSCSCC 2023 MMU Event Base
    class NSCSCC2023MMUEventBase {
    private:
        NSCSCC2023MMU*  mmu;

    public:
        NSCSCC2023MMUEventBase(NSCSCC2023MMU* mmu) noexcept;

        NSCSCC2023MMU*          GetMMU() noexcept;
        const NSCSCC2023MMU*    GetMMU() const noexcept;
    };


    // NSCSCC 2023 MMU Pre Read Pre Event Base
    class NSCSCC2023MMUPreReadPreEventBase {
    public:
        using proxy_type = std::function<LA32MOPOutcome(addr_t, LA32MOPWidth, memdata_t&)>;
        
    private:
        addr_t&         address;
        LA32MOPWidth&   width;

        bool            proxy;
        proxy_type      proxy_routine;

    public:
        NSCSCC2023MMUPreReadPreEventBase(addr_t& address, LA32MOPWidth& width) noexcept;

        addr_t          GetAddress() const noexcept;
        void            SetAddress(addr_t address) noexcept;

        LA32MOPWidth    GetWidth() const noexcept;
        void            SetWidth(LA32MOPWidth width) noexcept;

        void            SetProxy(bool proxy) noexcept;
        bool            HasProxy() const noexcept;

        void            SetProxyRoutine(proxy_type proxy_routine) noexcept;
        proxy_type      GetProxyRoutine() const noexcept;

        void            SetProxy(bool proxy, proxy_type proxy_routine) noexcept;
    };

    // NSCSCC 2023 MMU Pre Read Post Event Base
    class NSCSCC2023MMUPreReadPostEventBase {
    private:
        addr_t          address;
        LA32MOPWidth    width;

    public:
        NSCSCC2023MMUPreReadPostEventBase(addr_t address, LA32MOPWidth width) noexcept;

        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;
    };

    // NSCSCC 2023 MMU Post Read Pre Event Base
    class NSCSCC2023MMUPostReadPreEventBase {
    private:
        addr_t          address;
        LA32MOPWidth    width;
        memdata_t&      data;

    public:
        NSCSCC2023MMUPostReadPreEventBase(addr_t address, LA32MOPWidth width, memdata_t& data) noexcept;

        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;

        memdata_t       GetData() const noexcept;
        void            SetData(memdata_t data) noexcept;
    };

    // NSCSCC 2023 MMU Post Read Post Event Base
    class NSCSCC2023MMUPostReadPostEventBase {
    private:
        addr_t          address;
        LA32MOPWidth    width;
        memdata_t       data;

    public:
        NSCSCC2023MMUPostReadPostEventBase(addr_t address, LA32MOPWidth width, memdata_t data) noexcept;

        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;

        memdata_t       GetData() const noexcept;
    };


    // NSCSCC 2023 MMU Pre Write Pre Event Base
    class NSCSCC2023MMUPreWritePreEventBase {
    public:
        using proxy_type = std::function<LA32MOPOutcome(addr_t, LA32MOPWidth, memdata_t)>;

    private:
        addr_t&         address;
        LA32MOPWidth&   width;
        memdata_t&      data;

        bool            proxy;
        proxy_type      proxy_routine;

    public:
        NSCSCC2023MMUPreWritePreEventBase(addr_t& address, LA32MOPWidth& width, memdata_t& data) noexcept;

        addr_t          GetAddress() const noexcept;
        void            SetAddress(addr_t address) noexcept;

        LA32MOPWidth    GetWidth() const noexcept;
        void            SetWidth(LA32MOPWidth width) noexcept;

        memdata_t       GetData() const noexcept;
        void            SetData(memdata_t data) noexcept;

        bool            HasProxy() const noexcept;
        void            SetProxy(bool proxy) noexcept;

        proxy_type      GetProxyRoutine() const noexcept;
        void            SetProxyRoutine(proxy_type proxy_routine) noexcept;

        void            SetProxy(bool proxy, proxy_type proxy_routine) noexcept;
    };

    // NSCSCC 2023 MMU Pre Write Post Event Base
    class NSCSCC2023MMUPreWritePostEventBase {
    private:
        addr_t          address;
        LA32MOPWidth    width;
        memdata_t       data;

    public:
        NSCSCC2023MMUPreWritePostEventBase(addr_t address, LA32MOPWidth width, memdata_t data) noexcept;

        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;
        memdata_t       GetData() const noexcept;
    };

    // NSCSCC 2023 MMU Post Write Event Base
    class NSCSCC2023MMUPostWriteEventBase {
    private:
        addr_t          address;
        LA32MOPWidth    width;
        memdata_t       data;

    public:
        NSCSCC2023MMUPostWriteEventBase(addr_t address, LA32MOPWidth width, memdata_t data) noexcept;

        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;
        memdata_t       GetData() const noexcept;
    };



    // NSCSCC2023 MMU Serial Pre Read Pre Event
    class NSCSCC2023MMUSerialPreReadPreEvent 
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreReadPreEventBase
        , public Event<NSCSCC2023MMUSerialPreReadPreEvent>
        , public CancellableEvent {
    public:
        NSCSCC2023MMUSerialPreReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t&             address, 
            LA32MOPWidth&       width) noexcept;
    };

    // NSCSCC2023 MMU Serial Pre Read Post Event
    class NSCSCC2023MMUSerialPreReadPostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreReadPostEventBase
        , public Event<NSCSCC2023MMUSerialPreReadPostEvent> {
    public:
        NSCSCC2023MMUSerialPreReadPostEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width) noexcept;
    };

    // NSCSCC2023 MMU Serial Post Read Pre Event
    class NSCSCC2023MMUSerialPostReadPreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPreEventBase
        , public Event<NSCSCC2023MMUSerialPostReadPreEvent> 
        , public CancellableEvent {
    public:
        NSCSCC2023MMUSerialPostReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t&          data) noexcept;
    };

    // NSCSCC2023 MMU Serial Post Read Post Event
    class NSCSCC2023MMUSerialPostReadPostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPostEventBase
        , public Event<NSCSCC2023MMUSerialPostReadPostEvent> {
    public:
        NSCSCC2023MMUSerialPostReadPostEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data) noexcept;
    };

    
    // NSCSCC2023 MMU Serial Pre Write Pre Event
    class NSCSCC2023MMUSerialPreWritePreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreWritePreEventBase
        , public Event<NSCSCC2023MMUSerialPreWritePreEvent>
        , public CancellableEvent {
    public:
        NSCSCC2023MMUSerialPreWritePreEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t&             address, 
            LA32MOPWidth&       width, 
            memdata_t&          data) noexcept;
    };

    // NSCSCC2023 MMU Serial Pre Write Post Event
    class NSCSCC2023MMUSerialPreWritePostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreWritePostEventBase
        , public Event<NSCSCC2023MMUSerialPreWritePostEvent> {
    public:
        NSCSCC2023MMUSerialPreWritePostEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data) noexcept;
    };

    // NSCSCC2023 MMU Serial Post Write Pre Event
    class NSCSCC2023MMUSerialPostWritePreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostWriteEventBase
        , public Event<NSCSCC2023MMUSerialPostWritePreEvent>
        , public CancellableEvent {
    public:
        NSCSCC2023MMUSerialPostWritePreEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data) noexcept;
    };

    // NSCSCC2023 MMU Serial Post Write Post Event
    class NSCSCC2023MMUSerialPostWritePostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostWriteEventBase
        , public Event<NSCSCC2023MMUSerialPostWritePostEvent> {
    public:
        NSCSCC2023MMUSerialPostWritePostEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data) noexcept;
    };



    // NSCSCC2023 MMU BaseRAM Pre Read Pre Event
    class NSCSCC2023MMUBaseRAMPreReadPreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreReadPreEventBase
        , public Event<NSCSCC2023MMUBaseRAMPreReadPreEvent>
        , public CancellableEvent {
    public:
        NSCSCC2023MMUBaseRAMPreReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t&             address, 
            LA32MOPWidth&       width) noexcept;
    };

    // NSCSCC2023 MMU BaseRAM Pre Read Post Event
    class NSCSCC2023MMUBaseRAMPreReadPostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreReadPostEventBase
        , public Event<NSCSCC2023MMUBaseRAMPreReadPostEvent> {
    public:
        NSCSCC2023MMUBaseRAMPreReadPostEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width) noexcept;
    };

    // NSCSCC2023 MMU BaseRAM Post Read Pre Event
    class NSCSCC2023MMUBaseRAMPostReadPreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPreEventBase
        , public Event<NSCSCC2023MMUBaseRAMPostReadPreEvent>
        , public CancellableEvent {
    public:
        NSCSCC2023MMUBaseRAMPostReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t&          data) noexcept;
    };

    // NSCSCC2023 MMU BaseRAM Post Read Post Event
    class NSCSCC2023MMUBaseRAMPostReadPostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPostEventBase
        , public Event<NSCSCC2023MMUBaseRAMPostReadPostEvent> {
    public:
        NSCSCC2023MMUBaseRAMPostReadPostEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data) noexcept;
    };


    // NSCSCC2023 MMU BaseRAM Pre Write Pre Event
    class NSCSCC2023MMUBaseRAMPreWritePreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreWritePreEventBase
        , public Event<NSCSCC2023MMUBaseRAMPreWritePreEvent>
        , public CancellableEvent {
    public:
        NSCSCC2023MMUBaseRAMPreWritePreEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t&             address, 
            LA32MOPWidth&       width, 
            memdata_t&          data) noexcept;
    };

    // NSCSCC2023 MMU BaseRAM Pre Write Post Event
    class NSCSCC2023MMUBaseRAMPreWritePostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreWritePostEventBase
        , public Event<NSCSCC2023MMUBaseRAMPreWritePostEvent> {
    public:
        NSCSCC2023MMUBaseRAMPreWritePostEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data) noexcept;
    };

    // NSCSCC2023 MMU BaseRAM Post Write Pre Event
    class NSCSCC2023MMUBaseRAMPostWritePreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostWriteEventBase
        , public Event<NSCSCC2023MMUBaseRAMPostWritePreEvent>
        , public CancellableEvent {
    public:
        NSCSCC2023MMUBaseRAMPostWritePreEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data) noexcept;
    };

    // NSCSCC2023 MMU BaseRAM Post Write Post Event
    class NSCSCC2023MMUBaseRAMPostWritePostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostWriteEventBase
        , public Event<NSCSCC2023MMUBaseRAMPostWritePostEvent> {
    public:
        NSCSCC2023MMUBaseRAMPostWritePostEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data) noexcept;
    };



    // NSCSCC2023 MMU ExtRAM Pre Read Pre Event
    class NSCSCC2023MMUExtRAMPreReadPreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreReadPreEventBase
        , public Event<NSCSCC2023MMUExtRAMPreReadPreEvent>
        , public CancellableEvent {
    public:
        NSCSCC2023MMUExtRAMPreReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t&             address, 
            LA32MOPWidth&       width) noexcept;
    };

    // NSCSCC2023 MMU ExtRAM Pre Read Post Event
    class NSCSCC2023MMUExtRAMPreReadPostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreReadPostEventBase
        , public Event<NSCSCC2023MMUExtRAMPreReadPostEvent> {
    public:
        NSCSCC2023MMUExtRAMPreReadPostEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width) noexcept;
    };

    // NSCSCC2023 MMU ExtRAM Post Read Pre Event
    class NSCSCC2023MMUExtRAMPostReadPreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPreEventBase
        , public Event<NSCSCC2023MMUExtRAMPostReadPreEvent>
        , public CancellableEvent {
    public:
        NSCSCC2023MMUExtRAMPostReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t&          data) noexcept;
    };

    // NSCSCC2023 MMU ExtRAM Post Read Post Event
    class NSCSCC2023MMUExtRAMPostReadPostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPostEventBase
        , public Event<NSCSCC2023MMUExtRAMPostReadPostEvent> {
    public:
        NSCSCC2023MMUExtRAMPostReadPostEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data) noexcept;
    };

    
    // NSCSCC2023 MMU ExtRAM Pre Write Pre Event
    class NSCSCC2023MMUExtRAMPreWritePreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreWritePreEventBase
        , public Event<NSCSCC2023MMUExtRAMPreWritePreEvent>
        , public CancellableEvent {
    public:
        NSCSCC2023MMUExtRAMPreWritePreEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t&             address, 
            LA32MOPWidth&       width, 
            memdata_t&          data) noexcept;
    };

    // NSCSCC2023 MMU ExtRAM Pre Write Post Event
    class NSCSCC2023MMUExtRAMPreWritePostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreWritePostEventBase
        , public Event<NSCSCC2023MMUExtRAMPreWritePostEvent> {
    public:
        NSCSCC2023MMUExtRAMPreWritePostEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data) noexcept;
    };

    // NSCSCC2023 MMU ExtRAM Post Write Pre Event
    class NSCSCC2023MMUExtRAMPostWritePreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostWriteEventBase
        , public Event<NSCSCC2023MMUExtRAMPostWritePreEvent>
        , public CancellableEvent {
    public:
        NSCSCC2023MMUExtRAMPostWritePreEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data) noexcept;
    };

    // NSCSCC2023 MMU ExtRAM Post Write Post Event
    class NSCSCC2023MMUExtRAMPostWritePostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostWriteEventBase
        , public Event<NSCSCC2023MMUExtRAMPostWritePostEvent> {
    public:
        NSCSCC2023MMUExtRAMPostWritePostEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data) noexcept;
    };



    // NSCSCC2023 MMU Pre Read Pre Event
    class NSCSCC2023MMUPreReadPreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreReadPreEventBase
        , public Event<NSCSCC2023MMUPreReadPreEvent>
        , public CancellableEvent {
    public:
        NSCSCC2023MMUPreReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t&             address, 
            LA32MOPWidth&       width) noexcept;
    };

    // NSCSCC2023 MMU Pre Read Post Event
    class NSCSCC2023MMUPreReadPostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreReadPostEventBase
        , public Event<NSCSCC2023MMUPreReadPostEvent> {
    public:
        NSCSCC2023MMUPreReadPostEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width) noexcept;
    };

    // NSCSCC2023 MMU Post Read Pre Event
    class NSCSCC2023MMUPostReadPreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPreEventBase
        , public Event<NSCSCC2023MMUPostReadPreEvent>
        , public CancellableEvent {
    public:
        NSCSCC2023MMUPostReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t&          data) noexcept;
    };

    // NSCSCC2023 MMU Post Read Post Event
    class NSCSCC2023MMUPostReadPostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPostEventBase
        , public Event<NSCSCC2023MMUPostReadPostEvent> {
    public:
        NSCSCC2023MMUPostReadPostEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data) noexcept;
    };


    // NSCSCC2023 MMU Pre Write Pre Event
    class NSCSCC2023MMUPreWritePreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreWritePreEventBase
        , public Event<NSCSCC2023MMUPreWritePreEvent>
        , public CancellableEvent {
    public:
        NSCSCC2023MMUPreWritePreEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t&             address, 
            LA32MOPWidth&       width, 
            memdata_t&          data) noexcept;
    };

    // NSCSCC2023 MMU Pre Write Post Event
    class NSCSCC2023MMUPreWritePostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreWritePostEventBase
        , public Event<NSCSCC2023MMUPreWritePostEvent> {
    public:
        NSCSCC2023MMUPreWritePostEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data) noexcept;
    };

    // NSCSCC2023 MMU Post Write Pre Event
    class NSCSCC2023MMUPostWritePreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostWriteEventBase
        , public Event<NSCSCC2023MMUPostWritePreEvent>
        , public CancellableEvent {
    public:
        NSCSCC2023MMUPostWritePreEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data) noexcept;
    };

    // NSCSCC2023 MMU Post Write Post Event
    class NSCSCC2023MMUPostWritePostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostWriteEventBase
        , public Event<NSCSCC2023MMUPostWritePostEvent> {
    public:
        NSCSCC2023MMUPostWritePostEvent(
            NSCSCC2023MMU*      mmu, 
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data) noexcept;
    };

}


#endif
