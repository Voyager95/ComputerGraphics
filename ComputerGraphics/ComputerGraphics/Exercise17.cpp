#include "stdafx.h"
#include "Exercise17.h"
#include "stdafx.h"
#include "Scene.h"
#include "Object.h"
#include "Renderer.h"
#include "Transform.h"
#include "ModelInstnce.h"
#include "ResourceSystem.h"
#include "Camera.h"
#include "Rotator.h"

Exercise17::Exercise17()
{
	ResourceSystem& rs = ResourceSystem::GetInstance();


	////--- Camera ����
	std::shared_ptr<Object> camera = GlobalUtility::CreateObject();
	std::cout << "����" << camera.use_count() << "������Ʈ ������" << camera->GetComponents().size() << std::endl;
	auto z = camera->GetTransform();
	z->position.y += 0.5f;
	z->position.z += -1.0f;
	z->rotation.x += 45;
	//z->rotation.z += 45;
	auto c = std::make_shared<Camera>(1, camera);
	camera->AddComponent(c);
	AddObject(camera);

	std::cout << "����" << camera.use_count() << "������Ʈ ������" << camera->GetComponents().size() << std::endl;


	//--- Cube ����
	std::shared_ptr<Object> cube = GlobalUtility::CreateObject();
	//-- Renderer
	auto cubeRenderer = std::make_shared<Renderer>(cube);
	cube->AddComponent(cubeRenderer);
	auto model = rs.GetCopiedModelInstance("cube.obj");
	for (auto i = model->verticesPos.begin(); i != model->verticesPos.end(); ++i)
	{
		*i *= 0.3; 
	}
	model->RandomColor();
	model->UpdateBuffer();
	cubeRenderer->SetOwnModel(model);
	//-- Rotator
	auto cubeRotator = std::make_shared<Rotator>(cube);
	cube->AddComponent(cubeRotator);
	cubeRotator->speed = 1;
	cubeRotator->direction = glm::vec3(0, 10, 0);
	AddObject(cube);

}
