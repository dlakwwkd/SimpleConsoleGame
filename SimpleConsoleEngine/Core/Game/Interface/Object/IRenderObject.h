#pragma once
#include "IGameObject.h"
SCE_START
class IRenderComponent;

/////////////////////////////////////////////////////////////////////////////////////////
class IRenderObject : public IGameObject
{
public:
    virtual void Render() = 0;
};

SCE_END
