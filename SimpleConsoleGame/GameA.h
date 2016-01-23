#pragma once
#include "GameBase.h"
class GameA : public GameBase
{
public:
    GameA();
    ~GameA() override;

    void Init()             override;
    void Release()          override;

    void Update(float dt)   override;
    void Render()           override;
};
