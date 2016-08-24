#include "stdafx.h"
#include "CompositeBase.h"
#include "Interface/IComponent.h"
SCE_START


CompositeBase::CompositeBase(const CompositeBase& source) noexcept
{
    ComponentMapDeepCopy(source.m_ComponentMap);
}

CompositeBase::CompositeBase(CompositeBase&& source) noexcept
:   m_ComponentMap(std::move(source.m_ComponentMap))
{
}

CompositeBase& CompositeBase::operator=(const CompositeBase& source) noexcept
{
    ComponentMapDeepCopy(source.m_ComponentMap);
    return *this;
}

CompositeBase& CompositeBase::operator=(CompositeBase&& source) noexcept
{
    ComponentMapClear();
    m_ComponentMap = std::move(source.m_ComponentMap);
    return *this;
}



void CompositeBase::ComponentMapClear()
{
    for (auto& iter : m_ComponentMap)
    {
        auto& component = iter.second;
        if (component == nullptr)
            continue;

        component->Release();
    }
    m_ComponentMap.clear();
}

void CompositeBase::ComponentMapDeepCopy(const ComponentMap& source)
{
    ComponentMapClear();
    for (auto& iter : source)
    {
        auto& component = iter.second;
        if (component == nullptr)
            continue;

        m_ComponentMap.insert(std::make_pair(iter.first, component->Copy()));
    }
}

SCE_END
