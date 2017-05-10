#pragma once
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
class IObject
{
public:
    virtual ~IObject()      = default;
    virtual void Init()     = 0;
    virtual void Release()  = 0;
};

SCE_END
