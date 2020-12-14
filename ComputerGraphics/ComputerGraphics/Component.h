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

	virtual void OnCreate();		// �� ������Ʈ�� �����ǰ� ���� �߰� �Ǿ��� ��, ó������ ȣ��Ǵ� �Լ� �Դϴ�.
	virtual void OnEnable();		// �� ������Ʈ�� Ȱ��ȭ �Ǿ��� ��, �Ҹ��� �Լ��Դϴ�.
	virtual void OnDisable();		// �� ������Ʈ�� ��Ȱ��ȭ �Ǿ��� �� �Ҹ��� �Լ��Դϴ�.
	virtual void OnPreRender();		// �׸��� ���� ȣ��Ǵ� �Լ��Դϴ�.
	virtual void OnUpdate();		// ������Ʈ �� �Ҹ��� �Լ��Դϴ�.
	virtual void OnLateUpdate();	// ������Ʈ ���� �Ҹ��� �Լ� �Դϴ�.
	virtual void OnAddScene();		// ���� �߰��Ǿ��� ��, �Ҹ��� �Լ� �Դϴ�.
	virtual void OnSubScene();		// ���� ���� �Ǿ��� ��, �Ҹ��� �Լ� �Դϴ�.
	virtual void OnCollide(Object* object);
};

