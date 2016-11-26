#pragma once
#include "Core/Game/Interface/IGame.h"
SCE_START
class Command;
SCE_END
class Hero;
class Mob;


class Game : public SCE::IGame
{
    DECLARE_PIMPL
    SPECIALFUNC_SET(Game, delete)
    using CommandPtr    = std::unique_ptr<SCE::Command>;
    using HeroPtr       = std::shared_ptr<Hero>;
    using MobPtr        = std::shared_ptr<Mob>;
    using MobList       = std::vector<MobPtr>;
public:
    Game() noexcept;
    ~Game();

    virtual void Init()             override;
    virtual void Release()          override;
    virtual void Update(float _dt)  override;
    virtual void Render()           override;
};
