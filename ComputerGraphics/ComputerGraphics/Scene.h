#pragma once
#include "stdafx.h"

class Object;
class Component;

class Scene
{
public:
	std::list<Object*> objects;
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
	void SubObject(Object* object);
	void SubAllObject();

	virtual void OnCreate();			// �� ���� ���۵� ��, �Ҹ��� �Լ��Դϴ�.
	virtual void OnUpdate();			// ������Ʈ ���� �Ҹ��� �Լ� �Դϴ�. 
};

