#include "stdafx.h"
#include "GameObject.h"
#include "../../Console/Console.h"
#include "Effect/Dummy.h"
SCE_START


GameObject::GameObject() noexcept
    : m_Pos{ 0.0f, 0.0f }
    , m_Direction(Vec2::UP)
    , m_MovePower{ 0.0f, 0.0f }
    , m_MovePowerLimit(1.0f)
    , m_MovePowerFrict(1.5f)
    , m_Speed(100.0f)
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

void GameObject::Update(float dt)
{
    MovePowerFixInLimit();
    m_Pos += m_MovePower * (m_Speed / m_MovePowerLimit * dt);   // 현재 속도만큼 이동
    m_MovePower -= m_MovePower * (m_MovePowerFrict * dt);       // 마찰로 인한 속력 저하
    PosFixInScreanBoundary();
}

void GameObject::Render()
{
}


Vec2 GameObject::GetPos() const noexcept
{
    return m_Pos;
}

Vec2 GameObject::GetDirection() const noexcept
{
    return m_Direction;
}

float GameObject::GetMovePowerLimit() const noexcept
{
    return m_MovePowerLimit;
}

float GameObject::GetMovePowerFrict() const noexcept
{
    return m_MovePowerFrict;
}

float GameObject::GetSpeed() const noexcept
{
    return m_Speed;
}


void GameObject::SetPos(const Vec2& pos) noexcept
{
    m_Pos = pos;
}

void GameObject::SetDirection(const Vec2& dir) noexcept
{
    m_Direction = dir;
}

void GameObject::SetMovePower(const Vec2& power) noexcept
{
    m_MovePower = power;
}

void GameObject::AddMovePower(const Vec2& addPower) noexcept
{
    m_MovePower += addPower;
    m_Direction = m_MovePower.GetNormalized();
}

void GameObject::SetMovePowerLimit(float ratio) noexcept
{
    m_MovePowerLimit = ratio;
}

void GameObject::SetMovePowerFrict(float ratio) noexcept
{
    m_MovePowerFrict = ratio;
}

void GameObject::SetSpeed(float speed) noexcept
{
    m_Speed = speed;
}


void GameObject::MovePowerFixInLimit() noexcept
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

void GameObject::PosFixInScreanBoundary() noexcept
{
    static auto& console = Console::GetInstance();
    Vec2 bound(Coord::ConvertToVec2(console.GetScreenSize()));

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

void GameObject::DirectionShow() const noexcept
{
    if (m_MovePowerFrict < 0.01f || m_MovePowerLimit < 0.01f)
        return;

    float power = m_MovePower.Length();
    Vec2 dir = m_MovePower / power;
    Vec2 temp = m_Pos;

    static Dummy dummy;
    auto length = static_cast<size_t>(power * m_Speed / m_MovePowerFrict / m_MovePowerLimit);
    for (size_t i = 0; i < length; ++i)
    {
        temp += dir;
        dummy.SetPos(temp);
        dummy.Render();
    }
}

SCE_END
