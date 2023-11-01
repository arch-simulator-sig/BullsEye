#include "ds232_fetch.hpp"


// Implementation of: class FetchIDTrack
namespace BullsEye::Draconids3014 {
    /*
    fid_t           fid;

    Jasse::pc_t     pc;
    uop40_t         uop;
    */

    fid_t FetchIDTrack::GetFetchID() const noexcept 
    {
        return this->fid;
    }

    void FetchIDTrack::SetFetchID(fid_t fid) noexcept 
    {
        this->fid = fid;
    }

    Jasse::pc_t FetchIDTrack::GetPC() const noexcept 
    {
        return this->pc;
    }

    void FetchIDTrack::SetPC(Jasse::pc_t pc) noexcept 
    {
        this->pc = pc;
    }

    uop40_t FetchIDTrack::GetUOP() const noexcept 
    {
        return this->uop;
    }

    void FetchIDTrack::SetUOP(uop40_t uop) noexcept 
    {
        this->uop = uop;
    }
}


// Implementation of: class FetchIDTracker
namespace BullsEye::Draconids3014 {
    /*
    FetchIDTrack    tracks[256];
    */

    FetchIDTracker::FetchIDTracker() noexcept
        : tracks    ()
    {
        for (size_t fid = 0; fid < 256; fid++) 
            this->tracks[fid].SetFetchID(fid);
    }

    const FetchIDTrack& FetchIDTracker::Get(fid_t fid) const noexcept 
    {
        return this->tracks[fid];
    }

    void FetchIDTracker::Set(fid_t fid, const FetchIDTrack& track) noexcept 
    {
        this->tracks[fid] = track;
    }

    void FetchIDTracker::Set(fid_t fid, Jasse::pc_t pc, uop40_t uop) noexcept 
    {
        this->tracks[fid].SetPC(pc);
        this->tracks[fid].SetUOP(uop);
    }

    FetchIDTrack& FetchIDTracker::At(fid_t fid) noexcept 
    {
        return this->tracks[fid];
    }

    const FetchIDTrack& FetchIDTracker::At(fid_t fid) const noexcept 
    {
        return this->tracks[fid];
    }

    FetchIDTrack& FetchIDTracker::operator[](fid_t fid) noexcept 
    {
        return this->tracks[fid];
    }

    const FetchIDTrack& FetchIDTracker::operator[](fid_t fid) const noexcept 
    {
        return this->tracks[fid];
    }
}
