#include "stdafx.h"
#include "Object.h"
#include "Component.h"

Component::Component(Object* object)
{
	//--- 자신이 속해있는 오브젝트를 넣습니다.
	m_Object = object;

	//--- 컴포넌트가 생성되면 최초로 OnCreate 함수를 호출합니다.
	OnCreate();

	//--- 컴포넌트가 생성되면 enable 상태 이므로 OnEnable 함수를 호출합니다.
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
