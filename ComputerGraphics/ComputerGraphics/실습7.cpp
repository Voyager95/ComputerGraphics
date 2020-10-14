#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <array>
#include <random>
#include <memory>
#define TRINUM 10
using namespace std;

// �Լ� ����
void make_vertexShader();
void make_fragmentShader();
void InitBuffer();
void InitShader();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
char* filetobuf(const char* file);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Timer(int value);

// Ÿ�� ����

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

// ���� ����
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> colorDis(0.0f, 1.0f);
std::uniform_real_distribution<> triPosDis(-1.0f, 1.0f);
std::uniform_real_distribution<> deltaDis(-1.0f, 1.0f);

float winSizeX = 800;
float winSizeY = 800;

GLchar* vertexsource, * fragmentsource; // �ҽ��ڵ� ���� ����
GLuint vertexshader, fragmentshader; // ���̴� ��ü
array<GLuint, TRINUM> s_programs; // ���̴� ���α׷�

float triSize = 0.1f;

int targetTriIndex = 0;

array<GLfloat[2], TRINUM> triCenter;
array<GLfloat[3][3], TRINUM> triPos;
array<GLfloat[3][3], TRINUM> triColor;
array<GLfloat[2], TRINUM> triDelta;
array<GLint, TRINUM> triDirection;

GLuint vao, vbo[2];

bool isFill = true;

bool moveTri = false;

// Ÿ�̸�
unsigned int timerCycle = 100;

void ChangeTriangle(int index, float x, float y, int direction)
{	
	switch (direction)
	{
	case 0:
	{
		GLfloat newTriPos[3][3] = { { -triSize + x, -triSize + y ,0} , { +triSize + x, -triSize + y ,0}, { x, triSize * 2 + y ,0} };
		//GLfloat newColor[3][3] = { {colorDis(gen),colorDis(gen),colorDis(gen)},{colorDis(gen),colorDis(gen),colorDis(gen)},{colorDis(gen),colorDis(gen),colorDis(gen)} };
		memcpy(triPos[index], newTriPos, sizeof(newTriPos));
		//memcpy(triColor[index], newColor, sizeof(newColor));
	}
		break;
	case 1:
	{
		GLfloat newTriPos[3][3] = { { -triSize * 2 + x, y ,0} , { +triSize + x, -triSize + y ,0}, { x + triSize, triSize + y ,0} };
		//GLfloat newColor[3][3] = { {colorDis(gen),colorDis(gen),colorDis(gen)},{colorDis(gen),colorDis(gen),colorDis(gen)},{colorDis(gen),colorDis(gen),colorDis(gen)} };
		memcpy(triPos[index], newTriPos, sizeof(newTriPos));
		//memcpy(triColor[index], newColor, sizeof(newColor));
	}
		break;
	case 2:
	{
		GLfloat newTriPos[3][3] = { { -triSize + x, -triSize + y ,0} , { 2 * triSize + x, y ,0} ,{ -triSize + x, triSize + y ,0}};
		//GLfloat newColor[3][3] = { {colorDis(gen),colorDis(gen),colorDis(gen)},{colorDis(gen),colorDis(gen),colorDis(gen)},{colorDis(gen),colorDis(gen),colorDis(gen)} };
		memcpy(triPos[index], newTriPos, sizeof(newTriPos));
		//memcpy(triColor[index], newColor, sizeof(newColor));
	}
		break;
	}
}

void ChangeTrianglePos(int index, float x, float y)
{
	int direction = triDirection[index];
	switch (direction)
	{
	case 0:
	{
		GLfloat newTriPos[3][3] = { { -triSize + x, -triSize + y ,0} , { +triSize + x, -triSize + y ,0}, { x, triSize * 2 + y ,0} };
		//GLfloat newColor[3][3] = { {colorDis(gen),colorDis(gen),colorDis(gen)},{colorDis(gen),colorDis(gen),colorDis(gen)},{colorDis(gen),colorDis(gen),colorDis(gen)} };
		memcpy(triPos[index], newTriPos, sizeof(newTriPos));
		//memcpy(triColor[index], newColor, sizeof(newColor));
	}
	break;
	case 1:
	{
		GLfloat newTriPos[3][3] = { { -triSize * 2 + x, y ,0} , { +triSize + x, -triSize + y ,0}, { x + triSize, triSize + y ,0} };
		//GLfloat newColor[3][3] = { {colorDis(gen),colorDis(gen),colorDis(gen)},{colorDis(gen),colorDis(gen),colorDis(gen)},{colorDis(gen),colorDis(gen),colorDis(gen)} };
		memcpy(triPos[index], newTriPos, sizeof(newTriPos));
		//memcpy(triColor[index], newColor, sizeof(newColor));
	}
	break;
	case 2:
	{
		GLfloat newTriPos[3][3] = { { -triSize + x, -triSize + y ,0} ,{ 2 * triSize + x, y ,0}, { -triSize + x, triSize + y ,0} };
		//GLfloat newColor[3][3] = { {colorDis(gen),colorDis(gen),colorDis(gen)},{colorDis(gen),colorDis(gen),colorDis(gen)},{colorDis(gen),colorDis(gen),colorDis(gen)} };
		memcpy(triPos[index], newTriPos, sizeof(newTriPos));
		//memcpy(triColor[index], newColor, sizeof(newColor));
	}
	break;
	}
}

void ChangeTriangleColor(int index)
{
	GLfloat color0 = colorDis(gen);
	GLfloat color1 = colorDis(gen);
	GLfloat color2 = colorDis(gen);
	GLfloat newColor[3][3] = { {color0,color1,color2},{color0,color0,color2},{color0,color1,color2} };
	memcpy(triColor[index], newColor, sizeof(newColor));
}

//--- ���� �Լ�

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winSizeX, winSizeY);
	glutCreateWindow("Example1");

	//--- �ﰢ�� �ʱ�ȭ
	for (int i = 0; i < triPos.size(); ++i)
	{
		GLfloat x = triPosDis(gen);
		GLfloat y = triPosDis(gen);

		triCenter[i][0] = x;
		triCenter[i][1] = y;
		triDelta[i][0] = deltaDis(gen);
		triDelta[i][1] = deltaDis(gen);
		triDirection[i] = 0;
		ChangeTriangle(i, x, y, triDirection[i]);
	}

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	glewInit();
	InitShader();
	InitBuffer();
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(timerCycle, Timer, 1);
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}


GLvoid Keyboard(unsigned char key, int x, int y)
{
	char receivedKey = key;
	if (islower(receivedKey) != 0)
		receivedKey = toupper(receivedKey);

	switch (receivedKey) {
	case 'F':
		if (isFill == true)
		{
			isFill = false;
			glPolygonMode(GL_FRONT, GL_LINE);
		}
		else
		{
			isFill = true;
			glPolygonMode(GL_FRONT, GL_FILL);
		}
		break;
	case 'C':
		for (int i = 0; i < TRINUM; ++i)
		{
			ChangeTriangleColor(i);
			InitBuffer();
		}
		break;
	case 'M':
		moveTri = true;
		break;
	case 'S':
		moveTri = false;
		break;
	case 'Q':
		exit(EXIT_FAILURE);
		break;
	default:
		break;
	}
	glutPostRedisplay();											//������ �ٲ𶧸��� ��� �ݹ��Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
}

GLvoid Timer(int value)
{
	if (moveTri == true)
	{
		for (int i = 0; i < TRINUM; ++i)
		{
			bool isCol = false;

			float dx = triDelta[i][0] * (timerCycle * 0.001);
			float dy = triDelta[i][1] * (timerCycle * 0.001);
			if (triCenter[i][0] + triSize + dx > 1 || triCenter[i][0] - triSize + dx < -1)
			{
				dx *= -1;
				triDelta[i][0] *= -1;
				isCol = true;
			}
			if (triCenter[i][1] + triSize + dy > 1 || triCenter[i][1] - triSize + dy < -1)
			{
				dy *= -1;
				triDelta[i][1] *= -1;
				isCol = true;
			}

			if (isCol == true)
			{
				triDirection[i] += 1;
				triDirection[i] %= 3;
				ChangeTriangle(i, triCenter[i][0], triCenter[i][1], triDirection[i]);
			}

			triCenter[i][0] += dx;
			triCenter[i][1] += dy;
			ChangeTrianglePos(i, triCenter[i][0], triCenter[i][1]);
			InitBuffer();
		}

		glutPostRedisplay();
	}

	glutTimerFunc(100, Timer, 1);
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
		ChangeTriangle(targetTriIndex, normalizedX, normalizedY, 0);

		InitBuffer();

		targetTriIndex = (targetTriIndex + 1) % TRINUM;

		glutPostRedisplay();
	}
}

/// <summary>
/// �ٽ� �׸��� �ݹ� �Լ�
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
	glGenVertexArrays(1, &vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
	glBindVertexArray(vao); //--- VAO�� ���ε��ϱ�
	glGenBuffers(2, vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�

	//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	// ���� triShape ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
	// triShape �迭�� ������: 9 * float
	glBufferData(GL_ARRAY_BUFFER, TRINUM * 9 * sizeof(GLfloat), triPos[0], GL_STATIC_DRAW);
	// ��ǥ���� attribute �ε��� 0���� ����Ѵ�: ���ؽ� �� 3* float
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute �ε��� 0���� ��밡���ϰ� ��
	glEnableVertexAttribArray(0);

	//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	// ���� colors���� ���ؽ� ������ �����Ѵ�.
	// colors �迭�� ������: 9 *float
	glBufferData(GL_ARRAY_BUFFER, TRINUM * 9 * sizeof(GLfloat), triColor[0], GL_STATIC_DRAW);
	// ������ attribute �ε��� 1���� ����Ѵ�: ���ؽ� �� 3*float
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// attribute �ε��� 1���� ��� �����ϰ� ��.
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

		//--- Shader Program ����ϱ�
		glUseProgram(s_programs[i]);
	}

	//checkCompileErrors(s_program, "PROGRAM");




	//--- ���̴� �����ϱ�
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);
}

//--- �׸��� �ݹ� �Լ�
GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	//--- ����� ���� ����
	glClearColor(0.5, 0.5, 0.5, 1.0f);
	//glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ������ ���������ο� ���̴� �ҷ�����

	for (int i = 0; i < TRINUM; ++i)
	{

		glUseProgram(s_programs[i]);
		// ����� VAO �ҷ�����
		glBindVertexArray(vao);
		// �ﰢ�� �׸���
		glDrawArrays(GL_TRIANGLES, i * 3, 3);

	}

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
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