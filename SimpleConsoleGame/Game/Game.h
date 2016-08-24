#pragma once
#include "Core/Game/Interface/IGameBase.h"
SCE_START
class Command;
SCE_END
class Unit;
class Hero;
class Mob;


class Game : public SCE::IGameBase
{
    SPECIALFUNC_SET(Game, delete)
public:
    Game();
    virtual ~Game() override;

    virtual void Init()             override;
    virtual void Release()          override;
    virtual void Update(float dt)   override;
    virtual void Render()           override;

private:
    void CommandProc(float dt);

private:
    std::unique_ptr<SCE::Command>   m_Command;
    std::unique_ptr<Hero>           m_Hero;
    std::vector<Mob>                m_MobList;
};
