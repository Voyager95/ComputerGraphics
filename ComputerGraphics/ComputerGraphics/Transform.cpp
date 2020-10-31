#include "stdafx.h"
#include "Transform.h"

Transform::Transform(std::shared_ptr<Object> object) : Component(object)
{
	position.x = 0;
	position.y = 0;
	position.z = 0;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;

	scale.x = 0;
	scale.y = 0;
	scale.z = 0;
}
