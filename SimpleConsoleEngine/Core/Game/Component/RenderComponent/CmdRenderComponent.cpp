#include "stdafx.h"
#include "CmdRenderComponent.h"
#include "../../Composite/CompositeBase.h"
#include "../../../ObjectPool/ObjectPool.h"
SCE_START


CmdRenderComponent::CmdRenderComponent(const CompositeRef& owner) noexcept
    : m_Owner(owner)
    , m_IsShow(true)
    , m_Depth(0)
    , m_Coord{ 0,0 }
{
}

CmdRenderComponent::~CmdRenderComponent()
{
}


void CmdRenderComponent::Init()
{
}

void CmdRenderComponent::Release()
{
}

void CmdRenderComponent::Update(float dt)
{
}


std::string CmdRenderComponent::GetComponentName() const
{
    return CONVERT_STRING(CmdRenderComponent);
}

IComponent::CompositePtr CmdRenderComponent::GetOwner() const
{
    return m_Owner.lock();
}

IComponent::IComponentPtr CmdRenderComponent::Copy() const
{
    return ObjectPool<CmdRenderComponent>::Get(*this);
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

void CmdRenderComponent::SetCoord(const Coord& coord)
{
    m_Coord = coord;
}

void CmdRenderComponent::SetCoord(short x, short y)
{
    m_Coord.m_X = x;
    m_Coord.m_Y = y;
}

void CmdRenderComponent::SetShape(const Shape& shape)
{
    m_Shape = shape;
}

void CmdRenderComponent::SetShape(wchar_t form, Color color, Color bgColor)
{
    m_Shape.SetForm(form);
    m_Shape.SetColor(color);
    m_Shape.SetBGColor(bgColor);
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
