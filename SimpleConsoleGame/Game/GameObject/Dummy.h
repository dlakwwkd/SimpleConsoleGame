#pragma once
#include "Core/Game/Composite/GameObject.h"


class Dummy : public SCE::GameObject
{
    SPECIALFUNC_SET(Dummy, default)
public:
    Dummy();
    virtual ~Dummy() override;

    virtual void Init()             override;
    virtual void Release()          override;
    virtual void Update(float dt)   override;
    virtual void Render()           override;
};
