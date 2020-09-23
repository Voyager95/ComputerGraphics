#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <gl/glew.h> // 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <array>
#include <random>
#include <memory>
#define TRINUM 4
using namespace std;

// 함수 정의
void make_vertexShader();
void make_fragmentShader();
void InitBuffer();
void InitShader();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
char* filetobuf(const char* file);
GLvoid Mouse(int button, int state, int x, int y);

// 타입 정의

struct Vec3
{
public:
	GLfloat x, y, z;

	Vec3()
	{
		x = 0;
		y = 0;
		z = 0;
	}
};

// 전역 변수
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> colorDis(0.0f, 1.0f);
std::uniform_real_distribution<> triPosDis(-1.0f, 1.0f);

float winSizeX = 800;
float winSizeY = 800;

GLchar* vertexsource, * fragmentsource; // 소스코드 저장 변수
GLuint vertexshader, fragmentshader; // 세이더 객체
array<GLuint,4> s_programs; // 세이더 프로그램

float triSize = 0.1f;

int targetTriIndex = 0;

array<GLfloat[3][3], TRINUM> triPos;
array<GLfloat[3][3], TRINUM> triColor;

GLuint vao, vbo[2];

void ChangeTriangle(int index, float x, float y)
{
	GLfloat newTriPos[3][3] = { { -triSize + x, -triSize + y ,0} , { +triSize + x, -triSize + y ,0}, { x, triSize + y ,0} };
	GLfloat newColor[3][3] = { {colorDis(gen),colorDis(gen),colorDis(gen)},{colorDis(gen),colorDis(gen),colorDis(gen)},{colorDis(gen),colorDis(gen),colorDis(gen)} };
	memcpy(triPos[index], newTriPos, sizeof(newTriPos));
	memcpy(triColor[index], newColor, sizeof(newColor));
}

//--- 메인 함수

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winSizeX, winSizeY);
	glutCreateWindow("Example1");

	//--- 삼각형 초기화
	for (int i = 0; i < triPos.size(); ++i)
	{
		ChangeTriangle(i, triPosDis(gen), triPosDis(gen));
	}

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	glewInit();
	InitShader();
	InitBuffer();
	glutMouseFunc(Mouse);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
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
		ChangeTriangle(targetTriIndex, normalizedX, normalizedY);

		InitBuffer();

		targetTriIndex = (targetTriIndex + 1) % TRINUM;

		glutPostRedisplay();
	}
}

/// <summary>
/// 다시 그리기 콜백 함수
/// </summary>
/// <param name="w"></param>
/// <param name="h"></param>
/// <returns></returns>
GLvoid Reshape(int w, int h)
{
	winSizeX = w;
	winSizeY = h;

	glViewport(0, 0, w, h);
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
	glGenVertexArrays(1, &vao); //--- VAO 를 지정하고 할당하기
	glBindVertexArray(vao); //--- VAO를 바인드하기
	glGenBuffers(2, vbo); //--- 2개의 VBO를 지정하고 할당하기

	//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	// 변수 triShape 에서 버텍스 데이터 값을 버퍼에 복사한다.
	// triShape 배열의 사이즈: 9 * float
	glBufferData(GL_ARRAY_BUFFER, TRINUM * 9 * sizeof(GLfloat), triPos[0], GL_STATIC_DRAW);
	// 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute 인덱스 0번을 사용가능하게 함
	glEnableVertexAttribArray(0);

	//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	// 변수 colors에서 버텍스 색상을 복사한다.
	// colors 배열의 사이즈: 9 *float
	glBufferData(GL_ARRAY_BUFFER, TRINUM * 9 * sizeof(GLfloat), triColor[0], GL_STATIC_DRAW);
	// 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute 인덱스 1번을 사용 가능하게 함.
	glEnableVertexAttribArray(1);
}

void InitShader()
{
	make_vertexShader();
	make_fragmentShader();
	//-- shader Program
	for (int i = 0; i < TRINUM; ++i)
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

//--- 그리기 콜백 함수
GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	//--- 변경된 배경색 설정
	glClearColor(0.5, 0.5, 0.5, 1.0f);
	//glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 렌더링 파이프라인에 세이더 불러오기

	for (int i = 0; i < TRINUM; ++i)
	{

		glUseProgram(s_programs[i]);
		// 사용할 VAO 불러오기
		glBindVertexArray(vao);
		// 삼각형 그리기
		glDrawArrays(GL_TRIANGLES, i * 3, 3);

	}

	glutSwapBuffers(); // 화면에 출력하기
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
