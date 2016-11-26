#pragma once
#include "Core/Game/Composite/Unit/Unit.h"


class Mob : public SCE::Unit
{
    DECLARE_PIMPL
    SPECIALFUNC_MOVE_SET(Mob, default)
public:
    Mob() noexcept;
    virtual ~Mob() override;

    virtual void    Init()              override;
    virtual void    Release()           override;
    virtual void    Update(float _dt)   override;
    virtual void    Render()            override;

    void            SetToPosChangeProbability(float _prob);
    void            SetAIRatio(float _ratio);
    void            AI(float _dt);
};
