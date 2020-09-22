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

float RandomDelta();

// ���� ����
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> colorDis(0.0f, 1.0f);
std::uniform_int_distribution<> dirDis(0,1);
std::uniform_real_distribution<> deltaSizeDis(0.1, 0.2);

Colorf rectColor(1.0f, 0.0f, 0.0f, 0.0f);
Colorf bgColor(0.1f, 0.1f, 0.1f, 0.0f);


// ������ ũ��
float winSizeX = 500;
float winSizeY = 500;

// �簢�� ����
float rectPosX = 0;
float rectPosY = 0;
float rectSize = 0.1;
float rectDeltaX = RandomDelta();
float rectDeltaY = RandomDelta();
bool rectMove = false;

// Ÿ�̸�
unsigned int timerCycle = 100;

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
	glutInitWindowSize(winSizeX, winSizeY);							// �������� ũ�� ����
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
	glutTimerFunc(timerCycle, Timer, 1);
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
	case 'S':														// ������ ���������� ����
		rectMove = false;
		break;
	case 'A':
		rectMove = true;
		break;
	default:
		break;
	}
	glutPostRedisplay();											//������ �ٲ𶧸��� ��� �ݹ��Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
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
		rectPosX = normalizedX;
		rectPosY = normalizedY;
		rectColor.Set(colorDis(gen), colorDis(gen), colorDis(gen), 1.0f);
		rectDeltaX = RandomDelta();
		rectDeltaY = RandomDelta();

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
	glRectf( rectPosX - rectSize, rectPosY + rectSize, rectPosX + rectSize, rectPosY - rectSize);


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
	winSizeX = w;
	winSizeY = h;

	glViewport(0, 0, w, h);
}

GLvoid Timer(int value)
{

	if (rectMove == true)
	{
		float dx = rectDeltaX * (timerCycle * 0.001);
		float dy = rectDeltaY * (timerCycle * 0.001);
		if (rectPosX + dx > 1 || rectPosX + dx < -1)
		{
			dx *= -1;
			rectDeltaX *= -1;
		}
		if (rectPosY + dy > 1 || rectPosY + dy < -1)
		{
			dy *= -1;
			rectDeltaY *= -1;
		}

		rectPosX += dx;
		rectPosY += dy;

		glutPostRedisplay();
	}

	glutTimerFunc(100, Timer, 1);
}

float RandomDelta()
{
	if (dirDis(gen) == 0)
	{
		return deltaSizeDis(gen);
	}
	else
		return -deltaSizeDis(gen);
}