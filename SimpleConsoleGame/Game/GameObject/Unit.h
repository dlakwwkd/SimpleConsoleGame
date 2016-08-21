#pragma once
#include "SimpleConsoleEngine/Core/Game/GameObject.h"
#include "SimpleConsoleEngine/Core/Math/Vec2.h"
#include "SimpleConsoleEngine/Core/Console/Console.h"


class Unit : public SCE::GameObject
{
    SPECIALFUNC_SET(Unit, default)
public:
    Unit() noexcept;
    ~Unit() override;

    void Init()             override;
    void Release()          override;
    void Update(float dt)   override;
    void Render()           override;

    void SetSpeed(float speed) noexcept { m_Speed = speed; }
    void AddMovePower(const SCE::Vec2& addPower) noexcept { m_MovePower += addPower; }
    void MovePowerFixInLimit() noexcept
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
    __forceinline void PosFixInScreanBoundary() noexcept
    {
        static auto& console = SCE::Console::GetInstance();
        SCE::Vec2 bound(SCE::Coord::ConvertToVec2(console.GetScreenSize()));

        if (m_Pos.GetX() < 0.0f)
        {
            m_Pos.SetX(0.0f);
            m_MovePower.SetX(0.0f);
        }
        else if (m_Pos.GetX() > bound.GetX())
        {
            m_Pos.SetX(bound.GetX());
            m_MovePower.SetX(0.0f);
        }

        if (m_Pos.GetY() < 0.0f)
        {
            m_Pos.SetY(0.0f);
            m_MovePower.SetY(0.0f);
        }
        else if (m_Pos.GetY() > bound.GetY())
        {
            m_Pos.SetY(bound.GetY());
            m_MovePower.SetY(0.0f);
        }
    }

protected:
    SCE::Vec2   m_Pos;
    SCE::Vec2   m_MovePower;        // 현재의 이동방향과 속도축적값(벡터값)
    float       m_MovePowerLimit;   // zero에서 최대속도까지 도달하는데 걸리는 시간(초)
    float       m_MovePowerFrict;   // 마찰계수(1.0f이면, 최대속도에서 정지까지 1초 걸림, 2.0f면 0.5초 걸림)
    float       m_Speed;            // 최대속도에 도달시 초당 이동 칸수
};
