#pragma once
SCE_START
class IComponent;


class GameObject
{
    using IComponentPtr = std::shared_ptr<IComponent>;
    using ComponentMap = std::map<size_t, IComponentPtr>;
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
    bool                InsertComponent()
    {
        size_t componentId = T::GetComponentId();
        auto iter = m_ComponentMap.find(componentId);
        if (iter != m_ComponentMap.end())
            return false;

        m_ComponentMap.insert(std::make_pair(componentId, std::make_shared<T>()));
        return true;
    }

    template<IS_BASE_OF(T, IComponent)>
    std::shared_ptr<T>  GetComponent()
    {
        size_t componentId = T::GetComponentId();
        auto iter = m_ComponentMap.find(componentId);
        if (iter == m_ComponentMap.end())
            return nullptr;

        return std::dynamic_pointer_cast<T>(iter->second);
    }

private:
    void ComponentMapClear();
    bool ComponentMapDeepCopy(const ComponentMap& source);

private:
    ComponentMap m_ComponentMap;
};

SCE_END
