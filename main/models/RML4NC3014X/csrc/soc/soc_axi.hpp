#pragma once
//
//  AXI Bridge to NSCSCC2023 SoC for Verilated emulation
//
//

#ifndef __HEADER_DS232__SOC_AXI
#define __HEADER_DS232__SOC_AXI


#include <cstdint>
#include <bitset>

#include "autoinclude.h"

#include AUTOINC_BE_COMMON(amba/axi4.hpp)

#include AUTOINC_BE_N1_SOC_LA32(soc.hpp)


namespace BullsEye::Draconids3014 {

    // AXI-4 Fetch Channel Definition
    using FetchAXI4ReadAddressChannelM2S    = AXI4::ReadAddressChannelM2S<uint4_t, uint32_t, uint1_t>;

    using FetchAXI4ReadAddressChannelS2M    = AXI4::ReadAddressChannelS2M;

    using FetchAXI4ReadDataChannelM2S       = AXI4::ReadDataChannelM2S;

    using FetchAXI4ReadDataChannelS2M       = AXI4::ReadDataChannelS2M<uint4_t, uint32_t>;

    // AXI-4 Data Channel Definition
    using DataAXI4ReadAddressChannelM2S     = AXI4::ReadAddressChannelM2S<uint4_t, uint32_t, uint1_t>;

    using DataAXI4ReadAddressChannelS2M     = AXI4::ReadAddressChannelS2M;

    using DataAXI4ReadDataChannelM2S        = AXI4::ReadDataChannelM2S;

    using DataAXI4ReadDataChannelS2M        = AXI4::ReadDataChannelS2M<uint4_t, uint32_t>;

    using DataAXI4WriteAddressChannelM2S    = AXI4::WriteAddressChannelM2S<uint4_t, uint32_t, uint1_t>;

    using DataAXI4WriteAddressChannelS2M    = AXI4::WriteAddressChannelS2M;

    using DataAXI4WriteDataChannelM2S       = AXI4::WriteDataChannelM2S<uint32_t, std::bitset<4>>;

    using DataAXI4WriteDataChannelS2M       = AXI4::WriteDataChannelS2M;

    using DataAXI4WriteResponseChannelM2S   = AXI4::WriteResponseChannelM2S;

    using DataAXI4WriteResponseChannelS2M   = AXI4::WriteResponseChannelS2M<uint4_t>;

    
    //
    class SoCAXIBridgeDualChannel {
    private:
        enum class ReadState {
            AXI_READ_IDLE = 0,
            AXI_READ_ADDR,
            AXI_READ_DATA,
            AXI_READ_ERROR
        };

        enum class WriteState {
            AXI_WRITE_IDLE = 0,
            AXI_WRITE_ADDR,
            AXI_WRITE_DATA,
            AXI_WRITE_RESP,
            AXI_WRITE_ERROR
        };

    private:
        NSCSCCSingle::NSCSCC2023SoC*            soc;

        //
        unsigned int                            bus_clock_divider;

        //
        FetchAXI4ReadAddressChannelM2S          fetch_i_axi4ar;
        FetchAXI4ReadDataChannelM2S             fetch_i_axi4r;

        FetchAXI4ReadAddressChannelS2M          fetch_o_axi4ar;
        FetchAXI4ReadDataChannelS2M             fetch_o_axi4r;

        ReadState                               fetch_read_state;

        uint4_t                                 fetch_read_id;
        uint32_t                                fetch_read_addr;
        AXI4::attr_burst_t                      fetch_read_mode;
        AXI4::attr_size_t                       fetch_read_size;
        AXI4::attr_len_t                        fetch_read_length;
        bool                                    fetch_read_uncached;

        Jasse::LA32MOPWidth                     fetch_read_width;

        unsigned int                            fetch_read_trans_clock_divider;
        unsigned int                            fetch_read_trans_addr;
        unsigned int                            fetch_read_trans_readed;
        unsigned int                            fetch_read_trans_accepted;
        uint32_t                                fetch_read_trans_buffer[256];

        //
        DataAXI4ReadAddressChannelM2S           data_i_axi4ar;
        DataAXI4ReadDataChannelM2S              data_i_axi4r;

        DataAXI4ReadAddressChannelS2M           data_o_axi4ar;
        DataAXI4ReadDataChannelS2M              data_o_axi4r;

        ReadState                               data_read_state;

        uint4_t                                 data_read_id;
        uint32_t                                data_read_addr;
        AXI4::attr_burst_t                      data_read_mode;
        AXI4::attr_size_t                       data_read_size;
        AXI4::attr_len_t                        data_read_length;
        bool                                    data_read_uncached;

        Jasse::LA32MOPWidth                     data_read_width;

        unsigned int                            data_read_trans_clock_divider;
        unsigned int                            data_read_trans_addr;
        unsigned int                            data_read_trans_readed;
        unsigned int                            data_read_trans_accepted;
        uint32_t                                data_read_trans_buffer[256];

        //
        DataAXI4WriteAddressChannelM2S          data_i_axi4aw;
        DataAXI4WriteDataChannelM2S             data_i_axi4w;
        DataAXI4WriteResponseChannelM2S         data_i_axi4b;

        DataAXI4WriteAddressChannelS2M          data_o_axi4aw;
        DataAXI4WriteDataChannelS2M             data_o_axi4w;
        DataAXI4WriteResponseChannelS2M         data_o_axi4b;

        WriteState                              data_write_state;

        uint4_t                                 data_write_id;
        uint32_t                                data_write_addr;
        AXI4::attr_burst_t                      data_write_mode;
        AXI4::attr_size_t                       data_write_size;
        AXI4::attr_len_t                        data_write_length;
        bool                                    data_write_uncached;

        Jasse::LA32MOPWidth                     data_write_width;

        unsigned int                            data_write_trans_clock_divider;
        uint32_t                                data_write_trans_raddr;
        uint32_t                                data_write_trans_waddr;
        bool                                    data_write_trans_last;
        unsigned int                            data_write_trans_received;
        unsigned int                            data_write_trans_written;
        memdata_t                               data_write_trans_buffer[256];

        //
        bool                                    next_reset;

    private:
        static uint32_t                         _ConvertBusAddress(uint32_t addr, bool kseg1) noexcept;
        static Jasse::LA32MOPWidth              _ConvertWidth(AXI4::attr_size_t axsize) noexcept;
        static uint32_t                         _AlignBusData(memdata_t data, uint32_t addr, AXI4::attr_size_t axsize) noexcept;
        static memdata_t                        _UnalignBusData(uint32_t data, uint32_t addr, AXI4::attr_size_t axsize) noexcept;
        static uint32_t                         _IncrBusAddress(uint32_t addr, AXI4::attr_size_t axsize, AXI4::attr_burst_t axburst, AXI4::attr_len_t axlen) noexcept;

    private:
        void                                    _EvalFetchChannel() noexcept;
        void                                    _EvalDataChannel() noexcept;

    public:
        SoCAXIBridgeDualChannel(NSCSCCSingle::NSCSCC2023SoC* soc) noexcept;

        SoCAXIBridgeDualChannel(const SoCAXIBridgeDualChannel& obj) noexcept;
        SoCAXIBridgeDualChannel(SoCAXIBridgeDualChannel&& obj) noexcept;

        ~SoCAXIBridgeDualChannel() noexcept;

        //
        unsigned int                            GetBusClockDivider() const noexcept;
        void                                    SetBusClockDivider(unsigned int divider) noexcept;

        //
        void                                    NextFetchReadAddressM2S(const FetchAXI4ReadAddressChannelM2S& bundle) noexcept;
        void                                    NextFetchReadDataM2S(const FetchAXI4ReadDataChannelM2S& bundle) noexcept;

        void                                    NextDataReadAddressM2S(const DataAXI4ReadAddressChannelM2S& bundle) noexcept;
        void                                    NextDataReadDataM2S(const DataAXI4ReadDataChannelM2S& bundle) noexcept;

        void                                    NextDataWriteAddressM2S(const DataAXI4WriteAddressChannelM2S& bundle) noexcept;
        void                                    NextDataWriteDataM2S(const DataAXI4WriteDataChannelM2S& bundle) noexcept;
        void                                    NextDataWriteResponseM2S(const DataAXI4WriteResponseChannelM2S& bundle) noexcept;

        //
        const FetchAXI4ReadAddressChannelM2S&   GetNextFetchReadAddressM2S() const noexcept;
        const FetchAXI4ReadDataChannelM2S&      GetNextFetchReadDataM2S() const noexcept;

        const DataAXI4ReadAddressChannelM2S&    GetNextDataReadAddressM2S() const noexcept;
        const DataAXI4ReadDataChannelM2S&       GetNextDataReadDataM2S() const noexcept;

        const DataAXI4WriteAddressChannelM2S&   GetNextDataWriteAddressM2S() const noexcept;
        const DataAXI4WriteDataChannelM2S&      GetNextDataWriteDataM2S() const noexcept;
        const DataAXI4WriteResponseChannelM2S&  GetNextDataWriteResponseM2S() const noexcept;

        //
        const FetchAXI4ReadAddressChannelS2M&   GetFetchReadAddressS2M() const noexcept;
        const FetchAXI4ReadDataChannelS2M&      GetFetchReadDataS2M() const noexcept;

        const DataAXI4ReadAddressChannelS2M&    GetDataReadAddressS2M() const noexcept;
        const DataAXI4ReadDataChannelS2M&       GetDataReadDataS2M() const noexcept;

        const DataAXI4WriteAddressChannelS2M&   GetDataWriteAddressS2M() const noexcept;
        const DataAXI4WriteDataChannelS2M&      GetDataWriteDataS2M() const noexcept;
        const DataAXI4WriteResponseChannelS2M&  GetDataWriteResponseS2M() const noexcept;

        //
        void                                    NextReset(bool reset = true) noexcept;

        //
        void                                    Reset() noexcept;
        void                                    Eval(bool enable = true) noexcept;
    };


    //
    class SoCAXIBridgeSingleChannel {
    private:
        NSCSCCSingle::NSCSCC2023SoC*    soc;

    public:
        SoCAXIBridgeSingleChannel(NSCSCCSingle::NSCSCC2023SoC* soc) noexcept;

        SoCAXIBridgeSingleChannel(const SoCAXIBridgeSingleChannel& obj) noexcept;
        SoCAXIBridgeSingleChannel(SoCAXIBridgeSingleChannel&& obj) noexcept;

        ~SoCAXIBridgeSingleChannel() noexcept;
    };
}


namespace BullsEye::Draconids3014::SoCAXIBridgeEvent {

}


#endif
