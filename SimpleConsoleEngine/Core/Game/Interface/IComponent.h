#pragma once
SCE_START
struct _identifier {};


class IComponent
{
protected:
    using IComponentPtr = std::shared_ptr<IComponent>;
public:
    IComponent()            = default;
    virtual ~IComponent()   = default;

    virtual std::string     GetComponentName() const    = 0;
    virtual IComponentPtr   Copy() const                = 0;
    virtual void            Init()                      = 0;
    virtual void            Release()                   = 0;
};


template<typename Derived>
class IComponentCRTP : public IComponent
{
    static _identifier      s_Identifier;
public:
    static size_t           GetComponentId()
    {
        return reinterpret_cast<size_t>(&s_Identifier);
    }
public:
    IComponentCRTP()                    = default;
    virtual ~IComponentCRTP() override  = default;

    virtual std::string     GetComponentName() const    = 0;
    virtual IComponentPtr   Copy() const                = 0;
    virtual void            Init()                      = 0;
    virtual void            Release()                   = 0;
};

SCE_END
