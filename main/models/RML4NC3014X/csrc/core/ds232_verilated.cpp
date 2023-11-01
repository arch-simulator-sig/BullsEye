#include "ds232_verilated.hpp"


#include "ds232_event.hpp"


// Implementation of: class Thinpad
namespace BullsEye::Draconids3014 {
    /*
    unsigned int                    eventBusId;

    VerilatedVcdC*                  fp; // to form *.vcd file

    DS232*                          core;
    SoCAXIBridgeDualChannel*        soc_axi;

    bool                            next_reset;

    FetchIDTracker                  fid_tracker;

    vluint64_t                      eval_time;
    */

    Thinpad::Thinpad(unsigned int eventBusId, VerilatedVcdC* fp, NSCSCCSingle::NSCSCC2023SoC* soc) noexcept
        : eventBusId    (eventBusId)
        , fp            (fp)
        , core          (new DS232)
        , soc_axi       (new SoCAXIBridgeDualChannel(soc, eventBusId))
        , fid_tracker   ()
        , next_reset    (false)
        , eval_time     (0)
    { 
        if (fp)
            this->core->trace(fp, 64);
    }

    Thinpad::Thinpad(Thinpad&& obj) noexcept
        : eventBusId    (obj.eventBusId)
        , fp            (obj.fp)
        , core          (obj.core)
        , soc_axi       (obj.soc_axi)
        , fid_tracker   (obj.fid_tracker)
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

    unsigned int Thinpad::GetEventBusId() const noexcept
    {
        return this->eventBusId;
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

    FetchIDTracker& Thinpad::GetFetchIDTracker() noexcept
    {
        return this->fid_tracker;
    }

    const FetchIDTracker& Thinpad::GetFetchIDTracker() const noexcept
    {
        return this->fid_tracker;
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


            // update fetch id tracker & event
            if (this->core->predispatch0_valid)
            {
                FetchIDTrack& track = this->fid_tracker.At(this->core->predispatch0_fid);

                track.SetPC(this->core->predispatch0_pc);
                track.SetUOP({
                    .imm26      = this->core->predispatch0_uop_imm26,
                    .regctrl_w  = this->core->predispatch0_uop_regctrl_w,
                    .regctrl_r  = this->core->predispatch0_uop_regctrl_r,
                    .waystone   = this->core->predispatch0_uop_waystone,
                    .imm2       = this->core->predispatch0_uop_imm2,
                    .cmd        = this->core->predispatch0_uop_cmd
                });

                DS232PreDispatchEvent(this->core, track).Fire(eventBusId);
            }

            if (this->core->predispatch1_valid)
            {
                FetchIDTrack& track = this->fid_tracker.At(this->core->predispatch1_fid);

                track.SetPC(this->core->predispatch1_pc);
                track.SetUOP({
                    .imm26      = this->core->predispatch1_uop_imm26,
                    .regctrl_w  = this->core->predispatch1_uop_regctrl_w,
                    .regctrl_r  = this->core->predispatch1_uop_regctrl_r,
                    .waystone   = this->core->predispatch1_uop_waystone,
                    .imm2       = this->core->predispatch1_uop_imm2,
                    .cmd        = this->core->predispatch1_uop_cmd
                });

                DS232PreDispatchEvent(this->core, track).Fire(eventBusId);
            }


            // main commit event
            if (this->core->commit0_en)
            {
                DS232MainCommitEvent(
                    this->core,
                    this->core->commit0_fid,
                    this->core->commit0_reg_addr,
                    this->core->commit0_reg_data
                ).Fire(eventBusId);
            }

            if (this->core->commit1_en)
            {
                DS232MainCommitEvent(
                    this->core,
                    this->core->commit1_fid,
                    this->core->commit1_reg_addr,
                    this->core->commit1_reg_data
                ).Fire(eventBusId);
            }


            // rob commit event
            if (this->core->commit0_rob_en)
            {
                DS232ROBCommitEvent(
                    this->core,
                    this->core->commit0_rob_fid,
                    this->core->commit0_rob_reg_dst,
                    this->core->commit0_rob_reg_value,
                    this->core->commit0_rob_store,
                    this->core->commit0_rob_uload,
                    this->core->commit0_rob_uload_addr,
                    this->core->commit0_rob_uload_cmd
                ).Fire(eventBusId);
            }

            if (this->core->commit1_rob_en)
            {
                DS232ROBCommitEvent(
                    this->core,
                    this->core->commit1_rob_fid,
                    this->core->commit1_rob_reg_dst,
                    this->core->commit1_rob_reg_value,
                    this->core->commit1_rob_store,
                    this->core->commit1_rob_uload,
                    this->core->commit1_rob_uload_addr,
                    this->core->commit1_rob_uload_cmd
                ).Fire(eventBusId);
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
    unsigned int                    eventBusId;

    VerilatedVcdC*                  fp; // to form *.vcd file
    NSCSCCSingle::NSCSCC2023SoC*    soc;
    */

    Thinpad::Builder::Builder() noexcept
        : eventBusId    (0)
        , fp            (nullptr)
        , soc           (nullptr)
    {}

    Thinpad::Builder::~Builder() noexcept
    {}

    Thinpad::Builder& Thinpad::Builder::EventBusId(unsigned int eventBusId) noexcept
    {
        this->eventBusId = eventBusId;
        return *this;
    }

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

    unsigned int Thinpad::Builder::GetEventBusId() const noexcept
    {
        return this->eventBusId;
    }

    void Thinpad::Builder::SetEventBusId(unsigned int eventBusId) noexcept
    {
        this->eventBusId = eventBusId;
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
        return new Thinpad(this->eventBusId, this->fp, this->soc);
    }
}
