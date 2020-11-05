#include "stdafx.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "SceneSystem.h"

#include "Exercise17.h"

//--- ���� ����
const unsigned int TIMER_CYCLE = 100;
unsigned int WINSIZE_X = 800;
unsigned int WINSIZE_Y = 800;

//--- �Լ� ����
GLvoid Keyboard(unsigned char key, int x, int y);					// Ű���� �̺�Ʈ �Լ�
GLvoid DrawScene(GLvoid);											// ��� �̺�Ʈ �Լ� 
GLvoid Reshape(int w, int h);										// â ���� �̺�Ʈ �Լ�
GLvoid Mouse(int button, int state, int x, int y);					// ���콺 Ŭ�� �̺�Ʈ �Լ�
GLvoid MouseMotion(int x, int y);									// ���콺 ������ �̺�Ʈ �Լ�
GLvoid InitialLoop(int value);										// ó������ ���ư��� �����Դϴ�.

void main(int argc, char** argv)
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);											// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);		// ���÷��� ��� ����
	glEnable(GL_DEPTH_TEST);
	glutInitWindowPosition(100, 100);								// �������� ��ġ ����
	glutInitWindowSize(WINSIZE_X, WINSIZE_Y);						// �������� ũ�� ����
	glutCreateWindow("Example");									// ������ ����(������ �̸�)

	//--- System ����
	RenderSystem::GetInstance();									// ���� �ý��� ����
	ResourceSystem::GetInstance();									// ���ҽ� �ý��� ����
	SceneSystem::GetInstance();										// �� �ý��� ����

	//--- �̺�Ʈ �Լ� ���
	glutDisplayFunc(DrawScene);										// ��� �Լ��� ����( �� �׸� �Լ� ����)
	glutReshapeFunc(Reshape);										// �ٽ� �׸��� �Լ� ����
	glutMotionFunc(MouseMotion);
	glutTimerFunc(0, InitialLoop, 1);								// ó��
	glutKeyboardFunc(Keyboard);										// ���콺 �Է�
	glutMouseFunc(Mouse);											// ���콺 Ŭ��
	glutMainLoop();													// �̺�Ʈ ó�� ����
}


/// <summary>
/// �׸��� �ݹ� �Լ� 
/// </summary>
/// <returns></returns>
GLvoid DrawScene()
{	
	//--- �����ý������� �׸��ϴ�.
	RenderSystem& renderSys = RenderSystem::GetInstance();
	renderSys.Render();
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

/// <summary>
/// ���콺 ������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
GLvoid MouseMotion(int x, int y)
{
	//std::cout << x << " , " << y << std::endl;

	float xCoordinate = x - (WINSIZE_X / 2);
	float yCoordinate = -(y - (WINSIZE_X / 2));

	float normalizedX = xCoordinate / (WINSIZE_X / 2);
	float normalizedY = yCoordinate / (WINSIZE_X / 2);
}

/// <summary>
/// ���콺 Ŭ��
/// </summary>
/// <param name="button"></param>
/// <param name="state"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
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

/// <summary>
/// Ű���� ������
/// </summary>
/// <param name="key"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
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

GLvoid InitialLoop(int value)
{
	auto scene = std::make_shared< Exercise17>();

	auto& ss = SceneSystem::GetInstance();

	ss.StartScene(std::static_pointer_cast<Scene>(scene));
}
