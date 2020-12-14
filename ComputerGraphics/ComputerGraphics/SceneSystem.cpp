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
	if (m_PresentScene != nullptr)
	{
		if (m_TobeChangeScene != nullptr)
		{
			std::cout << "[SceneSystem StartScene()] �������� ���� ���� �̹� �ֽ��ϴ�." << std::endl;
			return;
		}
		m_TobeChangeScene = targetScene;
		StopLoop();
	}
	else
	{
		targetScene->SetIsActivatedScene(true);

		m_PresentScene = targetScene;

		StartLoop();
	}
}

void SceneSystem::ChangeScene()
{
	m_PresentScene->SetIsActivatedScene(false);
	m_PresentScene = nullptr;

	StartScene(m_TobeChangeScene);

	m_TobeChangeScene = nullptr;
}

SceneSystem::SceneSystem()
{
}

void SceneSystem::StartLoop()
{
	m_LoopEnd = false;

	//--- Scene OnCreate�� ȣ���մϴ�.
	SceneSystem& ss = SceneSystem::GetInstance();
	ss.GetPresentScene()->OnCreate();

	//--- ���� ����
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
		//--- Scene�� Update�� ȣ��
		ss.GetPresentScene()->OnUpdate();

		//--- SceneOBject�� Create�� ȣ��
		for (auto object = ss.GetPresentScene()->objects.begin(); object != ss.GetPresentScene()->objects.end(); ++object)
		{
			if ((*object)->GetIsAddedScene())
				(*object)->OnCreate();
		}

		//--- SceneOBject�� Update�� ȣ��
		for (auto object = ss.GetPresentScene()->objects.begin(); object != ss.GetPresentScene()->objects.end(); ++object)
		{
			if ((*object)->GetIsAddedScene())
				(*object)->OnUpdate();
		}

		//--- SceneOBject�� LateUpdate�� ȣ��
		for (auto object = ss.GetPresentScene()->objects.begin(); object != ss.GetPresentScene()->objects.end(); ++object)
		{
			if ((*object)->GetIsAddedScene())
				(*object)->OnLateUpdate();
		}

		//--- SceneOBject�� OnPreRender�� ȣ��
		for (auto object = ss.GetPresentScene()->objects.begin(); object != ss.GetPresentScene()->objects.end(); ++object)
		{
			if ((*object)->GetIsAddedScene())
				(*object)->OnPreRender();
		}

		//--- ��ǲ �ʱ�ȭ
		is.ResetKey();

		//--- ����
		glutPostRedisplay();

		//--- ���� ��� ������Ʈ ����
		ss.GetPresentScene()->ClearToRemove();

		//--- ���η��� ��� ȣ��
		glutTimerFunc(LOOPSPEED, MainLoop, 1);
	}
	else
	{
		ss.ChangeScene();
	}

}