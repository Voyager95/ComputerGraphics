#include "stdafx.h"
#include "Transform.h"

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

	parent = nullptr;
}

Transform::~Transform()
{
	std::cout << "Tranform ����" << std::endl;
}

glm::mat4x4 Transform::GetTransformMatrix()
{

	//-- �̵�
	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, position);

	//-- ȸ��
	glm::mat4 rotate = glm::mat4(1.0f);
	rotate = glm::rotate(rotate,glm::radians( rotation.x), glm::vec3(1, 0, 0));	// X�� ȸ��
	rotate = glm::rotate(rotate, glm::radians(rotation.y), glm::vec3(0, 1, 0));	// Y�� ȸ��
	rotate = glm::rotate(rotate, glm::radians(rotation.z), glm::vec3(0, 0, 1));	// Z�� ȸ��

	//-- ������
	glm::mat4 size = glm::mat4(1.0f);
	size = glm::scale(size, scale);

	if (parent != nullptr)
		return parent->GetTransformMatrix() * translate * rotate * size;
	else
		return translate * rotate * size;
}

glm::vec3 Transform::GetWorldPosition()
{
	return glm::vec3();
}
