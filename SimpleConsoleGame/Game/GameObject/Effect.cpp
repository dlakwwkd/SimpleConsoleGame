﻿#include "stdafx.h"
#include "Effect.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
SCE_USE


Effect::Effect()
{
    AddComponent<CmdRenderComponent>();
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
