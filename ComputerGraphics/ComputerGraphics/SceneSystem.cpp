#include "stdafx.h"
#include "SceneSystem.h"
#include "RenderSystem.h"
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

GLvoid MainLoop(int value)
{
	SceneSystem& ss = SceneSystem::GetInstance();
	RenderSystem& rs = RenderSystem::GetInstance();
	if (ss.LoopEnd() != true)
	{
		//--- Update�� ȣ��
		for (auto object = ss.GetPresentScene()->objects.begin(); object != ss.GetPresentScene()->objects.end(); ++object)
		{
			object->get()->OnUpdate();
		}

		//--- LateUpdate�� ȣ��
		for (auto object = ss.GetPresentScene()->objects.begin(); object != ss.GetPresentScene()->objects.end(); ++object)
		{
			object->get()->OnLateUpdate();
		}

		//--- OnPreRender�� ȣ��
		for (auto object = ss.GetPresentScene()->objects.begin(); object != ss.GetPresentScene()->objects.end(); ++object)
		{
			object->get()->OnPreRender();
		}

		//--- ����
		glutPostRedisplay();

		//--- ���η��� ��� ȣ��
		glutTimerFunc(20, MainLoop, 1);
	}

}