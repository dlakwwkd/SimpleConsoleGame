﻿#pragma once
#include "../../Interface/Component/IRenderComponent.h"
SCE_START
enum Color : unsigned short;
struct Coord;
struct Shape;

/////////////////////////////////////////////////////////////////////////////////////////
class WinRenderComponent : public IRenderComponent
{
    DECLARE_PIMPL
    SPECIALFUNC_MOVE_SET(WinRenderComponent, default)
public:
    WinRenderComponent(const CompositeRef& _owner) noexcept;
    virtual ~WinRenderComponent() override;

    virtual std::string     GetComponentName() const override;
    virtual CompositePtr    GetOwner() const override;
    virtual RenderType      GetRenderType() const override;
    virtual void            Render() override;

    bool                    IsShow() const noexcept;
    BYTE                    GetDepth() const noexcept;
    const Coord&            GetCoord() const noexcept;
    const Shape&            GetShape() const noexcept;
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