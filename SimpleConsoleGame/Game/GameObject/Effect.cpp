#include "stdafx.h"
#include "Effect.h"
//----------------------------------------------------------------------------------------------------
#include "Core/Console/Console.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
SCE_USE


Effect::Effect()
{
    AddComponent<CmdRenderComponent>();
}


Effect::~Effect()
{
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
