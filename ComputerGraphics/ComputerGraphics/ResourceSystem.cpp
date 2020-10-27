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
	//--- 키가 겹치는지 확인합니다.
	if (m_Models.find(key) == m_Models.end())
		m_Models.emplace(std::pair<std::string, std::shared_ptr<ModelInstance>>(key, model));
	else
		std::cout << "[ResourceSystem AddModelInstance()] 이미 이 키에 해당하는 모델이 있습니다 키: " << key << std::endl;
}

std::shared_ptr<ModelInstance> ResourceSystem::ReadObj(std::string path)
{
	auto objFile = fopen( path.c_str(), "r");

	if (objFile == nullptr)
	{
		std::cout << "[ResourceSystem ReadObj()] 일치하는 파일이 없습니다." << std::endl;
		fclose(objFile);
		return nullptr;
	}

	auto instance = std::make_shared<ModelInstance>();

	//--- 1. 전체 버텍스 개수 및 삼각형 개수 세기
	char count[100];
	int vertexNum = 0;
	int faceNum = 0;
	while (!feof(objFile)) {
		fscanf(objFile, "%s", count);
		if (count[0] == 'v' && count[1] == '\0')
			vertexNum += 1;
		else if (count[0] == 'f' && count[1] == '\0')
			faceNum += 1;
		memset(count, '\0', sizeof(count)); // 배열 초기화
	}
	//--- 2. 메모리 할당
	if (instance->verticesPos != nullptr)
		instance->verticesPos.reset();
	if (instance->tries != nullptr)
		instance->tries.reset();

	instance->verticesPos = std::make_unique<std::vector<glm::vec4>>(); //new glm::vec4[vertexNum]; //(glm::vec4*)malloc(sizeof(glm::vec4) * vertexNum);
	instance->tries = std::make_unique<std::vector<glm::ivec3>>(); // face = new glm::vec4[faceNum]; //(glm::vec4*)malloc(sizeof(glm::vec4) * faceNum);

	//--- 3. 할당된 메모리에 각 버텍스, 페이스 정보 입력
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
