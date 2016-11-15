﻿#pragma once
#include "Core/Game/Composite/GameObject.h"
#include "Core/Math/Vec2.h"
class Section;
class Skill;


class Unit : public SCE::GameObject
{
    SPECIALFUNC_SET(Unit, default)
    using SectionPtr    = std::shared_ptr<Section>;
    using SectionRef    = std::weak_ptr<Section>;
    using UnitPtr       = std::shared_ptr<Unit>;
    using SkillPtr      = std::shared_ptr<Skill>;
    using SkillList     = std::vector<SkillPtr>;
public:
    enum CollisionMask : unsigned char
    {
        NONE    = 0,
        PLAYER  = 1 << 0,
        ENEMY   = 1 << 1,
        ALL     = PLAYER | ENEMY
    };
    static bool     IsCollisionAble(const UnitPtr& unitA, const UnitPtr& unitB);
public:
    Unit();
    virtual ~Unit() override;

    virtual void    Init()              override = 0;
    virtual void    Release()           override = 0;
    virtual void    Update(float dt)    override;
    virtual void    Render()            override;

    virtual void    Hitted(int damage);
    virtual void    Death();

    bool            IsDeath() const;
    bool            CanAttack(const UnitPtr& target) const;

    void            InitHp();
    void            SetMaxHp(int maxHp);
    void            SetDamage(int damage);
    void            SetSpeed(float speed);
    void            SetMovePowerLimit(float ratio);
    void            SetMovePowerFrict(float ratio);
    void            SetPos(const SCE::Vec2& pos);
    void            SetSection(const SectionPtr& section);
    void            SetHitMask(CollisionMask mask);
    void            SetAttackMask(CollisionMask mask);
    void            AddMovePower(const SCE::Vec2& addPower);
    void            AddSkill(const SkillPtr& skill);

    int             GetDamage() const;
    SCE::Vec2       GetPos() const;
    SCE::Vec2       GetDirection() const;
    SectionPtr      GetSection() const;
    CollisionMask   GetHitMask() const;
    CollisionMask   GetAttackMask() const;

private:
    void            MovePowerFixInLimit();
    void            PosFixInScreanBoundary();
    void            DirectionShow() const;
    void            SetHitLock(bool lock);

protected:
    SCE::Vec2       m_Pos;
    SCE::Vec2       m_Direction;        // 이동방향(벡터값)
    SCE::Vec2       m_MovePower;        // 현재의 속도축적값(벡터값)
    float           m_MovePowerLimit;   // zero에서 최대속도까지 도달하는데 걸리는 시간(초)
    float           m_MovePowerFrict;   // 마찰계수(1.0f이면, 최대속도에서 정지까지 1초 걸림, 2.0f면 0.5초 걸림)
    float           m_Speed;            // 최대속도에 도달시 초당 이동 칸수

    int             m_MaxHp;
    int             m_CurHp;
    int             m_Damage;

    bool            m_IsDeath;
    bool            m_HitRenderFlag;
    bool            m_HitLock;
    SectionRef      m_Section;
    CollisionMask   m_HitMask;          // 맞을 수 있는 공격 종류
    CollisionMask   m_AttackMask;       // 때릴 수 있는 공격 종류

    SkillList       m_SkillList;
};
