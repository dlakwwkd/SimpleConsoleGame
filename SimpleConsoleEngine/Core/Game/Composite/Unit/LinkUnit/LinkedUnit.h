#pragma once
#include "../Unit.h"
SCE_START
struct Shape;
class Vec2;

/////////////////////////////////////////////////////////////////////////////////////////
class LinkedUnit : public Unit
{
    DECLARE_PIMPL
    SPECIALFUNC_MOVE_SET(LinkedUnit, default)
    using UnitPtr = std::shared_ptr<Unit>;
public:
    LinkedUnit() noexcept;
    virtual ~LinkedUnit() override;

    virtual void    Init() override;
    virtual void    Release() override;
    virtual void    Update(float _dt) override;

    virtual bool    Hitted(int _damage) override;
    virtual void    Death() override;

    static void     AddLinkedUnit(
                        const UnitPtr& _parent,
                        const Vec2& _pos,
                        const Shape& _shape,
                        bool _isShared = true,
                        int _hp = 0);
};

SCE_END
