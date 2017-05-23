#include "stdafx.h"
#include "Camera.h"
#include "../../../Math/Vec2.h"
#include "../../../Timer/Timer.h"
SCE_USE

/////////////////////////////////////////////////////////////////////////////////////////
struct Camera::impl
{
    impl() noexcept
        : moveMode{ MoveType::FIX_TO_OBJECT }
        , attachedObj{}
        , trackingDistance{ 15.f, 7.5f }
    {
    }

    MoveType        moveMode;
    GameObjectRef   attachedObj;
    Vec2            trackingDistance;
};

/////////////////////////////////////////////////////////////////////////////////////////
Camera::Camera() noexcept
    : pimpl{ std::make_unique<impl>() }
{
}

/////////////////////////////////////////////////////////////////////////////////////////
Camera::~Camera()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
void Camera::Init()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
void Camera::Release()
{
    pimpl->attachedObj.reset();
}

/////////////////////////////////////////////////////////////////////////////////////////
void Camera::Update(float _dt)
{
    MoveToAttachedObject(_dt);
    GameObject::Update(_dt);
}

/////////////////////////////////////////////////////////////////////////////////////////
void Camera::ChangeMoveTypeToNext()
{
    static Timer timer(0.5f);
    timer.Tick();
    timer.AccumDt();
    if (!timer.DurationCheck())
        return;

    size_t idx = static_cast<size_t>(pimpl->moveMode);
    if (++idx == static_cast<size_t>(MoveType::END))
    {
        idx = 0;
    }
    pimpl->moveMode = static_cast<MoveType>(idx);
}

/////////////////////////////////////////////////////////////////////////////////////////
void Camera::SetMoveType(MoveType _type)
{
    pimpl->moveMode = _type;
}

/////////////////////////////////////////////////////////////////////////////////////////
void Camera::AttachToObject(const GameObjectRef& _obj)
{
    pimpl->attachedObj = _obj;
}

/////////////////////////////////////////////////////////////////////////////////////////
void Camera::DetachObject()
{
    pimpl->attachedObj.reset();
}

/////////////////////////////////////////////////////////////////////////////////////////
void Camera::MoveToAttachedObject(float _dt)
{
    auto pObj = pimpl->attachedObj.lock();
    if (pObj == nullptr)
        return;

    switch (pimpl->moveMode)
    {
    case MoveType::FIX_TO_OBJECT:
        {
            SetPos(pObj->GetPos());
        }
        break;
    case MoveType::LINEAR:
        {
            Vec2 displacement = pObj->GetPos() - GetPos();
            if (std::abs(displacement.GetX()) > pimpl->trackingDistance.GetX() ||
                std::abs(displacement.GetY()) > pimpl->trackingDistance.GetY())
            {
                SetMovePower(displacement);
            }
        }
        break;
    case MoveType::EASE_IN_OUT:
        {
            Vec2 displacement = pObj->GetPos() - GetPos();
            if (std::abs(displacement.GetX()) > pimpl->trackingDistance.GetX() ||
                std::abs(displacement.GetY()) > pimpl->trackingDistance.GetY())
            {
                AddMovePower(displacement.Normalize() * _dt);
            }
        }
        break;
    }
}
