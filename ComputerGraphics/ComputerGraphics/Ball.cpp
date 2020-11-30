#include "stdafx.h"
#include "Ball.h"
#include "Object.h"

Ball::Ball(Object* object) : Component(object)
{
	radius = 5;

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
	std::cout << "�� ƨ��" << std::endl;
}

void Ball::Death()
{
	std::cout << "�� ����" << std::endl;
}
