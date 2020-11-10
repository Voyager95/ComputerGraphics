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

Exercise17::Exercise17()
{
	ResourceSystem& rs = ResourceSystem::GetInstance();


	////--- Camera 생성
	std::shared_ptr<Object> camera = GlobalUtility::CreateObject();
	std::cout << "참조" << camera.use_count() << "컴포넌트 사이즈" << camera->GetComponents().size() << std::endl;
	auto z = camera->GetTransform();
	z->position.y += 0.5f;
	z->rotation.y += 45;
	z->rotation.z += 45;
	auto c = std::make_shared<Camera>(1, camera);
	camera->AddComponent(c);
	AddObject(camera);

	std::cout << "참조" << camera.use_count() << "컴포넌트 사이즈" << camera->GetComponents().size() << std::endl;


	//--- Cube 생성
	std::shared_ptr<Object> cube = GlobalUtility::CreateObject();
	auto t = cube->GetTransform();
	t->position.y += 0.5f;
	t->rotation.y += 45;
	t->rotation.z += 45;
	std::cout << t->GetBelongingObject()->name << std::endl;
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
	AddObject(cube);

}
