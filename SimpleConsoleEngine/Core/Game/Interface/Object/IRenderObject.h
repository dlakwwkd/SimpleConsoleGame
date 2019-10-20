#pragma once
#include "IGameObject.h"
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
class IRenderObject : public IGameObject
{
public:
    virtual void Render() = 0;
};

SCE_END
