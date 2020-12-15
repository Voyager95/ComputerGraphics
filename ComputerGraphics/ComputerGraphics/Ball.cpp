#include "stdafx.h"
#include "Ball.h"
#include "Object.h"
#include "Rigidbody.h"
#include "SceneSystem.h"
#include "Scene.h"
#include "Renderer.h"
#include "ModelInstnce.h"
#include "TermProject.h"
#include "Tile.h"
#include "Transform.h"

Ball::Ball(Object* object) : Component(object)
{
	itemTimer = 5;
	m_BiggerTimer = 0;
	m_LighterTimer = 0;

	radius = 4;

	m_HitPoint = 1;

	defaultColor = glm::vec3(1, 1, 1);
	slowSpeedColor = glm::vec3(0.2, 0.2, 0.8);
	fastSpeedColor = glm::vec3(0.9, 0.7, 0.2);
	maxSpeedColor = glm::vec3(1, 0.0, 0.0);

	maxSlowSpeed = 18;
	maxFastSpeed = -22;

	m_Lighter = false;
	m_Bigger = false;

	m_MaxSpeedTimer = 0;

	m_Model = nullptr;

	invincibilityDuration = 1.0;
}

Ball::~Ball()
{
	if (m_Model != nullptr && m_Bigger)
	{
		m_Model->SetSize(0.5);
		m_Model->UpdateBuffer();
	}
}

void Ball::Damage(Tile* tile)
{
	//--- 커져서 부수고 가는 경우
	if (m_Bigger == true)
	{
		tile->Destory();

		return;
	}

	//--- 속도가 빨라서 부수고 가는 경우
	if (m_IsInvincibility == true)
	{
		m_IsInvincibility = false;

		auto rigidbody = GetBelongingObject()->GetComponent<Rigidbody>();

		if (rigidbody == nullptr)
			std::cout << "Rigidbody가 없습니다." << std::endl;
		else
			rigidbody->SetPresentDirection(glm::vec3(0, 0, 0));

		tile->Destory();
		return;
	}

	//--- 데미지처리
	--m_HitPoint;
	if (m_HitPoint <= 0)
	{
		Death();
	}
}

void Ball::Bounce(Tile* tile)
{
	//--- 커져서 부수고 가는 경우
	if (m_Bigger == true)
	{
		tile->Destory();

		return;
	}

	//--- 속도가 빨라서 부수고 가는 경우
	if (m_IsInvincibility == true)
	{
		m_IsInvincibility = false;

		auto rigidbody = GetBelongingObject()->GetComponent<Rigidbody>();

		if (rigidbody == nullptr)
			std::cout << "Rigidbody가 없습니다." << std::endl;
		else
			rigidbody->SetPresentDirection(glm::vec3(0, 0, 0));

		tile->Destory();
		return;
	}

	auto rigidbody = GetBelongingObject()->GetComponent<Rigidbody>();

	if (rigidbody == nullptr)
		std::cout << "Rigidbody가 없습니다." << std::endl;
	else
	{
		rigidbody->SetPresentDirection(glm::vec3(0, 0, 0));
		rigidbody->AddForce(glm::vec3(0, 10, 0));
	}

}

void Ball::Bigger(Tile* tile)
{
	if (m_Bigger == true)
		return;

	m_BiggerTimer = itemTimer;
	m_Bigger = true;

	auto renderer = GetBelongingObject()->GetComponent<Renderer>();
	auto model = renderer->GetModel();
	m_Model = model;

	model->SetSize(2);
	model->UpdateBuffer();
	radius = 5;

	tile->Destory();
}

void Ball::Lighter(Tile* tile)
{
	if (m_Lighter == true)
		return;

	m_LighterTimer = itemTimer;
	m_Lighter = true;
	auto rigidbody = GetBelongingObject()->GetComponent<Rigidbody>();
	rigidbody->gravityMultiples = 1.0f;

	tile->Destory();
}

void Ball::OnUpdate()
{
	auto rigidbody = GetBelongingObject()->GetComponent<Rigidbody>();
	auto renderer = GetBelongingObject()->GetComponent<Renderer>();
	auto direction = rigidbody->GetPresentDirection();
	auto model = renderer->GetModel();

	//--- 타이머 처리
	m_BiggerTimer -= DELTATIME;
	m_LighterTimer -= DELTATIME;

	//--- 아이템 처리
	if (m_BiggerTimer < 0 && m_Bigger)
	{
		model->SetSize(0.5);
		model->UpdateBuffer();
		radius = 4;

		m_Bigger = false;
	}

	if (m_LighterTimer < 0 && m_Lighter)
	{
		rigidbody->gravityMultiples = 2.0f;
		m_Lighter = false;
	}

	//--- 상태변화
	if (direction.y > maxFastSpeed)
	{
		m_IsInvincibility = false;
		m_MaxSpeedTimer = 0;

		if (direction.y > 0)
		{
			auto value = direction.y / maxSlowSpeed;
			value = glm::clamp(value, 0.0f, 1.0f);
			auto desiredColor = defaultColor * (1 - value) + slowSpeedColor * value;
			model->SetColor(desiredColor);
			model->UpdateBuffer();
		}
		else
		{
			auto value = direction.y / maxFastSpeed;
			value = glm::clamp(value, 0.0f, 1.0f);
			auto desiredColor = defaultColor* (1 - value) + fastSpeedColor * value;
			model->SetColor(desiredColor);
			model->UpdateBuffer();
		}
	}
	else
	{
		m_MaxSpeedTimer += DELTATIME;

		if (m_MaxSpeedTimer > invincibilityDuration)
		{
			m_IsInvincibility = true;
			model->SetColor(maxSpeedColor);
			model->UpdateBuffer();
		}
	}
}

void Ball::Death()
{
	std::cout << "공 죽음" << std::endl;

	auto scene = std::make_shared<TermProject>();

	auto& ss = SceneSystem::GetInstance();

	ss.StartScene(std::static_pointer_cast<Scene>(scene));
}
