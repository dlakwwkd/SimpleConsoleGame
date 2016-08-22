#pragma once
#include "RenderComponent.h"
#include "../../Console/Coord.hpp"
#include "../../Console/Shape.hpp"
SCE_START


class SCE_API CmdRenderComponent : public RenderComponent
{
public:
    CmdRenderComponent()
    :   m_IsShow(true),
        m_Depth(0),
        m_Coord{ 0,0 }
    {
    }

    virtual std::string GetComponentName() const override;
    virtual IComponent* CopyCreate() const override;

    virtual void        Init() override;
    virtual void        Release() override;
    virtual void        Render() override;

    bool    IsShow() const noexcept { return m_IsShow; }
    BYTE    GetDepth() const noexcept { return m_Depth; }
    Coord   GetCoord() const noexcept { return m_Coord; }
    Shape   GetShape() const noexcept { return m_Shape; }
    wchar_t GetForm() const noexcept { return m_Shape.GetForm(); }
    Color   GetColor() const noexcept { return m_Shape.GetColor(); }
    Color   GetBGColor() const noexcept { return m_Shape.GetBGColor(); }

    void    SetShow(bool isShow) noexcept { m_IsShow = isShow; }
    void    SetDepth(BYTE depth) noexcept { m_Depth = depth; }

    template<IS_SAME(T, Coord)>
    void    SetCoord(T&& coord) noexcept { m_Coord = std::forward<T>(coord); }
    void    SetCoord(short x, short y) noexcept { m_Coord.m_X = x; m_Coord.m_Y = y; }

    template<IS_SAME(T, Shape)>
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
