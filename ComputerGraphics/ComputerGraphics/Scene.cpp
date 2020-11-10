#include "stdafx.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "Object.h"

Scene::Scene()
{
}

void Scene::AddObject(std::shared_ptr<Object> object)
{
	objects.emplace_back(object);
}

void Scene::SubObject(std::shared_ptr<Object> object)
{
	objects.remove(object);
}
