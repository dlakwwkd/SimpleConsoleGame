SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
CHECKED_T(T) std::shared_ptr<T> CompositeBase::GetComponent() noexcept
{
    static auto componentId = T::GetComponentId();
    auto iter = componentMap.find(componentId);
    if (iter == componentMap.end())
        return nullptr;

    return std::dynamic_pointer_cast<T>(iter->second);
}

/////////////////////////////////////////////////////////////////////////////////////////
CHECKED_T(T) bool CompositeBase::AddComponent() noexcept
{
    static auto componentId = T::GetComponentId();
    auto iter = componentMap.find(componentId);
    if (iter != componentMap.end())
        return false;

    componentMap.insert(std::make_pair(componentId, ObjectPool<T>::Get(shared_from_this())));
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
CHECKED_T(T) void CompositeBase::RemoveComponent() noexcept
{
    static auto componentId = T::GetComponentId();
    auto iter = componentMap.find(componentId);
    if (iter != componentMap.end())
    {
        componentMap.erase(iter);
    }
}

SCE_END
