#include "stdafx.h"
#include "SimpleFallower.h"
#include "Object.h"

SimpleFallower::SimpleFallower(Object* object) : Component(object)
{
	fallow = true;
	offset = glm::vec3();
	pTarget = nullptr;
}

void SimpleFallower::OnUpdate()
{
	if (fallow == true && pTarget != nullptr)
	{

	}
}
