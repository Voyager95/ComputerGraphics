#include "stdafx.h"
#include "Object.h"

#include "Component.h"
#include "Transform.h"
#include "Renderer.h"

Object::Object()
{
	m_TransformExist = false;

	m_Transform = new Transform(this);

	m_Components.emplace_back(m_Transform);
}

Object::Object(std::string name) : Object()
{
	this->name = name;
}

Object::~Object()
{
	std::cout << name << " »èÁ¦µÊ" << " ÄÄÆ÷³ÍÆ® ¼ö: " << m_Components.size() << std::endl;
	//for (auto c = m_Components.begin(); c != m_Components.end(); ++c)
	//{
	//	delete(*c);
	//}

	delete(m_Transform);
		
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
