#include "stdafx.h"
#include "Object.h"
#include "Component.h"

Component::Component(Object* object)
{
	//--- �ڽ��� �����ִ� ������Ʈ�� �ֽ��ϴ�.
	m_Object = object;

	//--- ������Ʈ�� �����Ǹ� ���ʷ� OnCreate �Լ��� ȣ���մϴ�.
	OnCreate();

	//--- ������Ʈ�� �����Ǹ� enable ���� �̹Ƿ� OnEnable �Լ��� ȣ���մϴ�.
	OnEnable();
}

Component::~Component()
{
	OnDestory();
}

Transform* Component::GetBelongingTransform()
{
	return m_Object->GetTransform();
}

void Component::OnCreate()
{
}

void Component::OnEnable()
{
}

void Component::OnDisable()
{
}

void Component::OnPreRender()
{
}

void Component::OnUpdate()
{
}

void Component::OnLateUpdate()
{
}

void Component::OnDestory()
{
}

void Component::OnCollide(Object* object)
{
}
