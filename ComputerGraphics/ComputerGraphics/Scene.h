#pragma once
#include "stdafx.h"

class Object;
class Component;

class Scene
{
public:
	std::list<Object*> objects;
	std::list<Object*> toRemove;
private:
	bool m_IsActivatedScene;
public:
	//--- Getter
	bool GetIsActivatedScene() { return m_IsActivatedScene; }

	//--- Setter
	void SetIsActivatedScene(bool value) { m_IsActivatedScene = value; }

	//--- Constructor
	Scene();

	//--- Destorctor
	virtual ~Scene();

	void AddObject(Object* object);
	void SubObject(Object* object, bool toDelete = true); // *����� �׳� �ٷ� �����ϰ� �Ǿ����ϴ�.

	virtual void OnCreate();			// �� ���� ���۵� ��, �Ҹ��� �Լ��Դϴ�.
	virtual void OnUpdate();			// ������Ʈ ���� �Ҹ��� �Լ� �Դϴ�. 	

	void ClearToRemove();
};

