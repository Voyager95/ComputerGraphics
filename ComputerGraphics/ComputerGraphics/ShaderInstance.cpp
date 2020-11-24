#pragma once
#include "stdafx.h"
#include "ShaderInstance.h"
#include "ModelInstnce.h"
#include "TextureInstance.h"
#include "Renderer.h"
#include "Object.h"
#include "Camera.h"
#include "Transform.h"

ShaderInstance::ShaderInstance(ShaderType type)
{
	m_Type = type;

	//--- ���α׷� ����
	m_Program = glCreateProgram();

	//--- ���̴� ����	
	GLuint vertexShader = 0;
	GLuint fregmentShader = 0;
	switch (m_Type)
	{
	case ShaderType::VERTEX_ELEMENT:
		vertexShader = MakeVertexShader("VertexShader.glsl");
		fregmentShader = MakeFragmentShader("FragmentShader_Vertex.glsl");
		break;
	case ShaderType::TEXTURE_ELEMENT:
		vertexShader = MakeVertexShader("VertexShader.glsl");
		fregmentShader = MakeFragmentShader("FragmentShader_Texture.glsl");
		break;
	case ShaderType::VERTEX_ARRAY:
		vertexShader = MakeVertexShader("VertexShader.glsl");
		fregmentShader = MakeFragmentShader("FragmentShader_Vertex.glsl");
		break;
	case ShaderType::TEXTURE_ARRAY:
		vertexShader = MakeVertexShader("VertexShader.glsl");
		fregmentShader = MakeFragmentShader("FragmentShader_Texture.glsl");
		break;
	case ShaderType::LINE: 
		vertexShader = MakeVertexShader("VertexShader.glsl");
		fregmentShader = MakeFragmentShader("FragmentShader_Vertex.glsl");
		break;
	default:
		break;
	}

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
	m_UniformTexture = glGetUniformLocation(GetProgram(), "tex");
	glUniform1i(m_UniformTexture, 0);
}

void ShaderInstance::Render()
{
	if (Camera::main != nullptr)
	{
		//--- ���α׷� Ȱ��ȭ
		glUseProgram(GetProgram());

		//--- ī�޶� �� Uniform���� ����
		auto viewMat = Camera::main->GetViewMatrix();
		glUniformMatrix4fv(m_UniformViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));

		//--- ���� Uniform���� ����
		auto projMat = Camera::main->GetProjMatrix();
		glUniformMatrix4fv(m_UniformProjMat, 1, GL_FALSE, glm::value_ptr(projMat));

		//---�� ���̴����α׷����� �׷����� ��� ���������� vao�� ������� �׸���.
		for (auto rendererPtr = GetRenderer().begin(); rendererPtr != GetRenderer().end(); ++rendererPtr)
		{
			//-- vao ���ε�
			auto renderer = *rendererPtr;
			auto model = renderer->GetModel();
			auto vao = model->vao;
			glBindVertexArray(vao);

			//-- Texture���� ����
			if (renderer->GetIsTextureExist() == true)
			{
				auto tex = renderer->GetTexture();
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex->texture);
			}

			//-- Uniform���� ����
			auto transform = renderer->GetBelongingObject()->GetTransform();
			glUniformMatrix4fv(m_UniformTransformMat, 1, GL_FALSE, glm::value_ptr(transform->GetTransformMatrix()));

			//-- �ﰢ�� �׸���
			if (m_Type == ShaderType::TEXTURE_ELEMENT || m_Type == ShaderType::VERTEX_ELEMENT)
				glDrawElements(GL_TRIANGLES, model->triesIndex.size() * 3, GL_UNSIGNED_INT, 0);
			if (m_Type == ShaderType::LINE)
				glDrawArrays(GL_TRIANGLES, 0, 3);
			else
				glDrawArrays(GL_TRIANGLES, 0, model->triesIndex.size() * 3);
		}
	}
}

void ShaderInstance::SubRenderer(Renderer* renderer)
{
	if (std::find(m_TargetRenderer.begin(), m_TargetRenderer.end(), renderer) != m_TargetRenderer.end())
		m_TargetRenderer.remove(renderer);
	else
		std::cout << "[ShaderInstance AddRenderer()] �����ϰ��� �ϴ� �������� �̹� �����ϴ�." << std::endl;
}

void ShaderInstance::AddRenderer(Renderer* renderer)
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
