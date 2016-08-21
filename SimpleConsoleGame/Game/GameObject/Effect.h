﻿#pragma once
#include "SimpleConsoleEngine/Core/Game/GameObject.h"


class Effect : public SCE::GameObject
{
    SPECIALFUNC_SET(Effect, default)
public:
    Effect() noexcept = default;
    ~Effect() override = default;

    void Init()             override;
    void Release()          override;
    void Update(float dt)   override;
    void Render()           override;
};
