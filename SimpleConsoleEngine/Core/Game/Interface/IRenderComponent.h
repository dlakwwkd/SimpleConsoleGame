#pragma once
#include "IComponent.h"
#include "IRender.h"
SCE_START


class IRenderComponent
    : public IComponentCRTP<IRenderComponent>
    , public IRender
{
};

SCE_END
