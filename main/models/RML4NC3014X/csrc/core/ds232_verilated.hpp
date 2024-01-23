#pragma once

#ifndef __HEADER_DS232__CORE_VERILATED
#define __HEADER_DS232__CORE_VERILATED


#include <bitset>

#include <verilated.h>
#include <verilated_vcd_c.h>

#include "Vthinpad_verilated.h"

#include "../soc/soc_axi.hpp"

#include "ds232_fetch.hpp"


namespace BullsEye::Draconids3014 {

    // Core Instance
    using DS232 = Vthinpad_verilated;

    // Draconids 3014 Thinpad
    class Thinpad {
    public:
        class Builder;

    public:
        // Performance Profiling Interface
        class PPI {
        public:
            //
            bool            fetch_brob_read0_en;
            bool            fetch_brob_read0_bpmiss;

            bool            fetch_brob_read1_en;
            bool            fetch_brob_read1_bpmiss;

            uint64_t        fetch_brob_commit_count;
            uint64_t        fetch_brob_bpmiss_count;

            //
            std::bitset<6>  issue_iq0_pick_valid;
            std::bitset<6>  issue_iq0_pick_en;

            std::bitset<6>  issue_iq0_pick_on_forward;

            uint64_t        issue_iq0_pick_valid_counter    [6];
            uint64_t        issue_iq0_pick_en_counter       [6];

            uint64_t        issue_iq0_pick_counter;
            uint64_t        issue_iq0_pick_on_forward_counter;

            //
            std::bitset<6>  issue_iq1_pick_valid;
            std::bitset<6>  issue_iq1_pick_en;

            std::bitset<6>  issue_iq1_pick_on_forward;

            uint64_t        issue_iq1_pick_valid_counter    [6];
            uint64_t        issue_iq1_pick_en_counter       [6];

            uint64_t        issue_iq1_pick_counter;
            uint64_t        issue_iq1_pick_on_forward_counter;

            //
            std::bitset<6>  issue_iq2_pick_valid;
            std::bitset<6>  issue_iq2_pick_en;

            std::bitset<6>  issue_iq2_pick_on_forward;

            uint64_t        issue_iq2_pick_valid_counter    [6];
            uint64_t        issue_iq2_pick_en_counter       [6];

            uint64_t        issue_iq2_pick_counter;
            uint64_t        issue_iq2_pick_on_forward_counter;

            //
            std::bitset<6>  issue_iq3_pick_valid;
            std::bitset<6>  issue_iq3_pick_en;

            std::bitset<6>  issue_iq3_pick_on_forward;

            uint64_t        issue_iq3_pick_valid_counter    [6];
            uint64_t        issue_iq3_pick_en_counter       [6];

            uint64_t        issue_iq3_pick_counter;
            uint64_t        issue_iq3_pick_on_forward_counter;

        public:
            PPI() noexcept;

            void            Reset() noexcept;
        };  

    private:
        unsigned int                    eventBusId;

    private:
        VerilatedVcdC*                  fp; // to form *.vcd file

        DS232*                          core;
        SoCAXIBridgeDualChannel*        soc_axi;

        FetchIDTracker                  fid_tracker;

        bool                            next_reset;

        vluint64_t                      eval_time;

        PPI                             ppi;

    protected:
        friend class Builder;

        Thinpad(unsigned int eventBusId, VerilatedVcdC* fp, NSCSCCSingle::NSCSCC2023SoC* soc) noexcept;

    private:
        void                            _EvalCoreClockPositive() noexcept;
        void                            _EvalCoreClockNegative() noexcept;

    public:
        ~Thinpad() noexcept;
        Thinpad(Thinpad&&) noexcept;

        Thinpad(const Thinpad&) = delete;

        unsigned int                    GetEventBusId() const noexcept;

        PPI&                            GetPPI() noexcept;
        const PPI&                      GetPPI() const noexcept;

        VerilatedVcdC*                  GetVCD() noexcept;
        const VerilatedVcdC*            GetVCD() const noexcept;

        DS232*                          GetCore() noexcept;
        const DS232*                    GetCore() const noexcept;

        SoCAXIBridgeDualChannel*        GetSoCAXI() noexcept;
        const SoCAXIBridgeDualChannel*  GetSoCAXI() const noexcept;

        FetchIDTracker&                 GetFetchIDTracker() noexcept;
        const FetchIDTracker&           GetFetchIDTracker() const noexcept;

        vluint64_t                      GetEvalTime() const noexcept;

        void                            NextReset(bool reset = true) noexcept;

        void                            Eval() noexcept;
    };

    // Draconids 3014 Thinpad Builder
    class Thinpad::Builder {
    private:
        unsigned int                    eventBusId;

        VerilatedVcdC*                  fp; // to form *.vcd file
        NSCSCCSingle::NSCSCC2023SoC*    soc;

    public:
        Builder() noexcept;
        ~Builder() noexcept;

        Builder&                            EventBusId(unsigned int eventBusId) noexcept;
        Builder&                            VCD(VerilatedVcdC* fp) noexcept;
        Builder&                            SoC(NSCSCCSingle::NSCSCC2023SoC* soc) noexcept;

        unsigned int                        GetEventBusId() const noexcept;
        void                                SetEventBusId(unsigned int eventBusId) noexcept;

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
