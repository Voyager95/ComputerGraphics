#include "stdafx.h"
#include "Rotator.h"
#include "Object.h"
#include "Transform.h"

Rotator::Rotator(std::shared_ptr<Object> object) : Component(object)
{
	speed = 0;
	direction = glm::vec3();
}

void Rotator::OnUpdate()
{
	auto transform = GetBelongingObject()->GetTransform();

	transform->rotation += direction * speed * DELTATIME;
}
