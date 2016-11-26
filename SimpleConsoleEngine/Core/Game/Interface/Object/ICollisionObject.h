#pragma once
#include "IGameObject.h"
SCE_START
class ICollisionComponent;

using CollisionPtr = std::shared_ptr<ICollisionComponent>;
using CollisionRef = std::weak_ptr<ICollisionComponent>;


__interface ICollisionObject : public IGameObject
{
    CollisionPtr	GetCollision();
    bool			Hitted(int _damage);
    void			Death();
};

SCE_END
