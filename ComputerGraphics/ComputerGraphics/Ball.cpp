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
	std::cout << "°ø µ¥¹ÌÁö" << std::endl;

	//--- µ¥¹ÌÁöÃ³¸®
	--m_HitPoint;
	if (m_HitPoint <= 0)
	{
		Death();
	}
}

void Ball::Bounce()
{
	std::cout << "°ø Æ¨±è" << std::endl;
}

void Ball::Death()
{
	std::cout << "°ø Á×À½" << std::endl;
}
