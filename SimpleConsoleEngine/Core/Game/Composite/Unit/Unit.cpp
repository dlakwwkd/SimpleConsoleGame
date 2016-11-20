#include "stdafx.h"
#include "Unit.h"
#include "../Effect/Dummy.h"
#include "../../GameManager.h"
#include "../../Skill.h"
#include "../../Component/RenderComponent/CmdRenderComponent.h"
#include "../../Component/CollisionComponent/CollisionComponent.h"
#include "../../../ObjectPool/ObjectPool.h"
#include "../../../Console/Console.h"
SCE_START


Unit::Unit() noexcept
    : m_HitRenderFlag(false)
{
    if (AddComponent<CmdRenderComponent>())
    {
        m_Render = GetComponent<CmdRenderComponent>();
    }
    if (AddComponent<CollisionComponent>())
    {
        m_Collision = GetComponent<CollisionComponent>();
    }
}

Unit::~Unit()
{
}


void Unit::Init()
{
}

void Unit::Release()
{
}

void Unit::Update(float dt)
{
    if (IsDeath())
        return;

    for (auto& skill : m_SkillList)
    {
        skill->Update(dt);
    }
}

void Unit::Render()
{
    if (IsDeath())
        return;

    auto render = std::dynamic_pointer_cast<CmdRenderComponent>(m_Render.lock());
    if (render == nullptr)
        return;

    render->SetCoord(Coord(GetPos()));
    if (m_HitRenderFlag)
    {
        m_HitRenderFlag = false;
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


bool Unit::Hitted(int damage)
{
    if (IsDeath())
        return false;

    auto collision = m_Collision.lock();
    if (collision == nullptr)
        return false;

    if (collision->Hitted(damage))
    {
        m_HitRenderFlag = true;
        return true;
    }
    return false;
}

void Unit::Death()
{
    if (IsDeath())
        return;

    auto collision = m_Collision.lock();
    if (collision == nullptr)
        return;

    collision->Death();

    auto corpse = ObjectPool<Dummy>::Get();
    auto render = corpse->GetComponent<CmdRenderComponent>();
    if (render != nullptr)
    {
        render->SetCoord(Coord(GetPos()));
        render->SetShape(GetComponent<CmdRenderComponent>()->GetShape());
        render->SetColor(Color::BLACK);
        render->SetBGColor(Color::RED);
        GameManager::GetInstance().AddRender(corpse, 1.f);
    }
}


bool Unit::IsDeath() const
{
    auto collision = m_Collision.lock();
    if (collision == nullptr)
        return false;

    return collision->IsDeath();
}

bool Unit::CanAttack(const CollsionPtr& target) const
{
    auto collision = m_Collision.lock();
    if (collision == nullptr)
        return false;

    return collision->CanAttack(target);
}


int Unit::GetCurHp() const
{
    auto collision = m_Collision.lock();
    if (collision == nullptr)
        return 0;

    return collision->GetCurHp();
}

int Unit::GetMaxHp() const
{
    auto collision = m_Collision.lock();
    if (collision == nullptr)
        return 0;

    return collision->GetMaxHp();
}

int Unit::GetDamage() const
{
    auto collision = m_Collision.lock();
    if (collision == nullptr)
        return 0;

    return collision->GetDamage();
}

Vec2 Unit::GetPos() const
{
    return GameObject::GetPos();
}

Unit::SectionPtr Unit::GetSection() const
{
    auto collision = m_Collision.lock();
    if (collision == nullptr)
        return nullptr;

    return collision->GetSection();
}

Unit::CollisionMask Unit::GetHitMask() const
{
    auto collision = m_Collision.lock();
    if (collision == nullptr)
        return CollisionMask::NONE;

    return collision->GetHitMask();
}

Unit::CollisionMask Unit::GetAttackMask() const
{
    auto collision = m_Collision.lock();
    if (collision == nullptr)
        return CollisionMask::NONE;

    return collision->GetAttackMask();
}


void Unit::InitHp()
{
    auto collision = m_Collision.lock();
    if (collision != nullptr)
    {
        collision->InitHp();
    }
}

void Unit::SetMaxHp(int maxHp)
{
    auto collision = m_Collision.lock();
    if (collision != nullptr)
    {
        collision->SetMaxHp(maxHp);
    }
}

void Unit::SetDamage(int damage)
{
    auto collision = m_Collision.lock();
    if (collision != nullptr)
    {
        collision->SetDamage(damage);
    }
}

void Unit::SetPos(const Vec2& pos)
{
    GameObject::SetPos(pos);
}

void Unit::SetSection(const SectionPtr& section)
{
    auto collision = m_Collision.lock();
    if (collision != nullptr)
    {
        collision->SetSection(section);
    }
}

void Unit::SetHitMask(CollisionMask mask)
{
    auto collision = m_Collision.lock();
    if (collision != nullptr)
    {
        collision->SetHitMask(mask);
    }
}

void Unit::SetAttackMask(CollisionMask mask)
{
    auto collision = m_Collision.lock();
    if (collision != nullptr)
    {
        collision->SetAttackMask(mask);
    }
}

void Unit::SetHitLock(bool lock)
{
    auto collision = m_Collision.lock();
    if (collision != nullptr)
    {
        collision->SetHitLock(lock);
    }
}


void Unit::AddSkill(const SkillPtr& skill)
{
    if (skill == nullptr)
        return;

    skill->SetOwner(shared_from_this());
    m_SkillList.push_back(skill);
}

SCE_END
