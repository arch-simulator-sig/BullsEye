#pragma once

#ifndef __HEADER_DS232__CORE_VERILATED
#define __HEADER_DS232__CORE_VERILATED


#include <verilated.h>
#include <verilated_vcd_c.h>

#include "Vthinpad_verilated.h"

#include "../soc/soc_axi.hpp"

#include "ds232_event.hpp"


namespace BullsEye::Draconids3014 {

    // Core Instance
    using DS232 = Vthinpad_verilated;

    // Draconids 3014 Thinpad
    class Thinpad {
    public:
        class Builder;

    private:
        VerilatedVcdC*                  fp; // to form *.vcd file

        DS232*                          core;
        SoCAXIBridgeDualChannel*        soc_axi;

        bool                            next_reset;

        vluint64_t                      eval_time;
    
    protected:
        friend class Builder;

        Thinpad(VerilatedVcdC* fp, NSCSCCSingle::NSCSCC2023SoC* soc) noexcept;

    private:
        void                            _EvalCoreClockPositive() noexcept;
        void                            _EvalCoreClockNegative() noexcept;

    public:
        ~Thinpad() noexcept;
        Thinpad(Thinpad&&) noexcept;

        Thinpad(const Thinpad&) = delete;

        VerilatedVcdC*                  GetVCD() noexcept;
        const VerilatedVcdC*            GetVCD() const noexcept;

        DS232*                          GetCore() noexcept;
        const DS232*                    GetCore() const noexcept;

        SoCAXIBridgeDualChannel*        GetSoCAXI() noexcept;
        const SoCAXIBridgeDualChannel*  GetSoCAXI() const noexcept;

        vluint64_t                      GetEvalTime() const noexcept;

        void                            NextReset(bool reset = true) noexcept;

        void                            Eval() noexcept;
    };

    // Draconids 3014 Thinpad Builder
    class Thinpad::Builder {
    private:
        VerilatedVcdC*                  fp; // to form *.vcd file
        NSCSCCSingle::NSCSCC2023SoC*    soc;

    public:
        Builder() noexcept;
        ~Builder() noexcept;

        Builder&                            VCD(VerilatedVcdC* fp) noexcept;
        Builder&                            SoC(NSCSCCSingle::NSCSCC2023SoC* soc) noexcept;

        VerilatedVcdC*                      GetVCD() noexcept;
        const VerilatedVcdC*                GetVCD() const noexcept;
        void                                SetVCD(VerilatedVcdC* fp) noexcept;

        NSCSCCSingle::NSCSCC2023SoC*        GetSoC() noexcept;
        const NSCSCCSingle::NSCSCC2023SoC*  GetSoC() const noexcept;
        void                                SetSoC(NSCSCCSingle::NSCSCC2023SoC* soc) noexcept;

        Thinpad*                            Build() noexcept;
    };
}


#endif
