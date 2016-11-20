#pragma once
SCE_START


class IObject
{
    SPECIALFUNC_SET(IObject, default)
public:
    IObject() noexcept {}
    virtual ~IObject() {}

    virtual void Init()             = 0;
    virtual void Release()          = 0;
    virtual void Update(float dt)   = 0;
};

SCE_END
