#pragma once
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

    void SetAIRatio(float ratio) noexcept { m_AIRatio = ratio; }
    void SetToPosChangeProbability(float prob) noexcept { m_ToPosChangeProbability = prob; }

private:
    SCE::Vec2               m_ToPos;
    std::unique_ptr<Dummy>  m_ToPosShow;
    float                   m_AccumDt;
    float                   m_AIRatio;
    float                   m_ToPosChangeProbability;
};
