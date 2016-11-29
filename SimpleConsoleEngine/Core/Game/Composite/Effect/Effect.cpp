#include "stdafx.h"
#include "Effect.h"
#include "../../Component/RenderComponent/CmdRenderComponent.h"
SCE_START


struct Effect::impl
{
    impl() noexcept
        : render{}
    {
    }

    RenderRef render;
};


Effect::Effect() noexcept
    : pimpl{ std::make_unique<impl>() }
{
}

Effect::~Effect()
{
}


void Effect::Init()
{
    if (AddComponent<CmdRenderComponent>())
    {
        pimpl->render = GetComponent<CmdRenderComponent>();
    }
}

void Effect::Release()
{
}

void Effect::Update(float _dt)
{
    GameObject::Update(_dt);
}


IRenderObject::RenderPtr Effect::GetRender()
{
    return pimpl->render.lock();
}

void Effect::Render()
{
    auto render = pimpl->render.lock();
    if (render != nullptr)
    {
        render->Render();
    }
}

SCE_END
