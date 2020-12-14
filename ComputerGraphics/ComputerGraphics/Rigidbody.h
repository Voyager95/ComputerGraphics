#pragma once
#include "stdafx.h"
#include "Component.h"

static float GRAVITY = -9.8;

class Object;

/// <summary>
/// 파라미터 설정
/// -충돌처리를 할꺼니?
/// -충돌체 크기 설정
/// -중력크기
/// </summary>
class Rigidbody :
    public Component
{
public:
    bool gravity;                       // 중력을 적용할지 체크합니다.
    float gravityMultiples;              // 중력 적용 배수입니다.
    bool gravityLimit;                  // 특정 속력이 되면 중력을 더이상 적용하지 않을 것입니다.
    float gravitylimitSpeed;            // gravityLimit 최대 스피드
private:
    glm::vec3 m_presentDirection;
    glm::vec3 m_Torque;
public:
    //--- Setter
    void SetPresentDirection(glm::vec3 value) { m_presentDirection = value; }


    //--- Getter
    glm::vec3 GetPresentDirection() { return m_presentDirection; }

    Rigidbody(Object* object);

    void AddForce(glm::vec3 direction);

    void AddTorque(glm::vec3 direction);

    virtual void OnUpdate();
};

