#include "stdafx.h"
#include "Ball.h"
#include "Object.h"
#include "Rigidbody.h"

Ball::Ball(Object* object) : Component(object)
{
	radius = 4;

	m_HitPoint = 1;
}

void Ball::Damage()
{
	std::cout << "공 데미지" << std::endl;

	//--- 데미지처리
	--m_HitPoint;
	if (m_HitPoint <= 0)
	{
		Death();
	}
}

void Ball::Bounce()
{
	auto rigidbody = GetBelongingObject()->GetComponent<Rigidbody>();

	if (rigidbody == nullptr)
		std::cout << "Rigidbody가 없습니다." << std::endl;
	else
		rigidbody->AddForce(glm::vec3(0, 15, 0));

	std::cout << "공 튕김" << std::endl;
}

void Ball::Death()
{
	std::cout << "공 죽음" << std::endl;
}
