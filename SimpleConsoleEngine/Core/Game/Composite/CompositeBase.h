#pragma once
#include "../../ObjectPool/ObjectPool.h"
SCE_START
class IComponent;

/////////////////////////////////////////////////////////////////////////////////////////
class CompositeBase : public std::enable_shared_from_this<CompositeBase>
{
    SPECIALFUNC_MOVE_SET(CompositeBase, default)
public:
    CompositeBase() noexcept;
    virtual ~CompositeBase() {}

    IS_BASE_OF(T, IComponent) std::shared_ptr<T>    GetComponent() noexcept;
    IS_BASE_OF(T, IComponent) std::shared_ptr<T>    AddComponent() noexcept;
    IS_BASE_OF(T, IComponent) void                  RemoveComponent() noexcept;

private:
    std::map<size_t, std::shared_ptr<IComponent>>   componentMap;
};

SCE_END
#include "CompositeBase.inl"
