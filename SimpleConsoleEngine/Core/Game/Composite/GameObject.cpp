#include "stdafx.h"
#include "GameObject.h"
#include "../../Console/Console.h"
#include "../../Math/Vec2.h"
#include "Effect/Dummy.h"
SCE_START


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


GameObject::GameObject() noexcept
    : pimpl{ std::make_unique<impl>() }
{
}

GameObject::~GameObject()
{
}


void GameObject::Init()
{
}

void GameObject::Release()
{
}

void GameObject::Update(float _dt)
{
    pimpl->MovePowerFixInLimit();
    pimpl->pos += pimpl->movePower * (pimpl->speed / pimpl->movePowerLimit * _dt);  // 현재 속도만큼 이동
    pimpl->movePower -= pimpl->movePower * (pimpl->movePowerFrict * _dt);             // 마찰로 인한 속력 저하
    pimpl->PosFixInScreanBoundary();
}


Vec2 GameObject::GetPos() const noexcept
{
    return pimpl->pos;
}

Vec2 GameObject::GetDirection() const noexcept
{
    return pimpl->dir;
}

float GameObject::GetMovePowerLimit() const noexcept
{
    return pimpl->movePowerLimit;
}

float GameObject::GetMovePowerFrict() const noexcept
{
    return pimpl->movePowerFrict;
}

float GameObject::GetSpeed() const noexcept
{
    return pimpl->speed;
}


void GameObject::SetPos(const Vec2& _pos) noexcept
{
    pimpl->pos = _pos;
}

void GameObject::SetDirection(const Vec2& _dir) noexcept
{
    pimpl->dir = _dir;
}

void GameObject::SetMovePower(const Vec2& _power) noexcept
{
    pimpl->movePower = _power;
}

void GameObject::AddMovePower(const Vec2& _addPower) noexcept
{
    pimpl->movePower += _addPower;
    pimpl->dir = pimpl->movePower.GetNormalized();
}

void GameObject::SetMovePowerLimit(float _ratio) noexcept
{
    pimpl->movePowerLimit = _ratio;
}

void GameObject::SetMovePowerFrict(float _ratio) noexcept
{
    pimpl->movePowerFrict = _ratio;
}

void GameObject::SetSpeed(float _speed) noexcept
{
    pimpl->speed = _speed;
}


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

void GameObject::impl::PosFixInScreanBoundary() noexcept
{
    static auto& console = Console::GetInstance();
    Vec2 bound(Coord::ConvertToVec2(console.GetScreenSize()));

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

void GameObject::impl::DirectionShow() const noexcept
{
    if (movePowerFrict < 0.01f || movePowerLimit < 0.01f)
        return;

    float power = movePower.Length();
    Vec2 dir = movePower / power;
    Vec2 temp = pos;

    auto dummy = ObjectPool<Dummy>::GetWithInit();
    auto length = static_cast<size_t>(power * speed / movePowerFrict / movePowerLimit);
    for (size_t i = 0; i < length; ++i)
    {
        temp += dir;
        dummy->SetPos(temp);
        dummy->Render();
    }
}

SCE_END
