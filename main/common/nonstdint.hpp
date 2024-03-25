#pragma once
//
// Non-standard truncated integer templates
//
//

#include <concepts>
#include <type_traits>
#ifndef __BULLSEYE_UTILITY__NONSTDINT
#define __BULLSEYE_UTILITY__NONSTDINT


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
    template<unsigned _Len>
    struct uint_fit { using type = void; };

    template<unsigned _Len>
    using uint_fit_t = typename uint_fit<_Len>::type;

    template<> struct uint_fit<1>       { using type = uint1_t; };
    template<> struct uint_fit<2>       { using type = uint2_t; };
    template<> struct uint_fit<3>       { using type = uint3_t; };
    template<> struct uint_fit<4>       { using type = uint4_t; };
    template<> struct uint_fit<5>       { using type = uint5_t; };
    template<> struct uint_fit<6>       { using type = uint6_t; };
    template<> struct uint_fit<7>       { using type = uint7_t; };
    template<> struct uint_fit<8>       { using type = uint8_t; };

    template<> struct uint_fit<9>       { using type = uint9_t; };
    template<> struct uint_fit<10>      { using type = uint10_t; };
    template<> struct uint_fit<11>      { using type = uint11_t; };
    template<> struct uint_fit<12>      { using type = uint12_t; };
    template<> struct uint_fit<13>      { using type = uint13_t; };
    template<> struct uint_fit<14>      { using type = uint14_t; };
    template<> struct uint_fit<15>      { using type = uint15_t; };
    template<> struct uint_fit<16>      { using type = uint16_t; };

    template<> struct uint_fit<17>      { using type = uint17_t; };
    template<> struct uint_fit<18>      { using type = uint18_t; };
    template<> struct uint_fit<19>      { using type = uint19_t; };
    template<> struct uint_fit<20>      { using type = uint20_t; };
    template<> struct uint_fit<21>      { using type = uint21_t; };
    template<> struct uint_fit<22>      { using type = uint22_t; };
    template<> struct uint_fit<23>      { using type = uint23_t; };
    template<> struct uint_fit<24>      { using type = uint24_t; };
    template<> struct uint_fit<25>      { using type = uint25_t; };
    template<> struct uint_fit<26>      { using type = uint26_t; };
    template<> struct uint_fit<27>      { using type = uint27_t; };
    template<> struct uint_fit<28>      { using type = uint28_t; };
    template<> struct uint_fit<29>      { using type = uint29_t; };
    template<> struct uint_fit<30>      { using type = uint30_t; };
    template<> struct uint_fit<31>      { using type = uint31_t; };
    template<> struct uint_fit<32>      { using type = uint32_t; };

    template<> struct uint_fit<33>      { using type = uint33_t; };
    template<> struct uint_fit<34>      { using type = uint34_t; };
    template<> struct uint_fit<35>      { using type = uint35_t; };
    template<> struct uint_fit<36>      { using type = uint36_t; };
    template<> struct uint_fit<37>      { using type = uint37_t; };
    template<> struct uint_fit<38>      { using type = uint38_t; };
    template<> struct uint_fit<39>      { using type = uint39_t; };
    template<> struct uint_fit<40>      { using type = uint40_t; };
    template<> struct uint_fit<41>      { using type = uint41_t; };
    template<> struct uint_fit<42>      { using type = uint42_t; };
    template<> struct uint_fit<43>      { using type = uint43_t; };
    template<> struct uint_fit<44>      { using type = uint44_t; };
    template<> struct uint_fit<45>      { using type = uint45_t; };
    template<> struct uint_fit<46>      { using type = uint46_t; };
    template<> struct uint_fit<47>      { using type = uint47_t; };
    template<> struct uint_fit<48>      { using type = uint48_t; };
    template<> struct uint_fit<49>      { using type = uint49_t; };
    template<> struct uint_fit<50>      { using type = uint50_t; };
    template<> struct uint_fit<51>      { using type = uint51_t; };
    template<> struct uint_fit<52>      { using type = uint52_t; };
    template<> struct uint_fit<53>      { using type = uint53_t; };
    template<> struct uint_fit<54>      { using type = uint54_t; };
    template<> struct uint_fit<55>      { using type = uint55_t; };
    template<> struct uint_fit<56>      { using type = uint56_t; };
    template<> struct uint_fit<57>      { using type = uint57_t; };
    template<> struct uint_fit<58>      { using type = uint58_t; };
    template<> struct uint_fit<59>      { using type = uint59_t; };
    template<> struct uint_fit<60>      { using type = uint60_t; };
    template<> struct uint_fit<61>      { using type = uint61_t; };
    template<> struct uint_fit<62>      { using type = uint62_t; };
    template<> struct uint_fit<63>      { using type = uint63_t; };
    template<> struct uint_fit<64>      { using type = uint64_t; };
    

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
    template<unsigned _Len>
    struct int_fit { using type = void; };

    template<unsigned _Len>
    using int_fit_t = typename int_fit<_Len>::type;

    template<> struct int_fit<1>        { using type = int1_t; };
    template<> struct int_fit<2>        { using type = int2_t; };
    template<> struct int_fit<3>        { using type = int3_t; };
    template<> struct int_fit<4>        { using type = int4_t; };
    template<> struct int_fit<5>        { using type = int5_t; };
    template<> struct int_fit<6>        { using type = int6_t; };
    template<> struct int_fit<7>        { using type = int7_t; };
    template<> struct int_fit<8>        { using type = int8_t; };

    template<> struct int_fit<9>        { using type = int9_t; };
    template<> struct int_fit<10>       { using type = int10_t; };
    template<> struct int_fit<11>       { using type = int11_t; };
    template<> struct int_fit<12>       { using type = int12_t; };
    template<> struct int_fit<13>       { using type = int13_t; };
    template<> struct int_fit<14>       { using type = int14_t; };
    template<> struct int_fit<15>       { using type = int15_t; };
    template<> struct int_fit<16>       { using type = int16_t; };

    template<> struct int_fit<17>       { using type = int17_t; };
    template<> struct int_fit<18>       { using type = int18_t; };
    template<> struct int_fit<19>       { using type = int19_t; };
    template<> struct int_fit<20>       { using type = int20_t; };
    template<> struct int_fit<21>       { using type = int21_t; };
    template<> struct int_fit<22>       { using type = int22_t; };
    template<> struct int_fit<23>       { using type = int23_t; };
    template<> struct int_fit<24>       { using type = int24_t; };
    template<> struct int_fit<25>       { using type = int25_t; };
    template<> struct int_fit<26>       { using type = int26_t; };
    template<> struct int_fit<27>       { using type = int27_t; };
    template<> struct int_fit<28>       { using type = int28_t; };
    template<> struct int_fit<29>       { using type = int29_t; };
    template<> struct int_fit<30>       { using type = int30_t; };
    template<> struct int_fit<31>       { using type = int31_t; };
    template<> struct int_fit<32>       { using type = int32_t; };

    template<> struct int_fit<33>       { using type = int33_t; };
    template<> struct int_fit<34>       { using type = int34_t; };
    template<> struct int_fit<35>       { using type = int35_t; };
    template<> struct int_fit<36>       { using type = int36_t; };
    template<> struct int_fit<37>       { using type = int37_t; };
    template<> struct int_fit<38>       { using type = int38_t; };
    template<> struct int_fit<39>       { using type = int39_t; };
    template<> struct int_fit<40>       { using type = int40_t; };
    template<> struct int_fit<41>       { using type = int41_t; };
    template<> struct int_fit<42>       { using type = int42_t; };
    template<> struct int_fit<43>       { using type = int43_t; };
    template<> struct int_fit<44>       { using type = int44_t; };
    template<> struct int_fit<45>       { using type = int45_t; };
    template<> struct int_fit<46>       { using type = int46_t; };
    template<> struct int_fit<47>       { using type = int47_t; };
    template<> struct int_fit<48>       { using type = int48_t; };
    template<> struct int_fit<49>       { using type = int49_t; };
    template<> struct int_fit<50>       { using type = int50_t; };
    template<> struct int_fit<51>       { using type = int51_t; };
    template<> struct int_fit<52>       { using type = int52_t; };
    template<> struct int_fit<53>       { using type = int53_t; };
    template<> struct int_fit<54>       { using type = int54_t; };
    template<> struct int_fit<55>       { using type = int55_t; };
    template<> struct int_fit<56>       { using type = int56_t; };
    template<> struct int_fit<57>       { using type = int57_t; };
    template<> struct int_fit<58>       { using type = int58_t; };
    template<> struct int_fit<59>       { using type = int59_t; };
    template<> struct int_fit<60>       { using type = int60_t; };
    template<> struct int_fit<61>       { using type = int61_t; };
    template<> struct int_fit<62>       { using type = int62_t; };
    template<> struct int_fit<63>       { using type = int63_t; };
    template<> struct int_fit<64>       { using type = int64_t; };


    //
    struct _truncated_bits {};


    //
    template<class _Tsv, class _Tuv, unsigned _L>
    struct _truncated_uint_base : public _truncated_bits {
    private:
        static constexpr _Tuv       MASK            = (_Tuv(1) << _L) - 1;
        static constexpr unsigned   SIGN_SHIFT      = sizeof(_Tuv) * 8 - _L;

    public:
        static constexpr _Tuv       MAX             = MASK;
        static constexpr _Tuv       MIN             = 0;
        static constexpr unsigned   BITS            = _L;

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
    struct _truncated_int_base : public _truncated_bits {
    private:
        static constexpr _Tuv       MASK            = (_Tuv(1) << _L) - 1;
        static constexpr unsigned   SIGN_SHIFT      = sizeof(_Tuv) * 8 - _L;

    public:
        static constexpr _Tuv       MAX             = MASK >> 1;
        static constexpr _Tuv       MIN             = (~MAX) & MASK;
        static constexpr unsigned   BITS            = _L;

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

    
    //
    template<class T>
    concept _truncated_bits_concept = std::derived_from<T, _truncated_bits>;

    /*
    * bit_len_of<T>
    */
    template<class T>
    struct bit_len_of : std::integral_constant<unsigned, sizeof(T) * 8> {};

    template<_truncated_bits_concept T>
    struct bit_len_of<T> : std::integral_constant<unsigned, T::BITS> {};

    template<class T>
    inline constexpr unsigned bit_len_of_v = bit_len_of<T>::value;

    /*
    * is_same_leng<T, U>
    */
    template<class T, class U>
    struct is_same_len : std::integral_constant<bool, bit_len_of_v<T> == bit_len_of_v<U>> {};

    template<class T, class U>
    inline constexpr bool is_same_len_v = is_same_len<T, U>::value;


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

#endif // BULLSEYE_NONSTDINT_HPP
