#include "stdafx.h"
#include "Unit.h"
#include "../Effect/Dummy.h"
#include "../../Skill.h"
#include "../../GameManager.h"
#include "../../Component/RenderComponent/CmdRenderComponent.h"
#include "../../Component/CollisionComponent/CollisionComponent.h"
#include "../../../Math/Vec2.h"
SCE_START


struct Unit::impl
{
    impl() noexcept
        : skillList{}
        , render{}
        , collision{}
        , hitRenderFlag{}
    {
    }

    SkillList       skillList;
    RenderRef       render;
    CollisionRef    collision;
    bool            hitRenderFlag;
};


Unit::Unit() noexcept
    : pimpl{ std::make_unique<impl>() }
{
}

Unit::~Unit()
{
}


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

void Unit::Release()
{
}

void Unit::Update(float _dt)
{
    auto collision = std::dynamic_pointer_cast<CollisionComponent>(pimpl->collision.lock());
    if (!collision || collision->IsDeath())
        return;

    GameObject::Update(_dt);

    for (auto& skill : pimpl->skillList)
    {
        skill->Update(_dt);
    }
}


RenderPtr Unit::GetRender()
{
    return pimpl->render.lock();
}

void Unit::Render()
{
    auto collision = std::dynamic_pointer_cast<CollisionComponent>(pimpl->collision.lock());
    if (!collision || collision->IsDeath())
        return;

    auto render = std::dynamic_pointer_cast<CmdRenderComponent>(pimpl->render.lock());
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


CollisionPtr Unit::GetCollision()
{
    return pimpl->collision.lock();
}

bool Unit::Hitted(int _damage)
{
    auto collision = std::dynamic_pointer_cast<CollisionComponent>(pimpl->collision.lock());
    if (!collision || collision->IsDeath())
        return false;

    if (collision->Hitted(_damage))
    {
        pimpl->hitRenderFlag = true;
        return true;
    }
    return false;
}

void Unit::Death()
{
    auto collision = std::dynamic_pointer_cast<CollisionComponent>(pimpl->collision.lock());
    if (!collision || collision->IsDeath())
        return;

    collision->Death();

    static auto& gm = GameManager::GetInstance();
    gm.RemoveRender(std::dynamic_pointer_cast<IRenderObject>(shared_from_this()));

    auto corpse = ObjectPool<Dummy>::GetWithInit();
    auto render = corpse->GetComponent<CmdRenderComponent>();
    if (render != nullptr)
    {
        render->SetCoord(Coord(GetPos()));
        render->SetShape(GetComponent<CmdRenderComponent>()->GetShape());
        render->SetColor(Color::BLACK);
        render->SetBGColor(Color::RED);
        gm.AddRender(corpse, 1.f);
    }
}


void Unit::AddSkill(const SkillPtr& _skill)
{
    if (_skill == nullptr)
        return;

    _skill->SetOwner(shared_from_this());
    pimpl->skillList.push_back(_skill);
}

Unit::SkillList& Unit::GetSkillList()
{
    return pimpl->skillList;
}

SCE_END
