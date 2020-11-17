#include "stdafx.h"
#include "Camera.h"
#include "Object.h"
#include "Transform.h"

std::list<std::shared_ptr<Camera>> Camera::cameras;
std::shared_ptr<Camera> Camera::main = nullptr;

Camera::Camera(std::shared_ptr<Object> object): Component(object)
{
	//--- ���� �ʱ�ȭ
	projOption = CameraProj::PERSPECTIVE;
	//-- Ortho
	left = -50;
	right = 50;
	bottom = -50;
	top = 50;
	//-- Perspective
	fovy = 45;
	nearPlane = 0.1f;
	farPlane = 50.0f;
	m_Priority = 0;
}

Camera::Camera(int priority, std::shared_ptr<Object> object): Component(object)
{
	//--- ���� �ʱ�ȭ
	projOption = CameraProj::PERSPECTIVE;
	//-- Ortho
	left = -50;
	right = 50;
	bottom = -50;
	top = 50;
	//-- Perspective
	fovy = 45;
	nearPlane = 0.1f;
	farPlane = 50.0f;
	m_Priority = priority;
}

void Camera::SetPriority(int value)
{
	m_Priority = value;

	//--- �ֽ�ȭ
	if (cameras.empty() == false)
	{
		bool initialized = false;
		int highestPriority = -1;
		auto highestPrioirtyCameraIter = cameras.begin();
		for (auto iter = cameras.begin(); iter != cameras.end(); ++iter)
		{
			if (initialized == false)
			{
				highestPriority = iter->get()->GetPriority();
				highestPrioirtyCameraIter = iter;
				initialized = true;
				continue;
			}

			if (highestPriority < iter->get()->GetPriority())
			{
				highestPriority = iter->get()->GetPriority();
				highestPrioirtyCameraIter = iter;
			}
		}
		main = *highestPrioirtyCameraIter;
	}
	else
	{
		main = shared_from_this();
	}
}

glm::mat4 Camera::GetViewMatrix()
{
	auto transform = GetBelongingObject()->GetTransform();
	
	//-- ȸ��
	glm::mat4 rotate = glm::mat4(1.0f);
	rotate = glm::rotate(rotate, glm::radians(transform->rotation.x), glm::vec3(1, 0, 0));	// X�� ȸ��
	rotate = glm::rotate(rotate, glm::radians(transform->rotation.y), glm::vec3(0, 1, 0));	// Y�� ȸ��
	rotate = glm::rotate(rotate, glm::radians(transform->rotation.z), glm::vec3(0, 0, 1));	// Z�� ȸ��

	//--- ī�޶� ��ġ
	glm::vec3 cameraPos = transform->position;

	//--- ī�޶� �ٶ󺸴� ����
	glm::vec4 forward = glm::vec4(.0f, .0f, 1.0f, 1);
	glm::vec3 cameraforward = (glm::vec3)(rotate * forward);

	//--- ī�޶� ������ ��
	glm::vec4 right = glm::vec4(1.0f, .0f, 0.0f, 1);
	glm::vec3 cameraRight = (glm::vec3)(rotate * right);

	//--- ī�޶� ��
	glm::vec3 cameraUp = glm::cross(cameraforward, cameraRight);

	return glm::lookAt(cameraPos, cameraforward, cameraUp);
}

glm::mat4 Camera::GetProjMatrix()
{
	if (projOption == CameraProj::ORTHO)
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
