#pragma once
#include "../GameObject.h"
#include "../../Interface/Object/IRenderObject.h"
SCE_START


class Dummy
    : public IRenderObject
    , public GameObject
{
    DECLARE_PIMPL
    SPECIALFUNC_MOVE_SET(Dummy, default)
public:
    Dummy() noexcept;
    virtual ~Dummy() override;

    virtual void        Init() override;
    virtual void        Release() override;
    virtual void        Update(float _dt) override;

    virtual RenderPtr   GetRender() override;
    virtual void        Render() override;
};

SCE_END
