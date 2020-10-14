#pragma once
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include "GlobalUtility.h"

class Object
{
public:
	Transform* transform;
	
private:
	void Draw();
};

