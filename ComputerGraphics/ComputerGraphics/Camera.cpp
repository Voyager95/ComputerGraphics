#include "stdafx.h"
#include "Camera.h"
#include "Object.h"
#include "Transform.h"
std::list<std::shared_ptr<Camera>> Camera::cameras;
std::shared_ptr<Camera> Camera::main = nullptr;

Camera::Camera(std::shared_ptr<Object> object): Component(object)
{
}

void Camera::SetPriority(int value)
{
	m_Priority = value;

	//--- 최신화
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

glm::mat4 Camera::GetViewMatrix()
{
	auto transform = GetBelongingObject()->GetTransform();
	
	//-- 회전
	glm::mat4 rotate = glm::mat4(1.0f);
	rotate = glm::rotate(rotate, glm::radians(transform->rotation.x), glm::vec3(1, 0, 0));	// X축 회전
	rotate = glm::rotate(rotate, glm::radians(transform->rotation.y), glm::vec3(0, 1, 0));	// Y축 회전
	rotate = glm::rotate(rotate, glm::radians(transform->rotation.z), glm::vec3(0, 0, 1));	// Z축 회전

	//--- 카메라 위치
	glm::vec3 cameraPos = transform->position;

	//--- 카메라가 바라보는 방향
	glm::vec4 forward = glm::vec4(.0f, .0f, 1.0f, 1);
	glm::vec3 cameraforward = (glm::vec3)(rotate * forward);

	//--- 카메라 오른쪽 축
	glm::vec4 right = glm::vec4(1.0f, .0f, 0.0f, 1);
	glm::vec3 cameraRight = (glm::vec3)(rotate * right);

	//--- 카메라 업
	glm::vec3 cameraUp = glm::cross(cameraforward, cameraRight);

	return glm::lookAt(cameraPos, cameraforward, cameraUp);
}

void Camera::OnCreate()
{
	//--- 자신을 넣기
	cameras.emplace_back(std::shared_ptr<Camera>(this));

	SetPriority(0);
}

void Camera::OnDestory()
{
}
