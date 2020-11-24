#include "stdafx.h"
#include "RenderSystem.h"
#include "GlobalUtility.h"
#include "ShaderInstance.h"
#include "Renderer.h"

void RenderSystem::InitShader()
{
	//---shader 추가
	//--VERTEX_ELEMENT 추가
	shaders.insert(std::pair<ShaderType, std::unique_ptr<ShaderInstance>>( ShaderType::VERTEX_ELEMENT , std::make_unique<ShaderInstance>(ShaderType::VERTEX_ELEMENT)));
	//--VERTEX_ARRAY 추가
	shaders.insert(std::pair<ShaderType, std::unique_ptr<ShaderInstance>>(ShaderType::VERTEX_ARRAY, std::make_unique<ShaderInstance>(ShaderType::VERTEX_ARRAY)));
	//--TEXTURE_ARRAY 추가
	shaders.insert(std::pair<ShaderType, std::unique_ptr<ShaderInstance>>(ShaderType::TEXTURE_ARRAY, std::make_unique<ShaderInstance>(ShaderType::TEXTURE_ARRAY)));
	//--TEXTURE_ELEMENT 추가
	shaders.insert(std::pair<ShaderType, std::unique_ptr<ShaderInstance>>(ShaderType::TEXTURE_ELEMENT, std::make_unique<ShaderInstance>(ShaderType::TEXTURE_ELEMENT)));
	//-- LINE 추가
	shaders.insert(std::pair<ShaderType, std::unique_ptr<ShaderInstance>>(ShaderType::LINE, std::make_unique<ShaderInstance>(ShaderType::LINE)));
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

	//--- 렌더 설정
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glLineWidth(3.0f);

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

	//--- 메인카메라 렌더링
	for (auto s = shaders.begin(); s != shaders.end(); ++s)
	{
		s->second->Render();
	}

	glutSwapBuffers(); // 화면에 출력하기
}

void RenderSystem::AddRenderer(ShaderType type, Renderer* renderer)
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

void RenderSystem::SubRenderer(ShaderType type, Renderer* renderer)
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
