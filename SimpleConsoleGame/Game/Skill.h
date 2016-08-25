#pragma once


class Skill
{
    SPECIALFUNC_SET(Skill, default)
public:
    Skill()             = default;
    virtual ~Skill()    = default;

    virtual void Init();
    virtual void Release();
    virtual void Update(float dt);
    virtual void Render();
};
