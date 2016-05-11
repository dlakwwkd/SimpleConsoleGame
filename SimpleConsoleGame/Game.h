#pragma once
#include "Core/Game/IGame.h"
SCE_START
class Command;
SCE_END
class Unit;


class Game : public SCE::IGame
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

private:
    std::unique_ptr<SCE::Command>   m_Command;
    std::unique_ptr<Unit>           m_Unit;
};
