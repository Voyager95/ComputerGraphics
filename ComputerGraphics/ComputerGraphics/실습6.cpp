#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <array>
#include <random>
#include <memory>
#include <cmath>

#define SHAPENUM 10
#define PI 3.14159265
using namespace std;

// 타이머
unsigned int timerCycle = 100;

float getRadian(float angle);
void make_vertexShader();
void make_fragmentShader();
void InitBuffer();
void InitShader();
GLvoid Timer(int value);
char* filetobuf(const char* file);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);

GLchar* vertexsource, * fragmentsource; // 소스코드 저장 변수
GLuint vertexshader, fragmentshader; // 세이더 객체
array<GLuint, SHAPENUM> s_programs; // 세이더 프로그램

array<GLuint, SHAPENUM> vao;
array<GLuint[2], SHAPENUM> vbo;

array< vector< array<GLfloat,3 >>, SHAPENUM > shapePos;
array<vector<array<GLfloat, 3>>, SHAPENUM> shapeColor;
array<bool, 10> shapeAnim;
array<array<GLfloat, 3>, SHAPENUM> shapeOrin;
array<GLfloat, SHAPENUM> shapeRadius;
array<GLfloat, SHAPENUM> shapeAngle;
array<int, SHAPENUM> shapeTriNum = {0,};

int nextShapeIndex = 0;

float winSizeX = 800;
float winSizeY = 800;
GLfloat one[3];
GLfloat two[3];

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
	glutInitWindowSize(winSizeX, winSizeY);									// 윈도우의 크기 지정
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

	InitShader();
	InitBuffer();

	glutDisplayFunc(drawScene);										// 출력 함수의 지정( 즉 그릴 함수 지정)
	glutReshapeFunc(Reshape);										// 다시 그리기 함수 지정
	glutTimerFunc(timerCycle, Timer, 1);
	glutMouseFunc(Mouse);
	glutMainLoop();													// 이벤트 처리 시작 
}

void make_vertexShader()
{
	vertexsource = filetobuf("vertex.glsl");
	//--- 버텍스 세이더 객체 만들기
	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(vertexshader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, errorLog);
		cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;
		//return false;
	}
}

void make_fragmentShader()
{
	fragmentsource = filetobuf("fragment.glsl");
	//--- 프래그먼트 세이더 객체 만들기
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(fragmentshader);
	//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
		cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << endl;
		//return false;
	}
}

void InitBuffer()
{
	for (int i = 0; i < SHAPENUM; ++i)
	{
		glGenVertexArrays(1, &vao[i]); //--- VAO 를 지정하고 할당하기
		glBindVertexArray(vao[i]); //--- VAO를 바인드하기
		glGenBuffers(2, vbo[i]); //--- 2개의 VBO를 지정하고 할당하기

		//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, vbo[i][0]);
		// 변수 triShape 에서 버텍스 데이터 값을 버퍼에 복사한다.
		// triShape 배열의 사이즈:
		if (shapePos[i].size() > 0)
		{
			glBufferData(GL_ARRAY_BUFFER, shapePos[i].size() * sizeof(GLfloat) * 3, &shapePos[i][0], GL_STATIC_DRAW);
		}
		// 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		// attribute 인덱스 0번을 사용가능하게 함
		glEnableVertexAttribArray(0);

		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, vbo[i][1]);
		// 변수 colors에서 버텍스 색상을 복사한다.
		// colors 배열의 사이즈: 9 *float
		if (shapeColor[i].size() > 0)
		{
			glBufferData(GL_ARRAY_BUFFER, shapeColor[i].size() * sizeof(GLfloat) * 3, &shapeColor[i][0], GL_STATIC_DRAW);
		}
		// 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		// attribute 인덱스 1번을 사용 가능하게 함.
		glEnableVertexAttribArray(1);
	}
}

void InitShader()
{
	make_vertexShader();
	make_fragmentShader();
	//-- shader Program
	for (int i = 0; i < SHAPENUM; ++i)
	{
		s_programs[i] = glCreateProgram();
		glAttachShader(s_programs[i], vertexshader);
		glAttachShader(s_programs[i], fragmentshader);
		glLinkProgram(s_programs[i]);

		//--- Shader Program 사용하기
		glUseProgram(s_programs[i]);
	}

	//checkCompileErrors(s_program, "PROGRAM");




	//--- 세이더 삭제하기
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
}

/// <summary>
/// 그리기 콜백 함수 
/// </summary>
/// <returns></returns>
GLvoid drawScene()
{
	//--- 변경된 배경색 설정
	glClearColor(0.5, 0.5, 0.5, 1.0f);
	//glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 렌더링 파이프라인에 세이더 불러오기

	for (int i = 0; i < SHAPENUM; ++i)
	{

		glUseProgram(s_programs[i]);
		// 사용할 VAO 불러오기
		glBindVertexArray(vao[i]);
		// 삼각형 그리기
		glDrawArrays(GL_TRIANGLES, 0, shapeTriNum[i]*3);

	}

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

GLvoid Mouse(int button, int state, int x, int y)
{
	std::cout << x << " , " << y << std::endl;

	float xCoordinate = x - (winSizeX / 2);
	float yCoordinate = -(y - (winSizeY / 2));

	float normalizedX = xCoordinate / (winSizeX / 2);
	float normalizedY = yCoordinate / (winSizeY / 2);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		shapeAnim[nextShapeIndex] = true;

		shapeOrin[nextShapeIndex][0] = normalizedX;
		shapeOrin[nextShapeIndex][1] = normalizedY;

		shapeAngle[nextShapeIndex] = 5;
		shapeRadius[nextShapeIndex] = 0.1f;

		nextShapeIndex += 1;
		nextShapeIndex %= 10;

		InitBuffer();

		glutPostRedisplay();
	}
}

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading
	if (!fptr) // Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file
	length = ftell(fptr); // Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
	fclose(fptr); // Close the file
	buf[length] = 0; // Null terminator
	return buf; // Return the buffer
}

GLvoid Timer(int value)
{
	for (int i = 0; i < SHAPENUM; ++i)
	{
		if (shapeAnim[i] == true)
		{
			shapeTriNum[i] += 1;
			shapePos[i].push_back(shapeOrin[i]);
			
			float x1 = shapeOrin[i][0] + (cos(getRadian(shapeAngle[i]))* shapeRadius[i]);
			float y1 = shapeOrin[i][1] + (sin(getRadian(shapeAngle[i])) * shapeRadius[i]);

			float x2 = shapeOrin[i][0] + (cos(getRadian(shapeAngle[i] + 1)) * shapeRadius[i]);
			float y2 = shapeOrin[i][1] + (sin(getRadian(shapeAngle[i] + 1)) * shapeRadius[i]);
			shapePos[i].push_back(array<GLfloat, 3>{x1,y1,0});
			shapePos[i].push_back(array<GLfloat, 3>{x2,y2, 0});

			shapeAngle[i] += 1;
			shapeRadius[i] += 0.001;
		}
	}

	InitBuffer();

	glutPostRedisplay();
	glutTimerFunc(20, Timer, 1);
}

float getRadian(float angle)
{
	return angle * (PI / 180);
}