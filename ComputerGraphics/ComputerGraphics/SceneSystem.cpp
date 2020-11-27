#include "stdafx.h"
#include "SceneSystem.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "Scene.h"
#include "Object.h"
#include "Component.h"

SceneSystem& SceneSystem::GetInstance()
{
	static SceneSystem instance;
	return instance;
}

void SceneSystem::StartScene(std::shared_ptr<Scene> targetScene)
{
	m_PresentScene = targetScene;

	StartLoop();
}

SceneSystem::SceneSystem()
{
}

void SceneSystem::StartLoop()
{
	m_LoopEnd = false;
	glutTimerFunc( 0, MainLoop, 1);
}

void SceneSystem::StopLoop()
{
	m_LoopEnd = true;
}

Object* SceneSystem::GetObjectByName(std::string name)
{
	SceneSystem& ss = SceneSystem::GetInstance();

	for (auto o = ss.GetPresentScene()->objects.begin(); o != ss.GetPresentScene()->objects.end(); ++o)
	{
		if ((*o)->name == name)
		{
			return (*o);
		}
	}

	return nullptr;
}

GLvoid MainLoop(int value)
{
	SceneSystem& ss = SceneSystem::GetInstance();
	RenderSystem& rs = RenderSystem::GetInstance();
	InputSystem& is = InputSystem::GetInstance();

	if (ss.LoopEnd() != true)
	{
		//--- Create문 호출
		for (auto object = ss.GetPresentScene()->objects.begin(); object != ss.GetPresentScene()->objects.end(); ++object)
		{
			(*object)->OnCreate();
		}

		//--- Update문 호출
		for (auto object = ss.GetPresentScene()->objects.begin(); object != ss.GetPresentScene()->objects.end(); ++object)
		{
			(*object)->OnUpdate();
		}

		//--- LateUpdate문 호출
		for (auto object = ss.GetPresentScene()->objects.begin(); object != ss.GetPresentScene()->objects.end(); ++object)
		{
			(*object)->OnLateUpdate();
		}

		//--- OnPreRender문 호출
		for (auto object = ss.GetPresentScene()->objects.begin(); object != ss.GetPresentScene()->objects.end(); ++object)
		{
			(*object)->OnPreRender();
		}

		//--- 인풋 초기화
		is.ResetKey();

		//--- 렌더
		glutPostRedisplay();

		//--- 메인루프 재귀 호출
		glutTimerFunc(LOOPSPEED, MainLoop, 1);
	}

}