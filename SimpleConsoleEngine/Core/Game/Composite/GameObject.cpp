#include "stdafx.h"
#include "GameObject.h"
#include "../Component/IRenderComponent.h"
SCE_START


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}


GameObject::GameObject(const GameObject& source)
:   CompositeBase(source)
{
}

GameObject::GameObject(GameObject&& source)
:   CompositeBase(std::move(source))
{
}

GameObject& GameObject::operator=(const GameObject& source)
{
    Release();
    CompositeBase::operator=(source);
    return *this;
}

GameObject& GameObject::operator=(GameObject&& source)
{
    Release();
    CompositeBase::operator=(std::move(source));
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
