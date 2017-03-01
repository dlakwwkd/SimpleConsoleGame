#include "stdafx.h"
#include "CollisionComponent.h"
#include "../../GameManager.h"
#include "../../Composite/Unit/Unit.h"
SCE_USE

/////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////
CollisionComponent::CollisionComponent(const CompositeRef& _owner) noexcept
    : pimpl{ std::make_unique<impl>(_owner) }
{
}

/////////////////////////////////////////////////////////////////////////////////////////
CollisionComponent::~CollisionComponent()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
std::string CollisionComponent::GetComponentName() const
{
    return CONVERT_STRING(CollisionComponent);
}

/////////////////////////////////////////////////////////////////////////////////////////
IComponent::CompositePtr CollisionComponent::GetOwner() const
{
    return pimpl->owner.lock();
}

/////////////////////////////////////////////////////////////////////////////////////////
bool CollisionComponent::Hitted(int _damage) noexcept
{
    if (pimpl->isDeath || pimpl->hitLock)
        return false;

    pimpl->hitLock = true;
    GameManager::GetInstance().CallFuncAfterP(0.1f,
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

/////////////////////////////////////////////////////////////////////////////////////////
void CollisionComponent::Death() noexcept
{
    pimpl->isDeath = true;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool CollisionComponent::IsDeath() const noexcept
{
    return pimpl->isDeath;
}

/////////////////////////////////////////////////////////////////////////////////////////
bool CollisionComponent::CanAttack(const CollsionPtr& _target) const noexcept
{
    if (_target == nullptr)
        return false;

    return (_target->GetHitMask() & pimpl->attackMask) == 0 ? false : true;
}

/////////////////////////////////////////////////////////////////////////////////////////
int CollisionComponent::GetCurHp() const noexcept
{
    return pimpl->curHp;
}

/////////////////////////////////////////////////////////////////////////////////////////
int CollisionComponent::GetMaxHp() const noexcept
{
    return pimpl->maxHp;
}

/////////////////////////////////////////////////////////////////////////////////////////
int CollisionComponent::GetDamage() const noexcept
{
    return pimpl->damage;
}

/////////////////////////////////////////////////////////////////////////////////////////
CollisionComponent::SectionPtr CollisionComponent::GetSection() const noexcept
{
    return pimpl->section.lock();
}

/////////////////////////////////////////////////////////////////////////////////////////
CollisionComponent::CollisionMask CollisionComponent::GetHitMask() const noexcept
{
    return pimpl->hitMask;
}

/////////////////////////////////////////////////////////////////////////////////////////
CollisionComponent::CollisionMask CollisionComponent::GetAttackMask() const noexcept
{
    return pimpl->attackMask;
}

/////////////////////////////////////////////////////////////////////////////////////////
void CollisionComponent::InitHp() noexcept
{
    pimpl->curHp = pimpl->maxHp;
}

/////////////////////////////////////////////////////////////////////////////////////////
void CollisionComponent::SetMaxHp(int _maxHp) noexcept
{
    if (_maxHp > 0)
    {
        pimpl->maxHp = _maxHp;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void CollisionComponent::SetDamage(int _damage) noexcept
{
    pimpl->damage = _damage;
}

/////////////////////////////////////////////////////////////////////////////////////////
void CollisionComponent::SetSection(const SectionPtr& _section) noexcept
{
    pimpl->section = _section;
}

/////////////////////////////////////////////////////////////////////////////////////////
void CollisionComponent::SetHitMask(CollisionMask _mask) noexcept
{
    pimpl->hitMask = _mask;
}

/////////////////////////////////////////////////////////////////////////////////////////
void CollisionComponent::SetAttackMask(CollisionMask _mask) noexcept
{
    pimpl->attackMask = _mask;
}

/////////////////////////////////////////////////////////////////////////////////////////
void CollisionComponent::SetHitLock(bool _lock) noexcept
{
    pimpl->hitLock = _lock;
}
