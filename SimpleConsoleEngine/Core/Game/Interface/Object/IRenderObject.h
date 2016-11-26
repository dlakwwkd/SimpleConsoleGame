#pragma once
#include "IGameObject.h"
SCE_START
class IRenderComponent;

using RenderPtr = std::shared_ptr<IRenderComponent>;
using RenderRef = std::weak_ptr<IRenderComponent>;


__interface IRenderObject : public IGameObject
{
	RenderPtr	GetRender();
	void		Render();
};

SCE_END
