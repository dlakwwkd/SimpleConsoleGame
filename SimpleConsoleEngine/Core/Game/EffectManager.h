#pragma once
SCE_START
class Vec2;


enum class EffectType
{
    EXPLOSION_A,
    EXPLOSION_B,
    EXPLOSION_C,

    EFFECT_TYPE_MAX
};

class EffectManager
{
    DECLARE_PIMPL
    CREATE_SINGLETON_NOEXCEPT(EffectManager)
public:
    void PlayEffect(const Vec2& _pos, EffectType _type) const noexcept;
};

SCE_END
