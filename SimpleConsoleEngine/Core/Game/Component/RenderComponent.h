#pragma once
#include "../IComponent.h"
SCE_START


class SCE_API RenderComponent : public ComponentBase<RenderComponent>
{
public:
    virtual std::string GetComponentName() const = 0;
    virtual IComponent* CopyCreate() const = 0;

    virtual void        Init() = 0;
    virtual void        Release() = 0;
    virtual void        Render() = 0;
};


SCE_END
