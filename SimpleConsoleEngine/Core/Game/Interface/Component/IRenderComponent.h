#pragma once
#include "../IComponent.h"
SCE_START


class IRenderComponent : public IComponentCRTP<IRenderComponent>
{
public:
    virtual void Render() = 0;
};

SCE_END
