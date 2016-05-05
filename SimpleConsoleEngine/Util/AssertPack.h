#pragma once

// 비트 단위 연산을 제공해주는 함수들
namespace BitCalc
{
    template<typename T>                inline constexpr size_t BitSize() noexcept;
    template<typename T, typename S>    inline constexpr S      CalcRestBits(const S& source) noexcept;
}

// 릴리즈 빌드에선 컴파일 되지 않음이 보장되는 디버깅용 함수들
namespace Assert
{
    template<typename T, typename S>    inline void OverflowCheck(const S& source) noexcept;
}

// Assert를 통해 디버그 빌드에선 절대 안전성을 보장하는 함수들
namespace Safe
{
    template<typename T, typename S>    inline T    IntegralCast(const S& source) noexcept;
    template<typename T>                inline T*   New() noexcept;
    template<typename T>                inline void Delete(T* ptr) noexcept;
}

#include "AssertPack.inl"
