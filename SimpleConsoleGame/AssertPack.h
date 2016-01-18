// AssertPack.h : "AssertPack.inl"의 선언부만을 담기 위한 헤더
#pragma once

//template<typename T> constexpr T Type() { return 0; }
//template<typename T> struct Type { static constexpr T value = 0; };

namespace BitCalc   // 비트 단위 연산을 제공해주는 함수들
{
    template<typename T>                inline constexpr size_t BitSize();
    template<typename T, typename S>    inline constexpr S      CalcRestBits(const S& source);
}
namespace Assert    // 릴리즈 빌드에선 컴파일 되지 않음이 보장되는 디버깅용 함수들
{
    template<typename T, typename S>    inline void OverflowCheck(const S& source);
}
namespace Safe      // Assert를 통해 디버그 빌드에선 절대 안전성을 보장하는 함수들
{
    template<typename T, typename S>    inline T    IntegralCast(const S& source);
}
#include "AssertPack.inl"
