#include "../../ObjectPool/ObjectPool.h"
SCE_START


CHECKED_T(T)
std::shared_ptr<T> CompositeBase::GetComponent() noexcept
{
    static size_t componentId = T::GetComponentId();
    auto iter = m_ComponentMap.find(componentId);
    if (iter == m_ComponentMap.end())
        return nullptr;

    return std::dynamic_pointer_cast<T>(iter->second);
}

CHECKED_T(T)
bool CompositeBase::AddComponent() noexcept
{
    static size_t componentId = T::GetComponentId();
    auto iter = m_ComponentMap.find(componentId);
    if (iter != m_ComponentMap.end())
        return false;

    m_ComponentMap.insert(std::make_pair(componentId,
        ObjectPool<T>::Get(shared_from_this())));
    return true;
}

CHECKED_T(T)
void CompositeBase::RemoveComponent() noexcept
{
    static size_t componentId = T::GetComponentId();
    auto iter = m_ComponentMap.find(componentId);
    if (iter != m_ComponentMap.end())
    {
        m_ComponentMap.erase(iter);
    }
}

SCE_END
