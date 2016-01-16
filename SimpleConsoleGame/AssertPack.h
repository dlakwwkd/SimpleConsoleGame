// AssertPack.h : "AssertPack.inl"의 선언부만을 담기 위한 헤더
#pragma once

// 타입 정보를 매개변수로 넘기기 위한 템플릿 클래스
template<typename T> struct Type { static _CONST_DATA T value = 0; };

namespace BitCarc   // 비트 단위 연산을 제공해주는 함수들
{
    template<typename T>                inline size_t   GetBitSize(const T&);
    template<typename S, typename T>    inline S        CarcRestBits(const S& source, const T&);
}
namespace Assert    // 릴리즈 빌드에선 컴파일 되지 않음이 보장되는 디버깅용 함수들
{
    template<typename S, typename T>    inline void     OverflowCheck(const S& source, const T&);
}
namespace Safe      // Assert를 통해 디버그 빌드에선 절대 안전성을 보장하는 함수들
{
    template<typename S, typename T>    inline T        IntegralCast(const S& source, const T&);
}
#include "AssertPack.inl"
