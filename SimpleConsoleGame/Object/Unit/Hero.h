#pragma once
#include "Unit.h"


class Hero : public Unit
{
    SPECIALFUNC_SET(Hero, default)
public:
    Hero();
    ~Hero() override;

    void Init()             override;
    void Release()          override;
    void Update(float dt)   override;
    void Render()           override;
};
