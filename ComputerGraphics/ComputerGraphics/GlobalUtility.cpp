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

std::shared_ptr<Object> GlobalUtility::CreateObject()
{
	auto instance = std::make_shared<Object>();
	auto t = std::make_shared<Transform>(instance);
	instance->OnAddTransform(t);

	return instance;
}
