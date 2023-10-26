#pragma once
//
// D Flip-Flop programming model
//
//

#include <algorithm>


namespace BullsEye {


    //
    template<class _TResetRoutine, class _T>
    concept ResetRoutineConcept = requires (_TResetRoutine routine, _T& dst) {
        _TResetRoutine();
        routine(dst);
    };

    // 
    using DFFResetZero      = decltype([] (auto& dst) { dst = 0; });

    //
    template<auto _Val>
    using DFFResetValue     = decltype([] (auto& dst) { dst = _Val; });

    //
    using DFFNoReset        = decltype([] (auto& dst) {});


    // Normal DFF
    template<class _T, ResetRoutineConcept<_T> _TResetRoutine = DFFResetZero>
    class DFF {
    private:
        static const _TResetRoutine     RESET_ROUTINE;

    private:
        _T  val;

    public:
        DFF() noexcept;
        DFF(const _T& val) noexcept;
        DFF(const DFF<_T, _TResetRoutine>& obj) noexcept;

        ~DFF() noexcept;

        _T&                 Get() noexcept;
        const _T&           Get() const noexcept;

        void                Set(const _T& val) noexcept;
        void                Swap(_T& val) noexcept;

        void                Reset() noexcept;
        void                Eval(const _T& val, bool enable = true) noexcept;

        operator            _T() const noexcept;
    };


    // Stepping DFF (Better for overall emulation)
    template<class _T, ResetRoutineConcept<_T> _TResetRoutine = DFFResetZero>
    class SteppingDFF {
    private:
        static const _TResetRoutine     RESET_ROUTINE;

    private:
        _T  val;
        _T  next;

    public:
        SteppingDFF() noexcept;
        SteppingDFF(const _T& val) noexcept;
        SteppingDFF(const SteppingDFF<_T, _TResetRoutine>& obj) noexcept;

        ~SteppingDFF() noexcept;

        _T&                 Get() noexcept;
        const _T&           Get() const noexcept;

        _T&                 GetNext() noexcept;
        const _T&           GetNext() const noexcept;

        void                Set(const _T& val) noexcept;
        void                Swap(_T& val) noexcept;

        void                Next() noexcept;
        void                Next(const _T& val) noexcept;
        void                NextReset() noexcept;

        void                Reset() noexcept;
        void                Eval(bool enable = true) noexcept;

        operator            _T() const noexcept;
    };
}


// Implementation of: class DFF
namespace BullsEye {
    //
    // _T  val;
    //

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    DFF<_T, _TResetRoutine>::DFF() noexcept
        : val   ()
    { 
        RESET_ROUTINE(val);
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    DFF<_T, _TResetRoutine>::DFF(const _T& val) noexcept
        : val   (val)
    { }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    DFF<_T, _TResetRoutine>::DFF(const DFF<_T, _TResetRoutine>& obj) noexcept
        : val   (obj.val)
    { }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    DFF<_T, _TResetRoutine>::~DFF() noexcept
    { }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline _T& DFF<_T, _TResetRoutine>::Get() noexcept
    {
        return val;
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline const _T& DFF<_T, _TResetRoutine>::Get() const noexcept
    {
        return val;
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline void DFF<_T, _TResetRoutine>::Set(const _T& val) noexcept
    {
        this->val = val;
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline void DFF<_T, _TResetRoutine>::Swap(_T& val) noexcept
    {
        std::swap(this->val, val);
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline void DFF<_T, _TResetRoutine>::Reset() noexcept
    {
        RESET_ROUTINE(val);
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline void DFF<_T, _TResetRoutine>::Eval(const _T& val, bool enable) noexcept
    {
        if (enable)
            this->val = val;
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline DFF<_T, _TResetRoutine>::operator _T() const noexcept
    {
        return val;
    }
}


// Implementation of: class SteppingDFF
namespace BullsEye {
    //
    // _T  val;
    // _T  next;
    //

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    SteppingDFF<_T, _TResetRoutine>::SteppingDFF() noexcept
        : val   ()
        , next  ()
    { 
        RESET_ROUTINE(val);
        RESET_ROUTINE(next);
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    SteppingDFF<_T, _TResetRoutine>::SteppingDFF(const _T& val) noexcept
        : val   (val)
        , next  (val)
    { }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    SteppingDFF<_T, _TResetRoutine>::SteppingDFF(const SteppingDFF<_T, _TResetRoutine>& obj) noexcept
        : val   (obj.val)
        , next  (obj.next)
    { }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    SteppingDFF<_T, _TResetRoutine>::~SteppingDFF() noexcept
    { }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline _T& SteppingDFF<_T, _TResetRoutine>::Get() noexcept
    {
        return val;
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline const _T& SteppingDFF<_T, _TResetRoutine>::Get() const noexcept
    {
        return val;
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline _T& SteppingDFF<_T, _TResetRoutine>::GetNext() noexcept
    {
        return next;
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline const _T& SteppingDFF<_T, _TResetRoutine>::GetNext() const noexcept
    {
        return next;
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline void SteppingDFF<_T, _TResetRoutine>::Set(const _T& val) noexcept
    {
        this->val = val;
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline void SteppingDFF<_T, _TResetRoutine>::Swap(_T& val) noexcept
    {
        std::swap(this->val, val);
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline void SteppingDFF<_T, _TResetRoutine>::Next() noexcept
    {
        next = val;
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline void SteppingDFF<_T, _TResetRoutine>::Next(const _T& val) noexcept
    {
        next = val;
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline void SteppingDFF<_T, _TResetRoutine>::NextReset() noexcept
    {
        RESET_ROUTINE(next);
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline void SteppingDFF<_T, _TResetRoutine>::Reset() noexcept
    {
        RESET_ROUTINE(val);
        RESET_ROUTINE(next);
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline void SteppingDFF<_T, _TResetRoutine>::Eval(bool enable) noexcept
    {
        if (enable)
            val = next;
    }

    template<class _T, ResetRoutineConcept<_T> _TResetRoutine>
    inline SteppingDFF<_T, _TResetRoutine>::operator _T() const noexcept
    {
        return val;
    }
}
