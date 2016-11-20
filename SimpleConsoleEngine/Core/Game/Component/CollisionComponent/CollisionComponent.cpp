#include "stdafx.h"
#include "CollisionComponent.h"
#include "../../Composite/CompositeBase.h"
#include "../../../ObjectPool/ObjectPool.h"
#include "../../GameManager.h"
SCE_START


CollisionComponent::CollisionComponent(const CompositeRef& owner) noexcept
    : m_Owner(owner)
    , m_MaxHp(0)
    , m_CurHp(0)
    , m_Damage(0)
    , m_IsDeath(false)
    , m_HitLock(false)
    , m_HitMask(CollisionMask::NONE)
    , m_AttackMask(CollisionMask::NONE)
{
}

CollisionComponent::~CollisionComponent()
{
}


void CollisionComponent::Init()
{
}

void CollisionComponent::Release()
{
    m_Section.reset();
}

void CollisionComponent::Update(float dt)
{
}


std::string CollisionComponent::GetComponentName() const
{
    return CONVERT_STRING(CollisionComponent);
}

IComponent::CompositePtr CollisionComponent::GetOwner() const
{
    return m_Owner.lock();
}

IComponent::IComponentPtr CollisionComponent::Copy() const
{
    return ObjectPool<CollisionComponent>::Get(*this);
}


bool CollisionComponent::Hitted(int damage)
{
    if (m_IsDeath || m_HitLock)
        return false;

    m_HitLock = true;
    GameManager::GetInstance().CallFuncAfterP(0.2f,
        std::dynamic_pointer_cast<ICollision>(m_Owner.lock()),
        &ICollision::SetHitLock,
        false);

    m_CurHp -= damage;
    if (m_CurHp <= 0)
    {
        m_CurHp = 0;
        Death();
    }
    return true;
}

void CollisionComponent::Death()
{
    if (m_IsDeath)
        return;

    m_IsDeath = true;
}


bool CollisionComponent::IsDeath() const
{
    return m_IsDeath;
}

bool CollisionComponent::CanAttack(const CollsionPtr& target) const
{
    if (target == nullptr)
        return false;

    return (target->GetHitMask() & m_AttackMask) == 0 ? false : true;
}


int CollisionComponent::GetCurHp() const
{
    return m_CurHp;
}

int CollisionComponent::GetMaxHp() const
{
    return m_MaxHp;
}

int CollisionComponent::GetDamage() const
{
    return m_Damage;
}

Vec2 CollisionComponent::GetPos() const
{
    // only GameObject
    return Vec2();
}

ICollision::SectionPtr CollisionComponent::GetSection() const
{
    return m_Section.lock();
}

ICollision::CollisionMask CollisionComponent::GetHitMask() const
{
    return m_HitMask;
}

ICollision::CollisionMask CollisionComponent::GetAttackMask() const
{
    return m_AttackMask;
}


void CollisionComponent::InitHp()
{
    m_CurHp = m_MaxHp;
}

void CollisionComponent::SetMaxHp(int maxHp)
{
    if (maxHp > 0)
    {
        m_MaxHp = maxHp;
    }
}

void CollisionComponent::SetDamage(int damage)
{
    m_Damage = damage;
}

void CollisionComponent::SetPos(const Vec2& pos)
{
    // only GameObject
}

void CollisionComponent::SetSection(const SectionPtr& section)
{
    m_Section = section;
}

void CollisionComponent::SetHitMask(CollisionMask mask)
{
    m_HitMask = mask;
}

void CollisionComponent::SetAttackMask(CollisionMask mask)
{
    m_AttackMask = mask;
}


void CollisionComponent::SetHitLock(bool lock)
{
    m_HitLock = lock;
}

SCE_END
