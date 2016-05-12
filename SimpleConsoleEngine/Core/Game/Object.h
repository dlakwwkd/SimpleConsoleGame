﻿#pragma once
#include "../Console/Coord.hpp"
#include "../Console/Shape.hpp"
SCE_START


class SCE_API Object
{
    SPECIALFUNC_SET(Object, default)
public:
    Object()
    :   m_Coord{ 0,0 },
        m_IsShow(true)
    {
    }
    virtual ~Object()               = default;
    virtual void Init()             = 0;
    virtual void Release()          = 0;
    virtual void Update(float dt)   = 0;
    virtual void Render() { if (m_IsShow) m_Shape.Render(m_Coord); }
    
    inline void     SetCoord(const Coord& coord) noexcept { m_Coord = coord; }
    inline void     SetShape(const Shape& shape) noexcept { m_Shape = shape; }
    inline Coord    GetCoord() const noexcept { return m_Coord; }
    inline Shape    GetShape() const noexcept { return m_Shape; }

    inline void     SetShow(bool isShow) noexcept { m_IsShow = isShow; }
    inline bool     IsShow() const noexcept { return m_IsShow; }

protected:
    Coord   m_Coord;
    Shape   m_Shape;
    bool    m_IsShow;
};

SCE_END


