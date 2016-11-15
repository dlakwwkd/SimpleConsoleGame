#pragma once
SCE_START
class Timer;
SCE_END
class Unit;


class Skill
{
    SPECIALFUNC_SET(Skill, default)
protected:
    enum class State
    {
        READY,
        PREPARE,
        USING,
        COOLTIME,
    };
    using TimerPtr  = std::unique_ptr<SCE::Timer>;
    using UnitRef   = std::weak_ptr<Unit>;
public:
    Skill();
    virtual ~Skill() = default;

    virtual void        OnPrepare(float dt)     = 0;
    virtual void        OnBeginUse()            = 0;
    virtual void        OnUsing(float dt)       = 0;
    virtual void        OnEndUse()              = 0;

    bool                IsReadyToUse() const;
    void                UseSkill();
    void                Update(float dt);
    void                SetDuration(State state, float duration);

    template<typename T>
    std::shared_ptr<T>  GetOwner() const
    {
        return std::dynamic_pointer_cast<T>(m_Owner.lock());
    }
    template<typename T>
    void                SetOwner(const std::shared_ptr<T>& owner)
    {
        m_Owner = std::dynamic_pointer_cast<Unit>(owner);
    }

private:
    State               m_CurState;
    UnitRef             m_Owner;
    TimerPtr            m_PrepareTime;
    TimerPtr            m_UsingTime;
    TimerPtr            m_CoolTime;
};
