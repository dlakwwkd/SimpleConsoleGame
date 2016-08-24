#include "stdafx.h"
#include "CmdRenderComponent.h"
SCE_START


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

SCE_END
