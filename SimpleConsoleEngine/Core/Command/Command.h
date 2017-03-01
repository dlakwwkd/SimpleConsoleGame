#pragma once
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
class Command
{
public:
    enum KeyType
    {
        ENTER = 0,
        ESC,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        BUTTON_A,
        BUTTON_B,
        BUTTON_C,
        BUTTON_D,
        TOTAL_KEY_NUM
    };
    constexpr Command() noexcept;

    template<KeyType type> constexpr int    GetKey() const noexcept;
    template<KeyType type> void             SetKey(int _key) noexcept;
    template<KeyType type> bool             IsKeyPress() const noexcept;

private:
    std::array<int, KeyType::TOTAL_KEY_NUM> keyArr;
};

SCE_END
#include "Command.inl"
