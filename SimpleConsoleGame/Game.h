#pragma once
#include "Core/Game/IGame.h"
SCE_USE


class Game : public IGame
{
public:
    Game();
    ~Game() override;

    void Init()             override;
    void Release()          override;
    void Update(float dt)   override;
    void Render()           override;
};
