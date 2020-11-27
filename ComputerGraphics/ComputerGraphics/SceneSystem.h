#pragma once
#include "stdafx.h"

class Scene;
class Object;

void MainLoop(int);

class SceneSystem
{
public:
	//--- 싱글톤 디자인
	SceneSystem(const SceneSystem&) = delete;
	SceneSystem& operator=(const SceneSystem&) = delete;

	/// <summary>
	/// 싱글톤 인스턴스를 얻습니다.
	/// </summary>
	/// <returns></returns>
	static SceneSystem& GetInstance();
private:
	unsigned int LOOP_RATE = 1000 / 60;

	//--- 현재 씬 정보, 플레그
	std::shared_ptr<Scene> m_PresentScene;
	bool m_LoopEnd;

public:
	/// <summary>
	/// 해당 씬을 로드 하고 씬을 시작합니다.
	/// </summary>
	/// <param name="targetScene"></param>
	void StartScene(std::shared_ptr<Scene> targetScene);
private:	
	SceneSystem();

public:
	//--- Getter
	std::shared_ptr<Scene> GetPresentScene() { return m_PresentScene; }
	bool LoopEnd() { return m_LoopEnd; };

	/// <summary>
	/// 현재 씬을 시작합니다
	/// 즉, 루프를 돌립니다.
	/// </summary>
	void StartLoop();

	/// <summary>
	/// 현재 씬을 멈줍니다.
	/// 즉, 루프를 멈춥니다.
	/// </summary>
	void StopLoop();

public:
	static Object* GetObjectByName(std::string name);
};

