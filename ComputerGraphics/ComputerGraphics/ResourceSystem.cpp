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

void ResourceSystem::AddTextureInstance(std::string key, std::shared_ptr<TextureInstance> texture)
{
    //--- 키가 겹치는지 확인합니다.
    if (m_Texes.find(key) == m_Texes.end())
        m_Texes.emplace(std::pair<std::string, std::shared_ptr<TextureInstance>>(key, texture));
    else
        std::cout << "[ResourceSystem AddTextureInstance()] 이미 이 키에 해당하는 모델이 있습니다 키: " << key << std::endl;
}

std::shared_ptr<TextureInstance> ResourceSystem::GetSharedTextureInstance(std::string key)
{
    //-- 해당 모델이 존재하지 않는 경우
    if (m_Texes.find(key) == m_Texes.end())
    {
        //- key를 통해 새롭게 ModelInstance를 생성합니다.
        auto textureInstance = ReadTex(key);

        // 모델을 찾을 수 없는 경우
        if (textureInstance == nullptr)
        {
            return nullptr;
        }
        // 모델을 찾은 경우
        else
        {
            AddTextureInstance(key, textureInstance);
            return textureInstance;
        }
    }
    //-- 해당 모델이 존재하는 경우
    else
    {
        return m_Texes[key];
    }
}

std::shared_ptr<ModelInstance> ResourceSystem::ReadObj(std::string path)
{
    auto instance = std::make_shared<ModelInstance>();

    std::ifstream in(path.c_str());

    if (!in.is_open())
    {
        std::cout << "ReadObj(const char*, float*&, float*& float*&, int*&)" << std::endl;
        std::cout << path << " 파일을 읽지 못하였습니다." << std::endl;
        return nullptr;
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

    std::vector<float> dupPosBuffer; // Allowing Duplicating  중첩을 허용
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

    auto vertexCount = noDupLocations.size();
    auto indexCount = rawIndexCount;

    for (int i = 0; i < vertexCount; ++i)
    {
        instance->verticesPos.push_back(glm::vec3(
            dupPosBuffer[noDupLocations[i] * 3 + 0],
            dupPosBuffer[noDupLocations[i] * 3 + 1],
            dupPosBuffer[noDupLocations[i] * 3 + 2]));

        instance->verticesNormal.push_back(glm::vec3(
            dupNormalBuffer[noDupLocations[i] * 3 + 0],
            dupNormalBuffer[noDupLocations[i] * 3 + 1],
            dupNormalBuffer[noDupLocations[i] * 3 + 2]));

        instance->verticesUV.push_back(glm::vec2(
            dupTextureCoordinateBuffer[noDupLocations[i] * 2 + 0],
            dupTextureCoordinateBuffer[noDupLocations[i] * 2 + 1]));
    }


    for (int i = 0; i < indexCount/3; ++i)
    {
        instance->triesIndex.push_back(glm::ivec3(
            oldIndexToNewIndexDict[dupIndexBuffer[i *3 + 0]],
            oldIndexToNewIndexDict[dupIndexBuffer[i *3+ 1]],
            oldIndexToNewIndexDict[dupIndexBuffer[i *3 + 2]]
        ));
    }

    //for (auto i = instance->triesIndex.begin(); i != instance->triesIndex.end(); ++i)
    //{
    //    std::cout << "("<< i->x << ", " << i->y << ", " << i->z <<")" << std::endl;
    //    auto first = instance->verticesPos[i->x];
    //    std::cout << "first: (" << first.x << ", " << first.y << ", " << first.z << ")" << std::endl;
    //    auto second = instance->verticesPos[i->y];
    //    std::cout << "second (" << second.x << ", " << second.y << ", " << second.z << ")" << std::endl;
    //    auto third = instance->verticesPos[i->z];
    //    std::cout << "third (" << third.x << ", " << third.y << ", " << third.z << ")" << std::endl;
    //}

    instance->UpdateBuffer();

    return instance;
}

std::shared_ptr<TextureInstance> ResourceSystem::ReadTex(std::string path)
{
	auto instance = std::make_shared<TextureInstance>();
	
	stbi_set_flip_vertically_on_load(true);
	instance->data = stbi_load(path.c_str(), &instance->width, &instance->height, &instance->numberOfChannel, 0);

    glGenTextures(1, &instance->texture);
    glBindTexture(GL_TEXTURE_2D, instance->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, instance->width, instance->height, 0, GL_RGB, GL_UNSIGNED_BYTE, instance->data);



	return instance;
}
