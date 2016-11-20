#pragma once
#include "IComponent.h"
#include "ICollision.h"
SCE_START


class ICollisionComponent
    : public IComponentCRTP<ICollisionComponent>
    , public ICollision
{
};

SCE_END
