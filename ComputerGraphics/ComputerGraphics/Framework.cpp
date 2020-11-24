#include "stdafx.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "SceneSystem.h"
#include "InputSystem.h"

#include "TermProject.h"

//--- ���� ����

//--- �Լ� ����
GLvoid KeyboardDown(unsigned char key, int x, int y);				// Ű���� Down�̺�Ʈ �Լ�
GLvoid KeyboardUp(unsigned char key, int x, int y);					// Ű���� Up�̺�Ʈ �Լ�
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
	glutInitWindowSize((int)WinSize::WINSIZE_X,						// �������� ũ�� ����
					   (int)WinSize::WINSIZE_Y);					
	GlobalUtility::GetInstance().presentWinSize_X = (int)WinSize::WINSIZE_X;
	GlobalUtility::GetInstance().presentWinSize_Y = (int)WinSize::WINSIZE_Y;
	glutCreateWindow("2015182009������ Assignment1");				// ������ ����(������ �̸�)

	//--- System ����
	RenderSystem::GetInstance();									// ���� �ý��� ����
	ResourceSystem::GetInstance();									// ���ҽ� �ý��� ����
	SceneSystem::GetInstance();										// �� �ý��� ����
	InputSystem::GetInstance();										// ��ǲ �ý��� ����

	//--- �̺�Ʈ �Լ� ���
	glutDisplayFunc(DrawScene);										// ��� �Լ��� ����( �� �׸� �Լ� ����)
	glutReshapeFunc(Reshape);										// �ٽ� �׸��� �Լ� ����
	glutMotionFunc(MouseMotion);									// ���콺 ��ġ
	glutTimerFunc(0, InitialLoop, 1);								// ó��
	glutKeyboardFunc(KeyboardDown);									// ���콺 Down
	glutKeyboardUpFunc(KeyboardUp);									// Ű���� Up
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

	//--- ����� â ������ ����
	GlobalUtility::GetInstance().presentWinSize_X = w;
	GlobalUtility::GetInstance().presentWinSize_Y = h;

}

/// <summary>
/// ���콺 ������
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns>����</returns>
GLvoid MouseMotion(int x, int y)
{
	InputSystem& is = InputSystem::GetInstance();

	float xCoordinate = x - (GlobalUtility::GetInstance().presentWinSize_X / 2);
	float yCoordinate = -(y - (GlobalUtility::GetInstance().presentWinSize_Y / 2));

	float normalizedX = xCoordinate / (GlobalUtility::GetInstance().presentWinSize_X / 2);
	float normalizedY = yCoordinate / (GlobalUtility::GetInstance().presentWinSize_Y / 2);

	is.SetMousePos(glm::vec2(normalizedX, normalizedY));
}

/// <summary>
/// ���콺 Ŭ��
/// </summary>
/// <param name="button"></param>
/// <param name="state"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns>����</returns>
GLvoid Mouse(int button, int state, int x, int y)
{
	InputSystem& is = InputSystem::GetInstance();

	float xCoordinate = x - ((float)WinSize::WINSIZE_X / 2);
	float yCoordinate = -(y - ((float)WinSize::WINSIZE_Y / 2));

	float normalizedX = xCoordinate / ((float)WinSize::WINSIZE_X / 2);
	float normalizedY = yCoordinate / ((float)WinSize::WINSIZE_Y / 2);

	if (state == GLUT_DOWN)
	{
		is.SetMouseDown(button, true);
		is.SetMouse(button, true);
	}

	if (state == GLUT_UP)
	{
		is.SetMouse(button, false);
		is.SetMouseUp(button, true);
	}
}

/// <summary>
/// Ű���� Down ó�� �޼ҵ�
/// </summary>
/// <param name="key">�Է��� Ű</param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns>����</returns>
GLvoid KeyboardDown(unsigned char key, int x, int y)
{
	InputSystem& is = InputSystem::GetInstance();

	char receivedKey = key;
	if (islower(receivedKey) != 0)
		receivedKey = toupper(receivedKey);

	is.SetKey(receivedKey, true);
	is.SetKeyDown(receivedKey, true);
}

/// <summary>
/// Ű���� Down ó�� �޼ҵ�
/// </summary>
/// <param name="key">�Է��� Ű</param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns>����</returns>
GLvoid KeyboardUp(unsigned char key, int x, int y)
{
	InputSystem& is = InputSystem::GetInstance();

	char receivedKey = key;
	if (islower(receivedKey) != 0)
		receivedKey = toupper(receivedKey);


	is.SetKey(receivedKey, false);
	is.SetKeyUp(receivedKey,true);
}

GLvoid InitialLoop(int value)
{
	auto scene = std::make_shared<TermProject>();

	auto& ss = SceneSystem::GetInstance();

	ss.StartScene(std::static_pointer_cast<Scene>(scene));
}
