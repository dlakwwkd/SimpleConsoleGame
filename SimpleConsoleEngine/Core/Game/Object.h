#pragma once
#include "../Console/Coord.hpp"
#include "../Console/Shape.hpp"
SCE_START


class SCE_API Object
{
public:
    virtual ~Object()               = default;
    virtual void Init()             = 0;
    virtual void Release()          = 0;
    virtual void Update(float dt)   = 0;
    virtual void Render() const noexcept { m_Shape.Render(m_Pos); }
    
    inline void     SetPos(const Coord& pos) noexcept { m_Pos = pos; }
    inline void     SetShape(const Shape& shape) noexcept { m_Shape = shape; }
    inline Coord    GetPos() const noexcept { return m_Pos; }
    inline Shape    GetShape() const noexcept { return m_Shape; }

protected:
    Coord m_Pos;
    Shape m_Shape;
};

SCE_END


