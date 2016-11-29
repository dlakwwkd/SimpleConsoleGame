﻿#include "stdafx.h"
#include "CmdRenderComponent.h"
SCE_START


struct CmdRenderComponent::impl
{
    impl(const CompositeRef& _owner) noexcept
        : owner{ _owner }
        , isShow{ true }
        , depth{}
        , coord{}
        , shape{}
    {
    }

    CompositeRef    owner;
    bool            isShow;
    BYTE            depth;
    Coord           coord;
    Shape           shape;
};


CmdRenderComponent::CmdRenderComponent(const CompositeRef& _owner) noexcept
    : pimpl{ std::make_unique<impl>(_owner) }
{
}

CmdRenderComponent::~CmdRenderComponent()
{
}


std::string CmdRenderComponent::GetComponentName() const
{
    return CONVERT_STRING(CmdRenderComponent);
}

IComponent::CompositePtr CmdRenderComponent::GetOwner() const
{
    return pimpl->owner.lock();
}


void CmdRenderComponent::Render()
{
    if (pimpl->isShow)
    {
        pimpl->shape.Render(pimpl->coord, pimpl->depth);
    }
}


bool CmdRenderComponent::IsShow() const noexcept
{
    return pimpl->isShow;
}

BYTE CmdRenderComponent::GetDepth() const noexcept
{
    return pimpl->depth;
}

Coord CmdRenderComponent::GetCoord() const noexcept
{
    return pimpl->coord;
}

Shape CmdRenderComponent::GetShape() const noexcept
{
    return pimpl->shape;
}

wchar_t CmdRenderComponent::GetForm() const noexcept
{
    return pimpl->shape.form;
}

Color CmdRenderComponent::GetColor() const noexcept
{
    return pimpl->shape.color;
}

Color CmdRenderComponent::GetBGColor() const noexcept
{
    return pimpl->shape.bgColor;
}


void CmdRenderComponent::SetShow(bool _isShow) noexcept
{
    pimpl->isShow = _isShow;
}

void CmdRenderComponent::SetDepth(BYTE _depth) noexcept
{
    pimpl->depth = _depth;
}

void CmdRenderComponent::SetCoord(const Coord& _coord) noexcept
{
    pimpl->coord = _coord;
}

void CmdRenderComponent::SetCoord(short _x, short _y) noexcept
{
    pimpl->coord.x = _x;
    pimpl->coord.y = _y;
}

void CmdRenderComponent::SetShape(const Shape& _shape) noexcept
{
    pimpl->shape = _shape;
}

void CmdRenderComponent::SetShape(wchar_t _form) noexcept
{
    pimpl->shape.form = _form;
}

void CmdRenderComponent::SetColor(Color _color) noexcept
{
    pimpl->shape.color = _color;
}

void CmdRenderComponent::SetBGColor(Color _bgColor) noexcept
{
    pimpl->shape.bgColor = _bgColor;
}

SCE_END
