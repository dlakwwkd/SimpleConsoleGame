#include "stdafx.h"
#include "CmdRenderComponent.h"
SCE_START


CmdRenderComponent::CmdRenderComponent()
:   m_IsShow(true),
    m_Depth(0),
    m_Coord{ 0,0 }
{
}


CmdRenderComponent::~CmdRenderComponent()
{
}


std::string CmdRenderComponent::GetComponentName() const
{
    return CONVERT_STRING(CmdRenderComponent);
}

IComponent::IComponentPtr CmdRenderComponent::Copy() const
{
    return std::make_shared<CmdRenderComponent>(*this);
}

void CmdRenderComponent::Init()
{
}

void CmdRenderComponent::Release()
{
}

void CmdRenderComponent::Render()
{
    if (m_IsShow)
    {
        m_Shape.Render(m_Coord, m_Depth);
    }
}



bool CmdRenderComponent::IsShow() const
{
    return m_IsShow;
}

BYTE CmdRenderComponent::GetDepth() const
{
    return m_Depth;
}

Coord CmdRenderComponent::GetCoord() const
{
    return m_Coord;
}

Shape CmdRenderComponent::GetShape() const
{
    return m_Shape;
}

wchar_t CmdRenderComponent::GetForm() const
{
    return m_Shape.GetForm();
}

Color CmdRenderComponent::GetColor() const
{
    return m_Shape.GetColor();
}

Color CmdRenderComponent::GetBGColor() const
{
    return m_Shape.GetBGColor();
}


void CmdRenderComponent::SetShow(bool isShow)
{
    m_IsShow = isShow;
}

void CmdRenderComponent::SetDepth(BYTE depth)
{
    m_Depth = depth;
}

void CmdRenderComponent::SetCoord(short x, short y)
{
    m_Coord.m_X = x;
    m_Coord.m_Y = y;
}

void CmdRenderComponent::SetForm(wchar_t form)
{
    m_Shape.SetForm(form);
}

void CmdRenderComponent::SetColor(Color color)
{
    m_Shape.SetColor(color);
}

void CmdRenderComponent::SetBGColor(Color bgColor)
{
    m_Shape.SetBGColor(bgColor);
}

SCE_END
