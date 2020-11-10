#include "stdafx.h"
#include "GlobalUtility.h"
#include "Object.h"
#include "Transform.h"

std::shared_ptr<Object> GlobalUtility::CreateObject()
{
	auto instance = std::make_shared<Object>();
	auto t = std::make_shared<Transform>(instance);
	instance->OnAddTransform(t);

	return instance;
}
