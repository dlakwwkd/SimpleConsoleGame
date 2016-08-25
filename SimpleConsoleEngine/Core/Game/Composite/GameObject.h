#pragma once
#include "../CompositeBase.h"
SCE_START


class GameObject : public CompositeBase
{
    SPECIALFUNC_DECLARE(GameObject)
public:
    GameObject();
    virtual ~GameObject();

    virtual void Init();
    virtual void Release();
    virtual void Update(float dt);
    virtual void Render();
};

SCE_END
