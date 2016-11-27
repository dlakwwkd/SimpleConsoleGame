#include "stdafx.h"
#include "Dummy.h"
#include "../../Component/RenderComponent/CmdRenderComponent.h"
SCE_START


struct Dummy::impl
{
    impl() noexcept
        : render{}
    {
    }

    RenderRef render;
};


Dummy::Dummy() noexcept
    : pimpl{ std::make_unique<impl>() }
{
}

Dummy::~Dummy()
{
}


void Dummy::Init()
{
    if (AddComponent<CmdRenderComponent>())
    {
        auto pRender = GetComponent<CmdRenderComponent>();
        if (pRender == nullptr)
            return;

        pRender->SetShape(L'+');
        pRender->SetColor(Color::DARK_BLUE);
        pimpl->render = pRender;
    }
}

void Dummy::Release()
{
}

void Dummy::Update(float _dt)
{
    GameObject::Update(_dt);
}


IRenderObject::RenderPtr Dummy::GetRender()
{
    return pimpl->render.lock();
}

void Dummy::Render()
{
    auto render = IRenderObject::Get<CmdRenderComponent>();
    if (render != nullptr)
    {
        render->Render();
    }
}

SCE_END
