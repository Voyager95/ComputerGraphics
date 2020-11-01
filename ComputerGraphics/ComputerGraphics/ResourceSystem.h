#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <gl/glm/glm.hpp>
#include <map>
#include "ModelInstnce.h"

/// <summary>
/// 여러 리소스를 관리하는 시스템입니다.
/// 같은 리소스가 여러번 불리지 않게 방지해 줍니다.
/// </summary>
class ResourceSystem
{
public:
	//--- 싱글톤 디자인
	ResourceSystem(const ResourceSystem&) = delete;
	ResourceSystem& operator=(const ResourceSystem&) = delete;

	/// <summary>
	/// 싱글톤 인스턴스
	/// 
	/// </summary>
	/// <returns></returns>
	static ResourceSystem& GetInstance();

private:
	//--- Model
	std::map<std::string, std::shared_ptr<ModelInstance>> m_Models;

public:
	ResourceSystem();

	//--- Model

	/// <summary>
	/// 해당 키에 맞는 모델인스턴스를 반환합니다.
	/// 로드되어있는 모델이 없는 경우에 해당 키를 path로 하여 obj파일을 찾아 모델인스턴스를 생성하여 반환합니다.
	/// </summary>
	/// <param name="key">모델인스턴스의 키</param>
	/// <returns>키에 해당하는 모델인스턴스를 반환합니다. *해당인스턴스를 반환할 수 없을 때, Null값을 반한</returns>
	std::shared_ptr<ModelInstance> GetSharedModelInstance(std::string key);

	/// <summary>
	/// 복사 하여 반환해줍니다
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	std::shared_ptr<ModelInstance> GetCopiedModelInstance(std::string key);

	/// <summary>
	/// 특정 모델인스턴스를 추가합니다.
	/// </summary>
	/// <param name="key">이 모델의 키입니다.</param>
	/// <param name="model">모델의 인스턴스 포인터 입니다.</param>
	void AddModelInstance(std::string key, std::shared_ptr<ModelInstance> model);

	/// <summary>
	/// 모델인스턴스를 언로드합니다.
	/// *m_Models을 Clear하는 것이므로 다른 오브젝트에서 참조하고 있다면 해당 모델인스턴스는 남아있을 수 있습니다.
	/// </summary>
	void UnloadModel();

private:
	/// <summary>
	/// Obj파일을 읽어서 ModelInstance를 만들고 반환합니다.
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	std::shared_ptr<ModelInstance> ReadObj(std::string path);
};

