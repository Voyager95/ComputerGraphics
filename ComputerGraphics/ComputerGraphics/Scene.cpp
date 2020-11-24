#include "stdafx.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "Object.h"

Scene::Scene()
{
}

void Scene::AddObject(Object* object)
{
	objects.emplace_back(object);
}

void Scene::SubObject(Object* object)
{
	objects.remove(object);
	delete object;
}
