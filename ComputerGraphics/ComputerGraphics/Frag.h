#pragma once
#include "Component.h"

class Object;

class Frag :
    public Component
{
public:
    float duration;
private:
    float timer;
public:
    Frag(Object* object);

    virtual void OnUpdate();
};

