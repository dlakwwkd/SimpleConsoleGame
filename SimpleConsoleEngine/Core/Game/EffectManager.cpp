#include "stdafx.h"
#include "EffectManager.h"
#include "EffectManagerImpl.hpp"
#include "Composite/Unit/Unit.h"
#include "../Math/Vec2.h"
SCE_USE

/////////////////////////////////////////////////////////////////////////////////////////
EffectManager::EffectManager() noexcept
    : pimpl{ std::make_unique<impl>() }
{
}

/////////////////////////////////////////////////////////////////////////////////////////
EffectManager::~EffectManager()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
void EffectManager::PlayEffect(
    const Unit& _owner,
    const Vec2& _pos,
    EffectType _type) const noexcept
{
    auto& func = pimpl->effectFuncList.at(static_cast<size_t>(_type));
    if (func)
    {
        func(*pimpl, _owner, _pos);
    }
}
