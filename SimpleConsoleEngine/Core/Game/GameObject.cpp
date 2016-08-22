#include "stdafx.h"
#include "GameObject.h"
#include "Component/IRenderComponent.h"
SCE_START


GameObject::GameObject() noexcept
:   m_ComponentMap(nullptr)
{
    m_ComponentMap = Safe::New<ComponentMap>();
}

GameObject::~GameObject()
{
    Release();
    Safe::Delete(m_ComponentMap);
}



GameObject::GameObject(const GameObject& source) noexcept
:   m_ComponentMap(nullptr)
{
    m_ComponentMap = Safe::New<ComponentMap>();
    ComponentMapDeepCopy(source.m_ComponentMap);
}

GameObject::GameObject(GameObject&& source) noexcept
:   m_ComponentMap(std::move(source.m_ComponentMap))
{
}

GameObject& GameObject::operator=(const GameObject& source) noexcept
{
    Release();
    ComponentMapDeepCopy(source.m_ComponentMap);
    return *this;
}

GameObject& GameObject::operator=(GameObject&& source) noexcept
{
    Release();
    Safe::Delete(m_ComponentMap);
    m_ComponentMap = std::move(source.m_ComponentMap);
    return *this;
}



void GameObject::Init()
{
}

void GameObject::Release()
{
    ComponentMapClear();
}

void GameObject::Update(float dt)
{
}

void GameObject::Render()
{
    auto render = GetComponent<IRenderComponent>();
    if (render != nullptr)
    {
        render->Render();
    }
}



void GameObject::ComponentMapClear()
{
    for (auto& iter : *m_ComponentMap)
    {
        auto component = iter.second;
        if (component == nullptr)
            continue;

        component->Release();
        Safe::Delete(component);
    }
    m_ComponentMap->clear();
}

bool GameObject::ComponentMapDeepCopy(const ComponentMap* source)
{
    if (source == nullptr)
        return false;

    ComponentMapClear();
    for (auto& iter : *source)
    {
        auto component = iter.second;
        if (component == nullptr)
            continue;

        m_ComponentMap->insert(std::make_pair(iter.first, component->CopyCreate()));
    }
    return true;
}

SCE_END
