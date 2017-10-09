#pragma once
#include "../IComponent.h"
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
class IRenderComponent : public IComponentCRTP<IRenderComponent>
{
public:
    enum class RenderType
    {
        CmdConsole,
        Window,
    };
    virtual RenderType  GetRenderType() const   = 0;
    virtual void        Render()                = 0;
};

SCE_END
