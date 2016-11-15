#include "stdafx.h"
#include "Game.h"
#include "Section.h"
//----------------------------------------------------------------------------------------------------
#include "Core/Timer/Timer.h"
#include "Core/Command/Command.h"
#include "Core/Console/Console.h"
#include "Core/Game/GameManager.h"
#include "Core/Game/Component/RenderComponent/CmdRenderComponent.h"
//----------------------------------------------------------------------------------------------------
#include "GameObject/Dummy.h"
#include "GameObject/Unit.h"
#include "GameObject/Unit/Hero.h"
#include "GameObject/Unit/Mob.h"
#include "GameObject/Unit/Missile.h"
SCE_USE


Game::Game()
{
}


Game::~Game()
{
}

void Game::Init()
{
    srand((unsigned int)time(NULL));

    m_Command = std::make_unique<Command>();
    m_RootSection = std::make_shared<Section>(POINT{ 0, 0 }, 10);
    m_Hero = std::make_shared<Hero>();
    m_Hero->SetDefaultAttack();
    RegisterBuiltSection(m_RootSection, { 0, 0 });
    RegisterCollision(m_Hero);

    GenerateMob(100);
    /*
    // 테스트 용 코드
    auto& gm = GameManager::GetInstance();
    gm.CallFuncAfterM(8.0f, &gm, &GameManager::ReturnMain);     // 게임 초기화
    gm.CallFuncAfterM(2.0f, this, &Game::CommandProc, 10.0f);   // 순간가속
    gm.CallFuncAfterS(4.0f,                                     // 순간정지
        [](auto&& moblist)
        {
            for (size_t i = 0; i < moblist.size(); ++i)
            {
                Sleep(50);
            }
        },
        m_MobList);
    gm.CallFuncAfterP(5.f, m_Hero, &Hero::Hitted, 100);         // 영웅 죽이기
    */
}

void Game::Release()
{
    m_SectionMap.clear();
    m_SectionList.clear();
    m_OnlyRenderList.clear();
    m_CollisionList.clear();
    m_MobList.clear();
    m_Hero.reset();
    m_RootSection.reset();
    m_Command.reset();
}

void Game::Update(float dt)
{
    CommandProc(dt);
    for (auto& mob : m_MobList)
    {
        mob->AI(dt);
    }
    for (auto& unit : m_CollisionList)
    {
        unit->Update(dt);
    }
    CollisionCheck(dt);
}

void Game::Render()
{
    for (auto& obj : m_OnlyRenderList)
    {
        obj->Render();
    }
    for (auto& unit : m_CollisionList)
    {
        unit->Render();
    }
    SectionNumPrint();
}



void Game::AddOnlyRender(const ObjectPtr& obj, float lifeTime)
{
    m_OnlyRenderList.push_back(obj);
    if (lifeTime < 0.f)
        return;

    GameManager::GetInstance().CallFuncAfterM(lifeTime, this, &Game::RemoveOnlyRender, obj);
}

void Game::RemoveOnlyRender(const ObjectPtr& obj)
{
    m_OnlyRenderList.remove(obj);
}



void Game::RegisterCollision(const UnitPtr& unit)
{
    if (m_RootSection == nullptr)
        return;

    if (m_RootSection->RegisterUnit(unit))
    {
        AddCollision(unit);
    }
}

void Game::RegisterCollision(const UnitPtr& unit, const SectionPtr& trySection)
{
    if (trySection != nullptr)
    {
        if (trySection->RegisterUnit(unit))
        {
            AddCollision(unit);
        }
    }
    else
    {
        RegisterCollision(unit);
    }
}

void Game::UnRegisterCollision(const UnitPtr& unit)
{
    if (unit == nullptr)
        return;

    if (auto section = unit->GetSection())
    {
        section->UnRegisterUnit(unit);
    }
    GameManager::GetInstance().CallFuncAfterM(0.f, this, &Game::RemoveCollision, unit);
}



void Game::RegisterBuiltSection(const SectionPtr& section, const POINT& pos)
{
    m_SectionList.push_back(section);
    m_SectionMap.insert(std::make_pair(pos, SectionRef(section)));

    // 섹션 생성 과정을 눈으로 보기 위한 임시 코드
    for (int y = pos.y - 10; y < pos.y + 10; ++y)
    {
        for (int x = pos.x - 10; x < pos.x + 10; ++x)
        {
            auto temp = std::make_shared<Dummy>();
            auto render = temp->GetComponent<CmdRenderComponent>();
            if (render != nullptr)
            {
                render->SetCoord(Coord(x * 2, y));
                render->SetShape(Shape(L'■', Color::DARK_GREEN, Color::DARK_GREEN));
                GameManager::GetInstance().GetGame<Game>().AddOnlyRender(temp, 0.5f);
            }
        }
    }
}

Game::SectionPtr Game::FindSection(const POINT& pos) const
{
    auto iter = m_SectionMap.find(pos);
    if (iter == m_SectionMap.end())
        return nullptr;

    return iter->second.lock();
}



void Game::GenerateMob(int num)
{
    int mobType = num / 5;
    m_MobList.reserve(num);
    for (int i = 0; i < num; ++i)
    {
        m_MobList.emplace_back(std::make_shared<Mob>());
        auto& mob = m_MobList[i];
        auto render = mob->GetComponent<CmdRenderComponent>();
        if (render == nullptr)
            continue;

        RegisterCollision(mob);
        if (i < mobType)
        {
            render->SetShape(Shape(L'☠', Color::GREY));
            mob->SetSpeed(120.0f);
            mob->SetAIRatio(0.5f);
            mob->SetDamage(2);
            mob->SetMaxHp(100);
            mob->InitHp();
        }
        else if (i < mobType * 2)
        {
            render->SetShape(Shape(L'☣', Color::RED));
            mob->SetSpeed(70.0f);
            mob->SetAIRatio(1.0f);
            mob->SetDamage(4);
            mob->SetMaxHp(100);
            mob->InitHp();
        }
        else if (i < mobType * 3)
        {
            render->SetShape(Shape(L'☯', Color::MAGENTA));
            mob->SetSpeed(30.0f);
            mob->SetAIRatio(1.5f);
            mob->SetDamage(6);
            mob->SetMaxHp(100);
            mob->InitHp();
        }
        else if (i < mobType * 4)
        {
            render->SetShape(Shape(L'♋', Color::CYAN));
            mob->SetSpeed(30.0f);
            mob->SetAIRatio(1.5f);
            mob->SetDamage(8);
            mob->SetMaxHp(100);
            mob->InitHp();
        }
        else
        {
            render->SetShape(Shape(L'★', Color::YELLOW));
            mob->SetSpeed(10.0f);
            mob->SetAIRatio(2.0f);
            mob->SetDamage(10);
            mob->SetMaxHp(100);
            mob->InitHp();
        }
    }
}



void Game::AddCollision(const UnitPtr& unit)
{
    m_CollisionList.push_back(unit);
}

void Game::RemoveCollision(const UnitPtr& unit)
{
    m_CollisionList.remove(unit);
}



void Game::CollisionCheck(float dt)
{
    // 충돌 체크 주기
    static Timer timer(0.01f);
    timer.AccumDt(dt);
    if (!timer.DurationCheck())
        return;

    for (auto& unit : m_CollisionList)
    {
        if (unit->IsDeath())
        {
            UnRegisterCollision(unit);
        }
        else if (auto section = unit->GetSection())
        {
            section->SyncUnit(unit);
        }
    }
    for (auto& section : m_SectionList)
    {
        section->CollisionCheck();
    }
}

void Game::CommandProc(float dt) const
{
    if (m_Command->IsKeyPress<Command::ESC>())
    {
        GameManager::GetInstance().Shutdown();
        return;
    }
    if (m_Command->IsKeyPress<Command::ENTER>())
    {
        GameManager::GetInstance().ReturnMain();
        return;
    }
    if (m_Command->IsKeyPress<Command::UP>())
    {
        m_Hero->AddMovePower(Vec2::UP * dt);
    }
    if (m_Command->IsKeyPress<Command::DOWN>())
    {
        m_Hero->AddMovePower(Vec2::DOWN * dt);
    }
    if (m_Command->IsKeyPress<Command::LEFT>())
    {
        m_Hero->AddMovePower(Vec2::LEFT * dt);
    }
    if (m_Command->IsKeyPress<Command::RIGHT>())
    {
        m_Hero->AddMovePower(Vec2::RIGHT * dt);
    }
    if (m_Command->IsKeyPress<Command::BUTTON_A>())
    {
        m_Hero->ShootMissile();
    }
    if (m_Command->IsKeyPress<Command::BUTTON_B>())
    {
        m_Hero->SwapMissile();
    }
}

void Game::SectionNumPrint() const
{
    static auto& console = Console::GetInstance();
    std::wostringstream oss;
    oss << L"SectionNum: " << m_SectionList.size();
    size_t posX = console.GetScreenWidth() - oss.str().length();
    size_t posY = console.GetScreenHeight() + 1;
    console.SetColor(Color::WHITE);
    console.PrintText(Coord(posX, posY), oss.str().c_str());
}
