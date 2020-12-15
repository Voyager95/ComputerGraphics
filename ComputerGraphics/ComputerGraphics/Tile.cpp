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
	
	//--- �浹 üũ�մϴ�. 
	if (ball != nullptr)
	{
		bool isCollide = false;								// �浹���� �÷����Դϴ�.

		auto ballBall = ball->GetComponent<Ball>();			// ball�� Ball ������Ʈ�Դϴ�.
		auto ballTransform = ball->GetTransform();			// ball�� Transform ������Ʈ�Դϴ�.

		/*
		���⿡ �浹�ϴ� �˰����� �ۼ��ϸ� �˴ϴ�.
		������ �۵������ �����Ͻʽÿ�.
		- isCollide������ �⺻������ false������ ���Դϴ�. ���� �浹�ϸ� true�� �����Ͻʽÿ�
		- isCollide������ true�� �Ǹ� �� Ÿ���� Ÿ�Կ� ���� ball���� �浹������ �� �� �Դϴ�.
		- ball�� ��ġ�� (0, y, z)�� ������ ���̸� z�� �����̸� �����Ǿ� ���� ���Դϴ�. y���� ���� �������鼭 ���� ���Դϴ�.
		������ Tip�� �����Ͻʽÿ�.
		- �� Ÿ���� Trnasform�� rotation�� �����Ͽ� �浹 ������ �Ǵ� �������� Ȯ���Ͻʽÿ�.
		- ���� radius�� ���� �׸��� �� Ÿ���� ���̸� ���Ͻʽÿ�
		���� ���ǻ����� �����Ͻʽÿ�.
		- Ÿ���� �߽ɰ���, ���� radius�� �� ũ��� ���� ���� �� �ֽ��ϴ�. �浹�˰����� �ۼ��ϰ� ũ�⸦ �����ϸ鼭 ���߽ʽÿ�.
		*/

		auto tileTransform = GetBelongingTransform();		
		auto tileAngle = tileTransform->GetWorldRotation();				// ���� �����̼� -> ���� �����̼�
		auto tilePosition = tileTransform->GetWorldPosition();			// ���� ������ -> ���� ������
		auto ballPosition = ballTransform->GetWorldPosition();			// ���� ������ -> ���� ������
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
