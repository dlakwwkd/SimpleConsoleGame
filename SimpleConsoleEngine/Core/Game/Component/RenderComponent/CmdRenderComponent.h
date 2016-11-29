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

    virtual void            Render() override;

    bool                    IsShow() const noexcept;
    BYTE                    GetDepth() const noexcept;
    Coord                   GetCoord() const noexcept;
    Shape                   GetShape() const noexcept;
    wchar_t                 GetForm() const noexcept;
    Color                   GetColor() const noexcept;
    Color                   GetBGColor() const noexcept;

    void                    SetShow(bool _isShow) noexcept;
    void                    SetDepth(BYTE _depth) noexcept;
    void                    SetCoord(const Coord& _coord) noexcept;
    void                    SetCoord(short _x, short _y) noexcept;
    void                    SetShape(const Shape& _shape) noexcept;
    void                    SetShape(wchar_t _form) noexcept;
    void                    SetColor(Color _color) noexcept;
    void                    SetBGColor(Color _bgColor) noexcept;
};

SCE_END
