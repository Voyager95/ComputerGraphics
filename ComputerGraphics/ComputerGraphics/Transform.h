#pragma once
#include "stdafx.h"
#include "Component.h"

class Object;

class Transform :
    public Component
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform* parent;
	//--- Constructor
	Transform(Object* object);
	~Transform();

	//--- Getter
	glm::mat4x4 GetTransformMatrix();
	glm::vec3 GetWorldPosition();
	glm::vec3 GetWorldRotation();

	//--- Setter
	void SetWorldRotation(glm::vec3 target);
	void SetWorldPosition(glm::vec3 target);

	//--- Utility
	void LookAt(Object* target);
	void LookAt(glm::vec3 target);
};

