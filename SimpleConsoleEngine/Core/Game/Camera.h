#pragma once
SCE_START
class Vec2;

/////////////////////////////////////////////////////////////////////////////////////////
class Camera
{
    DECLARE_PIMPL
    SPECIALFUNC_SET(Camera, delete)
public:
    Camera() noexcept;
    ~Camera();

    const Vec2&     GetPos() const;
    void            SetPos(const Vec2& _pos);
    void            MoveTo(const Vec2& _pos);
};

SCE_END
