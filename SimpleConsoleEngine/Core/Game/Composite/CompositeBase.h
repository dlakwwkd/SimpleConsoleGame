#pragma once
SCE_START
class IComponent;


class CompositeBase : public std::enable_shared_from_this<CompositeBase>
{
    SPECIALFUNC_DECLARE_NOEXCEPT(CompositeBase)
    using ComponentPtr = std::shared_ptr<IComponent>;
    using ComponentMap = std::unordered_map<size_t, ComponentPtr>;
public:
    CompositeBase() noexcept {}
    virtual ~CompositeBase() {}

    IS_BASE_OF(T, IComponent) std::shared_ptr<T>    GetComponent() noexcept;
    IS_BASE_OF(T, IComponent) bool                  AddComponent() noexcept;
    IS_BASE_OF(T, IComponent) void                  RemoveComponent() noexcept;

    void            ComponentMapClear() noexcept;
    void            ComponentMapDeepCopy(const ComponentMap& source) noexcept;

private:
    ComponentMap    m_ComponentMap;
};

SCE_END
#include "CompositeBase.inl"
