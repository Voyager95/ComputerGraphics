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

	virtual void OnCreate();			// 이 씬이 시작될 때, 불리는 함수입니다.
	virtual void OnUpdate();			// 업데이트 마다 불리는 함수 입니다. 
private:
};

