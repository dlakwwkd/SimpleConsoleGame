#pragma once
#include "../CompositeBase.h"
#include "../Interface/IGameBase.h"
SCE_START


class GameObject : public IGameBase, public CompositeBase
{
    SPECIALFUNC_DECLARE(GameObject)
public:
    GameObject();
    virtual ~GameObject() override;

    virtual void Init() override;
    virtual void Release() override;
    virtual void Update(float dt) override;
    virtual void Render() override;
};

SCE_END
