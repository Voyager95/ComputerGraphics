#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include <array>
#include <random>
#include <memory>
#include <cmath>


//--- 전역 변수
#define SHAPENUM 2
const unsigned int TIMER_CYCLE= 100;
unsigned int WINSIZE_X = 800;
unsigned int WINSIZE_Y = 800;

//--- 함수 정의
void ReadObj(FILE* objFile, glm::vec4* &vertex, glm::vec4* &face);
void MakeVertexShader();
void MakeFragmentShader();
void InitBuffer();
void InitShader();
GLvoid Timer(int value);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid MouseMotion(int x, int y);
char* Filetobuf(const char* file);

// 랜덤
std::random_device rd;
std::mt19937 gen(rd());

// 랜더링
GLchar* vertexsource, * fragmentsource; // 소스코드 저장 변수
GLuint vertexshader, fragmentshader; // 세이더 객체
std::array<GLuint, SHAPENUM> s_programs; // 세이더 프로그램

std::array<GLuint, SHAPENUM> vao;
std::array<GLuint[2], SHAPENUM> vbo;
std::array<GLuint*, SHAPENUM> ebo;

std::array< std::vector< std::array<GLfloat, 3 >>, SHAPENUM > shapeStartPos;
std::array<std::vector<int>, SHAPENUM> shapetri;
std::array<std::vector<std::array<GLfloat, 3>>, SHAPENUM> shapeColor;
std::array<int, SHAPENUM> shapeTriNum = { 0, };



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
	glutInitWindowSize(WINSIZE_X, WINSIZE_Y);									// 윈도우의 크기 지정
	glutCreateWindow("Example");									// 윈도우 생성(윈도우 이름)

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

	FILE* cube = fopen("Cube.obj", "r");
	glm::vec4* cubeVertex = nullptr;
	glm::vec4* cubeFace = nullptr;
	ReadObj(cube, cubeVertex, cubeFace);

	for (int i = 0; i < 3; i++)
	{
		std::cout << (cubeVertex + i)->x << (cubeVertex + i)->y << (cubeVertex + i)->z << std::endl;
	}


	InitShader();
	InitBuffer();

	glutDisplayFunc(DrawScene);										// 출력 함수의 지정( 즉 그릴 함수 지정)
	glutReshapeFunc(Reshape);										// 다시 그리기 함수 지정
	glutTimerFunc(TIMER_CYCLE, Timer, 1);
	glutMotionFunc(MouseMotion);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop();													// 이벤트 처리 시작 
}

void MakeVertexShader()
{
	vertexsource = Filetobuf("vertex.glsl");
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
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		//return false;
	}
}

void MakeFragmentShader()
{
	fragmentsource = Filetobuf("fragment.glsl");
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
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
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
		glGenBuffers(2, &ebo[i][0]); //--- 2개의 EBO를 지정하고 할당하기
		//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, vbo[i][0]);
		// 변수 triShape 에서 버텍스 데이터 값을 버퍼에 복사한다.
		// triShape 배열의 사이즈:
		if (shapeStartPos[i].size() > 0)
		{
			glBufferData(GL_ARRAY_BUFFER, shapeStartPos[i].size() * sizeof(GLfloat) * 3, &shapeStartPos[i][0], GL_STATIC_DRAW);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i][0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(),)


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
	MakeVertexShader();
	MakeFragmentShader();
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
GLvoid DrawScene()
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
		glDrawArrays(GL_TRIANGLES, 0, 3);

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

GLvoid MouseMotion(int x, int y)
{
	//std::cout << x << " , " << y << std::endl;

	float xCoordinate = x - (WINSIZE_X / 2);
	float yCoordinate = -(y - (WINSIZE_X / 2));

	float normalizedX = xCoordinate / (WINSIZE_X / 2);
	float normalizedY = yCoordinate / (WINSIZE_X / 2);
}

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

char* Filetobuf(const char* file)
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
}


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

void ReadObj(FILE* objFile, glm::vec4* &vertex, glm::vec4* &face)
{
	//--- 1. 전체 버텍스 개수 및 삼각형 개수 세기
	char count[100];
	int vertexNum = 0;
	int faceNum = 0;
	while (!feof(objFile)) {
		fscanf(objFile, "%s", count);
		if (count[0] == 'v' && count[1] == '\0')
			vertexNum += 1;
		else if (count[0] == 'f' && count[1] == '\0')
			faceNum += 1;
		memset(count, '\0', sizeof(count)); // 배열 초기화
	}
	//--- 2. 메모리 할당
	if (vertex != nullptr)
		delete(vertex);
	if (face != nullptr)
		delete(face);
	int vertIndex = 0;
	int faceIndex = 0;
	vertex = new glm::vec4[vertexNum]; //(glm::vec4*)malloc(sizeof(glm::vec4) * vertexNum);
	face = new glm::vec4[faceNum]; //(glm::vec4*)malloc(sizeof(glm::vec4) * faceNum);

	//--- 3. 할당된 메모리에 각 버텍스, 페이스 정보 입력
	char bind[100];
	rewind(objFile);
	while (!feof(objFile)) {
		fscanf(objFile, "%s", bind);
		if (bind[0] == 'v' && bind[1] == '\0') {
			fscanf(objFile, "%f %f %f",
				&vertex[vertIndex].x, &vertex[vertIndex].y,
				&vertex[vertIndex].z);
			vertIndex++;
		}
		else if (bind[0] == 'f' && bind[1] == '\0') {
			fscanf(objFile, "%f %f %f",
				&face[faceIndex].x, &face[faceIndex].y, &face[faceIndex].z);
			faceIndex++;
		}
	}
}