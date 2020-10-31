#include "stdafx.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "SceneSystem.h"


#include "Scene.h"
#include "Object.h"
#include "Renderer.h"
#include "Transform.h"

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

void main(int argc, char** argv)
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);											// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);					// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);								// �������� ��ġ ����
	glutInitWindowSize(WINSIZE_X, WINSIZE_Y);						// �������� ũ�� ����
	glutCreateWindow("Example");									// ������ ����(������ �̸�)

	//--- System ����
	RenderSystem::GetInstance();									// ���� �ý��� ����
	ResourceSystem::GetInstance();									// ���ҽ� �ý��� ����
	SceneSystem& ss = SceneSystem::GetInstance();					// �� �ý��� ����

		//--- �ʱ� �� ����
	std::shared_ptr<Scene> exercise16 = std::make_shared<Scene>();

	std::shared_ptr<Object> cube = std::make_shared<Object>("Cube");

	auto t =  cube->GetTransform();
	std::cout << t->GetObjectW()->name << std::endl;

	auto cubeRenderer = std::make_shared<Renderer>(cube);
	cubeRenderer->SetSharedModel("Cube.obj");

	cube->AddComponent(cubeRenderer);
	exercise16->AddObject(cube);


	ss.StartScene(exercise16);

	//--- �̺�Ʈ �Լ� ���
	glutDisplayFunc(DrawScene);										// ��� �Լ��� ����( �� �׸� �Լ� ����)
	glutReshapeFunc(Reshape);										// �ٽ� �׸��� �Լ� ����
	glutMotionFunc(MouseMotion);
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

	//--- ����� ���� ����
	glClearColor(0.5, 0.5, 0.5, 1.0f);
	//glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ������ ���������ο� ���̴� �ҷ�����
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