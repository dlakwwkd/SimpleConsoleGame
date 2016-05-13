#pragma once
#include "../../Util/Macros.h"
SCE_START


class SCE_API GameBase
{
public:
    GameBase() noexcept
    :   m_FrameRate(0),
        m_RenderRate(0),
        m_RenderCount(0),
        m_RenderLimit(0.0f)
    {
    }
    virtual ~GameBase()             = default;
    virtual void Init()             = 0;
    virtual void Release()          = 0;
    virtual void Update(float dt)   = 0;
    virtual void Render()           = 0;

    inline void SetRenderFrameLimit(size_t limitFrame)
    {
        m_RenderLimit = 1.0f / limitFrame;
    }
    inline bool RenderLimitCheck(float dt)
    {
        static float accumDt = 0;
        accumDt += dt;
        if (accumDt > m_RenderLimit)
        {
            ++m_RenderCount;
            accumDt = 0.0f;
            return true;
        }
        return false;
    }
    inline void FrameCalc(float dt)
    {
        static float accumDt = 0;
        static size_t count = 0;
        accumDt += dt;
        ++count;
        if (accumDt > 1.0f)
        {
            m_FrameRate = count;
            m_RenderRate = m_RenderCount;
            m_RenderCount = 0;
            accumDt = 0.0f;
            count = 0;
        }
    }

protected:
    size_t  m_FrameRate;
    size_t  m_RenderRate;
    size_t  m_RenderCount;
    float   m_RenderLimit;
};

SCE_END


