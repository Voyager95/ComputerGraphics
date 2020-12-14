#include "stdafx.h"
#include "TermProject.h"
#include "Object.h"
#include "Ball.h"
#include "Rigidbody.h"
#include "Tile.h"
#include "Renderer.h"
#include "InputSystem.h"
#include "Transform.h"
#include "Camera.h"
#include "ResourceSystem.h"
#include "SceneSystem.h"
#include "ModelInstnce.h"
#include "Frag.h"

TermProject::TermProject()
{
	std::srand(time(NULL));

	//--- 초기화
	InitializeDiscSetting();
	InitializeDiscCombination();

	//--- Ball
	auto ball = InstantiateBall();
	m_Ball = ball;
	//Transform
	auto ballTransform = ball->GetTransform();
	ballTransform->position = glm::vec3(0, 0, -6);
	AddObject(ball);

	//--- Camera
	auto camera = new Object("Camera");
	//Transform
	auto cameraTransform = camera->GetTransform();
	cameraTransform->SetParent(ballTransform);
	cameraTransform->rotation = glm::vec3(15, 0, 0);
	cameraTransform->position = glm::vec3(0, 10, -50);
	//Camera
	camera->AddComponent<Camera>();
	AddObject(camera);

	//--- Initial Tower
	auto tower = InstantiateTower(0);
	m_Tower.emplace_back(tower);
	//Transform
	auto towerTransform = tower->GetTransform();
	towerTransform->position.y = -80;
	AddObject(tower);
}

void TermProject::OnUpdate()
{
	m_Timer += DELTATIME;

	//--- 키 입력 처리
	InputSystem& is = InputSystem::GetInstance();
	//-- 키
	float rotate = 0;
	if (is.GetKey('A'))
		rotate += -1;
	if (is.GetKey('D'))
		rotate += 1;
	//-- 적용
	if (m_Tower.empty() != true)
	{
		for (auto i = m_Tower.begin(); i != m_Tower.end(); ++i)
		{
			auto t = (*i)->GetTransform();

			t->rotation.y += m_TowerRotateSpeed * rotate * DELTATIME;
		}
	}

	//--- 생성 체크
	SpawnTower();

	//--- 삭제 체크
	DeleteTower();
}

void TermProject::DeleteTower()
{
	SceneSystem& ss = SceneSystem::GetInstance();
	auto presentScene = ss.GetPresentScene();

	if (m_Ball == nullptr || m_Tower.size() < 1)
		return;

	auto ballPos = m_Ball->GetTransform()->position;

	auto tower = m_Tower.begin();

	while (tower != m_Tower.end())
	{
		auto towerPos = (*tower)->GetTransform()->position;

		if (towerPos.y > ballPos.y + towerDeleteOffset)
		{
			auto target = *tower;
			tower =m_Tower.erase(tower);
			presentScene->SubObject(target);
		}
		else
		{
			tower++;
		}
	}
}

void TermProject::SpawnTower()
{
	SceneSystem& ss = SceneSystem::GetInstance();
	auto presentScene = ss.GetPresentScene();

	if (m_Ball == nullptr || m_Tower.size() < 1)
		return;
	auto ballTransform = m_Ball->GetTransform();
	auto towerIndex = m_Tower.size() - 1;
	auto tower = m_Tower[towerIndex];
	auto towerTransform = tower->GetTransform();

	auto spawnPosition = towerTransform->GetWorldPosition().y + towerInstantiateOffset;

	if ( spawnPosition > ballTransform->GetWorldPosition().y)
	{
		std::cout << "타워 생성 됨" << std::endl;

		auto instancedTower = InstantiateTower();
		m_Tower.emplace_back(instancedTower);
		auto instancedTowerTransform = instancedTower->GetTransform();
		//- 타워 위치 조정
		auto desiredPos = glm::vec3(0,towerTransform->GetWorldPosition().y - TOWERHEIGHT,0 );
		instancedTowerTransform->SetWorldPosition(desiredPos);

		presentScene->AddObject(instancedTower);
	}
}

void TermProject::InitializeDiscSetting()
{
	std::array<TileGenerate, TILENUMPERDDISC> tmp;

	//---Index NO.00
	tmp[0] = TileGenerate::BLACK;
	tmp[1] = TileGenerate::BLACK;
	tmp[2] = TileGenerate::NONE;
	tmp[3] = TileGenerate::BLACK;
	tmp[4] = TileGenerate::BLACK;
	tmp[5] = TileGenerate::NONE;
	tmp[6] = TileGenerate::BLACK;
	tmp[7] = TileGenerate::BLACK;
	discSetting.push_back(tmp);

	//---Index NO.01
	tmp[0] = TileGenerate::BLACK;
	tmp[1] = TileGenerate::BLACK;
	tmp[2] = TileGenerate::BLACK;
	tmp[3] = TileGenerate::BLACK;
	tmp[4] = TileGenerate::NONE;
	tmp[5] = TileGenerate::BLACK;
	tmp[6] = TileGenerate::BLACK;
	tmp[7] = TileGenerate::BLACK;
	discSetting.push_back(tmp);

	//---Index NO.02
	tmp[0] = TileGenerate::NONE;
	tmp[1] = TileGenerate::BLACK;
	tmp[2] = TileGenerate::BLACK;
	tmp[3] = TileGenerate::RED;
	tmp[4] = TileGenerate::BLACK;
	tmp[5] = TileGenerate::BLACK;
	tmp[6] = TileGenerate::BLACK;
	tmp[7] = TileGenerate::BLACK;
	discSetting.push_back(tmp);

	//---Index NO.03
	tmp[0] = TileGenerate::BLACK;
	tmp[1] = TileGenerate::BLACK;
	tmp[2] = TileGenerate::BLACK;
	tmp[3] = TileGenerate::BLACK;
	tmp[4] = TileGenerate::RED;
	tmp[5] = TileGenerate::BLACK;
	tmp[6] = TileGenerate::BLACK;
	tmp[7] = TileGenerate::NONE;
	discSetting.push_back(tmp);

	//---Index NO.04
	tmp[0] = TileGenerate::BLACK;
	tmp[1] = TileGenerate::NONE;
	tmp[2] = TileGenerate::BLACK;
	tmp[3] = TileGenerate::BLACK;
	tmp[4] = TileGenerate::NONE;
	tmp[5] = TileGenerate::BLACK;
	tmp[6] = TileGenerate::BLACK;
	tmp[7] = TileGenerate::RED;
	discSetting.push_back(tmp);

	//---Index NO.05
	tmp[0] = TileGenerate::BLACK;
	tmp[1] = TileGenerate::NONE;
	tmp[2] = TileGenerate::BLACK;
	tmp[3] = TileGenerate::BLACK;
	tmp[4] = TileGenerate::NONE;
	tmp[5] = TileGenerate::BLACK;
	tmp[6] = TileGenerate::BLACK;
	tmp[7] = TileGenerate::RED;
	discSetting.push_back(tmp);

	//---Index NO.06
	tmp[0] = TileGenerate::RED;
	tmp[1] = TileGenerate::BLACK;
	tmp[2] = TileGenerate::BLACK;
	tmp[3] = TileGenerate::BLACK;
	tmp[4] = TileGenerate::RED;
	tmp[5] = TileGenerate::BLACK;
	tmp[6] = TileGenerate::BLACK;
	tmp[7] = TileGenerate::NONE;
	discSetting.push_back(tmp);

	//---Index NO.07
	tmp[0] = TileGenerate::RED;
	tmp[1] = TileGenerate::BLACK;
	tmp[2] = TileGenerate::NONE;
	tmp[3] = TileGenerate::BLACK;
	tmp[4] = TileGenerate::RED;
	tmp[5] = TileGenerate::BLACK;
	tmp[6] = TileGenerate::RED;
	tmp[7] = TileGenerate::BLACK;
	discSetting.push_back(tmp);

	//---Index NO.08
	tmp[0] = TileGenerate::BLACK;
	tmp[1] = TileGenerate::BLACK;
	tmp[2] = TileGenerate::RED;
	tmp[3] = TileGenerate::BLACK;
	tmp[4] = TileGenerate::BLACK;
	tmp[5] = TileGenerate::RED;
	tmp[6] = TileGenerate::BLACK;
	tmp[7] = TileGenerate::NONE;
	discSetting.push_back(tmp);

	//---Index NO.09
	tmp[0] = TileGenerate::NONE;
	tmp[1] = TileGenerate::BLACK;
	tmp[2] = TileGenerate::BLACK;
	tmp[3] = TileGenerate::RED;
	tmp[4] = TileGenerate::BLACK;
	tmp[5] = TileGenerate::NONE;
	tmp[6] = TileGenerate::BLACK;
	tmp[7] = TileGenerate::RED;
	discSetting.push_back(tmp);

	//---Index NO.10
	tmp[0] = TileGenerate::NONE;
	tmp[1] = TileGenerate::BLACK;
	tmp[2] = TileGenerate::NONE;
	tmp[3] = TileGenerate::BIGGER;
	tmp[4] = TileGenerate::BLACK;
	tmp[5] = TileGenerate::NONE;
	tmp[6] = TileGenerate::LIGHTER;
	tmp[7] = TileGenerate::RED;
	discSetting.push_back(tmp);
}

void TermProject::InitializeDiscCombination()
{
	std::array<int, DISCNUMPERTOWER> tmp;

	//---Index NO.00
	tmp[0] = 1;
	tmp[1] = 4;
	tmp[2] = 10;
	tmp[3] = 2;
	tmp[4] = 1;
	tmp[5] = 10;
	tmp[6] = 0;
	tmp[7] = 1;
	discList.push_back(tmp);

	//---Index NO.01
	tmp[0] = 4;
	tmp[1] = 3;
	tmp[2] = 6;
	tmp[3] = 1;
	tmp[4] = 0;
	tmp[5] = 5;
	tmp[6] = 2;
	tmp[7] = 4;
	discList.push_back(tmp);

	//---Index NO.02
	tmp[0] = 2;
	tmp[1] = 4;
	tmp[2] = 1;
	tmp[3] = 5;
	tmp[4] = 7;
	tmp[5] = 6;
	tmp[6] = 3;
	tmp[7] = 0;
	discList.push_back(tmp);

	//---Index NO.03
	tmp[0] = 7;
	tmp[1] = 6;
	tmp[2] = 3;
	tmp[3] = 8;
	tmp[4] = 7;
	tmp[5] = 4;
	tmp[6] = 2;
	tmp[7] = 5;
	discList.push_back(tmp);

	//---Index NO.04
	tmp[0] = 5;
	tmp[1] = 2;
	tmp[2] = 7;
	tmp[3] = 6;
	tmp[4] = 4;
	tmp[5] = 9;
	tmp[6] = 3;
	tmp[7] = 8;
	discList.push_back(tmp);

	//---Index NO.05
	tmp[0] = 9;
	tmp[1] = 7;
	tmp[2] = 6;
	tmp[3] = 2;
	tmp[4] = 8;
	tmp[5] = 9;
	tmp[6] = 4;
	tmp[7] = 8;
	discList.push_back(tmp);
}

Object* TermProject::InstantiateBall()
{
	static std::shared_ptr<ModelInstance> ballModel;	
	if (ballModel == nullptr)
	{
		ResourceSystem& rs = ResourceSystem::GetInstance();
		ballModel = rs.GetCopiedModelInstance("Ball.obj");
		ballModel->SetColor(glm::vec3(0.5,0.5,0));
		ballModel->UpdateBuffer();
	}

	//--- Ball
	auto ball = new Object("Ball");
	//Ball
	ball->AddComponent<Ball>();
	//Rigidbody
	auto ballRigidbody = ball->AddComponent<Rigidbody>();
	ballRigidbody->gravitylimitSpeed = 20.0f;
	ballRigidbody->gravityMultiples = 2.0f;
	//Renderer
	auto ballRenderer = ball->AddComponent<Renderer>();	
	ballRenderer->SetTargetShader(ShaderType::VERTEX_ELEMENT);
	ballRenderer->SetOwnModel(ballModel);

	return ball;
}

Object* TermProject::InstantiateBlackTile()
{
	static std::shared_ptr<ModelInstance> blackTileModel;
	if (blackTileModel == nullptr)
	{
		ResourceSystem& rs = ResourceSystem::GetInstance();
		blackTileModel = rs.GetCopiedModelInstance("Pizza.obj");
		blackTileModel->SetColor(glm::vec3(0.1, 0.1, 0.1));
		blackTileModel->UpdateBuffer();
	}

	auto tile = new Object();
	//Tile
	auto tileTile = tile->AddComponent<Tile>();
	tileTile->type = TileType::BLACK;
	//Renderer
	auto tileRenderer = tile->AddComponent<Renderer>();
	tileRenderer->SetTargetShader(ShaderType::VERTEX_ELEMENT);
	tileRenderer->SetOwnModel(blackTileModel);

	return tile;
}

Object* TermProject::InstantiateBlackTileFrag()
{
	return nullptr;
}

Object* TermProject::InstantiateRedTile()
{
	static std::shared_ptr<ModelInstance> redTileModel;
	if (redTileModel == nullptr)
	{
		ResourceSystem& rs = ResourceSystem::GetInstance();
		redTileModel = rs.GetCopiedModelInstance("Pizza.obj");
		redTileModel->SetColor(glm::vec3(0.8, 0.2, 0.2));
		redTileModel->UpdateBuffer();
	}

	auto tile = new Object();
	//Tile
	auto tileTile = tile->AddComponent<Tile>();
	tileTile->type = TileType::RED;
	//Renderer
	auto tileRenderer = tile->AddComponent<Renderer>();
	tileRenderer->SetTargetShader(ShaderType::VERTEX_ELEMENT);
	tileRenderer->SetOwnModel(redTileModel);

	return tile;
}

Object* TermProject::InstantiateRedTileFrag()
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
			torque = glm::vec3(0,50,5);
			direction = glm::vec3(0, 30, 0);
			break;
		case 1:
			model = tileInRightModel;
			torque = glm::vec3(0, 50, 50);
			direction = glm::vec3(0, 30, 0);
			break;
		case 2:
			model = tileOutLeftModel;
			torque = glm::vec3(50, 50, 5);
			direction = glm::vec3(0, 30, 0);
			break;
		case 3:
			model = tileOutRightModel;
			torque = glm::vec3(50, 50, 50);
			direction = glm::vec3(0, 30, 0);
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

Object* TermProject::InstantiateBiggerTile()
{
	static std::shared_ptr<ModelInstance> BiggerTileModel;
	if (BiggerTileModel == nullptr)
	{
		ResourceSystem& rs = ResourceSystem::GetInstance();
		BiggerTileModel = rs.GetCopiedModelInstance("Tile_Bigger.obj");
		BiggerTileModel->SetColor(glm::vec3(0.2, 0.2, 0.2));
		BiggerTileModel->UpdateBuffer();
	}

	auto tile = new Object();
	//Tile
	auto tileTile = tile->AddComponent<Tile>();
	tileTile->type = TileType::BIGGER;
	//Renderer
	auto tileRenderer = tile->AddComponent<Renderer>();
	tileRenderer->SetTargetShader(ShaderType::VERTEX_ELEMENT);
	tileRenderer->SetOwnModel(BiggerTileModel);

	return tile;
}

Object* TermProject::InstantiateLighterTile()
{
	static std::shared_ptr<ModelInstance> BiggerTileModel;
	if (BiggerTileModel == nullptr)
	{
		ResourceSystem& rs = ResourceSystem::GetInstance();
		BiggerTileModel = rs.GetCopiedModelInstance("Tile_Lighter.obj");
		BiggerTileModel->SetColor(glm::vec3(0.8, 0.8, 0.8));
		BiggerTileModel->UpdateBuffer();
	}

	auto tile = new Object();
	//Tile
	auto tileTile = tile->AddComponent<Tile>();
	tileTile->type = TileType::LIGHTER;
	//Renderer
	auto tileRenderer = tile->AddComponent<Renderer>();
	tileRenderer->SetTargetShader(ShaderType::VERTEX_ELEMENT);
	tileRenderer->SetOwnModel(BiggerTileModel);

	return tile;
}

Object* TermProject::InstantiateTower()
{
	int count = discList.size();

	int index = std::rand() % count;

	auto tower = InstantiateTower(index);

	return tower;
}

Object* TermProject::InstantiateTower(int index)
{
	//--- 타워모델 생성
	static std::shared_ptr<ModelInstance> towerModel;
	if (towerModel == nullptr)
	{
		ResourceSystem& rs = ResourceSystem::GetInstance();
		towerModel = rs.GetCopiedModelInstance("Tower.obj");
		towerModel->SetColor(glm::vec3(0, 0.5, 0.5));
		towerModel->UpdateBuffer();
	}

	//--- Tower
	auto tower = new Object("타워");
	//Renderer
	auto towerRenderer = tower->AddComponent<Renderer>();
	towerRenderer->SetOwnModel(towerModel);
	towerRenderer->SetTargetShader(ShaderType::VERTEX_ELEMENT);

	//--- 디스크 리스크
	std::array<std::array<TileGenerate, TILENUMPERDDISC>, DISCNUMPERTOWER> discListInstance;
	auto selectedList = discList[index];
	for (int i = 0; i < DISCNUMPERTOWER; ++i)
	{
		discListInstance[i] = discSetting[selectedList[i]];
	}

	//--- 디스크 생성
	float discYPosition = 0.0f;
	for (int i = 0; i < DISCNUMPERTOWER; ++i)
	{
		discYPosition += 10;
		//-- Disc
		auto discInstance = InstantiateDisc(discListInstance[i]);
		discInstance->name = "디스크" + i;
		//Transform
		auto discInstanceTransform = discInstance->GetTransform();
		discInstanceTransform->SetParent(tower);
		discInstanceTransform->position.y = discYPosition;
	}

	return tower;
}

Object* TermProject::InstantiateDisc(std::array<TileGenerate, TILENUMPERDDISC> discCom)
{
	Object* disc = new Object("디스크");

	float yRotate = 0;

	for (int i = 0; i < TILENUMPERDDISC; ++i)
	{
		if (discCom[i] != TileGenerate::NONE)
		{
			Object* tile = nullptr;
			//-- 타일 생성
			switch (discCom[i])
			{
			case TileGenerate::BIGGER:
				tile = InstantiateBiggerTile();
				break;
			case TileGenerate::BLACK:
				tile = InstantiateBlackTile();
				break;
			case TileGenerate::LIGHTER:
				tile = InstantiateLighterTile();
				break;
			case TileGenerate::RED:
				tile = InstantiateRedTile();
				break;
			}
			tile->name = "타일";
			//Transform
			auto tileTransform = tile->GetTransform();
			tileTransform->SetParent(disc->GetTransform());
			tileTransform->rotation.y = yRotate;
		}

		yRotate += 45;
	}

	return disc;
}
