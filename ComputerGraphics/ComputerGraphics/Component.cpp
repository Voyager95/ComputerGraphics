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

void Component::OnAddScene()
{
}

void Component::OnSubScene()
{
}

void Component::OnCollide(Object* object)
{
}
