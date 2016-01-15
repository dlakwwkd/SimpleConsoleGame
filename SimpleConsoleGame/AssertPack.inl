// AssertPack.inl : 자주 사용하는 assert 구문에 대한 인라인 함수 패키지

#define TYPE(T) (T)0 // 타입 정보를 매개변수로 넘기기 위한 용도

namespace BitCarc
{
    template<typename T>
    inline size_t   GetBitSize(T&&)
    {
        return sizeof(T) << 3;
    }

    template<typename S, typename T>
    inline S        CarcRestBits(const S& source, T&&)
    {
        static_assert(std::is_integral<S>::value && std::is_integral<T>::value, "it's not integral type!");
        assert(GetBitSize(TYPE(T)) <= 32 && "it's over shift operator limit");
        return std::is_signed<S>::value ? source >> (GetBitSize(TYPE(T)) - 1) : (source >> (GetBitSize(TYPE(T)) - 1)) >> 1;
    }
}

namespace Assert
{
    template<typename S, typename T>
    inline void OverflowCheck(const S& source, T&&)
    {
        static_assert(std::is_integral<S>::value && std::is_integral<T>::value, "it's not integral type!");
        assert((!BitCarc::CarcRestBits(source, TYPE(T)) || !~(BitCarc::CarcRestBits(source, TYPE(T)))) && "it's overflow!");
//         /* 테스트 코드 출력 용 */
//         std::bitset<32> bit[5];
//         bit[0] = source;
//         bit[1] = BitCarc::GetBitSize(TYPE(T));
//         bit[2] = BitCarc::CarcRestBits(source, TYPE(T));
//         bit[3] = !BitCarc::CarcRestBits(source, TYPE(T));
//         bit[4] = !~(BitCarc::CarcRestBits(source, TYPE(T)));
//         for (int i = 0; i < 5; ++i)
//             std::cout << bit[i] << std::endl;
//         std::cout << std::endl;
    }
}

namespace Safe
{
    template<typename S, typename T>
    inline T IntegralCast(const S& source, T&&)
    {
        Assert::OverflowCheck(source, TYPE(T));
        return static_cast<T>(source);
    }
}
