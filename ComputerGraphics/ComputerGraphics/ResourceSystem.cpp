#include "stdafx.h"
#include "ResourceSystem.h"
#include "ModelInstnce.h"
#include "TextureInstance.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

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

std::shared_ptr<TextureInstance> ResourceSystem::GetSharedTextureInstance(std::string key)
{
	
	return nullptr;
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

bool ResourceSystem::ReadObj(const char* objFileName, float*& vPosOut, float*& vNormalOut, float*& vTextureCoordinateOut, int*& indexOut, int& vertexCount, int& indexCount)
{
    std::ifstream in(objFileName);

    if (!in.is_open())
    {
        std::cout << "ReadObj(const char*, float*&, float*& float*&, int*&)" << std::endl;
        std::cout << objFileName << " ������ ���� ���Ͽ����ϴ�." << std::endl;
        return false;
    }

    std::vector<float> rawPositionBuffer;
    std::vector<float> rawNormalBuffer;
    std::vector<float> rawTextureCoordinateBuffer;

    std::vector<int> rawPosIndexBuffer;
    std::vector<int> rawNormalIndexBuffer;
    std::vector<int> rawTextureCoordinateIndexBuffer;

    float tempFloat;
    std::string tempString;

    while (!in.eof())
    {
        in >> tempString;

        if (tempString.size() == 1 && tempString[0] == 'v')
        {
            in >> tempFloat;
            rawPositionBuffer.push_back(tempFloat);
            in >> tempFloat;
            rawPositionBuffer.push_back(tempFloat);
            in >> tempFloat;
            rawPositionBuffer.push_back(tempFloat);
        }
        else if (tempString.size() == 2 && tempString[0] == 'v' && tempString[1] == 'n')
        {
            in >> tempFloat;
            rawNormalBuffer.push_back(tempFloat);
            in >> tempFloat;
            rawNormalBuffer.push_back(tempFloat);
            in >> tempFloat;
            rawNormalBuffer.push_back(tempFloat);
        }
        else if (tempString.size() == 2 && tempString[0] == 'v' && tempString[1] == 't')
        {
            in >> tempFloat;
            rawTextureCoordinateBuffer.push_back(tempFloat);
            in >> tempFloat;
            rawTextureCoordinateBuffer.push_back(tempFloat);
        }
        else if (tempString.size() == 1 && tempString[0] == 'f')
        {
            for (int i = 0; i < 3; ++i)
            {
                in >> tempString;

                std::istringstream iss(tempString);

                std::getline(iss, tempString, '/');
                rawPosIndexBuffer.push_back(atoi(tempString.c_str()) - 1);

                std::getline(iss, tempString, '/');
                rawTextureCoordinateIndexBuffer.push_back(atoi(tempString.c_str()) - 1);

                std::getline(iss, tempString, '/');
                rawNormalIndexBuffer.push_back(atoi(tempString.c_str()) - 1);
            }
        }
    }

    std::vector<float> dupPosBuffer; // Allowing Duplicating  ��ø�� ���
    std::vector<float> dupNormalBuffer;
    std::vector<float> dupTextureCoordinateBuffer;
    std::vector<int> dupIndexBuffer;

    int rawIndexCount = rawPosIndexBuffer.size();

    for (int i = 0; i < rawIndexCount; ++i)
    {
        dupPosBuffer.push_back(rawPositionBuffer[rawPosIndexBuffer[i] * 3 + 0]);
        dupPosBuffer.push_back(rawPositionBuffer[rawPosIndexBuffer[i] * 3 + 1]);
        dupPosBuffer.push_back(rawPositionBuffer[rawPosIndexBuffer[i] * 3 + 2]);

        dupNormalBuffer.push_back(rawNormalBuffer[rawNormalIndexBuffer[i] * 3 + 0]);
        dupNormalBuffer.push_back(rawNormalBuffer[rawNormalIndexBuffer[i] * 3 + 1]);
        dupNormalBuffer.push_back(rawNormalBuffer[rawNormalIndexBuffer[i] * 3 + 2]);

        dupTextureCoordinateBuffer.push_back(rawTextureCoordinateBuffer[rawTextureCoordinateIndexBuffer[i] * 2 + 0]);
        dupTextureCoordinateBuffer.push_back(rawTextureCoordinateBuffer[rawTextureCoordinateIndexBuffer[i] * 2 + 1]);

        dupIndexBuffer.push_back(i);
    }

    std::vector<int> noDupLocations;
    noDupLocations.resize(dupIndexBuffer.size());
    std::iota(noDupLocations.begin(), noDupLocations.end(), 0);

    std::map<int, int> oldIndexToNewIndexDict;

    int checkIndex = 0;
    do
    {
        for (int i = checkIndex + 1; i < (int)noDupLocations.size(); ++i)
        {
            if (!CheckSame(dupPosBuffer, noDupLocations[checkIndex], noDupLocations[i], 3))
                continue;

            if (!CheckSame(dupNormalBuffer, noDupLocations[checkIndex], noDupLocations[i], 3))
                continue;

            if (!CheckSame(dupTextureCoordinateBuffer, noDupLocations[checkIndex], noDupLocations[i], 2))
                continue;

            oldIndexToNewIndexDict.emplace(noDupLocations[i], checkIndex);
            noDupLocations.erase(noDupLocations.begin() + i);

            --i;
        }

        ++checkIndex;
    } while (checkIndex < (int)noDupLocations.size());

    for (int i = 0; i < (int)noDupLocations.size(); ++i)
        oldIndexToNewIndexDict.emplace(noDupLocations[i], i);

    vertexCount = noDupLocations.size();
    indexCount = rawIndexCount;
    vPosOut = new float[vertexCount * 3];
    vNormalOut = new float[vertexCount * 3];
    vTextureCoordinateOut = new float[vertexCount * 2];
    indexOut = new int[indexCount];

    for (int i = 0; i < vertexCount; ++i)
    {
        vPosOut[i * 3 + 0] = dupPosBuffer[noDupLocations[i] * 3 + 0];
        vPosOut[i * 3 + 1] = dupPosBuffer[noDupLocations[i] * 3 + 1];
        vPosOut[i * 3 + 2] = dupPosBuffer[noDupLocations[i] * 3 + 2];

        vNormalOut[i * 3 + 0] = dupNormalBuffer[noDupLocations[i] * 3 + 0];
        vNormalOut[i * 3 + 1] = dupNormalBuffer[noDupLocations[i] * 3 + 1];
        vNormalOut[i * 3 + 2] = dupNormalBuffer[noDupLocations[i] * 3 + 2];

        vTextureCoordinateOut[i * 2 + 0] = dupTextureCoordinateBuffer[noDupLocations[i] * 2 + 0];
        vTextureCoordinateOut[i * 2 + 1] = dupTextureCoordinateBuffer[noDupLocations[i] * 2 + 1];
    }


    for (int i = 0; i < indexCount; ++i)
    {
        indexOut[i] = oldIndexToNewIndexDict[dupIndexBuffer[i]];
    }

    return true;
}

std::shared_ptr<TextureInstance> ResourceSystem::ReadTex(std::string path)
{
	auto instance = std::make_shared<TextureInstance>();
	
	stbi_set_flip_vertically_on_load(true);
	instance->data = stbi_load(path.c_str(), &instance->width, &instance->height, &instance->numberOfChannel, 0);


	return std::shared_ptr<TextureInstance>();
}
