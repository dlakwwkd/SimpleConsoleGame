#include "stdafx.h"
#include "EffectManager.h"
#include "GameManager.h"
#include "Composite/Effect/Effect.h"
#include "Component/RenderComponent/CmdRenderComponent.h"
#include "../Math/Vec2.h"
SCE_START


struct EffectManager::impl
{
    using EffectFunc    = std::function<void(impl&, const Vec2&)>;
    using SequenceFunc  = std::function<void(const Vec2&, int)>;

    impl() noexcept
    {
        RegisterEffectFunc();
        RegisterSequence();
    }

    void RegisterEffectFunc();
    void RegisterSequence();

    void CreateEffect(const Vec2& _pos, const Shape& _shape, float _delay, float _lifeTime) const noexcept;

    void ExplosionA(const Vec2& _pos) const noexcept;
    void ExplosionB(const Vec2& _pos) const noexcept;
    void ExplosionC(const Vec2& _pos) const noexcept;

    class Sequence
    {
    public:
        enum Type
        {
            SEQUENCE_TYPE_A,
            SEQUENCE_TYPE_B,
            SEQUENCE_TYPE_MAX
        };
        void Init(std::vector<Vec2> _posList) noexcept;
        void Play(SequenceFunc _func) const noexcept;

    private:
        std::vector<Vec2> posList;
    };

    std::vector<EffectFunc> effectFuncList;
    std::vector<Sequence>   sequenceList;
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
    auto& func = pimpl->effectFuncList.at(static_cast<size_t>(_type));
    if (func)
    {
        func(*pimpl, _pos);
    }
}


void EffectManager::impl::RegisterEffectFunc()
{
    if (!effectFuncList.empty())
        return;

    effectFuncList.resize((size_t)EffectType::EFFECT_TYPE_MAX);
    effectFuncList[(size_t)EffectType::EXPLOSION_A] = &impl::ExplosionA;
    effectFuncList[(size_t)EffectType::EXPLOSION_B] = &impl::ExplosionB;
    effectFuncList[(size_t)EffectType::EXPLOSION_C] = &impl::ExplosionC;
}

void EffectManager::impl::RegisterSequence()
{
    if (!sequenceList.empty())
        return;

    sequenceList.resize(Sequence::SEQUENCE_TYPE_MAX);
    sequenceList[Sequence::SEQUENCE_TYPE_A].Init(
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
    });
    sequenceList[Sequence::SEQUENCE_TYPE_B].Init(
    {
        Vec2::ZERO,
        Vec2::UP,
        Vec2::UP + Vec2::LEFT,
        Vec2::LEFT,
        Vec2::LEFT + Vec2::DOWN,
        Vec2::DOWN,
        Vec2::DOWN + Vec2::RIGHT,
        Vec2::RIGHT,
        Vec2::RIGHT + Vec2::UP,
        Vec2::UP,
    });
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


void EffectManager::impl::ExplosionA(const Vec2& _pos) const noexcept
{
    sequenceList[Sequence::SEQUENCE_TYPE_A].Play(
        [&](const Vec2& _squencePos, int _i)
        {
            CreateEffect(_pos + _squencePos,
                { L'▒', Color::MAGENTA, Color::BLUE },
                0.01f * _i,
                0.05f);
            CreateEffect(_pos + _squencePos,
                { L'▒', Color::MAGENTA, Color::BLUE },
                0.01f * _i + 0.1f,
                0.05f);
        });
}

void EffectManager::impl::ExplosionB(const Vec2& _pos) const noexcept
{
    sequenceList[Sequence::SEQUENCE_TYPE_A].Play(
        [&](const Vec2& _squencePos, int _i)
        {
            CreateEffect(_pos + _squencePos,
                { L'▨', Color::WHITE, Color::CYAN },
                0.02f * _i,
                0.1f);
        });
    sequenceList[Sequence::SEQUENCE_TYPE_B].Play(
        [&](const Vec2& _squencePos, int _i)
        {
            CreateEffect(_pos + _squencePos,
                { L'▨', Color::WHITE, Color::CYAN },
                0.02f * _i + 0.2f,
                0.1f);
        });
}

void EffectManager::impl::ExplosionC(const Vec2& _pos) const noexcept
{
    sequenceList[Sequence::SEQUENCE_TYPE_A].Play(
        [&](const Vec2& _squencePos, int _i)
        {
            CreateEffect(_pos + _squencePos,
                { L'▒', Color::YELLOW, Color::RED },
                0.02f * _i,
                0.1f);
        });
}


void EffectManager::impl::Sequence::Init(std::vector<Vec2> _posList) noexcept
{
    posList = std::move(_posList);
}

void EffectManager::impl::Sequence::Play(SequenceFunc _func) const noexcept
{
    for (int i = 0; i < posList.size(); ++i)
    {
        _func(posList[i], i);
    }
}

SCE_END
