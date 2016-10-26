#include "stdafx.h"
#include "Dummy.h"
//----------------------------------------------------------------------------------------------------
#include "Core/Console/Console.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
#include "Core/Math/Vec2.h"
SCE_USE


Dummy::Dummy()
{
    Init();
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

        render->SetShape(Shape(L'+', Color::DARK_BLUE));
    }
}

void Dummy::Release()
{
    RemoveComponent<CmdRenderComponent>();
}

void Dummy::Update(float dt)
{
}

void Dummy::Render()
{
    GameObject::Render();
}


void Dummy::SetPos(const Vec2& pos)
{
    auto render = GetComponent<CmdRenderComponent>();
    if (render == nullptr)
        return;

    render->SetCoord(Coord(pos));
}
