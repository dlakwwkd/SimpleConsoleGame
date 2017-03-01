#include "stdafx.h"
#include "Skill.h"
#include "../Timer/Timer.h"
SCE_USE

/////////////////////////////////////////////////////////////////////////////////////////
struct Skill::impl
{
    impl() noexcept
        : curState{ State::READY }
        , prepareTime{ std::make_unique<Timer>() }
        , usingTime{ std::make_unique<Timer>() }
        , coolTime{ std::make_unique<Timer>() }
    {
    }

    State       curState;
    TimerPtr    prepareTime;
    TimerPtr    usingTime;
    TimerPtr    coolTime;
};

/////////////////////////////////////////////////////////////////////////////////////////
Skill::Skill() noexcept
    : pimpl{ std::make_unique<impl>() }
{
}

/////////////////////////////////////////////////////////////////////////////////////////
Skill::~Skill()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
bool Skill::IsReadyToUse() const
{
    return pimpl->curState == State::READY;
}

/////////////////////////////////////////////////////////////////////////////////////////
void Skill::UseSkill()
{
    if (!IsReadyToUse())
        return;

    pimpl->curState = State::PREPARE;
}

/////////////////////////////////////////////////////////////////////////////////////////
void Skill::Update(float _dt)
{
    switch (pimpl->curState)
    {
    case Skill::State::PREPARE:
        {
            pimpl->prepareTime->AccumDt(_dt);
            if (pimpl->prepareTime->DurationCheck())
            {
                pimpl->curState = State::USING;
                OnBeginUse();
                return;
            }
            OnPrepare(_dt);
        }
        break;
    case Skill::State::USING:
        {
            pimpl->usingTime->AccumDt(_dt);
            if (pimpl->usingTime->DurationCheck())
            {
                pimpl->curState = State::COOLTIME;
                OnEndUse();
                return;
            }
            OnUsing(_dt);
        }
        break;
    case Skill::State::COOLTIME:
        {
            pimpl->coolTime->AccumDt(_dt);
            if (pimpl->coolTime->DurationCheck())
            {
                pimpl->curState = State::READY;
            }
        }
        break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
void Skill::SetDuration(State _state, float _duration)
{
    switch (_state)
    {
    case Skill::State::PREPARE:
        pimpl->prepareTime->SetDuration(_duration);
        break;
    case Skill::State::USING:
        pimpl->usingTime->SetDuration(_duration);
        break;
    case Skill::State::COOLTIME:
        pimpl->coolTime->SetDuration(_duration);
        break;
    }
}
