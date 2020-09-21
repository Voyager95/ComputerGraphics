#include <iostream>
#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <random>

// Ÿ�� ����

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


// �Լ� ����

GLvoid Timer(int value);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);

// ���� ����
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> colorDis(0.0f, 1.0f);

Colorf rectColor(1.0f,0.0f, 0.0f, 0.0f);
Colorf bgColor(1.0f, 0.0f, 1.0f, 0.0f);


// �簢�� ũ��

float rectW = 0.4;
float rectH = 0.4;

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
	glutInitWindowSize(250, 250);									// �������� ũ�� ����
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
	glutTimerFunc(100, Timer, 1);
	glutDisplayFunc(drawScene);										// ��� �Լ��� ����( �� �׸� �Լ� ����)
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);										// �ٽ� �׸��� �Լ� ����
	glutMainLoop();													// �̺�Ʈ ó�� ���� 
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	char receivedKey = key;
	if (islower(receivedKey) != 0)
		receivedKey = toupper(receivedKey);

	switch (receivedKey) {
	case 'R':														// ������ ���������� ����
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
	glutPostRedisplay();											//������ �ٲ𶧸��� ��� �ݹ��Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
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
/// �׸��� �ݹ� �Լ� 
/// </summary>
/// <returns></returns>
GLvoid drawScene()
{
	std::cout << "�ٽ� �׸�" << std::endl;

	glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	glClear(GL_COLOR_BUFFER_BIT);									// ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����
	
	glColor3f(rectColor.r, rectColor.g, rectColor.b);
	glRectf( -rectW * 0.5,-rectH*0.5 , rectW * 0.5, rectH * 0.5);
	

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

GLvoid Timer(int value)
{


	glutTimerFunc(500, Timer, 1);
}