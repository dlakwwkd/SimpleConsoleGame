#pragma once
#include "SimpleConsoleEngine/Core/Game/GameObject.h"


class Dummy : public SCE::GameObject
{
    SPECIALFUNC_SET(Dummy, default)
public:
    Dummy() noexcept = default;
    ~Dummy() override = default;

    void Init()             override;
    void Release()          override;
    void Update(float dt)   override;
    void Render()           override;
};
