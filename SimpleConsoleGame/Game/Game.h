#pragma once
#include "SimpleConsoleEngine/Core/Game/GameBase.h"
SCE_START
class Command;
SCE_END
class Unit;
class Hero;
class Mob;


class Game : public SCE::GameBase
{
    SPECIALFUNC_SET(Game, delete)
public:
    Game();
    ~Game() override;

    void Init()             override;
    void Release()          override;
    void Update(float dt)   override;
    void Render()           override;

private:
    void CommandProc(float dt);
    void FrameShow();

private:
    std::unique_ptr<SCE::Command>   m_Command;
    std::unique_ptr<Hero>           m_Hero;
    std::vector<Mob>                m_MobList;
};
