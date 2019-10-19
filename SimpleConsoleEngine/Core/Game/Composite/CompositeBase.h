#pragma once
#include "../../ObjectPool/ObjectPool.h"
SCE_START
class IComponent;

/////////////////////////////////////////////////////////////////////////////////////////
class CompositeBase : public std::enable_shared_from_this<CompositeBase>
{
    SPECIALFUNC_MOVE_SET(CompositeBase, default)
    using ComponentMap = std::map<size_t, std::shared_ptr<IComponent>>;
public:
    CompositeBase() noexcept;
    virtual ~CompositeBase() = default;

    template<typename T>
    std::shared_ptr<T>      GetComponent() noexcept requires std::derived_from<T, IComponent>;

    template<typename T>
    std::shared_ptr<T>      AddComponent() noexcept requires std::derived_from<T, IComponent>;

    template<typename T>
    void                    RemoveComponent() noexcept requires std::derived_from<T, IComponent>;

private:
    ComponentMap            componentMap;
};

SCE_END
#include "CompositeBase.inl"
