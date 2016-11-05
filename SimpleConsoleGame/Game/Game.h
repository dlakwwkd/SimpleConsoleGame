#pragma once
#include "Core/Game/Interface/IGameBase.h"
SCE_START
class Command;
class GameObject;
SCE_END
class Section;
class Unit;
class Hero;
class Mob;


class Game : public SCE::IGameBase
{
    SPECIALFUNC_SET(Game, delete)
    using ObjectPtr = std::shared_ptr<SCE::GameObject>;
    using UnitPtr   = std::shared_ptr<Unit>;
    using MobPtr    = std::shared_ptr<Mob>;
public:
    Game();
    virtual ~Game() override;

    virtual void Init()             override;
    virtual void Release()          override;
    virtual void Update(float dt)   override;
    virtual void Render()           override;

    void AddOnlyRender(const ObjectPtr& obj, float lifeTime);
    void AddOnlyRender(const ObjectPtr& obj);
    void RemoveOnlyRender(const ObjectPtr& obj);

    void RegisterCollision(const UnitPtr& unit);
    void UnRegisterCollision(const UnitPtr& unit);

private:
    void CommandProc(float dt);

private:
    std::unique_ptr<SCE::Command>   m_Command;
    std::shared_ptr<Section>        m_RootSection;
    std::shared_ptr<Hero>           m_Hero;
    std::vector<MobPtr>             m_MobList;
    std::list<UnitPtr>              m_CollisionList;
    std::list<ObjectPtr>            m_OnlyRenderList;
};
