#pragma once
#include "../GameObject.h"
SCE_START
class Vec2;

/////////////////////////////////////////////////////////////////////////////////////////
class Camera : public GameObject
{
    DECLARE_PIMPL
    SPECIALFUNC_MOVE_SET(Camera, default)
    using GameObjectRef = std::weak_ptr<GameObject>;
public:
    enum class MoveType
    {
        NON_TRACKING,
        FIX_TO_OBJECT,
        EASE_IN_OUT,
        END
    };
public:
    Camera() noexcept;
    virtual ~Camera() override;

    virtual void    Init() override;
    virtual void    Release() override;
    virtual void    Update(float _dt) override;

    void            ChangeMoveTypeToNext();
    void            SetMoveType(MoveType _type);

    void            AttachToObject(const GameObjectRef& _obj);
    void            DetachObject();

private:
    void            MoveToAttachedObject(float _dt);
};

SCE_END
