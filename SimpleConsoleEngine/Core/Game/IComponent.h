#pragma once
SCE_START
struct _component_identifier {};


class IComponent
{
protected:
    using IComponentPtr = std::shared_ptr<IComponent>;
public:
    virtual std::string     GetComponentName() const = 0;
    virtual IComponentPtr   Copy() const = 0;

    virtual void            Init() = 0;
    virtual void            Release() = 0;
};


template<typename Derived>
class IComponentCRTP : public IComponent
{
    static _component_identifier s_ComponentIdentifier;
public:
    static size_t       GetComponentId()
    {
        return reinterpret_cast<size_t>(&s_ComponentIdentifier);
    }
public:
    virtual std::string     GetComponentName() const = 0;
    virtual IComponentPtr   Copy() const = 0;

    virtual void            Init() = 0;
    virtual void            Release() = 0;
};

SCE_END
