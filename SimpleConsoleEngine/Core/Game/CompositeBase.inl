SCE_START


CHECKED_T(T)
std::shared_ptr<T> CompositeBase::GetComponent()
{
    static size_t componentId = T::GetComponentId();
    auto iter = m_ComponentMap.find(componentId);
    if (iter == m_ComponentMap.end())
        return nullptr;

    return std::dynamic_pointer_cast<T>(iter->second);
}

CHECKED_T(T)
bool CompositeBase::AddComponent()
{
    static size_t componentId = T::GetComponentId();
    auto iter = m_ComponentMap.find(componentId);
    if (iter != m_ComponentMap.end())
        return false;

    m_ComponentMap.insert(std::make_pair(componentId, std::make_shared<T>()));
    return true;
}

CHECKED_T(T)
void CompositeBase::RemoveComponent()
{
    static size_t componentId = T::GetComponentId();
    auto iter = m_ComponentMap.find(componentId);
    if (iter != m_ComponentMap.end())
    {
        m_ComponentMap.erase(iter);
    }
}

SCE_END
