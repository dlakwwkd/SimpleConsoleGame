#pragma once
#include "IGameObject.h"
SCE_START
class ICollisionComponent;
enum class EffectType;

/////////////////////////////////////////////////////////////////////////////////////////
class ICollisionObject : public IGameObject
{
public:
    virtual bool Hitted(int _damage)                = 0;
    virtual void Death()                            = 0;
    virtual void SetDeathEffect(EffectType _type)   = 0;
};

SCE_END
