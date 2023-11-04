#pragma once
//
//
//
//

#include <vector>
#include <utility>


#include "ds232_def.hpp"
#include "ds232_event.hpp"
#include "ds232_fetch.hpp"


#include "autoinclude.h"

#include AUTOINC_BE_JASSE2_LA32(base/la32def.hpp)
#include AUTOINC_BE_JASSE2_LA32(base/la32mem.hpp)


namespace BullsEye::Draconids3014 {

    // Differential Increment Vector
    template<class _T>
    class DS232IncrementVector {
    private:
        std::vector<_T> vector;

    public:
        DS232IncrementVector() noexcept;

        size_t      GetCount() const noexcept;

        void        Push(const _T& value) noexcept;

        template<class... _Args>
        _T&         Emplace(_Args&&... args) noexcept;

        _T&         Get(size_t index) noexcept;
        const _T&   Get(size_t index) const noexcept;

        _T&         GetLast() noexcept;
        const _T&   GetLast() const noexcept;

        bool        IsEmpty() const noexcept;

        void        Clear() noexcept;
    };


    // Differential Increment Base
    class DS232Increment {
    private:
        size_t      term_count;

    public:
        DS232Increment(size_t term_count = 0) noexcept;

        size_t      GetTermCount() const noexcept;
        void        SetTermCount(size_t term_count) noexcept;
        size_t      IncreaseTermCount() noexcept;
    };


    // Differential Increment of PC
    class DS232IncrementPC : public DS232Increment {
    private:
        pc_t        pc;

    public:
        DS232IncrementPC() noexcept;

        pc_t        GetPC() const noexcept;
        void        SetPC(pc_t pc) noexcept;
    };

    // Differential Increment of Instruction
    class DS232IncrementInstruction : public DS232Increment {
    private:
        insnraw_t   instruction;

    public:
        DS232IncrementInstruction() noexcept;

        insnraw_t   GetInstruction() const noexcept;
        void        SetInstruction(insnraw_t instruction) noexcept;
    };

    // Differential Increment of GPR
    class DS232IncrementGPR : public DS232Increment {
    private:
        unsigned int    gpr_index;
        arch32_t        gpr_value;

    public:
        DS232IncrementGPR() noexcept;

        unsigned int    GetGPRIndex() const noexcept;
        void            SetGPRIndex(unsigned int gpr_index) noexcept;

        arch32_t        GetGPRValue() const noexcept;
        void            SetGPRValue(arch32_t gpr_value) noexcept;

        void            SetGPR(unsigned int gpr_index, arch32_t gpr_value);
    };

    // Differential Increment of Memory Store
    class DS232IncrementMemoryStore : public DS232Increment {
    private:
        lswidth_t   width;
        lsstrb_t    strb;
        addr_t      address;
        uint32_t    data;
        bool        uncached;
    
    public:
        DS232IncrementMemoryStore() noexcept;

        lswidth_t       GetWidth() const noexcept;
        void            SetWidth(lswidth_t width) noexcept;

        lsstrb_t        GetStrobe() const noexcept;
        void            SetStrobe(lsstrb_t strb) noexcept;

        addr_t          GetAddress() const noexcept;
        void            SetAddress(addr_t address) noexcept;

        uint32_t        GetData() const noexcept;
        void            SetData(uint32_t data) noexcept;

        bool            IsUncached() const noexcept;
        void            SetUncached(bool uncached) noexcept;

        void            SetMemoryStore(lswidth_t width, lsstrb_t strb, addr_t address, uint32_t data, bool uncached) noexcept;
    };

    //
    using DS232IncrementVectorPC            = DS232IncrementVector<DS232IncrementPC>;
    using DS232IncrementVectorInstruction   = DS232IncrementVector<DS232IncrementInstruction>;
    using DS232IncrementVectorGPR           = DS232IncrementVector<DS232IncrementGPR>;
    using DS232IncrementVectorMemoryStore   = DS232IncrementVector<DS232IncrementMemoryStore>;



    // DS232 Differential Instance
    class DS232Differential {
    public:
        class Builder;
        
    private:
        FetchIDTracker*                 fidTracker;

        unsigned int                    eventBusId;
        int                             eventPriority;

        bool                            enabledIncrementPC;
        bool                            enabledIncrementInstruction;
        bool                            enabledIncrementGPR;
        bool                            enabledIncrementMemoryStore;

        DS232IncrementVectorPC          incrementPC;
        DS232IncrementVectorInstruction incrementInstruction;
        DS232IncrementVectorGPR         incrementGPR;
        DS232IncrementVectorMemoryStore incrementMemoryStore;

    protected:
        friend class Builder;
        DS232Differential(FetchIDTracker*   fidTracker,
                          unsigned int      eventBusId,
                          int               eventPriority,
                          bool              enabledIncrementPC,
                          bool              enabledIncrementInstruction,
                          bool              enabledIncrementGPR,
                          bool              enabledIncrementMemoryStore) noexcept;

    protected:
        void            OnPreEval(DS232PreEvalEvent& event) noexcept;
        void            OnPostEval(DS232PostEvalEvent& event) noexcept;

        void            OnROBCommit(DS232ROBCommitEvent& event) noexcept;
        void            OnStoreCommit(DS232StoreCommitEvent& event) noexcept;

    protected:
        std::string     GetListenerName(const char* increment_name) const noexcept;

        void            RegisterListeners() noexcept;
        void            UnregisterListeners() noexcept;

    public:
        DS232Differential(const DS232Differential&) = delete;
        DS232Differential(DS232Differential&&) = delete;

        ~DS232Differential() noexcept;

        FetchIDTracker*                         GetFetchIDTracker() noexcept;

        unsigned int                            GetEventBusId() const noexcept;
        int                                     GetEventPriority() const noexcept;

        bool                                    IsEnabledPC() const noexcept;
        bool                                    IsEnabledInstruction() const noexcept;
        bool                                    IsEnabledGPR() const noexcept;
        bool                                    IsEnabledMemoryStore() const noexcept;

        DS232IncrementVectorPC&                 GetIncrementPC() noexcept;
        const DS232IncrementVectorPC&           GetIncrementPC() const noexcept;
        DS232IncrementVectorInstruction&        GetIncrementInstruction() noexcept;
        const DS232IncrementVectorInstruction&  GetIncrementInstruction() const noexcept;
        DS232IncrementVectorGPR&                GetIncrementGPR() noexcept;
        const DS232IncrementVectorGPR&          GetIncrementGPR() const noexcept;
        DS232IncrementVectorMemoryStore&        GetIncrementMemoryStore() noexcept;
        const DS232IncrementVectorMemoryStore&  GetIncrementMemoryStore() const noexcept;

        DS232Differential& operator=(const DS232Differential&) = delete;
        DS232Differential& operator=(DS232Differential&&) = delete;
    };

    // DS232 Differential Instance Builder
    class DS232Differential::Builder {
    private:
        FetchIDTracker*     fidTracker;

        unsigned int        eventBusId;
        int                 eventPriority;

        bool                enabledIncrementPC;
        bool                enabledIncrementInstruction;
        bool                enabledIncrementGPR;
        bool                enabledIncrementMemoryStore;

    public:
        Builder() noexcept;

        //
        Builder&            FIDTracker(FetchIDTracker* fidTracker) noexcept;

        Builder&            EventBusId(unsigned int eventBusId) noexcept;
        Builder&            EventPriority(int eventPriority) noexcept;

        Builder&            EnablePC(bool enabledIncrementPC = true) noexcept;
        Builder&            EnableInstruction(bool enabledIncrementInstruction = true) noexcept;
        Builder&            EnableGPR(bool enabledIncrementGPR = true) noexcept;
        Builder&            EnableMemoryStore(bool enabledIncrementMemoryStore = true) noexcept;

        //
        FetchIDTracker*     GetFIDTracker() noexcept;
        void                SetFIDTracker(FetchIDTracker* fidTracker) noexcept;

        unsigned int        GetEventBusId() const noexcept;
        void                SetEventBusId(unsigned int eventBusId) noexcept;

        int                 GetEventPriority() const noexcept;
        void                SetEventPriority(int eventPriority) noexcept;

        bool                IsEnabledPC() const noexcept;
        void                SetEnabledPC(bool enabledIncrementPC) noexcept;

        bool                IsEnabledInstruction() const noexcept;
        void                SetEnabledInstruction(bool enabledIncrementInstruction) noexcept;

        bool                IsEnabledGPR() const noexcept;
        void                SetEnabledGPR(bool enabledIncrementGPR) noexcept;

        bool                IsEnabledMemoryStore() const noexcept;
        void                SetEnabledMemoryStore(bool enabledIncrementMemoryStore) noexcept;

        //
        DS232Differential*  Build() noexcept;
    };
}



// Implementation of: template class DS232IncrementVector
namespace BullsEye::Draconids3014 {
    /*
    std::vector<_T> vector;
    */
    
    template<class _T>
    inline DS232IncrementVector<_T>::DS232IncrementVector() noexcept
        : vector    () 
    { }

    template<class _T>
    inline size_t DS232IncrementVector<_T>::GetCount() const noexcept
    {
        return vector.size();
    }

    template<class _T>
    inline void DS232IncrementVector<_T>::Push(const _T& value) noexcept
    {
        vector.push_back(value);
    }

    template<class _T>
    template<class... _Args>
    inline _T& DS232IncrementVector<_T>::Emplace(_Args&&... args) noexcept
    {
        return vector.emplace_back(std::forward<_Args>(args)...);
    }

    template<class _T>
    inline _T& DS232IncrementVector<_T>::Get(size_t index) noexcept
    {
        return vector[index];
    }

    template<class _T>
    inline const _T& DS232IncrementVector<_T>::Get(size_t index) const noexcept
    {
        return vector[index];
    }

    template<class _T>
    inline _T& DS232IncrementVector<_T>::GetLast() noexcept
    {
        return vector.back();
    }

    template<class _T>
    inline const _T& DS232IncrementVector<_T>::GetLast() const noexcept
    {
        return vector.back();
    }

    template<class _T>
    inline bool DS232IncrementVector<_T>::IsEmpty() const noexcept
    {
        return vector.empty();
    }

    template<class _T>
    inline void DS232IncrementVector<_T>::Clear() noexcept
    {
        vector.clear();
    }
}
