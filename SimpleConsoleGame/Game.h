#pragma once
#include "Core/Game/IGame.h"
class Unit;


class Game : public SCE::IGame
{
public:
    Game();
    virtual ~Game();

    void Init()             override;
    void Release()          override;
    void Update(float dt)   override;
    void Render()           override;

private:
    Unit* m_Unit;
};
