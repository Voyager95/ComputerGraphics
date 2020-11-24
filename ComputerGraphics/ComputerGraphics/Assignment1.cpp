#include "stdafx.h"
#include "Assignment1.h"

#include "ModelInstnce.h"
#include "InputSystem.h"
#include "Object.h"
#include "Transform.h"
#include "Camera.h"
#include "Renderer.h"

Assignment1::Assignment1()
{
	//--- Camera 생성
	Object* camera = new Object();
	//-- Transform
	auto cameraTransform = camera->GetTransform();
	cameraTransform->position.y += 15.0f;
	cameraTransform->position.z += -10.0f;
	cameraTransform->rotation.x += 45;
	//-- Camera
	camera->AddComponent<Camera>();
	AddObject(camera);

	//--- Plane 생성
	auto plane = new Object();
	//-- Transform
	auto planeTransform = plane->GetTransform();
	planeTransform->scale *= 5;
	//-- Randerer
	auto planeRenderer = plane->AddComponent<Renderer>();
	planeRenderer->SetTargetShader(ShaderType::TEXTURE_ELEMENT);
	planeRenderer->SetSharedModel("human.obj");
	planeRenderer->SetSharedTextrue("human.png");
	AddObject(plane);


	//--- SliceLine 생성
	Object* sliceLine = new Object("SliceLine");
	//-- Renderer
	auto sliceLineRenderer = sliceLine->AddComponent<Renderer>();

	AddObject(sliceLine);

	SubObject(sliceLine);
	
}

SliceLine::SliceLine(Object* object) : Component(object)
{

}

void SliceLine::OnCreate()
{
	//--- 플레그 설정
	m_IsDragStart = false;

	//--- 모델 생성
	m_Model = std::make_shared<ModelInstance>();
	m_Model->usage = GL_DYNAMIC_DRAW;
	m_Model->verticesPos.emplace_back(glm::vec3());
	m_Model->verticesPos.emplace_back(glm::vec3());
	m_Model->verticesPos.emplace_back(glm::vec3());
	m_Model->verticesColor.emplace_back(glm::vec3(colorDis(gen), colorDis(gen), colorDis(gen)));
	m_Model->verticesColor.emplace_back(glm::vec3(colorDis(gen), colorDis(gen), colorDis(gen)));
	m_Model->verticesColor.emplace_back(glm::vec3(colorDis(gen), colorDis(gen), colorDis(gen)));

	//--- 렌더러 설정
	auto object = GetBelongingObject();
	auto renderer = object->GetComponent<Renderer>();
	if (renderer != nullptr)
	{
		renderer->SetOwnModel(m_Model);
		renderer->SetTargetShader(ShaderType::LINE);
	}
	else
	{
		std::cout << "[SliceLine OnCreate()] 렌더러가 없습니다" << std::endl;
		return;
	}
}

void SliceLine::OnUpdate()
{

	InputSystem& is = InputSystem::GetInstance();

	if (is.GetMouseDown(GLUT_LEFT_BUTTON) == true)
	{
		std::cout << "첫번째 점: (" << is.GetMousePos().x << ", " << is.GetMousePos().y << ")" << std::endl;
		m_IsDragStart = true;
		m_Model->verticesPos[0] = glm::vec3(is.GetMousePos(),0);
		m_Model->UpdateBuffer();
	}

	if (is.GetMouseUp(GLUT_LEFT_BUTTON) == true)
		m_IsDragStart = false;

	if (m_IsDragStart == true)
	{
		std::cout << "두번째 점: (" << is.GetMousePos().x << ", " << is.GetMousePos().y << ")" << std::endl;
		m_Model->verticesPos[1] = glm::vec3(is.GetMousePos(), 0);
		m_Model->UpdateBuffer();
	}
}
