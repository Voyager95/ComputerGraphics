#pragma once
#include "stdafx.h"

class Object;
class Component;

class Scene
{
public:
	std::list<Object*> objects;
 
	Scene();

	void AddObject(Object* object);
	void SubObject(Object* object);

	virtual void OnCreate();			// �� ���� ���۵� ��, �Ҹ��� �Լ��Դϴ�.
	virtual void OnUpdate();			// ������Ʈ ���� �Ҹ��� �Լ� �Դϴ�. 
private:
};

