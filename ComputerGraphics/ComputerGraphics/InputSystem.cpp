#include "stdafx.h"
#include "InputSystem.h"

InputSystem& InputSystem::GetInstance()
{
	static InputSystem instance;
	return instance;
}

InputSystem::InputSystem()
{
}

bool InputSystem::GetKeyDown(char key)
{
	return keyDown[key];
}

bool InputSystem::GetKey(char targetKey)
{
	return key[targetKey];
}

bool InputSystem::GetKeyUp(char key)
{
	return keyUp[key];
}

bool InputSystem::GetMouseDown(char button)
{
	return mouseDown[button];
}

bool InputSystem::GetMouse(char button)
{
	return mouse[button];
}

bool InputSystem::GetMouseUp(char button)
{
	return mouseUp[button];
}

void InputSystem::SetKeyDown(char key, bool value)
{
	keyDown[key] = value;
}

void InputSystem::SetKey(char targetKey, bool value)
{
	key[targetKey] = value;
}

void InputSystem::SetKeyUp(char key, bool value)
{
	keyUp[key] = value;
}

void InputSystem::SetMouseDown(char button, bool value)
{
	mouseDown[button] = value;
}

void InputSystem::SetMouse(char button, bool value)
{
	mouse[button] = value;
}

void InputSystem::SetMouseUp(char button, bool value)
{
	mouseUp[button] = value;
}

void InputSystem::ResetKey()
{
	for (auto k = keyUp.begin(); k != keyUp.end(); ++k)
	{
		k->second = false;
	}

	for (auto k = keyDown.begin(); k != keyDown.end(); ++k)
	{
		k->second = false;
	}

	for (auto k = mouseUp.begin(); k != mouseUp.end(); ++k)
	{
		k->second = false;
	}

	for (auto k = mouseDown.begin(); k != mouseDown.end(); ++k)
	{
		k->second = false;
	}
}
