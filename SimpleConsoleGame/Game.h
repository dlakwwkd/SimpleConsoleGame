#pragma once
#include "Core/Game/IGame.h"


class Game : public SCE::IGame
{
public:
    Game();
    ~Game() override;

    void Init()             override;
    void Release()          override;
    void Update(float dt)   override;
    void Render()           override;
};
