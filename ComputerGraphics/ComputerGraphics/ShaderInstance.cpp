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
	//--- ���α׷� ����
	m_Program = glCreateProgram();

	//--- ���̴� ����
	GLuint vertexShader = MakeVertexShader(vertexShaderPath);
	GLuint fregmentShader = MakeFragmentShader(fregmentShaderPath);

	//--- ���α׷��� ���̴� ���̱�
	glAttachShader(m_Program, vertexShader);
	glAttachShader(m_Program, fregmentShader);
	glLinkProgram(m_Program); // ���� �� ���α׷��� ������ ��.��.�� ���α׷��� �� ���Դϴ�. 
	glUseProgram(m_Program);

	//--- ���̴� ����
	glDeleteShader(vertexShader);
	glDeleteShader(fregmentShader);

	//--- ���̴� Uniform���� ����
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
		//--- ���α׷� Ȱ��ȭ
		glUseProgram(GetProgram());

		//--- ī�޶� �� Uniform���� ����
		auto viewMat = Camera::main->GetViewMatrix();
		glUniformMatrix4fv(m_UniformViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));

		//--- Ʃ�� Uniform���� ����
		auto projMat = Camera::main->GetProjMatrix();
		glUniformMatrix4fv(m_UniformProjMat, 1, GL_FALSE, glm::value_ptr(projMat));

		//---�� ���̴����α׷����� �׷����� ��� ���������� vao�� ������� �׸���.
		for (auto rendererPtr = GetRenderer().begin(); rendererPtr != GetRenderer().end(); ++rendererPtr)
		{
			//-- vao ���ε�
			auto renderer = rendererPtr->get();
			auto model = renderer->GetModel();
			auto vao = model->vao;
			glBindVertexArray(vao);

			//-- Uniform���� ����
			auto transform = renderer->GetBelongingObject()->GetTransform();
			glUniformMatrix4fv(m_UniformTransformMat, 1, GL_FALSE, glm::value_ptr(transform->GetTransformMatrix()));

			//-- �ﰢ�� �׸���
			glDrawElements(GL_TRIANGLES, model->triesIndex.size() * 3, GL_UNSIGNED_INT, 0);
		}
	}
}

void ShaderInstance::SubRenderer(std::shared_ptr<Renderer> renderer)
{
	if (std::find(m_TargetRenderer.begin(), m_TargetRenderer.end(), renderer) != m_TargetRenderer.end())
		m_TargetRenderer.remove(renderer);
	else
		std::cout << "[ShaderInstance AddRenderer()] �����ϰ��� �ϴ� �������� �̹� �����ϴ�." << std::endl;
}

void ShaderInstance::AddRenderer(std::shared_ptr<Renderer> renderer)
{
	if (std::find(m_TargetRenderer.begin(), m_TargetRenderer.end(), renderer) == m_TargetRenderer.end())
		m_TargetRenderer.emplace_back(renderer);
	else
		std::cout << "[ShaderInstance AddRenderer()] �̹� �߰��Ϸ��� �������� �ֽ��ϴ�." << std::endl;
}

GLuint ShaderInstance::MakeVertexShader(std::string vertexShaderPath)
{
	char* vertexsource = GlobalUtility::Filetobuf(vertexShaderPath.c_str());
	//--- ���ؽ� ���̴� ��ü �����
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, 0);
	//--- ���ؽ� ���̴� �������ϱ�
	glCompileShader(vertexshader);
	//--- �������� ����� ���� ���� ���: ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexshader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
	}

	return vertexshader;
}

GLuint ShaderInstance::MakeFragmentShader(std::string fregmentShaderPath)
{
	char* fragmentsource = GlobalUtility::Filetobuf(fregmentShaderPath.c_str());
	//--- �����׸�Ʈ ���̴� ��ü �����
	GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, 0);
	//--- �����׸�Ʈ ���̴� ������
	glCompileShader(fragmentshader);
	//--- �������� ����� ���� ���� ���: ������ ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
		std::cerr << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
	}

	return fragmentshader;
}
