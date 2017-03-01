#pragma once
#include "../Interface/Object/IGameObject.h"
#include "CompositeBase.h"
SCE_START
class Vec2;

/////////////////////////////////////////////////////////////////////////////////////////
class GameObject
    : public IGameObject
    , public CompositeBase
{
    DECLARE_PIMPL
    SPECIALFUNC_MOVE_SET(GameObject, default)
public:
    GameObject() noexcept;
    virtual ~GameObject() override;

    virtual void    Init()              override;
    virtual void    Release()           override;
    virtual void    Update(float _dt)   override;

    Vec2            GetPos() const noexcept;
    Vec2            GetDirection() const noexcept;
    float           GetMovePowerLimit() const noexcept;
    float           GetMovePowerFrict() const noexcept;
    float           GetSpeed() const noexcept;

    void            SetPos(const Vec2& _pos) noexcept;
    void            SetDirection(const Vec2& _dir) noexcept;
    void            SetMovePower(const Vec2& _power) noexcept;
    void            AddMovePower(const Vec2& _addPower) noexcept;
    void            SetMovePowerLimit(float _ratio) noexcept;
    void            SetMovePowerFrict(float _ratio) noexcept;
    void            SetSpeed(float _speed) noexcept;
};

SCE_END
