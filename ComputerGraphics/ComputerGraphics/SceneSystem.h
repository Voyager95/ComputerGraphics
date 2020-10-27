#pragma once

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
public:
	SceneSystem();
};

