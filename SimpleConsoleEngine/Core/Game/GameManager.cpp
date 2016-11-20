#include "stdafx.h"
#include "GameManager.h"
#include "Section.h"
#include "Interface/IGameBase.h"
#include "Composite/GameObject.h"
#include "Composite/Effect/Dummy.h"
#include "Component/RenderComponent/CmdRenderComponent.h"
#include "Component/CollisionComponent/CollisionComponent.h"
#include "../Timer/Timer.h"
#include "../Console/Console.h"
SCE_START


GameManager::GameManager() noexcept
    : m_IsRun(false)
    , m_IsPlay(false)
    , m_FrameCount(0)
    , m_RenderCount(0)
    , m_RenderLimit(0)
{
}

GameManager::~GameManager()
{
}


void GameManager::ReturnMain()
{
    m_IsPlay = false;
}

void GameManager::Shutdown()
{
    m_IsRun = m_IsPlay = false;
}


void GameManager::AddRender(const RenderPtr& obj, float lifeTime)
{
    m_RenderList.push_back(obj);
    if (lifeTime < 0.f)
        return;

    CallFuncAfterM(lifeTime, this, &GameManager::RemoveRender, obj);
}

void GameManager::RemoveRender(const RenderPtr& obj)
{
    m_RenderList.remove(obj);
}


void GameManager::RegisterCollision(const CollisionPtr& obj)
{
    if (m_RootSection == nullptr)
        return;

    if (m_RootSection->RegisterCollision(obj))
    {
        AddCollision(obj);
    }
}

void GameManager::RegisterCollision(const CollisionPtr& obj, const SectionPtr& trySection)
{
    if (trySection != nullptr)
    {
        if (trySection->RegisterCollision(obj))
        {
            AddCollision(obj);
        }
    }
    else
    {
        RegisterCollision(obj);
    }
}

void GameManager::UnRegisterCollision(const CollisionPtr& obj)
{
    if (obj == nullptr)
        return;

    if (auto section = obj->GetSection())
    {
        section->UnRegisterCollision(obj);
    }
    CallFuncAfterM(0.f, this, &GameManager::RemoveCollision, obj);
}


void GameManager::RegisterBuiltSection(const SectionPtr& section, const POINT& pos)
{
    m_SectionList.push_back(section);
    m_SectionMap.insert(std::make_pair(pos, SectionRef(section)));

    // 섹션 생성 과정을 눈으로 보기 위한 임시 코드
    for (int y = pos.y - 10; y < pos.y + 10; ++y)
    {
        for (int x = pos.x - 10; x < pos.x + 10; ++x)
        {
            auto temp = ObjectPool<Dummy>::GetWithInit();
            auto render = temp->GetComponent<CmdRenderComponent>();
            if (render != nullptr)
            {
                render->SetCoord(x * 2, y);
                render->SetShape(L'■', Color::DARK_GREEN, Color::DARK_GREEN);
                AddRender(temp, 0.5f);
            }
        }
    }
}

GameManager::SectionPtr GameManager::FindSection(const POINT& pos) const
{
    auto iter = m_SectionMap.find(pos);
    if (iter == m_SectionMap.end())
        return nullptr;

    return iter->second.lock();
}


void GameManager::InitGame()
{
    Console::GetInstance().Init();
    m_Scheduler = std::make_unique<Scheduler>();
    m_Timer = std::make_unique<Timer>();
    if (m_Scheduler && m_Timer)
    {
        m_IsRun = true;
    }
    else
    {
        m_IsRun = false;
    }
    m_IsPlay = false;
    m_FrameCount = 0;
    m_RenderCount = 0;
    m_RenderLimit = 0;
}

void GameManager::ReleaseGame()
{
    m_IsPlay = false;
    m_IsRun = false;
    m_Timer.reset();
    m_Scheduler.reset();
    Console::GetInstance().Release();
}

void GameManager::MainLoop()
{
    while (m_IsRun)
    {
        if (!m_Timer || !m_Game)
        {
            assert(false);
            return;
        }
        m_IsPlay = true;
        m_Timer->Init();
        GameLoop();
    }
}

void GameManager::GameLoop()
{
    m_RootSection = ObjectPool<Section>::Get(POINT{ 0, 0 }, 10);
    RegisterBuiltSection(m_RootSection, { 0, 0 });

    m_Game->Init();
    SetRenderLimit(60);
    while (m_IsPlay)
    {
        m_Scheduler->DoTask();
        UpdateProcess();
        if (RenderLimitCheck())
        {
            RenderProcess();
        }
    }
    m_Scheduler->Release();
    m_Game->Release();

    m_SectionMap.clear();
    m_SectionList.clear();
    m_RenderList.clear();
    m_CollisionList.clear();
    m_RootSection.reset();
}


void GameManager::UpdateProcess()
{
    float dt = FrameProgress();

    m_Game->Update(dt);
    for (auto& obj : m_CollisionList)
    {
        obj->Update(dt);
    }
    CollisionCheck(dt);
}

void GameManager::RenderProcess()
{
    static auto& console = Console::GetInstance();
    console.Clear();

    m_Game->Render();
    for (auto& obj : m_RenderList)
    {
        obj->Render();
    }
    PrintFrame();
    SectionNumPrint();

    console.SwapBuffer();
}


float GameManager::FrameProgress()
{
    ++m_FrameCount;
    m_Timer->Tick();
    return m_Timer->DeltaTime();
}

void GameManager::SetRenderLimit(size_t limitFrame)
{
    m_RenderLimit = limitFrame;
    m_Timer->SetDuration(1.0f / limitFrame);
}

bool GameManager::RenderLimitCheck()
{
    m_Timer->AccumDt();
    if (m_Timer->DurationCheck())
    {
        ++m_RenderCount;
        return true;
    }
    return false;
}

void GameManager::PrintFrame()
{
    static auto& console = Console::GetInstance();
    static size_t frameRate = 0;
    static size_t renderRate = 0;
    static Timer timer(1.f);
    timer.Tick();
    timer.AccumDt();
    if (timer.DurationCheck())
    {
        frameRate = m_FrameCount;
        renderRate = m_RenderCount;
        m_FrameCount = 0;
        m_RenderCount = 0;
    }
    std::wostringstream oss;
    oss << L"UpdateFrame: " << frameRate << L"\t"
        << L"RenderFrame: " << renderRate << L"/" << m_RenderLimit << L"\t"
        << L"DrawCall: " << console.GetDrawCallNum();
    console.SetColor(Color::WHITE);
    console.PrintText(Coord(0, console.GetScreenHeight() + 1), oss.str().c_str());
}


void GameManager::AddCollision(const CollisionPtr& obj)
{
    m_CollisionList.push_back(obj);
}

void GameManager::RemoveCollision(const CollisionPtr& obj)
{
    m_CollisionList.remove(obj);
}


void GameManager::CollisionCheck(float dt)
{
    // 충돌 체크 주기
    static Timer timer(0.01f);
    timer.AccumDt(dt);
    if (!timer.DurationCheck())
        return;

    for (auto& obj : m_CollisionList)
    {
        if (obj->IsDeath())
        {
            UnRegisterCollision(obj);
        }
        else if (auto section = obj->GetSection())
        {
            section->SyncCollision(obj);
        }
    }
    for (auto& section : m_SectionList)
    {
        section->CollisionCheck();
    }
}

void GameManager::SectionNumPrint() const
{
    static auto& console = Console::GetInstance();
    std::wostringstream oss;
    oss << L"SectionNum: " << m_SectionList.size();
    size_t posX = console.GetScreenWidth() - oss.str().length();
    size_t posY = console.GetScreenHeight() + 1;
    console.SetColor(Color::WHITE);
    console.PrintText(Coord(posX, posY), oss.str().c_str());
}

SCE_END
