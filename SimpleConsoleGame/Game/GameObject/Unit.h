#pragma once
#include "Core/Game/Composite/GameObject.h"
#include "Core/Math/Vec2.h"
class Section;


class Unit : public SCE::GameObject
{
    SPECIALFUNC_SET(Unit, default)
    using SectionPtr = std::shared_ptr<Section>;
public:
    Unit();
    virtual ~Unit() override;

    virtual void Init()             override = 0;
    virtual void Release()          override = 0;
    virtual void Update(float dt)   override;
    virtual void Render()           override;

    virtual void Hitted(int damage);
    virtual void Death();

    bool        IsDeath() const;

    void        InitHp();
    void        SetMaxHp(int maxHp);
    void        SetSpeed(float speed);
    void        SetSection(const SectionPtr& section);
    void        AddMovePower(const SCE::Vec2& addPower);

    SCE::Vec2   GetPos() const;
    SectionPtr  GetSection() const;

private:
    void        MovePowerFixInLimit();
    void        PosFixInScreanBoundary();
    void        DirectionShow() const;

protected:
    SCE::Vec2   m_Pos;
    SCE::Vec2   m_MovePower;        // 현재의 이동방향과 속도축적값(벡터값)
    float       m_MovePowerLimit;   // zero에서 최대속도까지 도달하는데 걸리는 시간(초)
    float       m_MovePowerFrict;   // 마찰계수(1.0f이면, 최대속도에서 정지까지 1초 걸림, 2.0f면 0.5초 걸림)
    float       m_Speed;            // 최대속도에 도달시 초당 이동 칸수

    int         m_MaxHp;
    int         m_CurHp;

    bool        m_IsDeath;
    bool        m_HitRenderFlag;
    SectionPtr  m_Section;
};
