#pragma once
//
// SRAM programming model
//
//


namespace BullsEye {

    // Simple/Pseudo Dual Port RAM model
    template<class _T, size_t _Isize>
    class DualPortRAM {
    private:
        _T*     ram;

        bool    next_write_a_enable;
        size_t  next_write_a_address;
        _T      next_write_a_data;

        size_t  next_read_b_address;

        _T      read_b_data;

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
        void                NextWriteA() noexcept;

        void                NextReadB(size_t address) noexcept;

        _T                  GetLastReadB() const noexcept;

        void                Eval() noexcept;
    };


}


// Implementation of: class DualPortRAM
namespace BullsEye {
    //
    // _T*     ram;
    //
    // bool    next_write_a_enable;
    // size_t  next_write_a_address;
    // _T      next_write_a_data;
    //
    // size_t  next_read_b_address;
    //
    // _T      read_b_data;
    //

    template<class _T, size_t _Isize>
    DualPortRAM<_T, _Isize>::DualPortRAM() noexcept
        : ram    (new _T[_Isize])
    { }

    template<class _T, size_t _Isize>
    DualPortRAM<_T, _Isize>::~DualPortRAM() noexcept
    {
        delete[] ram;
    }

    template<class _T, size_t _Isize>
    inline constexpr size_t DualPortRAM<_T, _Isize>::GetSize() const noexcept
    {
        return _Isize;
    }

    template<class _T, size_t _Isize>
    inline constexpr bool DualPortRAM<_T, _Isize>::CheckBound(size_t address) const noexcept
    {
        return address < _Isize;
    }

    template<class _T, size_t _Isize>
    inline _T& DualPortRAM<_T, _Isize>::At(size_t address) noexcept
    {
        return ram[address];
    }

    template<class _T, size_t _Isize>
    inline const _T& DualPortRAM<_T, _Isize>::At(size_t address) const noexcept
    {
        return ram[address];
    }

    template<class _T, size_t _Isize>
    inline _T DualPortRAM<_T, _Isize>::Get(size_t address) const noexcept
    {
        return ram[address];
    }

    template<class _T, size_t _Isize>
    inline void DualPortRAM<_T, _Isize>::Set(size_t address, const _T& data) noexcept
    {
        ram[address] = data;
    }

    template<class _T, size_t _Isize>
    inline void DualPortRAM<_T, _Isize>::NextWriteA(size_t address, _T data) noexcept
    {
        next_write_a_enable     = true;
        next_write_a_address    = address;
        next_write_a_data       = data;
    }

    template<class _T, size_t _Isize>
    inline void DualPortRAM<_T, _Isize>::NextWriteA(bool enable, size_t address, _T data) noexcept
    {
        if (enable)
            NextWriteA(address, data);
    }

    template<class _T, size_t _Isize>
    inline void DualPortRAM<_T, _Isize>::NextWriteA() noexcept
    {
        next_write_a_enable = false;
    }

    template<class _T, size_t _Isize>
    inline void DualPortRAM<_T, _Isize>::NextReadB(size_t address) noexcept
    {
        next_read_b_address = address;
    }

    template<class _T, size_t _Isize>
    inline _T DualPortRAM<_T, _Isize>::GetLastReadB() const noexcept
    {
        return read_b_data;
    }

    template<class _T, size_t _Isize>
    inline void DualPortRAM<_T, _Isize>::Eval() noexcept
    {
        read_b_data = ram[next_read_b_address];

        if (next_write_a_enable)
        {
            ram[next_write_a_address] = next_write_a_data;
            next_write_a_enable = false;
        }
    }
}
