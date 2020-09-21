#include <iostream>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>

// 타입 정의

struct Colorf
{
public:
	GLclampf r, g, b, a;

	Colorf()
	{
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		a = 0.0f;
	}

	Colorf(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	void Set(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};


// 함수 정의

GLvoid Timer(int value);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);

// 전역 변수
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> colorDis(0.0f, 1.0f);

Colorf rectColor(1.0f,0.0f, 0.0f, 0.0f);
Colorf bgColor(1.0f, 0.0f, 1.0f, 0.0f);


// 사각형 크기

float rectW = 0.4;
float rectH = 0.4;

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
		std::cerr << "Unable to initialize GLEW" << std::endl
			;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutTimerFunc(100, Timer, 1);
	glutDisplayFunc(drawScene);										// 출력 함수의 지정( 즉 그릴 함수 지정)
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);										// 다시 그리기 함수 지정
	glutMainLoop();													// 이벤트 처리 시작 
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	char receivedKey = key;
	if (islower(receivedKey) != 0)
		receivedKey = toupper(receivedKey);

	switch (receivedKey) {
	case 'R':														// 배경색을 빨강색으로 설정
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 'G':
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 'B':
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 'A':
		glClearColor(colorDis(gen), colorDis(gen), colorDis(gen), 1.0f);
		break;
	case 'W':
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		break;
	default:
		break;
	}
	glutPostRedisplay();											//배경색이 바뀔때마다 출력 콜백함수를 호출하여 화면을 refresh 한다
}


GLvoid Mouse(int button, int state, int x, int y)
{
	std::cout << x << " , " << y << std::endl;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (-rectH * 0.5 < y && y < rectH * 0.5 && -rectW * 0.5 < x && x < rectW * 0.5)
			rectColor.Set(colorDis(gen), colorDis(gen), colorDis(gen), 1.0f);
		else
			bgColor.Set(colorDis(gen), colorDis(gen), colorDis(gen), 1.0f);

		glutPostRedisplay();	
	}
}

/// <summary>
/// 그리기 콜백 함수 
/// </summary>
/// <returns></returns>
GLvoid drawScene()
{
	std::cout << "다시 그림" << std::endl;

	glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	glClear(GL_COLOR_BUFFER_BIT);									// 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현
	
	glColor3f(rectColor.r, rectColor.g, rectColor.b);
	glRectf( -rectW * 0.5,-rectH*0.5 , rectW * 0.5, rectH * 0.5);
	

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

GLvoid Timer(int value)
{


	glutTimerFunc(500, Timer, 1);
}