#pragma once
#include "Color.hpp"
#include "Coord.h"
SCE_START


class Console
{
    DECLARE_PIMPL
    CREATE_SINGLETON_NOEXCEPT(Console)
public:
    void    Init() noexcept;
    void    Release() noexcept;

    size_t  GetDrawCallNum() const noexcept;
    Coord   GetScreenSize() const noexcept;
    short   GetScreenWidth() const noexcept;
    short   GetScreenHeight() const noexcept;

    void    PrintText(const Coord& _pos, const std::wstring& _text) noexcept;
    void    Print(const Coord& _pos, wchar_t _word) noexcept;
    void    SetColor(Color _textColor, Color _bgColor = Color::BLACK) const noexcept;
    void    Clear() noexcept;
    void    SwapBuffer() noexcept;
    bool    DepthCheck(const Coord& _pos, BYTE _depth = 0) noexcept;
};

SCE_END
