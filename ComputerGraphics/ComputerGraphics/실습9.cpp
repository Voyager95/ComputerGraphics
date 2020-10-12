#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <array>
#include <random>
#include <memory>
#include <cmath>

#define SHAPENUM 4
#define PI 3.14159265
using namespace std;

// Ÿ�̸�
unsigned int timerCycle = 100;

float getRadian(float angle);
void make_vertexShader();
void make_fragmentShader();
void InitBuffer();
void InitShader();
GLvoid Timer(int value);
GLvoid Keyboard(unsigned char key, int x, int y);
char* filetobuf(const char* file);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Mouse(int button, int state, int x, int y);

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> colorDis(0.0f, 1.0f);

GLchar* vertexsource, * fragmentsource; // �ҽ��ڵ� ���� ����
GLuint vertexshader, fragmentshader; // ���̴� ��ü
array<GLuint, SHAPENUM> s_programs; // ���̴� ���α׷�

array<GLuint, SHAPENUM> vao;
array<GLuint[2], SHAPENUM> vbo;

array< vector< array<GLfloat, 3 >>, SHAPENUM > shapeStartPos;
array<vector<array<GLfloat, 3>>, SHAPENUM> shapeColor;
array<int, SHAPENUM> shapeTriNum = { 0, };

const float animDelta = 0.05f;
bool anim = false;
int scaleAnimCounter = 0;
bool scaleAnimDirection = true; // True: ���� ���� / False: ���� ����
bool posAnim = false;
int posAnimCounter = 0;
bool posAnimDirectiection = false;

float winSizeX = 800;
float winSizeY = 800;

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
	glutInitWindowSize(winSizeX, winSizeY);									// �������� ũ�� ����
	glutCreateWindow("Example1");									// ������ ����(������ �̸�)

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

	//--- �ﰢ�� �ʱ�ȭ�ϱ�
	shapeStartPos[0].push_back(array<GLfloat, 3> {0, 0, 0});
	shapeStartPos[0].push_back(array<GLfloat, 3> {-0.4, 0.4, 0});
	shapeStartPos[0].push_back(array<GLfloat, 3> {0.4, 0.4, 0});
	shapeStartPos[1].push_back(array<GLfloat, 3> {0, 0, 0});
	shapeStartPos[1].push_back(array<GLfloat, 3> {0.4, 0.4, 0});
	shapeStartPos[1].push_back(array<GLfloat, 3> {0.4, -0.4, 0});
	shapeStartPos[2].push_back(array<GLfloat, 3> {0, 0, 0});
	shapeStartPos[2].push_back(array<GLfloat, 3> {0.4, -0.4, 0});
	shapeStartPos[2].push_back(array<GLfloat, 3> {-0.4, -0.4, 0});
	shapeStartPos[3].push_back(array<GLfloat, 3> {0, 0, 0});
	shapeStartPos[3].push_back(array<GLfloat, 3> {-0.4, -0.4, 0});
	shapeStartPos[3].push_back(array<GLfloat, 3> {-0.4, 0.4, 0});

	shapeColor[0].push_back(array<GLfloat, 3> {0, 0, 0});
	shapeColor[0].push_back(array<GLfloat, 3> {(float)colorDis(gen), (float)colorDis(gen), (float)colorDis(gen)});
	shapeColor[0].push_back(array<GLfloat, 3> {(float)colorDis(gen), (float)colorDis(gen), (float)colorDis(gen)});
	shapeColor[1].push_back(array<GLfloat, 3> {0, 0, 0});
	shapeColor[1].push_back(array<GLfloat, 3> {(float)colorDis(gen), (float)colorDis(gen), (float)colorDis(gen)});
	shapeColor[1].push_back(array<GLfloat, 3> {(float)colorDis(gen), (float)colorDis(gen), (float)colorDis(gen)});
	shapeColor[2].push_back(array<GLfloat, 3> {0, 0, 0});
	shapeColor[2].push_back(array<GLfloat, 3> {(float)colorDis(gen), (float)colorDis(gen), (float)colorDis(gen)});
	shapeColor[2].push_back(array<GLfloat, 3> {(float)colorDis(gen), (float)colorDis(gen), (float)colorDis(gen)});
	shapeColor[3].push_back(array<GLfloat, 3> {0, 0, 0});
	shapeColor[3].push_back(array<GLfloat, 3> {(float)colorDis(gen), (float)colorDis(gen), (float)colorDis(gen)});
	shapeColor[3].push_back(array<GLfloat, 3> {(float)colorDis(gen), (float)colorDis(gen), (float)colorDis(gen)});

	InitShader();
	InitBuffer();

	glutDisplayFunc(drawScene);										// ��� �Լ��� ����( �� �׸� �Լ� ����)
	glutReshapeFunc(Reshape);										// �ٽ� �׸��� �Լ� ����
	glutTimerFunc(timerCycle, Timer, 1);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop();													// �̺�Ʈ ó�� ���� 
}

void make_vertexShader()
{
	vertexsource = filetobuf("vertex.glsl");
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
		cerr << "ERROR: vertex shader ������ ����\n" << errorLog << endl;
		//return false;
	}
}

void make_fragmentShader()
{
	fragmentsource = filetobuf("fragment.glsl");
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
		cerr << "ERROR: fragment shader ������ ����\n" << errorLog << endl;
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

		//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, vbo[i][0]);
		// ���� triShape ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
		// triShape �迭�� ������:
		if (shapeStartPos[i].size() > 0)
		{
			glBufferData(GL_ARRAY_BUFFER, shapeStartPos[i].size() * sizeof(GLfloat) * 3, &shapeStartPos[i][0], GL_STATIC_DRAW);
		}
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
	make_vertexShader();
	make_fragmentShader();
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
GLvoid drawScene()
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

GLvoid Mouse(int button, int state, int x, int y)
{
	std::cout << x << " , " << y << std::endl;

	float xCoordinate = x - (winSizeX / 2);
	float yCoordinate = -(y - (winSizeY / 2));

	float normalizedX = xCoordinate / (winSizeX / 2);
	float normalizedY = yCoordinate / (winSizeY / 2);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// ����
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
	if (posAnim == true)
	{
		posAnimCounter++;

		if (posAnimDirectiection == true)
		{
			for (int i = 0; i < 3; ++i)
			{
				shapeStartPos[0][i][1] += animDelta;
			}
			for (int i = 0; i < 3; ++i)
			{
				shapeStartPos[2][i][1] -= animDelta;
			}
			for (int i = 0; i < 3; ++i)
			{
				shapeStartPos[1][i][0] += animDelta;
			}
			for (int i = 0; i < 3; ++i)
			{
				shapeStartPos[3][i][0] -= animDelta;
			}

		}
		else
		{
			for (int i = 0; i < 3; ++i)
			{
				shapeStartPos[0][i][1] -= animDelta;
			}
			for (int i = 0; i < 3; ++i)
			{
				shapeStartPos[2][i][1] += animDelta;
			}
			for (int i = 0; i < 3; ++i)
			{
				shapeStartPos[1][i][0] -= animDelta;
			}
			for (int i = 0; i < 3; ++i)
			{
				shapeStartPos[3][i][0] += animDelta;
			}
		}

		if (posAnimCounter >= 0.6 / animDelta)
		{
			posAnimCounter = 0;
			posAnimDirectiection = !posAnimDirectiection;
		}
	}
	if (anim == true)
	{
		scaleAnimCounter++;

		if (scaleAnimDirection == true)
		{
			
			shapeStartPos[0][1][0] += animDelta;
			shapeStartPos[0][2][0] -= animDelta;
			shapeStartPos[2][1][0] -= animDelta;
			shapeStartPos[2][2][0] += animDelta;
			
			shapeStartPos[1][1][1] -= animDelta;
			shapeStartPos[1][2][1] += animDelta;
			shapeStartPos[3][1][1] += animDelta;
			shapeStartPos[3][2][1] -= animDelta;

		}
		else
		{
			shapeStartPos[0][1][0] -= animDelta;
			shapeStartPos[0][2][0] += animDelta;
			shapeStartPos[2][1][0] += animDelta;
			shapeStartPos[2][2][0] -= animDelta;

			shapeStartPos[1][1][1] += animDelta;
			shapeStartPos[1][2][1] -= animDelta;
			shapeStartPos[3][1][1] -= animDelta;
			shapeStartPos[3][2][1] += animDelta;
		}

		if (scaleAnimCounter >= 0.4 / animDelta)
		{
			scaleAnimCounter = 0;
			scaleAnimDirection = !scaleAnimDirection;
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


GLvoid Keyboard(unsigned char key, int x, int y)
{
	char receivedKey = key;
	if (islower(receivedKey) != 0)
		receivedKey = toupper(receivedKey);

	switch (receivedKey) {
	case 'T':														// ������ ���������� ����
		posAnim = !posAnim;
		break;
	case 'S':
		anim = !anim;
		break;
	default:
		break;
	}
	glutPostRedisplay();											//������ �ٲ𶧸��� ��� �ݹ��Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
}