#include "stdafx.h"
#include "TermProject.h"
#include "Object.h"
#include "Camera.h"
#include "Transform.h"
#include "Renderer.h"
#include "SimpleMove.h"

TermProject::TermProject()
{
	//--- Camera »ý¼º
	Object* camera = new Object();
	//-- Transform
	auto cameraTransform = camera->GetTransform();
	cameraTransform->position.y += 15.0f;
	cameraTransform->position.z += -50.0f;
	cameraTransform->rotation.x += 45;
	//-- Camera
	camera->AddComponent<Camera>();
	//-- SimpleMove
	auto cameraSimpleMove = camera->AddComponent<SimpleMove>();
	cameraSimpleMove->MoveToByTime(glm::vec3(0), 10);
	AddObject(camera);

	Object* cylinder = new Object();
	//Transform 
	auto cylinderTransform = cylinder->GetTransform();
	cylinderTransform->scale = glm::vec3(3);
	//Renderer
	auto cylinderRenderer = cylinder->AddComponent<Renderer>();
	cylinderRenderer->SetTargetShader(ShaderType::VERTEX_ELEMENT);
	cylinderRenderer->SetSharedModel("tree.obj");
	AddObject(cylinder);

}
