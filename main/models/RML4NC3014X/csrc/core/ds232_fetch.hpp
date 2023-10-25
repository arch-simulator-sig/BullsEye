#pragma once

#ifndef __HEADER_DS232__CORE_FETCH
#define __HEADER_DS232__CORE_FETCH


#include "autoinclude.h"

#include AUTOINC_BE_JASSE2_LA32(la32.hpp)


#include "ds232_def.hpp"
#include "ds232_uop40.hpp"


namespace BullsEye::Draconids3014 {

    class FetchIDTrack;
    class FetchIDTracker;


    class FetchIDTrack {
    private:
        fid_t           fid;

        Jasse::pc_t     pc;
        uop40_t         uop;

    protected:
        friend class FetchIDTracker;

        void            SetFetchID(fid_t fid) noexcept;

    public:
        fid_t           GetFetchID() const noexcept;

        Jasse::pc_t     GetPC() const noexcept;
        void            SetPC(Jasse::pc_t pc) noexcept;

        uop40_t         GetUOP() const noexcept;
        void            SetUOP(uop40_t uop) noexcept;
    };

    class FetchIDTracker {
    private:
        FetchIDTrack    tracks[256];

    public:
        FetchIDTracker() noexcept;

        const FetchIDTrack& Get(fid_t fid) const noexcept;

        void                Set(fid_t fid, const FetchIDTrack& track) noexcept;
        void                Set(fid_t fid, Jasse::pc_t pc, uop40_t uop) noexcept;

        FetchIDTrack&       At(fid_t fid) noexcept;
        const FetchIDTrack& At(fid_t fid) const noexcept;

        FetchIDTrack&       operator[](fid_t fid) noexcept;
        const FetchIDTrack& operator[](fid_t fid) const noexcept;
    };
}


#endif
