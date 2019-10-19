#pragma once
#include "../../ObjectPool/ObjectPool.h"
SCE_START
class IComponent;

template<typename T>
concept Compnent = std::derived_from<T, IComponent>;

/////////////////////////////////////////////////////////////////////////////////////////
class CompositeBase : public std::enable_shared_from_this<CompositeBase>
{
    SPECIALFUNC_MOVE_SET(CompositeBase, default)
    using ComponentMap = std::map<size_t, std::shared_ptr<IComponent>>;
public:
    CompositeBase() noexcept;
    virtual ~CompositeBase() = default;

    template<Compnent T> std::shared_ptr<T> GetComponent() noexcept;
    template<Compnent T> std::shared_ptr<T> AddComponent() noexcept;
    template<Compnent T> void               RemoveComponent() noexcept;

private:
    ComponentMap                            componentMap;
};

SCE_END
#include "CompositeBase.inl"
