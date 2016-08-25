#include "stdafx.h"
#include "Dummy.h"
//----------------------------------------------------------------------------------------------------
#include "Core/Console/Console.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
SCE_USE


Dummy::Dummy()
{
    AddComponent<CmdRenderComponent>();
}


Dummy::~Dummy()
{
    Release();
}

void Dummy::Init()
{
}

void Dummy::Release()
{
}

void Dummy::Update(float dt)
{
}

void Dummy::Render()
{
    GameObject::Render();
}
