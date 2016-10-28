#pragma once


class Section
{
    SPECIALFUNC_SET(Section, default)
public:
    Section()   = default;
    ~Section()  = default;

    void Init();
    void Release();
};
