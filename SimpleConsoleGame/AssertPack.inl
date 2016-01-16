// AssertPack.inl : 안전성&효율성 보장되는 인라인 템플릿 함수 패키지

namespace BitCarc
{
    template<typename T>
    inline size_t   GetBitSize(const T&)
    {
        return sizeof(T) << 3;
    }

    template<typename S, typename T>
    inline S        CarcRestBits(const S& source, const T&)
    {
        static_assert(std::is_integral<S>::value && std::is_integral<T>::value, "it's not integral type!");
        assert(GetBitSize(Type<T>::value) <= 32 && "it's over shift operator limit");
        return std::is_signed<S>::value ? source >> (GetBitSize(Type<T>::value) - 1) : (source >> (GetBitSize(Type<T>::value) - 1)) >> 1;
    }
}

namespace Assert
{
    template<typename S, typename T>
    inline void OverflowCheck(const S& source, const T&)
    {
        static_assert(std::is_integral<S>::value && std::is_integral<T>::value, "it's not integral type!");
        assert((!BitCarc::CarcRestBits(source, Type<T>::value) || !~(BitCarc::CarcRestBits(source, Type<T>::value))) && "it's overflow!");
//         /* 테스트 코드 출력 용 */
//         std::bitset<32> bit[5];
//         bit[0] = source;
//         bit[1] = BitCarc::GetBitSize(Type<T>::value);
//         bit[2] = BitCarc::CarcRestBits(source, Type<T>::value);
//         bit[3] = !BitCarc::CarcRestBits(source, Type<T>::value);
//         bit[4] = !~(BitCarc::CarcRestBits(source, Type<T>::value));
//         for (int i = 0; i < 5; ++i)
//             std::cout << bit[i] << std::endl;
//         std::cout << std::endl;
    }
}

namespace Safe
{
    template<typename S, typename T>
    inline T IntegralCast(const S& source, const T&)
    {
        Assert::OverflowCheck(source, Type<T>::value);
        return static_cast<T>(source);
    }
}
