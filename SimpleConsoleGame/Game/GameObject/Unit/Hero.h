#pragma once
#include "../Unit.h"


class Hero : public Unit
{
    SPECIALFUNC_SET(Hero, default)
public:
    Hero();
    virtual ~Hero() override;

    virtual void Init()             override;
    virtual void Release()          override;
    virtual void Update(float dt)   override;
    virtual void Render()           override;
};
