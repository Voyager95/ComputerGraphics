#include <iostream>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

/// <summary>
/// 윈도우 출력하고 콜백함수 설정 
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
void main(int argc, char** argv)
{ 
	//--- 윈도우 생성하기
	glutInit(&argc, argv);											// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);					// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);								// 윈도우의 위치 지정
	glutInitWindowSize(250, 250);									// 윈도우의 크기 지정
	glutCreateWindow("Example1");									// 윈도우 생성(윈도우 이름)
		
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew(즉 Open GL) 초기화
	{
		std::cerr <<  "Unable to initialize GLEW" << std::endl
			;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	glutDisplayFunc(drawScene);										// 출력 함수의 지정( 즉 그릴 함수 지정)
	glutReshapeFunc(Reshape);										// 다시 그리기 함수 지정
	glutMainLoop();													// 이벤트 처리 시작 
}

/// <summary>
/// 그리기 콜백 함수 
/// </summary>
/// <returns></returns>
GLvoid drawScene()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);							// 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT);									// 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현
	//--- 그리기 관련 부분이 여기에 포함된다.
	glutSwapBuffers(); // 화면에 출력하기
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