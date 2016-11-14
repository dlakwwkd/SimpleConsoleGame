#include "stdafx.h"
#include "Skill.h"
#include "Core/Timer/Timer.h"
SCE_USE


Skill::Skill()
:   m_CurState(State::READY)
{
    m_PrepareTime = std::make_unique<Timer>();
    m_UsingTime = std::make_unique<Timer>();
    m_CoolTime = std::make_unique<Timer>();
}

bool Skill::IsReadyToUse() const
{
    return m_CurState == State::READY;
}

void Skill::UseSkill()
{
    if (!IsReadyToUse())
        return;

    m_CurState = State::PREPARE;
}

void Skill::Update(float dt)
{
    switch (m_CurState)
    {
    case Skill::State::PREPARE:
        {
            m_PrepareTime->AccumDt(dt);
            if (m_PrepareTime->DurationCheck())
            {
                m_CurState = State::USING;
                OnBeginUse();
                return;
            }
            OnPrepare(dt);
        }
        break;
    case Skill::State::USING:
        {
            m_UsingTime->AccumDt(dt);
            if (m_UsingTime->DurationCheck())
            {
                m_CurState = State::COOLTIME;
                OnEndUse();
                return;
            }
            OnUsing(dt);
        }
        break;
    case Skill::State::COOLTIME:
        {
            m_CoolTime->AccumDt(dt);
            if (m_CoolTime->DurationCheck())
            {
                m_CurState = State::READY;
            }
        }
        break;
    }
}

void Skill::SetDuration(State state, float duration)
{
    switch (state)
    {
    case Skill::State::PREPARE:
        m_PrepareTime->SetDuration(duration);
        break;
    case Skill::State::USING:
        m_UsingTime->SetDuration(duration);
        break;
    case Skill::State::COOLTIME:
        m_CoolTime->SetDuration(duration);
        break;
    }
}
