#include "stdafx.h"
#include "TermProject.h"
#include "Object.h"
#include "Camera.h"
#include "Transform.h"
#include "Renderer.h"
#include "SimpleMove.h"
#include "Rotator.h"
#include "InputSystem.h"
#include "SceneSystem.h"

TermProject::TermProject()
{
	//--- Camera 생성
	Object* camera = new Object();
	//-- Camera
	camera->AddComponent<Camera>();
	camera->AddComponent<CameraController>();
	AddObject(camera);

	//--- Player 생성
	Object* player = new Object("Player");
	//Transform 
	auto playerTransform = player->GetTransform();
	playerTransform->position = glm::vec3(0, 0, 0);
	playerTransform->scale = glm::vec3(1);
	//Renderer
	auto playerRenderer = player->AddComponent<Renderer>();
	playerRenderer->SetTargetShader(ShaderType::VERTEX_ELEMENT);
	playerRenderer->SetSharedModel("cube.obj");
	//Rotator
	auto playerRotator = player->AddComponent<Rotator>();
	playerRotator->direction = glm::vec3(0, 45, 0);
	playerRotator->speed = 5;
	//Player
	auto playerPlayer = player->AddComponent<Player>();
	AddObject(player);

	Object* playerChild = new Object();
	//Transform 
	auto playerChildTransform = playerChild->GetTransform();
	playerChildTransform->scale = glm::vec3(1);
	playerChildTransform->position = glm::vec3(5, 0, 0);
	playerChildTransform->parent = playerTransform;
	//Renderer
	auto playerChildRenderer = playerChild->AddComponent<Renderer>();
	playerChildRenderer->SetTargetShader(ShaderType::VERTEX_ELEMENT);
	playerChildRenderer->SetSharedModel("cube.obj");
	AddObject(playerChild);

}

Player::Player(Object* object) : Component(object)
{
	dx = 5;
	dz = 5;
}

void Player::OnUpdate()
{
	InputSystem& is = InputSystem::GetInstance();
	Transform* t = GetBelongingObject()->GetTransform();
	float vertical = 0;
	float horizontal = 0;
	if (is.GetKey('I') == true)
		vertical += 1;
	if (is.GetKey('K') == true)
		vertical += -1;
	if (is.GetKey('J') == true)
		horizontal += 1;
	if (is.GetKey('L') == true)
		horizontal += -1;

	t->position.x += dx * horizontal * DELTATIME;
	t->position.z += dz * vertical * DELTATIME;

}

CameraController::CameraController(Object* object) : Component(object)
{
	isThirdPersonView = true;
}

void CameraController::OnCreate()
{
	if (isThirdPersonView == true)
		ThirdPersonView();
	else
		FirstPersonView();
}

void CameraController::OnUpdate()
{
	InputSystem& is = InputSystem::GetInstance();

	if (is.GetKeyDown('Y') == true)
	{
		isThirdPersonView = !isThirdPersonView;

		if (isThirdPersonView == true)
			ThirdPersonView();
		else
			FirstPersonView();
	}
}

void CameraController::FirstPersonView()
{
	SceneSystem& ss = SceneSystem::GetInstance();
	auto cameraTransform = GetBelongingObject()->GetTransform();

	//-- 부모설정
	auto player = ss.GetObjectByName("Player");
	if (player == nullptr)
	{
		std::cout << "해당 오브젝트는 없습니다" << std::endl;
		return;
	}
	cameraTransform->parent = player->GetTransform();

	cameraTransform->position.y = 0;
	cameraTransform->position.z = 0.5f;
	cameraTransform->rotation.x = 0;
}

void CameraController::ThirdPersonView()
{
	auto cameraTransform = GetBelongingObject()->GetTransform();

	//--- 부모 제거
	cameraTransform->parent = nullptr;

	//-- Transform
	cameraTransform->position.y = 15.0f;
	cameraTransform->position.z = -70.0f;
	cameraTransform->rotation.x = 45;
}

Object* CreateObject()
{
	Object* robot = new Object();
	auto robotRenderer = robot->AddComponent<Renderer>();
	robotRenderer->SetTargetShader(ShaderType::TEXTURE_ELEMENT);
	robotRenderer->SetSharedModel("robot.obj");
	robotRenderer->SetSharedTextrue("robot.png");

	return robot;
}

Robot::Robot(Object* object) : Component(object)
{
	m_Timer = 0;
	detectDistance = 4;
	m_IsDetectedPlayer = false;
}

void Robot::OnUpdate()
{
	SceneSystem& ss = SceneSystem::GetInstance();
	auto transform = GetBelongingObject()->GetTransform();
	auto player = ss.GetObjectByName("Player");

	m_Timer += DELTATIME;

	//--- 위치 설정
	transform->position.y = 0.3 + glm::sin(m_Timer);

	//--- 플레이어간 위치 계산
	if (player != nullptr)
	{
		if (glm::distance(transform->position, player->GetTransform()->position) < 4)
		{
			m_IsDetectedPlayer = true;
		}
		else
			m_IsDetectedPlayer = false;
	}

	//--- 상황에 맞게 움직임
	//-- 플레이어를 따라가야하는 경우
	if (m_IsDetectedPlayer == true)
	{
		
	}
	//-- 페트롤포인트를 따라가야하는 경우
	else
	{
		if (m_PatrolPointTargetIndex < 0 && m_PatrolPointTargetIndex >= patrolPoint.size())
		{

		}
	}
}
