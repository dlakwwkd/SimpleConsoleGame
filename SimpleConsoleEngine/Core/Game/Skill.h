#pragma once
SCE_START
class Timer;
class Unit;


class Skill
{
    DECLARE_PIMPL
    SPECIALFUNC_MOVE_SET(Skill, default)
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
    Skill() noexcept;
    virtual ~Skill();

    virtual void        OnPrepare(float _dt)    = 0;
    virtual void        OnBeginUse()            = 0;
    virtual void        OnUsing(float _dt)      = 0;
    virtual void        OnEndUse()              = 0;

    bool                IsReadyToUse() const;
    void                UseSkill();
    void                Update(float _dt);
    void                SetDuration(State _state, float _duration);

    template<typename T>
    std::shared_ptr<T>  GetOwner() const
    {
        return std::dynamic_pointer_cast<T>(owner.lock());
    }
    template<typename T>
    void                SetOwner(const std::shared_ptr<T>& _owner)
    {
        owner = std::dynamic_pointer_cast<Unit>(_owner);
    }

private:
    UnitRef             owner;
};

SCE_END
