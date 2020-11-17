#include "stdafx.h"
#include "Renderer.h"
#include "ResourceSystem.h"
#include "RenderSystem.h"
#include "ModelInstnce.h"

Renderer::Renderer(std::shared_ptr<Object> object) : Component(object)
{
	//--- 변수 초기화
	m_TargetShaderType = ShaderType::VERTEX_ELEMENT;
	m_IsAssigned = false;
	m_IsModelExist = false;
}

Renderer::Renderer(std::shared_ptr<Object> object, std::string objPath) : Renderer(object)
{
	SetSharedModel(objPath);
}

void Renderer::SetTargetShader(ShaderType type)
{
	RenderSystem& rs = RenderSystem::GetInstance();

	//--- 현재 렌더 시스템에 추가되어 있다면 제거
	if (m_IsAssigned == true)
	{
		rs.SubRenderer(m_TargetShaderType, shared_from_this());
		m_IsAssigned = false;
	}
	

	//--- 쉐이더 변경
	m_TargetShaderType = type;

	//--- 상태 검사
	CheckState();
	
}

void Renderer::SetSharedModel(std::string key)
{
	ResourceSystem& ss = ResourceSystem::GetInstance();
	
	auto model = ss.GetSharedModelInstance(key);

	if (model == nullptr)
	{
		m_Model = nullptr;
		m_IsModelExist = false;
	}
	else
	{
		m_Model = model;
		m_IsModelExist = true;
	}

	CheckState();
}

void Renderer::SetSharedTextrue(std::string key)
{
	ResourceSystem& ss = ResourceSystem::GetInstance();

	auto texture = ss.GetSharedTextureInstance(key);

	if (texture == nullptr)
	{
		m_Tex = nullptr;
		m_IsTexExist = false;
	}
	else
	{
		m_Tex = texture;
		m_IsTexExist = true;
	}
}

void Renderer::SetOwnModel(std::shared_ptr<ModelInstance> model)
{
	m_Model = model;
	m_IsModelExist = true;
	CheckState();
}

void Renderer::OnEnable()
{
	CheckState();
}

void Renderer::OnDisable()
{
	CheckState();
}

void Renderer::CheckState()
{
	//--- 렌더를 해야할지 판단합니다. *현재는 enable된 상태라면 ShaderInstance에 등록합니다.
	bool isRender = true;

	//--- 조건들 확인
	if (GetEnable() == false)
		isRender = false;

	if (GetIsModelExist() == false)
		isRender = false;

	//--- 렌더시스템에 등록 또는 해제 합니다.
	if (isRender)
	{
		if (m_IsAssigned)			// 항당 되어있다면 아무것도 하지 않습니다.
		{

		}
		else
		{
			RenderSystem& rs = RenderSystem::GetInstance();
			rs.AddRenderer(m_TargetShaderType, shared_from_this());
		}
	}
	else
	{
		if (m_IsAssigned)
		{
			RenderSystem& rs = RenderSystem::GetInstance();
			rs.SubRenderer(m_TargetShaderType, shared_from_this());
		}
		else
		{

		}
	}
}