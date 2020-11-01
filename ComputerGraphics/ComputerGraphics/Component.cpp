#include "stdafx.h"
#include "Object.h"
#include "Component.h"

Component::Component(std::shared_ptr<Object> object)
{
	//--- �ڽ��� �����ִ� ������Ʈ�� �ֽ��ϴ�.
	m_Object = object;

	object->AddComponent(std::shared_ptr<Component>(this));

	//--- ������Ʈ�� �����Ǹ� ���ʷ� OnCreate �Լ��� ȣ���մϴ�.
	OnCreate();

	//--- ������Ʈ�� �����Ǹ� enable ���� �̹Ƿ� OnEnable �Լ��� ȣ���մϴ�.
	OnEnable();
}

Component::~Component()
{
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
	//--- ���� �� ������Ʈ�� ��Ȱ��ȭ �մϴ�.
	SetEnable(false);

	//--- �ı� �Լ��� Ȱ��ȭ�մϴ�.
	OnDestory();
}