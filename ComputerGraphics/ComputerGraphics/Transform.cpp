#include "stdafx.h"
#include "Transform.h"
#include "Object.h"

Transform::Transform(Object* object) : Component(object)
{
	position.x = 0;
	position.y = 0;
	position.z = 0;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;

	scale.x = 1;
	scale.y = 1;
	scale.z = 1;

	m_Parent = nullptr;
}

Transform::~Transform()
{
	std::cout << "Tranform 삭제" << std::endl;
}

glm::mat4x4 Transform::GetTransformMatrix()
{

	//-- 이동
	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, position);

	//-- 회전
	glm::mat4 rotate = glm::mat4(1.0f);
	rotate = glm::rotate(rotate,glm::radians( rotation.x), glm::vec3(1, 0, 0));	// X축 회전
	rotate = glm::rotate(rotate, glm::radians(rotation.y), glm::vec3(0, 1, 0));	// Y축 회전
	rotate = glm::rotate(rotate, glm::radians(rotation.z), glm::vec3(0, 0, 1));	// Z축 회전

	//-- 스케일
	glm::mat4 size = glm::mat4(1.0f);
	size = glm::scale(size, scale);

	if (m_Parent != nullptr)
		return m_Parent->GetTransformMatrix() * translate * rotate * size;
	else
		return translate * rotate * size;
}

glm::vec3 Transform::GetWorldPosition()
{
	auto worldPos = GetTransformMatrix()* glm::vec4(0,0,0,1);
	/*std::cout << worldPos.x << ", " << worldPos.y << ", " << worldPos.z << std::endl;*/
	return  glm::vec3(worldPos);
}

glm::vec3 Transform::GetWorldRotation()
{
	if (m_Parent == nullptr)
		return rotation;
	else
		return rotation + m_Parent->GetWorldRotation();
}

void Transform::SetWorldRotation(glm::vec3 target)
{
	if (m_Parent == nullptr)
		rotation = target;
	else
	{
		rotation = target - m_Parent->GetWorldRotation();
	}
}

void Transform::SetWorldPosition(glm::vec3 target)
{
	if (m_Parent == nullptr)
		position = target;
	else
	{
		position = target - m_Parent->GetWorldPosition();
	}
}

void Transform::LookAt(Object* target)
{
	LookAt(target->GetTransform()->GetWorldPosition());
}

void Transform::LookAt(glm::vec3 target)
{
	// 구현되지 않음
}

void Transform::SetParent(Object* object)
{
	SetParent(object->GetTransform());
}

void Transform::SetParent(Transform* transform)
{
	m_Parent = transform;
	transform->m_Children.emplace_back(this);
}

void Transform::DeleteParent()
{
	if (m_Parent != nullptr)
	{
		m_Parent->m_Children.remove(this);
		m_Parent = nullptr;
	}
}
