#include "ds232_event.hpp"


// Implementation of: class DS232EventBase
namespace BullsEye::Draconids3014 {
    /*
    DS232*  core;
    */

    DS232EventBase::DS232EventBase(DS232* core) noexcept
        : core  (core)
    { }

    DS232* DS232EventBase::GetCore() noexcept
    {
        return core;
    }

    const DS232* DS232EventBase::GetCore() const noexcept
    {
        return core;
    }
}


// Implementation of: class DS232MultiPortedEventBase
namespace BullsEye::Draconids3014 {
    /*
    unsigned int    port_id;
    */

    DS232MultiPortedEventBase::DS232MultiPortedEventBase(unsigned int port_id) noexcept
        : port_id   (port_id)
    { }

    unsigned int DS232MultiPortedEventBase::GetPortID() const noexcept
    {
        return port_id;
    }
}


// Implementation of: class DS232FIDEventBase
namespace BullsEye::Draconids3014 {
    /*
    fid_t   fid;
    */

    DS232FIDEventBase::DS232FIDEventBase(fid_t fid) noexcept
        : fid   (fid)
    { }

    fid_t DS232FIDEventBase::GetFID() const noexcept
    {
        return fid;
    }
}


// Implementation of: class DS232FIDTrackEventBase
namespace BullsEye::Draconids3014 {
    /*
    FetchIDTrack    fid_track;
    */

    DS232FIDTrackEventBase::DS232FIDTrackEventBase(const FetchIDTrack& fid_track) noexcept
        : fid_track (fid_track)
    { }

    const FetchIDTrack& DS232FIDTrackEventBase::GetFIDTrack() const noexcept
    {
        return fid_track;
    }
}



// Implementation of: class DS232GPRCommitEventBase
namespace BullsEye::Draconids3014 {
    /*
    unsigned int    gpr_index;
    arch32_t        gpr_value;
    */

    DS232GPRCommitEventBase::DS232GPRCommitEventBase(unsigned int gpr_index, arch32_t gpr_value) noexcept
        : gpr_index (gpr_index)
        , gpr_value (gpr_value)
    { }

    unsigned int DS232GPRCommitEventBase::GetGPRIndex() const noexcept
    {
        return gpr_index;
    }

    arch32_t DS232GPRCommitEventBase::GetGPRValue() const noexcept
    {
        return gpr_value;
    }
}



// Implementation of: class DS232PreEvalEvent
namespace BullsEye::Draconids3014 {

    DS232PreEvalEvent::DS232PreEvalEvent(DS232* core) noexcept
        : DS232EventBase            (core)
    { }
}


// Implementation of: class DS232PostEvalEvent
namespace BullsEye::Draconids3014 {

    DS232PostEvalEvent::DS232PostEvalEvent(DS232* core) noexcept
        : DS232EventBase            (core)
    { }
}



// Implementation of: class DS232PreDispatchEvent
namespace BullsEye::Draconids3014 {

    DS232PreDispatchEvent::DS232PreDispatchEvent(DS232* core, unsigned int port_id, const FetchIDTrack& fid_track) noexcept
        : DS232EventBase            (core)
        , DS232MultiPortedEventBase (port_id)
        , DS232FIDTrackEventBase    (fid_track)
    { }
}


// Implementation of: class DS232MainCommitEvent
namespace BullsEye::Draconids3014 {

    DS232MainCommitEvent::DS232MainCommitEvent(DS232* core, unsigned int port_id, fid_t fid, unsigned int gpr_index, arch32_t gpr_value) noexcept
        : DS232EventBase            (core)
        , DS232MultiPortedEventBase (port_id)
        , DS232FIDEventBase         (fid)
        , DS232GPRCommitEventBase   (gpr_index, gpr_value)
    { }
}


// Implementation of: class DS232ROBCommitEvent
namespace BullsEye::Draconids3014 {
    /*
    bool            store;
    bool            uload;
    addr_t          uload_addr;
    uop40::cmd_t    uload_cmd;
    */
    
    DS232ROBCommitEvent::DS232ROBCommitEvent(DS232* core, unsigned int port_id, fid_t fid, unsigned int gpr_index, arch32_t gpr_value, bool store, bool uload, addr_t uload_addr, uop40::cmd_t uload_cmd) noexcept
        : DS232EventBase            (core)
        , DS232MultiPortedEventBase (port_id)
        , DS232FIDEventBase         (fid)
        , DS232GPRCommitEventBase   (gpr_index, gpr_value)
        , store                     (store)
        , uload                     (uload)
        , uload_addr                (uload_addr)
        , uload_cmd                 (uload_cmd)
    { }

    bool DS232ROBCommitEvent::IsStore() const noexcept
    {
        return store;
    }

    bool DS232ROBCommitEvent::IsUncachedLoad() const noexcept
    {
        return uload;
    }

    addr_t DS232ROBCommitEvent::GetUncachedLoadAddress() const noexcept
    {
        return uload_addr;
    }

    uop40::cmd_t DS232ROBCommitEvent::GetUncachedLoadCommand() const noexcept
    {
        return uload_cmd;
    }
}


// Implementation of: class DS232StoreCommitEvent
namespace BullsEye::Draconids3014 {
    /*
    lswidth_t       width;
    lsstrb_t        strb;
    addr_t          addr;
    uint32_t        data;
    bool            uncached;
    */

    DS232StoreCommitEvent::DS232StoreCommitEvent(DS232*        core, 
                                                 unsigned int  port_id,
                                                 lswidth_t     width, 
                                                 lsstrb_t      strb, 
                                                 addr_t        addr, 
                                                 uint32_t      data, 
                                                 bool          uncached) noexcept
        : DS232EventBase            (core)
        , DS232MultiPortedEventBase (port_id)
        , width                     (width)
        , strb                      (strb)
        , addr                      (addr)
        , data                      (data)
        , uncached                  (uncached)
    { }

    lswidth_t DS232StoreCommitEvent::GetWidth() const noexcept
    {
        return width;
    }

    lsstrb_t DS232StoreCommitEvent::GetStrobe() const noexcept
    {
        return strb;
    }

    addr_t DS232StoreCommitEvent::GetAddress() const noexcept
    {
        return addr;
    }

    uint32_t DS232StoreCommitEvent::GetData() const noexcept
    {
        return data;
    }

    bool DS232StoreCommitEvent::IsUncached() const noexcept
    {
        return uncached;
    }
}
