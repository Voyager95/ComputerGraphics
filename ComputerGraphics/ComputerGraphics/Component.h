#pragma once
#include "stdafx.h"

class Object;
class Transform;

class Component
{
private:
	Object* m_Object;
	bool m_Enable;


public:
	Component(Object* object);
	virtual ~Component();

	//--- Getter
	bool GetEnable() { return m_Enable; }
	Transform* GetBelongingTransform();
	Object* GetBelongingObject() { return m_Object; }


	//--- Setter
	void SetEnable(bool value) { m_Enable = value; if (value == true) OnEnable(); else OnDisable(); }

	virtual void OnCreate();		// 이 컴포넌트가 생성되고 씬에 추가 되었을 때, 처음으로 호출되는 함수 입니다.
	virtual void OnEnable();		// 이 컴포넌트가 활성화 되었을 때, 불리는 함수입니다.
	virtual void OnDisable();		// 이 컴포넌트가 비활성화 되었을 때 불리는 함수입니다.
	virtual void OnPreRender();		// 그리기 전에 호출되는 함수입니다.
	virtual void OnUpdate();		// 업데이트 떄 불리는 함수입니다.
	virtual void OnLateUpdate();	// 업데이트 이후 불리는 함수 입니다.
	virtual void OnAddScene();		// 씬에 추가되었을 때, 불리는 함수 입니다.
	virtual void OnSubScene();		// 씬에 제거 되었을 때, 불리는 함수 입니다.
	virtual void OnCollide(Object* object);
};

