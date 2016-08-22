namespace BitCalc
{
    // 무조건 컴파일 타임 리턴 <- 사실 여기엔 inline, noexcept 등의 키워드가 필요없지만 통일성을 위해 붙여줌
    template<typename T>
    inline constexpr size_t BitSize() noexcept
    {
        return sizeof(T) << 3;
    }

    // 매개변수가 리터럴일 경우 컴파일 타임 리턴
    template<typename T, typename S>
    inline constexpr S CalcRestBits(const S& source) noexcept
    {
        static_assert(std::is_integral<T>::value && std::is_integral<S>::value, "it's not integral type!");
        static_assert(BitSize<T>() <= 32, "it's over that limit of shift operator");
        return std::is_signed<S>::value ? source >> (BitSize<T>() - 1) : source >> BitSize<T>();
    }
}

namespace Assert
{
    // 변환하려는 타입의 비트범위 바깥에 유효비트가 있는지 체크하는 함수
    template<typename T, typename S>
    inline constexpr void OverflowCheck(const S& source) noexcept
    {
        static_assert(std::is_integral<T>::value && std::is_integral<S>::value, "it's not integral type!");
        assert((!BitCalc::CalcRestBits<T>(source) || !~BitCalc::CalcRestBits<T>(source)) && "it's overflow!");
    }
}

namespace Safe
{
    // 대상이 정수형 타입이고, 데이터 손실이 발생하지 않음이 확인되면, 캐스팅을 진행하는 함수
    template<typename T, typename S>
    inline constexpr T IntegralCast(const S& source) noexcept
    {
        Assert::OverflowCheck<T>(source);
        return static_cast<T>(source);
    }

    // 메모리 할당 실패 시, assert 발생시키는 new
    template<typename T, typename... Args>
    inline T* New(Args&&... args) noexcept
    {
        T* ret = new(std::nothrow) T(std::forward<Args>(args)...);
        assert(ret != nullptr && "new operate failed!");
        return ret;
    }

    // 포인터가 존재하는지 체크하고, delete 후에 nullptr 대입해주는 delete
    template<typename T>
    inline void Delete(T* ptr) noexcept
    {
        if (ptr)
        {
            delete ptr;
            ptr = nullptr;
        }
    }
}
