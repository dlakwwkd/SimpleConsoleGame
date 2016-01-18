// AssertPack.inl : 안전성&효율성 보장되는 인라인 템플릿 함수 패키지

namespace BitCalc
{
    template<typename T>
    inline constexpr size_t BitSize()   // 무조건 컴파일 타임 리턴 <- 사실 여기엔 inline 키워드 필요없는데 아래와의 통일성을 위해 붙여줌
    {
        return sizeof(T) << 3;
    }

    template<typename T, typename S>
    inline constexpr S CalcRestBits(const S& source)   // 매개변수가 리터럴일 경우 컴파일 타임 리턴
    {
        static_assert(std::is_integral<T>::value && std::is_integral<S>::value, "it's not integral type!");
        static_assert(BitSize<T>() <= 32, "it's over shift operator limit");
        return std::is_signed<S>::value ? source >> (BitSize<T>() - 1) : (source >> (BitSize<T>() - 1)) >> 1;
    }
}

namespace Assert
{
    template<typename T, typename S>
    inline void OverflowCheck(const S& source)
    {
        static_assert(std::is_integral<T>::value && std::is_integral<S>::value, "it's not integral type!");
        assert((!BitCalc::CalcRestBits<T>(source) || !~BitCalc::CalcRestBits<T>(source)) && "it's overflow!");
    }
}

namespace Safe
{
    template<typename T, typename S>
    inline T IntegralCast(const S& source)
    {
        Assert::OverflowCheck<T>(source);
        return static_cast<T>(source);
    }
}
