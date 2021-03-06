﻿#include "../Console/Console.h"
#include "../Console/Coord.h"
#include "../Timer/Timer.h"
#include "../Command/Command.h"
#include "Composite/Camera/Camera.h"
#include "Component/RenderComponent.h"
SCE_START

/////////////////////////////////////////////////////////////////////////////////////////
struct GameManager::impl
{
    impl() noexcept
        : frameCount{}
        , renderCount{}
        , renderLimit{}
        , rootSection{}
        , sectionList{}
        , sectionMap{}
        , renderList{}
        , collisionList{}
        , mainCamera{}
        , command{}
        , renderType{ RenderComponent::RenderType::CmdConsole }
        , windowThreadPtr{}
    {
    }

    void                            PrintFrame();
    void                            SectionNumPrint() const;

    size_t                          frameCount;
    size_t                          renderCount;
    size_t                          renderLimit;
    SectionPtr                      rootSection;
    std::vector<SectionPtr>         sectionList;
    std::map<POINT, SectionRef>     sectionMap;
    std::list<RenderObjPtr>         renderList;
    std::list<CollisionObjPtr>      collisionList;
    CameraPtr                       mainCamera;
    CommandPtr                      command;
    RenderComponent::RenderType     renderType;
    std::unique_ptr<std::thread>    windowThreadPtr;
};

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::impl::PrintFrame()
{
    static auto& console = Console::GetInstance();
    static size_t frameRate = 0;
    static size_t renderRate = 0;
    static Timer timer(1.f);
    timer.Tick();
    timer.AccumDt();
    if (timer.DurationCheck())
    {
        frameRate = frameCount;
        renderRate = renderCount;
        frameCount = 0;
        renderCount = 0;
    }
    std::wostringstream oss;
    oss << L"UpdateFrame: " << frameRate << L"\t"
        << L"RenderFrame: " << renderRate << L"/" << renderLimit << L"\t";
    console.PrintText(Coord(0, console.GetScreenHeight() + 1), oss.str());
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::impl::SectionNumPrint() const
{
    static auto& console = Console::GetInstance();
    std::wostringstream oss;
    oss << L"SectionNum: " << sectionList.size();
    size_t posX = console.GetScreenWidth() - oss.str().length();
    size_t posY = console.GetScreenHeight() + 1;
    console.PrintText(Coord(posX, posY), oss.str());
}

SCE_END
