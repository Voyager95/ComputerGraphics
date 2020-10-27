#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <gl/glm/glm.hpp>
#include <map>
#include "ModelInstnce.h"

/// <summary>
/// ���� ���ҽ��� �����ϴ� �ý����Դϴ�.
/// ���� ���ҽ��� ������ �Ҹ��� �ʰ� ������ �ݴϴ�.
/// </summary>
class ResourceSystem
{
public:
	//--- �̱��� ������
	ResourceSystem(const ResourceSystem&) = delete;
	ResourceSystem& operator=(const ResourceSystem&) = delete;

	/// <summary>
	/// �̱��� �ν��Ͻ�
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
	std::shared_ptr<ModelInstance> GetModelInstance(std::string key);

	/// <summary>
	/// Ư���н��� �ִ� ������Ʈ�� ã�� 
	/// </summary>
	/// <param name="key"></param>
	void AddModelInstance(std::string path);

	/// <summary>
	/// Ư�� ���ν��Ͻ��� �߰��մϴ�.
	/// </summary>
	/// <param name="key">�� ���� Ű�Դϴ�.</param>
	/// <param name="model">���� �ν��Ͻ� ������ �Դϴ�.</param>
	void AddModelInstance(std::string key, std::shared_ptr<ModelInstance> model);

	/// <summary>
	/// ���ν��Ͻ��� ��ε��մϴ�.
	/// *m_Models�� Clear�ϴ� ���̹Ƿ� �ٸ� ������Ʈ���� �����ϰ� �ִٸ� �ش� ���ν��Ͻ��� �������� �� �ֽ��ϴ�.
	/// </summary>
	void UnloadModel();

private:
	/// <summary>
	/// Obj������ �о ModelInstance�� ����� ��ȯ�մϴ�.
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	std::shared_ptr<ModelInstance> ReadObj(std::string path);
};

