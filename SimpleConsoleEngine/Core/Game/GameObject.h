#pragma once
#include "IComponent.h"
SCE_START


class GameObject
{
    using ComponentMap = std::map<size_t, IComponent*>;
public:
    GameObject() noexcept;
    virtual ~GameObject();

    GameObject(const GameObject& source) noexcept;
    GameObject(GameObject&& source) noexcept;
    GameObject& operator=(const GameObject& source) noexcept;
    GameObject& operator=(GameObject&& source) noexcept;

    virtual void Init();
    virtual void Release();
    virtual void Update(float dt);
    virtual void Render();

    template<IS_BASE_OF(T, IComponent)>
    bool    InsertComponent(IComponent* component)
    {
        if (component == nullptr)
            return false;

        size_t componentId = T::GetComponentId();
        auto iter = m_ComponentMap->find(componentId);
        if (iter != m_ComponentMap->end())
            return false;

        m_ComponentMap->insert(std::make_pair(componentId, component));
        return true;
    }

    template<IS_BASE_OF(T, IComponent)>
    T*      GetComponent()
    {
        size_t componentId = T::GetComponentId();
        auto iter = m_ComponentMap->find(componentId);
        if (iter == m_ComponentMap->end())
            return nullptr;

        return dynamic_cast<T*>(iter->second);
    }

private:
    void    ComponentMapClear();
    bool    ComponentMapDeepCopy(const ComponentMap* source);

private:
    ComponentMap*   m_ComponentMap;
};

SCE_END
