#pragma once
#include "Component.h"

class Object;

class Ball :
    public Component
{
public:
    float radius;                   // 공의 지름입니다.
    float maxSpeed;                 // 최고 속도
    glm::vec3 slowSpeedColor;       // 느린 공의 색
    glm::vec3 fastSpeedColor;       // 빠른 공의 색
    glm::vec3 maxSpeedColor;        // 최고 빠른 공의 색
private:
    int m_HitPoint;                 // 공의 체력입니다.
public:
    
    Ball(Object* object);

    /// <summary>
    /// 공이 죽는경우 호출합니다.
    /// </summary>
    void Damage();

    /// <summary>
    /// 튕겨야하는 경우 호출합니다.
    /// </summary>
    void Bounce();

    virtual void OnUpdate();

private:
    /// <summary>
    /// 공 파괴되는 경우 호출합니다.
    /// </summary>
    void Death();
};

