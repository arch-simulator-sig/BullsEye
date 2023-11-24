#pragma once
//
// Non-standard truncated integer templates
//
//

#include <cstdint>


/*
namespace BullsEye {
    */

    //
    typedef     unsigned char       uchar;
    typedef     unsigned short      ushort;
    typedef     unsigned int        uint;
    typedef     unsigned long       ulong;
    typedef     unsigned long long  ulonglong;


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
    struct _truncated_int_base;
    
    template<class _Tsv, class _Tuv, unsigned _L>
    struct _truncated_uint_base;


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
    using uint1_t               = truncated_uint8_t<1>;
    using uint2_t               = truncated_uint8_t<2>;
    using uint3_t               = truncated_uint8_t<3>;
    using uint4_t               = truncated_uint8_t<4>;
    using uint5_t               = truncated_uint8_t<5>;
    using uint6_t               = truncated_uint8_t<6>;
    using uint7_t               = truncated_uint8_t<7>;

    using uint9_t               = truncated_uint16_t<9>;
    using uint10_t              = truncated_uint16_t<10>;
    using uint11_t              = truncated_uint16_t<11>;
    using uint12_t              = truncated_uint16_t<12>;
    using uint13_t              = truncated_uint16_t<13>;
    using uint14_t              = truncated_uint16_t<14>;
    using uint15_t              = truncated_uint16_t<15>;

    using uint17_t              = truncated_uint32_t<17>;
    using uint18_t              = truncated_uint32_t<18>;
    using uint19_t              = truncated_uint32_t<19>;
    using uint20_t              = truncated_uint32_t<20>;
    using uint21_t              = truncated_uint32_t<21>;
    using uint22_t              = truncated_uint32_t<22>;
    using uint23_t              = truncated_uint32_t<23>;
    using uint24_t              = truncated_uint32_t<24>;
    using uint25_t              = truncated_uint32_t<25>;
    using uint26_t              = truncated_uint32_t<26>;
    using uint27_t              = truncated_uint32_t<27>;
    using uint28_t              = truncated_uint32_t<28>;
    using uint29_t              = truncated_uint32_t<29>;
    using uint30_t              = truncated_uint32_t<30>;
    using uint31_t              = truncated_uint32_t<31>;

    using uint33_t              = truncated_uint64_t<33>;
    using uint34_t              = truncated_uint64_t<34>;
    using uint35_t              = truncated_uint64_t<35>;
    using uint36_t              = truncated_uint64_t<36>;
    using uint37_t              = truncated_uint64_t<37>;
    using uint38_t              = truncated_uint64_t<38>;
    using uint39_t              = truncated_uint64_t<39>;
    using uint40_t              = truncated_uint64_t<40>;
    using uint41_t              = truncated_uint64_t<41>;
    using uint42_t              = truncated_uint64_t<42>;
    using uint43_t              = truncated_uint64_t<43>;
    using uint44_t              = truncated_uint64_t<44>;
    using uint45_t              = truncated_uint64_t<45>;
    using uint46_t              = truncated_uint64_t<46>;
    using uint47_t              = truncated_uint64_t<47>;
    using uint48_t              = truncated_uint64_t<48>;
    using uint49_t              = truncated_uint64_t<49>;
    using uint50_t              = truncated_uint64_t<50>;
    using uint51_t              = truncated_uint64_t<51>;
    using uint52_t              = truncated_uint64_t<52>;
    using uint53_t              = truncated_uint64_t<53>;
    using uint54_t              = truncated_uint64_t<54>;
    using uint55_t              = truncated_uint64_t<55>;
    using uint56_t              = truncated_uint64_t<56>;
    using uint57_t              = truncated_uint64_t<57>;
    using uint58_t              = truncated_uint64_t<58>;
    using uint59_t              = truncated_uint64_t<59>;
    using uint60_t              = truncated_uint64_t<60>;
    using uint61_t              = truncated_uint64_t<61>;
    using uint62_t              = truncated_uint64_t<62>;
    using uint63_t              = truncated_uint64_t<63>;


    //
    using int1_t                = truncated_int8_t<1>;
    using int2_t                = truncated_int8_t<2>;
    using int3_t                = truncated_int8_t<3>;
    using int4_t                = truncated_int8_t<4>;
    using int5_t                = truncated_int8_t<5>;
    using int6_t                = truncated_int8_t<6>;
    using int7_t                = truncated_int8_t<7>;

    using int9_t                = truncated_int16_t<9>;
    using int10_t               = truncated_int16_t<10>;
    using int11_t               = truncated_int16_t<11>;
    using int12_t               = truncated_int16_t<12>;
    using int13_t               = truncated_int16_t<13>;
    using int14_t               = truncated_int16_t<14>;
    using int15_t               = truncated_int16_t<15>;
    
    using int17_t               = truncated_int32_t<17>;
    using int18_t               = truncated_int32_t<18>;
    using int19_t               = truncated_int32_t<19>;
    using int20_t               = truncated_int32_t<20>;
    using int21_t               = truncated_int32_t<21>;
    using int22_t               = truncated_int32_t<22>;
    using int23_t               = truncated_int32_t<23>;
    using int24_t               = truncated_int32_t<24>;
    using int25_t               = truncated_int32_t<25>;
    using int26_t               = truncated_int32_t<26>;
    using int27_t               = truncated_int32_t<27>;
    using int28_t               = truncated_int32_t<28>;
    using int29_t               = truncated_int32_t<29>;
    using int30_t               = truncated_int32_t<30>;
    using int31_t               = truncated_int32_t<31>;

    using int33_t               = truncated_int64_t<33>;
    using int34_t               = truncated_int64_t<34>;
    using int35_t               = truncated_int64_t<35>;
    using int36_t               = truncated_int64_t<36>;
    using int37_t               = truncated_int64_t<37>;
    using int38_t               = truncated_int64_t<38>;
    using int39_t               = truncated_int64_t<39>;
    using int40_t               = truncated_int64_t<40>;
    using int41_t               = truncated_int64_t<41>;
    using int42_t               = truncated_int64_t<42>;
    using int43_t               = truncated_int64_t<43>;
    using int44_t               = truncated_int64_t<44>;
    using int45_t               = truncated_int64_t<45>;
    using int46_t               = truncated_int64_t<46>;
    using int47_t               = truncated_int64_t<47>;
    using int48_t               = truncated_int64_t<48>;
    using int49_t               = truncated_int64_t<49>;
    using int50_t               = truncated_int64_t<50>;
    using int51_t               = truncated_int64_t<51>;
    using int52_t               = truncated_int64_t<52>;
    using int53_t               = truncated_int64_t<53>;
    using int54_t               = truncated_int64_t<54>;
    using int55_t               = truncated_int64_t<55>;
    using int56_t               = truncated_int64_t<56>;
    using int57_t               = truncated_int64_t<57>;
    using int58_t               = truncated_int64_t<58>;
    using int59_t               = truncated_int64_t<59>;
    using int60_t               = truncated_int64_t<60>;
    using int61_t               = truncated_int64_t<61>;
    using int62_t               = truncated_int64_t<62>;
    using int63_t               = truncated_int64_t<63>;


    //
    template<class _Tsv, class _Tuv, unsigned _L>
    struct _truncated_uint_base {
    private:
        static constexpr _Tuv       MASK            = (_Tuv(1) << _L) - 1;
        static constexpr unsigned   SIGN_SHIFT      = sizeof(_Tuv) * 8 - _L;

    private:
        _Tuv    val;

    public:
        using value_type = _Tuv;

    public:
        constexpr _truncated_uint_base() noexcept;
        constexpr _truncated_uint_base(const _truncated_uint_base<_Tsv, _Tuv, _L>&) noexcept;
        constexpr _truncated_uint_base(const _truncated_int_base<_Tsv, _Tuv, _L>&) noexcept;
        constexpr _truncated_uint_base(_Tuv val) noexcept;

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

        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator<<(int) const noexcept;
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator>>(int) const noexcept;

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

        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator<<=(int) noexcept;
        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  operator>>=(int) noexcept;

        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  to_unsigned() const noexcept;
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   to_signed() const noexcept;

        constexpr operator      _truncated_int_base<_Tsv, _Tuv, _L>() const noexcept;
        constexpr operator      _Tuv() const noexcept;
        explicit constexpr operator bool() const noexcept;
    };


    //
    template<class _Tsv, class _Tuv, unsigned _L>
    struct _truncated_int_base {
    private:
        static constexpr _Tuv       MASK            = (_Tuv(1) << _L) - 1;
        static constexpr unsigned   SIGN_SHIFT      = sizeof(_Tuv) * 8 - _L;

    private:
        _Tsv    val;

    public:
        using value_type = _Tsv;

    public:
        constexpr _truncated_int_base() noexcept;
        constexpr _truncated_int_base(const _truncated_uint_base<_Tsv, _Tuv, _L>&) noexcept;
        constexpr _truncated_int_base(const _truncated_int_base<_Tsv, _Tuv, _L>&) noexcept;
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

        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator<<(int) const noexcept;
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator>>(int) const noexcept;

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

        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator<<=(int) noexcept;
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   operator>>=(int) noexcept;

        constexpr _truncated_uint_base<_Tsv, _Tuv, _L>  to_unsigned() const noexcept;
        constexpr _truncated_int_base<_Tsv, _Tuv, _L>   to_signed() const noexcept;

        constexpr operator      _truncated_uint_base<_Tsv, _Tuv, _L>() const noexcept;
        constexpr operator      _Tsv() const noexcept;
        explicit constexpr operator bool() const noexcept;
    };

    /*
}
*/


// Implementation of: struct _truncated_uint_base
/*
namespace BullsEye {
    */
    //
    // _Tuv    val;
    //

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L>::_truncated_uint_base() noexcept
        : val()
    { }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L>::_truncated_uint_base(const _truncated_uint_base<_Tsv, _Tuv, _L>& other) noexcept
        : val(other.val)
    { }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L>::_truncated_uint_base(const _truncated_int_base<_Tsv, _Tuv, _L>& other) noexcept
        : val(static_cast<_Tuv>(other))
    { }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L>::_truncated_uint_base(_Tuv val) noexcept
        : val(val)
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
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator<<(int n) const noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val << n);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator>>(int n) const noexcept
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
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator<<=(int n) noexcept
    {
        return _truncated_uint_base<_Tsv, _Tuv, _L>(val <<= n);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L> _truncated_uint_base<_Tsv, _Tuv, _L>::operator>>=(int n) noexcept
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
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L>::operator _Tuv() const noexcept
    {
        return val & MASK;
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_uint_base<_Tsv, _Tuv, _L>::operator bool() const noexcept
    {
        return (val & MASK) != 0;
    }
    /*
}
*/


// Implementation of: struct truncated_int_base
/*
namespace BullsEye {
    */
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
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator<<(int n) const noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val << n);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator>>(int n) const noexcept
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
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator<<=(int n) noexcept
    {
        return _truncated_int_base<_Tsv, _Tuv, _L>(val <<= n);
    }

    template<class _Tsv, class _Tuv, unsigned _L>
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L> _truncated_int_base<_Tsv, _Tuv, _L>::operator>>=(int n) noexcept
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
    inline constexpr _truncated_int_base<_Tsv, _Tuv, _L>::operator bool() const noexcept
    {
        return (val & MASK) != 0;
    }
    /*
}
*/
