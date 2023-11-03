#pragma once

#ifndef __HEADER_DS232__CORE_EVENT
#define __HEADER_DS232__CORE_EVENT


#include "autoinclude.h"

#include AUTOINC_BE_COMMON(eventbus.hpp)


#include "ds232_fetch.hpp"
#include "ds232_verilated.hpp"


namespace BullsEye::Draconids3014 {

    // DS232 Event Base
    class DS232EventBase {
    private:
        DS232*  core;

    public:
        DS232EventBase(DS232* core) noexcept;

        DS232*              GetCore() noexcept;
        const DS232*        GetCore() const noexcept;
    };

    // DS232 Multi Ported Event Base
    class DS232MultiPortedEventBase {
    private:
        unsigned int    port_id;

    public:
        DS232MultiPortedEventBase(unsigned int port_id) noexcept;

        unsigned int        GetPortID() const noexcept;
    };

    // DS232 FID Event Base
    class DS232FIDEventBase {
    private:
        fid_t   fid;

    public:
        DS232FIDEventBase(fid_t fid) noexcept;

        fid_t               GetFID() const noexcept;
    };

    // DS232 FID Track Event Base
    class DS232FIDTrackEventBase {
    private:
        FetchIDTrack    fid_track;

    public:
        DS232FIDTrackEventBase(const FetchIDTrack& fid_track) noexcept;

        const FetchIDTrack& GetFIDTrack() const noexcept;
    };

    
    // DS232 GPR Commit Event Base
    class DS232GPRCommitEventBase {
    private:
        unsigned int    gpr_index;
        arch32_t        gpr_value;

    public:
        DS232GPRCommitEventBase(unsigned int gpr_index, arch32_t gpr_value) noexcept;

        unsigned int        GetGPRIndex() const noexcept;
        arch32_t            GetGPRValue() const noexcept;
    };



    // DS232 Pre-Eval Event
    class DS232PreEvalEvent 
        : public DS232EventBase 
        , public Event<DS232PreEvalEvent> {
    public: 
        DS232PreEvalEvent(DS232* core) noexcept;
    };

    // DS232 Post-Eval Event
    class DS232PostEvalEvent 
        : public DS232EventBase 
        , public Event<DS232PostEvalEvent> {
    public:
        DS232PostEvalEvent(DS232* core) noexcept;
    };



    // DS232 Pre-Dispatch Event
    class DS232PreDispatchEvent
        : public DS232EventBase
        , public DS232MultiPortedEventBase
        , public DS232FIDTrackEventBase
        , public Event<DS232PreDispatchEvent> {
    public:
        DS232PreDispatchEvent(DS232* core, unsigned int port_id, const FetchIDTrack& fid_track) noexcept;
    };


    // DS232 Main Commit Event
    class DS232MainCommitEvent
        : public DS232EventBase
        , public DS232MultiPortedEventBase
        , public DS232FIDEventBase
        , public DS232GPRCommitEventBase
        , public Event<DS232MainCommitEvent> {
    public:
        DS232MainCommitEvent(DS232*         core, 
                             unsigned int   port_id,
                             fid_t          fid, 
                             unsigned int   gpr_index, 
                             arch32_t       gpr_value) noexcept;
    };


    // DS232 ROB Commit Event
    class DS232ROBCommitEvent 
        : public DS232EventBase 
        , public DS232MultiPortedEventBase
        , public DS232FIDEventBase
        , public DS232GPRCommitEventBase
        , public Event<DS232ROBCommitEvent> {
    private:
        bool            store;
        bool            uload;
        addr_t          uload_addr;
        uop40::cmd_t    uload_cmd;

    public:
        DS232ROBCommitEvent(DS232*          core, 
                            unsigned int    port_id,
                            fid_t           fid, 
                            unsigned int    gpr_index, 
                            arch32_t        gpr_value, 
                            bool            store, 
                            bool            uload, 
                            addr_t          uload_addr, 
                            uop40::cmd_t    uload_cmd) noexcept;

        bool            IsStore() const noexcept;

        bool            IsUncachedLoad() const noexcept;
        addr_t          GetUncachedLoadAddress() const noexcept;
        uop40::cmd_t    GetUncachedLoadCommand() const noexcept;
    };


    // DS232 Store Commit Event
    class DS232StoreCommitEvent
        : public DS232EventBase
        , public DS232MultiPortedEventBase
        , public Event<DS232StoreCommitEvent> {
    private:
        lswidth_t       width;
        lsstrb_t        strb;
        addr_t          addr;
        uint32_t        data;
        bool            uncached;

    public:
        DS232StoreCommitEvent(DS232*        core, 
                              unsigned int  port_id,
                              lswidth_t     width, 
                              lsstrb_t      strb, 
                              addr_t        addr, 
                              uint32_t      data, 
                              bool          uncached) noexcept;

        lswidth_t       GetWidth() const noexcept;
        lsstrb_t        GetStrobe() const noexcept;
        addr_t          GetAddress() const noexcept;
        uint32_t        GetData() const noexcept;
        bool            IsUncached() const noexcept;
    };
}

#endif
