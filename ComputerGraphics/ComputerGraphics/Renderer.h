#pragma once
#include "stdafx.h"
#include "Component.h"

class RenderSystem;
class ModelInstance;


/// <summary>
/// ������Ʈ�� �׸��� ������Ʈ �Դϴ�.
/// </summary>
class Renderer :
    public Component, public std::enable_shared_from_this<Renderer>
{
public:

private:

    //--- �� ����
    bool isSharedModel;             // �� ���� ResourceSystem���κ��� ������� ���� ������ Ȯ���մϴ�.
    bool m_IsModelExist;              // ���� �ִ��� �Ǵ��ϴ� �÷����Դϴ�.
    std::shared_ptr<ModelInstance> m_Model;

    //--- �ؽ��� ����
    //std::shared_ptr<TextureInstance> m_Tex;

    //--- ���̴� ����    
    bool m_IsAssigned;              // �� �������� �����ý��ۿ� ��ϵǾ� �ִ��� �Ǵ��ϴ� �÷��� �Դϴ�.
    ShaderType m_TargetShaderType;



public:
    //--- Constructor
    Renderer(std::shared_ptr<Object> object);
    Renderer(std::shared_ptr<Object> object, std::string objPath);

    //--- Getter
    std::shared_ptr<ModelInstance> GetModel() { return m_Model; }
    bool GetIsModelExist() { return m_IsModelExist; }

    //--- Setter
    void SetTargetShader(ShaderType type);

    /// <summary>
    /// ResourceSystem�� ���ؼ� ModelInstance�� ������ �ɴϴ�.
    /// </summary>
    /// <param name="objName">������Ʈ�� ��ġ�̴�</param>
    void SetSharedModel(std::string key);

    /// <summary>
    /// Ŀ���� ���� �����մϴ�.
    /// </summary>
    /// <param name="model"></param>
    void SetOwnModel(std::shared_ptr<ModelInstance> model);

    //--- Event
    
    /// <summary>
    /// CheckState()
    /// </summary>
    virtual void OnEnable();


    virtual void OnDisable();

private:

    /// <summary>
    /// ���� Renderer�� ������ üũ�մϴ�. ���� ȭ�鿡 �׷����ϴ� ��� RenderSystem�� ShaderInstance�� �ڱ� �ڽ��� ����Ͽ� �׸������մϴ�.
    /// </summary>
    void CheckState();
};

