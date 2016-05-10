#pragma once
#include "../../Util/Macros.h"
SCE_START


class SCE_API IGame
{
public:
    virtual ~IGame()                = default;
    virtual void Init()             = 0;
    virtual void Release()          = 0;
    virtual void Update(float dt)   = 0;
    virtual void Render()           = 0;
};

SCE_END


