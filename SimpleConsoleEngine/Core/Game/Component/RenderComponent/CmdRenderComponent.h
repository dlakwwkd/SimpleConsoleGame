#pragma once
#include "../../Interface/Component/IRenderComponent.h"
#include "../../../Console/Coord.h"
#include "../../../Console/Shape.h"
SCE_START


class CmdRenderComponent : public IRenderComponent
{
    DECLARE_PIMPL
    SPECIALFUNC_MOVE_SET(CmdRenderComponent, default)
public:
    CmdRenderComponent(const CompositeRef& _owner) noexcept;
    ~CmdRenderComponent();

    virtual std::string     GetComponentName() const override;
    virtual CompositePtr    GetOwner() const override;

    void                    Render();

    bool                    IsShow() const;
    BYTE                    GetDepth() const;
    Coord                   GetCoord() const;
    Shape                   GetShape() const;
    wchar_t                 GetForm() const;
    Color                   GetColor() const;
    Color                   GetBGColor() const;

    void                    SetShow(bool _isShow);
    void                    SetDepth(BYTE _depth);
    void                    SetCoord(const Coord& _coord);
    void                    SetCoord(short _x, short _y);
    void                    SetShape(const Shape& _shape);
    void                    SetShape(wchar_t _form);
    void                    SetColor(Color _color);
    void                    SetBGColor(Color _bgColor);
};

SCE_END
