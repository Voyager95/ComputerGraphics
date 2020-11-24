#pragma once
#include "stdafx.h"
#include "Component.h"

class Object;

class SimpleMove :
    public Component
{
public:
    enum class MoveType
    {
        BY_DIRECTION,
        BY_DESTINATION_TIME,
        BY_DESTINATION_SPEED,
        NONE
    };


    MoveType presentMoveType;
    float speed;
    float duration;
    glm::vec3 direction;
    glm::vec3 destination;
private:
    glm::vec3 m_StartPosition;
    float m_PresentDuration;
public:

    SimpleMove(Object* object);

    virtual void OnUpdate();

    void MoveToBySpeed(glm::vec3 destination, float speed);

    void MoveToByTime(glm::vec3 destination, float duration);
};

