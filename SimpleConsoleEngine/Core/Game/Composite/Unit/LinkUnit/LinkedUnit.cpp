#include "stdafx.h"
#include "LinkedUnit.h"
#include "../../Effect/Effect.h"
#include "../../../GameManager.h"
#include "../../../Component/RenderComponent.h"
#include "../../../Component/CollisionComponent.h"
#include "../../../../Console/Console.h"
#include "../../../../Console/Coord.h"
#include "../../../../Math/Vec2.h"
SCE_USE

/////////////////////////////////////////////////////////////////////////////////////////
struct LinkedUnit::impl
{
    impl() noexcept
        : parent{}
        , localPos{}
        , isHpShared{ true }
    {
    }

    UnitPtr parent;
    Vec2    localPos;
    bool    isHpShared;
};

/////////////////////////////////////////////////////////////////////////////////////////
LinkedUnit::LinkedUnit() noexcept
    : pimpl{ std::make_unique<impl>() }
{
}

/////////////////////////////////////////////////////////////////////////////////////////
LinkedUnit::~LinkedUnit()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
void LinkedUnit::Init()
{
    Unit::Init();
}

/////////////////////////////////////////////////////////////////////////////////////////
void LinkedUnit::Release()
{
    pimpl->parent.reset();
    Unit::Release();
}

/////////////////////////////////////////////////////////////////////////////////////////
void LinkedUnit::Update(float _dt)
{
    if (!GetCollision() || GetCollision()->IsDeath())
        return;

    if (pimpl->parent != nullptr)
    {
        SetPos(pimpl->parent->GetPos() + pimpl->localPos);

        // 부모 유닛이 죽으면 나도 죽는다.
        if (auto& collision = pimpl->parent->GetCollision())
        {
            if (collision->IsDeath())
            {
                Unit::Death();
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
bool LinkedUnit::Hitted(int _damage)
{
    if (Unit::Hitted(_damage))
    {
        if (pimpl->isHpShared)
        {
            return pimpl->parent->Hitted(_damage);
        }
        return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
void LinkedUnit::Death()
{
    if (!pimpl->isHpShared)
    {
        Unit::Death();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void LinkedUnit::AddLinkedUnit(
    const UnitPtr& _parent,
    const Vec2& _pos,
    const Shape& _shape,
    bool _isHpShared,
    int _additionalHp,
    int _additionalDamage)
{
    if (_parent == nullptr)
        return;

    auto newUnit = ObjectPool<LinkedUnit>::GetWithInit();
    newUnit->pimpl->parent = _parent;
    newUnit->pimpl->localPos = _pos;
    newUnit->pimpl->isHpShared = _isHpShared;
    newUnit->SetPos(_parent->GetPos() + _pos);

    auto& collision = newUnit->GetCollision();
    auto& parentCollision = _parent->GetCollision();
    if (!collision || !parentCollision)
        return;

    if (_isHpShared)
    {
        // 체력 공유 시 부모의 자식리스트에 추가하고 부모의 체력을 늘려준다.
        _parent->AddSharedUnit(newUnit);
        if (_additionalHp != 0)
        {
            parentCollision->AddHp(_additionalHp, true);
        }
    }
    else
    {
        // 아닌 경우 스스로가 체력을 가진다.
        collision->SetMaxHp(_additionalHp);
        collision->InitHp();
    }
    collision->SetAttackMask(parentCollision->GetAttackMask());
    collision->SetHitMask(parentCollision->GetHitMask());
    collision->SetDamage(parentCollision->GetDamage() + _additionalDamage);

    if (auto& render = newUnit->GetRender())
    {
        render->SetShape(_shape);
        if (auto& parentRender = _parent->GetRender())
        {
            render->SetDepth(parentRender->GetDepth());
            render->SetShow(parentRender->IsShow());
        }
    }

    static auto& gm = GameManager::GetInstance();
    gm.RegisterCollision(newUnit);
    gm.AddRender(newUnit);
}
