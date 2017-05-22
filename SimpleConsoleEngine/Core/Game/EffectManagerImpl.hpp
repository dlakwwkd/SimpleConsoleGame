#include "GameManager.h"
#include "Composite/Unit/Unit.h"
#include "Composite/Effect/Effect.h"
#include "Component/RenderComponent/CmdRenderComponent.h"
#include "../Math/Vec2.h"
#include "../Console/Coord.h"
#include "../Console/Shape.h"
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
struct EffectManager::impl
{
    using EffectFunc    = std::function<void(impl&, const Unit&, const Vec2&)>;
    using SequenceFunc  = std::function<void(const Vec2&, size_t)>;

    impl() noexcept
    {
        RegisterEffectFunc();
        RegisterSequence();
    }

    void RegisterEffectFunc();
    void RegisterSequence();

    void CreateEffect(
        const Vec2& _pos,
        const Shape& _shape,
        float _delay,
        float _lifeTime) const noexcept;

    void UnitDeath(const Unit& _owner, const Vec2& _pos) const noexcept;
    void ExplosionA(const Unit& _owner, const Vec2& _pos) const noexcept;
    void ExplosionB(const Unit& _owner, const Vec2& _pos) const noexcept;
    void ExplosionC(const Unit& _owner, const Vec2& _pos) const noexcept;

    /////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////
void EffectManager::impl::RegisterEffectFunc()
{
    if (!effectFuncList.empty())
        return;

    effectFuncList.resize((size_t)EffectType::EFFECT_TYPE_MAX);
    effectFuncList[(size_t)EffectType::UNIT_DEATH] = &impl::UnitDeath;
    effectFuncList[(size_t)EffectType::EXPLOSION_A] = &impl::ExplosionA;
    effectFuncList[(size_t)EffectType::EXPLOSION_B] = &impl::ExplosionB;
    effectFuncList[(size_t)EffectType::EXPLOSION_C] = &impl::ExplosionC;
}

/////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////
void EffectManager::impl::CreateEffect(
    const Vec2& _pos,
    const Shape& _shape,
    float _delay,
    float _lifeTime) const noexcept
{
    auto effect = ObjectPool<Effect>::GetWithInit();
    if (auto& render = effect->GetRender())
    {
        render->SetCoord(Coord(_pos));
        render->SetShape(_shape);

        static auto& gm = GameManager::GetInstance();
        gm.CallFuncAfterM(_delay, &gm, &GameManager::AddRender, effect, _lifeTime);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void EffectManager::impl::UnitDeath(const Unit& _owner, const Vec2& _pos) const noexcept
{
    if (auto& render = _owner.GetRender())
    {
        auto shape = render->GetShape();
        shape.color = Color::BLACK;
        shape.bgColor = Color::RED;
        CreateEffect(_pos, shape, 0.f, 1.f);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void EffectManager::impl::ExplosionA(const Unit& _owner, const Vec2& _pos) const noexcept
{
    sequenceList[Sequence::SEQUENCE_TYPE_A].Play(
        [&](const Vec2& _squencePos, size_t _i)
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

/////////////////////////////////////////////////////////////////////////////////////////
void EffectManager::impl::ExplosionB(const Unit& _owner, const Vec2& _pos) const noexcept
{
    sequenceList[Sequence::SEQUENCE_TYPE_A].Play(
        [&](const Vec2& _squencePos, size_t _i)
        {
            CreateEffect(_pos + _squencePos,
                { L'▨', Color::WHITE, Color::CYAN },
                0.02f * _i,
                0.1f);
        });
    sequenceList[Sequence::SEQUENCE_TYPE_B].Play(
        [&](const Vec2& _squencePos, size_t _i)
        {
            CreateEffect(_pos + _squencePos,
                { L'▨', Color::WHITE, Color::CYAN },
                0.02f * _i + 0.2f,
                0.1f);
        });
}

/////////////////////////////////////////////////////////////////////////////////////////
void EffectManager::impl::ExplosionC(const Unit& _owner, const Vec2& _pos) const noexcept
{
    sequenceList[Sequence::SEQUENCE_TYPE_A].Play(
        [&](const Vec2& _squencePos, size_t _i)
        {
            CreateEffect(_pos + _squencePos,
                { L'▒', Color::YELLOW, Color::RED },
                0.02f * _i,
                0.1f);
        });
}

/////////////////////////////////////////////////////////////////////////////////////////
void EffectManager::impl::Sequence::Init(std::vector<Vec2> _posList) noexcept
{
    posList = std::move(_posList);
}

/////////////////////////////////////////////////////////////////////////////////////////
void EffectManager::impl::Sequence::Play(SequenceFunc _func) const noexcept
{
    for (size_t i = 0; i < posList.size(); ++i)
    {
        _func(posList[i], i);
    }
}

SCE_END
