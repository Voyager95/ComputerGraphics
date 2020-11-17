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
	std::shared_ptr<Object> camera = GlobalUtility::CreateObject();
	//-- Transform
	auto cameraTransform = camera->GetTransform();
	cameraTransform->position.y += 15.0f;
	cameraTransform->position.z += -10.0f;
	cameraTransform->rotation.x += 45;
	//-- Camera
	auto cameraCamera = std::make_shared<Camera>(1, camera);
	camera->AddComponent(cameraCamera);
	//cameraCamera->projOption = CameraProj::ORTHO;
	AddObject(camera);

	//--- Plane 생성
	std::shared_ptr<Object> plane = GlobalUtility::CreateObject();
	//-- Transform
	auto planeTransform = plane->GetTransform();
	planeTransform->scale *= 5;
	//-- Randerer
	auto planeRenderer = std::make_shared<Renderer>(plane);
	plane->AddComponent(planeRenderer);
	planeRenderer->SetTargetShader(ShaderType::TEXTURE_ELEMENT);
	planeRenderer->SetSharedModel("human.obj");
	planeRenderer->SetSharedTextrue("human.png");
	AddObject(plane);

	//--- SliceLine 생성
	std::shared_ptr<Object> sliceLine = GlobalUtility::CreateObject();
	//-- Renderer
	auto sliceLineRenderer = sliceLine->AddComponent<Renderer>();
	//-- SliceLine
	auto sliceLineSliceLine = std::make_shared<SliceLine>(sliceLine);
	sliceLine->AddComponent(sliceLineSliceLine);
	AddObject(sliceLine);
	
}

SliceLine::SliceLine(std::shared_ptr<Object> object) : Component(object)
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
