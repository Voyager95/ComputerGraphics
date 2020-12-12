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
#include "ModelInstnce.h"

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
}

void TermProject::SpawnTower()
{
	if (m_Ball == nullptr || m_Tower.size() < 1)
		return;
	auto ballTransform = m_Ball->GetTransform();
	auto towerIndex = m_Tower.size() - 1;
	auto tower = m_Tower[towerIndex];
	auto towerTransform = tower->GetTransform();

	auto spawnPosition = towerTransform->GetWorldPosition().y + towerInstantiateOffset;
	std::cout << "생성 위치: " << spawnPosition << " 공 위치: " << ballTransform->GetWorldPosition().y << std::endl;
	if ( spawnPosition > ballTransform->GetWorldPosition().y)
	{
		std::cout << "타워 생성 됨" << std::endl;

		auto instancedTower = InstantiateTower();
		m_Tower.emplace_back(instancedTower);
		auto instancedTowerTransform = instancedTower->GetTransform();
		//- 타워 위치 조정
		auto desiredPos = glm::vec3(0,towerTransform->GetWorldPosition().y - TOWERHEIGHT,0 );
		instancedTowerTransform->SetWorldPosition(desiredPos);
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
}

void TermProject::InitializeDiscCombination()
{
	std::array<int, DISCNUMPERTOWER> tmp;

	//---Index NO.00
	tmp[0] = 1;
	tmp[1] = 0;
	tmp[2] = 3;
	tmp[3] = 2;
	tmp[4] = 1;
	tmp[5] = 2;
	tmp[6] = 0;
	tmp[7] = 1;
	discList.push_back(tmp);

	//---Index NO.01
	tmp[0] = 1;
	tmp[1] = 0;
	tmp[2] = 3;
	tmp[3] = 2;
	tmp[4] = 1;
	tmp[5] = 2;
	tmp[6] = 0;
	tmp[7] = 1;
	discList.push_back(tmp);

	//---Index NO.02
	tmp[0] = 1;
	tmp[1] = 0;
	tmp[2] = 3;
	tmp[3] = 2;
	tmp[4] = 1;
	tmp[5] = 2;
	tmp[6] = 0;
	tmp[7] = 1;
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
	ball->AddComponent<Rigidbody>();
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

Object* TermProject::InstantiateBiggerItem()
{
	return nullptr;
}

Object* TermProject::InstantiateLighterItem()
{
	return nullptr;
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
	auto tower = new Object();
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
	Object* disc = new Object();
	disc->name = "디스크";

	float yRotate = 0;

	for (int i = 0; i < TILENUMPERDDISC; ++i)
	{
		if (discCom[i] != TileGenerate::NONE)
		{
			Object* tile = nullptr;
			//-- 타일 생성
			if (discCom[i] == TileGenerate::BLACK)
				tile = InstantiateBlackTile();
			else
				tile = InstantiateRedTile();
			tile->name = "타일" + i;
			//Transform
			auto tileTransform = tile->GetTransform();
			tileTransform->SetParent(disc->GetTransform());
			tileTransform->rotation.y = yRotate;
		}

		yRotate += 45;
	}

	return disc;
}
