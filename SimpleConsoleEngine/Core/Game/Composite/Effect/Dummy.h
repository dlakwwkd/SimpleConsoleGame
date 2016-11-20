#pragma once
#include "Core/Game/Composite/GameObject.h"
SCE_START
class Vec2;


class Dummy : public GameObject
{
    SPECIALFUNC_SET(Dummy, default)
public:
    Dummy() noexcept;
    virtual ~Dummy() override;

    virtual void Init()             override;
    virtual void Release()          override;
    virtual void Update(float dt)   override;
    virtual void Render()           override;
};

SCE_END
