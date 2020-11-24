#include "stdafx.h"
#include "RenderSystem.h"
#include "GlobalUtility.h"
#include "ShaderInstance.h"
#include "Renderer.h"

void RenderSystem::InitShader()
{
	//---shader �߰�
	//--VERTEX_ELEMENT �߰�
	shaders.insert(std::pair<ShaderType, std::unique_ptr<ShaderInstance>>( ShaderType::VERTEX_ELEMENT , std::make_unique<ShaderInstance>(ShaderType::VERTEX_ELEMENT)));
	//--VERTEX_ARRAY �߰�
	shaders.insert(std::pair<ShaderType, std::unique_ptr<ShaderInstance>>(ShaderType::VERTEX_ARRAY, std::make_unique<ShaderInstance>(ShaderType::VERTEX_ARRAY)));
	//--TEXTURE_ARRAY �߰�
	shaders.insert(std::pair<ShaderType, std::unique_ptr<ShaderInstance>>(ShaderType::TEXTURE_ARRAY, std::make_unique<ShaderInstance>(ShaderType::TEXTURE_ARRAY)));
	//--TEXTURE_ELEMENT �߰�
	shaders.insert(std::pair<ShaderType, std::unique_ptr<ShaderInstance>>(ShaderType::TEXTURE_ELEMENT, std::make_unique<ShaderInstance>(ShaderType::TEXTURE_ELEMENT)));
	//-- LINE �߰�
	shaders.insert(std::pair<ShaderType, std::unique_ptr<ShaderInstance>>(ShaderType::LINE, std::make_unique<ShaderInstance>(ShaderType::LINE)));
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

	//--- ���� ����
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glLineWidth(3.0f);

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

	//--- ����ī�޶� ������
	for (auto s = shaders.begin(); s != shaders.end(); ++s)
	{
		s->second->Render();
	}

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

void RenderSystem::AddRenderer(ShaderType type, Renderer* renderer)
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

void RenderSystem::SubRenderer(ShaderType type, Renderer* renderer)
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
