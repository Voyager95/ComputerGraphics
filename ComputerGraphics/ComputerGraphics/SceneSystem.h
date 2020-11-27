#pragma once
#include "stdafx.h"

class Scene;
class Object;

void MainLoop(int);

class SceneSystem
{
public:
	//--- �̱��� ������
	SceneSystem(const SceneSystem&) = delete;
	SceneSystem& operator=(const SceneSystem&) = delete;

	/// <summary>
	/// �̱��� �ν��Ͻ��� ����ϴ�.
	/// </summary>
	/// <returns></returns>
	static SceneSystem& GetInstance();
private:
	unsigned int LOOP_RATE = 1000 / 60;

	//--- ���� �� ����, �÷���
	std::shared_ptr<Scene> m_PresentScene;
	bool m_LoopEnd;

public:
	/// <summary>
	/// �ش� ���� �ε� �ϰ� ���� �����մϴ�.
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
	/// ���� ���� �����մϴ�
	/// ��, ������ �����ϴ�.
	/// </summary>
	void StartLoop();

	/// <summary>
	/// ���� ���� ���ݴϴ�.
	/// ��, ������ ����ϴ�.
	/// </summary>
	void StopLoop();

public:
	static Object* GetObjectByName(std::string name);
};

