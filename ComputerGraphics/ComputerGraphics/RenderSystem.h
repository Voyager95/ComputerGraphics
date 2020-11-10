#pragma once
#include <map>
#include <memory>
#include <vector>
#include <string>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include "GlobalUtility.h"
#include "ShaderInstance.h"

class Renderer;

/// <summary>
/// 실제로 그리는 역할을 하는 시스템입니다.
/// - 쉐이더프로그램을 관리합니다.
/// - 오브젝트로 부터 받은 버퍼를 쉐이더 프로그램으로 전달합니다.
/// *싱글톤 디자인 패턴이 적용되었습니다.
/// </summary>
class RenderSystem
{
public:
	//--- 싱글톤 디자인
	RenderSystem(const RenderSystem&) = delete;
	RenderSystem& operator=(const RenderSystem&) = delete;

	/// <summary>
	/// 싱글톤 인스턴스를 얻습니다.
	/// </summary>
	/// <returns></returns>
	static RenderSystem& GetInstance();
private:
	std::map<ShaderType, std::unique_ptr<ShaderInstance>> shaders;
public:

	void Render();
	void AddRenderer(ShaderType type, std::shared_ptr<Renderer> renderer);
	void SubRenderer(ShaderType type, std::shared_ptr<Renderer> renderer);
private:	
	/// <summary>
	/// - 쉐이더를 생성합니다.
	/// </summary>
	RenderSystem();

	/// <summary>
	/// 쉐이더를 생성합니다.
	/// </summary>
	void InitShader();
};


