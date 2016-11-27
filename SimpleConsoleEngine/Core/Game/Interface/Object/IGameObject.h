#pragma once
#include "../IObject.h"
SCE_START


__interface IGameObject : public IObject
{
    void Update(float _dt);
};

SCE_END
