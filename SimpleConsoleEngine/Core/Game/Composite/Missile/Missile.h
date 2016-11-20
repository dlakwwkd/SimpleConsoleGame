#pragma once
#include "../Unit/Unit.h"
SCE_START
class Timer;
class Dummy;


class Missile : public Unit
{
    SPECIALFUNC_SET(Missile, default)
public:
    Missile() noexcept;
    virtual ~Missile() override;

    virtual void Init()             override;
    virtual void Release()          override;
    virtual void Update(float dt)   override;
    virtual void Render()           override;
    virtual void Death()            override;

    void SetAIRatio(float ratio);
    void AI(float dt);

private:
    std::shared_ptr<Timer> m_AITimer;
};

SCE_END
