#pragma once
#include "stdafx.h"
#include "Scene.h"
#include "Component.h"

class ModelInstance;

class Assignment1 :
    public Scene
{
public:
    Assignment1();
};

class SliceLine : 
    public Component
{
private:
    bool m_IsDragStart;

    std::shared_ptr<ModelInstance> m_Model;

public:
    SliceLine(Object* object);

    virtual void OnCreate();
    virtual void OnUpdate();
};

