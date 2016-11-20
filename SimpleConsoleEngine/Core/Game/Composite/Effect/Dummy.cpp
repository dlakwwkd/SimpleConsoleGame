#include "stdafx.h"
#include "Dummy.h"
#include "../../Component/RenderComponent/CmdRenderComponent.h"
#include "../../../Console/Console.h"
#include "../../../Math/Vec2.h"
SCE_START


Dummy::Dummy() noexcept
{
    if (AddComponent<CmdRenderComponent>())
    {
        auto render = GetComponent<CmdRenderComponent>();
        if (render == nullptr)
            return;

        render->SetShape(L'+', Color::DARK_BLUE);
    }
}

Dummy::~Dummy()
{
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
    auto render = GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    render->SetCoord(Coord(GetPos()));
    render->Render();
}

SCE_END
