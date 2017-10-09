#pragma once
#include "Core/Game/Interface/IGame.h"
class Hero;
class Mob;


class Game : public SCE::IGame
{
    DECLARE_PIMPL
    SPECIALFUNC_SET(Game, delete)
    using HeroPtr   = std::shared_ptr<Hero>;
    using MobPtr    = std::shared_ptr<Mob>;
    using MobList   = std::list<MobPtr>;
public:
    Game() noexcept;
    virtual ~Game() override;

    virtual void Init()             override;
    virtual void Release()          override;
    virtual void Update(float _dt)  override;
    virtual void Render()           override;
};
