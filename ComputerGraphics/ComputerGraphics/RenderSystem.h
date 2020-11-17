#pragma once
#include "stdafx.h"
#include "GlobalUtility.h"
#include "ShaderInstance.h"

class ShaderInstance;
class Renderer;

/// <summary>
/// ������ �׸��� ������ �ϴ� �ý����Դϴ�.
/// - ���̴����α׷��� �����մϴ�.
/// - ������Ʈ�� ���� ���� ���۸� ���̴� ���α׷����� �����մϴ�.
/// *�̱��� ������ ������ ����Ǿ����ϴ�.
/// </summary>
class RenderSystem
{
public:
	//--- �̱��� ������
	RenderSystem(const RenderSystem&) = delete;
	RenderSystem& operator=(const RenderSystem&) = delete;

	/// <summary>
	/// �̱��� �ν��Ͻ��� ����ϴ�.
	/// </summary>
	/// <returns></returns>
	static RenderSystem& GetInstance();
private:
	std::map<ShaderType, std::unique_ptr<ShaderInstance>> shaders;
public:

	void Render();
	void AddRenderer(ShaderType type, std::shared_ptr<Renderer> renderer);
	void SubRenderer(ShaderType type, std::shared_ptr<Renderer> renderer);

	void SetPolygonMode(int mode) { glPolygonMode(GL_FRONT_AND_BACK, mode); }
private:	
	/// <summary>
	/// - ���̴��� �����մϴ�.
	/// </summary>
	RenderSystem();

	/// <summary>
	/// ���̴��� �����մϴ�.
	/// </summary>
	void InitShader();
};


