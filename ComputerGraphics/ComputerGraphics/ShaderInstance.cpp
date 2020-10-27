#include "ShaderInstance.h"
#include "stdafx.h"
#include "Renderer.h"

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

	//--- ���̴� ����
	glDeleteShader(vertexShader);
	glDeleteShader(fregmentShader);
}

void ShaderInstance::Render()
{
	//--- ���α׷� Ȱ��ȭ
	glUseProgram(GetProgram());

	//---�� ���̴����α׷����� �׷����� ��� ���������� vao�� ������� �׸���.
	for (auto rendererPtr = GetRenderer().begin(); rendererPtr != GetRenderer().end(); ++rendererPtr)
	{
		auto renderer = rendererPtr->get();

		//-- vao ���ε�
		glBindVertexArray(renderer->GetModel()->vao);

		// �ﰢ�� �׸���
		glDrawElements(GL_TRIANGLES, 6, GL_INT,0);
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
	char* vertexsource = Filetobuf(vertexShaderPath.c_str());
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
	char* fragmentsource = Filetobuf(fregmentShaderPath.c_str());
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
