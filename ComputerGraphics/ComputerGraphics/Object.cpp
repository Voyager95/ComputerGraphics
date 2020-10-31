#include "stdafx.h"
#include "Object.h"

#include "Component.h"
#include "Transform.h"
#include "Renderer.h"

Object::Object()
{
	//--- 기본 트랜스폼을 추가합니다.
	m_Transform = std::make_shared<Transform>(shared_from_this());
	m_Components.emplace_back(m_Transform);
}

template<class T>
inline std::shared_ptr<T> Object::AddComponent()
{
	auto t = std::shared_ptr<T>(shared_from_this());
	m_Components.emplace_back(t);
	return t;
}

void Object::AddComponent(std::shared_ptr<Component> component)
{
	m_Components.emplace_back(component);
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
