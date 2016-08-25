#pragma once
SCE_START


class IGameBase
{
public:
    IGameBase()             = default;
    virtual ~IGameBase()    = default;

    virtual void Init()             = 0;
    virtual void Release()          = 0;
    virtual void Update(float dt)   = 0;
    virtual void Render()           = 0;
};

SCE_END
