#include "ResourceSystem.h"
#include "stdafx.h"
ResourceSystem& ResourceSystem::GetInstance()
{
	static ResourceSystem instance;
	return instance;
}

ResourceSystem::ResourceSystem()
{
}

std::shared_ptr<ModelInstance> ResourceSystem::GetSharedModelInstance(std::string key)
{
	//-- �ش� ���� �������� �ʴ� ���
	if (m_Models.find(key) == m_Models.end())
	{
		//- key�� ���� ���Ӱ� ModelInstance�� �����մϴ�.
		auto modelInstance = ReadObj(key);

		// ���� ã�� �� ���� ���
		if (modelInstance == nullptr)
		{
			return nullptr;
		}
		// ���� ã�� ���
		else
		{
			AddModelInstance(key, modelInstance);
			return modelInstance;
		}
	}
	//-- �ش� ���� �����ϴ� ���
	else
	{
		return m_Models[key];
	}
}

// *��������ڷ� �����ؾ��ϴµ� �����𸣰��� �Ф�
std::shared_ptr<ModelInstance> ResourceSystem::GetCopiedModelInstance(std::string key)
{
	auto sharedModel = GetSharedModelInstance(key);

	//ModelInstance d(sharedModel);

	//auto copiedModel = std::make_shared<ModelInstance>(sharedModel);

	return sharedModel;
}

void ResourceSystem::AddModelInstance(std::string key,std::shared_ptr<ModelInstance> model)
{
	//--- Ű�� ��ġ���� Ȯ���մϴ�.
	if (m_Models.find(key) == m_Models.end())
		m_Models.emplace(std::pair<std::string, std::shared_ptr<ModelInstance>>(key, model));
	else
		std::cout << "[ResourceSystem AddModelInstance()] �̹� �� Ű�� �ش��ϴ� ���� �ֽ��ϴ� Ű: " << key << std::endl;
}

std::shared_ptr<ModelInstance> ResourceSystem::ReadObj(std::string path)
{
	auto objFile = fopen( path.c_str(), "r");

	if (objFile == nullptr)
	{
		std::cout << "[ResourceSystem ReadObj()] ��ġ�ϴ� ������ �����ϴ�." << std::endl;
		fclose(objFile);
		return nullptr;
	}

	auto instance = std::make_shared<ModelInstance>();

	//--- 1. ��ü ���ؽ� ���� �� �ﰢ�� ���� ����
	char count[128];
	int vertexNum = 0;
	int faceNum = 0;
	while (!feof(objFile)) {
		fscanf(objFile, "%s", count);
		if (count[0] == 'v' && count[1] == '\0')
			vertexNum += 1;
		else if (count[0] == 'f' && count[1] == '\0')
			faceNum += 1;
		memset(count, '\0', sizeof(count)); // �迭 �ʱ�ȭ
	}

	//--- 3. �Ҵ�� �޸𸮿� �� ���ؽ�, ���̽� ���� �Է�
	char bind[100];
	rewind(objFile);
	while (!feof(objFile)) {
		fscanf(objFile, "%s", bind);
		if (bind[0] == 'v' && bind[1] == '\0') {
			glm::vec3 vertex = glm::vec3(1);
			
			fscanf(objFile, "%f %f %f",
				&vertex.x, &vertex.y,
				&vertex.z);

			std::cout << "("<<vertex.x <<", " <<vertex.y<< ", " << vertex.z << ")" << std::endl;

			instance->verticesPos.push_back(vertex);
		}
		else if (bind[0] == 'f' && bind[1] == '\0') {
			glm::ivec3 triesPos = glm::ivec3(1);
			glm::ivec3 triesUV = glm::ivec3(1);
			glm::ivec3 triesNormal = glm::ivec3(1);

			int result = fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d",
				&triesPos.x, &triesUV.x, &triesNormal.x, &triesPos.y, &triesUV.y, &triesNormal.y, &triesPos.z, &triesUV.z, &triesNormal.z );
			
			if (result > 0)
			{
				std::cout << "(" << triesPos.x << ", " << triesPos.y << ", " << triesPos.z << ")" << std::endl;
				instance->triesPos.push_back(triesPos);
			}
		}
	}
	fclose(objFile);

	instance->UpdateBuffer();
	return instance;
}
