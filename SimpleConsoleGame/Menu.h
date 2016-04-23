#pragma once
class Menu
{
public:
    enum class Type
    {
        NONE,

        MAIN,
        GAME_SELECT,
        SETTING,
        KEY_SETTING,
        PAUSE,

        MAX_MENU_NUM
    };
public:
    Menu(Type menuType);
    ~Menu();

private:
};