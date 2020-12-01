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
	//--- Ball
	auto ball = InstantiateBall();
	//Transform
	auto ballTransform = ball->GetTransform();
	ballTransform->position = glm::vec3(0, 15, -6);
	AddObject(ball);

	//--- Camera
	auto camera = new Object("Camera");
	//Transform
	auto cameraTransform = camera->GetTransform();
	//cameraTransform->parent = ballTransform;
	cameraTransform->rotation = glm::vec3(15, 0, 0);
	cameraTransform->position = glm::vec3(0, 10, -50);
	//Camera
	camera->AddComponent<Camera>();
	AddObject(camera);

	//--- Tower
	auto tower = InstantiateTower();
	//Transform
	auto towerTransform = tower->GetTransform();
	towerTransform->position.y -= 10;
	AddObject(tower);

	//--- Tile
	auto tile = InstantiateBlackTile();
	//Transform
	auto tileTransform = tile->GetTransform();
	tileTransform->rotation.y = -22.5;
	AddObject(tile);
}

void TermProject::OnUpdate()
{
	InputSystem& is = InputSystem::GetInstance();

	float rotate = 0;
	if (is.GetKey('A'))
		rotate += -1;
	if (is.GetKey('D'))
		rotate += 1;

	if (m_Tower.empty() != true)
	{
		for (auto i = m_Tower.begin(); i != m_Tower.end(); ++i)
		{
			auto t = (*i)->GetTransform();

			t->rotation += m_TowerRotateSpeed * rotate * DELTATIME;
		}
	}
}

Object* InstantiateBall()
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

Object* InstantiateBlackTile()
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

Object* InstantiateRedTile()
{
	auto tile = new Object();
	//Tile
	auto tileTile = tile->AddComponent<Tile>();
	tileTile->type = TileType::RED;
	//Renderer
	auto tileRenderer = tile->AddComponent<Renderer>();
	tileRenderer->SetSharedModel("Tile.obj");
	tileRenderer->SetSharedTextrue("Red.png");
	tileRenderer->SetTargetShader(ShaderType::TEXTURE_ELEMENT);

	return tile;
}

Object* InstantiateBiggerItem()
{
	return nullptr;
}

Object* InstantiateLighterItem()
{
	return nullptr;
}

Object* InstantiateTower()
{
	static std::shared_ptr<ModelInstance> towerModel;
	if (towerModel == nullptr)
	{
		ResourceSystem& rs = ResourceSystem::GetInstance();
		towerModel = rs.GetCopiedModelInstance("Tower.obj");
		towerModel->SetColor(glm::vec3(0, 0.5, 0.5));
		towerModel->UpdateBuffer();
	}

	auto tower = new Object();
	//Renderer
	auto towerRenderer = tower->AddComponent<Renderer>();
	towerRenderer->SetOwnModel(towerModel);
	towerRenderer->SetTargetShader(ShaderType::VERTEX_ELEMENT);

	return tower;
}

Object* InstnatiateDisc()
{
	return nullptr;
}
