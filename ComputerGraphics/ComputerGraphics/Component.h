#pragma once
#include <memory>
#include "Object.h"
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
	std::shared_ptr<Object> GetObject() { return m_Object; }

	//--- Setter
	void SetEnable(bool value) { m_Enable = value; if (value == true) OnEnable(); else OnDisable(); }

	virtual void OnCreate();		// �� ������Ʈ�� �����Ǿ��� ��, �Ҹ��� �Լ��Դϴ�. ������ ȣ�⶧ �Ҹ��� �˴ϴ�.
	virtual void OnEnable();
	virtual void OnDisable();		// �� ������Ʈ�� ��Ȱ��ȭ �Ǿ��� �� �Ҹ��� �Լ��Դϴ�.
	virtual void OnPreRender();		// �׸��� ���� ȣ��Ǵ� �Լ��Դϴ�.
	virtual void OnUpdate();		// ������Ʈ �� �Ҹ��� �Լ��Դϴ�.
	virtual void OnLateUpdate();	// ������Ʈ ���� �Ҹ��� �Լ� �Դϴ�.
	virtual void OnDestory();		// �ı��� ��, �Ҹ��� �Լ��Դϴ�.
};

