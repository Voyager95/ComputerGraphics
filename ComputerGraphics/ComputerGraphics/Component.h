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
	~Component();

	//--- Getter
	bool GetEnable() { return m_Enable; }
	Transform* GetBelongingTransform() { return m_Object->GetTransform(); }
	Object* GetBelongingObject() { return m_Object; }


	//--- Setter
	void SetEnable(bool value) { m_Enable = value; if (value == true) OnEnable(); else OnDisable(); }

	virtual void OnCreate();		// �� ������Ʈ�� �����Ǿ��� ��, �Ҹ��� �Լ��Դϴ�. ������Ʈ ���� �Ҹ��� �ѹ��� �Ҹ��� �˴ϴ�.
	virtual void OnEnable();
	virtual void OnDisable();		// �� ������Ʈ�� ��Ȱ��ȭ �Ǿ��� �� �Ҹ��� �Լ��Դϴ�.
	virtual void OnPreRender();		// �׸��� ���� ȣ��Ǵ� �Լ��Դϴ�.
	virtual void OnUpdate();		// ������Ʈ �� �Ҹ��� �Լ��Դϴ�.
	virtual void OnLateUpdate();	// ������Ʈ ���� �Ҹ��� �Լ� �Դϴ�.
	virtual void OnDestory();		// �ı��� ��, �Ҹ��� �Լ��Դϴ�. (������ ����, �Ҹ��� ���)
	virtual void OnCollide(Object* object);
};

