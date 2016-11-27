#pragma once
#include "IObject.h"
SCE_START
struct _identifier {};
class CompositeBase;


class IComponent : public std::enable_shared_from_this<IComponent>
{
protected:
    using IComponentPtr = std::shared_ptr<IComponent>;
    using CompositePtr  = std::shared_ptr<CompositeBase>;
    using CompositeRef  = std::weak_ptr<CompositeBase>;
public:
    virtual std::string     GetComponentName() const    = 0;
    virtual CompositePtr    GetOwner() const            = 0;
};


template<typename Derived>
class IComponentCRTP : public IComponent
{
    static _identifier      s_Identifier;
public:
    static size_t           GetComponentId() noexcept
    {
        return reinterpret_cast<size_t>(&s_Identifier);
    }
};

SCE_END
