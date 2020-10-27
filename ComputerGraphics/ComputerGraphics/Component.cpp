#include "Component.h"
#include "stdafx.h"
Component::Component(std::shared_ptr<Object> object)
{
	//--- �ڽ��� �����ִ� ������Ʈ�� 
	m_Object = object;

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

void Component::OnPreDraw()
{
}

void Component::OnDraw()
{
}

void Component::OnUpdate()
{
}

void Component::OnDestory()
{
	//--- ���� �� ������Ʈ�� ��Ȱ��ȭ �մϴ�.
	SetEnable(false);

	//--- �ı� �Լ��� Ȱ��ȭ�մϴ�.
	OnDestory();
}
