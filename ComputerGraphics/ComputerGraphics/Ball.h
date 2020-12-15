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
    float invincibilityDuration;    // �󸶸�ŭ �ִ�ӵ��� �����ؾ� ������ �����
    float radius;                   // ���� �����Դϴ�.
    float maxSlowSpeed;             // ���� �ӵ� ���
    float maxFastSpeed;             // �ְ� �ӵ� ����
    glm::vec3 defaultColor;         // �⺻ ���� ��
    glm::vec3 slowSpeedColor;       // ���� ���� ��
    glm::vec3 fastSpeedColor;       // ���� ���� ��
    glm::vec3 maxSpeedColor;        // �ְ� ���� ���� ��
private:
    int m_HitPoint;                 // ���� ü���Դϴ�.
    bool m_IsInvincibility;         // �������� ��Ÿ���ϴ�.

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
    /// ���� �״°�� ȣ���մϴ�.
    /// </summary>
    void Damage(Tile* tile);

    /// <summary>
    /// ƨ�ܾ��ϴ� ��� ȣ���մϴ�.
    /// </summary>
    void Bounce(Tile* tile);

    void Bigger(Tile* tile);

    void Lighter(Tile* tile);

    virtual void OnUpdate();

private:
    /// <summary>
    /// �� �ı��Ǵ� ��� ȣ���մϴ�.
    /// </summary>
    void Death();
};

