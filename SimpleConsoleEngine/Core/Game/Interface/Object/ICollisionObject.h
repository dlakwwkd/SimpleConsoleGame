#pragma once
#include "IGameObject.h"
SCE_START
class ICollisionComponent;


class ICollisionObject : public IGameObject
{
protected:
    using CollisionPtr = std::shared_ptr<ICollisionComponent>;
    using CollisionRef = std::weak_ptr<ICollisionComponent>;
public:
    virtual CollisionPtr    GetCollision()      = 0;
    virtual bool            Hitted(int _damage) = 0;
    virtual void            Death()             = 0;

    IS_BASE_OF(T, ICollisionComponent)
    std::shared_ptr<T>      Get() noexcept
    {
        return std::static_pointer_cast<T>(GetCollision());
    }
};

SCE_END
