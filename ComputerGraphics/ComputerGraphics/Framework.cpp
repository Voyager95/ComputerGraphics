#include "stdafx.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "SceneSystem.h"


#include "Scene.h"
#include "Object.h"
#include "Renderer.h"
#include "Transform.h"
#include "ModelInstnce.h"

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
	ResourceSystem& rs = ResourceSystem::GetInstance();									// ���ҽ� �ý��� ����
	SceneSystem& ss = SceneSystem::GetInstance();					// �� �ý��� ����

	//--- �ʱ� �� ����
	std::shared_ptr<Scene> exercise16 = std::make_shared<Scene>();

	std::shared_ptr<Object> cube = std::make_shared<Object>("Cube");

	auto t =  cube->GetTransform();
	std::cout << t->GetObjectW()->name << std::endl;

	auto cubeRenderer = std::make_shared<Renderer>(cube);

	//auto model = rs.GetCopiedModelInstance("Cube.obj");
	//for (auto i = model->verticesPos.begin(); i != model->verticesPos.end(); ++i)
	//{
	//	*i *= -0.1;
	//}
	//model->UpdateBuffer();

	auto model = std::make_shared<ModelInstance>();
	model->verticesPos.push_back(glm::vec3(-0.1, -0.1, 0));	
	model->verticesPos.push_back(glm::vec3(0, 0.1, 0));
	model->verticesPos.push_back(glm::vec3(0.1, -0.1, 0));

	model->verticesColor.push_back(glm::vec3(1, 0, 0));
	model->verticesColor.push_back(glm::vec3(0, 1, 0));
	model->verticesColor.push_back(glm::vec3(0, 0, 1));

	model->triesPos.push_back(glm::ivec3(0, 1, 2));
	model->triesColor.push_back(glm::ivec3(2, 1, 0));

	model->UpdateBuffer();

	cubeRenderer->SetOwnModel(model);

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