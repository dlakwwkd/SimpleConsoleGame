#pragma once
#include "IObject.h"
#include "IRender.h"
SCE_START


class IGameBase
    : public IObject
    , public IRender
{
};

SCE_END
