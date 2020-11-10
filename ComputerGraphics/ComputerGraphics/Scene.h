#pragma once
#include "stdafx.h"

class Object;
class Component;

class Scene
{
public:
	std::list<std::shared_ptr<Object>> objects;

	Scene();

	void AddObject(std::shared_ptr<Object> object);
	void SubObject(std::shared_ptr<Object> object);
private:
};

