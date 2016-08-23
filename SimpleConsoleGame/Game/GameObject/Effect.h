#pragma once
#include "SimpleConsoleEngine/Core/Game/GameObject.h"


class Effect : public SCE::GameObject
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
