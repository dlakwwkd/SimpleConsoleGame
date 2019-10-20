#include "../../Console/Console.h"
#include "../../Console/Coord.h"
#include "../../Math/Vec2.h"
#include "Effect/Effect.h"
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
struct GameObject::impl
{
    impl() noexcept
        : pos{}
        , dir{ Vec2::UP }
        , movePower{}
        , movePowerLimit{ 1.0f }
        , movePowerFrict{ 1.5f }
        , speed{ 100.0f }
    {
    }

    void    MovePowerFixInLimit() noexcept;
    void    PosFixInScreanBoundary() noexcept;
    void    DirectionShow() const noexcept;

    Vec2    pos;
    Vec2    dir;            // 이동방향(벡터값)
    Vec2    movePower;      // 현재의 속도축적값(벡터값)
    float   movePowerLimit; // zero에서 최대속도까지 도달하는데 걸리는 시간(초)
    float   movePowerFrict; // 마찰계수(1.0f이면, 최대속도에서 정지까지 1초 걸림, 2.0f면 0.5초 걸림)
    float   speed;          // 최대속도에 도달시 초당 이동 칸수
};

/////////////////////////////////////////////////////////////////////////////////////////
void GameObject::impl::MovePowerFixInLimit() noexcept
{
    float length = movePower.Length();
    if (length < 0.0001f)
    {
        movePower.SetZero();
    }
    else if (length > movePowerLimit)
    {
        movePower *= movePowerLimit / length;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameObject::impl::PosFixInScreanBoundary() noexcept
{
    static auto& console = Console::GetInstance();
    Vec2 bound = console.GetScreenSize().ConvertToVec2();

    if (pos.GetX() < 0.0f)
    {
        pos.SetX(0.0f);
        movePower.SetX(0.0f);
    }
    else if (pos.GetX() > bound.GetX())
    {
        pos.SetX(bound.GetX());
        movePower.SetX(0.0f);
    }

    if (pos.GetY() < 0.0f)
    {
        pos.SetY(0.0f);
        movePower.SetY(0.0f);
    }
    else if (pos.GetY() > bound.GetY())
    {
        pos.SetY(bound.GetY());
        movePower.SetY(0.0f);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameObject::impl::DirectionShow() const noexcept
{
    if (movePowerFrict < 0.01f || movePowerLimit < 0.01f)
        return;

    float power = movePower.Length();
    Vec2 dir = movePower / power;
    Vec2 temp = pos;

    auto dummy = ObjectPool<Effect>::GetWithInit();
    auto length = static_cast<size_t>(power * speed / movePowerFrict / movePowerLimit);
    for (size_t i = 0; i < length; ++i)
    {
        temp += dir;
        dummy->SetPos(temp);
        dummy->Render();
    }
}

SCE_END
