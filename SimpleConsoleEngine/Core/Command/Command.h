#pragma once
SCE_START


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
public:
    constexpr Command() noexcept;

    template<KeyType type> constexpr int    GetKey() const noexcept;
    template<KeyType type> void             SetKey(int key) noexcept;
    template<KeyType type> bool             IsKeyPress() const noexcept;

private:
    std::array<int, KeyType::TOTAL_KEY_NUM> m_KeyArr;
};


constexpr Command::Command() noexcept
    : m_KeyArr
        {
            VK_RETURN,
            VK_ESCAPE,
            VK_UP,
            VK_DOWN,
            VK_LEFT,
            VK_RIGHT,
            'Z',
            'X',
            'C',
            'V'
        }
{
}

template<Command::KeyType type>
constexpr int Command::GetKey() const noexcept
{
    static_assert(type < KeyType::TOTAL_KEY_NUM, "KeyType is invalid");
    return m_KeyArr[type];
}

template<Command::KeyType type>
void Command::SetKey(int key) noexcept
{
    static_assert(type < KeyType::TOTAL_KEY_NUM, "KeyType is invalid");
    m_KeyArr[type] = key;
}

template<Command::KeyType type>
bool Command::IsKeyPress() const noexcept
{
    static_assert(type < KeyType::TOTAL_KEY_NUM, "KeyType is invalid");
    return GetAsyncKeyState(m_KeyArr[type]) & 0x8000 ? true : false;
}

SCE_END
