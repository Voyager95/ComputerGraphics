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
/// 쉐이더 프로그램, 이 쉐이더로 그릴 Renderer Component의 집합입니다.
/// </summary>
class ShaderInstance
{
private:
	GLuint m_Program;												// 쉐이더 프로그램
	GLuint m_UniformTransformMat;									// Uniform 변수
	GLuint m_UniformProjMat;
	GLuint m_UniformViewMat;										// Uniform 변수
	GLuint m_UniformTexture;
	std::list<std::shared_ptr<Renderer>> m_TargetRenderer;			// 이 쉐이더를 사용하는 렌더러 입니다.

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
	/// 쉐이더 버텍스를 만들어 반환합니다.
	/// </summary>
	/// <returns> 참조 용도의 값입니다. *쉐이더 프로그램에 바인드 후에는 삭제하십시오 </returns>
	GLuint MakeVertexShader(std::string vertexShaderPath);

	/// <summary>
	/// 프레그먼트 버텍스를 만들어 반환합니다.
	/// </summary>
	/// <returns> 참조 용도의 값입니다. *쉐이더 프로그램에 바인드 후에는 삭제하십시오 </returns>
	GLuint MakeFragmentShader(std::string fregmentShaderPath);
};

