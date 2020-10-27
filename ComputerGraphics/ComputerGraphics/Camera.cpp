#include "Camera.h"
#include "stdafx.h"
Camera::Camera(std::shared_ptr<Object> object) : Component(object)
{
	
}

void Camera::OnCreate()
{
	m_Priority = 0;
}

void Camera::OnDestory()
{
}
