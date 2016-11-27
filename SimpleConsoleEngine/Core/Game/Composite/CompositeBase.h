#pragma once
#include "../../ObjectPool/ObjectPool.h"
SCE_START
class IComponent;


class CompositeBase : public std::enable_shared_from_this<CompositeBase>
{
    SPECIALFUNC_MOVE_SET(CompositeBase, default)
public:
    CompositeBase() noexcept;
    virtual ~CompositeBase() {}

    IS_BASE_OF(T, IComponent) std::shared_ptr<T>    GetComponent() noexcept;
    IS_BASE_OF(T, IComponent) bool                  AddComponent() noexcept;
    IS_BASE_OF(T, IComponent) void                  RemoveComponent() noexcept;

private:
    std::map<size_t, std::shared_ptr<IComponent>>   componentMap;
};


CHECKED_T(T)
std::shared_ptr<T> CompositeBase::GetComponent() noexcept
{
    static auto componentId = T::GetComponentId();
    auto iter = componentMap.find(componentId);
    if (iter == componentMap.end())
        return nullptr;

    return std::dynamic_pointer_cast<T>(iter->second);
}

CHECKED_T(T)
bool CompositeBase::AddComponent() noexcept
{
    static auto componentId = T::GetComponentId();
    auto iter = componentMap.find(componentId);
    if (iter != componentMap.end())
        return false;

    componentMap.insert(std::make_pair(componentId, ObjectPool<T>::Get(shared_from_this())));
    return true;
}

CHECKED_T(T)
void CompositeBase::RemoveComponent() noexcept
{
    static auto componentId = T::GetComponentId();
    auto iter = componentMap.find(componentId);
    if (iter != componentMap.end())
    {
        componentMap.erase(iter);
    }
}

SCE_END
