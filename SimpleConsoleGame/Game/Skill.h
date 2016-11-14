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
public:
    Skill();
    virtual ~Skill() = default;

    virtual void    OnPrepare(float dt)     = 0;
    virtual void    OnBeginUse()            = 0;
    virtual void    OnUsing(float dt)       = 0;
    virtual void    OnEndUse()              = 0;

    bool            IsReadyToUse() const;
    void            UseSkill();
    void            Update(float dt);
    void            SetDuration(State state, float duration);

private:
    State           m_CurState;
    TimerPtr        m_PrepareTime;
    TimerPtr        m_UsingTime;
    TimerPtr        m_CoolTime;
};
