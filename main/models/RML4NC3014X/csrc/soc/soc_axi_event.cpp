#include "soc_axi_event.hpp"


// Implementation of: class SoCAXIBridgeEventBase
namespace BullsEye::Draconids3014 {
    /*
    SoCAXIBridgel*  soc_axi;
    */

    SoCAXIBridgeEventBase::SoCAXIBridgeEventBase(SoCAXIBridge* soc_axi) noexcept
        : soc_axi   (soc_axi)
    { }

    SoCAXIBridge* SoCAXIBridgeEventBase::GetBridge() noexcept
    {
        return soc_axi;
    }

    const SoCAXIBridge* SoCAXIBridgeEventBase::GetBridge() const noexcept
    {
        return soc_axi;
    }
}


// Implementation of: class SoCAXIBridgeFetchReadAddressChannelM2SPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchReadAddressChannelM2SPreEvent::SoCAXIBridgeFetchReadAddressChannelM2SPreEvent(
        SoCAXIBridge*                           soc_axi, 
        FetchAXI4ReadAddressChannelM2S&         bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeFetchReadAddressChannelM2SPreEventBase    (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeFetchReadAddressChannelM2SPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchReadAddressChannelM2SPostEvent::SoCAXIBridgeFetchReadAddressChannelM2SPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const FetchAXI4ReadAddressChannelM2S&   bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeFetchReadAddressChannelM2SPostEventBase   (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeFetchReadAddressChannelS2MPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchReadAddressChannelS2MPreEvent::SoCAXIBridgeFetchReadAddressChannelS2MPreEvent(
        SoCAXIBridge*                           soc_axi, 
        FetchAXI4ReadAddressChannelS2M&         bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeFetchReadAddressChannelS2MPreEventBase    (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeFetchReadAddressChannelS2MPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchReadAddressChannelS2MPostEvent::SoCAXIBridgeFetchReadAddressChannelS2MPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const FetchAXI4ReadAddressChannelS2M&   bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeFetchReadAddressChannelS2MPostEventBase   (bundle)
    { }
}


// Implementation of: class SoCAXIBridgeFetchReadDataChannelM2SPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchReadDataChannelM2SPreEvent::SoCAXIBridgeFetchReadDataChannelM2SPreEvent(
        SoCAXIBridge*                           soc_axi, 
        FetchAXI4ReadDataChannelM2S&            bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeFetchReadDataChannelM2SPreEventBase       (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeFetchReadDataChannelM2SPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchReadDataChannelM2SPostEvent::SoCAXIBridgeFetchReadDataChannelM2SPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const FetchAXI4ReadDataChannelM2S&      bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeFetchReadDataChannelM2SPostEventBase      (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeFetchReadDataChannelS2MPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchReadDataChannelS2MPreEvent::SoCAXIBridgeFetchReadDataChannelS2MPreEvent(
        SoCAXIBridge*                           soc_axi, 
        FetchAXI4ReadDataChannelS2M&            bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeFetchReadDataChannelS2MPreEventBase       (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeFetchReadDataChannelS2MPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchReadDataChannelS2MPostEvent::SoCAXIBridgeFetchReadDataChannelS2MPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const FetchAXI4ReadDataChannelS2M&      bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeFetchReadDataChannelS2MPostEventBase      (bundle)
    { }
}


// Implementation of: class SoCAXIBridgeDataReadAddressChannelM2SPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataReadAddressChannelM2SPreEvent::SoCAXIBridgeDataReadAddressChannelM2SPreEvent(
        SoCAXIBridge*                           soc_axi, 
        DataAXI4ReadAddressChannelM2S&          bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataReadAddressChannelM2SPreEventBase     (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataReadAddressChannelM2SPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataReadAddressChannelM2SPostEvent::SoCAXIBridgeDataReadAddressChannelM2SPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const DataAXI4ReadAddressChannelM2S&    bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataReadAddressChannelM2SPostEventBase    (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataReadAddressChannelS2MPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataReadAddressChannelS2MPreEvent::SoCAXIBridgeDataReadAddressChannelS2MPreEvent(
        SoCAXIBridge*                           soc_axi, 
        DataAXI4ReadAddressChannelS2M&          bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataReadAddressChannelS2MPreEventBase     (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataReadAddressChannelS2MPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataReadAddressChannelS2MPostEvent::SoCAXIBridgeDataReadAddressChannelS2MPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const DataAXI4ReadAddressChannelS2M&    bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataReadAddressChannelS2MPostEventBase    (bundle)
    { }
}



// Implementation of: class SoCAXIBridgeDataReadDataChannelM2SPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataReadDataChannelM2SPreEvent::SoCAXIBridgeDataReadDataChannelM2SPreEvent(
        SoCAXIBridge*                           soc_axi, 
        DataAXI4ReadDataChannelM2S&             bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataReadDataChannelM2SPreEventBase        (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataReadDataChannelM2SPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataReadDataChannelM2SPostEvent::SoCAXIBridgeDataReadDataChannelM2SPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const DataAXI4ReadDataChannelM2S&       bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataReadDataChannelM2SPostEventBase       (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataReadDataChannelS2MPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataReadDataChannelS2MPreEvent::SoCAXIBridgeDataReadDataChannelS2MPreEvent(
        SoCAXIBridge*                           soc_axi, 
        DataAXI4ReadDataChannelS2M&             bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataReadDataChannelS2MPreEventBase        (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataReadDataChannelS2MPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataReadDataChannelS2MPostEvent::SoCAXIBridgeDataReadDataChannelS2MPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const DataAXI4ReadDataChannelS2M&       bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataReadDataChannelS2MPostEventBase       (bundle)
    { }
}


// Implementation of: class SoCAXIBridgeDataWriteAddressChannelM2SPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteAddressChannelM2SPreEvent::SoCAXIBridgeDataWriteAddressChannelM2SPreEvent(
        SoCAXIBridge*                           soc_axi, 
        DataAXI4WriteAddressChannelM2S&         bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteAddressChannelM2SPreEventBase    (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataWriteAddressChannelM2SPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteAddressChannelM2SPostEvent::SoCAXIBridgeDataWriteAddressChannelM2SPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const DataAXI4WriteAddressChannelM2S&   bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteAddressChannelM2SPostEventBase   (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataWriteAddressChannelS2MPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteAddressChannelS2MPreEvent::SoCAXIBridgeDataWriteAddressChannelS2MPreEvent(
        SoCAXIBridge*                           soc_axi, 
        DataAXI4WriteAddressChannelS2M&         bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteAddressChannelS2MPreEventBase    (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataWriteAddressChannelS2MPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteAddressChannelS2MPostEvent::SoCAXIBridgeDataWriteAddressChannelS2MPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const DataAXI4WriteAddressChannelS2M&   bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteAddressChannelS2MPostEventBase   (bundle)
    { }
}


// Implementation of: class SoCAXIBridgeDataWriteDataChannelM2SPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteDataChannelM2SPreEvent::SoCAXIBridgeDataWriteDataChannelM2SPreEvent(
        SoCAXIBridge*                           soc_axi, 
        DataAXI4WriteDataChannelM2S&            bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteDataChannelM2SPreEventBase       (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataWriteDataChannelM2SPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteDataChannelM2SPostEvent::SoCAXIBridgeDataWriteDataChannelM2SPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const DataAXI4WriteDataChannelM2S&      bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteDataChannelM2SPostEventBase      (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataWriteDataChannelS2MPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteDataChannelS2MPreEvent::SoCAXIBridgeDataWriteDataChannelS2MPreEvent(
        SoCAXIBridge*                           soc_axi, 
        DataAXI4WriteDataChannelS2M&            bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteDataChannelS2MPreEventBase       (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataWriteDataChannelS2MPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteDataChannelS2MPostEvent::SoCAXIBridgeDataWriteDataChannelS2MPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const DataAXI4WriteDataChannelS2M&      bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteDataChannelS2MPostEventBase      (bundle)
    { }
}


// Implementation of: class SoCAXIBridgeDataWriteResponseChannelM2SPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteResponseChannelM2SPreEvent::SoCAXIBridgeDataWriteResponseChannelM2SPreEvent(
        SoCAXIBridge*                           soc_axi, 
        DataAXI4WriteResponseChannelM2S&        bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteResponseChannelM2SPreEventBase   (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataWriteResponseChannelM2SPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteResponseChannelM2SPostEvent::SoCAXIBridgeDataWriteResponseChannelM2SPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const DataAXI4WriteResponseChannelM2S&  bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteResponseChannelM2SPostEventBase  (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataWriteResponseChannelS2MPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteResponseChannelS2MPreEvent::SoCAXIBridgeDataWriteResponseChannelS2MPreEvent(
        SoCAXIBridge*                           soc_axi, 
        DataAXI4WriteResponseChannelS2M&        bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteResponseChannelS2MPreEventBase   (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataWriteResponseChannelS2MPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteResponseChannelS2MPostEvent::SoCAXIBridgeDataWriteResponseChannelS2MPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const DataAXI4WriteResponseChannelS2M&  bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteResponseChannelS2MPostEventBase  (bundle)
    { }
}



// Implementation of: class SoCAXIBridgeFetchReadAddressAcceptedPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchReadAddressAcceptedPreEvent::SoCAXIBridgeFetchReadAddressAcceptedPreEvent(
        SoCAXIBridge*                           soc_axi, 
        FetchAXI4ReadAddressChannelM2S&         bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeFetchReadAddressChannelM2SPreEventBase    (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeFetchReadAddressAcceptedPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchReadAddressAcceptedPostEvent::SoCAXIBridgeFetchReadAddressAcceptedPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const FetchAXI4ReadAddressChannelM2S&   bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeFetchReadAddressChannelM2SPostEventBase   (bundle)
    { }
}


// Implementation of: class SoCAXIBridgeFetchReadDataAcceptedPreEvent
/*
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchReadDataAcceptedPreEvent::SoCAXIBridgeFetchReadDataAcceptedPreEvent(
        SoCAXIBridge*                           soc_axi,
        FetchAXI4ReadDataChannelS2M&            bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeFetchReadDataChannelS2MPreEventBase       (bundle)
    { }
}
*/

// Implementation of: class SoCAXIBridgeFetchReadDataAcceptedPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchReadDataAcceptedPostEvent::SoCAXIBridgeFetchReadDataAcceptedPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const FetchAXI4ReadDataChannelS2M&      bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeFetchReadDataChannelS2MPostEventBase      (bundle)
    { }
}


// Implementation of: class SoCAXIBridgeDataReadAddressAcceptedPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataReadAddressAcceptedPreEvent::SoCAXIBridgeDataReadAddressAcceptedPreEvent(
        SoCAXIBridge*                           soc_axi, 
        DataAXI4ReadAddressChannelM2S&          bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataReadAddressChannelM2SPreEventBase     (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataReadAddressAcceptedPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataReadAddressAcceptedPostEvent::SoCAXIBridgeDataReadAddressAcceptedPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const DataAXI4ReadAddressChannelM2S&    bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataReadAddressChannelM2SPostEventBase    (bundle)
    { }
}


// Implementation of: class SoCAXIBridgeDataReadDataAcceptedPreEvent
/*
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataReadDataAcceptedPreEvent::SoCAXIBridgeDataReadDataAcceptedPreEvent(
        SoCAXIBridge*                           soc_axi, 
        DataAXI4ReadDataChannelS2M&             bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataReadDataChannelS2MPreEventBase        (bundle)
    { }
}
*/

// Implementation of: class SoCAXIBridgeDataReadDataAcceptedPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataReadDataAcceptedPostEvent::SoCAXIBridgeDataReadDataAcceptedPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const DataAXI4ReadDataChannelS2M&       bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataReadDataChannelS2MPostEventBase       (bundle)
    { }
}


// Implementation of: class SoCAXIBridgeDataWriteAddressAcceptedPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteAddressAcceptedPreEvent::SoCAXIBridgeDataWriteAddressAcceptedPreEvent(
        SoCAXIBridge*                           soc_axi, 
        DataAXI4WriteAddressChannelM2S&         bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteAddressChannelM2SPreEventBase    (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataWriteAddressAcceptedPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteAddressAcceptedPostEvent::SoCAXIBridgeDataWriteAddressAcceptedPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const DataAXI4WriteAddressChannelM2S&   bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteAddressChannelM2SPostEventBase   (bundle)
    { }
}


// Implementation of: class SoCAXIBridgeDataWriteDataAcceptedPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteDataAcceptedPreEvent::SoCAXIBridgeDataWriteDataAcceptedPreEvent(
        SoCAXIBridge*                           soc_axi, 
        DataAXI4WriteDataChannelM2S&            bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteDataChannelM2SPreEventBase       (bundle)
    { }
}

// Implementation of: class SoCAXIBridgeDataWriteDataAcceptedPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteDataAcceptedPostEvent::SoCAXIBridgeDataWriteDataAcceptedPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const DataAXI4WriteDataChannelM2S&      bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteDataChannelM2SPostEventBase      (bundle)
    { }
}


// Implementation of: class SoCAXIBridgeDataWriteResponseAcceptedPreEvent
/*
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteResponseAcceptedPreEvent::SoCAXIBridgeDataWriteResponseAcceptedPreEvent(
        SoCAXIBridge*                           soc_axi, 
        DataAXI4WriteResponseChannelS2M&        bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteResponseChannelS2MPreEventBase   (bundle)
    { }
}
*/

// Implementation of: class SoCAXIBridgeDataWriteResponseAcceptedPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataWriteResponseAcceptedPostEvent::SoCAXIBridgeDataWriteResponseAcceptedPostEvent(
        SoCAXIBridge*                           soc_axi, 
        const DataAXI4WriteResponseChannelS2M&  bundle) noexcept
        : SoCAXIBridgeEventBase                                 (soc_axi)
        , SoCAXIBridgeDataWriteResponseChannelS2MPostEventBase  (bundle)
    { }
}




// Implementation of: class SoCAXIBridgeMMUPreWritePreEventBase
namespace BullsEye::Draconids3014 {
    /*
    addr_t&         address;
    LA32MOPWidth&   width;
    memdata_t&      data;
    */

    SoCAXIBridgeMMUPreWritePreEventBase::SoCAXIBridgeMMUPreWritePreEventBase(
        addr_t&                                 address, 
        LA32MOPWidth&                           width, 
        memdata_t&                              data) noexcept
        : address   (address)
        , width     (width)
        , data      (data)
    { }

    addr_t SoCAXIBridgeMMUPreWritePreEventBase::GetAddress() const noexcept
    {
        return address;
    }

    LA32MOPWidth SoCAXIBridgeMMUPreWritePreEventBase::GetWidth() const noexcept
    {
        return width;
    }

    memdata_t SoCAXIBridgeMMUPreWritePreEventBase::GetData() const noexcept
    {
        return data;
    }

    void SoCAXIBridgeMMUPreWritePreEventBase::SetAddress(addr_t address) noexcept
    {
        this->address = address;
    }

    void SoCAXIBridgeMMUPreWritePreEventBase::SetWidth(LA32MOPWidth width) noexcept
    {
        this->width = width;
    }

    void SoCAXIBridgeMMUPreWritePreEventBase::SetData(memdata_t data) noexcept
    {
        this->data = data;
    }
}

// Implementation of: class SoCAXIBridgeMMUPreWritePostEventBase
namespace BullsEye::Draconids3014 {
    /*
    addr_t          address;
    LA32MOPWidth    width;
    memdata_t       data;
    */

    SoCAXIBridgeMMUPreWritePostEventBase::SoCAXIBridgeMMUPreWritePostEventBase(
        addr_t                                  address, 
        LA32MOPWidth                            width, 
        memdata_t                               data) noexcept
        : address   (address)
        , width     (width)
        , data      (data)
    { }

    addr_t SoCAXIBridgeMMUPreWritePostEventBase::GetAddress() const noexcept
    {
        return address;
    }

    LA32MOPWidth SoCAXIBridgeMMUPreWritePostEventBase::GetWidth() const noexcept
    {
        return width;
    }

    memdata_t SoCAXIBridgeMMUPreWritePostEventBase::GetData() const noexcept
    {
        return data;
    }
}

// Implementation of: class SoCAXIBridgeMMUPostWritePreEventBase
namespace BullsEye::Draconids3014 {
    /*
    addr_t          address;
    LA32MOPWidth    width;
    memdata_t       data;
    LA32MOPOutcome& outcome;
    */

    SoCAXIBridgeMMUPostWritePreEventBase::SoCAXIBridgeMMUPostWritePreEventBase(
        addr_t                                  address, 
        LA32MOPWidth                            width, 
        memdata_t                               data, 
        LA32MOPOutcome&                         outcome) noexcept
        : address   (address)
        , width     (width)
        , data      (data)
        , outcome   (outcome)
    { }

    addr_t SoCAXIBridgeMMUPostWritePreEventBase::GetAddress() const noexcept
    {
        return address;
    }

    LA32MOPWidth SoCAXIBridgeMMUPostWritePreEventBase::GetWidth() const noexcept
    {
        return width;
    }

    memdata_t SoCAXIBridgeMMUPostWritePreEventBase::GetData() const noexcept
    {
        return data;
    }

    LA32MOPOutcome SoCAXIBridgeMMUPostWritePreEventBase::GetOutcome() const noexcept
    {
        return outcome;
    }

    void SoCAXIBridgeMMUPostWritePreEventBase::SetOutcome(LA32MOPOutcome outcome) noexcept
    {
        this->outcome = outcome;
    }
}

// Implementation of: class SoCAXIBridgeMMUPostWritePostEventBase
namespace BullsEye::Draconids3014 {
    /*
    addr_t          address;
    LA32MOPWidth    width;
    memdata_t       data;
    LA32MOPOutcome  outcome;
    */

    SoCAXIBridgeMMUPostWritePostEventBase::SoCAXIBridgeMMUPostWritePostEventBase(
        addr_t                                  address, 
        LA32MOPWidth                            width, 
        memdata_t                               data, 
        LA32MOPOutcome                          outcome) noexcept
        : address   (address)
        , width     (width)
        , data      (data)
        , outcome   (outcome)
    { }

    addr_t SoCAXIBridgeMMUPostWritePostEventBase::GetAddress() const noexcept
    {
        return address;
    }

    LA32MOPWidth SoCAXIBridgeMMUPostWritePostEventBase::GetWidth() const noexcept
    {
        return width;
    }

    memdata_t SoCAXIBridgeMMUPostWritePostEventBase::GetData() const noexcept
    {
        return data;
    }

    LA32MOPOutcome SoCAXIBridgeMMUPostWritePostEventBase::GetOutcome() const noexcept
    {
        return outcome;
    }
}


// Implementation of: class SoCAXIBridgeMMUPreReadPreEventBase
namespace BullsEye::Draconids3014 {
    /*
    addr_t&         address;
    LA32MOPWidth&   width;
    */

    SoCAXIBridgeMMUPreReadPreEventBase::SoCAXIBridgeMMUPreReadPreEventBase(
        addr_t&                                 address, 
        LA32MOPWidth&                           width) noexcept
        : address   (address)
        , width     (width)
    { }

    addr_t SoCAXIBridgeMMUPreReadPreEventBase::GetAddress() const noexcept
    {
        return address;
    }

    LA32MOPWidth SoCAXIBridgeMMUPreReadPreEventBase::GetWidth() const noexcept
    {
        return width;
    }

    void SoCAXIBridgeMMUPreReadPreEventBase::SetAddress(addr_t address) noexcept
    {
        this->address = address;
    }

    void SoCAXIBridgeMMUPreReadPreEventBase::SetWidth(LA32MOPWidth width) noexcept
    {
        this->width = width;
    }
}

// Implementation of: class SoCAXIBridgeMMUPreReadPostEventBase
namespace BullsEye::Draconids3014 {
    /*
    addr_t          address;
    LA32MOPWidth    width;
    */

    SoCAXIBridgeMMUPreReadPostEventBase::SoCAXIBridgeMMUPreReadPostEventBase(
        addr_t                                  address, 
        LA32MOPWidth                            width) noexcept
        : address   (address)
        , width     (width)
    { }

    addr_t SoCAXIBridgeMMUPreReadPostEventBase::GetAddress() const noexcept
    {
        return address;
    }

    LA32MOPWidth SoCAXIBridgeMMUPreReadPostEventBase::GetWidth() const noexcept
    {
        return width;
    }
}

// Implementation of: class SoCAXIBridgeMMUPostReadPreEventBase
namespace BullsEye::Draconids3014 {
    /*
    addr_t          address;
    LA32MOPWidth    width;
    memdata_t&      data;
    LA32MOPOutcome& outcome;
    */

    SoCAXIBridgeMMUPostReadPreEventBase::SoCAXIBridgeMMUPostReadPreEventBase(
        addr_t                                  address, 
        LA32MOPWidth                            width, 
        memdata_t&                              data, 
        LA32MOPOutcome&                         outcome) noexcept
        : address   (address)
        , width     (width)
        , data      (data)
        , outcome   (outcome)
    { }

    addr_t SoCAXIBridgeMMUPostReadPreEventBase::GetAddress() const noexcept
    {
        return address;
    }

    LA32MOPWidth SoCAXIBridgeMMUPostReadPreEventBase::GetWidth() const noexcept
    {
        return width;
    }

    memdata_t SoCAXIBridgeMMUPostReadPreEventBase::GetData() const noexcept
    {
        return data;
    }

    LA32MOPOutcome SoCAXIBridgeMMUPostReadPreEventBase::GetOutcome() const noexcept
    {
        return outcome;
    }

    void SoCAXIBridgeMMUPostReadPreEventBase::SetOutcome(LA32MOPOutcome outcome) noexcept
    {
        this->outcome = outcome;
    }

    void SoCAXIBridgeMMUPostReadPreEventBase::SetData(memdata_t data) noexcept
    {
        this->data = data;
    }
}

// Implementation of: class SoCAXIBridgeMMUPostReadPostEventBase
namespace BullsEye::Draconids3014 {
    /*
    addr_t          address;
    LA32MOPWidth    width;
    memdata_t       data;
    LA32MOPOutcome  outcome;
    */

    SoCAXIBridgeMMUPostReadPostEventBase::SoCAXIBridgeMMUPostReadPostEventBase(
        addr_t                                  address, 
        LA32MOPWidth                            width, 
        memdata_t                               data, 
        LA32MOPOutcome                          outcome) noexcept
        : address   (address)
        , width     (width)
        , data      (data)
        , outcome   (outcome)
    { }

    addr_t SoCAXIBridgeMMUPostReadPostEventBase::GetAddress() const noexcept
    {
        return address;
    }

    LA32MOPWidth SoCAXIBridgeMMUPostReadPostEventBase::GetWidth() const noexcept
    {
        return width;
    }

    memdata_t SoCAXIBridgeMMUPostReadPostEventBase::GetData() const noexcept
    {
        return data;
    }

    LA32MOPOutcome SoCAXIBridgeMMUPostReadPostEventBase::GetOutcome() const noexcept
    {
        return outcome;
    }
}



// Implementation of: class SoCAXIBridgeFetchMMUPreWritePreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchMMUPreWritePreEvent::SoCAXIBridgeFetchMMUPreWritePreEvent(
        SoCAXIBridge*   soc_axi, 
        addr_t&         address, 
        LA32MOPWidth&   width, 
        memdata_t&      data) noexcept
        : SoCAXIBridgeEventBase                 (soc_axi)
        , SoCAXIBridgeMMUPreWritePreEventBase   (address, width, data)
    { }
}

// Implementation of: class SoCAXIBridgeFetchMMUPreWritePostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchMMUPreWritePostEvent::SoCAXIBridgeFetchMMUPreWritePostEvent(
        SoCAXIBridge*   soc_axi, 
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data) noexcept
        : SoCAXIBridgeEventBase                 (soc_axi)
        , SoCAXIBridgeMMUPreWritePostEventBase  (address, width, data)
    { }
}

// Implementation of: class SoCAXIBridgeFetchMMUPostWritePreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchMMUPostWritePreEvent::SoCAXIBridgeFetchMMUPostWritePreEvent(
        SoCAXIBridge*   soc_axi, 
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data, 
        LA32MOPOutcome& outcome) noexcept
        : SoCAXIBridgeEventBase                 (soc_axi)
        , SoCAXIBridgeMMUPostWritePreEventBase  (address, width, data, outcome)
    { }
}

// Implementation of: class SoCAXIBridgeFetchMMUPostWritePostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchMMUPostWritePostEvent::SoCAXIBridgeFetchMMUPostWritePostEvent(
        SoCAXIBridge*   soc_axi, 
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data, 
        LA32MOPOutcome  outcome) noexcept
        : SoCAXIBridgeEventBase                 (soc_axi)
        , SoCAXIBridgeMMUPostWritePostEventBase (address, width, data, outcome)
    { }
}


// Implementation of: class SoCAXIBridgeFetchMMUPreReadPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchMMUPreReadPreEvent::SoCAXIBridgeFetchMMUPreReadPreEvent(
        SoCAXIBridge*   soc_axi, 
        addr_t&         address, 
        LA32MOPWidth&   width) noexcept
        : SoCAXIBridgeEventBase                 (soc_axi)
        , SoCAXIBridgeMMUPreReadPreEventBase    (address, width)
    { }
}

// Implementation of: class SoCAXIBridgeFetchMMUPreReadPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchMMUPreReadPostEvent::SoCAXIBridgeFetchMMUPreReadPostEvent(
        SoCAXIBridge*   soc_axi, 
        addr_t          address, 
        LA32MOPWidth    width) noexcept
        : SoCAXIBridgeEventBase                 (soc_axi)
        , SoCAXIBridgeMMUPreReadPostEventBase   (address, width)
    { }
}

// Implementation of: class SoCAXIBridgeFetchMMUPostReadPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchMMUPostReadPreEvent::SoCAXIBridgeFetchMMUPostReadPreEvent(
        SoCAXIBridge*   soc_axi, 
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t&      data, 
        LA32MOPOutcome& outcome) noexcept
        : SoCAXIBridgeEventBase                 (soc_axi)
        , SoCAXIBridgeMMUPostReadPreEventBase   (address, width, data, outcome)
    { }
}

// Implementation of: class SoCAXIBridgeFetchMMUPostReadPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchMMUPostReadPostEvent::SoCAXIBridgeFetchMMUPostReadPostEvent(
        SoCAXIBridge*   soc_axi, 
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data, 
        LA32MOPOutcome  outcome) noexcept
        : SoCAXIBridgeEventBase                 (soc_axi)
        , SoCAXIBridgeMMUPostReadPostEventBase  (address, width, data, outcome)
    { }
}



// Implementation of: class SoCAXIBridgeDataMMUPreWritePreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataMMUPreWritePreEvent::SoCAXIBridgeDataMMUPreWritePreEvent(
        SoCAXIBridge*   soc_axi, 
        addr_t&         address, 
        LA32MOPWidth&   width, 
        memdata_t&      data) noexcept
        : SoCAXIBridgeEventBase                 (soc_axi)
        , SoCAXIBridgeMMUPreWritePreEventBase   (address, width, data)
    { }
}

// Implementation of: class SoCAXIBridgeDataMMUPreWritePostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataMMUPreWritePostEvent::SoCAXIBridgeDataMMUPreWritePostEvent(
        SoCAXIBridge*   soc_axi, 
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data) noexcept
        : SoCAXIBridgeEventBase                 (soc_axi)
        , SoCAXIBridgeMMUPreWritePostEventBase  (address, width, data)
    { }
}

// Implementation of: class SoCAXIBridgeDataMMUPostWritePreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataMMUPostWritePreEvent::SoCAXIBridgeDataMMUPostWritePreEvent(
        SoCAXIBridge*   soc_axi, 
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data, 
        LA32MOPOutcome& outcome) noexcept
        : SoCAXIBridgeEventBase                 (soc_axi)
        , SoCAXIBridgeMMUPostWritePreEventBase  (address, width, data, outcome)
    { }
}

// Implementation of: class SoCAXIBridgeDataMMUPostWritePostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataMMUPostWritePostEvent::SoCAXIBridgeDataMMUPostWritePostEvent(
        SoCAXIBridge*   soc_axi, 
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data, 
        LA32MOPOutcome  outcome) noexcept
        : SoCAXIBridgeEventBase                 (soc_axi)
        , SoCAXIBridgeMMUPostWritePostEventBase (address, width, data, outcome)
    { }
}


// Implementation of: class SoCAXIBridgeDataMMUPreReadPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataMMUPreReadPreEvent::SoCAXIBridgeDataMMUPreReadPreEvent(
        SoCAXIBridge*   soc_axi, 
        addr_t&         address, 
        LA32MOPWidth&   width) noexcept
        : SoCAXIBridgeEventBase                 (soc_axi)
        , SoCAXIBridgeMMUPreReadPreEventBase    (address, width)
    { }
}

// Implementation of: class SoCAXIBridgeDataMMUPreReadPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataMMUPreReadPostEvent::SoCAXIBridgeDataMMUPreReadPostEvent(
        SoCAXIBridge*   soc_axi, 
        addr_t          address, 
        LA32MOPWidth    width) noexcept
        : SoCAXIBridgeEventBase                 (soc_axi)
        , SoCAXIBridgeMMUPreReadPostEventBase   (address, width)
    { }
}

// Implementation of: class SoCAXIBridgeDataMMUPostReadPreEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataMMUPostReadPreEvent::SoCAXIBridgeDataMMUPostReadPreEvent(
        SoCAXIBridge*   soc_axi, 
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t&      data, 
        LA32MOPOutcome& outcome) noexcept
        : SoCAXIBridgeEventBase                 (soc_axi)
        , SoCAXIBridgeMMUPostReadPreEventBase   (address, width, data, outcome)
    { }
}

// Implementation of: class SoCAXIBridgeDataMMUPostReadPostEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataMMUPostReadPostEvent::SoCAXIBridgeDataMMUPostReadPostEvent(
        SoCAXIBridge*   soc_axi, 
        addr_t          address, 
        LA32MOPWidth    width, 
        memdata_t       data, 
        LA32MOPOutcome  outcome) noexcept
        : SoCAXIBridgeEventBase                 (soc_axi)
        , SoCAXIBridgeMMUPostReadPostEventBase  (address, width, data, outcome)
    { }
}




// Implementation of: class SoCAXIBridgeErrorEventBase
namespace BullsEye::Draconids3014 {
    /*
    uint4_t     transaction_id;
    ErrorType   type;
    */

    SoCAXIBridgeErrorEventBase::SoCAXIBridgeErrorEventBase(
        uint4_t     transaction_id, 
        ErrorType   type) noexcept
        : transaction_id    (transaction_id)
        , type              (type)
    { }

    uint4_t SoCAXIBridgeErrorEventBase::GetTransactionID() const noexcept
    {
        return transaction_id;
    }

    SoCAXIBridgeErrorEventBase::ErrorType SoCAXIBridgeErrorEventBase::GetType() const noexcept
    {
        return type;
    }
}



// Implementation of: class SoCAXIBridgeFetchErrorEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeFetchErrorEvent::SoCAXIBridgeFetchErrorEvent(
        SoCAXIBridge*   soc_axi, 
        uint4_t         transaction_id, 
        ErrorType       type) noexcept
        : SoCAXIBridgeEventBase     (soc_axi)
        , SoCAXIBridgeErrorEventBase(transaction_id, type)
    { }
}

// Implementation of: class SoCAXIBridgeDataErrorEvent
namespace BullsEye::Draconids3014 {

    SoCAXIBridgeDataErrorEvent::SoCAXIBridgeDataErrorEvent(
        SoCAXIBridge*   soc_axi, 
        uint4_t         transaction_id, 
        ErrorType       type) noexcept
        : SoCAXIBridgeEventBase     (soc_axi)
        , SoCAXIBridgeErrorEventBase(transaction_id, type)
    { }
}
