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

std::shared_ptr<ModelInstance> ResourceSystem::GetModelInstance(std::string key)
{
	return std::shared_ptr<ModelInstance>();
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
	char count[100];
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
	//--- 2. �޸� �Ҵ�
	if (instance->verticesPos != nullptr)
		instance->verticesPos.reset();
	if (instance->tries != nullptr)
		instance->tries.reset();

	instance->verticesPos = std::make_unique<std::vector<glm::vec4>>(); //new glm::vec4[vertexNum]; //(glm::vec4*)malloc(sizeof(glm::vec4) * vertexNum);
	instance->tries = std::make_unique<std::vector<glm::ivec3>>(); // face = new glm::vec4[faceNum]; //(glm::vec4*)malloc(sizeof(glm::vec4) * faceNum);

	//--- 3. �Ҵ�� �޸𸮿� �� ���ؽ�, ���̽� ���� �Է�
	char bind[100];
	rewind(objFile);
	while (!feof(objFile)) {
		fscanf(objFile, "%s", bind);
		if (bind[0] == 'v' && bind[1] == '\0') {
			glm::vec4 vertex = glm::vec4(1);
			
			fscanf(objFile, "%f %f %f",
				vertex.x, vertex.y,
				vertex.z);

			instance->verticesPos.get()->push_back(vertex);
		}
		else if (bind[0] == 'f' && bind[1] == '\0') {
			glm::ivec4 tri = glm::ivec4(1);

			fscanf(objFile, "%f %f %f",
				tri.x, tri.y, tri.z);

			instance->tries.get()->push_back(tri);
		}
	}
	fclose(objFile);
	return instance;
}
