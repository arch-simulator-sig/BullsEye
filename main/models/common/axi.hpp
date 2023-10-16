#pragma once
//
// AXI Channel Structures
//
//

#include <cstdint>

#include "common/nonstdint.hpp"


#define     AXI4_AXSIZE_1B              0b000
#define     AXI4_AXSIZE_2B              0b001
#define     AXI4_AXSIZE_4B              0b010
#define     AXI4_AXSIZE_8B              0b011
#define     AXI4_AXSIZE_16B             0b100
#define     AXI4_AXSIZE_32B             0b101
#define     AXI4_AXSIZE_64B             0b110
#define     AXI4_AXSIZE_128B            0b111

#define     AXI4_AXBURST_FIXED          0b00
#define     AXI4_AXBURST_INCR           0b01
#define     AXI4_AXBURST_WRAP           0b10

#define     AXI4_BRESP_OKAY             0b000
#define     AXI4_BRESP_EXOKAY           0b001
#define     AXI4_BRESP_SLVERR           0b010
#define     AXI4_BRESP_DECERR           0b011
#define     AXI4_BRESP_DEFER            0b100
#define     AXI4_BRESP_TRANSFAULT       0b101
#define     AXI4_BRESP_UNSUPPORTED      0b111

#define     AXI4_RRESP_OKAY             0b000
#define     AXI4_RRESP_EXOKAY           0b001
#define     AXI4_RRESP_SLVERR           0b010
#define     AXI4_RRESP_DECERR           0b011
#define     AXI4_RRESP_PREFETCHED       0b100
#define     AXI4_RRESP_TRANSFAULT       0b101
#define     AXI4_RRESP_OKAYDIRTY        0b110


namespace BullsEye {

    // AXI-4 attributes
    namespace AXI4::Attributes {

        //
        static constexpr uint8_t AXSIZE_1B          = AXI4_AXSIZE_1B;
        static constexpr uint8_t AXSIZE_2B          = AXI4_AXSIZE_2B;
        static constexpr uint8_t AXSIZE_4B          = AXI4_AXSIZE_4B;
        static constexpr uint8_t AXSIZE_8B          = AXI4_AXSIZE_8B;
        static constexpr uint8_t AXSIZE_16B         = AXI4_AXSIZE_16B;
        static constexpr uint8_t AXSIZE_32B         = AXI4_AXSIZE_32B;
        static constexpr uint8_t AXSIZE_64B         = AXI4_AXSIZE_64B;
        static constexpr uint8_t AXSIZE_128B        = AXI4_AXSIZE_128B;

        static constexpr uint8_t AXBURST_FIXED      = AXI4_AXBURST_FIXED;
        static constexpr uint8_t AXBURST_INCR       = AXI4_AXBURST_INCR;
        static constexpr uint8_t AXBURST_WRAP       = AXI4_AXBURST_WRAP;

        static constexpr uint8_t BRESP_OKAY         = AXI4_BRESP_OKAY;
        static constexpr uint8_t BRESP_EXOKAY       = AXI4_BRESP_EXOKAY;
        static constexpr uint8_t BRESP_SLVERR       = AXI4_BRESP_SLVERR;
        static constexpr uint8_t BRESP_DECERR       = AXI4_BRESP_DECERR;
        static constexpr uint8_t BRESP_DEFER        = AXI4_BRESP_DEFER;
        static constexpr uint8_t BRESP_TRANSFAULT   = AXI4_BRESP_TRANSFAULT;
        static constexpr uint8_t BRESP_UNSUPPORTED  = AXI4_BRESP_UNSUPPORTED;

        static constexpr uint8_t RRESP_OKAY         = AXI4_RRESP_OKAY;
        static constexpr uint8_t RRESP_EXOKAY       = AXI4_RRESP_EXOKAY;
        static constexpr uint8_t RRESP_SLVERR       = AXI4_RRESP_SLVERR;
        static constexpr uint8_t RRESP_DECERR       = AXI4_RRESP_DECERR;
        static constexpr uint8_t RRESP_PREFETCHED   = AXI4_RRESP_PREFETCHED;
        static constexpr uint8_t RRESP_TRANSFAULT   = AXI4_RRESP_TRANSFAULT;
        static constexpr uint8_t RRESP_OKAYDIRTY    = AXI4_RRESP_OKAYDIRTY;

        //
        template<uint8_t _Val> requires (_Val > 0)
        struct AXLEN_t {
            static constexpr uint8_t value = _Val - 1;
        };

        template<uint8_t _Val>
        static constexpr uint8_t AXLEN = AXLEN_t<_Val>::value;

        //
        template<uint8_t _Val>
        struct AXSIZE_t {
            static constexpr uint8_t value {/*BRACE required by GCC 11 on C++20, GCC is Wrong!*/};
        };

        template<uint8_t _Val>
        static constexpr uint8_t AXSIZE = AXSIZE_t<_Val>::value;

        template<> struct AXSIZE_t<1  > { static constexpr uint8_t value    = AXI4_AXSIZE_1B;   };
        template<> struct AXSIZE_t<2  > { static constexpr uint8_t value    = AXI4_AXSIZE_2B;   };
        template<> struct AXSIZE_t<4  > { static constexpr uint8_t value    = AXI4_AXSIZE_4B;   };
        template<> struct AXSIZE_t<8  > { static constexpr uint8_t value    = AXI4_AXSIZE_8B;   };
        template<> struct AXSIZE_t<16 > { static constexpr uint8_t value    = AXI4_AXSIZE_16B;  };
        template<> struct AXSIZE_t<32 > { static constexpr uint8_t value    = AXI4_AXSIZE_32B;  };
        template<> struct AXSIZE_t<64 > { static constexpr uint8_t value    = AXI4_AXSIZE_64B;  };
        template<> struct AXSIZE_t<128> { static constexpr uint8_t value    = AXI4_AXSIZE_128B; };
    };


    // AXI-4 Read Address Channel structs
    namespace AXI4 {

        // Type definition of AXI-4 Attribute AxSIZE
        using attr_size_t           = truncated_uint8_t<3>; 

        // Type definition of AXI-4 Attribute AxBURST
        using attr_burst_t          = truncated_uint8_t<2>;

        // Type definition of AXI-4 Attribute AxLEN
        using attr_len_t            = uint8_t;


        // Type definition of AXI-4 Attribute BRESP
        using attr_bresp_t          = truncated_uint8_t<3>;

        // Type definition of AXI-4 Attribute RRESP
        using attr_rresp_t          = truncated_uint8_t<3>;


        // Read Address Channel bundle of Master to Slave
        template<class arid_t = uint8_t, class araddr_t = uint64_t, class aruser_t = uint8_t>
        struct ReadAddressChannelM2S {
            arid_t          arid;
            araddr_t        araddr;
            attr_len_t      arlen;
            attr_size_t     arsize;
            attr_burst_t    arburst;
            aruser_t        aruser;
            uint1_t         arvalid;
        };

        // Read Address Channel bundle of Slave to Master
        struct ReadAddressChannelS2M {
            uint1_t         arready;
        };


        // Read Data Channel bundle of Master to Slave
        struct ReadDataChannelM2S {
            uint1_t         rready;
        };

        // Read Data Channel bundle of Slave to Master
        template<class rid_t = uint8_t, class rdata_t = uint64_t>
        struct ReadDataChannelS2M {
            rid_t           rid;
            rdata_t         rdata;
            attr_rresp_t    rresp;
            uint1_t         rlast;
            uint1_t         rvalid;
        };


        // Write Address Channel bundle of Master to Slave
        template<class awid_t = uint8_t, class awaddr_t = uint64_t, class awuser_t = uint8_t>
        struct WriteAddressChannelM2S {
            awid_t          awid;
            awaddr_t        awaddr;
            attr_len_t      awlen;
            attr_size_t     awsize;
            attr_burst_t    awburst;
            awuser_t        awuser;
            uint1_t         awvalid;
        };

        // Write Address Channel bundle of Slave to Master
        struct WriteAddressChannelS2M {
            uint1_t         awready;
        };


        // Write Data Channel bundle of Master to Slave
        template<class wdata_t = uint64_t, class wstrb_t = uint8_t>
        struct WriteDataChannelM2S {
            wdata_t         wdata;
            wstrb_t         wstrb;
            uint1_t         wlast;
            uint1_t         wvalid;
        };

        // Write Data Channel bundle of Slave to Master
        struct WriteDataChannelS2M {
            uint1_t         wready;
        };


        // Write Response Channel bundle of Master to Slave
        struct WriteResponseChannelM2S {
            uint1_t         bready;
        };

        // Write Response Channel bundle of Slave to Master
        template<class bid_t = uint8_t>
        struct WriteResponseChannelS2M {
            bid_t           bid;
            attr_bresp_t    bresp;
            uint1_t         bvalid;
        };
    }

}
