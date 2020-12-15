#include "stdafx.h"
#include "Assignment2.h"
#include "Object.h"
#include "Camera.h"
#include "Transform.h"
#include "Renderer.h"
#include "SimpleMove.h"
#include "Rotator.h"
#include "InputSystem.h"
#include "SceneSystem.h"

Assignment2::Assignment2()
{
	//--- 설명
	std::cout << "I/K/J/L: 플레이어 이동" << std::endl;
	std::cout << "W/S/A/D: 카메라 이동" << std::endl;
	std::cout << "Q/E: 카메라 업/다운" << std::endl;
	std::cout << "Y: 시점 변경" << std::endl;

	//--- Camera 생성
	Object* camera = new Object("Camera");
	//-- Camera
	camera->AddComponent<Camera>();
	camera->AddComponent<CameraController>();
	AddObject(camera);

	//--- Plane 생성
	Object* plane = new Object();
	//Transform
	auto planeTransform = plane->GetTransform();
	planeTransform->scale = glm::vec3(50);
	planeTransform->position = glm::vec3(0, -4, 0);
	//Renderer
	auto planeRenderer = plane->AddComponent<Renderer>();
	planeRenderer->SetTargetShader(ShaderType::TEXTURE_ELEMENT);
	planeRenderer->SetSharedModel("plane.obj");
	planeRenderer->SetSharedTextrue("tile.png");
	AddObject(plane);

	//--- Player 생성
	Object* player = new Object("Player");
	//Transform 
	auto playerTransform = player->GetTransform();
	playerTransform->position = glm::vec3(1, 0, 0);
	playerTransform->scale = glm::vec3(1);
	std::cout << playerTransform->GetWorldPosition().x << std::endl;
	//Renderer
	auto playerRenderer = player->AddComponent<Renderer>();
	playerRenderer->SetTargetShader(ShaderType::VERTEX_ELEMENT);
	playerRenderer->SetSharedModel("cube.obj");
	//Rotator
	//auto playerRotator = player->AddComponent<Rotator>();
	//playerRotator->direction = glm::vec3(0, 45, 0);
	//playerRotator->speed = 5;
	//Player
	auto playerPlayer = player->AddComponent<Player>();
	AddObject(player);

	Object* playerChild = new Object();
	//Transform 
	auto playerChildTransform = playerChild->GetTransform();
	playerChildTransform->scale = glm::vec3(1);
	playerChildTransform->position = glm::vec3(5, 0, 0);
	playerChildTransform->SetParent(playerTransform);
	std::cout << playerChildTransform->GetWorldPosition().x << std::endl;
	//Renderer
	auto playerChildRenderer = playerChild->AddComponent<Renderer>();
	playerChildRenderer->SetTargetShader(ShaderType::VERTEX_ELEMENT);
	playerChildRenderer->SetSharedModel("cube.obj");
	AddObject(playerChild);

	//--- Robot1
	Object* robot1 = CreateRobot();
	//Transform
	auto robot1Transform = robot1->GetTransform();
	robot1Transform->position = glm::vec3(-5, 0.3, -5);
	robot1Transform->rotation = glm::vec3(0, 90, 0);
	//Robot
	auto robot1Robot = robot1->GetComponent<Robot>();
	robot1Robot->patrolPoint.push_back(glm::vec3(-10, 0, 7));
	robot1Robot->patrolPoint.push_back(glm::vec3(-10, 0, -7));
	robot1Robot->patrolPoint.push_back(glm::vec3(0, 0, -7));
	robot1Robot->patrolPoint.push_back(glm::vec3(0, 0, 30));
	robot1Robot->patrolPoint.push_back(glm::vec3(15, 0, 0));
	AddObject(robot1);

	//--- Robot2
	Object* robot2 = CreateRobot();
	//Transform
	auto robot2Transform = robot2->GetTransform();
	robot2Transform->position = glm::vec3(15, 0.3, -5);
	robot2Transform->rotation = glm::vec3(0, 90, 0);
	//Robot
	auto robot2Robot = robot2->GetComponent<Robot>();
	robot2Robot->patrolPoint.push_back(glm::vec3(10, 0, 7));
	robot2Robot->patrolPoint.push_back(glm::vec3(10, 0, -7));
	robot2Robot->patrolPoint.push_back(glm::vec3(15, 0, 30));
	robot2Robot->patrolPoint.push_back(glm::vec3(0, 0, 30));
	robot2Robot->patrolPoint.push_back(glm::vec3(-10, 0, 30));
	AddObject(robot2);

	//--- Robot3
	Object* robot3 = CreateRobot();
	//Transform
	auto robot3Transform = robot3->GetTransform();
	robot3Transform->position = glm::vec3(15, 0.3, -20);
	robot3Transform->rotation = glm::vec3(0, 90, 0);
	//Robot
	auto robot3Robot = robot3->GetComponent<Robot>();
	robot3Robot->patrolPoint.push_back(glm::vec3(15, 0, -25));
	robot3Robot->patrolPoint.push_back(glm::vec3(15, 0, -40));
	robot3Robot->patrolPoint.push_back(glm::vec3(-27, 0, 2));
	robot3Robot->patrolPoint.push_back(glm::vec3(0, 0, 20));
	robot3Robot->patrolPoint.push_back(glm::vec3(0, 0, 10));
	AddObject(robot3);

	//--- Robot4
	Object* robot4 = CreateRobot();
	//Transform
	auto robot4Transform = robot4->GetTransform();
	robot4Transform->position = glm::vec3(-15, 0.3, -20);
	robot4Transform->rotation = glm::vec3(0, 90, 0);
	//Robot
	auto robot4Robot = robot4->GetComponent<Robot>();
	robot4Robot->patrolPoint.push_back(glm::vec3(-15, 0, -25));
	robot4Robot->patrolPoint.push_back(glm::vec3(-15, 0, -40));
	robot4Robot->patrolPoint.push_back(glm::vec3(0, 0, 20));
	robot4Robot->patrolPoint.push_back(glm::vec3(-20, 0, 30));
	robot4Robot->patrolPoint.push_back(glm::vec3(-17, 0, -10));
	AddObject(robot4);
}

Player::Player(Object* object) : Component(object)
{
	dx = 20;
	dz = 20;
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
	dz = 10;
	dx = 10;
	dc = 10;
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

	auto t = GetBelongingObject()->GetTransform();

	if (is.GetKeyDown('Y') == true)
	{
		isThirdPersonView = !isThirdPersonView;

		if (isThirdPersonView == true)
			ThirdPersonView();
		else
			FirstPersonView();
	}

	float vertical = 0;
	float horizontal = 0;
	float camera = 0;
	if (is.GetKey('W') == true)
		vertical += 1;
	if (is.GetKey('S') == true)
		vertical += -1;
	if (is.GetKey('A') == true)
		horizontal += 1;
	if (is.GetKey('D') == true)
		horizontal += -1;
	if (is.GetKey('Q') == true)
		camera += 1;
	if (is.GetKey('E') == true)
		camera += -1;

	t->position.x += dx * horizontal * DELTATIME;
	t->position.z += dz * vertical * DELTATIME;
	t->rotation.x += dc * camera * DELTATIME;
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
	cameraTransform->SetParent(player->GetTransform());

	cameraTransform->position.y = 0;
	cameraTransform->position.z = 0.5f;
	cameraTransform->rotation.x = 0;
}

void CameraController::ThirdPersonView()
{
	auto cameraTransform = GetBelongingObject()->GetTransform();

	//--- 부모 제거
	cameraTransform->DeleteParent();

	//-- Transform
	cameraTransform->position.y = 15.0f;
	cameraTransform->position.z = -60.0f;
	cameraTransform->rotation.x = 20;
}

Object* CreateRobot()
{
	Object* robot = new Object();
	auto robotRenderer = robot->AddComponent<Renderer>();
	robotRenderer->SetTargetShader(ShaderType::TEXTURE_ELEMENT);
	robotRenderer->SetSharedModel("robot.obj");
	robotRenderer->SetSharedTextrue("robot.png");
	robot->AddComponent<Robot>();
	return robot;
}

Robot::Robot(Object* object) : Component(object)
{
	m_Timer = 0;
	detectDistance = 12;
	m_enoughDistance = 1;
	m_IsDetectedPlayer = false;
	m_PatrolPointTargetIndex = 0;
}

void Robot::LookAt(glm::vec3 targetPos)
{
	auto transform = GetBelongingObject()->GetTransform();

	auto lookAt = targetPos - transform->GetWorldPosition();

	lookAt.y = 0;
	auto lookAtNormalized = glm::normalize(lookAt);

	auto result = glm::vec3(
		0,
		glm::degrees(glm::acos(glm::dot(lookAtNormalized, glm::vec3(1, 0, 0)))) + 90,
		0);

	transform->SetWorldRotation(result);
}

void Robot::LookAt(Object* target)
{
	auto targetPos = target->GetTransform()->GetWorldPosition();
	LookAt(targetPos);
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
		float distance = glm::distance(transform->GetWorldPosition(), player->GetTransform()->GetWorldPosition());
		if (distance < detectDistance && m_IsDetectedPlayer == false)
		{
			//std::cout << GetBelongingObject()->name << "플레이어와 가까워 졌습니다." << std::endl;

			m_IsDetectedPlayer = true;

			
		}

		if (distance > detectDistance && m_IsDetectedPlayer == true)
		{
			//std::cout << GetBelongingObject()->name << "플레이어와 멀어졌습니다." << std::endl;

			m_IsDetectedPlayer = false;
		}

		if (distance < m_enoughDistance)
			m_enoughDistance = true;
		else
			m_enoughDistance = false;
	}

	//--- 상황에 맞게 움직임
	//-- 플레이어를 따라가야하는 경우
	if (m_IsDetectedPlayer == true)
	{
		LookAt(player);

		if (m_enoughDistance == false)
		{
			transform->position = GlobalUtility::Lerp(transform->position, player->GetTransform()->position, DELTATIME);
		}
	}
	//-- 페트롤포인트를 따라가야하는 경우
	else
	{
		if (patrolPoint.size() > 0)
		{

			//- 해당 방향으로 이동
			transform->position = GlobalUtility::Lerp(transform->position, patrolPoint[m_PatrolPointTargetIndex], DELTATIME);

			//- 가까워지면 다음 인덱스로
			if (glm::distance(patrolPoint[m_PatrolPointTargetIndex], transform->position) < 0.3)
			{
				++m_PatrolPointTargetIndex;

				//- Repaet
				if (m_PatrolPointTargetIndex < 0 || m_PatrolPointTargetIndex >= patrolPoint.size())
				{
					m_PatrolPointTargetIndex = 0;
				}

				LookAt(patrolPoint[m_PatrolPointTargetIndex]);
			}
		}
	}
}
