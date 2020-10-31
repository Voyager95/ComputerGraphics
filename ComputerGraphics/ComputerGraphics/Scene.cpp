#include "stdafx.h"
#include "Scene.h"
#include "Object.h"

Scene::Scene()
{
}

void Scene::AddObject(std::shared_ptr<Object> object)
{
	objects.emplace_back(object);
}
