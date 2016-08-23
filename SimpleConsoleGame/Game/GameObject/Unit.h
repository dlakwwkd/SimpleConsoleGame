#pragma once
#include "SimpleConsoleEngine/Core/Game/GameObject.h"
#include "SimpleConsoleEngine/Core/Math/Vec2.h"


class Unit : public SCE::GameObject
{
    SPECIALFUNC_SET(Unit, default)
public:
    Unit() noexcept;
    virtual ~Unit() override;

    virtual void    Init()             override;
    virtual void    Release()          override;
    virtual void    Update(float dt)   override;
    virtual void    Render()           override;

    inline void     SetSpeed(float speed) noexcept;
    inline void     AddMovePower(const SCE::Vec2& addPower) noexcept;

private:
    void            MovePowerFixInLimit() noexcept;
    void            PosFixInScreanBoundary() noexcept;
    void            DirectionShow() const;

protected:
    SCE::Vec2       m_Pos;
    SCE::Vec2       m_MovePower;        // 현재의 이동방향과 속도축적값(벡터값)
    float           m_MovePowerLimit;   // zero에서 최대속도까지 도달하는데 걸리는 시간(초)
    float           m_MovePowerFrict;   // 마찰계수(1.0f이면, 최대속도에서 정지까지 1초 걸림, 2.0f면 0.5초 걸림)
    float           m_Speed;            // 최대속도에 도달시 초당 이동 칸수
};

#include "Unit.inl"
