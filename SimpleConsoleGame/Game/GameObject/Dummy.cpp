#include "stdafx.h"
#include "Dummy.h"
#include "SimpleConsoleEngine/Core/Game/Component/CmdRenderComponent.h"
SCE_USE


Dummy::Dummy() noexcept
{
    InsertComponent<CmdRenderComponent>();
    Init();
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
