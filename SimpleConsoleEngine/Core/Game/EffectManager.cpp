#include "stdafx.h"
#include "EffectManager.h"
#include "GameManager.h"
#include "Composite/Effect/Effect.h"
#include "Component/RenderComponent/CmdRenderComponent.h"
#include "../Math/Vec2.h"
SCE_START


struct EffectManager::impl
{
    impl() noexcept
    {
    }
    
    void ExplosionA(const Vec2& _pos) const noexcept;
    void ExplosionB(const Vec2& _pos) const noexcept;
    void ExplosionC(const Vec2& _pos) const noexcept;

    void CreateEffect(const Vec2& _pos, const Shape& _shape, float _delay, float _lifeTime) const noexcept;
    
    const size_t    spuenceASize = 10;
    const Vec2      spuenceA[10] =
    {
        Vec2::ZERO,
        Vec2::UP,
        Vec2::UP + Vec2::RIGHT,
        Vec2::RIGHT,
        Vec2::RIGHT + Vec2::DOWN,
        Vec2::DOWN,
        Vec2::DOWN + Vec2::LEFT,
        Vec2::LEFT,
        Vec2::LEFT + Vec2::UP,
        Vec2::UP,
    };
};


EffectManager::EffectManager() noexcept
    : pimpl{ std::make_unique<impl>() }
{
}

EffectManager::~EffectManager()
{
}


void EffectManager::PlayEffect(const Vec2& _pos, EffectType _type) const noexcept
{
    switch (_type)
    {
    case EffectType::EXPLOSION_A:   pimpl->ExplosionA(_pos);    break;
    case EffectType::EXPLOSION_B:   pimpl->ExplosionB(_pos);    break;
    case EffectType::EXPLOSION_C:   pimpl->ExplosionC(_pos);    break;
    default:
        break;
    }
}


void EffectManager::impl::ExplosionA(const Vec2& _pos) const noexcept
{
    for (int i = 0; i < spuenceASize; ++i)
    {
        CreateEffect(_pos + spuenceA[i], { L'▒', Color::MAGENTA, Color::BLUE }, 0.02f * i, 0.1f);
    }
}

void EffectManager::impl::ExplosionB(const Vec2& _pos) const noexcept
{
    for (int i = 0; i < spuenceASize; ++i)
    {
        CreateEffect(_pos + spuenceA[i], { L'▨', Color::WHITE, Color::CYAN }, 0.02f * i, 0.1f);
        CreateEffect(_pos + spuenceA[i], { L'▨', Color::WHITE, Color::CYAN }, 0.02f * i + 0.2f, 0.1f);
    }
}

void EffectManager::impl::ExplosionC(const Vec2& _pos) const noexcept
{
    for (int i = 0; i < spuenceASize; ++i)
    {
        CreateEffect(_pos + spuenceA[i], { L'▒', Color::YELLOW, Color::RED }, 0.02f * i, 0.1f);
    }
}


void EffectManager::impl::CreateEffect(const Vec2& _pos, const Shape& _shape, float _delay, float _lifeTime) const noexcept
{
    static auto& gm = GameManager::GetInstance();
    auto effect = ObjectPool<Effect>::GetWithInit();
    auto render = effect->Get<CmdRenderComponent>();
    if (render != nullptr)
    {
        render->SetCoord(Coord(_pos));
        render->SetShape(_shape);
        gm.CallFuncAfterM(_delay, &gm, &GameManager::AddRender, effect, _lifeTime);
    }
}

SCE_END
