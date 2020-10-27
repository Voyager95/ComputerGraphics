#pragma once

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
public:
	SceneSystem();
};

