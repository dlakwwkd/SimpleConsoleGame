#pragma once


class Skill
{
    SPECIALFUNC_SET(Skill, default)
public:
    Skill() noexcept = default;
    virtual ~Skill() = default;

    virtual void Init();
    virtual void Release();
    virtual void Update(float dt);
    virtual void Render();
};
