#pragma once
#include "Core/Game/Interface/IGameBase.h"
SCE_START
class Command;
class GameObject;
class Section;
class Unit;
SCE_END
class Hero;
class Mob;


class Game : public SCE::IGameBase
{
    SPECIALFUNC_SET(Game, delete)
    using ObjectPtr     = std::shared_ptr<SCE::GameObject>;
    using MobPtr        = std::shared_ptr<Mob>;
public:
    Game() noexcept;
    virtual ~Game() override;

    virtual void Init()             override;
    virtual void Release()          override;
    virtual void Update(float dt)   override;
    virtual void Render()           override;

private:
    void    GenerateMob(int num);
    void    CommandProc(float dt) const;

private:
    std::unique_ptr<SCE::Command>   m_Command;
    std::shared_ptr<Hero>           m_Hero;
    std::vector<MobPtr>             m_MobList;
};
