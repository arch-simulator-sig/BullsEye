#pragma once
//
// Non-standard truncated integer templates
//
//

#include <cstdint>


namespace BullsEye {

    //
    template<unsigned _Val>
    concept TL8 =   _Val > 0 && _Val < 8;

    template<unsigned _Val>
    concept TL16 =  _Val > 0 && _Val < 16;

    template<unsigned _Val>
    concept TL32 =  _Val > 0 && _Val < 32;

    template<unsigned _Val>
    concept TL64 =  _Val > 0 && _Val < 64;

    
    //
    template<class _Tsv, class _Tuv, unsigned _L>
    class _truncated_int_base;
    
    template<class _Tsv, class _Tuv, unsigned _L>
    class _truncated_uint_base;


    //
    template<unsigned _Len> requires TL8<_Len>
    using truncated_int8_t      = _truncated_int_base<int8_t, uint8_t, _Len>;

    template<unsigned _Len> requires TL8<_Len>
    using truncated_uint8_t     = _truncated_uint_base<int8_t, uint8_t, _Len>;

    template<unsigned _Len> requires TL16<_Len>
    using truncated_int16_t     = _truncated_int_base<int16_t, uint16_t, _Len>;

    template<unsigned _Len> requires TL16<_Len>
    using truncated_uint16_t    = _truncated_uint_base<int16_t, uint16_t, _Len>;

    template<unsigned _Len> requires TL32<_Len>
    using truncated_int32_t     = _truncated_int_base<int32_t, uint32_t, _Len>;

    template<unsigned _Len> requires TL32<_Len>
    using truncated_uint32_t    = _truncated_uint_base<int32_t, uint32_t, _Len>;

    template<unsigned _Len> requires TL64<_Len>
    using truncated_int64_t     = _truncated_int_base<int64_t, uint64_t, _Len>;

    template<unsigned _Len> requires TL64<_Len>
    using truncated_uint64_t    = _truncated_uint_base<int64_t, uint64_t, _Len>;


    //
    template<class _Tsv, class _Tuv, unsigned _L>
    class _truncated_uint_base {
    private:
        static constexpr _Tuv       MASK            = (_Tuv(1) << _L) - 1;
        static constexpr unsigned   SIGN_SHIFT      = sizeof(_Tuv) * 8 - _L;

    private:
        _Tuv    val;

    public:
        constexpr _truncated_uint_base() noexcept;
        constexpr _truncated_uint_base(const _truncated_uint_base<_Tsv, _Tuv, _L>&) noexcept;
        constexpr _truncated_uint_base(const _truncated_int_base<_Tsv, _Tuv, _L>&) noexcept;
        constexpr _truncated_uint_base(_Tuv val) noexcept;
        constexpr _truncated_uint_base(_Tsv val) noexcept;

        template<class _Tother>
        constexpr bool          operator==(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr bool          operator!=(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr bool          operator<(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr bool          operator>(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr bool          operator<=(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr bool          operator>=(const _Tother&) const noexcept;

        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator~() const noexcept;

        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator<<(unsigned) const noexcept;
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator>>(unsigned) const noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator&(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator|(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator^(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator+(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator-(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator*(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator/(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator%(const _Tother&) const noexcept;

        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator++() noexcept;
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator--() noexcept;

        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator++(int) noexcept;
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator--(int) noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator=(const _Tother&) noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator+=(const _Tother&) noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator-=(const _Tother&) noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator*=(const _Tother&) noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator/=(const _Tother&) noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator%=(const _Tother&) noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator&=(const _Tother&) noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator|=(const _Tother&) noexcept;

        template<class _Tother>
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator^=(const _Tother&) noexcept;

        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator<<=(unsigned) noexcept;
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator>>=(unsigned) noexcept;

        _truncated_uint_base<_Tsv, _Tuv, _L>            to_unsigned() const noexcept;
        _truncated_int_base<_Tsv, _Tuv, _L>             to_signed() const noexcept;

        constexpr operator      _truncated_int_base<_Tsv, _Tuv, _L>() const noexcept;

        constexpr operator      _Tsv() const noexcept;
        constexpr operator      _Tuv() const noexcept;
        constexpr operator      bool() const noexcept;
    };


    //
    template<class _Tsv, class _Tuv, unsigned _L>
    class _truncated_int_base {
    private:
        static constexpr _Tuv       MASK            = (_Tuv(1) << _L) - 1;
        static constexpr unsigned   SIGN_SHIFT      = sizeof(_Tuv) * 8 - _L;

    private:
        _Tsv    val;

    public:
        constexpr _truncated_int_base() noexcept;
        constexpr _truncated_int_base(const _truncated_uint_base<_Tsv, _Tuv, _L>&) noexcept;
        constexpr _truncated_int_base(const _truncated_int_base<_Tsv, _Tuv, _L>&) noexcept;
        constexpr _truncated_int_base(_Tuv val) noexcept;
        constexpr _truncated_int_base(_Tsv val) noexcept;

        template<class _Tother>
        constexpr bool          operator==(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr bool          operator!=(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr bool          operator<(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr bool          operator>(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr bool          operator<=(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr bool          operator>=(const _Tother&) const noexcept;

        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator~() const noexcept;

        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator<<(unsigned) const noexcept;
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator>>(unsigned) const noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator&(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator|(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator^(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator+(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator-(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator*(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator/(const _Tother&) const noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator%(const _Tother&) const noexcept;

        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator++() noexcept;
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator--() noexcept;

        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator++(int) noexcept;
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator--(int) noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator=(const _Tother&) noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator+=(const _Tother&) noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator-=(const _Tother&) noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator*=(const _Tother&) noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator/=(const _Tother&) noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator%=(const _Tother&) noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator&=(const _Tother&) noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator|=(const _Tother&) noexcept;

        template<class _Tother>
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator^=(const _Tother&) noexcept;

        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator<<=(unsigned) noexcept;
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator>>=(unsigned) noexcept;

        _truncated_uint_base<_Tsv, _Tuv, _L>            to_unsigned() const noexcept;
        _truncated_int_base<_Tsv, _Tuv, _L>             to_signed() const noexcept;

        constexpr operator      _truncated_uint_base<_Tsv, _Tuv, _L>() const noexcept;

        constexpr operator      _Tsv() const noexcept;
        constexpr operator      _Tuv() const noexcept;
        constexpr operator      bool() const noexcept;
    };
}


// Implementation of: class _truncated_uint_base
namespace BullsEye {
    //
    // _Tuv    val;
    //

    template<class _Tsv, class _Tuv, unsigned _L>
    constexpr _truncated_uint_base<_Tsv, _Tuv, _L>::_truncated_uint_base() noexcept
        : val()
    { }

    template<class _Tsv, class _Tuv, unsigned _L>
    constexpr _truncated_uint_base<_Tsv, _Tuv, _L>::_truncated_uint_base(const _truncated_uint_base<_Tsv, _Tuv, _L>& other) noexcept
        : val(other.val)
    { }

    template<class _Tsv, class _Tuv, unsigned _L>
    constexpr _truncated_uint_base<_Tsv, _Tuv, _L>::_truncated_uint_base(const _truncated_int_base<_Tsv, _Tuv, _L>& other) noexcept
        : val(static_cast<_Tuv>(other))
    { }

    template<class _Tsv, class _Tuv, unsigned _L>
    constexpr _truncated_uint_base<_Tsv, _Tuv, _L>::_truncated_uint_base(_Tuv val) noexcept
        : val(val)
    { }

    template<class _Tsv, class _Tuv, unsigned _L>
    constexpr _truncated_uint_base<_Tsv, _Tuv, _L>::_truncated_uint_base(_Tsv val) noexcept
        : val(static_cast<_Tuv>(val))
    { }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr bool _truncated_uint_base<_Tsv, _Tuv, _L>::operator==(const _Tother& other) const noexcept
    {
        return static_cast<_Tuv>(*this) == static_cast<_Tuv>(other);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr bool _truncated_uint_base<_Tsv, _Tuv, _L>::operator!=(const _Tother& other) const noexcept
    {
        return static_cast<_Tuv>(*this) != static_cast<_Tuv>(other);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr bool _truncated_uint_base<_Tsv, _Tuv, _L>::operator<(const _Tother& other) const noexcept
    {
        return static_cast<_Tuv>(*this) < static_cast<_Tuv>(other);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr bool _truncated_uint_base<_Tsv, _Tuv, _L>::operator>(const _Tother& other) const noexcept
    {
        return static_cast<_Tuv>(*this) > static_cast<_Tuv>(other);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr bool _truncated_uint_base<_Tsv, _Tuv, _L>::operator<=(const _Tother& other) const noexcept
    {
        return static_cast<_Tuv>(*this) <= static_cast<_Tuv>(other);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr bool _truncated_uint_base<_Tsv, _Tuv, _L>::operator>=(const _Tother& other) const noexcept
    {
        return static_cast<_Tuv>(*this) >= static_cast<_Tuv>(other);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator~() const noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(~val);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator<<(unsigned n) const noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val << n);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator>>(unsigned n) const noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val >> n);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator&(const _Tother& other) const noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val & static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator|(const _Tother& other) const noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val | static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator^(const _Tother& other) const noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val ^ static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator+(const _Tother& other) const noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val + static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator-(const _Tother& other) const noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val - static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator*(const _Tother& other) const noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val * static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator/(const _Tother& other) const noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(static_cast<_Tuv>(*this) / static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator%(const _Tother& other) const noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(static_cast<_Tuv>(*this) % static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator++() noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(++val);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator--() noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(--val);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator++(int) noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val++);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator--(int) noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val--);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator=(const _Tother& other) noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val = static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator+=(const _Tother& other) noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val += static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator-=(const _Tother& other) noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val -= static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator*=(const _Tother& other) noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val *= static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator/=(const _Tother& other) noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val = static_cast<_Tuv>(*this) / static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator%=(const _Tother& other) noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val = static_cast<_Tuv>(*this) % static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator&=(const _Tother& other) noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val &= static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator|=(const _Tother& other) noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val |= static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator^=(const _Tother& other) noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val ^= static_cast<_Tuv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator<<=(unsigned n) noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val <<= n);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator>>=(unsigned n) noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val >>= n);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::to_unsigned() const noexcept
    {
        return *this;
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::to_signed() const noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(*this);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L>::operator _truncated_int_base<_Tsv, _Tuv, _L>() const noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(*this);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L>::operator _Tsv() const noexcept
    {
        return static_cast<_Tsv>(val & MASK);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L>::operator _Tuv() const noexcept
    {
        return val & MASK;
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L>::operator bool() const noexcept
    {
        return (val & MASK) != 0;
    }
}


// Implementation of: class truncated_int_base
namespace BullsEye {
    //
    // _Tsv    val;
    //

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L>::_truncated_int_base() noexcept
        : val()
    { }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L>::_truncated_int_base(const _truncated_uint_base<_Tsv, _Tuv, _L>& other) noexcept
        : val(static_cast<_Tsv>(other))
    { }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L>::_truncated_int_base(const _truncated_int_base<_Tsv, _Tuv, _L>& other) noexcept
        : val(other.val)
    { }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L>::_truncated_int_base(_Tuv val) noexcept
        : val(static_cast<_Tsv>(val))
    { }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L>::_truncated_int_base(_Tsv val) noexcept
        : val(val)
    { }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr bool _truncated_int_base<_Tsv, _Tuv, _L>::operator==(const _Tother& other) const noexcept
    {
        return static_cast<_Tsv>(*this) == static_cast<_Tsv>(other);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr bool _truncated_int_base<_Tsv, _Tuv, _L>::operator!=(const _Tother& other) const noexcept
    {
        return static_cast<_Tsv>(*this) != static_cast<_Tsv>(other);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr bool _truncated_int_base<_Tsv, _Tuv, _L>::operator<(const _Tother& other) const noexcept
    {
        return static_cast<_Tsv>(*this) < static_cast<_Tsv>(other);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr bool _truncated_int_base<_Tsv, _Tuv, _L>::operator>(const _Tother& other) const noexcept
    {
        return static_cast<_Tsv>(*this) > static_cast<_Tsv>(other);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr bool _truncated_int_base<_Tsv, _Tuv, _L>::operator<=(const _Tother& other) const noexcept
    {
        return static_cast<_Tsv>(*this) <= static_cast<_Tsv>(other);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr bool _truncated_int_base<_Tsv, _Tuv, _L>::operator>=(const _Tother& other) const noexcept
    {
        return static_cast<_Tsv>(*this) >= static_cast<_Tsv>(other);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator~() const noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(~val);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator<<(unsigned n) const noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val << n);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator>>(unsigned n) const noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(static_cast<_Tsv>(*this) >> n);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator&(const _Tother& other) const noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val & static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator|(const _Tother& other) const noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val | static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator^(const _Tother& other) const noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val ^ static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator+(const _Tother& other) const noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val + static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator-(const _Tother& other) const noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val - static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator*(const _Tother& other) const noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val * static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator/(const _Tother& other) const noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(static_cast<_Tsv>(*this) / static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator%(const _Tother& other) const noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(static_cast<_Tsv>(*this) % static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator++() noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(++val);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator--() noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(--val);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator++(int) noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val++);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator--(int) noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val--);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator=(const _Tother& other) noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val = static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator+=(const _Tother& other) noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val += static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator-=(const _Tother& other) noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val -= static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator*=(const _Tother& other) noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val *= static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator/=(const _Tother& other) noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(static_cast<_Tsv>(*this) /= static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator%=(const _Tother& other) noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(static_cast<_Tsv>(*this) %= static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator&=(const _Tother& other) noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val &= static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator|=(const _Tother& other) noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val |= static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    template<class _Tother>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator^=(const _Tother& other) noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val ^= static_cast<_Tsv>(other));
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator<<=(unsigned n) noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val <<= n);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator>>=(unsigned n) noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val = static_cast<_Tsv>(*this) >> n);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::to_unsigned() const noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(*this);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::to_signed() const noexcept
    {
        return *this;
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L>::operator _truncated_uint_base<_Tsv, _Tuv, _L>() const noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(*this);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L>::operator _Tsv() const noexcept
    {
        return ((val << SIGN_SHIFT) >> SIGN_SHIFT) & MASK;
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L>::operator _Tuv() const noexcept
    {
        return static_cast<_Tuv>(val);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L>::operator bool() const noexcept
    {
        return val != 0;
    }
}
