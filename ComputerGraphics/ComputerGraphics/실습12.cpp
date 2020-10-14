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


//--- ���� ����
#define SHAPENUM 2
const unsigned int TIMER_CYCLE= 100;
unsigned int WINSIZE_X = 800;
unsigned int WINSIZE_Y = 800;

//--- �Լ� ����
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

// ����
std::random_device rd;
std::mt19937 gen(rd());

// ������
GLchar* vertexsource, * fragmentsource; // �ҽ��ڵ� ���� ����
GLuint vertexshader, fragmentshader; // ���̴� ��ü
std::array<GLuint, SHAPENUM> s_programs; // ���̴� ���α׷�

std::array<GLuint, SHAPENUM> vao;
std::array<GLuint[2], SHAPENUM> vbo;
std::array<GLuint*, SHAPENUM> ebo;

std::array< std::vector< std::array<GLfloat, 3 >>, SHAPENUM > shapeStartPos;
std::array<std::vector<int>, SHAPENUM> shapetri;
std::array<std::vector<std::array<GLfloat, 3>>, SHAPENUM> shapeColor;
std::array<int, SHAPENUM> shapeTriNum = { 0, };



/// <summary>
/// ������ ����ϰ� �ݹ��Լ� ���� 
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
void main(int argc, char** argv)
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);											// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);					// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);								// �������� ��ġ ����
	glutInitWindowSize(WINSIZE_X, WINSIZE_Y);									// �������� ũ�� ����
	glutCreateWindow("Example");									// ������ ����(������ �̸�)

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew(�� Open GL) �ʱ�ȭ
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

	glutDisplayFunc(DrawScene);										// ��� �Լ��� ����( �� �׸� �Լ� ����)
	glutReshapeFunc(Reshape);										// �ٽ� �׸��� �Լ� ����
	glutTimerFunc(TIMER_CYCLE, Timer, 1);
	glutMotionFunc(MouseMotion);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop();													// �̺�Ʈ ó�� ���� 
}

void MakeVertexShader()
{
	vertexsource = Filetobuf("vertex.glsl");
	//--- ���ؽ� ���̴� ��ü �����
	vertexshader = glCreateShader(GL_VERTEX_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
	//--- ���ؽ� ���̴� �������ϱ�
	glCompileShader(vertexshader);
	//--- �������� ����� ���� ���� ���: ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
		//return false;
	}
}

void MakeFragmentShader()
{
	fragmentsource = Filetobuf("fragment.glsl");
	//--- �����׸�Ʈ ���̴� ��ü �����
	fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);
	//--- �����׸�Ʈ ���̴� ������
	glCompileShader(fragmentshader);
	//--- �������� ����� ���� ���� ���: ������ ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
		//return false;
	}
}

void InitBuffer()
{
	for (int i = 0; i < SHAPENUM; ++i)
	{
		glGenVertexArrays(1, &vao[i]); //--- VAO �� �����ϰ� �Ҵ��ϱ�
		glBindVertexArray(vao[i]); //--- VAO�� ���ε��ϱ�
		glGenBuffers(2, vbo[i]); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�
		glGenBuffers(2, &ebo[i][0]); //--- 2���� EBO�� �����ϰ� �Ҵ��ϱ�
		//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, vbo[i][0]);
		// ���� triShape ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
		// triShape �迭�� ������:
		if (shapeStartPos[i].size() > 0)
		{
			glBufferData(GL_ARRAY_BUFFER, shapeStartPos[i].size() * sizeof(GLfloat) * 3, &shapeStartPos[i][0], GL_STATIC_DRAW);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i][0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(),)


		// ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		// attribute �ε��� 0���� ��밡���ϰ� ��
		glEnableVertexAttribArray(0);

		//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, vbo[i][1]);
		// ���� colors���� ���ؽ� ������ �����Ѵ�.
		// colors �迭�� ������: 9 *float
		if (shapeColor[i].size() > 0)
		{
			glBufferData(GL_ARRAY_BUFFER, shapeColor[i].size() * sizeof(GLfloat) * 3, &shapeColor[i][0], GL_STATIC_DRAW);
		}
		// ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 3*float
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		// attribute �ε��� 1���� ��� �����ϰ� ��.
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

		//--- Shader Program ����ϱ�
		glUseProgram(s_programs[i]);
	}

	//checkCompileErrors(s_program, "PROGRAM");




	//--- ���̴� �����ϱ�
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
}

/// <summary>
/// �׸��� �ݹ� �Լ� 
/// </summary>
/// <returns></returns>
GLvoid DrawScene()
{
	//--- ����� ���� ����
	glClearColor(0.5, 0.5, 0.5, 1.0f);
	//glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ������ ���������ο� ���̴� �ҷ�����

	for (int i = 0; i < SHAPENUM; ++i)
	{

		glUseProgram(s_programs[i]);
		// ����� VAO �ҷ�����
		glBindVertexArray(vao[i]);
		// �ﰢ�� �׸���
		glDrawArrays(GL_TRIANGLES, 0, 3);

	}

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

/// <summary>
/// �ٽ� �׸��� �ݹ� �Լ�
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
	//--- 1. ��ü ���ؽ� ���� �� �ﰢ�� ���� ����
	char count[100];
	int vertexNum = 0;
	int faceNum = 0;
	while (!feof(objFile)) {
		fscanf(objFile, "%s", count);
		if (count[0] == 'v' && count[1] == '\0')
			vertexNum += 1;
		else if (count[0] == 'f' && count[1] == '\0')
			faceNum += 1;
		memset(count, '\0', sizeof(count)); // �迭 �ʱ�ȭ
	}
	//--- 2. �޸� �Ҵ�
	if (vertex != nullptr)
		delete(vertex);
	if (face != nullptr)
		delete(face);
	int vertIndex = 0;
	int faceIndex = 0;
	vertex = new glm::vec4[vertexNum]; //(glm::vec4*)malloc(sizeof(glm::vec4) * vertexNum);
	face = new glm::vec4[faceNum]; //(glm::vec4*)malloc(sizeof(glm::vec4) * faceNum);

	//--- 3. �Ҵ�� �޸𸮿� �� ���ؽ�, ���̽� ���� �Է�
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