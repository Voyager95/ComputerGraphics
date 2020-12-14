#include "stdafx.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "Object.h"
#include "Transform.h"
Scene::Scene()
{
	m_IsActivatedScene = false;
}

Scene::~Scene()
{
	std::cout << "[Scene ~Scene()] 삭제됩니다" << std::endl;

	while (objects.empty() != true)
	{
		auto obj = objects.begin();

		std::cout << (*obj)->name << " 오브젝트 삭제" << std::endl;
		delete((*obj));
		
		ClearToRemove();
	}

	
}

void Scene::AddObject(Object* object)
{
	auto result = std::find(objects.begin(), objects.end(), object);
	if (result == objects.end())
	{
		object->OnAddScene(this);
		objects.emplace_back(object);
	}

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

void Scene::SubObject(Object* object, bool toDelete)
{
	auto result = std::find(objects.begin(), objects.end(), object);
	auto isExistToRemove = std::find(toRemove.begin(), toRemove.end(), object);
	if (result != objects.end() && isExistToRemove == toRemove.end())
	{
		object->OnSubScene();
		toRemove.push_back(object);
	}

	auto objectTransform = object->GetTransform();
	auto objectChildren = objectTransform->GetChildren();
	if (objectChildren.size() > 0)
	{
		for (auto i = objectChildren.begin(); i != objectChildren.end(); ++i)
			SubObject((*i)->GetBelongingObject());
	}
}

void Scene::OnCreate()
{
}

void Scene::OnUpdate()
{
}

void Scene::ClearToRemove()
{
	while (toRemove.empty() != true)
	{
		auto object = toRemove.begin();
		objects.remove(*object);
		toRemove.remove(*object);
		//delete(*object);
	}
}
