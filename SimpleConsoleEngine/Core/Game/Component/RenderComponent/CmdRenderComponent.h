#pragma once
#include "../IRenderComponent.h"
#include "../../../Console/Coord.h"
#include "../../../Console/Shape.h"
SCE_START


class CmdRenderComponent : public IRenderComponent
{
public:
    CmdRenderComponent();
    virtual ~CmdRenderComponent() override;

    virtual std::string     GetComponentName() const override;
    virtual IComponentPtr   Copy() const override;
    virtual void            Init() override;
    virtual void            Release() override;
    virtual void            Render() override;

    bool    IsShow() const;
    BYTE    GetDepth() const;
    Coord   GetCoord() const;
    Shape   GetShape() const;
    wchar_t GetForm() const;
    Color   GetColor() const;
    Color   GetBGColor() const;

    void    SetShow(bool isShow);
    void    SetDepth(BYTE depth);

    IS_SAME(T, Coord)
    void    SetCoord(T&& coord);
    void    SetCoord(short x, short y);

    IS_SAME(T, Shape)
    void    SetShape(T&& shape);
    void    SetForm(wchar_t form);
    void    SetColor(Color color);
    void    SetBGColor(Color bgColor);

private:
    bool    m_IsShow;
    BYTE    m_Depth;
    Coord   m_Coord;
    Shape   m_Shape;
};


CHECKED_T(T)
void CmdRenderComponent::SetCoord(T&& coord)
{
    m_Coord = std::forward<T>(coord);
}

CHECKED_T(T)
void CmdRenderComponent::SetShape(T&& shape)
{
    m_Shape = std::forward<T>(shape);
}

SCE_END
