#pragma once
#include "Core/Game/Interface/IGameBase.h"
SCE_START
class Command;
class GameObject;
SCE_END
class Unit;
class Hero;
class Mob;


class Game : public SCE::IGameBase
{
    SPECIALFUNC_SET(Game, delete)
    using ObjectPtr = std::shared_ptr<SCE::GameObject>;
public:
    Game();
    virtual ~Game() override;

    virtual void Init()             override;
    virtual void Release()          override;
    virtual void Update(float dt)   override;
    virtual void Render()           override;

    void AddRenderList(const ObjectPtr& obj, float lifeTime);
    void AddRenderList(const ObjectPtr& obj);
    void RemoveRenderList(const ObjectPtr& obj);

    void RegisterCollisionList(const ObjectPtr& obj);
    void UnRegisterCollisionList(const ObjectPtr& obj);

private:
    void CommandProc(float dt);

private:
    std::unique_ptr<SCE::Command>       m_Command;
    std::shared_ptr<Hero>               m_Hero;
    std::vector<std::shared_ptr<Mob>>   m_MobList;
    std::list<ObjectPtr>                m_RenderList;
    std::list<ObjectPtr>                m_CollisionList;
};
