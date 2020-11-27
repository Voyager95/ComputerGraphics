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

private:
};

