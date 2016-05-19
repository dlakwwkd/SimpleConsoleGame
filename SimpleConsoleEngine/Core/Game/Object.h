#pragma once
#include "../Console/Coord.hpp"
#include "../Console/Shape.hpp"
#include "Vec2.h"
SCE_START


class SCE_API Object
{
    SPECIALFUNC_SET(Object, default)
public:
    Object() noexcept
    :   m_IsShow(true),
        m_Depth(0),
        m_Coord{ 0,0 }
    {
    }
    virtual ~Object()               = default;
    virtual void Init()             = 0;
    virtual void Release()          = 0;
    virtual void Update(float dt)   = 0;
    virtual void Render() { if (m_IsShow) m_Shape.Render(m_Coord, m_Depth); }

    bool    IsShow() const noexcept { return m_IsShow; }
    BYTE    GetDepth() const noexcept { return m_Depth; }
    Coord   GetCoord() const noexcept { return m_Coord; }
    Shape   GetShape() const noexcept { return m_Shape; }
    wchar_t GetForm() const noexcept { return m_Shape.GetForm(); }
    Color   GetColor() const noexcept { return m_Shape.GetColor(); }
    Color   GetBGColor() const noexcept { return m_Shape.GetBGColor(); }

    void    SetShow(bool isShow) noexcept { m_IsShow = isShow; }
    void    SetDepth(BYTE depth) noexcept { m_Depth = depth; }

    template<typename T, SAMETYPE_CHECK(T, Coord)>
    void    SetCoord(T&& coord) noexcept { m_Coord = std::forward<T>(coord); }
    void    SetCoord(short x, short y) noexcept { m_Coord.m_X = x; m_Coord.m_Y = y; }
    void    SetCoord(const Vec2& pos) noexcept
    {
        m_Coord.m_X = static_cast<short>(pos.m_X * 2.0f);
        m_Coord.m_Y = static_cast<short>(pos.m_Y);
    }

    template<typename T, SAMETYPE_CHECK(T, Shape)>
    void    SetShape(T&& shape) noexcept { m_Shape = std::forward<T>(shape); }
    void    SetForm(wchar_t form) noexcept { m_Shape.SetForm(form); }
    void    SetColor(Color color) noexcept { m_Shape.SetColor(color); }
    void    SetBGColor(Color bgColor) noexcept { m_Shape.SetBGColor(bgColor); }

private:
    bool    m_IsShow;
    BYTE    m_Depth;
    Coord   m_Coord;
    Shape   m_Shape;
};

SCE_END
