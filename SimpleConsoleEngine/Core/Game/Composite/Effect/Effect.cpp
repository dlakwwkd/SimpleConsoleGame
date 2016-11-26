#include "stdafx.h"
#include "Effect.h"
#include "../../../Console/Console.h"
#include "../../Component/RenderComponent/CmdRenderComponent.h"
SCE_START


Effect::Effect() noexcept
{
}

Effect::~Effect()
{
}


void Effect::Init()
{
    AddComponent<CmdRenderComponent>();
}

void Effect::Release()
{
}

void Effect::Update(float _dt)
{
    GameObject::Update(_dt);
}

SCE_END
