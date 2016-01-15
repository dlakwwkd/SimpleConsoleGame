// AssertPack.h : "AssertPack.inl"의 선언부만을 담기 위한 헤더
#pragma once
namespace BitCarc
{
    template<typename T>                inline size_t   GetBitSize(T&&);
    template<typename S, typename T>    inline S        CarcRestBits(const S& source, T&&);
}
namespace Assert
{
    template<typename S, typename T>    inline void     OverflowCheck(const S& source, T&&);
}
namespace Safe
{
    template<typename S, typename T>    inline T        IntegralCast(const S& source, T&&);
}
#include "AssertPack.inl"
