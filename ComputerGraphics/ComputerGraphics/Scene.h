#pragma once
#include "stdafx.h"

class Object;

class Scene
{
public:
	std::vector<std::shared_ptr<Object>> objects;
public:
	Scene();

	void AddObject(std::shared_ptr<Object> object);
private:
};

