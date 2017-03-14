#pragma once
#include "../../Interface/Object/IRenderObject.h"
#include "../GameObject.h"
SCE_START
class CmdRenderComponent;

/////////////////////////////////////////////////////////////////////////////////////////
class Effect
    : public IRenderObject
    , public GameObject
{
    SPECIALFUNC_MOVE_SET(Effect, default)
    using RenderPtr = std::shared_ptr<CmdRenderComponent>;
public:
    Effect() noexcept;
    virtual ~Effect() override;

    virtual void        Init() override;
    virtual void        Release() override;
    virtual void        Update(float _dt) override;
    virtual void        Render() override;

public:
    const RenderPtr&    GetRender() const { return render; }

private:
    RenderPtr           render;
};

SCE_END
