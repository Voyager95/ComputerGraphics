#pragma once
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <string>
#include <list>
#include <memory>
#include "GlobalUtility.h"

class Component;
class Transform;

class Object : std::enable_shared_from_this<Object>
{
public:
	std::string tag;
private:
	std::list<std::shared_ptr<Component>> m_Components;
	std::shared_ptr<Transform> m_Transform;
public:
	Object();
};

