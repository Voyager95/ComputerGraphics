#include "stdafx.h"
#include "Renderer.h"
#include "ResourceSystem.h"

Renderer::Renderer(std::shared_ptr<Object> object) : Component(object)
{
	//--- ���� �ʱ�ȭ
	m_TargetShaderType = ShaderType::VERTEX;
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

	//--- ���� ���� �ý��ۿ� �߰��Ǿ� �ִٸ� ����
	if (m_IsAssigned == true)
	{
		rs.SubRenderer(m_TargetShaderType, enable_shared_from_this<Renderer>::shared_from_this());
		m_IsAssigned = false;
	}
	

	//--- ���̴� ����
	m_TargetShaderType = type;

	//--- ���� �˻�
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
	//--- ������ �ؾ����� �Ǵ��մϴ�. *����� enable�� ���¶�� ShaderInstance�� ����մϴ�.
	bool isRender = true;

	//--- ���ǵ� Ȯ��
	if (GetEnable() == false)
		isRender = false;

	if (GetIsModelExist() == false)
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
			rs.AddRenderer(m_TargetShaderType, enable_shared_from_this<Renderer>::shared_from_this());
		}
	}
	else
	{
		if (m_IsAssigned)
		{
			RenderSystem& rs = RenderSystem::GetInstance();
			rs.SubRenderer(m_TargetShaderType, enable_shared_from_this<Renderer>::shared_from_this());
		}
		else
		{

		}
	}
}