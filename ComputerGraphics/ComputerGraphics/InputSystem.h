#pragma once
#include "stdafx.h"

/// <summary>
/// 인풋시스템입니다. 현재 입력에 대한 정보를 가지고 있습니다.
/// *싱글톤 디자인 패턴이 적용되었습니다.
/// 
/// 현재 문제점
/// - 외부에서 현재 키상태를 변경 할 수 있음(은닉 필요)
/// </summary>
class InputSystem
{
public:
	//--- 싱글톤 디자인
	InputSystem(const InputSystem&) = delete;
	InputSystem& operator=(const InputSystem&) = delete;

	/// <summary>
	/// 싱글톤 인스턴스를 얻습니다.
	/// *없는 경우 새로 만들어서 반환해줄 것입니다.
	/// </summary>
	/// <returns>싱글톤 인스턴스</returns>
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
	/// 현재 입력을 초기화합니다
	/// *이 함수는 씬 루프의 가장 마지막에 불러지게 될 것입니다.
	/// </summary>
	void ResetKey();

};

