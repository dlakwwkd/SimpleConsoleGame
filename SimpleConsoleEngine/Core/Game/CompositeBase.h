#pragma once
SCE_START
class IComponent;


class CompositeBase
{
    SPECIALFUNC_DECLARE_NOEXCEPT(CompositeBase)
    using ComponentPtr = std::shared_ptr<IComponent>;
    using ComponentMap = std::map<size_t, ComponentPtr>;
public:
    CompositeBase()             = default;
    virtual ~CompositeBase()    = default;

    template<IS_BASE_OF(T, IComponent)>
    bool                AddComponent();
    template<IS_BASE_OF(T, IComponent)>
    std::shared_ptr<T>  GetComponent();

    void ComponentMapClear();
    void ComponentMapDeepCopy(const ComponentMap& source);

private:
    ComponentMap m_ComponentMap;
};

SCE_END
#include "CompositeBase.inl"
