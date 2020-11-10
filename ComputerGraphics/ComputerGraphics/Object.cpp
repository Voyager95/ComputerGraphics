#include "stdafx.h"
#include "Object.h"

#include "Component.h"
#include "Transform.h"
#include "Renderer.h"

Object::Object()
{
	m_TransformExist = false;
}

Object::Object(std::string name) : Object()
{
	this->name = name;
}

Object::~Object()
{
	std::cout << name << " »èÁ¦µÊ" << std::endl;
}

template<class T>
inline std::shared_ptr<T> Object::AddComponent()
{
	auto t = std::shared_ptr<T>(shared_from_this());
	m_Components.emplace_back(t);
	return t;
}

void Object::OnAddTransform(std::shared_ptr<Transform> transform)
{
	m_Transform = transform;
	AddComponent(transform);
	m_TransformExist = true;
}

void Object::AddComponent(std::shared_ptr<Component> component)
{
	m_Components.emplace_back(component);
	m_OnCreateComponents.push(component);
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
		c->get()->OnUpdate();
	}
}

void Object::OnLateUpdate()
{
	for (auto c = m_Components.begin(); c != m_Components.end(); ++c)
	{
		c->get()->OnLateUpdate();
	}
}

void Object::OnPreRender()
{
	for (auto c = m_Components.begin(); c != m_Components.end(); ++c)
	{
		c->get()->OnPreRender();
	}
}
