#pragma once
#include "stdafx.h"
#include "Component.h"

class RenderSystem;
class ModelInstance;
class TextureInstance;


/// <summary>
/// 오브젝트를 그리는 컴포넌트 입니다.
/// </summary>
class Renderer :
    public Component
{
public:

private:

    //--- 모델 설정
    bool isSharedModel;             // 이 모델이 ResourceSystem으로부터 가지고온 공유 모델인지 확인합니다.
    bool m_IsModelExist;              // 모델이 있는지 판단하는 플레그입니다.
    std::shared_ptr<ModelInstance> m_Model;

    //--- 텍스쳐 설정
    bool m_IsTexExist;
    std::shared_ptr<TextureInstance> m_Tex;

    //--- 쉐이더 설정    
    bool m_IsAssigned;              // 이 렌더러가 렌더시스템에 등록되어 있는지 판단하는 플레그 입니다.
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
    /// ResourceSystem을 통해서 ModelInstance를 가지고 옵니다.
    /// </summary>
    /// <param name="objName">오브젝트의 위치이다</param>
    void SetSharedModel(std::string key);

    void SetSharedTextrue(std::string key);

    /// <summary>
    /// 커스텀 모델을 제공합니다.
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
    /// 현재 Renderer의 설정을 체크합니다. 만일 화면에 그려야하는 경우 RenderSystem의 ShaderInstance에 자기 자신을 등록하여 그리도록합니다.
    /// </summary>
    void CheckState();
};

