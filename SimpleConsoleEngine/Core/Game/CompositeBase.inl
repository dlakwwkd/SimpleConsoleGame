SCE_START


template<CHECKED_T(T)>
bool CompositeBase::AddComponent()
{
    size_t componentId = T::GetComponentId();
    auto iter = m_ComponentMap.find(componentId);
    if (iter != m_ComponentMap.end())
        return false;

    m_ComponentMap.insert(std::make_pair(componentId, std::make_shared<T>()));
    return true;
}

template<CHECKED_T(T)>
std::shared_ptr<T> CompositeBase::GetComponent()
{
    size_t componentId = T::GetComponentId();
    auto iter = m_ComponentMap.find(componentId);
    if (iter == m_ComponentMap.end())
        return nullptr;

    return std::dynamic_pointer_cast<T>(iter->second);
}

SCE_END
