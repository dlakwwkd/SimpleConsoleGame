SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
std::shared_ptr<T> CompositeBase::GetComponent() noexcept requires std::derived_from<T, IComponent>
{
    static auto componentId = T::GetComponentId();
    auto iter = componentMap.find(componentId);
    if (iter == componentMap.end())
        return nullptr;

    return std::dynamic_pointer_cast<T>(iter->second);
}

/////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
std::shared_ptr<T> CompositeBase::AddComponent() noexcept requires std::derived_from<T, IComponent>
{
    RemoveComponent<T>();
    auto component = ObjectPool<T>::Get(shared_from_this());
    if (component == nullptr)
        return nullptr;

    static auto componentId = T::GetComponentId();
    componentMap.insert(std::make_pair(componentId, component));
    return component;
}

/////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
void CompositeBase::RemoveComponent() noexcept requires std::derived_from<T, IComponent>
{
    static auto componentId = T::GetComponentId();
    auto iter = componentMap.find(componentId);
    if (iter != componentMap.end())
    {
        componentMap.erase(iter);
    }
}

SCE_END
