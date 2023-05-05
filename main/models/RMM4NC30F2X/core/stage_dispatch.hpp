#pragma once
//
// Dispatch Stage models for RMM4NC30F2X (Gemini 30F2)
//
//
//

#include <cstdint>
#include <bitset>

#include "common/nonstdint.hpp"

#include "models/common/dff.hpp"
#include "models/common/sram.hpp"
#include "models/common/axi.hpp"

#include "models/util/mips32helper.hpp"


#include "def_global.hpp"
#include "stage_global.hpp"

#include "stage_fetch.hpp"
#include "stage_decode.hpp"
#include "stage_issue.hpp"


namespace BullsEye::Gemini30F2::Dispatch {

    using FromIssue     = Issue::Issue::ToDispatch;

    using ToExecute     = FromIssue;
}


namespace BullsEye::Gemini30F2::Dispatch {

    // Dispatch DFFs
    class DispatchDFFs {
    public:
        using FromIssue         = FromIssue;

    private:
        SteppingDFF<FromIssue, decltype([] (FromIssue& obj) {
            obj.valid = false;
        })>                         dff;

        bool                        next_bco_valid;

    public:
        DispatchDFFs() noexcept;
        ~DispatchDFFs() noexcept;

        void        NextFromIssue(const FromIssue& bundle) noexcept;

        void        NextBranchCommitOverride(bool bco_valid) noexcept;

        void        NextReset() noexcept;

        FromIssue   GetLastFromIssue() const noexcept;

        void        Reset() noexcept;
        void        Eval() noexcept;
    };


    // Dispatch AIO
    class Dispatch {
    public:
        using FromIssue         = DispatchDFFs::FromIssue;

        using ToExecute         = ToExecute;

    private:
        DispatchDFFs        module_dffs;

    public:
        Dispatch() noexcept;
        ~Dispatch() noexcept;

        void        NextFromIssue(const FromIssue& bundle) noexcept;

        void        NextBranchCommitOverride(bool bco_valid) noexcept;

        void        NextReset() noexcept;

        ToExecute   GetLastToExecute() const noexcept;

        void        Reset() noexcept;
        void        Eval() noexcept;
    };
};


// Implementation of: class DispatchDFFs
namespace BullsEye::Gemini30F2::Dispatch {
    //
    // SteppingDFF<FromIssue, decltype([] (FromIssue& obj) {
    //     obj.valid = false;
    // })>                         dff;
    //
    // bool                        next_bco_valid;
    //

    DispatchDFFs::DispatchDFFs() noexcept
        : dff               ()
        , next_bco_valid    (false)
    { }

    DispatchDFFs::DispatchDFFs() noexcept
    { }

    inline void DispatchDFFs::NextFromIssue(const FromIssue& bundle) noexcept 
    {
        dff.Next(bundle);
    }

    inline void DispatchDFFs::NextBranchCommitOverride(bool bco_valid) noexcept
    {
        next_bco_valid = bco_valid;
    }

    inline void DispatchDFFs::NextReset() noexcept
    {
        dff.NextReset();
    }

    inline FromIssue DispatchDFFs::GetLastFromIssue() const noexcept
    {
        return dff.Get();
    }

    void DispatchDFFs::Reset() noexcept
    {
        dff.Reset();
    }

    void DispatchDFFs::Eval() noexcept
    {
        //
        if (next_bco_valid)
            dff.GetNext().valid = false;

        //
        dff.Eval();
    }
}


// Implementation of: class Dispatch
namespace BullsEye::Gemini30F2::Dispatch {
    //
    // DispatchDFFs        module_dffs;
    //

    Dispatch::Dispatch() noexcept
        : module_dffs   ()
    { }

    Dispatch::~Dispatch() noexcept
    { }

    inline void Dispatch::NextFromIssue(const FromIssue& bundle) noexcept
    {
        module_dffs.NextFromIssue(bundle);
    }

    inline void Dispatch::NextBranchCommitOverride(bool bco_valid) noexcept
    {
        module_dffs.NextBranchCommitOverride(bco_valid);
    }

    inline void Dispatch::NextReset() noexcept
    {
        module_dffs.NextReset();
    }

    inline ToExecute Dispatch::GetLastToExecute() const noexcept
    {
        return module_dffs.GetLastFromIssue();
    }

    void Dispatch::Reset() noexcept
    {
        module_dffs.Reset();
    }

    void Dispatch::Eval() noexcept
    {
        module_dffs.Eval();
    }
}
