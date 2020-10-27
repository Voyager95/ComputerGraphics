#include "Renderer.h"
#include "stdafx.h"
Renderer::Renderer(std::shared_ptr<Object> object) : Component(object)
{
	//--- 변수 초기화
	m_TargetShader = VERTEX;
	m_IsAssigned = false;
}

Renderer::Renderer(std::shared_ptr<Object> object, std::string objPath) : Renderer(object)
{
}

void Renderer::SetTargetShader(ShaderType type)
{
	RenderSystem& rs = RenderSystem::GetInstance();

	//--- 현재 렌더 시스템에 추가되어 있다면 제거
	if (m_IsAssigned == true)
	{
		rs.SubRenderer(m_TargetShader, shared_from_this());
		m_IsAssigned = false;
	}
	

	//--- 쉐이더 변경
	m_TargetShader = type;

	//--- 상태 검사
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
	if (GetEnable() == false)
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
			rs.AddRenderer(m_TargetShader, shared_from_this());
		}
	}
	else
	{
		if (m_IsAssigned)
		{
			RenderSystem& rs = RenderSystem::GetInstance();
			rs.SubRenderer(m_TargetShader, shared_from_this());
		}
		else
		{

		}
	}
}