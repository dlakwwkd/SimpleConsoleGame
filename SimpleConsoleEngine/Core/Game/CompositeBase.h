#pragma once
SCE_START
class IComponent;


class CompositeBase : public std::enable_shared_from_this<CompositeBase>
{
    SPECIALFUNC_DECLARE(CompositeBase)
    using ComponentPtr = std::shared_ptr<IComponent>;
    using ComponentMap = std::unordered_map<size_t, ComponentPtr>;
public:
    CompositeBase()             = default;
    virtual ~CompositeBase()    = default;

    IS_BASE_OF(T, IComponent) std::shared_ptr<T>  GetComponent();
    IS_BASE_OF(T, IComponent) bool                AddComponent();
    IS_BASE_OF(T, IComponent) void                RemoveComponent();

    void ComponentMapClear();
    void ComponentMapDeepCopy(const ComponentMap& source);

private:
    ComponentMap m_ComponentMap;
};

SCE_END
#include "CompositeBase.inl"
