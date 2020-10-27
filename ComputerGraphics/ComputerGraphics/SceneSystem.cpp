#include "SceneSystem.h"
#include "stdafx.h"
SceneSystem& SceneSystem::GetInstance()
{
	static SceneSystem instance;
	return instance;
}

SceneSystem::SceneSystem()
{
}
