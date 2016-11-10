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
    using ObjectPtr     = std::shared_ptr<SCE::GameObject>;
    using UnitPtr       = std::shared_ptr<Unit>;
    using MobPtr        = std::shared_ptr<Mob>;
    using SectionPtr    = std::shared_ptr<Section>;
    using SectionRef    = std::weak_ptr<Section>;
public:
    Game();
    virtual ~Game() override;

    virtual void Init()             override;
    virtual void Release()          override;
    virtual void Update(float dt)   override;
    virtual void Render()           override;

    void        AddOnlyRender(const ObjectPtr& obj, float lifeTime);
    void        AddOnlyRender(const ObjectPtr& obj);
    void        RemoveOnlyRender(const ObjectPtr& obj);

    void        RegisterCollision(const UnitPtr& unit);
    void        RegisterCollision(const UnitPtr& unit, const SectionPtr& trySection);
    void        UnRegisterCollision(const UnitPtr& unit);

    void        RegisterBuiltSection(const SectionPtr& section, const POINT& pos);
    SectionPtr  FindSection(const POINT& pos) const;

private:
    void        GenerateMob(int num);

    void        AddCollision(const UnitPtr& unit);
    void        RemoveCollision(const UnitPtr& unit);

    void        CollisionCheck(float dt);
    void        CommandProc(float dt) const;
    void        SectionNumPrint() const;

private:
    std::unique_ptr<SCE::Command>   m_Command;
    std::shared_ptr<Section>        m_RootSection;
    std::shared_ptr<Hero>           m_Hero;
    std::vector<MobPtr>             m_MobList;
    std::list<UnitPtr>              m_CollisionList;
    std::list<ObjectPtr>            m_OnlyRenderList;
    std::vector<SectionPtr>         m_SectionList;
    std::map<POINT, SectionRef>     m_SectionMap;

    friend bool operator<(const POINT& l, const POINT& r)
    {
        return l.x < r.x || (l.x == r.x && l.y < r.y);
    }
};
