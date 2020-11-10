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
	auto c = std::make_shared<Camera>(camera);
	camera->AddComponent(c);
	//AddObject(camera);

	std::cout << "참조" << camera.use_count() << "컴포넌트 사이즈" << camera->GetComponents().size() << std::endl;


	////--- Cube 생성
	//std::shared_ptr<Object> cube = std::make_shared<Object>("Cube");
	//auto t = cube->GetTransform();
	//t->position.y += 0.5f;
	//t->rotation.y += 45;
	//t->rotation.z += 45;
	//std::cout << t->GetBelongingObject()->name << std::endl;
	//auto cubeRenderer = std::make_shared<Renderer>(cube);
	//auto model = rs.GetCopiedModelInstance("Cube.obj");
	//for (auto i = model->verticesPos.begin(); i != model->verticesPos.end(); ++i)
	//{
	//	*i *= 0.2;
	//}
	//model->RandomColor();
	//model->UpdateBuffer();
	//cubeRenderer->SetOwnModel(model);
	//AddObject(cube);

	
	//SubObject(camera);
}
