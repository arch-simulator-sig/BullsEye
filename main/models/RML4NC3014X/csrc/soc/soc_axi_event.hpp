#pragma once

#ifndef __HEADER_DS232__SOC_AXI_EVENT
#define __HEADER_DS232__SOC_AXI_EVENT


#include "autoinclude.h"

#include AUTOINC_BE_COMMON(eventbus.hpp)


#include "soc_axi.hpp"


namespace BullsEye::Draconids3014 {

    // SoC AXI Bridge Bundle Pre Event Template
    template<class _TBundle>
    class SoCAXIBridgeBundlePreEventBase {
    private:
        _TBundle&       bundle;

    public:
        SoCAXIBridgeBundlePreEventBase(_TBundle& bundle) noexcept
        : bundle(bundle) { }

        _TBundle&       GetBundle() noexcept        { return bundle; }
        const _TBundle& GetBundle() const noexcept  { return bundle; }
    };

    // SoC AXI Bridge Bundle Post Event Template
    template<class _TBundle>
    class SoCAXIBridgeBundlePostEventBase {
    private:
        const _TBundle& bundle;

    public:
        SoCAXIBridgeBundlePostEventBase(const _TBundle& bundle) noexcept
        : bundle(bundle) { }

        const _TBundle& GetBundle() const noexcept  { return bundle; }
    };


    // SoC AXI Bridge Event Base
    class SoCAXIBridgeEventBase {
    private:
        SoCAXIBridge*   soc_axi;

    public:
        SoCAXIBridgeEventBase(SoCAXIBridge* soc_axi) noexcept;

        SoCAXIBridge*       GetBridge() noexcept;
        const SoCAXIBridge* GetBridge() const noexcept;
    };


    // Fetch Read Address Channel Master-to-Slave Pre Event Base
    using SoCAXIBridgeFetchReadAddressChannelM2SPreEventBase 
        = SoCAXIBridgeBundlePreEventBase<FetchAXI4ReadAddressChannelM2S>;

    // Fetch Read Address Channel Master-to-Slave Post Event Base
    using SoCAXIBridgeFetchReadAddressChannelM2SPostEventBase 
        = SoCAXIBridgeBundlePostEventBase<FetchAXI4ReadAddressChannelM2S>;

    // Fetch Read Address Channel Slave-to-Master Pre Event Base
    using SoCAXIBridgeFetchReadAddressChannelS2MPreEventBase 
        = SoCAXIBridgeBundlePreEventBase<FetchAXI4ReadAddressChannelS2M>;

    // Fetch Read Address Channel Slave-to-Master Post Event Base
    using SoCAXIBridgeFetchReadAddressChannelS2MPostEventBase 
        = SoCAXIBridgeBundlePostEventBase<FetchAXI4ReadAddressChannelS2M>;


    // Fetch Read Data Channel Master-to-Slave Event Pre Base
    using SoCAXIBridgeFetchReadDataChannelM2SPreEventBase 
        = SoCAXIBridgeBundlePreEventBase<FetchAXI4ReadDataChannelM2S>;

    // Fetch Read Data Channel Master-to-Slave Event Post Base
    using SoCAXIBridgeFetchReadDataChannelM2SPostEventBase 
        = SoCAXIBridgeBundlePostEventBase<FetchAXI4ReadDataChannelM2S>;

    // Fetch Read Data Channel Slave-to-Master Event Pre Base
    using SoCAXIBridgeFetchReadDataChannelS2MPreEventBase 
        = SoCAXIBridgeBundlePreEventBase<FetchAXI4ReadDataChannelS2M>;

    // Fetch Read Data Channel Slave-to-Master Event Post Base
    using SoCAXIBridgeFetchReadDataChannelS2MPostEventBase 
        = SoCAXIBridgeBundlePostEventBase<FetchAXI4ReadDataChannelS2M>;

    
    // Data Read Address Channel Master-to-Slave Pre Event Base
    using SoCAXIBridgeDataReadAddressChannelM2SPreEventBase 
        = SoCAXIBridgeBundlePreEventBase<DataAXI4ReadAddressChannelM2S>;

    // Data Read Address Channel Master-to-Slave Post Event Base
    using SoCAXIBridgeDataReadAddressChannelM2SPostEventBase 
        = SoCAXIBridgeBundlePostEventBase<DataAXI4ReadAddressChannelM2S>;

    // Data Read Address Channel Slave-to-Master Pre Event Base
    using SoCAXIBridgeDataReadAddressChannelS2MPreEventBase 
        = SoCAXIBridgeBundlePreEventBase<DataAXI4ReadAddressChannelS2M>;

    // Data Read Address Channel Slave-to-Master Post Event Base
    using SoCAXIBridgeDataReadAddressChannelS2MPostEventBase 
        = SoCAXIBridgeBundlePostEventBase<DataAXI4ReadAddressChannelS2M>;


    // Data Read Data Channel Master-to-Slave Pre Event Base
    using SoCAXIBridgeDataReadDataChannelM2SPreEventBase 
        = SoCAXIBridgeBundlePreEventBase<DataAXI4ReadDataChannelM2S>;

    // Data Read Data Channel Master-to-Slave Post Event Base
    using SoCAXIBridgeDataReadDataChannelM2SPostEventBase 
        = SoCAXIBridgeBundlePostEventBase<DataAXI4ReadDataChannelM2S>;

    // Data Read Data Channel Slave-to-Master Pre Event Base
    using SoCAXIBridgeDataReadDataChannelS2MPreEventBase 
        = SoCAXIBridgeBundlePreEventBase<DataAXI4ReadDataChannelS2M>;

    // Data Read Data Channel Slave-to-Master Post Event Base
    using SoCAXIBridgeDataReadDataChannelS2MPostEventBase 
        = SoCAXIBridgeBundlePostEventBase<DataAXI4ReadDataChannelS2M>;


    // Data Write Address Channel Master-to-Slave Pre Event Base
    using SoCAXIBridgeDataWriteAddressChannelM2SPreEventBase 
        = SoCAXIBridgeBundlePreEventBase<DataAXI4WriteAddressChannelM2S>;

    // Data Write Address Channel Master-to-Slave Post Event Base
    using SoCAXIBridgeDataWriteAddressChannelM2SPostEventBase 
        = SoCAXIBridgeBundlePostEventBase<DataAXI4WriteAddressChannelM2S>;

    // Data Write Address Channel Slave-to-Master Pre Event Base
    using SoCAXIBridgeDataWriteAddressChannelS2MPreEventBase 
        = SoCAXIBridgeBundlePreEventBase<DataAXI4WriteAddressChannelS2M>;

    // Data Write Address Channel Slave-to-Master Post Event Base
    using SoCAXIBridgeDataWriteAddressChannelS2MPostEventBase 
        = SoCAXIBridgeBundlePostEventBase<DataAXI4WriteAddressChannelS2M>;


    // Data Write Data Channel Master-to-Slave Pre Event Base
    using SoCAXIBridgeDataWriteDataChannelM2SPreEventBase 
        = SoCAXIBridgeBundlePreEventBase<DataAXI4WriteDataChannelM2S>;

    // Data Write Data Channel Master-to-Slave Post Event Base
    using SoCAXIBridgeDataWriteDataChannelM2SPostEventBase 
        = SoCAXIBridgeBundlePostEventBase<DataAXI4WriteDataChannelM2S>;

    // Data Write Data Channel Slave-to-Master Pre Event Base
    using SoCAXIBridgeDataWriteDataChannelS2MPreEventBase 
        = SoCAXIBridgeBundlePreEventBase<DataAXI4WriteDataChannelS2M>;

    // Data Write Data Channel Slave-to-Master Post Event Base
    using SoCAXIBridgeDataWriteDataChannelS2MPostEventBase 
        = SoCAXIBridgeBundlePostEventBase<DataAXI4WriteDataChannelS2M>;

    
    // Data Write Response Channel Master-to-Slave Pre Event Base
    using SoCAXIBridgeDataWriteResponseChannelM2SPreEventBase 
        = SoCAXIBridgeBundlePreEventBase<DataAXI4WriteResponseChannelM2S>;

    // Data Write Response Channel Master-to-Slave Post Event Base
    using SoCAXIBridgeDataWriteResponseChannelM2SPostEventBase 
        = SoCAXIBridgeBundlePostEventBase<DataAXI4WriteResponseChannelM2S>;

    // Data Write Response Channel Slave-to-Master Pre Event Base
    using SoCAXIBridgeDataWriteResponseChannelS2MPreEventBase 
        = SoCAXIBridgeBundlePreEventBase<DataAXI4WriteResponseChannelS2M>;

    // Data Write Response Channel Slave-to-Master Post Event Base
    using SoCAXIBridgeDataWriteResponseChannelS2MPostEventBase 
        = SoCAXIBridgeBundlePostEventBase<DataAXI4WriteResponseChannelS2M>;


    
    // SoC AXI Bridge Fetch Read Address Channel Master-to-Slave Pre Event
    class SoCAXIBridgeFetchReadAddressChannelM2SPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeFetchReadAddressChannelM2SPreEventBase
        , public Event<SoCAXIBridgeFetchReadAddressChannelM2SPreEvent> {
    public:
        SoCAXIBridgeFetchReadAddressChannelM2SPreEvent(SoCAXIBridge*, FetchAXI4ReadAddressChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Fetch Read Address Channel Master-to-Slave Post Event
    class SoCAXIBridgeFetchReadAddressChannelM2SPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeFetchReadAddressChannelM2SPostEventBase
        , public Event<SoCAXIBridgeFetchReadAddressChannelM2SPostEvent> {
    public:
        SoCAXIBridgeFetchReadAddressChannelM2SPostEvent(SoCAXIBridge*, const FetchAXI4ReadAddressChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Fetch Read Address Channel Slave-to-Master Pre Event
    class SoCAXIBridgeFetchReadAddressChannelS2MPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeFetchReadAddressChannelS2MPreEventBase
        , public Event<SoCAXIBridgeFetchReadAddressChannelS2MPreEvent> {
    public:
        SoCAXIBridgeFetchReadAddressChannelS2MPreEvent(SoCAXIBridge*, FetchAXI4ReadAddressChannelS2M& bundle) noexcept;
    };

    // SoC AXI Bridge Fetch Read Address Channel Slave-to-Master Post Event
    class SoCAXIBridgeFetchReadAddressChannelS2MPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeFetchReadAddressChannelS2MPostEventBase
        , public Event<SoCAXIBridgeFetchReadAddressChannelS2MPostEvent> {
    public:
        SoCAXIBridgeFetchReadAddressChannelS2MPostEvent(SoCAXIBridge*, const FetchAXI4ReadAddressChannelS2M& bundle) noexcept;
    };


    // SoC AXI Bridge Fetch Read Data Channel Master-to-Slave Pre Event
    class SoCAXIBridgeFetchReadDataChannelM2SPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeFetchReadDataChannelM2SPreEventBase
        , public Event<SoCAXIBridgeFetchReadDataChannelM2SPreEvent> {
    public:
        SoCAXIBridgeFetchReadDataChannelM2SPreEvent(SoCAXIBridge*, FetchAXI4ReadDataChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Fetch Read Data Channel Master-to-Slave Post Event
    class SoCAXIBridgeFetchReadDataChannelM2SPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeFetchReadDataChannelM2SPostEventBase
        , public Event<SoCAXIBridgeFetchReadDataChannelM2SPostEvent> {
    public:
        SoCAXIBridgeFetchReadDataChannelM2SPostEvent(SoCAXIBridge*, const FetchAXI4ReadDataChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Fetch Read Data Channel Slave-to-Master Pre Event
    class SoCAXIBridgeFetchReadDataChannelS2MPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeFetchReadDataChannelS2MPreEventBase
        , public Event<SoCAXIBridgeFetchReadDataChannelS2MPreEvent> {
    public:
        SoCAXIBridgeFetchReadDataChannelS2MPreEvent(SoCAXIBridge*, FetchAXI4ReadDataChannelS2M& bundle) noexcept;
    };

    // SoC AXI Bridge Fetch Read Data Channel Slave-to-Master Post Event
    class SoCAXIBridgeFetchReadDataChannelS2MPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeFetchReadDataChannelS2MPostEventBase
        , public Event<SoCAXIBridgeFetchReadDataChannelS2MPostEvent> {
    public:
        SoCAXIBridgeFetchReadDataChannelS2MPostEvent(SoCAXIBridge*, const FetchAXI4ReadDataChannelS2M& bundle) noexcept;
    };


    // SoC AXI Bridge Data Read Address Channel Master-to-Slave Pre Event
    class SoCAXIBridgeDataReadAddressChannelM2SPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataReadAddressChannelM2SPreEventBase
        , public Event<SoCAXIBridgeDataReadAddressChannelM2SPreEvent> {
    public:
        SoCAXIBridgeDataReadAddressChannelM2SPreEvent(SoCAXIBridge*, DataAXI4ReadAddressChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Data Read Address Channel Master-to-Slave Post Event
    class SoCAXIBridgeDataReadAddressChannelM2SPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataReadAddressChannelM2SPostEventBase
        , public Event<SoCAXIBridgeDataReadAddressChannelM2SPostEvent> {
    public:
        SoCAXIBridgeDataReadAddressChannelM2SPostEvent(SoCAXIBridge*, const DataAXI4ReadAddressChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Data Read Address Channel Slave-to-Master Pre Event
    class SoCAXIBridgeDataReadAddressChannelS2MPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataReadAddressChannelS2MPreEventBase
        , public Event<SoCAXIBridgeDataReadAddressChannelS2MPreEvent> {
    public:
        SoCAXIBridgeDataReadAddressChannelS2MPreEvent(SoCAXIBridge*, DataAXI4ReadAddressChannelS2M& bundle) noexcept;
    };

    // SoC AXI Bridge Data Read Address Channel Slave-to-Master Post Event
    class SoCAXIBridgeDataReadAddressChannelS2MPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataReadAddressChannelS2MPostEventBase
        , public Event<SoCAXIBridgeDataReadAddressChannelS2MPostEvent> {
    public:
        SoCAXIBridgeDataReadAddressChannelS2MPostEvent(SoCAXIBridge*, const DataAXI4ReadAddressChannelS2M& bundle) noexcept;
    };


    // SoC AXI Bridge Data Read Data Channel Master-to-Slave Pre Event
    class SoCAXIBridgeDataReadDataChannelM2SPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataReadDataChannelM2SPreEventBase
        , public Event<SoCAXIBridgeDataReadDataChannelM2SPreEvent> {
    public:
        SoCAXIBridgeDataReadDataChannelM2SPreEvent(SoCAXIBridge*, DataAXI4ReadDataChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Data Read Data Channel Master-to-Slave Post Event
    class SoCAXIBridgeDataReadDataChannelM2SPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataReadDataChannelM2SPostEventBase
        , public Event<SoCAXIBridgeDataReadDataChannelM2SPostEvent> {
    public:
        SoCAXIBridgeDataReadDataChannelM2SPostEvent(SoCAXIBridge*, const DataAXI4ReadDataChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Data Read Data Channel Slave-to-Master Pre Event
    class SoCAXIBridgeDataReadDataChannelS2MPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataReadDataChannelS2MPreEventBase
        , public Event<SoCAXIBridgeDataReadDataChannelS2MPreEvent> {
    public:
        SoCAXIBridgeDataReadDataChannelS2MPreEvent(SoCAXIBridge*, DataAXI4ReadDataChannelS2M& bundle) noexcept;
    };

    // SoC AXI Bridge Data Read Data Channel Slave-to-Master Post Event
    class SoCAXIBridgeDataReadDataChannelS2MPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataReadDataChannelS2MPostEventBase
        , public Event<SoCAXIBridgeDataReadDataChannelS2MPostEvent> {
    public:
        SoCAXIBridgeDataReadDataChannelS2MPostEvent(SoCAXIBridge*, const DataAXI4ReadDataChannelS2M& bundle) noexcept;
    };


    // SoC AXI Bridge Data Write Address Channel Master-to-Slave Pre Event
    class SoCAXIBridgeDataWriteAddressChannelM2SPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteAddressChannelM2SPreEventBase
        , public Event<SoCAXIBridgeDataWriteAddressChannelM2SPreEvent> {
    public:
        SoCAXIBridgeDataWriteAddressChannelM2SPreEvent(SoCAXIBridge*, DataAXI4WriteAddressChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Data Write Address Channel Master-to-Slave Post Event
    class SoCAXIBridgeDataWriteAddressChannelM2SPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteAddressChannelM2SPostEventBase
        , public Event<SoCAXIBridgeDataWriteAddressChannelM2SPostEvent> {
    public:
        SoCAXIBridgeDataWriteAddressChannelM2SPostEvent(SoCAXIBridge*, const DataAXI4WriteAddressChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Data Write Address Channel Slave-to-Master Pre Event
    class SoCAXIBridgeDataWriteAddressChannelS2MPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteAddressChannelS2MPreEventBase
        , public Event<SoCAXIBridgeDataWriteAddressChannelS2MPreEvent> {
    public:
        SoCAXIBridgeDataWriteAddressChannelS2MPreEvent(SoCAXIBridge*, DataAXI4WriteAddressChannelS2M& bundle) noexcept;
    };

    // SoC AXI Bridge Data Write Address Channel Slave-to-Master Post Event
    class SoCAXIBridgeDataWriteAddressChannelS2MPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteAddressChannelS2MPostEventBase
        , public Event<SoCAXIBridgeDataWriteAddressChannelS2MPostEvent> {
    public:
        SoCAXIBridgeDataWriteAddressChannelS2MPostEvent(SoCAXIBridge*, const DataAXI4WriteAddressChannelS2M& bundle) noexcept;
    };


    // SoC AXI Bridge Data Write Data Channel Master-to-Slave Pre Event
    class SoCAXIBridgeDataWriteDataChannelM2SPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteDataChannelM2SPreEventBase
        , public Event<SoCAXIBridgeDataWriteDataChannelM2SPreEvent> {
    public:
        SoCAXIBridgeDataWriteDataChannelM2SPreEvent(SoCAXIBridge*, DataAXI4WriteDataChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Data Write Data Channel Master-to-Slave Post Event
    class SoCAXIBridgeDataWriteDataChannelM2SPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteDataChannelM2SPostEventBase
        , public Event<SoCAXIBridgeDataWriteDataChannelM2SPostEvent> {
    public:
        SoCAXIBridgeDataWriteDataChannelM2SPostEvent(SoCAXIBridge*, const DataAXI4WriteDataChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Data Write Data Channel Slave-to-Master Pre Event
    class SoCAXIBridgeDataWriteDataChannelS2MPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteDataChannelS2MPreEventBase
        , public Event<SoCAXIBridgeDataWriteDataChannelS2MPreEvent> {
    public:
        SoCAXIBridgeDataWriteDataChannelS2MPreEvent(SoCAXIBridge*, DataAXI4WriteDataChannelS2M& bundle) noexcept;
    };

    // SoC AXI Bridge Data Write Data Channel Slave-to-Master Post Event
    class SoCAXIBridgeDataWriteDataChannelS2MPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteDataChannelS2MPostEventBase
        , public Event<SoCAXIBridgeDataWriteDataChannelS2MPostEvent> {
    public:
        SoCAXIBridgeDataWriteDataChannelS2MPostEvent(SoCAXIBridge*, const DataAXI4WriteDataChannelS2M& bundle) noexcept;
    };


    // SoC AXI Bridge Data Write Response Channel Master-to-Slave Pre Event
    class SoCAXIBridgeDataWriteResponseChannelM2SPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteResponseChannelM2SPreEventBase
        , public Event<SoCAXIBridgeDataWriteResponseChannelM2SPreEvent> {
    public:
        SoCAXIBridgeDataWriteResponseChannelM2SPreEvent(SoCAXIBridge*, DataAXI4WriteResponseChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Data Write Response Channel Master-to-Slave Post Event
    class SoCAXIBridgeDataWriteResponseChannelM2SPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteResponseChannelM2SPostEventBase
        , public Event<SoCAXIBridgeDataWriteResponseChannelM2SPostEvent> {
    public:
        SoCAXIBridgeDataWriteResponseChannelM2SPostEvent(SoCAXIBridge*, const DataAXI4WriteResponseChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Data Write Response Channel Slave-to-Master Pre Event
    class SoCAXIBridgeDataWriteResponseChannelS2MPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteResponseChannelS2MPreEventBase
        , public Event<SoCAXIBridgeDataWriteResponseChannelS2MPreEvent> {
    public:
        SoCAXIBridgeDataWriteResponseChannelS2MPreEvent(SoCAXIBridge*, DataAXI4WriteResponseChannelS2M& bundle) noexcept;
    };

    // SoC AXI Bridge Data Write Response Channel Slave-to-Master Post Event
    class SoCAXIBridgeDataWriteResponseChannelS2MPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteResponseChannelS2MPostEventBase
        , public Event<SoCAXIBridgeDataWriteResponseChannelS2MPostEvent> {
    public:
        SoCAXIBridgeDataWriteResponseChannelS2MPostEvent(SoCAXIBridge*, const DataAXI4WriteResponseChannelS2M& bundle) noexcept;
    };


    
    // SoC AXI Bridge Fetch Read Address Accepted Pre Event
    class SoCAXIBridgeFetchReadAddressAcceptedPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeFetchReadAddressChannelM2SPreEventBase
        , public Event<SoCAXIBridgeFetchReadAddressAcceptedPreEvent> {
    public:
        SoCAXIBridgeFetchReadAddressAcceptedPreEvent(SoCAXIBridge*, FetchAXI4ReadAddressChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Fetch Read Address Accepted Post Event
    class SoCAXIBridgeFetchReadAddressAcceptedPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeFetchReadAddressChannelM2SPostEventBase
        , public Event<SoCAXIBridgeFetchReadAddressAcceptedPostEvent> {
    public:
        SoCAXIBridgeFetchReadAddressAcceptedPostEvent(SoCAXIBridge*, const FetchAXI4ReadAddressChannelM2S& bundle) noexcept;
    };


    // SoC AXI Bridge Fetch Read Data Accepted Pre Event *unused*
    /*
    class SoCAXIBridgeFetchReadDataAcceptedPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeFetchReadDataChannelS2MPreEventBase
        , public Event<SoCAXIBridgeFetchReadDataAcceptedPreEvent> {
    public:
        SoCAXIBridgeFetchReadDataAcceptedPreEvent(SoCAXIBridge*, FetchAXI4ReadDataChannelS2M& bundle) noexcept;
    };
    */

    // SoC AXI Bridge Fetch Read Data Accepted Post Event
    class SoCAXIBridgeFetchReadDataAcceptedPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeFetchReadDataChannelS2MPostEventBase
        , public Event<SoCAXIBridgeFetchReadDataAcceptedPostEvent> {
    public:
        SoCAXIBridgeFetchReadDataAcceptedPostEvent(SoCAXIBridge*, const FetchAXI4ReadDataChannelS2M& bundle) noexcept;
    };



    // SoC AXI Bridge Data Read Address Accepted Pre Event
    class SoCAXIBridgeDataReadAddressAcceptedPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataReadAddressChannelM2SPreEventBase
        , public Event<SoCAXIBridgeDataReadAddressAcceptedPreEvent> {
    public:
        SoCAXIBridgeDataReadAddressAcceptedPreEvent(SoCAXIBridge*, DataAXI4ReadAddressChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Data Read Address Accepted Post Event
    class SoCAXIBridgeDataReadAddressAcceptedPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataReadAddressChannelM2SPostEventBase
        , public Event<SoCAXIBridgeDataReadAddressAcceptedPostEvent> {
    public:
        SoCAXIBridgeDataReadAddressAcceptedPostEvent(SoCAXIBridge*, const DataAXI4ReadAddressChannelM2S& bundle) noexcept;
    };


    // SoC AXI Bridge Data Read Data Accepted Pre Event *unused*
    /*
    class SoCAXIBridgeDataReadDataAcceptedPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataReadDataChannelS2MPreEventBase
        , public Event<SoCAXIBridgeDataReadDataAcceptedPreEvent> {
    public:
        SoCAXIBridgeDataReadDataAcceptedPreEvent(SoCAXIBridge*, DataAXI4ReadDataChannelS2M& bundle) noexcept;
    };
    */

    // SoC AXI Bridge Data Read Data Accepted Post Event
    class SoCAXIBridgeDataReadDataAcceptedPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataReadDataChannelS2MPostEventBase
        , public Event<SoCAXIBridgeDataReadDataAcceptedPostEvent> {
    public:
        SoCAXIBridgeDataReadDataAcceptedPostEvent(SoCAXIBridge*, const DataAXI4ReadDataChannelS2M& bundle) noexcept;
    };


    // SoC AXI Bridge Data Write Address Accepted Pre Event
    class SoCAXIBridgeDataWriteAddressAcceptedPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteAddressChannelM2SPreEventBase
        , public Event<SoCAXIBridgeDataWriteAddressAcceptedPreEvent> {
    public:
        SoCAXIBridgeDataWriteAddressAcceptedPreEvent(SoCAXIBridge*, DataAXI4WriteAddressChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Data Write Address Accepted Post Event
    class SoCAXIBridgeDataWriteAddressAcceptedPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteAddressChannelM2SPostEventBase
        , public Event<SoCAXIBridgeDataWriteAddressAcceptedPostEvent> {
    public:
        SoCAXIBridgeDataWriteAddressAcceptedPostEvent(SoCAXIBridge*, const DataAXI4WriteAddressChannelM2S& bundle) noexcept;
    };


    // SoC AXI Bridge Data Write Data Accepted Pre Event
    class SoCAXIBridgeDataWriteDataAcceptedPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteDataChannelM2SPreEventBase
        , public Event<SoCAXIBridgeDataWriteDataAcceptedPreEvent> {
    public:
        SoCAXIBridgeDataWriteDataAcceptedPreEvent(SoCAXIBridge*, DataAXI4WriteDataChannelM2S& bundle) noexcept;
    };

    // SoC AXI Bridge Data Write Data Accepted Post Event
    class SoCAXIBridgeDataWriteDataAcceptedPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteDataChannelM2SPostEventBase
        , public Event<SoCAXIBridgeDataWriteDataAcceptedPostEvent> {
    public:
        SoCAXIBridgeDataWriteDataAcceptedPostEvent(SoCAXIBridge*, const DataAXI4WriteDataChannelM2S& bundle) noexcept;
    };


    // SoC AXI Bridge Data Write Response Accepted Pre Event *unused*
    /*
    class SoCAXIBridgeDataWriteResponseAcceptedPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteResponseChannelS2MPreEventBase
        , public Event<SoCAXIBridgeDataWriteResponseAcceptedPreEvent> {
    public:
        SoCAXIBridgeDataWriteResponseAcceptedPreEvent(SoCAXIBridge*, DataAXI4WriteResponseChannelS2M& bundle) noexcept;
    };
    */

    // SoC AXI Bridge Data Write Response Accepted Post Event
    class SoCAXIBridgeDataWriteResponseAcceptedPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeDataWriteResponseChannelS2MPostEventBase
        , public Event<SoCAXIBridgeDataWriteResponseAcceptedPostEvent> {
    public:
        SoCAXIBridgeDataWriteResponseAcceptedPostEvent(SoCAXIBridge*, const DataAXI4WriteResponseChannelS2M& bundle) noexcept;
    };



    // SoC AXI Bridge MMU Pre Write Pre Event Base
    class SoCAXIBridgeMMUPreWritePreEventBase {
    private:
        addr_t&         address;
        LA32MOPWidth&   width;
        memdata_t&      data;

    public:
        SoCAXIBridgeMMUPreWritePreEventBase(addr_t& address, LA32MOPWidth& width, memdata_t& data) noexcept;

        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;
        memdata_t       GetData() const noexcept;

        void            SetAddress(addr_t addr) noexcept;
        void            SetWidth(LA32MOPWidth width) noexcept;
        void            SetData(memdata_t data) noexcept;
    };

    // SoC AXI Bridge MMU Pre Write Post Event Base
    class SoCAXIBridgeMMUPreWritePostEventBase {
    private:
        addr_t          address;
        LA32MOPWidth    width;
        memdata_t       data;

    public:
        SoCAXIBridgeMMUPreWritePostEventBase(addr_t address, LA32MOPWidth width, memdata_t data) noexcept;

        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;
        memdata_t       GetData() const noexcept;
    };

    // SoC AXI Bridge MMU Post Write Pre Event Base
    class SoCAXIBridgeMMUPostWritePreEventBase {
    private:
        addr_t          address;
        LA32MOPWidth    width;
        memdata_t       data;
        LA32MOPOutcome& outcome;

    public:
        SoCAXIBridgeMMUPostWritePreEventBase(addr_t address, LA32MOPWidth width, memdata_t data, LA32MOPOutcome& outcome) noexcept;

        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;
        memdata_t       GetData() const noexcept;
        LA32MOPOutcome  GetOutcome() const noexcept;

        void            SetOutcome(LA32MOPOutcome outcome) noexcept;
    };

    // SoC AXI Bridge MMU Post Write Post Event Base
    class SoCAXIBridgeMMUPostWritePostEventBase {
    private:
        addr_t          address;
        LA32MOPWidth    width;
        memdata_t       data;
        LA32MOPOutcome  outcome;

    public:
        SoCAXIBridgeMMUPostWritePostEventBase(addr_t address, LA32MOPWidth width, memdata_t data, LA32MOPOutcome outcome) noexcept;

        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;
        memdata_t       GetData() const noexcept;
        LA32MOPOutcome  GetOutcome() const noexcept;
    };


    // SoC AXI Bridge MMU Pre Read Pre Event Base
    class SoCAXIBridgeMMUPreReadPreEventBase {
    private:
        addr_t&         address;
        LA32MOPWidth&   width;

    public:
        SoCAXIBridgeMMUPreReadPreEventBase(addr_t& address, LA32MOPWidth& width) noexcept;

        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;

        void            SetAddress(addr_t addr) noexcept;
        void            SetWidth(LA32MOPWidth width) noexcept;
    };

    // SoC AXI Bridge MMU Pre Read Post Event Base
    class SoCAXIBridgeMMUPreReadPostEventBase {
    private:
        addr_t          address;
        LA32MOPWidth    width;

    public:
        SoCAXIBridgeMMUPreReadPostEventBase(addr_t address, LA32MOPWidth width) noexcept;

        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;
    };

    // SoC AXI Bridge MMU Post Read Pre Event Base
    class SoCAXIBridgeMMUPostReadPreEventBase {
    private:
        addr_t          address;
        LA32MOPWidth    width;
        memdata_t&      data;
        LA32MOPOutcome& outcome;

    public:
        SoCAXIBridgeMMUPostReadPreEventBase(addr_t address, LA32MOPWidth width, memdata_t& data, LA32MOPOutcome& outcome) noexcept;

        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;
        memdata_t       GetData() const noexcept;
        LA32MOPOutcome  GetOutcome() const noexcept;

        void            SetData(memdata_t data) noexcept;
        void            SetOutcome(LA32MOPOutcome outcome) noexcept;
    };

    // SoC AXI Bridge MMU Post Read Post Event Base
    class SoCAXIBridgeMMUPostReadPostEventBase {
    private:
        addr_t          address;
        LA32MOPWidth    width;
        memdata_t       data;
        LA32MOPOutcome  outcome;

    public:
        SoCAXIBridgeMMUPostReadPostEventBase(addr_t address, LA32MOPWidth width, memdata_t data, LA32MOPOutcome outcome) noexcept;

        addr_t          GetAddress() const noexcept;
        LA32MOPWidth    GetWidth() const noexcept;
        memdata_t       GetData() const noexcept;
        LA32MOPOutcome  GetOutcome() const noexcept;
    };


    // SoC AXI Bridge Fetch MMU Pre Write Pre Event
    class SoCAXIBridgeFetchMMUPreWritePreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeMMUPreWritePreEventBase
        , public Event<SoCAXIBridgeFetchMMUPreWritePreEvent>
        , public CancellableEvent {
    public:
        SoCAXIBridgeFetchMMUPreWritePreEvent(SoCAXIBridge*, addr_t& address, LA32MOPWidth& width, memdata_t& data) noexcept;
    };

    // SoC AXI Bridge Fetch MMU Pre Write Post Event
    class SoCAXIBridgeFetchMMUPreWritePostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeMMUPreWritePostEventBase
        , public Event<SoCAXIBridgeFetchMMUPreWritePostEvent> {
    public:
        SoCAXIBridgeFetchMMUPreWritePostEvent(SoCAXIBridge*, addr_t address, LA32MOPWidth width, memdata_t data) noexcept;
    };

    // SoC AXI Bridge Fetch MMU Post Write Pre Event
    class SoCAXIBridgeFetchMMUPostWritePreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeMMUPostWritePreEventBase
        , public Event<SoCAXIBridgeFetchMMUPostWritePreEvent>
        , public CancellableEvent {
    public:
        SoCAXIBridgeFetchMMUPostWritePreEvent(SoCAXIBridge*, addr_t address, LA32MOPWidth width, memdata_t data, LA32MOPOutcome& outcome) noexcept;
    };

    // SoC AXI Bridge Fetch MMU Post Write Post Event
    class SoCAXIBridgeFetchMMUPostWritePostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeMMUPostWritePostEventBase
        , public Event<SoCAXIBridgeFetchMMUPostWritePostEvent> {
    public:
        SoCAXIBridgeFetchMMUPostWritePostEvent(SoCAXIBridge*, addr_t address, LA32MOPWidth width, memdata_t data, LA32MOPOutcome outcome) noexcept;
    };


    // SoC AXI Bridge Fetch MMU Pre Read Pre Event
    class SoCAXIBridgeFetchMMUPreReadPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeMMUPreReadPreEventBase
        , public Event<SoCAXIBridgeFetchMMUPreReadPreEvent>
        , public CancellableEvent {
    public:
        SoCAXIBridgeFetchMMUPreReadPreEvent(SoCAXIBridge*, addr_t& address, LA32MOPWidth& width) noexcept;
    };

    // SoC AXI Bridge Fetch MMU Pre Read Post Event
    class SoCAXIBridgeFetchMMUPreReadPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeMMUPreReadPostEventBase
        , public Event<SoCAXIBridgeFetchMMUPreReadPostEvent> {
    public:
        SoCAXIBridgeFetchMMUPreReadPostEvent(SoCAXIBridge*, addr_t address, LA32MOPWidth width) noexcept;
    };

    // SoC AXI Bridge Fetch MMU Post Read Pre Event
    class SoCAXIBridgeFetchMMUPostReadPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeMMUPostReadPreEventBase
        , public Event<SoCAXIBridgeFetchMMUPostReadPreEvent>
        , public CancellableEvent {
    public:
        SoCAXIBridgeFetchMMUPostReadPreEvent(SoCAXIBridge*, addr_t address, LA32MOPWidth width, memdata_t& data, LA32MOPOutcome& outcome) noexcept;
    };

    // SoC AXI Bridge Fetch MMU Post Read Post Event
    class SoCAXIBridgeFetchMMUPostReadPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeMMUPostReadPostEventBase
        , public Event<SoCAXIBridgeFetchMMUPostReadPostEvent> {
    public:
        SoCAXIBridgeFetchMMUPostReadPostEvent(SoCAXIBridge*, addr_t address, LA32MOPWidth width, memdata_t data, LA32MOPOutcome outcome) noexcept;
    };


    // SoC AXI Bridge Data MMU Pre Write Pre Event
    class SoCAXIBridgeDataMMUPreWritePreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeMMUPreWritePreEventBase
        , public Event<SoCAXIBridgeDataMMUPreWritePreEvent>
        , public CancellableEvent {
    public:
        SoCAXIBridgeDataMMUPreWritePreEvent(SoCAXIBridge*, addr_t& address, LA32MOPWidth& width, memdata_t& data) noexcept;
    };

    // SoC AXI Bridge Data MMU Pre Write Post Event
    class SoCAXIBridgeDataMMUPreWritePostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeMMUPreWritePostEventBase
        , public Event<SoCAXIBridgeDataMMUPreWritePostEvent> {
    public:
        SoCAXIBridgeDataMMUPreWritePostEvent(SoCAXIBridge*, addr_t address, LA32MOPWidth width, memdata_t data) noexcept;
    };

    // SoC AXI Bridge Data MMU Post Write Pre Event
    class SoCAXIBridgeDataMMUPostWritePreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeMMUPostWritePreEventBase
        , public Event<SoCAXIBridgeDataMMUPostWritePreEvent>
        , public CancellableEvent {
    public:
        SoCAXIBridgeDataMMUPostWritePreEvent(SoCAXIBridge*, addr_t address, LA32MOPWidth width, memdata_t data, LA32MOPOutcome& outcome) noexcept;
    };

    // SoC AXI Bridge Data MMU Post Write Post Event
    class SoCAXIBridgeDataMMUPostWritePostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeMMUPostWritePostEventBase
        , public Event<SoCAXIBridgeDataMMUPostWritePostEvent> {
    public:
        SoCAXIBridgeDataMMUPostWritePostEvent(SoCAXIBridge*, addr_t address, LA32MOPWidth width, memdata_t data, LA32MOPOutcome outcome) noexcept;
    };


    // SoC AXI Bridge Data MMU Pre Read Pre Event
    class SoCAXIBridgeDataMMUPreReadPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeMMUPreReadPreEventBase
        , public Event<SoCAXIBridgeDataMMUPreReadPreEvent>
        , public CancellableEvent {
    public:
        SoCAXIBridgeDataMMUPreReadPreEvent(SoCAXIBridge*, addr_t& address, LA32MOPWidth& width) noexcept;
    };

    // SoC AXI Bridge Data MMU Pre Read Post Event
    class SoCAXIBridgeDataMMUPreReadPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeMMUPreReadPostEventBase
        , public Event<SoCAXIBridgeDataMMUPreReadPostEvent> {
    public:
        SoCAXIBridgeDataMMUPreReadPostEvent(SoCAXIBridge*, addr_t address, LA32MOPWidth width) noexcept;
    };

    // SoC AXI Bridge Data MMU Post Read Pre Event
    class SoCAXIBridgeDataMMUPostReadPreEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeMMUPostReadPreEventBase
        , public Event<SoCAXIBridgeDataMMUPostReadPreEvent>
        , public CancellableEvent {
    public:
        SoCAXIBridgeDataMMUPostReadPreEvent(SoCAXIBridge*, addr_t address, LA32MOPWidth width, memdata_t& data, LA32MOPOutcome& outcome) noexcept;
    };

    // SoC AXI Bridge Data MMU Post Read Post Event
    class SoCAXIBridgeDataMMUPostReadPostEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeMMUPostReadPostEventBase
        , public Event<SoCAXIBridgeDataMMUPostReadPostEvent> {
    public:
        SoCAXIBridgeDataMMUPostReadPostEvent(SoCAXIBridge*, addr_t address, LA32MOPWidth width, memdata_t data, LA32MOPOutcome outcome) noexcept;
    };



    // SoC AXI Bridge Error Event Base
    class SoCAXIBridgeErrorEventBase {
    public:
        enum class ErrorType {
            READ_MOP_NOT_SUCCESS = 0,
            WRITE_MOP_NOT_SUCCESS,
            WRITE_OVERFLOW,
            WRITE_UNDERFLOW
        };

    private:
        uint4_t     transaction_id;
        ErrorType   type;

    public:
        SoCAXIBridgeErrorEventBase(uint4_t transaction_id, ErrorType type) noexcept;

        uint4_t     GetTransactionID() const noexcept;
        ErrorType   GetType() const noexcept;
    };


    // SoC AXI Bridge Fetch Error Event
    class SoCAXIBridgeFetchErrorEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeErrorEventBase
        , public Event<SoCAXIBridgeFetchErrorEvent> {
    public:
        SoCAXIBridgeFetchErrorEvent(SoCAXIBridge*, uint4_t transaction_id, ErrorType type) noexcept;
    };

    // SoC AXI Bridge Data Error Event
    class SoCAXIBridgeDataErrorEvent
        : public SoCAXIBridgeEventBase
        , public SoCAXIBridgeErrorEventBase
        , public Event<SoCAXIBridgeDataErrorEvent> {
    public:
        SoCAXIBridgeDataErrorEvent(SoCAXIBridge*, uint4_t transaction_id, ErrorType type) noexcept;
    };
}


#endif
