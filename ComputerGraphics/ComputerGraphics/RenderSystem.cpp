#include "RenderSystem.h"
#include "stdafx.h"
#include "Renderer.h"

void RenderSystem::InitShader()
{
	//---VERTEX shader을 추가 
	shaders.insert(std::pair<ShaderType, std::unique_ptr<ShaderInstance>>( VERTEX , std::make_unique<ShaderInstance>("vertex.glsl", "fragment.glsl")));
}

RenderSystem& RenderSystem::GetInstance()
{
	static RenderSystem instance;
	return instance;
}

RenderSystem::RenderSystem()
{
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew(즉 Open GL) 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl
			;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";



	//--- 쉐이더 생성
	InitShader();
}

void RenderSystem::Render()
{
	//--- 변경된 배경색 설정
	glClearColor(0.5, 0.5, 0.5, 1.0f);
	//glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 렌더링 파이프라인에 세이더 불러오기

	for (auto s = shaders.begin(); s != shaders.end(); ++s)
	{
		s->second->Render();
	}

	glutSwapBuffers(); // 화면에 출력하기
}

void RenderSystem::AddRenderer(ShaderType type, std::shared_ptr<Renderer> renderer)
{
	if (shaders.find(type) != shaders.end())
	{
		shaders[type]->AddRenderer(renderer);
	}
	else
	{
		std::cout << "[RenderSystem AddRenderer()] 해당 쉐이더 인스턴스가 없습니다" << std::endl;
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
		std::cout << "[RenderSystem AddRenderer()] 해당 쉐이더 인스턴스가 없습니다" << std::endl;
	}
}
