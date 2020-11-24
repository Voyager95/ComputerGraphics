#include "stdafx.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "SceneSystem.h"
#include "InputSystem.h"

#include "TermProject.h"

//--- 전역 변수

//--- 함수 정의
GLvoid KeyboardDown(unsigned char key, int x, int y);				// 키보드 Down이벤트 함수
GLvoid KeyboardUp(unsigned char key, int x, int y);					// 키보드 Up이벤트 함수
GLvoid DrawScene(GLvoid);											// 출력 이벤트 함수 
GLvoid Reshape(int w, int h);										// 창 변경 이벤트 함수
GLvoid Mouse(int button, int state, int x, int y);					// 마우스 클릭 이벤트 함수
GLvoid MouseMotion(int x, int y);									// 마우스 움직임 이벤트 함수
GLvoid InitialLoop(int value);										// 처음으로 돌아가는 루프입니다.

void main(int argc, char** argv)
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);											// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);		// 디스플레이 모드 설정
	glEnable(GL_DEPTH_TEST);
	glutInitWindowPosition(100, 100);								// 윈도우의 위치 지정
	glutInitWindowSize((int)WinSize::WINSIZE_X,						// 윈도우의 크기 지정
					   (int)WinSize::WINSIZE_Y);					
	GlobalUtility::GetInstance().presentWinSize_X = (int)WinSize::WINSIZE_X;
	GlobalUtility::GetInstance().presentWinSize_Y = (int)WinSize::WINSIZE_Y;
	glutCreateWindow("2015182009김태현 Assignment1");				// 윈도우 생성(윈도우 이름)

	//--- System 생성
	RenderSystem::GetInstance();									// 렌더 시스템 생성
	ResourceSystem::GetInstance();									// 리소스 시스템 생성
	SceneSystem::GetInstance();										// 씬 시스템 생성
	InputSystem::GetInstance();										// 인풋 시스템 생성

	//--- 이벤트 함수 등록
	glutDisplayFunc(DrawScene);										// 출력 함수의 지정( 즉 그릴 함수 지정)
	glutReshapeFunc(Reshape);										// 다시 그리기 함수 지정
	glutMotionFunc(MouseMotion);									// 마우스 위치
	glutTimerFunc(0, InitialLoop, 1);								// 처음
	glutKeyboardFunc(KeyboardDown);									// 마우스 Down
	glutKeyboardUpFunc(KeyboardUp);									// 키보드 Up
	glutMouseFunc(Mouse);											// 마우스 클릭
	glutMainLoop();													// 이벤트 처리 시작
}


/// <summary>
/// 그리기 콜백 함수 
/// </summary>
/// <returns></returns>
GLvoid DrawScene()
{	
	//--- 렌더시스템으로 그립니다.
	RenderSystem& renderSys = RenderSystem::GetInstance();
	renderSys.Render();
}

/// <summary>
/// 다시 그리기 콜백 함수
/// </summary>
/// <param name="w"></param>
/// <param name="h"></param>
/// <returns></returns>
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	//--- 변경된 창 사이즈 적용
	GlobalUtility::GetInstance().presentWinSize_X = w;
	GlobalUtility::GetInstance().presentWinSize_Y = h;

}

/// <summary>
/// 마우스 움직임
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns>없음</returns>
GLvoid MouseMotion(int x, int y)
{
	InputSystem& is = InputSystem::GetInstance();

	float xCoordinate = x - (GlobalUtility::GetInstance().presentWinSize_X / 2);
	float yCoordinate = -(y - (GlobalUtility::GetInstance().presentWinSize_Y / 2));

	float normalizedX = xCoordinate / (GlobalUtility::GetInstance().presentWinSize_X / 2);
	float normalizedY = yCoordinate / (GlobalUtility::GetInstance().presentWinSize_Y / 2);

	is.SetMousePos(glm::vec2(normalizedX, normalizedY));
}

/// <summary>
/// 마우스 클릭
/// </summary>
/// <param name="button"></param>
/// <param name="state"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns>없음</returns>
GLvoid Mouse(int button, int state, int x, int y)
{
	InputSystem& is = InputSystem::GetInstance();

	float xCoordinate = x - ((float)WinSize::WINSIZE_X / 2);
	float yCoordinate = -(y - ((float)WinSize::WINSIZE_Y / 2));

	float normalizedX = xCoordinate / ((float)WinSize::WINSIZE_X / 2);
	float normalizedY = yCoordinate / ((float)WinSize::WINSIZE_Y / 2);

	if (state == GLUT_DOWN)
	{
		is.SetMouseDown(button, true);
		is.SetMouse(button, true);
	}

	if (state == GLUT_UP)
	{
		is.SetMouse(button, false);
		is.SetMouseUp(button, true);
	}
}

/// <summary>
/// 키보드 Down 처리 메소드
/// </summary>
/// <param name="key">입력한 키</param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns>없음</returns>
GLvoid KeyboardDown(unsigned char key, int x, int y)
{
	InputSystem& is = InputSystem::GetInstance();

	char receivedKey = key;
	if (islower(receivedKey) != 0)
		receivedKey = toupper(receivedKey);

	is.SetKey(receivedKey, true);
	is.SetKeyDown(receivedKey, true);
}

/// <summary>
/// 키보드 Down 처리 메소드
/// </summary>
/// <param name="key">입력한 키</param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns>없음</returns>
GLvoid KeyboardUp(unsigned char key, int x, int y)
{
	InputSystem& is = InputSystem::GetInstance();

	char receivedKey = key;
	if (islower(receivedKey) != 0)
		receivedKey = toupper(receivedKey);


	is.SetKey(receivedKey, false);
	is.SetKeyUp(receivedKey,true);
}

GLvoid InitialLoop(int value)
{
	auto scene = std::make_shared<TermProject>();

	auto& ss = SceneSystem::GetInstance();

	ss.StartScene(std::static_pointer_cast<Scene>(scene));
}
