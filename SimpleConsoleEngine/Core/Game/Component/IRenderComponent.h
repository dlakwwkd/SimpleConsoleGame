#pragma once
#include "../IComponent.h"
SCE_START


class IRenderComponent : public IComponentCRTP<IRenderComponent>
{
public:
    virtual std::string     GetComponentName() const = 0;
    virtual IComponentPtr   Copy() const = 0;

    virtual void            Init() = 0;
    virtual void            Release() = 0;
    virtual void            Render() = 0;
};


SCE_END
