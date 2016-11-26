#pragma once
#include "Core/Game/Composite/Unit/Unit.h"


class Hero : public SCE::Unit
{
    DECLARE_PIMPL
    SPECIALFUNC_MOVE_SET(Hero, default)
public:
    Hero() noexcept;
    virtual ~Hero() override;

    virtual void    Init()              override;
    virtual void    Release()           override;
    virtual void    Update(float _dt)   override;
    virtual void    Render()            override;

    void            SetDefaultAttack();
    void            ShootMissile();
    void            SwapMissile();
    void            SwapMissile(int _idx);
};
