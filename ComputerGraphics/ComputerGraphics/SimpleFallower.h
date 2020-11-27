#pragma once
#include "Component.h"

class Object;
class Transform;
class SimpleFallower :
    public Component
{
public:
    bool fallow;
    glm::vec3 offset;
    Transform* pTarget;

    SimpleFallower(Object* object);

    virtual void OnUpdate();
};

