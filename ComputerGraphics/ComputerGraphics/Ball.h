#pragma once
#include "Component.h"

class Object;

class Ball :
    public Component
{
public:
    float radius;                   // ���� �����Դϴ�.
    float maxSpeed;                 // �ְ� �ӵ�
    glm::vec3 slowSpeedColor;       // ���� ���� ��
    glm::vec3 fastSpeedColor;       // ���� ���� ��
    glm::vec3 maxSpeedColor;        // �ְ� ���� ���� ��
private:
    int m_HitPoint;                 // ���� ü���Դϴ�.
public:
    
    Ball(Object* object);

    /// <summary>
    /// ���� �״°�� ȣ���մϴ�.
    /// </summary>
    void Damage();

    /// <summary>
    /// ƨ�ܾ��ϴ� ��� ȣ���մϴ�.
    /// </summary>
    void Bounce();

    virtual void OnUpdate();

private:
    /// <summary>
    /// �� �ı��Ǵ� ��� ȣ���մϴ�.
    /// </summary>
    void Death();
};

