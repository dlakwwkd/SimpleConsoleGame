#include "stdafx.h"
#include "CollisionComponent.h"
#include "../../GameManager.h"
#include "../../Composite/Unit/Unit.h"
SCE_START


struct CollisionComponent::impl
{
    impl(const CompositeRef& _owner) noexcept
        : owner{ _owner }
        , section{}
        , maxHp{}
        , curHp{}
        , damage{}
        , isDeath{}
        , hitLock{}
        , hitMask{}
        , attackMask{}
    {
    }

    CompositeRef    owner;
    SectionRef      section;
    int             maxHp;
    int             curHp;
    int             damage;
    bool            isDeath;
    bool            hitLock;
    CollisionMask   hitMask;    // 맞을 수 있는 공격 종류
    CollisionMask   attackMask; // 때릴 수 있는 공격 종류
};


CollisionComponent::CollisionComponent(const CompositeRef& _owner) noexcept
    : pimpl{ std::make_unique<impl>(_owner) }
{
}

CollisionComponent::~CollisionComponent()
{
}


std::string CollisionComponent::GetComponentName() const
{
    return CONVERT_STRING(CollisionComponent);
}

IComponent::CompositePtr CollisionComponent::GetOwner() const
{
    return pimpl->owner.lock();
}


bool CollisionComponent::Hitted(int _damage)
{
    if (pimpl->isDeath || pimpl->hitLock)
        return false;

    pimpl->hitLock = true;
    GameManager::GetInstance().CallFuncAfterP(0.2f,
        std::dynamic_pointer_cast<CollisionComponent>(shared_from_this()),
        &CollisionComponent::SetHitLock,
        false);

    pimpl->curHp -= _damage;
    if (pimpl->curHp <= 0)
    {
        pimpl->curHp = 0;

        auto owner = std::dynamic_pointer_cast<ICollisionObject>(pimpl->owner.lock());
        owner->Death();
    }
    return true;
}

void CollisionComponent::Death()
{
    pimpl->isDeath = true;
}


bool CollisionComponent::IsDeath() const
{
    return pimpl->isDeath;
}

bool CollisionComponent::CanAttack(const CollsionPtr& _target) const
{
    if (_target == nullptr)
        return false;

    return (_target->GetHitMask() & pimpl->attackMask) == 0 ? false : true;
}


int CollisionComponent::GetCurHp() const
{
    return pimpl->curHp;
}

int CollisionComponent::GetMaxHp() const
{
    return pimpl->maxHp;
}

int CollisionComponent::GetDamage() const
{
    return pimpl->damage;
}

CollisionComponent::SectionPtr CollisionComponent::GetSection() const
{
    return pimpl->section.lock();
}

CollisionComponent::CollisionMask CollisionComponent::GetHitMask() const
{
    return pimpl->hitMask;
}

CollisionComponent::CollisionMask CollisionComponent::GetAttackMask() const
{
    return pimpl->attackMask;
}


void CollisionComponent::InitHp()
{
    pimpl->curHp = pimpl->maxHp;
}

void CollisionComponent::SetMaxHp(int _maxHp)
{
    if (_maxHp > 0)
    {
        pimpl->maxHp = _maxHp;
    }
}

void CollisionComponent::SetDamage(int _damage)
{
    pimpl->damage = _damage;
}

void CollisionComponent::SetSection(const SectionPtr& _section)
{
    pimpl->section = _section;
}

void CollisionComponent::SetHitMask(CollisionMask _mask)
{
    pimpl->hitMask = _mask;
}

void CollisionComponent::SetAttackMask(CollisionMask _mask)
{
    pimpl->attackMask = _mask;
}


void CollisionComponent::SetHitLock(bool _lock)
{
    pimpl->hitLock = _lock;
}

SCE_END
