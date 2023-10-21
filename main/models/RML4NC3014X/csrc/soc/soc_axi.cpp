#include "soc_axi.hpp"
//
//  AXI Bridge to NSCSCC2023 SoC for Verilated emulation
//
//


// Implementation of: class SoCAXIBridgeDualChannel
namespace BullsEye::Draconids3014 {

    /*
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
    */

    SoCAXIBridgeDualChannel::SoCAXIBridgeDualChannel(NSCSCCSingle::NSCSCC2023SoC* soc) noexcept
        : soc                   (soc)
        , bus_clock_divider     (0)
        , fetch_i_axi4ar        ()
        , fetch_i_axi4r         ()
        , fetch_o_axi4ar        ()
        , fetch_o_axi4r         ()
        , fetch_read_state      (ReadState::AXI_READ_IDLE)
        , data_i_axi4ar         ()
        , data_i_axi4r          ()
        , data_o_axi4ar         ()
        , data_o_axi4r          ()
        , data_read_state       (ReadState::AXI_READ_IDLE)
        , data_i_axi4aw         ()
        , data_i_axi4w          ()
        , data_i_axi4b          ()
        , data_o_axi4aw         ()
        , data_o_axi4w          ()
        , data_o_axi4b          ()
        , data_write_state      (WriteState::AXI_WRITE_IDLE)
        , next_reset            (false)
    { }

    SoCAXIBridgeDualChannel::SoCAXIBridgeDualChannel(const SoCAXIBridgeDualChannel& obj) noexcept
        : soc                   (obj.soc)
        , bus_clock_divider     (obj.bus_clock_divider)
        , fetch_i_axi4ar        (obj.fetch_i_axi4ar)
        , fetch_i_axi4r         (obj.fetch_i_axi4r)
        , fetch_o_axi4ar        (obj.fetch_o_axi4ar)
        , fetch_o_axi4r         (obj.fetch_o_axi4r)
        , fetch_read_state      (obj.fetch_read_state)
        , data_i_axi4ar         (obj.data_i_axi4ar)
        , data_i_axi4r          (obj.data_i_axi4r)
        , data_o_axi4ar         (obj.data_o_axi4ar)
        , data_o_axi4r          (obj.data_o_axi4r)
        , data_read_state       (obj.data_read_state)
        , data_i_axi4aw         (obj.data_i_axi4aw)
        , data_i_axi4w          (obj.data_i_axi4w)
        , data_i_axi4b          (obj.data_i_axi4b)
        , data_o_axi4aw         (obj.data_o_axi4aw)
        , data_o_axi4w          (obj.data_o_axi4w)
        , data_o_axi4b          (obj.data_o_axi4b)
        , data_write_state      (obj.data_write_state)
        , next_reset            (obj.next_reset)
    { }

    SoCAXIBridgeDualChannel::SoCAXIBridgeDualChannel(SoCAXIBridgeDualChannel&& obj) noexcept
        : soc                   (obj.soc)
        , bus_clock_divider     (obj.bus_clock_divider)
        , fetch_i_axi4ar        (obj.fetch_i_axi4ar)
        , fetch_i_axi4r         (obj.fetch_i_axi4r)
        , fetch_o_axi4ar        (obj.fetch_o_axi4ar)
        , fetch_o_axi4r         (obj.fetch_o_axi4r)
        , fetch_read_state      (obj.fetch_read_state)
        , data_i_axi4ar         (obj.data_i_axi4ar)
        , data_i_axi4r          (obj.data_i_axi4r)
        , data_o_axi4ar         (obj.data_o_axi4ar)
        , data_o_axi4r          (obj.data_o_axi4r)
        , data_read_state       (obj.data_read_state)
        , data_i_axi4aw         (obj.data_i_axi4aw)
        , data_i_axi4w          (obj.data_i_axi4w)
        , data_i_axi4b          (obj.data_i_axi4b)
        , data_o_axi4aw         (obj.data_o_axi4aw)
        , data_o_axi4w          (obj.data_o_axi4w)
        , data_o_axi4b          (obj.data_o_axi4b)
        , data_write_state      (obj.data_write_state)
        , next_reset            (obj.next_reset)
    { }

    SoCAXIBridgeDualChannel::~SoCAXIBridgeDualChannel() noexcept
    { }

    unsigned int SoCAXIBridgeDualChannel::GetBusClockDivider() const noexcept
    {
        return this->bus_clock_divider;
    }

    void SoCAXIBridgeDualChannel::SetBusClockDivider(unsigned int divider) noexcept
    {
        this->bus_clock_divider = divider;
    }

    void SoCAXIBridgeDualChannel::NextFetchReadAddressM2S(const FetchAXI4ReadAddressChannelM2S& bundle) noexcept
    {
        this->fetch_i_axi4ar = bundle;
    }

    void SoCAXIBridgeDualChannel::NextFetchReadDataM2S(const FetchAXI4ReadDataChannelM2S& bundle) noexcept
    {
        this->fetch_i_axi4r = bundle;
    }

    void SoCAXIBridgeDualChannel::NextDataReadAddressM2S(const DataAXI4ReadAddressChannelM2S& bundle) noexcept
    {
        this->data_i_axi4ar = bundle;
    }

    void SoCAXIBridgeDualChannel::NextDataReadDataM2S(const DataAXI4ReadDataChannelM2S& bundle) noexcept
    {
        this->data_i_axi4r = bundle;
    }

    void SoCAXIBridgeDualChannel::NextDataWriteAddressM2S(const DataAXI4WriteAddressChannelM2S& bundle) noexcept
    {
        this->data_i_axi4aw = bundle;
    }

    void SoCAXIBridgeDualChannel::NextDataWriteDataM2S(const DataAXI4WriteDataChannelM2S& bundle) noexcept
    {
        this->data_i_axi4w = bundle;
    }

    void SoCAXIBridgeDualChannel::NextDataWriteResponseM2S(const DataAXI4WriteResponseChannelM2S& bundle) noexcept
    {
        this->data_i_axi4b = bundle;
    }

    const FetchAXI4ReadAddressChannelM2S& SoCAXIBridgeDualChannel::GetNextFetchReadAddressM2S() const noexcept
    {
        return this->fetch_i_axi4ar;
    }

    const FetchAXI4ReadDataChannelM2S& SoCAXIBridgeDualChannel::GetNextFetchReadDataM2S() const noexcept
    {
        return this->fetch_i_axi4r;
    }

    const DataAXI4ReadAddressChannelM2S& SoCAXIBridgeDualChannel::GetNextDataReadAddressM2S() const noexcept
    {
        return this->data_i_axi4ar;
    }

    const DataAXI4ReadDataChannelM2S& SoCAXIBridgeDualChannel::GetNextDataReadDataM2S() const noexcept
    {
        return this->data_i_axi4r;
    }

    const DataAXI4WriteAddressChannelM2S& SoCAXIBridgeDualChannel::GetNextDataWriteAddressM2S() const noexcept
    {
        return this->data_i_axi4aw;
    }

    const DataAXI4WriteDataChannelM2S& SoCAXIBridgeDualChannel::GetNextDataWriteDataM2S() const noexcept
    {
        return this->data_i_axi4w;
    }

    const DataAXI4WriteResponseChannelM2S& SoCAXIBridgeDualChannel::GetNextDataWriteResponseM2S() const noexcept
    {
        return this->data_i_axi4b;
    }

    const FetchAXI4ReadAddressChannelS2M& SoCAXIBridgeDualChannel::GetFetchReadAddressS2M() const noexcept
    {
        return this->fetch_o_axi4ar;
    }

    const FetchAXI4ReadDataChannelS2M& SoCAXIBridgeDualChannel::GetFetchReadDataS2M() const noexcept
    {
        return this->fetch_o_axi4r;
    }

    const DataAXI4ReadAddressChannelS2M& SoCAXIBridgeDualChannel::GetDataReadAddressS2M() const noexcept
    {
        return this->data_o_axi4ar;
    }

    const DataAXI4ReadDataChannelS2M& SoCAXIBridgeDualChannel::GetDataReadDataS2M() const noexcept
    {
        return this->data_o_axi4r;
    }

    const DataAXI4WriteAddressChannelS2M& SoCAXIBridgeDualChannel::GetDataWriteAddressS2M() const noexcept
    {
        return this->data_o_axi4aw;
    }

    const DataAXI4WriteDataChannelS2M& SoCAXIBridgeDualChannel::GetDataWriteDataS2M() const noexcept
    {
        return this->data_o_axi4w;
    }

    const DataAXI4WriteResponseChannelS2M& SoCAXIBridgeDualChannel::GetDataWriteResponseS2M() const noexcept
    {
        return this->data_o_axi4b;
    }

    void SoCAXIBridgeDualChannel::NextReset(bool reset) noexcept
    {
        this->next_reset = reset;
    }

    void SoCAXIBridgeDualChannel::Reset() noexcept
    {
        //
        fetch_o_axi4ar.arready = true;

        fetch_o_axi4r.rvalid = false;

        fetch_read_state = ReadState::AXI_READ_IDLE;

        //
        data_o_axi4ar.arready = false;

        data_o_axi4r.rvalid = false;

        data_read_state = ReadState::AXI_READ_IDLE;

        //
        data_o_axi4aw.awready = true;

        data_o_axi4w.wready = false;

        data_o_axi4b.bvalid = false;

        data_write_state = WriteState::AXI_WRITE_IDLE;

        //
        next_reset = false;
    }

    uint32_t SoCAXIBridgeDualChannel::_ConvertBusAddress(uint32_t addr, bool kseg1) noexcept
    {
        if (kseg1)
            return (addr & 0x1FFFFFFF) | 0xA0000000;
        else
            return (addr & 0x1FFFFFFF);
    }

    Jasse::LA32MOPWidth SoCAXIBridgeDualChannel::_ConvertWidth(AXI4::attr_size_t axsize) noexcept
    {
        switch (axsize)
        {
            case AXI4::Attributes::AXSIZE_1B:
                return Jasse::MOPW_BYTE;

            case AXI4::Attributes::AXSIZE_2B:
                return Jasse::MOPW_HALF_WORD;

            case AXI4::Attributes::AXSIZE_4B:
                return Jasse::MOPW_WORD;

            [[unlikely]] default:
                return Jasse::MOPW_WORD;
        }
    }

    uint32_t SoCAXIBridgeDualChannel::_AlignBusData(memdata_t data, uint32_t addr, AXI4::attr_size_t axsize) noexcept
    {
        switch (axsize)
        {
            case AXI4::Attributes::AXSIZE_1B:
                return uint32_t(data.data8 ) << ((addr & 0x3) << 3);

            case AXI4::Attributes::AXSIZE_2B:
                return uint32_t(data.data16) << ((addr & 0x2) << 3);

            case AXI4::Attributes::AXSIZE_4B:
                return uint32_t(data.data32);

            [[unlikely]] default:
                return 0;
        }
    }

    memdata_t SoCAXIBridgeDualChannel::_UnalignBusData(uint32_t data, uint32_t addr, AXI4::attr_size_t axsize) noexcept
    {
        memdata_t result;

        switch (axsize)
        {
            case AXI4::Attributes::AXSIZE_1B:
                result.data8  = uint8_t (data >> ((addr & 0x3) << 3));
                break;

            case AXI4::Attributes::AXSIZE_2B:
                result.data16 = uint16_t(data >> ((addr & 0x2) << 3));
                break;

            case AXI4::Attributes::AXSIZE_4B:
                result.data32 = uint32_t(data);
                break;

            [[unlikely]] default:
                return { 0 };
        }

        return result;
    }

    uint32_t SoCAXIBridgeDualChannel::_IncrBusAddress(uint32_t addr, AXI4::attr_size_t axsize, AXI4::attr_burst_t axburst, AXI4::attr_len_t axlen) noexcept
    {
        switch (axburst)
        {
            case AXI4::Attributes::AXBURST_FIXED:
                return addr;

            case AXI4::Attributes::AXBURST_INCR:
                switch (axsize)
                {
                    case AXI4::Attributes::AXSIZE_1B:
                        return addr + 1;

                    case AXI4::Attributes::AXSIZE_2B:
                        return addr + 2;

                    case AXI4::Attributes::AXSIZE_4B:
                        return addr + 4;

                    [[unlikely]] default:
                        return addr;
                }

            case AXI4::Attributes::AXBURST_WRAP:
                switch (axlen)
                {
                    case AXI4::Attributes::AXLEN<2>:
                        switch (axsize)
                        {
                            case AXI4::Attributes::AXSIZE_1B:
                                return (addr & 0xFFFFFFFE) | ((addr + 1) & 0x00000001);

                            case AXI4::Attributes::AXSIZE_2B:
                                return (addr & 0xFFFFFFFC) | ((addr + 2) & 0x00000003);

                            case AXI4::Attributes::AXSIZE_4B:
                                return (addr & 0xFFFFFFF8) | ((addr + 4) & 0x00000007);

                            [[unlikely]] default:
                                return addr;
                        }

                    case AXI4::Attributes::AXLEN<4>:
                        switch (axsize)
                        {
                            case AXI4::Attributes::AXSIZE_1B:
                                return (addr & 0xFFFFFFFC) | ((addr + 1) & 0x00000003);

                            case AXI4::Attributes::AXSIZE_2B:
                                return (addr & 0xFFFFFFF8) | ((addr + 2) & 0x00000007);

                            case AXI4::Attributes::AXSIZE_4B:
                                return (addr & 0xFFFFFFF0) | ((addr + 4) & 0x0000000F);

                            [[unlikely]] default:
                                return addr;
                        }

                    case AXI4::Attributes::AXLEN<8>:
                        switch (axsize)
                        {
                            case AXI4::Attributes::AXSIZE_1B:
                                return (addr & 0xFFFFFFF8) | ((addr + 1) & 0x00000007);

                            case AXI4::Attributes::AXSIZE_2B:
                                return (addr & 0xFFFFFFF0) | ((addr + 2) & 0x0000000F);

                            case AXI4::Attributes::AXSIZE_4B:
                                return (addr & 0xFFFFFFE0) | ((addr + 4) & 0x0000001F);

                            [[unlikely]] default:
                                return addr;
                        }

                    case AXI4::Attributes::AXLEN<16>:
                        switch (axsize)
                        {
                            case AXI4::Attributes::AXSIZE_1B:
                                return (addr & 0xFFFFFFF0) | ((addr + 1) & 0x0000000F);

                            case AXI4::Attributes::AXSIZE_2B:
                                return (addr & 0xFFFFFFE0) | ((addr + 2) & 0x0000001F);

                            case AXI4::Attributes::AXSIZE_4B:
                                return (addr & 0xFFFFFFC0) | ((addr + 4) & 0x0000003F);

                            [[unlikely]] default:
                                return addr;
                        }

                    [[unlikely]] default:
                        return addr;
                }

            [[unlikely]] default:
                return addr;
        }
    }

    void SoCAXIBridgeDualChannel::_EvalFetchChannel() noexcept
    {
        // Fetch Channel logic
        ReadState fetch_read_state_next = fetch_read_state;

        // fetch read FSM
        switch (fetch_read_state)
        {
            case ReadState::AXI_READ_IDLE:

                if (fetch_i_axi4ar.arvalid)
                {
                    fetch_read_state_next = ReadState::AXI_READ_DATA;

                    if (fetch_i_axi4ar.arsize == AXI4::Attributes::AXSIZE_1B
                    ||  fetch_i_axi4ar.arsize == AXI4::Attributes::AXSIZE_2B
                    ||  fetch_i_axi4ar.arsize == AXI4::Attributes::AXSIZE_4B)
                        ;
                    else
                    {
                        // unsupported burst size
                        fetch_read_state_next = ReadState::AXI_READ_ERROR;
                        break;
                    }

                    if (fetch_i_axi4ar.arburst == AXI4::Attributes::AXBURST_WRAP)
                    {
                        if (fetch_i_axi4ar.arlen == AXI4::Attributes::AXLEN<2>
                        ||  fetch_i_axi4ar.arlen == AXI4::Attributes::AXLEN<4>
                        ||  fetch_i_axi4ar.arlen == AXI4::Attributes::AXLEN<8>
                        ||  fetch_i_axi4ar.arlen == AXI4::Attributes::AXLEN<16>)
                            ;
                        else
                        {
                            // wrong burst length in WRAP mode
                            fetch_read_state_next = ReadState::AXI_READ_ERROR;
                            break;
                        }
                    }
                }

                break;

            case ReadState::AXI_READ_DATA:

                if (fetch_read_trans_accepted == uint(fetch_read_length) + 1)
                    fetch_read_state_next = ReadState::AXI_READ_IDLE;

                break;

            [[unlikely]] default: break;
        }

        // fetch read address channel logic
        switch (fetch_read_state)
        {
            case ReadState::AXI_READ_IDLE:

                if (fetch_read_state_next == ReadState::AXI_READ_DATA)
                {
                    fetch_read_id       = fetch_i_axi4ar.arid;
                    fetch_read_addr     = fetch_i_axi4ar.araddr;
                    fetch_read_mode     = fetch_i_axi4ar.arburst;
                    fetch_read_size     = fetch_i_axi4ar.arsize;
                    fetch_read_length   = fetch_i_axi4ar.arlen;
                    fetch_read_uncached = fetch_i_axi4ar.aruser;

                    fetch_read_width    = _ConvertWidth(fetch_read_size);

                    fetch_o_axi4ar.arready = false;
                }

                break;

            case ReadState::AXI_READ_DATA:

                if (fetch_read_state_next == ReadState::AXI_READ_IDLE)
                    fetch_o_axi4ar.arready = true;

                break;

            [[unlikely]] case ReadState::AXI_READ_ERROR:

                fetch_o_axi4ar.arready = false;

                break;

            [[unlikely]] default: break;
        }

        // fetch read data channel logic
        switch (fetch_read_state)
        {
            case ReadState::AXI_READ_IDLE:

                if (fetch_read_state_next == ReadState::AXI_READ_DATA)
                {
                    fetch_read_trans_clock_divider  = bus_clock_divider;
                    fetch_read_trans_addr           = _ConvertBusAddress(fetch_read_addr, fetch_read_uncached);
                    fetch_read_trans_readed         = 0;
                    fetch_read_trans_accepted       = 0;
                }

                break;

            case ReadState::AXI_READ_DATA:

                if (fetch_read_state_next == ReadState::AXI_READ_DATA)
                {
                    if (fetch_read_trans_accepted != fetch_read_trans_readed)
                    {
                        if (fetch_o_axi4r.rvalid && fetch_i_axi4r.rready)
                        {
                            fetch_read_trans_accepted++;

                            if (fetch_read_trans_accepted == fetch_read_trans_readed)
                            {
                                // buffer empty
                                fetch_o_axi4r.rvalid = false;
                            }
                            else
                            {
                                // buffer pop
                                fetch_o_axi4r.rid       = fetch_read_id;
                                fetch_o_axi4r.rdata     = fetch_read_trans_buffer[fetch_read_trans_accepted];
                                fetch_o_axi4r.rresp     = AXI4::Attributes::RRESP_OKAY;
                                fetch_o_axi4r.rlast     = fetch_read_trans_accepted == uint(fetch_read_length);
                                fetch_o_axi4r.rvalid    = true;
                            }
                        }
                        else
                        {
                            fetch_o_axi4r.rid       = fetch_read_id;
                            fetch_o_axi4r.rdata     = fetch_read_trans_buffer[fetch_read_trans_accepted];
                            fetch_o_axi4r.rresp     = AXI4::Attributes::RRESP_OKAY;
                            fetch_o_axi4r.rlast     = fetch_read_trans_accepted == uint(fetch_read_length);
                            fetch_o_axi4r.rvalid    = true;
                        }
                    }
                    else
                    {
                        fetch_o_axi4r.rvalid = false;
                    }
                }

                break;

            [[unlikely]] case ReadState::AXI_READ_ERROR:

                fetch_o_axi4r.rvalid = false;

                break;

            [[unlikely]] default: break;
        }

        // fetch read buffer logic
        switch (fetch_read_state)
        {
            case ReadState::AXI_READ_DATA:

                if (fetch_read_trans_readed < uint(fetch_read_length) + 1)
                {
                    // bus clock divider
                    if (fetch_read_trans_clock_divider)
                    {
                        fetch_read_trans_clock_divider--;
                        break;
                    }
                    else
                        fetch_read_trans_clock_divider = bus_clock_divider;

                    // bus read to buffer
                    memdata_t memdata;
                    LA32MOPOutcome mopoutcome 
                        = soc->MMU().ReadInsn(fetch_read_trans_addr, fetch_read_width, &memdata);
                    
                    if (mopoutcome.status != LA32MOPStatus::MOP_SUCCESS)
                    {
                        // bus read fault
                        fetch_read_state_next = ReadState::AXI_READ_ERROR;
                        break;
                    }

                    fetch_read_trans_buffer[fetch_read_trans_readed++]
                        = _AlignBusData(memdata, fetch_read_trans_addr, fetch_read_size);

                    fetch_read_trans_addr 
                        = _IncrBusAddress(fetch_read_trans_addr, fetch_read_size, fetch_read_mode, fetch_read_length);
                }

                break;

            default: break;
        }

        //
        fetch_read_state = fetch_read_state_next;
    }

    void SoCAXIBridgeDualChannel::_EvalDataChannel() noexcept
    {
        // Data Write Channel logic
        WriteState data_write_state_next = data_write_state;

        // data write channel FSM
        switch (data_write_state)
        {
            case WriteState::AXI_WRITE_IDLE:

                if (data_i_axi4aw.awvalid)
                {
                    data_write_state_next = WriteState::AXI_WRITE_DATA;

                    if (data_i_axi4aw.awsize == AXI4::Attributes::AXSIZE_1B
                    ||  data_i_axi4aw.awsize == AXI4::Attributes::AXSIZE_2B
                    ||  data_i_axi4aw.awsize == AXI4::Attributes::AXSIZE_4B)
                        ;
                    else
                    {
                        data_write_state_next = WriteState::AXI_WRITE_ERROR;
                        break;
                    }

                    if (data_i_axi4aw.awburst == AXI4::Attributes::AXBURST_WRAP)
                    {
                        if (data_i_axi4aw.awlen == AXI4::Attributes::AXLEN<2>
                        ||  data_i_axi4aw.awlen == AXI4::Attributes::AXLEN<4>
                        ||  data_i_axi4aw.awlen == AXI4::Attributes::AXLEN<8>
                        ||  data_i_axi4aw.awlen == AXI4::Attributes::AXLEN<16>)
                            ;
                        else
                        {
                            data_write_state_next = WriteState::AXI_WRITE_ERROR;
                            break;
                        }
                    }
                }

                break;

            case WriteState::AXI_WRITE_DATA:

                if (data_write_trans_last && data_write_trans_received == data_write_trans_written)
                    data_write_state_next = WriteState::AXI_WRITE_RESP;

                break;

            case WriteState::AXI_WRITE_RESP:

                if (data_i_axi4b.bready)
                    data_write_state_next = WriteState::AXI_WRITE_IDLE;

                break;

            [[unlikely]] default:
                break;
        }

        // data write address channel logic
        if (data_write_state == WriteState::AXI_WRITE_ERROR
        ||  data_read_state  == ReadState::AXI_READ_ERROR) [[unlikely]]
        {
            data_o_axi4aw.awready = false;
        }
        else switch (data_write_state)
        {
            case WriteState::AXI_WRITE_IDLE:

                if (data_write_state_next == WriteState::AXI_WRITE_DATA)
                {
                    data_write_id       = data_i_axi4aw.awid;
                    data_write_addr     = data_i_axi4aw.awaddr;
                    data_write_mode     = data_i_axi4aw.awburst;
                    data_write_size     = data_i_axi4aw.awsize;
                    data_write_length   = data_i_axi4aw.awlen;
                    data_write_uncached = data_i_axi4aw.awuser;

                    data_write_width    = _ConvertWidth(data_i_axi4aw.awsize);

                    data_o_axi4aw.awready = false;
                }

                break;

            case WriteState::AXI_WRITE_RESP:

                if (data_write_state_next == WriteState::AXI_WRITE_IDLE)
                    data_o_axi4aw.awready = true;

                break;

            default: break;
        }

        // data write data channel logic
        if (data_write_state == WriteState::AXI_WRITE_ERROR
        ||  data_read_state  == ReadState::AXI_READ_ERROR) [[unlikely]]
        {
            data_o_axi4w.wready = false;
        }
        else switch (data_write_state)
        {
            case WriteState::AXI_WRITE_IDLE:

                if (data_write_state_next == WriteState::AXI_WRITE_DATA)
                {
                    data_write_trans_clock_divider  = bus_clock_divider;
                    data_write_trans_raddr          = _ConvertBusAddress(data_i_axi4aw.awaddr, data_write_uncached);
                    data_write_trans_waddr          = data_write_trans_raddr;
                    data_write_trans_last           = false;
                    data_write_trans_received       = 0;
                    data_write_trans_written        = 0;

                    data_o_axi4w.wready = true;
                }

                break;

            case WriteState::AXI_WRITE_DATA:

                if (data_write_state_next == WriteState::AXI_WRITE_DATA)
                {
                    if (data_i_axi4w.wvalid)
                    {
                        if (data_write_trans_received > data_write_length) [[unlikely]]
                        {
                            // bus write transaction overflow
                            // TODO
                        }

                        if (data_i_axi4w.wlast && data_write_trans_received < data_write_length) [[unlikely]]
                        {
                            // bus write transaction underflow
                            // TODO
                        }

                        data_write_trans_last = data_i_axi4w.wlast;
                        data_write_trans_buffer[data_write_trans_received++] 
                            = _UnalignBusData(data_i_axi4w.wdata, data_write_trans_raddr, data_write_size);

                        data_write_trans_raddr 
                            = _IncrBusAddress(data_write_trans_raddr, data_write_size, data_write_mode, data_write_length);

                        if (data_write_trans_last)
                            data_o_axi4w.wready = false;
                    }
                }

                break;

            default: break;
        }

        // data write response channel logic
        if (data_write_state == WriteState::AXI_WRITE_ERROR
        ||  data_read_state  == ReadState::AXI_READ_ERROR) [[unlikely]]
        {
            data_o_axi4b.bvalid = false;
        }
        else switch (data_write_state)
        {
            case WriteState::AXI_WRITE_DATA:

                if (data_write_state_next == WriteState::AXI_WRITE_RESP)
                {
                    data_o_axi4b.bid    = data_write_id;
                    data_o_axi4b.bresp  = AXI4::Attributes::BRESP_OKAY;
                    data_o_axi4b.bvalid = true;
                }

                break;

            case WriteState::AXI_WRITE_RESP:

                if (data_write_state_next == WriteState::AXI_WRITE_IDLE)
                    data_o_axi4b.bvalid = false;

                break;

            default: break;
        }

        // data write buffer logic
        switch (data_write_state)
        {
            case WriteState::AXI_WRITE_DATA:

                if (data_read_state != ReadState::AXI_READ_IDLE)
                    break;

                if (data_write_trans_written != data_write_trans_received)
                {
                    if (data_write_trans_clock_divider)
                    {
                        data_write_trans_clock_divider--;
                        break;
                    }
                    else
                        data_write_trans_clock_divider = bus_clock_divider;

                    memdata_t memdata = data_write_trans_buffer[data_write_trans_written];
                    LA32MOPOutcome mopoutcome 
                        = soc->MMU().WriteData(data_write_trans_waddr, data_write_width, memdata);

                    if (mopoutcome.status != LA32MOPStatus::MOP_SUCCESS)
                    {
                        // bus write fault
                        data_write_state_next = WriteState::AXI_WRITE_ERROR;
                        break;
                    }

                    data_write_trans_written++;

                    data_write_trans_waddr 
                        = _IncrBusAddress(data_write_trans_waddr, data_write_size, data_write_mode, data_write_length);
                }

                break;

            default: break;
        }

        
        // Data Read Channel logic
        ReadState data_read_state_next = data_read_state;

        // data read channel FSM
        switch (data_read_state)
        {
            case ReadState::AXI_READ_IDLE:

                if (data_write_state != WriteState::AXI_WRITE_IDLE)
                    break;

                if (data_write_state_next != WriteState::AXI_WRITE_IDLE)
                    break;

                if (data_i_axi4ar.arvalid)
                {
                    data_read_state_next = ReadState::AXI_READ_ADDR;

                    if (data_i_axi4ar.arsize == AXI4::Attributes::AXSIZE_1B
                    ||  data_i_axi4ar.arsize == AXI4::Attributes::AXSIZE_2B
                    ||  data_i_axi4ar.arsize == AXI4::Attributes::AXSIZE_4B)
                        ;
                    else
                    {
                        // unsupported burst size
                        data_read_state_next = ReadState::AXI_READ_ERROR;
                        break;
                    }

                    if (data_i_axi4ar.arburst == AXI4::Attributes::AXBURST_WRAP)
                    {
                        if (data_i_axi4ar.arlen == AXI4::Attributes::AXLEN<2>
                        ||  data_i_axi4ar.arlen == AXI4::Attributes::AXLEN<4>
                        ||  data_i_axi4ar.arlen == AXI4::Attributes::AXLEN<8>
                        ||  data_i_axi4ar.arlen == AXI4::Attributes::AXLEN<16>)
                            ;
                        else
                        {
                            // wrong burst length in WRAP mode
                            data_read_state_next = ReadState::AXI_READ_ERROR;
                            break;
                        }
                    }
                }

                break;

            case ReadState::AXI_READ_ADDR:

                if (data_i_axi4ar.arvalid)
                    data_read_state_next = ReadState::AXI_READ_DATA;
                else
                {
                    // but why you bully me? :(
                    data_read_state_next = ReadState::AXI_READ_IDLE;
                }

                break;

            case ReadState::AXI_READ_DATA:

                if (data_read_trans_accepted == uint(data_read_length) + 1)
                    data_read_state_next = ReadState::AXI_READ_IDLE;

                break;

            [[unlikely]] default:
                break;
        }

        // data read address channel logic
        if (data_write_state == WriteState::AXI_WRITE_ERROR
        ||  data_read_state  == ReadState::AXI_READ_ERROR) [[unlikely]]
        {
            data_o_axi4ar.arready = false;
        }
        else switch (data_read_state)
        {
            case ReadState::AXI_READ_IDLE:

                if (data_read_state_next == ReadState::AXI_READ_ADDR)
                    data_o_axi4ar.arready = true;

                break;

            case ReadState::AXI_READ_ADDR:

                if (data_read_state_next != ReadState::AXI_READ_ADDR)
                    data_o_axi4ar.arready = false;

                if (data_read_state_next == ReadState::AXI_READ_DATA)
                {
                    data_read_id       = data_i_axi4ar.arid;
                    data_read_addr     = data_i_axi4ar.araddr;
                    data_read_mode     = data_i_axi4ar.arburst;
                    data_read_size     = data_i_axi4ar.arsize;
                    data_read_length   = data_i_axi4ar.arlen;
                    data_read_uncached = data_i_axi4ar.aruser;

                    data_read_width    = _ConvertWidth(data_read_size);
                }

                break;

            default: break;
        }

        // data read data channe logic
        if (data_write_state == WriteState::AXI_WRITE_ERROR
        ||  data_read_state  == ReadState::AXI_READ_ERROR) [[unlikely]]
        {
            data_o_axi4r.rvalid = false;
        }
        else switch (data_read_state)
        {
            case ReadState::AXI_READ_ADDR:

                if (data_read_state_next == ReadState::AXI_READ_DATA)
                {
                    data_read_trans_clock_divider   = bus_clock_divider;
                    data_read_trans_addr            = _ConvertBusAddress(data_read_addr, data_read_uncached);
                    data_read_trans_readed          = 0;
                    data_read_trans_accepted        = 0;

                    data_o_axi4r.rvalid = false;
                }

                break;

            case ReadState::AXI_READ_DATA:

                if (data_read_state_next == ReadState::AXI_READ_DATA)
                {
                    if (data_read_trans_accepted != data_read_trans_readed)
                    {
                        if (data_o_axi4r.rvalid && data_i_axi4r.rready)
                        {
                            data_read_trans_accepted++;

                            if (data_read_trans_accepted == data_read_trans_readed)
                            {
                                // buffer empty
                                data_o_axi4r.rvalid = false;
                            }
                            else
                            {
                                // buffer pop
                                data_o_axi4r.rid    = data_read_id;
                                data_o_axi4r.rdata  = data_read_trans_buffer[data_read_trans_accepted];
                                data_o_axi4r.rresp  = AXI4::Attributes::RRESP_OKAY;
                                data_o_axi4r.rlast  = data_read_trans_accepted == uint(data_read_length);
                                data_o_axi4r.rvalid = true;
                            }
                        }
                        else
                        {
                            data_o_axi4r.rid       = data_read_id;
                            data_o_axi4r.rdata     = data_read_trans_buffer[data_read_trans_accepted];
                            data_o_axi4r.rresp     = AXI4::Attributes::RRESP_OKAY;
                            data_o_axi4r.rlast     = data_read_trans_accepted == uint(data_read_length);
                            data_o_axi4r.rvalid    = true;
                        }
                    }
                    else
                    {
                        data_o_axi4r.rvalid = false;
                    }
                }

                break;

            default: break;
        }

        // data read buffer logic
        switch (data_read_state)
        {
            case ReadState::AXI_READ_DATA:

                if (data_read_trans_readed < uint(data_read_length) + 1)
                {
                    // bus clock divider
                    if (data_read_trans_clock_divider)
                    {
                        data_read_trans_clock_divider--;
                        break;
                    }
                    else
                        data_read_trans_clock_divider = bus_clock_divider;

                    // bus read to buffer
                    memdata_t memdata;
                    LA32MOPOutcome mopoutcome 
                        = soc->MMU().ReadData(data_read_trans_addr, data_read_width, &memdata);
                    
                    if (mopoutcome.status != LA32MOPStatus::MOP_SUCCESS)
                    {
                        // bus read fault
                        data_read_state_next = ReadState::AXI_READ_ERROR;
                        break;
                    }

                    data_read_trans_buffer[data_read_trans_readed++]
                        = _AlignBusData(memdata, data_read_trans_addr, data_read_size);

                    data_read_trans_addr 
                        = _IncrBusAddress(data_read_trans_addr, data_read_size, data_read_mode, data_read_length);
                }

                break;

            default: break;
        }

        //
        data_write_state    = data_write_state_next; 
        data_read_state     = data_read_state_next;
    }

    void SoCAXIBridgeDualChannel::Eval(bool enable) noexcept
    {
        if (!enable)
            return;

        if (next_reset)
        {
            Reset();
            return;
        }

        _EvalFetchChannel();
        _EvalDataChannel();

        //
    }
}
