
/////////////////////////////////////////////////////////////////////////////////////////
namespace BitCalc
{
    /////////////////////////////////////////////////////////////////////////////////////
    // 무조건 컴파일 타임 리턴 <- 사실 여기엔 inline, noexcept 등의 키워드가 필요없지만 통일성을 위해 붙여줌
    template<typename T>
    constexpr size_t BitSize() noexcept
    {
        return sizeof(T) << 3;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    // 매개변수가 리터럴일 경우 컴파일 타임 리턴
    template<typename T, typename S>
    constexpr S CalcRestBits(const S& _source) noexcept
    {
        static_assert(std::is_integral<T>::value && std::is_integral<S>::value, "it's not integral type!");
        static_assert(BitSize<T>() <= 32, "it's over that limit of shift operator");
        return std::is_signed<S>::value ? _source >> (BitSize<T>() - 1) : _source >> BitSize<T>();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
namespace Assert
{
    /////////////////////////////////////////////////////////////////////////////////////
    // 변환하려는 타입의 비트범위 바깥에 유효비트가 있는지 체크하는 함수
    template<typename T, typename S>
    constexpr void OverflowCheck(const S& _source) noexcept
    {
        static_assert(std::is_integral<T>::value && std::is_integral<S>::value, "it's not integral type!");
        assert((!BitCalc::CalcRestBits<T>(_source) || !~BitCalc::CalcRestBits<T>(_source)) && "it's overflow!");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
namespace Safe
{
    /////////////////////////////////////////////////////////////////////////////////////
    // 대상이 정수형 타입이고, 데이터 손실이 발생하지 않음이 확인되면, 캐스팅을 진행하는 함수
    template<typename T, typename S>
    constexpr T IntegralCast(const S& _source) noexcept
    {
        Assert::OverflowCheck<T>(_source);
        return static_cast<T>(_source);
    }

    /////////////////////////////////////////////////////////////////////////////////////
    // 메모리 할당 실패 시, assert 발생시키는 new
    template<typename T, typename... Args>
    T* New(Args&&... _args) noexcept
    {
        T* ret = new(std::nothrow) T(std::forward<Args>(_args)...);
        assert(ret != nullptr && "new operate failed!");
        return ret;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    // 포인터가 존재하는지 체크하고, delete 후에 nullptr 대입해주는 delete
    template<typename T>
    void Delete(T* _ptr) noexcept
    {
        if (_ptr != nullptr)
        {
            delete _ptr;
            _ptr = nullptr;
        }
    }
}
