#include "stdafx.h"
#include "Camera.h"
#include "Object.h"
#include "Transform.h"

std::list<Camera*> Camera::cameras;
Camera* Camera::main = nullptr;

Camera::Camera(Object* object): Component(object)
{
	//--- 변수 초기화
	projOption = CameraProj::PERSPECTIVE;
	//-- Ortho
	left = -50;
	right = 50;
	bottom = -50;
	top = 50;
	//-- Perspective
	fovy = 60;
	nearPlane = 0.1f;
	farPlane = 100.0f;
	m_Priority = 0;
}

void Camera::SetPriority(int value)
{
	m_Priority = value;

	//--- 최신화
	if (cameras.empty() == false)
	{
		bool initialized = false;
		int highestPriority = -1;
		auto highestPrioirtyCameraIter = cameras.begin();
		for (auto iter = cameras.begin(); iter != cameras.end(); ++iter)
		{
			if (initialized == false)
			{
				highestPriority = (*iter)->GetPriority();
				highestPrioirtyCameraIter = iter;
				initialized = true;
				continue;
			}

			if (highestPriority < (*iter)->GetPriority())
			{
				highestPriority = (*iter)->GetPriority();
				highestPrioirtyCameraIter = iter;
			}
		}
		main = *highestPrioirtyCameraIter;
	}
	else
	{
		main = this;
	}
}

glm::mat4 Camera::GetViewMatrix()
{
	auto transform = GetBelongingObject()->GetTransform();
	
	//-- 회전
	glm::mat4 rotate = glm::mat4(1.0f);
	rotate = glm::rotate(rotate, glm::radians(transform->GetWorldRotation().x), glm::vec3(1, 0, 0));	// X축 회전
	rotate = glm::rotate(rotate, glm::radians(transform->GetWorldRotation().y), glm::vec3(0, 1, 0));	// Y축 회전
	rotate = glm::rotate(rotate, glm::radians(transform->GetWorldRotation().z), glm::vec3(0, 0, 1));	// Z축 회전

	//--- 카메라 위치
	glm::vec3 cameraPos = transform->GetWorldPosition();

	//--- 카메라가 바라보는 방향
	glm::vec4 forward = glm::vec4(.0f, 0.0f, 1.0f, 1);
	glm::vec3 cameraforward = (glm::vec3)(rotate * forward);

	//--- 카메라 오른쪽 축
	glm::vec4 right = glm::vec4(1.0f, .0f, 0.0f, 1);
	glm::vec3 cameraRight = (glm::vec3)(rotate * right);


	//--- 카메라 업
	glm::vec3 cameraUp = glm::cross(cameraforward, cameraRight);

	return glm::lookAt(cameraPos, cameraPos + cameraforward *100.0f, glm::vec3(0,1,0));
}

glm::mat4 Camera::GetProjMatrix()
{
	if (projOption == CameraProj::PERSPECTIVE)
	{
		float aspect = (float)WinSize::WINSIZE_X / (float)WinSize::WINSIZE_Y;
		auto mat = glm::perspective(glm::radians(fovy), aspect , nearPlane,farPlane);

		return mat;
	}
	else
	{
		auto mat = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
		return mat;
	}
}

void Camera::OnCreate()
{
	SetPriority(m_Priority);
}

void Camera::OnDestory()
{
}
