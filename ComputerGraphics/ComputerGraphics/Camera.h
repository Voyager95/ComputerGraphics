#pragma once
#include "stdafx.h"
#include "Component.h"

class Camera :
    public Component
{
public:
    static std::list<std::shared_ptr<Camera>> cameras;
    static std::shared_ptr<Camera> main;
private:
    int m_Priority;
public:
    Camera(std::shared_ptr<Object> object);

    virtual void OnCreate();
    virtual void OnDestory();
};

