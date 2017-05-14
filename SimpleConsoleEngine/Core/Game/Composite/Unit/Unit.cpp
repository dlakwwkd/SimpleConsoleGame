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
        , hitRenderFlag{ false }
        , deathEffect{ EffectType::UNIT_DEATH }
        , sharedUnitList{}
    {
    }
    using UnitRef   = std::weak_ptr<Unit>;
    using UnitList  = std::vector<UnitRef>;

    SkillList   skillList;
    bool        hitRenderFlag;
    EffectType  deathEffect;
    UnitList    sharedUnitList;
};

/////////////////////////////////////////////////////////////////////////////////////////
Unit::Unit() noexcept
    : pimpl{ std::make_unique<impl>() }
    , render{}
    , collision{}
{
}

/////////////////////////////////////////////////////////////////////////////////////////
Unit::~Unit()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
void Unit::Init()
{
    render = AddComponent<CmdRenderComponent>();
    collision = AddComponent<CollisionComponent>();
}

/////////////////////////////////////////////////////////////////////////////////////////
void Unit::Release()
{
    RemoveComponent<CmdRenderComponent>();
    RemoveComponent<CollisionComponent>();
    render.reset();
    collision.reset();
}

/////////////////////////////////////////////////////////////////////////////////////////
void Unit::Update(float _dt)
{
    if (!collision || collision->IsDeath())
        return;

    GameObject::Update(_dt);

    for (auto& skill : pimpl->skillList)
    {
        skill->Update(_dt);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void Unit::Render()
{
    if (!collision || collision->IsDeath())
        return;

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
bool Unit::Hitted(int _damage)
{
    if (!collision || collision->IsDeath())
        return false;

    if (collision->Hitted(_damage))
    {
        pimpl->hitRenderFlag = true;
        for (auto& unitRef : pimpl->sharedUnitList)
        {
            if (auto unit = unitRef.lock())
            {
                unit->pimpl->hitRenderFlag = true;
            }
        }
        return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
void Unit::Death()
{
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
void Unit::AddSharedUnit(const UnitPtr& _unit)
{
    pimpl->sharedUnitList.push_back(_unit);
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
