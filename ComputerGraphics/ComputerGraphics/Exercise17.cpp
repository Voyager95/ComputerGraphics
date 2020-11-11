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


	////--- Camera 생성
	std::shared_ptr<Object> camera = GlobalUtility::CreateObject();
	std::cout << "참조" << camera.use_count() << "컴포넌트 사이즈" << camera->GetComponents().size() << std::endl;
	auto z = camera->GetTransform();
	z->position.y += 15.0f;
	z->position.z += -10.0f;
	z->rotation.x += 45;
	auto c = std::make_shared<Camera>(1, camera);
	camera->AddComponent(c);
	AddObject(camera);

	std::cout << "참조" << camera.use_count() << "컴포넌트 사이즈" << camera->GetComponents().size() << std::endl;


	////--- Cube 생성
	//std::shared_ptr<Object> cube = GlobalUtility::CreateObject();
	////-- Transform
	//auto cubeTransform = cube->GetTransform();
	//cubeTransform->position.z += 30;
	//cubeTransform->scale *= 10;
	////-- Renderer
	//auto cubeRenderer = std::make_shared<Renderer>(cube);
	//cube->AddComponent(cubeRenderer);
	//auto model = rs.GetCopiedModelInstance("tree.obj");
	//model->RandomColor();
	//model->UpdateBuffer();
	//cubeRenderer->SetOwnModel(model);
	//cubeRenderer->SetSharedTextrue("tree.png");
	////-- Rotator
	//auto cubeRotator = std::make_shared<Rotator>(cube);
	//cube->AddComponent(cubeRotator);
	//cubeRotator->speed = 1;
	//cubeRotator->direction = glm::vec3(0, 10, 0);
	//AddObject(cube);

	//--- Plane 생성
	std::shared_ptr<Object> plane = GlobalUtility::CreateObject();
	//-- Transform
	auto planeTransform = plane->GetTransform();
	planeTransform->scale *= 25;
	//-- Randerer
	auto planeRenderer = std::make_shared<Renderer>(plane);
	plane->AddComponent(planeRenderer);
	planeRenderer->SetSharedModel("plane.obj");
	planeRenderer->SetSharedTextrue("plane.png");
	AddObject(plane);
}
