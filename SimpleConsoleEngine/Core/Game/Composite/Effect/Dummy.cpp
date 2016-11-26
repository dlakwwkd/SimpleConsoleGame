#include "stdafx.h"
#include "Dummy.h"
#include "../../Component/RenderComponent/CmdRenderComponent.h"
SCE_START


Dummy::Dummy() noexcept
{
}

Dummy::~Dummy()
{
}


void Dummy::Init()
{
    if (AddComponent<CmdRenderComponent>())
    {
        auto render = GetComponent<CmdRenderComponent>();
        if (render == nullptr)
            return;

        render->SetShape(L'+');
        render->SetColor(Color::DARK_BLUE);
    }
}

void Dummy::Release()
{
}

void Dummy::Update(float _dt)
{
    GameObject::Update(_dt);
}


RenderPtr Dummy::GetRender()
{
    return GetComponent<CmdRenderComponent>();
}

void Dummy::Render()
{
    auto render = GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    render->Render();
}

SCE_END
