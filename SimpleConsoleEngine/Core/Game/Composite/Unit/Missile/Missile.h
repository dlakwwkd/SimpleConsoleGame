#pragma once
#include "../Unit.h"
SCE_START
enum class EffectType;


class Missile : public Unit
{
    DECLARE_PIMPL
    SPECIALFUNC_MOVE_SET(Missile, default)
public:
    Missile() noexcept;
    virtual ~Missile() override;

    virtual void    Init()             override;
    virtual void    Release()          override;
    virtual void    Update(float _dt)  override;
    virtual void    Death()            override;

    void            SetExplosionEffect(EffectType _type) noexcept;
    void            SetAIRatio(float _ratio);
    void            AI(float _dt);
};

SCE_END
