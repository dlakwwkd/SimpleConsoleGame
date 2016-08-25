#include "stdafx.h"
#include "GameObject.h"
#include "../Component/IRenderComponent.h"
SCE_START


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
    Release();
}


GameObject::GameObject(const GameObject& source)
{
}

GameObject::GameObject(GameObject&& source)
{
}

GameObject& GameObject::operator=(const GameObject& source)
{
    Release();
    return *this;
}

GameObject& GameObject::operator=(GameObject&& source)
{
    Release();
    return *this;
}


void GameObject::Init()
{
}

void GameObject::Release()
{
}

void GameObject::Update(float dt)
{
}

void GameObject::Render()
{
    auto render = GetComponent<IRenderComponent>();
    if (render != nullptr)
    {
        render->Render();
    }
}

SCE_END
