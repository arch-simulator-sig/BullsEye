#include "ds232_verilated.hpp"


// Implementation of: class Thinpad
namespace BullsEye::Draconids3014 {
    /*
    VerilatedVcdC*                  fp; // to form *.vcd file

    DS232*                          core;
    SoCAXIBridgeDualChannel*        soc_axi;

    bool                            next_reset;

    vluint64_t                      eval_time;
    */

    Thinpad::Thinpad(VerilatedVcdC* fp, NSCSCCSingle::NSCSCC2023SoC* soc) noexcept
        : fp            (fp)
        , core          (new DS232)
        , soc_axi       (new SoCAXIBridgeDualChannel(soc))
        , next_reset    (false)
        , eval_time     (0)
    { 
        if (fp)
            this->core->trace(fp, 64);
    }

    Thinpad::Thinpad(Thinpad&& obj) noexcept
        : fp            (obj.fp)
        , core          (obj.core)
        , soc_axi       (obj.soc_axi)
        , next_reset    (obj.next_reset)
        , eval_time     (obj.eval_time)
    { 
        obj.fp      = nullptr;
        obj.core    = nullptr;
        obj.soc_axi = nullptr;
    }

    Thinpad::~Thinpad() noexcept
    {
        delete this->core;
        delete this->soc_axi;
    }

    VerilatedVcdC* Thinpad::GetVCD() noexcept
    {
        return this->fp;
    }

    const VerilatedVcdC* Thinpad::GetVCD() const noexcept
    {
        return this->fp;
    }

    DS232* Thinpad::GetCore() noexcept
    {
        return this->core;
    }

    const DS232* Thinpad::GetCore() const noexcept
    {
        return this->core;
    }

    SoCAXIBridgeDualChannel* Thinpad::GetSoCAXI() noexcept
    {
        return this->soc_axi;
    }

    const SoCAXIBridgeDualChannel* Thinpad::GetSoCAXI() const noexcept
    {
        return this->soc_axi;
    }

    vluint64_t Thinpad::GetEvalTime() const noexcept
    {
        return this->eval_time;
    }

    void Thinpad::NextReset(bool reset) noexcept
    {
        this->next_reset = reset;
    }

    void Thinpad::_EvalCoreClockPositive() noexcept
    {
        core->clk = 1;
        core->eval();

        if (fp)
            fp->dump(eval_time);

        eval_time++;
    }

    void Thinpad::_EvalCoreClockNegative() noexcept
    {
        core->clk = 0;
        core->eval();

        if (fp)
            fp->dump(eval_time);

        eval_time++;
    }

    void Thinpad::Eval() noexcept
    {
        if (next_reset) // reset cycle
        {
            _EvalCoreClockNegative();

            // core reset
            this->core->reset = 1;

            _EvalCoreClockNegative();
            _EvalCoreClockPositive();

            this->core->reset = 0;

            // soc reset
            this->soc_axi->NextReset(true);
            this->soc_axi->Eval();

            //
            next_reset = false;
        }
        else // normal cycle
        {
            // core -> soc_axi
            this->soc_axi->NextFetchReadAddressM2S({
                .arid       = this->core->if_axi_m_arid,
                .araddr     = this->core->if_axi_m_araddr,
                .arlen      = this->core->if_axi_m_arlen,
                .arsize     = this->core->if_axi_m_arsize,
                .arburst    = this->core->if_axi_m_arburst,
                .aruser     = this->core->if_axi_m_aruser,
                .arvalid    = this->core->if_axi_m_arvalid
            });

            this->soc_axi->NextFetchReadDataM2S({
                .rready     = this->core->if_axi_m_rready
            });

            this->soc_axi->NextDataWriteAddressM2S({
                .awid       = this->core->mem_axi_m_awid,
                .awaddr     = this->core->mem_axi_m_awaddr,
                .awlen      = this->core->mem_axi_m_awlen,
                .awsize     = this->core->mem_axi_m_awsize,
                .awburst    = this->core->mem_axi_m_awburst,
                .awuser     = this->core->mem_axi_m_awuser,
                .awvalid    = this->core->mem_axi_m_awvalid
            });

            this->soc_axi->NextDataWriteDataM2S({
                .wdata      = this->core->mem_axi_m_wdata,
                .wstrb      = this->core->mem_axi_m_wstrb,
                .wlast      = this->core->mem_axi_m_wlast,
                .wvalid     = this->core->mem_axi_m_wvalid
            });

            this->soc_axi->NextDataWriteResponseM2S({
                .bready     = this->core->mem_axi_m_bready
            });

            this->soc_axi->NextDataReadAddressM2S({
                .arid       = this->core->mem_axi_m_arid,
                .araddr     = this->core->mem_axi_m_araddr,
                .arlen      = this->core->mem_axi_m_arlen,
                .arsize     = this->core->mem_axi_m_arsize,
                .arburst    = this->core->mem_axi_m_arburst,
                .aruser     = this->core->mem_axi_m_aruser,
                .arvalid    = this->core->mem_axi_m_arvalid
            });

            this->soc_axi->NextDataReadDataM2S({
                .rready     = this->core->mem_axi_m_rready
            });

            // soc_axi -> core
            {
                const FetchAXI4ReadAddressChannelS2M& bundle
                    = this->soc_axi->GetFetchReadAddressS2M();

                this->core->if_axi_m_arready    = bundle.arready;
            }

            {
                const FetchAXI4ReadDataChannelS2M& bundle
                    = this->soc_axi->GetFetchReadDataS2M();

                this->core->if_axi_m_rid        = bundle.rid;
                this->core->if_axi_m_rdata      = bundle.rdata;
                this->core->if_axi_m_rresp      = bundle.rresp;
                this->core->if_axi_m_rlast      = bundle.rlast;
                this->core->if_axi_m_rvalid     = bundle.rvalid;
            }

            {
                const DataAXI4WriteAddressChannelS2M& bundle
                    = this->soc_axi->GetDataWriteAddressS2M();

                this->core->mem_axi_m_awready   = bundle.awready;
            }

            {
                const DataAXI4WriteDataChannelS2M& bundle
                    = this->soc_axi->GetDataWriteDataS2M();

                this->core->mem_axi_m_wready    = bundle.wready;
            }

            {
                const DataAXI4WriteResponseChannelS2M& bundle
                    = this->soc_axi->GetDataWriteResponseS2M();

                this->core->mem_axi_m_bid       = bundle.bid;
                this->core->mem_axi_m_bresp     = bundle.bresp;
                this->core->mem_axi_m_bvalid    = bundle.bvalid;
            }

            {
                const DataAXI4ReadAddressChannelS2M& bundle
                    = this->soc_axi->GetDataReadAddressS2M();

                this->core->mem_axi_m_arready   = bundle.arready;
            }

            {
                const DataAXI4ReadDataChannelS2M& bundle
                    = this->soc_axi->GetDataReadDataS2M();

                this->core->mem_axi_m_rid       = bundle.rid;
                this->core->mem_axi_m_rdata     = bundle.rdata;
                this->core->mem_axi_m_rresp     = bundle.rresp;
                this->core->mem_axi_m_rlast     = bundle.rlast;
                this->core->mem_axi_m_rvalid    = bundle.rvalid;
            }

            // core eval
            _EvalCoreClockNegative();
            _EvalCoreClockPositive();

            // soc eval
            this->soc_axi->Eval();
        }
    }
}


// Implementation of: class Thinpad::Builder
namespace BullsEye::Draconids3014 {
    /*
    VerilatedVcdC*                  fp; // to form *.vcd file
    NSCSCCSingle::NSCSCC2023SoC*    soc;
    */

    Thinpad::Builder::Builder() noexcept:
        fp(nullptr),
        soc(nullptr)
    {}

    Thinpad::Builder::~Builder() noexcept
    {}

    Thinpad::Builder& Thinpad::Builder::VCD(VerilatedVcdC* fp) noexcept
    {
        this->fp = fp;
        return *this;
    }

    Thinpad::Builder& Thinpad::Builder::SoC(NSCSCCSingle::NSCSCC2023SoC* soc) noexcept
    {
        this->soc = soc;
        return *this;
    }

    VerilatedVcdC* Thinpad::Builder::GetVCD() noexcept
    {
        return this->fp;
    }

    const VerilatedVcdC* Thinpad::Builder::GetVCD() const noexcept
    {
        return this->fp;
    }

    void Thinpad::Builder::SetVCD(VerilatedVcdC* fp) noexcept
    {
        this->fp = fp;
    }

    NSCSCCSingle::NSCSCC2023SoC* Thinpad::Builder::GetSoC() noexcept
    {
        return this->soc;
    }

    const NSCSCCSingle::NSCSCC2023SoC* Thinpad::Builder::GetSoC() const noexcept
    {
        return this->soc;
    }

    void Thinpad::Builder::SetSoC(NSCSCCSingle::NSCSCC2023SoC* soc) noexcept
    {
        this->soc = soc;
    }

    Thinpad* Thinpad::Builder::Build() noexcept
    {
        return new Thinpad(this->fp, this->soc);
    }
}
