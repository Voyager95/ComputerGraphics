#include "stdafx.h"
#include "GlobalUtility.h"
#include "Object.h"
#include "Transform.h"

GlobalUtility& GlobalUtility::GetInstance()
{
	static GlobalUtility instance;
	return instance;
}

GlobalUtility::GlobalUtility()
{
	//--- WinSize
	presentWinSize_X = (int)WinSize::WINSIZE_X;
	presentWinSize_Y = (int)WinSize::WINSIZE_Y;
}

glm::vec3 GlobalUtility::Lerp(glm::vec3 from, glm::vec3 to, float factor)
{
	return from * (1 - factor) + to * factor;
}

void GlobalUtility::PrintVec3(std::string name, glm::vec3 value)
{
	std::cout << name << ": " << value.x << " " << value.y << " " << value.z << std::endl;
}
