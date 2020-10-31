#include "stdafx.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "SceneSystem.h"


#include "Scene.h"
#include "Object.h"
#include "Renderer.h"
#include "Transform.h"

//--- 전역 변수
const unsigned int TIMER_CYCLE = 100;
unsigned int WINSIZE_X = 800;
unsigned int WINSIZE_Y = 800;

//--- 함수 정의
GLvoid Keyboard(unsigned char key, int x, int y);					// 키보드 이벤트 함수
GLvoid DrawScene(GLvoid);											// 출력 이벤트 함수 
GLvoid Reshape(int w, int h);										// 창 변경 이벤트 함수
GLvoid Mouse(int button, int state, int x, int y);					// 마우스 클릭 이벤트 함수
GLvoid MouseMotion(int x, int y);									// 마우스 움직임 이벤트 함수

void main(int argc, char** argv)
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);											// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);					// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);								// 윈도우의 위치 지정
	glutInitWindowSize(WINSIZE_X, WINSIZE_Y);						// 윈도우의 크기 지정
	glutCreateWindow("Example");									// 윈도우 생성(윈도우 이름)

	//--- System 생성
	RenderSystem::GetInstance();									// 렌더 시스템 생성
	ResourceSystem::GetInstance();									// 리소스 시스템 생성
	SceneSystem& ss = SceneSystem::GetInstance();					// 씬 시스템 생성

		//--- 초기 씬 시작
	std::shared_ptr<Scene> exercise16 = std::make_shared<Scene>();

	std::shared_ptr<Object> cube = std::make_shared<Object>("Cube");

	auto t =  cube->GetTransform();
	std::cout << t->GetObjectW()->name << std::endl;

	auto cubeRenderer = std::make_shared<Renderer>(cube);
	cubeRenderer->SetSharedModel("Cube.obj");

	cube->AddComponent(cubeRenderer);
	exercise16->AddObject(cube);


	ss.StartScene(exercise16);

	//--- 이벤트 함수 등록
	glutDisplayFunc(DrawScene);										// 출력 함수의 지정( 즉 그릴 함수 지정)
	glutReshapeFunc(Reshape);										// 다시 그리기 함수 지정
	glutMotionFunc(MouseMotion);
	glutKeyboardFunc(Keyboard);										// 마우스 입력
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

	//--- 변경된 배경색 설정
	glClearColor(0.5, 0.5, 0.5, 1.0f);
	//glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 렌더링 파이프라인에 세이더 불러오기
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
}

/// <summary>
/// 마우스 움직임
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
GLvoid MouseMotion(int x, int y)
{
	//std::cout << x << " , " << y << std::endl;

	float xCoordinate = x - (WINSIZE_X / 2);
	float yCoordinate = -(y - (WINSIZE_X / 2));

	float normalizedX = xCoordinate / (WINSIZE_X / 2);
	float normalizedY = yCoordinate / (WINSIZE_X / 2);
}

/// <summary>
/// 마우스 클릭
/// </summary>
/// <param name="button"></param>
/// <param name="state"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
GLvoid Mouse(int button, int state, int x, int y)
{
	//std::cout << x << " , " << y << std::endl;

	float xCoordinate = x - (WINSIZE_X / 2);
	float yCoordinate = -(y - (WINSIZE_Y / 2));

	float normalizedX = xCoordinate / (WINSIZE_X / 2);
	float normalizedY = yCoordinate / (WINSIZE_Y / 2);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
	}
}

/// <summary>
/// 키보드 움직임
/// </summary>
/// <param name="key"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
GLvoid Keyboard(unsigned char key, int x, int y)
{
	char receivedKey = key;
	if (islower(receivedKey) != 0)
		receivedKey = toupper(receivedKey);

	switch (receivedKey) {
	case 'T':
		break;
	case 'S':
		break;
	default:
		break;
	}
	glutPostRedisplay();
}