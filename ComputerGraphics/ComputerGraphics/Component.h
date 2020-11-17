#pragma once
#include "stdafx.h"

class Object;

class Component
{
private:
	std::shared_ptr<Object> m_Object;
	bool m_Enable;
public:
	Component(std::shared_ptr<Object> object);
	~Component();

	//--- Getter
	bool GetEnable() { return m_Enable; }
	std::shared_ptr<Object> GetBelongingObject() { return m_Object; }

	//--- Setter
	void SetEnable(bool value) { m_Enable = value; if (value == true) OnEnable(); else OnDisable(); }

	virtual void OnCreate();		// 이 컴포넌트가 생성되었을 때, 불리는 함수입니다. 업데이트 전에 불리며 한번만 불리게 됩니다.
	virtual void OnEnable();
	virtual void OnDisable();		// 이 컴포넌트가 비활성화 되었을 때 불리는 함수입니다.
	virtual void OnPreRender();		// 그리기 전에 호출되는 함수입니다.
	virtual void OnUpdate();		// 업데이트 떄 불리는 함수입니다.
	virtual void OnLateUpdate();	// 업데이트 이후 불리는 함수 입니다.
	virtual void OnDestory();		// 파괴할 때, 불리는 함수입니다.
	virtual void OnCollide(std::shared_ptr<Object> object);
};

