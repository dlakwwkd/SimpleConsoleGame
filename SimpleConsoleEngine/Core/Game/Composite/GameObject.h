#pragma once
#include "../CompositeBase.h"
SCE_START


class GameObject : public CompositeBase
{
    SPECIALFUNC_DECLARE_NOEXCEPT(GameObject)
public:
    GameObject() noexcept;
    virtual ~GameObject();

    virtual void Init();
    virtual void Release();
    virtual void Update(float dt);
    virtual void Render();
};

SCE_END
