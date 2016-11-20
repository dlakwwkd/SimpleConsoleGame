#pragma once
#include "../../Interface/IRenderComponent.h"
#include "../../../Console/Coord.h"
#include "../../../Console/Shape.h"
SCE_START


class CmdRenderComponent : public IRenderComponent
{
    SPECIALFUNC_SET(CmdRenderComponent, default)
public:
    CmdRenderComponent(const CompositeRef& owner) noexcept;
    virtual ~CmdRenderComponent() override;

    virtual void            Init() override;
    virtual void            Release() override;
    virtual void            Update(float dt) override;

    virtual std::string     GetComponentName() const override;
    virtual CompositePtr    GetOwner() const override;
    virtual IComponentPtr   Copy() const override;

    virtual void            Render() override;

public:
    bool                    IsShow() const;
    BYTE                    GetDepth() const;
    Coord                   GetCoord() const;
    Shape                   GetShape() const;
    wchar_t                 GetForm() const;
    Color                   GetColor() const;
    Color                   GetBGColor() const;

    void                    SetShow(bool isShow);
    void                    SetDepth(BYTE depth);
    void                    SetCoord(const Coord& coord);
    void                    SetCoord(short x, short y);
    void                    SetShape(const Shape& shape);
    void                    SetShape(wchar_t form, Color color = Color::WHITE, Color bgColor = Color::BLACK);
    void                    SetForm(wchar_t form);
    void                    SetColor(Color color);
    void                    SetBGColor(Color bgColor);

private:
    CompositeRef            m_Owner;
    bool                    m_IsShow;
    BYTE                    m_Depth;
    Coord                   m_Coord;
    Shape                   m_Shape;
};

SCE_END
