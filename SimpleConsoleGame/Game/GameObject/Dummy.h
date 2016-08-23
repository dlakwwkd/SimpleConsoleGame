#pragma once
#include "SimpleConsoleEngine/Core/Game/GameObject.h"


class Dummy : public SCE::GameObject
{
    SPECIALFUNC_SET(Dummy, default)
public:
    Dummy() noexcept;
    virtual ~Dummy() override;

    virtual void Init()             override;
    virtual void Release()          override;
    virtual void Update(float dt)   override;
    virtual void Render()           override;
};
