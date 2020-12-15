#pragma once
#include "Component.h"

class Object;
class Tile;
class ModelInstance;

class Ball :
    public Component
{
public:
    float itemTimer;
    float invincibilityDuration;    // 얼마만큼 최대속도를 유지해야 무적을 얻는지
    float radius;                   // 공의 지름입니다.
    float maxSlowSpeed;             // 최저 속도 양수
    float maxFastSpeed;             // 최고 속도 음수
    glm::vec3 defaultColor;         // 기본 공의 색
    glm::vec3 slowSpeedColor;       // 느린 공의 색
    glm::vec3 fastSpeedColor;       // 빠른 공의 색
    glm::vec3 maxSpeedColor;        // 최고 빠른 공의 색
private:
    int m_HitPoint;                 // 공의 체력입니다.
    bool m_IsInvincibility;         // 무적인지 나타냅니다.

    float m_BiggerTimer;
    bool m_Bigger;
    float m_LighterTimer;
    bool m_Lighter;

    float m_MaxSpeedTimer;

    std::shared_ptr<ModelInstance> m_Model;
public:
    
    Ball(Object* object);
    ~Ball();

    /// <summary>
    /// 공이 죽는경우 호출합니다.
    /// </summary>
    void Damage(Tile* tile);

    /// <summary>
    /// 튕겨야하는 경우 호출합니다.
    /// </summary>
    void Bounce(Tile* tile);

    void Bigger(Tile* tile);

    void Lighter(Tile* tile);

    virtual void OnUpdate();

private:
    /// <summary>
    /// 공 파괴되는 경우 호출합니다.
    /// </summary>
    void Death();
};

