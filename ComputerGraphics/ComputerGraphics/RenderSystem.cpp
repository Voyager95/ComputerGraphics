#include "RenderSystem.h"
#include "stdafx.h"
#include "Renderer.h"

void RenderSystem::InitShader()
{
	//---VERTEX shader�� �߰� 
	shaders.insert(std::pair<ShaderType, std::unique_ptr<ShaderInstance>>( VERTEX , std::make_unique<ShaderInstance>("vertex.glsl", "fragment.glsl")));
}

RenderSystem& RenderSystem::GetInstance()
{
	static RenderSystem instance;
	return instance;
}

RenderSystem::RenderSystem()
{
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



	//--- ���̴� ����
	InitShader();
}

void RenderSystem::Render()
{
	//--- ����� ���� ����
	glClearColor(0.5, 0.5, 0.5, 1.0f);
	//glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ������ ���������ο� ���̴� �ҷ�����

	for (auto s = shaders.begin(); s != shaders.end(); ++s)
	{
		s->second->Render();
	}

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

void RenderSystem::AddRenderer(ShaderType type, std::shared_ptr<Renderer> renderer)
{
	if (shaders.find(type) != shaders.end())
	{
		shaders[type]->AddRenderer(renderer);
	}
	else
	{
		std::cout << "[RenderSystem AddRenderer()] �ش� ���̴� �ν��Ͻ��� �����ϴ�" << std::endl;
	}
}

void RenderSystem::SubRenderer(ShaderType type, std::shared_ptr<Renderer> renderer)
{
	if (shaders.find(type) != shaders.end())
	{
		shaders[type]->SubRenderer(renderer);
	}
	else
	{
		std::cout << "[RenderSystem AddRenderer()] �ش� ���̴� �ν��Ͻ��� �����ϴ�" << std::endl;
	}
}
