#include "stdafx.h"
#include "½Ç½À16.h"
#include "Object.h"
#include "Renderer.h"

void Exercise18()
{
	exercise18 = std::make_shared<Scene>();
	//--- Cube
	std::shared_ptr<Object> cube = std::make_shared<Object>();
	std::shared_ptr<Renderer> cube_Renderer = std::make_shared<Renderer>(cube);
}
