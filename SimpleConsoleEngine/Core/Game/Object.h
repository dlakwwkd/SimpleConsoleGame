#pragma once
#include "../Console/Coord.hpp"
#include "../Console/Shape.hpp"
SCE_START


class SCE_API Object
{
    SPECIALFUNC_SET(Object, default)
public:
    Object()
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

    inline bool     IsShow() const noexcept { return m_IsShow; }
    inline BYTE     GetDepth() const noexcept { return m_Depth; }
    inline Coord    GetCoord() const noexcept { return m_Coord; }
    inline Shape    GetShape() const noexcept { return m_Shape; }
    inline wchar_t  GetForm() const noexcept { return m_Shape.GetForm(); }
    inline Color    GetColor() const noexcept { return m_Shape.GetColor(); }
    inline Color    GetBGColor() const noexcept { return m_Shape.GetBGColor(); }

    inline void     SetShow(bool isShow) noexcept { m_IsShow = isShow; }
    inline void     SetDepth(BYTE depth) noexcept { m_Depth = depth; }
    inline void     SetCoord(const Coord& coord) noexcept { m_Coord = coord; }
    inline void     SetCoord(short x, short y) noexcept { m_Coord.m_X = x; m_Coord.m_Y = y; }
    inline void     SetShape(const Shape& shape) noexcept { m_Shape = shape; }
    inline void     SetForm(wchar_t form) noexcept { m_Shape.SetForm(form); }
    inline void     SetColor(Color color) noexcept { m_Shape.SetColor(color); }
    inline void     SetBGColor(Color bgColor) noexcept { m_Shape.SetBGColor(bgColor); }

protected:
    bool    m_IsShow;
    BYTE    m_Depth;
    Coord   m_Coord;
    Shape   m_Shape;
};

SCE_END


