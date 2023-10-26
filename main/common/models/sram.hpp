#pragma once
//
// SRAM programming model
//
//

#include <cstddef>


namespace BullsEye {


    //
    template<class _T, class _TData, class _TStrobe>
    concept WriteStrobeRoutine = requires (_T routine, _TData& dst, const _TData& src, const _TStrobe& strobe) {
        _T();
        routine(dst, src, strobe);
    };


    // Default Empty Routine
    using NoWriteStrobe     = decltype([] (auto& dst, const auto& src, const auto& strobe) {});


    // Simple/Pseudo Dual Port RAM model
    template<class _T, size_t _Isize, class _TStrobe = _T, WriteStrobeRoutine<_T, _TStrobe> _TStrobeRoutine = NoWriteStrobe>
    class DualPortRAM {
    private:
        static const _TStrobeRoutine        STROBE_ROUTINE;

    private:
        _T*         ram;

        bool        next_write_a_enable;
        size_t      next_write_a_address;
        _T          next_write_a_data;
        bool        next_write_a_with_strobe;
        _TStrobe    next_write_a_strobe;

        size_t      next_read_b_address;

        _T          read_b_data;

    public:
        DualPortRAM() noexcept;
        ~DualPortRAM() noexcept;

        constexpr size_t    GetSize() const noexcept;
        constexpr bool      CheckBound(size_t address) const noexcept;

        _T&                 At(size_t addres) noexcept;
        const _T&           At(size_t address) const noexcept;
        _T                  Get(size_t address) const noexcept;
        void                Set(size_t address, const _T& data) noexcept;

        void                NextWriteA(size_t address, _T data) noexcept;
        void                NextWriteA(bool enable, size_t address, _T data) noexcept;
        void                NextWriteA(bool enable, size_t address, _T data, _TStrobe strobe, bool with_strobe = true) noexcept;
        void                NextWriteA() noexcept;

        void                NextReadB(size_t address) noexcept;

        _T                  GetLastReadB() const noexcept;

        void                Eval() noexcept;
    };


}


// Implementation of: class DualPortRAM
namespace BullsEye {
    //
    // _T*         ram;
    //
    // bool        next_write_a_enable;
    // size_t      next_write_a_address;
    // _T          next_write_a_data;
    // bool        next_write_a_with_strobe;
    // _TStrobe    next_write_a_strobe;
    //
    // size_t      next_read_b_address;
    //
    // _T          read_b_data;
    //

    template<class _T, size_t _Isize, class _TStrobe, WriteStrobeRoutine<_T, _TStrobe> _TStrobeRoutine>
    DualPortRAM<_T, _Isize, _TStrobe, _TStrobeRoutine>::DualPortRAM() noexcept
        : ram                       (new _T[_Isize])
        , next_write_a_enable       (false)
        , next_write_a_address      ()
        , next_write_a_data         ()
        , next_write_a_with_strobe  (false)
        , next_write_a_strobe       ()
        , next_read_b_address       ()
        , read_b_data               ()
    { }

    template<class _T, size_t _Isize, class _TStrobe, WriteStrobeRoutine<_T, _TStrobe> _TStrobeRoutine>
    DualPortRAM<_T, _Isize, _TStrobe, _TStrobeRoutine>::~DualPortRAM() noexcept
    {
        delete[] ram;
    }

    template<class _T, size_t _Isize, class _TStrobe, WriteStrobeRoutine<_T, _TStrobe> _TStrobeRoutine>
    inline constexpr size_t DualPortRAM<_T, _Isize, _TStrobe, _TStrobeRoutine>::GetSize() const noexcept
    {
        return _Isize;
    }

    template<class _T, size_t _Isize, class _TStrobe, WriteStrobeRoutine<_T, _TStrobe> _TStrobeRoutine>
    inline constexpr bool DualPortRAM<_T, _Isize, _TStrobe, _TStrobeRoutine>::CheckBound(size_t address) const noexcept
    {
        return address < _Isize;
    }

    template<class _T, size_t _Isize, class _TStrobe, WriteStrobeRoutine<_T, _TStrobe> _TStrobeRoutine>
    inline _T& DualPortRAM<_T, _Isize, _TStrobe, _TStrobeRoutine>::At(size_t address) noexcept
    {
        return ram[address];
    }

    template<class _T, size_t _Isize, class _TStrobe, WriteStrobeRoutine<_T, _TStrobe> _TStrobeRoutine>
    inline const _T& DualPortRAM<_T, _Isize, _TStrobe, _TStrobeRoutine>::At(size_t address) const noexcept
    {
        return ram[address];
    }

    template<class _T, size_t _Isize, class _TStrobe, WriteStrobeRoutine<_T, _TStrobe> _TStrobeRoutine>
    inline _T DualPortRAM<_T, _Isize, _TStrobe, _TStrobeRoutine>::Get(size_t address) const noexcept
    {
        return ram[address];
    }

    template<class _T, size_t _Isize, class _TStrobe, WriteStrobeRoutine<_T, _TStrobe> _TStrobeRoutine>
    inline void DualPortRAM<_T, _Isize, _TStrobe, _TStrobeRoutine>::Set(size_t address, const _T& data) noexcept
    {
        ram[address] = data;
    }

    template<class _T, size_t _Isize, class _TStrobe, WriteStrobeRoutine<_T, _TStrobe> _TStrobeRoutine>
    inline void DualPortRAM<_T, _Isize, _TStrobe, _TStrobeRoutine>::NextWriteA(size_t address, _T data) noexcept
    {
        next_write_a_enable         = true;
        next_write_a_address        = address;
        next_write_a_data           = data;
        next_write_a_with_strobe    = false;
    }

    template<class _T, size_t _Isize, class _TStrobe, WriteStrobeRoutine<_T, _TStrobe> _TStrobeRoutine>
    inline void DualPortRAM<_T, _Isize, _TStrobe, _TStrobeRoutine>::NextWriteA(bool enable, size_t address, _T data, _TStrobe strobe, bool with_strobe) noexcept
    {
        if (enable)
        {
            NextWriteA(address, data);

            if (with_strobe)
            {
                next_write_a_with_strobe = true;
                next_write_a_strobe      = strobe;
            }
        }
    }

    template<class _T, size_t _Isize, class _TStrobe, WriteStrobeRoutine<_T, _TStrobe> _TStrobeRoutine>
    inline void DualPortRAM<_T, _Isize, _TStrobe, _TStrobeRoutine>::NextWriteA(bool enable, size_t address, _T data) noexcept
    {
        if (enable)
            NextWriteA(address, data);
    }

    template<class _T, size_t _Isize, class _TStrobe, WriteStrobeRoutine<_T, _TStrobe> _TStrobeRoutine>
    inline void DualPortRAM<_T, _Isize, _TStrobe, _TStrobeRoutine>::NextWriteA() noexcept
    {
        next_write_a_enable = false;
    }

    template<class _T, size_t _Isize, class _TStrobe, WriteStrobeRoutine<_T, _TStrobe> _TStrobeRoutine>
    inline void DualPortRAM<_T, _Isize, _TStrobe, _TStrobeRoutine>::NextReadB(size_t address) noexcept
    {
        next_read_b_address = address;
    }

    template<class _T, size_t _Isize, class _TStrobe, WriteStrobeRoutine<_T, _TStrobe> _TStrobeRoutine>
    inline _T DualPortRAM<_T, _Isize, _TStrobe, _TStrobeRoutine>::GetLastReadB() const noexcept
    {
        return read_b_data;
    }

    template<class _T, size_t _Isize, class _TStrobe, WriteStrobeRoutine<_T, _TStrobe> _TStrobeRoutine>
    inline void DualPortRAM<_T, _Isize, _TStrobe, _TStrobeRoutine>::Eval() noexcept
    {
        read_b_data = ram[next_read_b_address];

        if (next_write_a_enable)
        {
            if (next_write_a_with_strobe)
                _TStrobeRoutine(next_write_a_data, ram[next_write_a_address], next_write_a_strobe);

            ram[next_write_a_address] = next_write_a_data;

            next_write_a_enable         = false;
            next_write_a_with_strobe    = false;
        }
    }
}
