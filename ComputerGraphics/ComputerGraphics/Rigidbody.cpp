#include "stdafx.h"
#include "Rigidbody.h"
#include "Object.h"
#include "Transform.h"

Rigidbody::Rigidbody(Object* object) : Component(object)
{
	gravity = true;
}

void Rigidbody::AddForce(glm::vec3 direction)
{
	m_presentDirecttion += direction;
}

void Rigidbody::OnUpdate()
{
	//--- 중력 가속도 적용
	if (gravity== true &&m_presentDirecttion.y > GRAVITY)
	{
		m_presentDirecttion += GRAVITY * DELTATIME;
	}

	//--- 이동
	auto transform = GetBelongingTransform();
	transform->position += m_presentDirecttion * DELTATIME;
}
