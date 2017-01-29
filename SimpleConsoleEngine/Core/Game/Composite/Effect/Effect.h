#pragma once
#include "../GameObject.h"
#include "../../Interface/Object/IRenderObject.h"
SCE_START


class Effect
    : public IRenderObject
    , public GameObject
{
    DECLARE_PIMPL
    SPECIALFUNC_MOVE_SET(Effect, default)
public:
    Effect() noexcept;
    virtual ~Effect() override;

    virtual void        Init() override;
    virtual void        Release() override;
    virtual void        Update(float _dt) override;

    virtual RenderPtr   GetRender() const override;
    virtual void        Render() override;
};

SCE_END
