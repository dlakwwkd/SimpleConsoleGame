#pragma once
#include "Core/Game/Composite/GameObject.h"


class Effect : public SCE::GameObject
{
    SPECIALFUNC_SET(Effect, default)
public:
    Effect();
    virtual ~Effect() override;

    virtual void Init()             override;
    virtual void Release()          override;
    virtual void Update(float dt)   override;
    virtual void Render()           override;
};
