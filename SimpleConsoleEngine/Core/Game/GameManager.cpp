﻿#include "stdafx.h"
#include "GameManager.h"
#include "Section.h"
#include "Interface/IGame.h"
#include "Composite/Unit/Unit.h"
#include "Composite/Effect/Dummy.h"
#include "Component/RenderComponent/CmdRenderComponent.h"
#include "Component/CollisionComponent/CollisionComponent.h"
#include "../Timer/Timer.h"
#include "../Console/Console.h"
SCE_START


struct GameManager::impl
{
    impl() noexcept
        : frameCount{}
        , renderCount{}
        , renderLimit{}
        , renderList{}
        , collisionList{}
        , sectionList{}
        , sectionMap{}
        , rootSection{}
    {
    }

    void                        PrintFrame();
    void                        SectionNumPrint() const;

    size_t                      frameCount;
    size_t                      renderCount;
    size_t                      renderLimit;
    SectionPtr                  rootSection;
    std::vector<SectionPtr>     sectionList;
    std::map<POINT, SectionRef> sectionMap;
    std::list<RenderObjPtr>		renderList;
    std::list<CollisionObjPtr>	collisionList;
};


GameManager::GameManager() noexcept
    : pimpl{ std::make_unique<impl>() }
    , scheduler{}
    , gameTimer{}
    , curGame{}
    , isRun{}
    , isPlay{}
{
}

GameManager::~GameManager()
{
}


void GameManager::ReturnMain()
{
    isPlay = false;
}

void GameManager::Shutdown()
{
    isRun = isPlay = false;
}


void GameManager::AddRender(const RenderObjPtr& _obj, float _lifeTime)
{
    pimpl->renderList.push_back(_obj);
    if (_lifeTime < 0.f)
        return;

    CallFuncAfterM(_lifeTime, this, &GameManager::RemoveRender, _obj);
}

void GameManager::RemoveRender(const RenderObjPtr& _obj)
{
    pimpl->renderList.remove(_obj);
}


void GameManager::RegisterCollision(const CollisionObjPtr& _obj)
{
    if (pimpl->rootSection == nullptr)
        return;

    auto unit = std::static_pointer_cast<Unit>(_obj);
    if (unit == nullptr)
        return;

    if (pimpl->rootSection->RegisterCollision(unit))
    {
        AddCollision(_obj);
    }
}

void GameManager::RegisterCollision(const CollisionObjPtr& _obj, const SectionPtr& _trySection)
{
    auto unit = std::static_pointer_cast<Unit>(_obj);
    if (unit == nullptr)
        return;

    if (_trySection != nullptr)
    {
        if (_trySection->RegisterCollision(unit))
        {
            AddCollision(_obj);
        }
    }
    else
    {
        RegisterCollision(_obj);
    }
}

void GameManager::UnRegisterCollision(const CollisionObjPtr& _obj)
{
    auto unit = std::static_pointer_cast<Unit>(_obj);
    if (unit == nullptr)
        return;

    if (auto collision = _obj->Get<CollisionComponent>())
    {
        if (auto section = collision->GetSection())
        {
            section->UnRegisterCollision(unit);
        }
    }
    CallFuncAfterM(0.f, this, &GameManager::RemoveCollision, _obj);
}


void GameManager::RegisterBuiltSection(const SectionPtr& _section, const POINT& _pos)
{
    pimpl->sectionList.push_back(_section);
    pimpl->sectionMap.insert(std::make_pair(_pos, SectionRef(_section)));

    // 섹션 생성 과정을 눈으로 보기 위한 임시 코드
    for (int y = _pos.y - 10; y < _pos.y + 10; ++y)
    {
        for (int x = _pos.x - 10; x < _pos.x + 10; ++x)
        {
            auto temp = ObjectPool<Dummy>::GetWithInit();
            auto render = temp->Get<CmdRenderComponent>();
            if (render != nullptr)
            {
                render->SetCoord(x * 2, y);
                render->SetShape(L'■');
                render->SetColor(Color::DARK_GREEN);
                render->SetBGColor(Color::DARK_GREEN);
                AddRender(temp, 0.5f);
            }
        }
    }
}

GameManager::SectionPtr GameManager::FindSection(const POINT& _pos) const
{
    auto iter = pimpl->sectionMap.find(_pos);
    if (iter == pimpl->sectionMap.end())
        return nullptr;

    return iter->second.lock();
}


void GameManager::InitGame()
{
    Console::GetInstance().Init();
    scheduler = std::make_unique<Scheduler>();
    gameTimer = std::make_unique<Timer>();
    if (scheduler && gameTimer)
    {
        isRun = true;
    }
    else
    {
        isRun = false;
    }
    isPlay = false;
    pimpl->frameCount = 0;
    pimpl->renderCount = 0;
    pimpl->renderLimit = 0;
}

void GameManager::ReleaseGame()
{
    isPlay = false;
    isRun = false;
    gameTimer.reset();
    scheduler.reset();
    Console::GetInstance().Release();
}

void GameManager::MainLoop()
{
    while (isRun)
    {
        if (!gameTimer || !curGame)
        {
            assert(false);
            return;
        }
        isPlay = true;
        gameTimer->Init();
        GameLoop();
    }
}

void GameManager::GameLoop()
{
    pimpl->rootSection = ObjectPool<Section>::Get(POINT{ 0, 0 }, 10);
    RegisterBuiltSection(pimpl->rootSection, { 0, 0 });

    curGame->Init();
    SetRenderLimit(60);
    while (isPlay)
    {
        scheduler->DoTask();
        UpdateProcess();
        if (RenderLimitCheck())
        {
            RenderProcess();
        }
    }
    scheduler->Release();
    curGame->Release();

    pimpl->sectionMap.clear();
    pimpl->sectionList.clear();
    pimpl->renderList.clear();
    pimpl->collisionList.clear();
    pimpl->rootSection.reset();
}


void GameManager::UpdateProcess()
{
    float dt = FrameProgress();

    curGame->Update(dt);
    for (auto& obj : pimpl->collisionList)
    {
        obj->Update(dt);
    }
    CollisionCheck(dt);
}

void GameManager::RenderProcess()
{
    static auto& console = Console::GetInstance();
    console.Clear();

    curGame->Render();
    for (auto& obj : pimpl->renderList)
    {
        obj->Render();
    }
    pimpl->PrintFrame();
    pimpl->SectionNumPrint();

    console.SwapBuffer();
}


float GameManager::FrameProgress()
{
    pimpl->frameCount++;
    gameTimer->Tick();
    return gameTimer->DeltaTime();
}

void GameManager::SetRenderLimit(size_t _limitFrame)
{
    pimpl->renderLimit = _limitFrame;
    gameTimer->SetDuration(1.0f / _limitFrame);
}

bool GameManager::RenderLimitCheck()
{
    gameTimer->AccumDt();
    if (gameTimer->DurationCheck())
    {
        pimpl->renderCount++;
        return true;
    }
    return false;
}


void GameManager::AddCollision(const CollisionObjPtr& _obj)
{
    pimpl->collisionList.push_back(_obj);
}

void GameManager::RemoveCollision(const CollisionObjPtr& _obj)
{
    pimpl->collisionList.remove(_obj);
}


void GameManager::CollisionCheck(float _dt)
{
    // 충돌 체크 주기
    static Timer timer(0.01f);
    timer.AccumDt(_dt);
    if (!timer.DurationCheck())
        return;

    for (auto& obj : pimpl->collisionList)
    {
        auto collision = obj->Get<CollisionComponent>();
        if (!collision || collision->IsDeath())
        {
            UnRegisterCollision(obj);
        }
        else if (auto section = collision->GetSection())
        {
            section->SyncCollision(std::static_pointer_cast<Unit>(obj));
        }
    }
    for (auto& section : pimpl->sectionList)
    {
        section->CollisionCheck();
    }
}


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
        << L"RenderFrame: " << renderRate << L"/" << renderLimit << L"\t"
        << L"DrawCall: " << console.GetDrawCallNum();
    console.SetColor(Color::WHITE);
    console.PrintText(Coord(0, console.GetScreenHeight() + 1), oss.str().c_str());
}

void GameManager::impl::SectionNumPrint() const
{
    static auto& console = Console::GetInstance();
    std::wostringstream oss;
    oss << L"SectionNum: " << sectionList.size();
    size_t posX = console.GetScreenWidth() - oss.str().length();
    size_t posY = console.GetScreenHeight() + 1;
    console.SetColor(Color::WHITE);
    console.PrintText(Coord(posX, posY), oss.str().c_str());
}

SCE_END
