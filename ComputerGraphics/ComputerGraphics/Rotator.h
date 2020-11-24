#pragma once
#include "Component.h"
class Rotator :
    public Component
{
public:
    float speed;
    glm::vec3 direction;

    Rotator(Object* object);

    virtual void OnUpdate();
};

