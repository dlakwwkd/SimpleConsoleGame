#pragma once
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
class IGame
{
public:
    virtual ~IGame()                = default;
    virtual void Init()             = 0;
    virtual void Release()          = 0;
    virtual void Update(float _dt)  = 0;
    virtual void Render()           = 0;
};

SCE_END
