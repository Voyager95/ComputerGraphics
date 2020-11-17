#pragma once
#include "stdafx.h"
#include "Component.h"

enum class CameraProj
{
    ORTHO,
    PERSPECTIVE
};

class Camera :
    public Component, public std::enable_shared_from_this<Camera>
{
public:
    static std::list<std::shared_ptr<Camera>> cameras;
    static std::shared_ptr<Camera> main;
private:
    int m_Priority;
public:
    CameraProj projOption;

    //--- Ortho Proj Option
    float left;
    float right;
    float bottom;
    float top;

    //--- Perspective Proj Option
    float fovy;

    //--- Proj Common Option
    float nearPlane;
    float farPlane;

    Camera(std::shared_ptr<Object> object);
    Camera(int priority, std::shared_ptr<Object> object);

    //--- Getter
    int GetPriority() { return m_Priority; }

    //--- Setter
    void SetPriority(int value);

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjMatrix();

    virtual void OnCreate();
    virtual void OnDestory();

private:
};

