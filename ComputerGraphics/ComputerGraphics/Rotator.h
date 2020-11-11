#pragma once
#include "stdafx.h"
#include "Component.h"

class Object;

class Rotator :
    public Component
{
public:
    float speed;
    glm::vec3 direction;

    Rotator(std::shared_ptr<Object> object);

    virtual void OnUpdate();
};

