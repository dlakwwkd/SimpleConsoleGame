﻿#pragma once
#include "Unit.h"
class Dummy;


class Mob : public Unit
{
    SPECIALFUNC_SET(Mob, default)
public:
    Mob();
    ~Mob() override;

    void Init()             override;
    void Release()          override;
    void Update(float dt)   override;
    void Render()           override;

    void AI(float dt);

private:
    SCE::Vec2               m_ToPos;
    std::unique_ptr<Dummy>  m_ToPosShow;
};
