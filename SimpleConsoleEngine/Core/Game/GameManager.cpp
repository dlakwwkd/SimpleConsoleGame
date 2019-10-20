#include "stdafx.h"
#include "GameManager.h"
#include "GameManagerImpl.hpp"
#include "Section.h"
#include "Interface/IGame.h"
#include "Composite/Unit/Unit.h"
#include "Composite/Effect/Effect.h"
#include "Component/RenderComponent.h"
#include "Component/CollisionComponent.h"
#include "../Console/Color.hpp"
#include "../Console/Console.h"
#include "../Timer/Timer.h"
#include "../Math/Vec2.h"
#include "../Command/Command.h"
SCE_USE

LRESULT CALLBACK    WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);
LPCTSTR             lpszClass = TEXT("SimpleGame");
HINSTANCE           g_Inst = nullptr;
HWND                g_hWnd = nullptr;
std::atomic<bool>   g_waitForRenderToWindow = false;

/////////////////////////////////////////////////////////////////////////////////////////
GameManager::GameManager() noexcept
    : pimpl{ std::make_unique<impl>() }
    , scheduler{}
    , gameTimer{}
    , curGame{}
    , isRun{}
    , isPlay{}
{
}

/////////////////////////////////////////////////////////////////////////////////////////
GameManager::~GameManager()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::ReturnMain()
{
    isPlay = false;
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::Shutdown()
{
    isRun = isPlay = false;
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::AddRender(const RenderObjPtr& _obj, float _lifeTime)
{
    pimpl->renderList.push_back(_obj);
    if (_lifeTime < 0.f)
        return;

    CallFuncAfterM(_lifeTime, this, &GameManager::RemoveRender, _obj);
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::RemoveRender(const RenderObjPtr& _obj)
{
    pimpl->renderList.remove(_obj);
}

/////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::UnRegisterCollision(const CollisionObjPtr& _obj)
{
    auto unit = std::static_pointer_cast<Unit>(_obj);
    if (unit == nullptr)
        return;

    if (auto& collision = unit->GetCollision())
    {
        if (auto section = collision->GetSection())
        {
            section->UnRegisterCollision(unit);
        }
    }
    CallFuncAfterM(0.f, this, &GameManager::RemoveCollision, _obj);
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::RegisterBuiltSection(const SectionPtr& _section, const POINT& _pos)
{
    pimpl->sectionList.push_back(_section);
    pimpl->sectionMap.insert(std::make_pair(_pos, SectionRef(_section)));

    // 섹션 생성 과정을 눈으로 보기 위한 임시 코드
/*    for (int y = _pos.y - 10; y < _pos.y + 10; ++y)
    {
        for (int x = _pos.x - 10; x < _pos.x + 10; ++x)
        {
            auto temp = ObjectPool<Effect>::GetWithInit();
            if (temp == nullptr)
                continue;

            if (auto& render = temp->GetRender())
            {
                render->SetCoord(x * 2, y);
                render->SetShape(L'■');
                render->SetColor(Color::DARK_GREEN);
                render->SetBGColor(Color::DARK_GREEN);
                AddRender(temp, 0.5f);
            }
        }
    }*/
}

/////////////////////////////////////////////////////////////////////////////////////////
GameManager::SectionPtr GameManager::FindSection(const POINT& _pos) const
{
    auto iter = pimpl->sectionMap.find(_pos);
    if (iter == pimpl->sectionMap.end())
        return nullptr;

    return iter->second.lock();
}

/////////////////////////////////////////////////////////////////////////////////////////
GameManager::CameraPtr& GameManager::GetMainCamera()
{
    return pimpl->mainCamera;
}

/////////////////////////////////////////////////////////////////////////////////////////
GameManager::CommandPtr& GameManager::GetCommand()
{
    return pimpl->command;
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::CommandProc(float dt)
{
    auto& cmd = *pimpl->command;
    if (cmd.IsKeyPress<Command::ESC>())
    {
        Shutdown();
    }
    else if (cmd.IsKeyPress<Command::ENTER>())
    {
        ReturnMain();
    }
    else if (cmd.IsKeyPress<Command::F12>())
    {
        ChangeRenderMode();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::InitGame()
{
    Console::GetInstance().Init();
    scheduler = std::make_unique<Scheduler>();
    gameTimer = std::make_unique<Timer>();
    pimpl->mainCamera = std::make_unique<Camera>();
    pimpl->command = std::make_unique<Command>();
    if (scheduler
        && gameTimer
        && pimpl->mainCamera
        && pimpl->command)
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

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::ReleaseGame()
{
    isPlay = false;
    isRun = false;
    pimpl->command.reset();
    pimpl->mainCamera.reset();
    if (pimpl->windowThreadPtr)
    {
        PostMessage(g_hWnd, WM_DESTROY, 0, 0);
        pimpl->windowThreadPtr->detach();
        pimpl->windowThreadPtr.reset();
    }
    gameTimer.reset();
    scheduler.reset();
    Console::GetInstance().Release();
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::MainLoop()
{
    while (isRun)
    {
        if (!gameTimer
            || !curGame
            || !pimpl->mainCamera
            || !pimpl->command)
        {
            assert(false);
            return;
        }
        isPlay = true;
        gameTimer->Init();
        GameLoop();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::GameLoop()
{
    pimpl->rootSection = ObjectPool<Section>::Get(POINT{ 0, 0 }, 10);
    RegisterBuiltSection(pimpl->rootSection, { 0, 0 });

    pimpl->mainCamera->Init();
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
    pimpl->mainCamera->Release();

    pimpl->sectionMap.clear();
    pimpl->sectionList.clear();
    pimpl->renderList.clear();
    pimpl->collisionList.clear();
    pimpl->rootSection.reset();
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::UpdateProcess()
{
    float dt = FrameProgress();

    CommandProc(dt);
    curGame->Update(dt);
    for (auto& obj : pimpl->collisionList)
    {
        obj->Update(dt);
    }
    CollisionCheck(dt);

    pimpl->mainCamera->Update(dt);
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::RenderProcess()
{
    if (g_waitForRenderToWindow)
        return;

    static auto& console = Console::GetInstance();
    console.Clear();

    curGame->Render();
    for (auto& obj : pimpl->renderList)
    {
        obj->Render();
    }
    pimpl->PrintFrame();
    pimpl->SectionNumPrint();

    if (pimpl->renderType == RenderComponent::RenderType::CmdConsole)
    {
        console.SwapBuffer();
    }
    else
    {
        g_waitForRenderToWindow = true;
        RedrawWindow(g_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
float GameManager::FrameProgress()
{
    pimpl->frameCount++;
    gameTimer->Tick();
    return gameTimer->DeltaTime();
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::SetRenderLimit(size_t _limitFrame)
{
    pimpl->renderLimit = _limitFrame;
    gameTimer->SetDuration(1.0f / _limitFrame);
}

/////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::AddCollision(const CollisionObjPtr& _obj)
{
    pimpl->collisionList.push_back(_obj);
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::RemoveCollision(const CollisionObjPtr& _obj)
{
    pimpl->collisionList.remove(_obj);
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::CollisionCheck(float _dt)
{
    // 충돌 체크 주기
    static Timer timer(0.01f);
    timer.AccumDt(_dt);
    if (!timer.DurationCheck())
        return;

    for (auto& obj : pimpl->collisionList)
    {
        auto unit = std::static_pointer_cast<Unit>(obj);
        if (unit == nullptr)
            continue;

        auto& collision = unit->GetCollision();
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

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::ChangeRenderMode()
{
    static Timer timer(0.3f);
    timer.Tick();
    timer.AccumDt();
    if (!timer.DurationCheck())
        return;

    if (pimpl->renderType == RenderComponent::RenderType::CmdConsole)
    {
        pimpl->renderType = RenderComponent::RenderType::Window;
        Console::GetInstance().Clear();
        Console::GetInstance().SwapBuffer();

        if (!pimpl->windowThreadPtr)
        {
            pimpl->windowThreadPtr = std::make_unique<std::thread>(&GameManager::WindowMain);
        }
        ShowWindow(GetConsoleWindow(), 0);
    }
    else
    {
        pimpl->renderType = RenderComponent::RenderType::CmdConsole;

        if (pimpl->windowThreadPtr)
        {
            PostMessage(g_hWnd, WM_DESTROY, 0, 0);
            pimpl->windowThreadPtr->detach();
            pimpl->windowThreadPtr.reset();
        }
        ShowWindow(GetConsoleWindow(), 1);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void GameManager::WindowMain()
{
    g_Inst = GetModuleHandle(NULL);

    WNDCLASS WndClass;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hInstance = g_Inst;
    WndClass.lpszClassName = lpszClass;
    WndClass.lpszMenuName = NULL;
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = WndProc;
    RegisterClass(&WndClass);

    RECT rect;
    GetWindowRect(GetConsoleWindow(), &rect);
    g_hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL, (HMENU)NULL, g_Inst, NULL);

    ShowWindow(g_hWnd, SW_SHOW);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
    switch (iMessage)
    {
    case WM_PAINT:
        {
            if (g_waitForRenderToWindow)
            {
                Console::GetInstance().RenderToWindow(hWnd);
                g_waitForRenderToWindow = false;
            }
        }
        break;
    case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
        break;
    default:
        return DefWindowProc(hWnd, iMessage, wParam, IParam);
    }
    return 0;
}
