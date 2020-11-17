#pragma once
#include "stdafx.h"

/// <summary>
/// ��ǲ�ý����Դϴ�. ���� �Է¿� ���� ������ ������ �ֽ��ϴ�.
/// *�̱��� ������ ������ ����Ǿ����ϴ�.
/// 
/// ���� ������
/// - �ܺο��� ���� Ű���¸� ���� �� �� ����(���� �ʿ�)
/// </summary>
class InputSystem
{
public:
	//--- �̱��� ������
	InputSystem(const InputSystem&) = delete;
	InputSystem& operator=(const InputSystem&) = delete;

	/// <summary>
	/// �̱��� �ν��Ͻ��� ����ϴ�.
	/// *���� ��� ���� ���� ��ȯ���� ���Դϴ�.
	/// </summary>
	/// <returns>�̱��� �ν��Ͻ�</returns>
	static InputSystem& GetInstance();

private:
	//--- Key
	std::map<char, bool> keyDown;
	std::map<char, bool> key;
	std::map<char, bool> keyUp;

	//---Mouse
	std::map<char, bool> mouseDown;							
	std::map<char, bool> mouse;
	std::map<char, bool> mouseUp;
	glm::vec2 mousePosition;

	//--- Constructor
	InputSystem();
	
public:
	//---Getter
	//-- Key
	bool GetKeyDown(char key);
	bool GetKey(char key);
	bool GetKeyUp(char key);
	//-- Mouse
	bool GetMouseDown(char button);
	bool GetMouse(char button);
	bool GetMouseUp(char button);
	glm::vec2 GetMousePos() { return mousePosition; }
	//---Setter
	//-- Key
	void SetKeyDown(char key, bool value);
	void SetKey(char key, bool value);
	void SetKeyUp(char key, bool value);
	//-- Mouse
	void SetMouseDown(char button, bool value);
	void SetMouse(char button, bool value);
	void SetMouseUp(char button, bool value);
	void SetMousePos(glm::vec2 pos) { mousePosition = pos; }

	/// <summary>
	/// ���� �Է��� �ʱ�ȭ�մϴ�
	/// *�� �Լ��� �� ������ ���� �������� �ҷ����� �� ���Դϴ�.
	/// </summary>
	void ResetKey();

};

