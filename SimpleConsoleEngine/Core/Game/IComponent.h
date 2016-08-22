#pragma once
SCE_START
struct _component_identifier {};


class IComponent
{
public:
    template<IS_BASE_OF(T, IComponent)>
    static IComponent*  Create()
    {
        return Safe::New<T>();
    }
    template<IS_BASE_OF(T, IComponent)>
    static IComponent*  Create(const T& source)
    {
        return Safe::New<T>(source);
    }
public:
    virtual std::string GetComponentName() const = 0;
    virtual IComponent* CopyCreate() const = 0;

    virtual void        Init() = 0;
    virtual void        Release() = 0;
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
    virtual std::string GetComponentName() const = 0;
    virtual IComponent* CopyCreate() const = 0;

    virtual void        Init() = 0;
    virtual void        Release() = 0;
};

SCE_END
