#pragma once
#include <vector>
#include <memory>
#include <list>
#include <string>
#include <algorithm>
#include <gl/glew.h>
#include "GlobalUtility.h"

class Renderer;

/// <summary>
/// ���̴� ���α׷�, �� ���̴��� �׸� Renderer Component�� �����Դϴ�.
/// </summary>
class ShaderInstance
{
private:
	GLuint m_Program;												// ���̴� ���α׷�
	GLuint m_UniformTransformMat;									// Uniform ����
	GLuint m_UniformProjMat;
	GLuint m_UniformViewMat;										// Uniform ����
	GLuint m_UniformTexture;
	std::list<std::shared_ptr<Renderer>> m_TargetRenderer;			// �� ���̴��� ����ϴ� ������ �Դϴ�.

public:
	//--- Constructor
	ShaderInstance(std::string vertexShaderPath, std::string fregmentShaderPath);

	//--- Getter
	GLuint GetProgram() { return m_Program; };
	std::list<std::shared_ptr<Renderer>>& GetRenderer() {return m_TargetRenderer; };


	void Render();
	void SubRenderer(std::shared_ptr<Renderer> renderer);
	void AddRenderer(std::shared_ptr<Renderer> renderer);
private:
	/// <summary>
	/// ���̴� ���ؽ��� ����� ��ȯ�մϴ�.
	/// </summary>
	/// <returns> ���� �뵵�� ���Դϴ�. *���̴� ���α׷��� ���ε� �Ŀ��� �����Ͻʽÿ� </returns>
	GLuint MakeVertexShader(std::string vertexShaderPath);

	/// <summary>
	/// �����׸�Ʈ ���ؽ��� ����� ��ȯ�մϴ�.
	/// </summary>
	/// <returns> ���� �뵵�� ���Դϴ�. *���̴� ���α׷��� ���ε� �Ŀ��� �����Ͻʽÿ� </returns>
	GLuint MakeFragmentShader(std::string fregmentShaderPath);
};

