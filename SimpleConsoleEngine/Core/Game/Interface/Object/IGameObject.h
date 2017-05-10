#pragma once
#include "../IObject.h"
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
class IGameObject : public IObject
{
public:
    virtual void Update(float _dt) = 0;
};

SCE_END
