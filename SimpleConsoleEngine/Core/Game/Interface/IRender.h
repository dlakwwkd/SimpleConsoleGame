#pragma once
SCE_START


class IRender
{
    SPECIALFUNC_SET(IRender, default)
public:
    IRender() noexcept {}
    virtual ~IRender() {}

    virtual void Render() = 0;
};

SCE_END
