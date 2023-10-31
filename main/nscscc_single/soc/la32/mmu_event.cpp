#include "mmu_event.hpp"
//
//


// Implementation of: class NSCSCC2023MMUEventBase
namespace BullsEye::NSCSCCSingle {
    /*
    NSCSCC2023MMU*  mmu;
    */

    NSCSCC2023MMUEventBase::NSCSCC2023MMUEventBase(NSCSCC2023MMU* mmu) noexcept
        : mmu   (mmu)
    { }

    NSCSCC2023MMU* NSCSCC2023MMUEventBase::GetMMU() noexcept
    {
        return mmu;
    }

    const NSCSCC2023MMU* NSCSCC2023MMUEventBase::GetMMU() const noexcept
    {
        return mmu;
    }
}


// Implementation of: class NSCSCC2023MMUPreReadPreEventBase
namespace BullsEye::NSCSCCSingle {
    /*
    LA32MOPPath     path;
    addr_t&         address;
    LA32MOPWidth&   width;

    bool            proxy;
    proxy_type      proxy_routine;
    */

    NSCSCC2023MMUPreReadPreEventBase::NSCSCC2023MMUPreReadPreEventBase(
        LA32MOPPath     path,
        addr_t&         address, 
        LA32MOPWidth&   width) noexcept
        : path          (path)
        , address       (address)
        , width         (width)
        , proxy         (false)
        , proxy_routine ()
    { }

    LA32MOPPath NSCSCC2023MMUPreReadPreEventBase::GetPath() const noexcept
    {
        return path;
    }

    addr_t NSCSCC2023MMUPreReadPreEventBase::GetAddress() const noexcept
    {
        return address;
    }

    void NSCSCC2023MMUPreReadPreEventBase::SetAddress(addr_t address) noexcept
    {
        this->address = address;
    }

    LA32MOPWidth NSCSCC2023MMUPreReadPreEventBase::GetWidth() const noexcept
    {
        return width;
    }

    void NSCSCC2023MMUPreReadPreEventBase::SetWidth(LA32MOPWidth width) noexcept
    {
        this->width = width;
    }

    bool NSCSCC2023MMUPreReadPreEventBase::HasProxy() const noexcept
    {
        return proxy;
    }

    void NSCSCC2023MMUPreReadPreEventBase::SetProxy(bool proxy) noexcept
    {
        this->proxy = proxy;
    }

    NSCSCC2023MMUPreReadPreEventBase::proxy_type NSCSCC2023MMUPreReadPreEventBase::GetProxyRoutine() const noexcept
    {
        return proxy_routine;
    }

    void NSCSCC2023MMUPreReadPreEventBase::SetProxyRoutine(proxy_type proxy_routine) noexcept
    {
        this->proxy_routine = proxy_routine;
    }

    void NSCSCC2023MMUPreReadPreEventBase::SetProxy(bool proxy, proxy_type proxy_routine) noexcept
    {
        this->proxy         = proxy;
        this->proxy_routine = proxy_routine;
    }
}

// Implementation of: class NSCSCC2023MMUPreReadPostEventBase
namespace BullsEye::NSCSCCSingle {
    /*
    LA32MOPPath     path;
    addr_t          address;
    LA32MOPWidth    width;

    bool            proxy;
    */

    NSCSCC2023MMUPreReadPostEventBase::NSCSCC2023MMUPreReadPostEventBase(
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width,
        bool            proxy) noexcept
        : path          (path)
        , address       (address)
        , width         (width)
        , proxy         (proxy)
    { }

    LA32MOPPath NSCSCC2023MMUPreReadPostEventBase::GetPath() const noexcept
    {
        return path;
    }

    addr_t NSCSCC2023MMUPreReadPostEventBase::GetAddress() const noexcept
    {
        return address;
    }

    LA32MOPWidth NSCSCC2023MMUPreReadPostEventBase::GetWidth() const noexcept
    {
        return width;
    }

    bool NSCSCC2023MMUPreReadPostEventBase::HasProxy() const noexcept
    {
        return proxy;
    }
}

// Implementation of: class NSCSCC2023MMUPostReadPreEventBase
namespace BullsEye::NSCSCCSingle {
    /*
    LA32MOPPath     path;
    addr_t          address;
    LA32MOPWidth    width;
    memdata_t&      data;
    */

    NSCSCC2023MMUPostReadPreEventBase::NSCSCC2023MMUPostReadPreEventBase(
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t&      data) noexcept
        : path          (path)
        , address       (address)
        , width         (width)
        , data          (data)
    { }

    LA32MOPPath NSCSCC2023MMUPostReadPreEventBase::GetPath() const noexcept
    {
        return path;
    }

    addr_t NSCSCC2023MMUPostReadPreEventBase::GetAddress() const noexcept
    {
        return address;
    }

    LA32MOPWidth NSCSCC2023MMUPostReadPreEventBase::GetWidth() const noexcept
    {
        return width;
    }

    memdata_t NSCSCC2023MMUPostReadPreEventBase::GetData() const noexcept
    {
        return data;
    }

    void NSCSCC2023MMUPostReadPreEventBase::SetData(memdata_t data) noexcept
    {
        this->data = data;
    }
}

// Implementation of: class NSCSCC2023MMUPostReadPostEventBase
namespace BullsEye::NSCSCCSingle {
    /*
    LA32MOPPath     path;
    addr_t          address;
    LA32MOPWidth    width;
    memdata_t       data;
    */

    NSCSCC2023MMUPostReadPostEventBase::NSCSCC2023MMUPostReadPostEventBase(
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data) noexcept
        : path          (path)
        , address       (address)
        , width         (width)
        , data          (data)
    { }

    LA32MOPPath NSCSCC2023MMUPostReadPostEventBase::GetPath() const noexcept
    {
        return path;
    }

    addr_t NSCSCC2023MMUPostReadPostEventBase::GetAddress() const noexcept
    {
        return address;
    }

    LA32MOPWidth NSCSCC2023MMUPostReadPostEventBase::GetWidth() const noexcept
    {
        return width;
    }

    memdata_t NSCSCC2023MMUPostReadPostEventBase::GetData() const noexcept
    {
        return data;
    }
}


// Implementation of: class NSCSCC2023MMUPreWritePreEventBase
namespace BullsEye::NSCSCCSingle {
    /*
    LA32MOPPath     path;
    addr_t&         address;
    LA32MOPWidth&   width;
    memdata_t&      data;

    bool            proxy;
    proxy_type      proxy_routine;
    */

    NSCSCC2023MMUPreWritePreEventBase::NSCSCC2023MMUPreWritePreEventBase(
        LA32MOPPath     path,
        addr_t&         address, 
        LA32MOPWidth&   width, 
        memdata_t&      data) noexcept
        : path          (path)
        , address       (address)
        , width         (width)
        , data          (data)
        , proxy         (false)
        , proxy_routine ()
    { }

    LA32MOPPath NSCSCC2023MMUPreWritePreEventBase::GetPath() const noexcept
    {
        return path;
    }

    void NSCSCC2023MMUPreWritePreEventBase::SetPath(LA32MOPPath path) noexcept
    {
        this->path = path;
    }

    addr_t NSCSCC2023MMUPreWritePreEventBase::GetAddress() const noexcept
    {
        return address;
    }

    void NSCSCC2023MMUPreWritePreEventBase::SetAddress(addr_t address) noexcept
    {
        this->address = address;
    }

    LA32MOPWidth NSCSCC2023MMUPreWritePreEventBase::GetWidth() const noexcept
    {
        return width;
    }

    void NSCSCC2023MMUPreWritePreEventBase::SetWidth(LA32MOPWidth width) noexcept
    {
        this->width = width;
    }

    memdata_t NSCSCC2023MMUPreWritePreEventBase::GetData() const noexcept
    {
        return data;
    }

    void NSCSCC2023MMUPreWritePreEventBase::SetData(memdata_t data) noexcept
    {
        this->data = data;
    }

    bool NSCSCC2023MMUPreWritePreEventBase::HasProxy() const noexcept
    {
        return proxy;
    }

    void NSCSCC2023MMUPreWritePreEventBase::SetProxy(bool proxy) noexcept
    {
        this->proxy = proxy;
    }

    NSCSCC2023MMUPreWritePreEventBase::proxy_type NSCSCC2023MMUPreWritePreEventBase::GetProxyRoutine() const noexcept
    {
        return proxy_routine;
    }

    void NSCSCC2023MMUPreWritePreEventBase::SetProxyRoutine(proxy_type proxy_routine) noexcept
    {
        this->proxy_routine = proxy_routine;
    }

    void NSCSCC2023MMUPreWritePreEventBase::SetProxy(bool proxy, proxy_type proxy_routine) noexcept
    {
        this->proxy         = proxy;
        this->proxy_routine = proxy_routine;
    }
}

// Implementation of: class NSCSCC2023MMUPreWritePostEventBase
namespace BullsEye::NSCSCCSingle {
    /*
    LA32MOPPath     path;
    addr_t          address;
    LA32MOPWidth    width;
    memdata_t       data;

    bool            proxy;
    */

    NSCSCC2023MMUPreWritePostEventBase::NSCSCC2023MMUPreWritePostEventBase(
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data,
        bool            proxy) noexcept
        : path          (path)
        , address       (address)
        , width         (width)
        , data          (data)
        , proxy         (proxy)
    { }

    LA32MOPPath NSCSCC2023MMUPreWritePostEventBase::GetPath() const noexcept
    {
        return path;
    }

    addr_t NSCSCC2023MMUPreWritePostEventBase::GetAddress() const noexcept
    {
        return address;
    }

    LA32MOPWidth NSCSCC2023MMUPreWritePostEventBase::GetWidth() const noexcept
    {
        return width;
    }

    memdata_t NSCSCC2023MMUPreWritePostEventBase::GetData() const noexcept
    {
        return data;
    }

    bool NSCSCC2023MMUPreWritePostEventBase::HasProxy() const noexcept
    {
        return proxy;
    }
}

// Implementation of: class NSCSCC2023MMUPostWriteEventBase
namespace BullsEye::NSCSCCSingle {
    /*
    LA32MOPPath     path;
    addr_t          address;
    LA32MOPWidth    width;
    memdata_t       data;
    */

    NSCSCC2023MMUPostWriteEventBase::NSCSCC2023MMUPostWriteEventBase(
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data) noexcept
        : path          (path)
        , address       (address)
        , width         (width)
        , data          (data)
    { }

    LA32MOPPath NSCSCC2023MMUPostWriteEventBase::GetPath() const noexcept
    {
        return path;
    }

    addr_t NSCSCC2023MMUPostWriteEventBase::GetAddress() const noexcept
    {
        return address;
    }

    LA32MOPWidth NSCSCC2023MMUPostWriteEventBase::GetWidth() const noexcept
    {
        return width;
    }

    memdata_t NSCSCC2023MMUPostWriteEventBase::GetData() const noexcept
    {
        return data;
    }
}



// Implementation of: class NSCSCC2023MMUSerialPreReadPreEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUSerialPreReadPreEvent::NSCSCC2023MMUSerialPreReadPreEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t&         address, 
        LA32MOPWidth&   width) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPreReadPreEventBase  (path, address, width)
    { }
}

// Implementation of: class NSCSCC2023MMUSerialPreReadPostEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUSerialPreReadPostEvent::NSCSCC2023MMUSerialPreReadPostEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width,
        bool            proxy) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPreReadPostEventBase (path, address, width, proxy)
    { }
}

// Implementation of: class NSCSCC2023MMUSerialPostReadPreEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUSerialPostReadPreEvent::NSCSCC2023MMUSerialPostReadPreEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t&      data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPostReadPreEventBase (path, address, width, data)
    { }
}

// Implementation of: class NSCSCC2023MMUSerialPostReadPostEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUSerialPostReadPostEvent::NSCSCC2023MMUSerialPostReadPostEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPostReadPostEventBase(path, address, width, data)
    { }
}


// Implementation of: class NSCSCC2023MMUSerialPreWritePreEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUSerialPreWritePreEvent::NSCSCC2023MMUSerialPreWritePreEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t&         address, 
        LA32MOPWidth&   width, 
        memdata_t&      data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPreWritePreEventBase (path, address, width, data)
    { }
}

// Implementation of: class NSCSCC2023MMUSerialPreWritePostEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUSerialPreWritePostEvent::NSCSCC2023MMUSerialPreWritePostEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data,
        bool            proxy) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPreWritePostEventBase(path, address, width, data, proxy)
    { }
}

// Implementation of: class NSCSCC2023MMUSerialPostWritePreEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUSerialPostWritePreEvent::NSCSCC2023MMUSerialPostWritePreEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPostWriteEventBase   (path, address, width, data)
    { }
}

// Implementation of: class NSCSCC2023MMUSerialPostWritePostEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUSerialPostWritePostEvent::NSCSCC2023MMUSerialPostWritePostEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPostWriteEventBase   (path, address, width, data)
    { }
}



// Implementation of: class NSCSCC2023MMUBaseRAMPreReadPreEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUBaseRAMPreReadPreEvent::NSCSCC2023MMUBaseRAMPreReadPreEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t&         address, 
        LA32MOPWidth&   width) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPreReadPreEventBase  (path, address, width)
    { }
}

// Implementation of: class NSCSCC2023MMUBaseRAMPreReadPostEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUBaseRAMPreReadPostEvent::NSCSCC2023MMUBaseRAMPreReadPostEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width,
        bool            proxy) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPreReadPostEventBase (path, address, width, proxy)
    { }
}

// Implementation of: class NSCSCC2023MMUBaseRAMPostReadPreEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUBaseRAMPostReadPreEvent::NSCSCC2023MMUBaseRAMPostReadPreEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t&      data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPostReadPreEventBase (path, address, width, data)
    { }
}

// Implementation of: class NSCSCC2023MMUBaseRAMPostReadPostEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUBaseRAMPostReadPostEvent::NSCSCC2023MMUBaseRAMPostReadPostEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPostReadPostEventBase(path, address, width, data)
    { }
}


// Implementation of: class NSCSCC2023MMUBaseRAMPreWritePreEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUBaseRAMPreWritePreEvent::NSCSCC2023MMUBaseRAMPreWritePreEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t&         address, 
        LA32MOPWidth&   width, 
        memdata_t&      data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPreWritePreEventBase (path, address, width, data)
    { }
}

// Implementation of: class NSCSCC2023MMUBaseRAMPreWritePostEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUBaseRAMPreWritePostEvent::NSCSCC2023MMUBaseRAMPreWritePostEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data,
        bool            proxy) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPreWritePostEventBase(path, address, width, data, proxy)
    { }
}

// Implementation of: class NSCSCC2023MMUBaseRAMPostWritePreEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUBaseRAMPostWritePreEvent::NSCSCC2023MMUBaseRAMPostWritePreEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPostWriteEventBase   (path, address, width, data)
    { }
}

// Implementation of: class NSCSCC2023MMUBaseRAMPostWritePostEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUBaseRAMPostWritePostEvent::NSCSCC2023MMUBaseRAMPostWritePostEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPostWriteEventBase   (path, address, width, data)
    { }
}



// Implementation of: class NSCSCC2023MMUExtRAMPreReadPreEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUExtRAMPreReadPreEvent::NSCSCC2023MMUExtRAMPreReadPreEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t&         address, 
        LA32MOPWidth&   width) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPreReadPreEventBase  (path, address, width)
    { }
}

// Implementation of: class NSCSCC2023MMUExtRAMPreReadPostEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUExtRAMPreReadPostEvent::NSCSCC2023MMUExtRAMPreReadPostEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width,
        bool            proxy) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPreReadPostEventBase (path, address, width, proxy)
    { }
}

// Implementation of: class NSCSCC2023MMUExtRAMPostReadPreEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUExtRAMPostReadPreEvent::NSCSCC2023MMUExtRAMPostReadPreEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t&      data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPostReadPreEventBase (path, address, width, data)
    { }
}

// Implementation of: class NSCSCC2023MMUExtRAMPostReadPostEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUExtRAMPostReadPostEvent::NSCSCC2023MMUExtRAMPostReadPostEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPostReadPostEventBase(path, address, width, data)
    { }
}


// Implementation of: class NSCSCC2023MMUExtRAMPreWritePreEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUExtRAMPreWritePreEvent::NSCSCC2023MMUExtRAMPreWritePreEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t&         address, 
        LA32MOPWidth&   width, 
        memdata_t&      data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPreWritePreEventBase (path, address, width, data)
    { }
}

// Implementation of: class NSCSCC2023MMUExtRAMPreWritePostEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUExtRAMPreWritePostEvent::NSCSCC2023MMUExtRAMPreWritePostEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data,
        bool            proxy) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPreWritePostEventBase(path, address, width, data, proxy)
    { }
}

// Implementation of: class NSCSCC2023MMUExtRAMPostWritePreEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUExtRAMPostWritePreEvent::NSCSCC2023MMUExtRAMPostWritePreEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPostWriteEventBase   (path, address, width, data)
    { }
}

// Implementation of: class NSCSCC2023MMUExtRAMPostWritePostEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUExtRAMPostWritePostEvent::NSCSCC2023MMUExtRAMPostWritePostEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPostWriteEventBase   (path, address, width, data)
    { }
}



// Implementation of: class NSCSCC2023MMUPreReadPreEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUPreReadPreEvent::NSCSCC2023MMUPreReadPreEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t&         address, 
        LA32MOPWidth&   width) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPreReadPreEventBase  (path, address, width)
    { }
}

// Implementation of: class NSCSCC2023MMUPreReadPostEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUPreReadPostEvent::NSCSCC2023MMUPreReadPostEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width,
        bool            proxy) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPreReadPostEventBase (path, address, width, proxy)
    { }
}

// Implementation of: class NSCSCC2023MMUPostReadPreEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUPostReadPreEvent::NSCSCC2023MMUPostReadPreEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path, 
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t&      data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPostReadPreEventBase (path, address, width, data)
    { }
}

// Implementation of: class NSCSCC2023MMUPostReadPostEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUPostReadPostEvent::NSCSCC2023MMUPostReadPostEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path, 
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPostReadPostEventBase(path, address, width, data)
    { }
}


// Implementation of: class NSCSCC2023MMUPreWritePreEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUPreWritePreEvent::NSCSCC2023MMUPreWritePreEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t&         address, 
        LA32MOPWidth&   width, 
        memdata_t&      data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPreWritePreEventBase (path, address, width, data)
    { }
}

// Implementation of: class NSCSCC2023MMUPreWritePostEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUPreWritePostEvent::NSCSCC2023MMUPreWritePostEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data,
        bool            proxy) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPreWritePostEventBase(path, address, width, data, proxy)
    { }
}

// Implementation of: class NSCSCC2023MMUPostWritePreEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUPostWritePreEvent::NSCSCC2023MMUPostWritePreEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPostWriteEventBase   (path, address, width, data)
    { }
}

// Implementation of: class NSCSCC2023MMUPostWritePostEvent
namespace BullsEye::NSCSCCSingle {

    NSCSCC2023MMUPostWritePostEvent::NSCSCC2023MMUPostWritePostEvent(
        NSCSCC2023MMU*  mmu, 
        LA32MOPPath     path,
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data) noexcept
        : NSCSCC2023MMUEventBase            (mmu)
        , NSCSCC2023MMUPostWriteEventBase   (path, address, width, data)
    { }
}
