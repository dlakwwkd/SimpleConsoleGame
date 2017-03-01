#pragma once
#include "IGameObject.h"
SCE_START
class IRenderComponent;

/////////////////////////////////////////////////////////////////////////////////////////
class IRenderObject : public IGameObject
{
protected:
    using RenderPtr = std::shared_ptr<IRenderComponent>;
    using RenderRef = std::weak_ptr<IRenderComponent>;
public:
    virtual RenderPtr   GetRender() const   = 0;
    virtual void        Render()            = 0;

    /////////////////////////////////////////////////////////////////////////////////////
    IS_BASE_OF(T, IRenderComponent)
    std::shared_ptr<T>  Get() const noexcept
    {
        return std::static_pointer_cast<T>(GetRender());
    }
};

SCE_END
