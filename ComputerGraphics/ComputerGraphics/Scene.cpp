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
	std::cout << "[Scene ~Scene()] �����˴ϴ�" << std::endl;

	while (objects.empty() != true)
	{
		auto obj = objects.begin();

		std::cout << (*obj)->name << " ������Ʈ ����" << std::endl;
		delete((*obj));
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

void Scene::SubObject(Object* object)
{
	auto result = std::find(objects.begin(), objects.end(), object);
	if (result != objects.end())
	{
		object->OnSubScene();
		objects.remove(object);
	}
	else
		std::cout << "[Scene SubObject()] �̹� ���� ���� ������Ʈ�Դϴ�. " << object->name << std::endl;

	auto objectTransform = object->GetTransform();
	auto objectChildren = objectTransform->GetChildren();
	if (objectChildren.size() > 0)
	{
		for (auto i = objectChildren.begin(); i != objectChildren.end(); ++i)
			SubObject((*i)->GetBelongingObject());
	}
}

void Scene::SubAllObject()
{
}

void Scene::OnCreate()
{
}

void Scene::OnUpdate()
{
}
