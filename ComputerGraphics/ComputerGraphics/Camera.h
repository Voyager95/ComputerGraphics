#pragma once
#include "stdafx.h"
#include "Component.h"

class Camera :
    public Component, public std::enable_shared_from_this<Camera>
{
public:
    static std::list<std::shared_ptr<Camera>> cameras;
    static std::shared_ptr<Camera> main;
private:
    int m_Priority;
public:
    Camera(int priority, std::shared_ptr<Object> object);

    //--- Getter
    int GetPriority() { return m_Priority; }

    //--- Setter
    void SetPriority(int value);

    glm::mat4 GetViewMatrix();

    virtual void OnCreate();
    virtual void OnDestory();

private:
};

