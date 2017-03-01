#pragma once
#include "IGameObject.h"
SCE_START
class ICollisionComponent;
enum class EffectType;

/////////////////////////////////////////////////////////////////////////////////////////
class ICollisionObject : public IGameObject
{
protected:
    using CollisionPtr = std::shared_ptr<ICollisionComponent>;
    using CollisionRef = std::weak_ptr<ICollisionComponent>;
public:
    virtual CollisionPtr    GetCollision() const                = 0;
    virtual bool            Hitted(int _damage)                 = 0;
    virtual void            Death()                             = 0;
    virtual void            SetDeathEffect(EffectType _type)    = 0;

    /////////////////////////////////////////////////////////////////////////////////////
    IS_BASE_OF(T, ICollisionComponent)
    std::shared_ptr<T>      Get() const noexcept
    {
        return std::static_pointer_cast<T>(GetCollision());
    }
};

SCE_END
