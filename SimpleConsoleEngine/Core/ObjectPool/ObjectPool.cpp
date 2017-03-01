#include "stdafx.h"
#include "ObjectPool.h"
SCE_USE

std::vector<uint8_t*> _objectPoolDeleteHelper::poolList;

_objectPoolDeleteHelper s_ObjectPoolDeleteHelper;
