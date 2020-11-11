#pragma once
#include "stdafx.h"
#include "ShaderInstance.h"
#include "ModelInstnce.h"
#include "Renderer.h"
#include "Object.h"
#include "Camera.h"
#include "Transform.h"

ShaderInstance::ShaderInstance(std::string vertexShaderPath, std::string fregmentShaderPath)
{
	//--- 프로그램 생성
	m_Program = glCreateProgram();

	//--- 쉐이더 생성
	GLuint vertexShader = MakeVertexShader(vertexShaderPath);
	GLuint fregmentShader = MakeFragmentShader(fregmentShaderPath);

	//--- 프로그램에 쉐이더 붙이기
	glAttachShader(m_Program, vertexShader);
	glAttachShader(m_Program, fregmentShader);
	glLinkProgram(m_Program); // 이제 이 프로그램은 실행이 가.능.한 프로그램이 된 것입니다. 
	glUseProgram(m_Program);

	//--- 쉐이더 제거
	glDeleteShader(vertexShader);
	glDeleteShader(fregmentShader);

	//--- 쉐이더 Uniform변수 생성
	m_UniformTransformMat = glGetUniformLocation(GetProgram(), "transform");
	m_UniformViewMat = glGetUniformLocation(GetProgram(), "view");
	m_UniformProjMat = glGetUniformLocation(GetProgram(), "proj");
}

void ShaderInstance::Render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	if (Camera::main != nullptr)
	{
		//--- 프로그램 활성화
		glUseProgram(GetProgram());

		//--- 카메라 뷰 Uniform변수 전달
		auto viewMat = Camera::main->GetViewMatrix();
		glUniformMatrix4fv(m_UniformViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));

		//--- 튜영 Uniform변수 전달
		auto projMat = Camera::main->GetProjMatrix();
		glUniformMatrix4fv(m_UniformProjMat, 1, GL_FALSE, glm::value_ptr(projMat));

		//---이 쉐이더프로그램으로 그려야할 모든 렌더러들의 vao를 가지고와 그린다.
		for (auto rendererPtr = GetRenderer().begin(); rendererPtr != GetRenderer().end(); ++rendererPtr)
		{
			//-- vao 바인딩
			auto renderer = rendererPtr->get();
			auto model = renderer->GetModel();
			auto vao = model->vao;
			glBindVertexArray(vao);

			//-- Uniform변수 전달
			auto transform = renderer->GetBelongingObject()->GetTransform();
			glUniformMatrix4fv(m_UniformTransformMat, 1, GL_FALSE, glm::value_ptr(transform->GetTransformMatrix()));

			//-- 삼각형 그리기
			glDrawElements(GL_TRIANGLES, model->triesIndex.size() * 3, GL_UNSIGNED_INT, 0);
		}
	}
}

void ShaderInstance::SubRenderer(std::shared_ptr<Renderer> renderer)
{
	if (std::find(m_TargetRenderer.begin(), m_TargetRenderer.end(), renderer) != m_TargetRenderer.end())
		m_TargetRenderer.remove(renderer);
	else
		std::cout << "[ShaderInstance AddRenderer()] 삭제하고자 하는 렌더러는 이미 없습니다." << std::endl;
}

void ShaderInstance::AddRenderer(std::shared_ptr<Renderer> renderer)
{
	if (std::find(m_TargetRenderer.begin(), m_TargetRenderer.end(), renderer) == m_TargetRenderer.end())
		m_TargetRenderer.emplace_back(renderer);
	else
		std::cout << "[ShaderInstance AddRenderer()] 이미 추가하려는 렌더러가 있습니다." << std::endl;
}

GLuint ShaderInstance::MakeVertexShader(std::string vertexShaderPath)
{
	char* vertexsource = GlobalUtility::Filetobuf(vertexShaderPath.c_str());
	//--- 버텍스 세이더 객체 만들기
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(vertexshader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
	}

	return vertexshader;
}

GLuint ShaderInstance::MakeFragmentShader(std::string fregmentShaderPath)
{
	char* fragmentsource = GlobalUtility::Filetobuf(fregmentShaderPath.c_str());
	//--- 프래그먼트 세이더 객체 만들기
	GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(fragmentshader);
	//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
	}

	return fragmentshader;
}
