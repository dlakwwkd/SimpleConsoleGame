#pragma once
SCE_START
struct Coord;
struct Shape;

/////////////////////////////////////////////////////////////////////////////////////////
class Console
{
    DECLARE_PIMPL
    CREATE_SINGLETON_NOEXCEPT(Console)
public:
    void    Init() noexcept;
    void    Release() noexcept;

    Coord   GetScreenSize() const noexcept;
    short   GetScreenWidth() const noexcept;
    short   GetScreenHeight() const noexcept;

    void    Clear() noexcept;
    void    SwapBuffer() noexcept;
    void    PrintText(const Coord& _pos, const std::wstring& _text) noexcept;
    bool    DepthCheck(const Coord& _pos, BYTE _depth = 0) noexcept;
    void    StoreShape(const Coord& _pos, const Shape& _shape) noexcept;
};

SCE_END
