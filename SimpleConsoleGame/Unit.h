#pragma once
#include "Core/Game/Object.h"
#include "Core/Game/Vec2.h"


class Unit : public SCE::Object
{
    SPECIALFUNC_SET(Unit, default)
public:
    Unit();
    ~Unit() override;

    void Init()             override;
    void Release()          override;
    void Update(float dt)   override;
    void Render()           override;

    void PosFixInScreanBoundary() noexcept;

    inline void SetSpeed(float speed) noexcept { m_Speed = speed; }
    inline void AddMovePower(const SCE::Vec2& addPower) noexcept { m_MovePower += addPower; }
    inline void MovePowerFixInLimit() noexcept
    {
        float length = m_MovePower.Length();
        if (length < 0.0001f)
        {
            m_MovePower.SetZero();
        }
        else if (length > m_MovePowerLimit)
        {
            m_MovePower *= m_MovePowerLimit / length;
        }
    }
    inline void SyncCoordFromPos() noexcept
    {
        m_Coord.m_X = static_cast<decltype(m_Coord.m_X)>(m_Pos.m_X * 2.0f);
        m_Coord.m_Y = static_cast<decltype(m_Coord.m_Y)>(m_Pos.m_Y);
    }

protected:
    SCE::Vec2   m_Pos;
    SCE::Vec2   m_MovePower;        // 현재의 이동방향과 속도축적값(벡터값)
    float       m_MovePowerLimit;   // zero에서 최대속도까지 도달하는데 걸리는 시간(초)
    float       m_MovePowerFrict;   // 마찰계수(1.0f이면, 최대속도에서 정지까지 1초 걸림, 2.0f면 0.5초 걸림)
    float       m_Speed;            // 최대속도에 도달시 초당 이동 칸수
};
