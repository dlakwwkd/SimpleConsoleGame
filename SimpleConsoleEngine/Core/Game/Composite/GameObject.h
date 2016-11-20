#pragma once
#include "CompositeBase.h"
#include "../Interface/IGameBase.h"
#include "../../Math/Vec2.h"
SCE_START


class GameObject
    : public IGameBase
    , public CompositeBase
{
    SPECIALFUNC_SET(GameObject, default)
public:
    GameObject() noexcept;
    virtual ~GameObject() override;

    virtual void    Init()             override;
    virtual void    Release()          override;
    virtual void    Update(float dt)   override;
    virtual void    Render()           override;

    Vec2            GetPos() const noexcept;
    Vec2            GetDirection() const noexcept;
    float           GetMovePowerLimit() const noexcept;
    float           GetMovePowerFrict() const noexcept;
    float           GetSpeed() const noexcept;

    void            SetPos(const Vec2& pos) noexcept;
    void            SetDirection(const Vec2& dir) noexcept;
    void            SetMovePower(const Vec2& power) noexcept;
    void            AddMovePower(const Vec2& addPower) noexcept;
    void            SetMovePowerLimit(float ratio) noexcept;
    void            SetMovePowerFrict(float ratio) noexcept;
    void            SetSpeed(float speed) noexcept;

private:
    void            MovePowerFixInLimit() noexcept;
    void            PosFixInScreanBoundary() noexcept;
    void            DirectionShow() const noexcept;

private:
    Vec2            m_Pos;
    Vec2            m_Direction;        // 이동방향(벡터값)
    Vec2            m_MovePower;        // 현재의 속도축적값(벡터값)
    float           m_MovePowerLimit;   // zero에서 최대속도까지 도달하는데 걸리는 시간(초)
    float           m_MovePowerFrict;   // 마찰계수(1.0f이면, 최대속도에서 정지까지 1초 걸림, 2.0f면 0.5초 걸림)
    float           m_Speed;            // 최대속도에 도달시 초당 이동 칸수
};

SCE_END
