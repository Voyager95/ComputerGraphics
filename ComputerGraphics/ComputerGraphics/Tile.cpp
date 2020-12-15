#include "stdafx.h"
#include "Tile.h"
#include "SceneSystem.h"
#include "Transform.h"
#include "Ball.h"
#include "Object.h"
#include "Frag.h"
#include "Renderer.h"
#include "rigidbody.h"
#include "ModelInstnce.h"
#include "ResourceSystem.h"
#include "Scene.h"
Tile::Tile(Object* object) : Component(object)
{
	type = TileType::BLACK;
	angle = 30;
}

void Tile::Destory()
{
	switch (type)
	{
	case TileType::BLACK:
	{
		auto frag = Tile::InstantiateBlackFragTile();
		auto scene = GetBelongingObject()->GetBelongingScene();
		auto transform = frag->GetTransform();
		transform->SetWorldPosition(GetBelongingTransform()->GetWorldPosition());
		transform->SetWorldRotation(GetBelongingTransform()->GetWorldRotation());
		scene->AddObject(frag);
	}
		break;
	case TileType::RED:
	{
		auto frag = Tile::InstantiateRedFragTile();
		auto scene = GetBelongingObject()->GetBelongingScene();
		auto transform = frag->GetTransform();
		transform->SetWorldPosition(GetBelongingTransform()->GetWorldPosition());
		transform->SetWorldRotation(GetBelongingTransform()->GetWorldRotation());
		scene->AddObject(frag);
	}
		break;
	case TileType::LIGHTER:
		break;
	case TileType::BIGGER:
		break;
	default:
		break;
	}
	GetBelongingObject()->SubObject();
}

void Tile::OnCreate()
{
	auto tileTransform = GetBelongingTransform();
}

void Tile::OnUpdate()
{
	SceneSystem& ss = SceneSystem::GetInstance();
	auto ball = ss.GetObjectByName("Ball");
	
	//--- 충돌 체크합니다. 
	if (ball != nullptr)
	{
		bool isCollide = false;								// 충돌판정 플레그입니다.

		auto ballBall = ball->GetComponent<Ball>();			// ball의 Ball 컴포넌트입니다.
		auto ballTransform = ball->GetTransform();			// ball의 Transform 컴포넌트입니다.

		/*
		여기에 충돌하는 알고리즘을 작성하면 됩니다.
		다음의 작동방식을 참고하십시오.
		- isCollide변수가 기본적으로 false상태일 것입니다. 만일 충돌하면 true로 변경하십시오
		- isCollide변수가 true가 되면 이 타일의 타입에 따라 ball에게 충돌정보를 줄 것 입니다.
		- ball의 위치는 (0, y, z)의 형태일 것이며 z는 음수이며 고정되어 있을 것입니다. y값은 공이 떨어지면서 변할 것입니다.
		다음의 Tip을 참고하십시오.
		- 이 타일의 Trnasform의 rotation에 접근하여 충돌 판정이 되는 각도인지 확인하십시오.
		- 공의 radius와 높이 그리고 이 타일의 높이를 비교하십시오
		다음 주의사항을 참고하십시오.
		- 타일의 중심각도, 공의 radius는 모델 크기와 맞지 않을 수 있습니다. 충돌알고리즘을 작성하고 크기를 조절하면서 맞추십시오.
		*/

		auto tileTransform = GetBelongingTransform();		
		auto tileAngle = tileTransform->GetWorldRotation();				// 로컬 로테이션 -> 월드 로테이션
		auto tilePosition = tileTransform->GetWorldPosition();			// 로컬 포지션 -> 월드 포지션
		auto ballPosition = ballTransform->GetWorldPosition();			// 로컬 포지션 -> 월드 포지션
		auto ballRigidbody = ball->GetComponent<Rigidbody>();
		auto rigidbody = ballRigidbody->GetPresentDirection();

		if (tileAngle.y > 360)
			tileAngle.y = tileAngle.y - 360;
		else if (tileAngle.y < -360)
			tileAngle.y = tileAngle.y + 360;
	
		if (tileAngle.y <= 0 && tileAngle.y >= -45 || tileAngle.y >= 315 && tileAngle.y <= 360)
		{
			if (ballPosition.y - ballBall->radius <= tilePosition.y && ballPosition.y - ballBall->radius >= tilePosition.y - 1)
			{
				isCollide = true;
			}
		}
		else
		{
			isCollide = false;
		}
		
		if (isCollide == true && rigidbody.y < 0)
		{
			switch (type)
			{
			case TileType::BLACK:
				ballBall->Bounce(this);
				break;
			case TileType::RED:
				ballBall->Damage(this);
				break;
			case TileType::BIGGER:
				ballBall->Bigger(this);
				break;
			case TileType::LIGHTER:
				ballBall->Lighter(this);
				break;
			default:
				break;
			}
		}

	}
}

Object* Tile::InstantiateRedFragTile()
{
	static std::shared_ptr<ModelInstance> tileInLeftModel;
	static std::shared_ptr<ModelInstance> tileInRightModel;
	static std::shared_ptr<ModelInstance> tileOutLeftModel;
	static std::shared_ptr<ModelInstance> tileOutRightModel;
	if (tileInLeftModel == nullptr)
	{
		ResourceSystem& rs = ResourceSystem::GetInstance();
		tileInLeftModel = rs.GetCopiedModelInstance("Pizza_InLeft.obj");
		tileInLeftModel->SetColor(glm::vec3(0.8, 0.2, 0.2));
		tileInLeftModel->UpdateBuffer();

		tileInRightModel = rs.GetCopiedModelInstance("Pizza_InRight.obj");
		tileInRightModel->SetColor(glm::vec3(0.8, 0.2, 0.2));
		tileInRightModel->UpdateBuffer();

		tileOutLeftModel = rs.GetCopiedModelInstance("Pizza_OutLeft.obj");
		tileOutLeftModel->SetColor(glm::vec3(0.8, 0.2, 0.2));
		tileOutLeftModel->UpdateBuffer();

		tileOutRightModel = rs.GetCopiedModelInstance("Pizza_OutRight.obj");
		tileOutRightModel->SetColor(glm::vec3(0.8, 0.2, 0.2));
		tileOutRightModel->UpdateBuffer();
	}

	//--- Parent
	auto parent = new Object();
	//Transform
	auto parentTransform = parent->GetTransform();
	//Frag
	auto parentFrag = parent->AddComponent<Frag>();

	//--- Frag
	for (int i = 0; i < 4; ++i)
	{
		std::shared_ptr<ModelInstance> model = nullptr;
		glm::vec3 direction;
		glm::vec3 torque;
		switch (i)
		{
		case 0:
			model = tileInLeftModel;
			torque = glm::vec3(10, 50, -5);
			direction = glm::vec3(0, 8, 10);
			break;
		case 1:
			model = tileInRightModel;
			torque = glm::vec3(0, -50, 50);
			direction = glm::vec3(0, 10, 0);
			break;
		case 2:
			model = tileOutLeftModel;
			torque = glm::vec3(50, 50, -5);
			direction = glm::vec3(0, 5, 0);
			break;
		case 3:
			model = tileOutRightModel;
			torque = glm::vec3(-50, -50, 50);
			direction = glm::vec3(10, 10, 0);
			break;
		}

		auto tile = new Object();
		//Transform
		auto tileTransform = tile->GetTransform();
		tileTransform->SetParent(parentTransform);
		//Renderer
		auto tileRenderer = tile->AddComponent<Renderer>();
		tileRenderer->SetTargetShader(ShaderType::VERTEX_ELEMENT);
		tileRenderer->SetOwnModel(model);
		//Rigidbody
		auto tileRigidbody = tile->AddComponent<Rigidbody>();
		tileRigidbody->AddForce(direction);
		tileRigidbody->AddTorque(torque);
	}


	return parent;
}

Object* Tile::InstantiateBlackFragTile()
{
	static std::shared_ptr<ModelInstance> tileInLeftModel;
	static std::shared_ptr<ModelInstance> tileInRightModel;
	static std::shared_ptr<ModelInstance> tileOutLeftModel;
	static std::shared_ptr<ModelInstance> tileOutRightModel;
	if (tileInLeftModel == nullptr)
	{
		ResourceSystem& rs = ResourceSystem::GetInstance();
		tileInLeftModel = rs.GetCopiedModelInstance("Pizza_InLeft.obj");
		tileInLeftModel->SetColor(glm::vec3(0.1, 0.1, 0.1));
		tileInLeftModel->UpdateBuffer();

		tileInRightModel = rs.GetCopiedModelInstance("Pizza_InRight.obj");
		tileInRightModel->SetColor(glm::vec3(0.1, 0.1, 0.1));
		tileInRightModel->UpdateBuffer();

		tileOutLeftModel = rs.GetCopiedModelInstance("Pizza_OutLeft.obj");
		tileOutLeftModel->SetColor(glm::vec3(0.1, 0.1, 0.1));
		tileOutLeftModel->UpdateBuffer();

		tileOutRightModel = rs.GetCopiedModelInstance("Pizza_OutRight.obj");
		tileOutRightModel->SetColor(glm::vec3(0.1, 0.1, 0.1));
		tileOutRightModel->UpdateBuffer();
	}

	//--- Parent
	auto parent = new Object();
	//Transform
	auto parentTransform = parent->GetTransform();
	//Frag
	auto parentFrag = parent->AddComponent<Frag>();

	//--- Frag
	for (int i = 0; i < 4; ++i)
	{
		std::shared_ptr<ModelInstance> model = nullptr;
		glm::vec3 direction;
		glm::vec3 torque;
		switch (i)
		{
		case 0:
			model = tileInLeftModel;
			torque = glm::vec3(0, 50, 5);
			direction = glm::vec3(0, 8, 0);
			break;
		case 1:
			model = tileInRightModel;
			torque = glm::vec3(0, -50, 50);
			direction = glm::vec3(0, 10, 0);
			break;
		case 2:
			model = tileOutLeftModel;
			torque = glm::vec3(50, 50, -5);
			direction = glm::vec3(0, 5, 0);
			break;
		case 3:
			model = tileOutRightModel;
			torque = glm::vec3(-50, -50, 50);
			direction = glm::vec3(0, 5, 0);
			break;
		}

		auto tile = new Object();
		//Transform
		auto tileTransform = tile->GetTransform();
		tileTransform->SetParent(parentTransform);
		//Renderer
		auto tileRenderer = tile->AddComponent<Renderer>();
		tileRenderer->SetTargetShader(ShaderType::VERTEX_ELEMENT);
		tileRenderer->SetOwnModel(model);
		//Rigidbody
		auto tileRigidbody = tile->AddComponent<Rigidbody>();
		tileRigidbody->AddForce(direction);
		tileRigidbody->AddTorque(torque);
	}


	return parent;
}
