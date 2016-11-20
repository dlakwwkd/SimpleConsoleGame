#pragma once
#include "../../Composite/GameObject.h"
SCE_START


class Effect : public GameObject
{
    SPECIALFUNC_SET(Effect, default)
public:
    Effect() noexcept;
    virtual ~Effect() override;

    virtual void Init()             override;
    virtual void Release()          override;
    virtual void Update(float dt)   override;
    virtual void Render()           override;
};

SCE_END
