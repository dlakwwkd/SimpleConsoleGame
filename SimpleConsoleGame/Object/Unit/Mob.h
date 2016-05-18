#pragma once
#include "Unit.h"
SCE_START
class Timer;
SCE_END
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
    void SetAIRatio(float ratio);

    void SetToPosChangeProbability(float prob) noexcept { m_ToPosChangeProbability = prob; }

private:
    std::unique_ptr<SCE::Timer> m_AITimer;
    std::unique_ptr<Dummy>      m_ToPosShow;
    SCE::Vec2                   m_ToPos;
    float                       m_ToPosChangeProbability;
};
