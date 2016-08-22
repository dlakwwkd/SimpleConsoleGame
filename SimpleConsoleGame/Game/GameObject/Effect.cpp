#include "stdafx.h"
#include "Effect.h"
#include "SimpleConsoleEngine/Core/Game/Component/CmdRenderComponent.h"
SCE_USE


Effect::Effect() noexcept
{
    InsertComponent<CmdRenderComponent>();
    Init();
}


Effect::~Effect()
{
    Release();
}

void Effect::Init()
{
}

void Effect::Release()
{
}

void Effect::Update(float dt)
{
}

void Effect::Render()
{
    GameObject::Render();
}
