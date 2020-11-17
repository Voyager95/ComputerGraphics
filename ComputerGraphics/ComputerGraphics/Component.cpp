#include "stdafx.h"
#include "Object.h"
#include "Component.h"

Component::Component(std::shared_ptr<Object> object)
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
	m_Object = nullptr;
	
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
	//--- 먼저 이 컴포넌트를 비활성화 합니다.
	SetEnable(false);

	//--- 파괴 함수를 활성화합니다.
	OnDestory();
}

void Component::OnCollide(std::shared_ptr<Object> object)
{
}
