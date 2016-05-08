#pragma once
#include "../../Util/Macros.h"
#include "../../Util/AssertPack.h"
SCE_START


struct SCE_API Coord
{
    short m_X;
    short m_Y;

    Coord() : m_X(0), m_Y(0) {}
    template<typename T> Coord(T x, T y)
    :   m_X(Safe::IntegralCast<decltype(m_X)>(x)),
        m_Y(Safe::IntegralCast<decltype(m_Y)>(y))
    {
    }
};

SCE_END
