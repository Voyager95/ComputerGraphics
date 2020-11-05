#pragma once
#include "Scene.h"

class Exercise17 : public Scene
{
public:
	Exercise17();
};


//#include "stdafx.h"
//#include "Scene.h"
//#include "Object.h"
//#include "Renderer.h"
//#include "Transform.h"
//#include "ModelInstnce.h"
//#include "ResourceSystem.h"
//
//void Exercise()
//{
//	ResourceSystem& rs = ResourceSystem::GetInstance();
//
//	//--- √ ±‚ æ¿ Ω√¿€
//	std::shared_ptr<Scene> exercise16 = std::make_shared<Scene>();
//
//	std::shared_ptr<Object> cube = std::make_shared<Object>("Cube");
//
//	auto t = cube->GetTransform();
//	t->position.y += 0.5f;
//	t->rotation.y += 45;
//	t->rotation.z += 45;
//	std::cout << t->GetObjectW()->name << std::endl;
//
//	auto cubeRenderer = std::make_shared<Renderer>(cube);
//
//	auto model = rs.GetCopiedModelInstance("Cube.obj");
//	for (auto i = model->verticesPos.begin(); i != model->verticesPos.end(); ++i)
//	{
//		*i *= 0.2;
//	}
//	model->RandomColor();
//	model->UpdateBuffer();
//
//	cubeRenderer->SetOwnModel(model);
//
//	exercise16->AddObject(cube);
//
//}