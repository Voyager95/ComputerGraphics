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

public:
	std::list<Transform*> m_Children;
	Transform* m_Parent;
public:
	//--- Constructor
	Transform(Object* object);
	~Transform();

	//--- Getter
	Transform* GetParent() { return m_Parent; }
	std::list<Transform*> GetChildren() { return m_Children; }
	glm::mat4x4 GetTransformMatrix();
	glm::vec3 GetWorldPosition();
	glm::vec3 GetWorldRotation();

	//--- Setter
	void SetWorldRotation(glm::vec3 target);
	void SetWorldPosition(glm::vec3 target);

	//--- Utility
	void LookAt(Object* target);
	void LookAt(glm::vec3 target);

	//--- Parent/Child
	void SetParent(Object* object);
	void SetParent(Transform* transform);
	void DeleteParent();
};

