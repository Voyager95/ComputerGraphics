#pragma once
#include "stdafx.h"
#include "Component.h"

class RenderSystem;
class ModelInstance;
class TextureInstance;


/// <summary>
/// ������Ʈ�� �׸��� ������Ʈ �Դϴ�.
/// </summary>
class Renderer :
    public Component
{
public:

private:

    //--- �� ����
    bool isSharedModel;             // �� ���� ResourceSystem���κ��� ������� ���� ������ Ȯ���մϴ�.
    bool m_IsModelExist;              // ���� �ִ��� �Ǵ��ϴ� �÷����Դϴ�.
    std::shared_ptr<ModelInstance> m_Model;

    //--- �ؽ��� ����
    bool m_IsTexExist;
    std::shared_ptr<TextureInstance> m_Tex;

    //--- ���̴� ����    
    bool m_IsAssigned;              // �� �������� �����ý��ۿ� ��ϵǾ� �ִ��� �Ǵ��ϴ� �÷��� �Դϴ�.
    ShaderType m_TargetShaderType;



public:
    //--- Constructor
    Renderer(Object* object);
    ~Renderer();

    //--- Getter
    std::shared_ptr<TextureInstance> GetTexture() { return m_Tex; }
    std::shared_ptr<ModelInstance> GetModel() { return m_Model; }
    bool GetIsModelExist() { return m_IsModelExist; }
    bool GetIsTextureExist() { return m_IsTexExist; }

    //--- Setter
    void SetTargetShader(ShaderType type);

    /// <summary>
    /// ResourceSystem�� ���ؼ� ModelInstance�� ������ �ɴϴ�.
    /// </summary>
    /// <param name="objName">������Ʈ�� ��ġ�̴�</param>
    void SetSharedModel(std::string key);

    void SetSharedTextrue(std::string key);

    /// <summary>
    /// Ŀ���� ���� �����մϴ�.
    /// </summary>
    /// <param name="model"></param>
    void SetOwnModel(std::shared_ptr<ModelInstance> model);

    //--- Event
    
    virtual void OnEnable();

    virtual void OnDisable();

    virtual void OnDestroy();

    virtual void OnAddScene();

    virtual void OnSubScene();

private:

    /// <summary>
    /// ���� Renderer�� ������ üũ�մϴ�. ���� ȭ�鿡 �׷����ϴ� ��� RenderSystem�� ShaderInstance�� �ڱ� �ڽ��� ����Ͽ� �׸������մϴ�.
    /// </summary>
    void CheckState();
};

