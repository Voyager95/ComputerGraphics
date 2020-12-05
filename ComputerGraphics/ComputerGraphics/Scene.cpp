#include "stdafx.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "Object.h"
#include "Transform.h"
Scene::Scene()
{
}

void Scene::AddObject(Object* object)
{
	auto result = std::find(objects.begin(), objects.end(), object);
	if (result == objects.end())
		objects.emplace_back(object);

	auto objectTransform = object->GetTransform();
	auto objectChildren = objectTransform->m_Children;
	if (objectChildren.size() > 0)
	{
		for (auto i = objectChildren.begin(); i != objectChildren.end(); ++i)
		{
			auto child = (*i)->GetBelongingObject();
			AddObject(child);
		}
	}
}

void Scene::SubObject(Object* object, bool isDelete)
{
	auto result = std::find(objects.begin(), objects.end(), object);
	if (result != objects.end())
		objects.remove(object);
	else
		std::cout << "[Scene SubObject()] 이미 씬에 없는 오브젝트입니다. " << object->name << std::endl;

	auto objectTransform = object->GetTransform();
	auto objectChildren = objectTransform->GetChildren();
	if (objectChildren.size() > 0)
	{
		for (auto i = objectChildren.begin(); i != objectChildren.end(); ++i)
			SubObject((*i)->GetBelongingObject());
	}	
	
	if (isDelete)
		delete object;
}

void Scene::OnCreate()
{
}

void Scene::OnUpdate()
{
}
