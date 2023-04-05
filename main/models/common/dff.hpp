#pragma once
//
// D Flip-Flop programming model
//
//

#include <algorithm>


namespace BullsEye {

    // Normal DFF
    template<class _T, _T _ResetValue>
    class DFF {
    private:
        _T  val;

    public:
        DFF(const _T& val = _ResetValue) noexcept;
        DFF(const DFF<_T, _ResetValue>& obj) noexcept;

        ~DFF() noexcept;

        _T&                 Get() noexcept;
        const _T&           Get() const noexcept;

        void                Set(const _T& val) noexcept;
        void                Swap(_T& val) noexcept;

        void                Reset() noexcept;
        void                Eval(const _T& val, bool enable = true) noexcept;
    };


    // Stepping DFF (Better for overall emulation)
    template<class _T, _T _ResetValue>
    class SteppingDFF {
    private:
        _T  val;
        _T  next;

    public:
        SteppingDFF(const _T& val = _ResetValue) noexcept;
        SteppingDFF(const SteppingDFF<_T, _ResetValue>& obj) noexcept;

        ~SteppingDFF() noexcept;

        _T&                 Get() noexcept;
        const _T&           Get() const noexcept;

        void                Set(const _T& val) noexcept;
        void                Swap(_T& val) noexcept;

        _T&                 Next() noexcept; 
        const _T&           Next() const noexcept;
        void                Next(const _T& val) noexcept;
        void                NextReset() noexcept;

        void                Reset() noexcept;
        void                Eval(bool enable = true) noexcept;
    };
}


// Implementation of: class DFF
namespace BullsEye {
    //
    // _T  val;
    //

    template<class _T, _T _ResetValue>
    DFF<_T, _ResetValue>::DFF(const _T& val) noexcept
        : val   (val)
    { }

    template<class _T, _T _ResetValue>
    DFF<_T, _ResetValue>::DFF(const DFF<_T, _ResetValue>& obj) noexcept
        : val   (obj.val)
    { }

    template<class _T, _T _ResetValue>
    DFF<_T, _ResetValue>::~DFF() noexcept
    { }

    template<class _T, _T _ResetValue>
    inline _T& DFF<_T, _ResetValue>::Get() noexcept
    {
        return val;
    }

    template<class _T, _T _ResetValue>
    inline const _T& DFF<_T, _ResetValue>::Get() const noexcept
    {
        return val;
    }

    template<class _T, _T _ResetValue>
    inline void DFF<_T, _ResetValue>::Set(const _T& val) noexcept
    {
        this->val = val;
    }

    template<class _T, _T _ResetValue>
    inline void DFF<_T, _ResetValue>::Swap(_T& val) noexcept
    {
        std::swap(this->val, val);
    }

    template<class _T, _T _ResetValue>
    inline void DFF<_T, _ResetValue>::Reset() noexcept
    {
        val = _ResetValue;
    }

    template<class _T, _T _ResetValue>
    inline void DFF<_T, _ResetValue>::Eval(const _T& val, bool enable) noexcept
    {
        if (enable)
            this->val = val;
    }
}


// Implementation of: class SteppingDFF
namespace BullsEye {
    //
    // _T  val;
    // _T  next;
    //

    template<class _T, _T _ResetValue>
    SteppingDFF<_T, _ResetValue>::SteppingDFF(const _T& val) noexcept
        : val   (val)
        , next  (val)
    { }

    template<class _T, _T _ResetValue>
    SteppingDFF<_T, _ResetValue>::SteppingDFF(const SteppingDFF<_T, _ResetValue>& obj) noexcept
        : val   (obj.val)
        , next  (obj.next)
    { }

    template<class _T, _T _ResetValue>
    SteppingDFF<_T, _ResetValue>::~SteppingDFF() noexcept
    { }

    template<class _T, _T _ResetValue>
    inline _T& SteppingDFF<_T, _ResetValue>::Get() noexcept
    {
        return val;
    }

    template<class _T, _T _ResetValue>
    inline const _T& SteppingDFF<_T, _ResetValue>::Get() const noexcept
    {
        return val;
    }

    template<class _T, _T _ResetValue>
    inline void SteppingDFF<_T, _ResetValue>::Set(const _T& val) noexcept
    {
        this->val = val;
    }

    template<class _T, _T _ResetValue>
    inline void SteppingDFF<_T, _ResetValue>::Swap(_T& val) noexcept
    {
        std::swap(this->val, val);
    }

    template<class _T, _T _ResetValue>
    inline _T& SteppingDFF<_T, _ResetValue>::Next() noexcept
    {
        return next;
    }

    template<class _T, _T _ResetValue>
    inline const _T& SteppingDFF<_T, _ResetValue>::Next() const noexcept
    {
        return next;
    }

    template<class _T, _T _ResetValue>
    inline void SteppingDFF<_T, _ResetValue>::Next(const _T& val) noexcept
    {
        next = val;
    }

    template<class _T, _T _ResetValue>
    inline void SteppingDFF<_T, _ResetValue>::NextReset() noexcept
    {
        next = _ResetValue;
    }

    template<class _T, _T _ResetValue>
    inline void SteppingDFF<_T, _ResetValue>::Reset() noexcept
    {
        val  = _ResetValue;
        next = _ResetValue;
    }

    template<class _T, _T _ResetValue>
    inline void SteppingDFF<_T, _ResetValue>::Eval(bool enable) noexcept
    {
        if (enable)
            val = next;
    }
}
