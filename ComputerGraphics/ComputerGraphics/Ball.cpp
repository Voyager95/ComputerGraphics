#include "stdafx.h"
#include "Ball.h"
#include "Object.h"
#include "Rigidbody.h"
#include "SceneSystem.h"
#include "Scene.h"
#include "TermProject.h"

Ball::Ball(Object* object) : Component(object)
{
	radius = 4;

	m_HitPoint = 1;

	slowSpeedColor = glm::vec3(0.2, 0.2, 0.8);
	fastSpeedColor = glm::vec3(0.9, 0.7, 0.2);
	maxSpeedColor = glm::vec3(1, 0.2, 0.2);

	maxSpeed = 18;
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

void Ball::OnUpdate()
{
}

void Ball::Death()
{
	std::cout << "공 죽음" << std::endl;

	auto scene = std::make_shared<TermProject>();

	auto& ss = SceneSystem::GetInstance();

	ss.StartScene(std::static_pointer_cast<Scene>(scene));
}
