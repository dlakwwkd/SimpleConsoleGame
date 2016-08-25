#pragma once
#include "../Unit.h"
SCE_START
class Timer;
SCE_END
class Dummy;


class Missile : public Unit
{
    SPECIALFUNC_SET(Missile, default)
public:
    Missile();
    virtual ~Missile() override;

    virtual void Init()             override;
    virtual void Release()          override;
    virtual void Update(float dt)   override;
    virtual void Render()           override;

    void SetToPosChangeProbability(float prob);
    void SetAIRatio(float ratio);

    void AI(float dt);

private:
    std::shared_ptr<SCE::Timer> m_AITimer;
    std::shared_ptr<Dummy>      m_ToPosShow;
    SCE::Vec2                   m_ToPos;
    float                       m_ToPosChangeProbability;
};
