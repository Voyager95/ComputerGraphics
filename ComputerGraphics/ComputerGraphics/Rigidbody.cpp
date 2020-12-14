#include "stdafx.h"
#include "Rigidbody.h"
#include "Object.h"
#include "Transform.h"

Rigidbody::Rigidbody(Object* object) : Component(object)
{
	gravity = true;
	gravityMultiples = 1;
	m_presentDirection = glm::vec3(0, 0, 0);
	m_Torque = glm::vec3(0, 0, 0);
	gravityLimit = true;
	gravitylimitSpeed = 30;
}

void Rigidbody::AddForce(glm::vec3 direction)
{
	m_presentDirection += direction;
}

void Rigidbody::AddTorque(glm::vec3 direction)
{
	m_Torque += direction;
}


void Rigidbody::OnUpdate()
{
	//--- �߷� ���ӵ� ����
	if (gravity == true )
	{
		if (gravityLimit == false)
			m_presentDirection.y += GRAVITY * DELTATIME * gravityMultiples;
		else
		{
			auto size = glm::length(m_presentDirection);
			if (gravitylimitSpeed > size)
			{
				m_presentDirection.y += GRAVITY * DELTATIME * gravityMultiples;
			}
		}
	}

	auto transform = GetBelongingTransform();

	//--- �̵�
	transform->position += m_presentDirection * DELTATIME;

	//--- ȸ��
	transform->rotation += m_Torque * DELTATIME;
}
