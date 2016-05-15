#pragma once
SCE_START


class SCE_API Command
{
public:
    enum KeyType : size_t
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
    Command() : m_KeyArr{ VK_RETURN, VK_ESCAPE, VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, 'Z', 'X', 'C', 'V' }
    {
    }

    int GetKey(KeyType type) const noexcept
    {
        if (type < m_KeyArr.size())
        {
            return m_KeyArr[type];
        }
        assert(false && "KeyType is invalid");
        return 0;
    }
    void SetKey(KeyType type, int key) noexcept
    {
        if (type < m_KeyArr.size())
        {
            m_KeyArr[type] = key;
        }
        assert(false && "KeyType is invalid");
    }
    bool IsKeyPress(KeyType type) const noexcept
    {
        if (type < m_KeyArr.size())
        {
            return GetAsyncKeyState(m_KeyArr[type]) & 0x8000 ? true : false;
        }
        assert(false && "KeyType is invalid");
        return false;
    }

private:
    std::array<int, KeyType::TOTAL_KEY_NUM> m_KeyArr;
};

SCE_END
