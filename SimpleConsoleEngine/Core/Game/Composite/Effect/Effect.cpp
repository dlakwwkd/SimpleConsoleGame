#include "stdafx.h"
#include "Effect.h"
#include "../../../Console/Console.h"
#include "../../Component/RenderComponent/CmdRenderComponent.h"
SCE_START


Effect::Effect() noexcept
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

SCE_END
