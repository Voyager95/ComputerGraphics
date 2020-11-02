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
	//-- 해당 모델이 존재하지 않는 경우
	if (m_Models.find(key) == m_Models.end())
	{
		//- key를 통해 새롭게 ModelInstance를 생성합니다.
		auto modelInstance = ReadObj(key);

		// 모델을 찾을 수 없는 경우
		if (modelInstance == nullptr)
		{
			return nullptr;
		}
		// 모델을 찾은 경우
		else
		{
			AddModelInstance(key, modelInstance);
			return modelInstance;
		}
	}
	//-- 해당 모델이 존재하는 경우
	else
	{
		return m_Models[key];
	}
}

// *복사생성자로 복사해야하는데 아직모르겠음 ㅠㅠ
std::shared_ptr<ModelInstance> ResourceSystem::GetCopiedModelInstance(std::string key)
{
	auto sharedModel = GetSharedModelInstance(key);

	//ModelInstance d(sharedModel);

	//auto copiedModel = std::make_shared<ModelInstance>(sharedModel);

	return sharedModel;
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
	char count[128];
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

	//--- 3. 할당된 메모리에 각 버텍스, 페이스 정보 입력
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
