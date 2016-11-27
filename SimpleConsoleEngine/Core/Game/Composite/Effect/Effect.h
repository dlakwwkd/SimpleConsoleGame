#pragma once
#include "../../Composite/GameObject.h"
SCE_START


class Effect : public GameObject
{
    SPECIALFUNC_MOVE_SET(Effect, default)
public:
    Effect() noexcept;
    virtual ~Effect() override;

    virtual void Init()             override;
    virtual void Release()          override;
    virtual void Update(float _dt)  override;
};

SCE_END
