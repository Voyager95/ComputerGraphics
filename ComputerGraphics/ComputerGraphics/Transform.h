#pragma once
#include <memory>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include "Component.h"
#include "Object.h"

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
};

