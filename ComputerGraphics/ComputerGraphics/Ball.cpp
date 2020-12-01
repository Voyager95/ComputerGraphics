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
	std::cout << "�� ������" << std::endl;

	//--- ������ó��
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
		std::cout << "Rigidbody�� �����ϴ�." << std::endl;
	else
		rigidbody->AddForce(glm::vec3(0, 15, 0));

	std::cout << "�� ƨ��" << std::endl;
}

void Ball::Death()
{
	std::cout << "�� ����" << std::endl;
}
