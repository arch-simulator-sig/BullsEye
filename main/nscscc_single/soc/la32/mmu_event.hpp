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
        using proxy_type = std::function<LA32MOPOutcome(LA32MOPPath, addr_t, LA32MOPWidth, memdata_t*)>;
        
    private:
        LA32MOPPath     path;
        addr_t&         address;
        LA32MOPWidth&   width;

        bool            proxy;
        proxy_type      proxy_routine;

    public:
        NSCSCC2023MMUPreReadPreEventBase(LA32MOPPath path, addr_t& address, LA32MOPWidth& width) noexcept;

        LA32MOPPath     GetPath() const noexcept;

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
        LA32MOPPath     path;
        addr_t          address;
        LA32MOPWidth    width;

        bool            proxy;

    public:
        NSCSCC2023MMUPreReadPostEventBase(LA32MOPPath path, addr_t address, LA32MOPWidth width, bool proxy) noexcept;

        LA32MOPPath     GetPath() const noexcept;
        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;

        bool            HasProxy() const noexcept;
    };

    // NSCSCC 2023 MMU Post Read Pre Event Base
    class NSCSCC2023MMUPostReadPreEventBase {
    private:
        LA32MOPPath     path;
        addr_t          address;
        LA32MOPWidth    width;
        memdata_t&      data;
        LA32MOPOutcome& outcome;

    public:
        NSCSCC2023MMUPostReadPreEventBase(LA32MOPPath path, addr_t address, LA32MOPWidth width, memdata_t& data, LA32MOPOutcome& outcome) noexcept;

        LA32MOPPath     GetPath() const noexcept;
        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;

        memdata_t       GetData() const noexcept;
        void            SetData(memdata_t data) noexcept;

        LA32MOPOutcome  GetOutcome() const noexcept;
        void            SetOutcome(LA32MOPOutcome outcome) noexcept;
    };

    // NSCSCC 2023 MMU Post Read Post Event Base
    class NSCSCC2023MMUPostReadPostEventBase {
    private:
        LA32MOPPath     path;
        addr_t          address;
        LA32MOPWidth    width;
        memdata_t       data;
        LA32MOPOutcome  outcome;

    public:
        NSCSCC2023MMUPostReadPostEventBase(LA32MOPPath path, addr_t address, LA32MOPWidth width, memdata_t data, LA32MOPOutcome outcome) noexcept;

        LA32MOPPath     GetPath() const noexcept;
        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;

        memdata_t       GetData() const noexcept;
        LA32MOPOutcome  GetOutcome() const noexcept;
    };


    // NSCSCC 2023 MMU Pre Write Pre Event Base
    class NSCSCC2023MMUPreWritePreEventBase {
    public:
        using proxy_type = std::function<LA32MOPOutcome(LA32MOPPath, addr_t, LA32MOPWidth, memdata_t)>;

    private:
        LA32MOPPath     path;
        addr_t&         address;
        LA32MOPWidth&   width;
        memdata_t&      data;

        bool            proxy;
        proxy_type      proxy_routine;

    public:
        NSCSCC2023MMUPreWritePreEventBase(LA32MOPPath path, addr_t& address, LA32MOPWidth& width, memdata_t& data) noexcept;

        LA32MOPPath     GetPath() const noexcept;
        void            SetPath(LA32MOPPath path) noexcept;

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
        LA32MOPPath     path;
        addr_t          address;
        LA32MOPWidth    width;
        memdata_t       data;

        bool            proxy;

    public:
        NSCSCC2023MMUPreWritePostEventBase(LA32MOPPath path, addr_t address, LA32MOPWidth width, memdata_t data, bool proxy) noexcept;

        LA32MOPPath     GetPath() const noexcept;
        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;
        memdata_t       GetData() const noexcept;

        bool            HasProxy() const noexcept;
    };


    // NSCSCC 2023 MMU Post Write Pre Event Base
    class NSCSCC2023MMUPostWritePreEventBase {
    private:
        LA32MOPPath     path;
        addr_t          address;
        LA32MOPWidth    width;
        memdata_t       data;
        LA32MOPOutcome& outcome;
    public:
        NSCSCC2023MMUPostWritePreEventBase(LA32MOPPath path, addr_t address, LA32MOPWidth width, memdata_t data, LA32MOPOutcome& outcome) noexcept;

        LA32MOPPath     GetPath() const noexcept;
        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;
        memdata_t       GetData() const noexcept;

        LA32MOPOutcome  GetOutcome() const noexcept;
        void            SetOutcome(LA32MOPOutcome outcome) noexcept;
    };

    // NSCSCC 2023 MMU Post Write Post Event Base
    class NSCSCC2023MMUPostWritePostEventBase {
    private:
        LA32MOPPath     path;
        addr_t          address;
        LA32MOPWidth    width;
        memdata_t       data;
        LA32MOPOutcome  outcome;

    public:
        NSCSCC2023MMUPostWritePostEventBase(LA32MOPPath path, addr_t address, LA32MOPWidth width, memdata_t data, LA32MOPOutcome outcome) noexcept;

        LA32MOPPath     GetPath() const noexcept;
        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;
        memdata_t       GetData() const noexcept;

        LA32MOPOutcome  GetOutcome() const noexcept;
    };



    // NSCSCC2023 MMU MMIO Serial Pre Read Pre Event
    class NSCSCC2023MMUMappedIOSerialPreReadPreEvent 
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreReadPreEventBase
        , public Event<NSCSCC2023MMUMappedIOSerialPreReadPreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUMappedIOSerialPreReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t&             address, 
            LA32MOPWidth&       width) noexcept;
    };

    // NSCSCC2023 MMU MMIO Serial Pre Read Post Event
    class NSCSCC2023MMUMappedIOSerialPreReadPostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreReadPostEventBase
        , public Event<NSCSCC2023MMUMappedIOSerialPreReadPostEvent> {
    public:
        NSCSCC2023MMUMappedIOSerialPreReadPostEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width,
            bool                proxy) noexcept;
    };

    // NSCSCC2023 MMU MMIO Serial Post Read Pre Event
    class NSCSCC2023MMUMappedIOSerialPostReadPreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPreEventBase
        , public Event<NSCSCC2023MMUMappedIOSerialPostReadPreEvent> 
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUMappedIOSerialPostReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t&          data,
            LA32MOPOutcome&     outcome) noexcept;
    };

    // NSCSCC2023 MMU MMIO Serial Post Read Post Event
    class NSCSCC2023MMUMappedIOSerialPostReadPostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPostEventBase
        , public Event<NSCSCC2023MMUMappedIOSerialPostReadPostEvent> {
    public:
        NSCSCC2023MMUMappedIOSerialPostReadPostEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            LA32MOPOutcome      outcome) noexcept;
    };

    
    // NSCSCC2023 MMU MMIO Serial Pre Write Pre Event
    class NSCSCC2023MMUMappedIOSerialPreWritePreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreWritePreEventBase
        , public Event<NSCSCC2023MMUMappedIOSerialPreWritePreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUMappedIOSerialPreWritePreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t&             address, 
            LA32MOPWidth&       width, 
            memdata_t&          data) noexcept;
    };

    // NSCSCC2023 MMU MMIO Serial Pre Write Post Event
    class NSCSCC2023MMUMappedIOSerialPreWritePostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreWritePostEventBase
        , public Event<NSCSCC2023MMUMappedIOSerialPreWritePostEvent> {
    public:
        NSCSCC2023MMUMappedIOSerialPreWritePostEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            bool                proxy) noexcept;
    };

    // NSCSCC2023 MMU MMIO Serial Post Write Pre Event
    class NSCSCC2023MMUMappedIOSerialPostWritePreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostWritePreEventBase
        , public Event<NSCSCC2023MMUMappedIOSerialPostWritePreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUMappedIOSerialPostWritePreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            LA32MOPOutcome&     outcome) noexcept;
    };

    // NSCSCC2023 MMU MMIO Serial Post Write Post Event
    class NSCSCC2023MMUMappedIOSerialPostWritePostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostWritePostEventBase
        , public Event<NSCSCC2023MMUMappedIOSerialPostWritePostEvent> {
    public:
        NSCSCC2023MMUMappedIOSerialPostWritePostEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            LA32MOPOutcome      outcome) noexcept;
    };



    // NSCSCC2023 MMU MMIO ClockCounter Pre Read Pre Event
    class NSCSCC2023MMUMappedIOClockCounterPreReadPreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreReadPreEventBase
        , public Event<NSCSCC2023MMUMappedIOClockCounterPreReadPreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUMappedIOClockCounterPreReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t&             address, 
            LA32MOPWidth&       width) noexcept;
    };

    // NSCSCC2023 MMU MMIO ClockCounter Pre Read Post Event
    class NSCSCC2023MMUMappedIOClockCounterPreReadPostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreReadPostEventBase
        , public Event<NSCSCC2023MMUMappedIOClockCounterPreReadPostEvent> {
    public:
        NSCSCC2023MMUMappedIOClockCounterPreReadPostEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width,
            bool                proxy) noexcept;
    };

    // NSCSCC2023 MMU MMIO ClockCounter Post Read Pre Event
    class NSCSCC2023MMUMappedIOClockCounterPostReadPreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPreEventBase
        , public Event<NSCSCC2023MMUMappedIOClockCounterPostReadPreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUMappedIOClockCounterPostReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t&          data,
            LA32MOPOutcome&     outcome) noexcept;
    };

    // NSCSCC2023 MMU MMIO ClockCounter Post Read Post Event
    class NSCSCC2023MMUMappedIOClockCounterPostReadPostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPostEventBase
        , public Event<NSCSCC2023MMUMappedIOClockCounterPostReadPostEvent> {
    public:
        NSCSCC2023MMUMappedIOClockCounterPostReadPostEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            LA32MOPOutcome      outcome) noexcept;
    };



    // NSCSCC2023 MMU BaseRAM Pre Read Pre Event
    class NSCSCC2023MMUBaseRAMPreReadPreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreReadPreEventBase
        , public Event<NSCSCC2023MMUBaseRAMPreReadPreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUBaseRAMPreReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
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
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width,
            bool                proxy) noexcept;
    };

    // NSCSCC2023 MMU BaseRAM Post Read Pre Event
    class NSCSCC2023MMUBaseRAMPostReadPreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPreEventBase
        , public Event<NSCSCC2023MMUBaseRAMPostReadPreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUBaseRAMPostReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t&          data,
            LA32MOPOutcome&     outcome) noexcept;
    };

    // NSCSCC2023 MMU BaseRAM Post Read Post Event
    class NSCSCC2023MMUBaseRAMPostReadPostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPostEventBase
        , public Event<NSCSCC2023MMUBaseRAMPostReadPostEvent> {
    public:
        NSCSCC2023MMUBaseRAMPostReadPostEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            LA32MOPOutcome      outcome) noexcept;
    };


    // NSCSCC2023 MMU BaseRAM Pre Write Pre Event
    class NSCSCC2023MMUBaseRAMPreWritePreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreWritePreEventBase
        , public Event<NSCSCC2023MMUBaseRAMPreWritePreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUBaseRAMPreWritePreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
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
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            bool                proxy) noexcept;
    };

    // NSCSCC2023 MMU BaseRAM Post Write Pre Event
    class NSCSCC2023MMUBaseRAMPostWritePreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostWritePreEventBase
        , public Event<NSCSCC2023MMUBaseRAMPostWritePreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUBaseRAMPostWritePreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            LA32MOPOutcome&     outcome) noexcept;
    };

    // NSCSCC2023 MMU BaseRAM Post Write Post Event
    class NSCSCC2023MMUBaseRAMPostWritePostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostWritePostEventBase
        , public Event<NSCSCC2023MMUBaseRAMPostWritePostEvent> {
    public:
        NSCSCC2023MMUBaseRAMPostWritePostEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            LA32MOPOutcome      outcome) noexcept;
    };



    // NSCSCC2023 MMU ExtRAM Pre Read Pre Event
    class NSCSCC2023MMUExtRAMPreReadPreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreReadPreEventBase
        , public Event<NSCSCC2023MMUExtRAMPreReadPreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUExtRAMPreReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
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
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width,
            bool                proxy) noexcept;
    };

    // NSCSCC2023 MMU ExtRAM Post Read Pre Event
    class NSCSCC2023MMUExtRAMPostReadPreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPreEventBase
        , public Event<NSCSCC2023MMUExtRAMPostReadPreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUExtRAMPostReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t&          data,
            LA32MOPOutcome&     outcome) noexcept;
    };

    // NSCSCC2023 MMU ExtRAM Post Read Post Event
    class NSCSCC2023MMUExtRAMPostReadPostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPostEventBase
        , public Event<NSCSCC2023MMUExtRAMPostReadPostEvent> {
    public:
        NSCSCC2023MMUExtRAMPostReadPostEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            LA32MOPOutcome      outcome) noexcept;
    };

    
    // NSCSCC2023 MMU ExtRAM Pre Write Pre Event
    class NSCSCC2023MMUExtRAMPreWritePreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreWritePreEventBase
        , public Event<NSCSCC2023MMUExtRAMPreWritePreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUExtRAMPreWritePreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
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
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            bool                proxy) noexcept;
    };

    // NSCSCC2023 MMU ExtRAM Post Write Pre Event
    class NSCSCC2023MMUExtRAMPostWritePreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostWritePreEventBase
        , public Event<NSCSCC2023MMUExtRAMPostWritePreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUExtRAMPostWritePreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            LA32MOPOutcome&     outcome) noexcept;
    };

    // NSCSCC2023 MMU ExtRAM Post Write Post Event
    class NSCSCC2023MMUExtRAMPostWritePostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostWritePostEventBase
        , public Event<NSCSCC2023MMUExtRAMPostWritePostEvent> {
    public:
        NSCSCC2023MMUExtRAMPostWritePostEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            LA32MOPOutcome      outcome) noexcept;
    };



    // NSCSCC2023 MMU Pre Read Pre Event
    class NSCSCC2023MMUPreReadPreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreReadPreEventBase
        , public Event<NSCSCC2023MMUPreReadPreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUPreReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
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
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width,
            bool                proxy) noexcept;
    };

    // NSCSCC2023 MMU Post Read Pre Event
    class NSCSCC2023MMUPostReadPreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPreEventBase
        , public Event<NSCSCC2023MMUPostReadPreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUPostReadPreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t&          data,
            LA32MOPOutcome&     outcome) noexcept;
    };

    // NSCSCC2023 MMU Post Read Post Event
    class NSCSCC2023MMUPostReadPostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostReadPostEventBase
        , public Event<NSCSCC2023MMUPostReadPostEvent> {
    public:
        NSCSCC2023MMUPostReadPostEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            LA32MOPOutcome      outcome) noexcept;
    };


    // NSCSCC2023 MMU Pre Write Pre Event
    class NSCSCC2023MMUPreWritePreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPreWritePreEventBase
        , public Event<NSCSCC2023MMUPreWritePreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUPreWritePreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
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
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            bool                proxy) noexcept;
    };

    // NSCSCC2023 MMU Post Write Pre Event
    class NSCSCC2023MMUPostWritePreEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostWritePreEventBase
        , public Event<NSCSCC2023MMUPostWritePreEvent>
        , public ExceptionableEvent<LA32MOPOutcome> {
    public:
        NSCSCC2023MMUPostWritePreEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            LA32MOPOutcome&     outcome) noexcept;
    };

    // NSCSCC2023 MMU Post Write Post Event
    class NSCSCC2023MMUPostWritePostEvent
        : public NSCSCC2023MMUEventBase
        , public NSCSCC2023MMUPostWritePostEventBase
        , public Event<NSCSCC2023MMUPostWritePostEvent> {
    public:
        NSCSCC2023MMUPostWritePostEvent(
            NSCSCC2023MMU*      mmu, 
            LA32MOPPath         path,
            addr_t              address, 
            LA32MOPWidth        width, 
            memdata_t           data,
            LA32MOPOutcome      outcome) noexcept;
    };

}


#endif
