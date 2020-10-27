#include "Renderer.h"
#include "stdafx.h"
Renderer::Renderer(std::shared_ptr<Object> object) : Component(object)
{
	//--- ���� �ʱ�ȭ
	m_TargetShader = VERTEX;
	m_IsAssigned = false;
}

Renderer::Renderer(std::shared_ptr<Object> object, std::string objPath) : Renderer(object)
{
}

void Renderer::SetTargetShader(ShaderType type)
{
	RenderSystem& rs = RenderSystem::GetInstance();

	//--- ���� ���� �ý��ۿ� �߰��Ǿ� �ִٸ� ����
	if (m_IsAssigned == true)
	{
		rs.SubRenderer(m_TargetShader, shared_from_this());
		m_IsAssigned = false;
	}
	

	//--- ���̴� ����
	m_TargetShader = type;

	//--- ���� �˻�
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
	//--- ������ �ؾ����� �Ǵ��մϴ�. *����� enable�� ���¶�� ShaderInstance�� ����մϴ�.
	bool isRender = true;
	if (GetEnable() == false)
		isRender = false;

	//--- �����ý��ۿ� ��� �Ǵ� ���� �մϴ�.
	if (isRender)
	{
		if (m_IsAssigned)			// �״� �Ǿ��ִٸ� �ƹ��͵� ���� �ʽ��ϴ�.
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