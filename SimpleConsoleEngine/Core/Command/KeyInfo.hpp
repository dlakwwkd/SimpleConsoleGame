#pragma once
SCE_START


class SCE_API KeyInfo
{
public:
    enum KeyType : unsigned
    {
        UP = 0,
        DOWN,
        LEFT,
        RIGHT,
        BUTTON_A,
        BUTTON_B,
        BUTTON_C,
        BUTTON_D,
        KEYTYPE_END
    };
public:
    KeyInfo()
    :   m_Key{ 
        VK_UP,
        VK_DOWN,
        VK_LEFT,
        VK_RIGHT,
        'z',
        'x',
        'c',
        'v'}
    {
    }
    ~KeyInfo() {}

    void    SetKey(KeyType type, int key) { if (type < KEYTYPE_END) m_Key[type] = key; }
    int     GetKey(KeyType type) { if (type < KEYTYPE_END) return m_Key[type]; }

private:
    int m_Key[KeyType::KEYTYPE_END];
};

SCE_END
