#include "stdafx.h"
#include "SimpleMove.h"
#include "Object.h"
#include "Transform.h"

SimpleMove::SimpleMove(Object* object) : Component(object)
{
	presentMoveType = MoveType::NONE;
	speed = 0;
	direction = glm::vec3();
	destination = glm::vec3();
}

void SimpleMove::OnUpdate()
{
	auto transform = GetBelongingObject()->GetTransform();
	switch (presentMoveType)
	{
	case MoveType::BY_DESTINATION_SPEED:
		transform->position += direction * speed * DELTATIME;
		break;
	case MoveType::BY_DESTINATION_TIME:
	{
		m_PresentDuration += DELTATIME;
		float e = m_PresentDuration / duration;

		transform->position = m_StartPosition * (1 - e) + destination * e;

		std::cout << m_PresentDuration << "현재위치: " << transform->position.x  <<", " << transform->position.y << ", " << transform->position.z << std::endl;

		if (m_PresentDuration > duration)
			presentMoveType = MoveType::NONE;
	}
		break;
	case MoveType::BY_DIRECTION:
		break;
	default:
		break;
	}
}

void SimpleMove::MoveToBySpeed(glm::vec3 destination, float speed)
{
}

void SimpleMove::MoveToByTime(glm::vec3 newDestination, float newDuration)
{
	presentMoveType = MoveType::BY_DESTINATION_TIME;
	m_StartPosition = GetBelongingObject()->GetTransform()->position;
	destination = newDestination;
	duration = newDuration;
	m_PresentDuration = 0;
}
