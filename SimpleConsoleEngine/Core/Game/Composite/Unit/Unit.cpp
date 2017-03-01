#include "stdafx.h"
#include "Unit.h"
#include "../Effect/Effect.h"
#include "../../Skill.h"
#include "../../GameManager.h"
#include "../../EffectManager.h"
#include "../../Component/RenderComponent/CmdRenderComponent.h"
#include "../../Component/CollisionComponent/CollisionComponent.h"
#include "../../../Console/Coord.h"
#include "../../../Console/Color.hpp"
#include "../../../Math/Vec2.h"
SCE_USE

/////////////////////////////////////////////////////////////////////////////////////////
struct Unit::impl
{
    impl() noexcept
        : skillList{}
        , render{}
        , collision{}
        , hitRenderFlag{ false }
        , deathEffect{ EffectType::UNIT_DEATH }
    {
    }

    SkillList       skillList;
    RenderRef       render;
    CollisionRef    collision;
    bool            hitRenderFlag;
    EffectType      deathEffect;
};

/////////////////////////////////////////////////////////////////////////////////////////
Unit::Unit() noexcept
    : pimpl{ std::make_unique<impl>() }
{
}

/////////////////////////////////////////////////////////////////////////////////////////
Unit::~Unit()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
void Unit::Init()
{
    if (AddComponent<CmdRenderComponent>())
    {
        pimpl->render = GetComponent<CmdRenderComponent>();
    }
    if (AddComponent<CollisionComponent>())
    {
        pimpl->collision = GetComponent<CollisionComponent>();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void Unit::Release()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
void Unit::Update(float _dt)
{
    auto collision = ICollisionObject::Get<CollisionComponent>();
    if (!collision || collision->IsDeath())
        return;

    GameObject::Update(_dt);

    for (auto& skill : pimpl->skillList)
    {
        skill->Update(_dt);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
IRenderObject::RenderPtr Unit::GetRender() const
{
    return pimpl->render.lock();
}

/////////////////////////////////////////////////////////////////////////////////////////
void Unit::Render()
{
    auto collision = ICollisionObject::Get<CollisionComponent>();
    if (!collision || collision->IsDeath())
        return;

    auto render = IRenderObject::Get<CmdRenderComponent>();
    if (!render)
        return;

    render->SetCoord(Coord(GetPos()));
    if (pimpl->hitRenderFlag)
    {
        pimpl->hitRenderFlag = false;

        auto orgBGColor = render->GetBGColor();
        render->SetBGColor(Color::MAGENTA);
        render->Render();
        render->SetBGColor(orgBGColor);
    }
    else
    {
        render->Render();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
ICollisionObject::CollisionPtr Unit::GetCollision() const
{
    return pimpl->collision.lock();
}

/////////////////////////////////////////////////////////////////////////////////////////
bool Unit::Hitted(int _damage)
{
    auto collision = ICollisionObject::Get<CollisionComponent>();
    if (!collision || collision->IsDeath())
        return false;

    if (collision->Hitted(_damage))
    {
        pimpl->hitRenderFlag = true;
        return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
void Unit::Death()
{
    auto collision = ICollisionObject::Get<CollisionComponent>();
    if (!collision || collision->IsDeath())
        return;

    collision->Death();

    static auto& gm = GameManager::GetInstance();
    static auto& em = EffectManager::GetInstance();
    gm.RemoveRender(std::dynamic_pointer_cast<IRenderObject>(shared_from_this()));
    em.PlayEffect(*this, GetPos(), pimpl->deathEffect);
}

/////////////////////////////////////////////////////////////////////////////////////////
void Unit::SetDeathEffect(EffectType _type)
{
    pimpl->deathEffect = _type;
}

/////////////////////////////////////////////////////////////////////////////////////////
void Unit::AddSkill(const SkillPtr& _skill)
{
    if (_skill == nullptr)
        return;

    _skill->SetOwner(shared_from_this());
    pimpl->skillList.push_back(_skill);
}

/////////////////////////////////////////////////////////////////////////////////////////
Unit::SkillList& Unit::GetSkillList()
{
    return pimpl->skillList;
}
