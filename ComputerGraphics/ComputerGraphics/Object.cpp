#include "stdafx.h"
#include "Object.h"

#include "Component.h"
#include "Transform.h"
#include "Renderer.h"
#include "SceneSystem.h"
#include "Scene.h"

Object::Object()
{
	m_TransformExist = false;

	m_Transform = new Transform(this);

	m_Components.emplace_back(m_Transform);
}

Object::Object(std::string name) : Object()
{
	this->name = name;
	m_BelongingScene = nullptr;
}

Object::~Object()
{
	//--- �ڽ� ������Ʈ�� ���� ���� ��� 
	auto childrenList = m_Transform->GetChildren();
	if (childrenList.size() > 0)
	{
		for (auto i = childrenList.begin(); i != childrenList.end(); ++i)
		{
			delete((*i)->GetBelongingObject());
		}
	}

	// ���� �߰��Ǿ� �ִٸ� �����ϱ�
	if (m_IsAddedScene == true)
	{
		SubObject();
	}

	// ������Ʈ ����
	std::cout << name << " ������" << " ������Ʈ ��: " << m_Components.size() << std::endl;
	for (auto c = m_Components.begin(); c != m_Components.end(); ++c)
	{
		delete(*c);
	}
}

void Object::OnAddTransform(Transform* transform)
{
	m_Transform = transform;
	AddComponent(transform);
	m_TransformExist = true;
}

void Object::AddComponent(Component* component)
{
	m_Components.emplace_back(component);
	m_OnCreateComponents.push(component);
}

void Object::SubObject()
{
	if (m_IsAddedScene == true)
	{
		m_BelongingScene->SubObject(this);
	}
}

void Object::OnCreate()
{
	while (m_OnCreateComponents.empty() == false)
	{
		auto c = m_OnCreateComponents.front();
		c->OnCreate();

		m_OnCreateComponents.pop();
	}
}

void Object::OnUpdate()
{
	for (auto c = m_Components.begin(); c != m_Components.end(); ++c)
	{
		(*c)->OnUpdate();
	}
}

void Object::OnLateUpdate()
{
	for (auto c = m_Components.begin(); c != m_Components.end(); ++c)
	{
		(*c)->OnLateUpdate();
	}
}

void Object::OnPreRender()
{
	for (auto c = m_Components.begin(); c != m_Components.end(); ++c)
	{
		(*c)->OnPreRender();
	}
}

void Object::OnAddScene(Scene* scene)
{
	m_BelongingScene = scene;
	m_IsAddedScene = true;

	for (auto c = m_Components.begin(); c != m_Components.end(); ++c)
	{
		(*c)->OnAddScene();
	}
}

void Object::OnSubScene()
{
	m_IsAddedScene = false;

	for (auto c = m_Components.begin(); c != m_Components.end(); ++c)
	{
		(*c)->OnSubScene();
	}
}
