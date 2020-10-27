#include "Object.h"
#include "stdafx.h"
#include "Component.h"
#include "Transform.h"

Object::Object()
{
	//--- �⺻ Ʈ�������� �߰��մϴ�.
	m_Transform = std::make_shared<Transform>(shared_from_this());
	m_Components.emplace_back(m_Transform);
}
