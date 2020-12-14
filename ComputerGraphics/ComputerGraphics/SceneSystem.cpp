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
			std::cout << "[SceneSystem StartScene()] 다음으로 만들 씬이 이미 있습니다." << std::endl;
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

	//--- Scene OnCreate를 호출합니다.
	SceneSystem& ss = SceneSystem::GetInstance();
	ss.GetPresentScene()->OnCreate();

	//--- 루프 시작
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
		//--- Scene의 Update문 호출
		ss.GetPresentScene()->OnUpdate();

		//--- SceneOBject의 Create문 호출
		for (auto object = ss.GetPresentScene()->objects.begin(); object != ss.GetPresentScene()->objects.end(); ++object)
		{
			if ((*object)->GetIsAddedScene())
				(*object)->OnCreate();
		}

		//--- SceneOBject의 Update문 호출
		for (auto object = ss.GetPresentScene()->objects.begin(); object != ss.GetPresentScene()->objects.end(); ++object)
		{
			if ((*object)->GetIsAddedScene())
				(*object)->OnUpdate();
		}

		//--- SceneOBject의 LateUpdate문 호출
		for (auto object = ss.GetPresentScene()->objects.begin(); object != ss.GetPresentScene()->objects.end(); ++object)
		{
			if ((*object)->GetIsAddedScene())
				(*object)->OnLateUpdate();
		}

		//--- SceneOBject의 OnPreRender문 호출
		for (auto object = ss.GetPresentScene()->objects.begin(); object != ss.GetPresentScene()->objects.end(); ++object)
		{
			if ((*object)->GetIsAddedScene())
				(*object)->OnPreRender();
		}

		//--- 인풋 초기화
		is.ResetKey();

		//--- 렌더
		glutPostRedisplay();

		//--- 삭제 대상 오브젝트 삭제
		ss.GetPresentScene()->ClearToRemove();

		//--- 메인루프 재귀 호출
		glutTimerFunc(LOOPSPEED, MainLoop, 1);
	}
	else
	{
		ss.ChangeScene();
	}

}