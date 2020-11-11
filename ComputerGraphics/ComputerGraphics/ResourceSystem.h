#pragma once
#include "stdafx.h"

class ModelInstance;
class TextureInstance;

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

	std::map<std::string, std::shared_ptr<TextureInstance>> m_Texes;
public:
	ResourceSystem();

	//--- Model

	/// <summary>
	/// �ش� Ű�� �´� ���ν��Ͻ��� ��ȯ�մϴ�.
	/// �ε�Ǿ��ִ� ���� ���� ��쿡 �ش� Ű�� path�� �Ͽ� obj������ ã�� ���ν��Ͻ��� �����Ͽ� ��ȯ�մϴ�.
	/// </summary>
	/// <param name="key">���ν��Ͻ��� Ű</param>
	/// <returns>Ű�� �ش��ϴ� ���ν��Ͻ��� ��ȯ�մϴ�. *�ش��ν��Ͻ��� ��ȯ�� �� ���� ��, Null���� ����</returns>
	std::shared_ptr<ModelInstance> GetSharedModelInstance(std::string key);

	/// <summary>
	/// ���� �Ͽ� ��ȯ���ݴϴ�
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	std::shared_ptr<ModelInstance> GetCopiedModelInstance(std::string key);

	/// <summary>
	/// Ư�� ���ν��Ͻ��� �߰��մϴ�.
	/// </summary>
	/// <param name="key">�� ���� Ű�Դϴ�.</param>
	/// <param name="model">���� �ν��Ͻ� ������ �Դϴ�.</param>
	void AddModelInstance(std::string key, std::shared_ptr<ModelInstance> model);

	void AddTextureInstance(std::string key, std::shared_ptr<TextureInstance> texture);

	/// <summary>
	/// ���ν��Ͻ��� ��ε��մϴ�.
	/// *m_Models�� Clear�ϴ� ���̹Ƿ� �ٸ� ������Ʈ���� �����ϰ� �ִٸ� �ش� ���ν��Ͻ��� �������� �� �ֽ��ϴ�.
	/// </summary>
	void UnloadModel();


	//--- Texture

	std::shared_ptr<TextureInstance> GetSharedTextureInstance(std::string key);

	std::shared_ptr<TextureInstance> GetCopiedTextureInstance(std::string key);

	void UnloadTextrue();

private:
	/// <summary>
	/// Obj������ �о ModelInstance�� ����� ��ȯ�մϴ�.
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	std::shared_ptr<ModelInstance> ReadObj(std::string path);

    template<class T>
    bool CheckSame(T& container, int index_0, int index_1, int count)
    {
        for (int i = 0; i < count; ++i)
        {
            if (container[index_0 * count + i] != container[index_1 * count + i])
                return false;
        }

        return true;
    }

	std::shared_ptr<TextureInstance> ReadTex(std::string path);
};

