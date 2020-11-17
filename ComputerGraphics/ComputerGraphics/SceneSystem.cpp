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

GLvoid MainLoop(int value)
{
	SceneSystem& ss = SceneSystem::GetInstance();
	RenderSystem& rs = RenderSystem::GetInstance();
	InputSystem& is = InputSystem::GetInstance();

	if (ss.LoopEnd() != true)
	{
		//--- Create�� ȣ��
		for (auto object = ss.GetPresentScene()->objects.begin(); object != ss.GetPresentScene()->objects.end(); ++object)
		{
			object->get()->OnCreate();
		}

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

		//--- ��ǲ �ʱ�ȭ
		is.ResetKey();

		//--- ����
		glutPostRedisplay();

		//--- ���η��� ��� ȣ��
		glutTimerFunc(LOOPSPEED, MainLoop, 1);
	}

}