#pragma once
#include "../Interface/IComponent.h"
SCE_START


class IRenderComponent : public IComponentCRTP<IRenderComponent>
{
public:
    IRenderComponent() {}
    virtual ~IRenderComponent() override {}

    virtual std::string     GetComponentName() const override   = 0;
    virtual IComponentPtr   Copy() const override               = 0;
    virtual void            Init() override                     = 0;
    virtual void            Release() override                  = 0;

    virtual void            Render()                            = 0;
};

SCE_END
