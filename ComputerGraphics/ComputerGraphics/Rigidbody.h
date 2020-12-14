#pragma once
#include "stdafx.h"
#include "Component.h"

static float GRAVITY = -9.8;

class Object;

/// <summary>
/// �Ķ���� ����
/// -�浹ó���� �Ҳ���?
/// -�浹ü ũ�� ����
/// -�߷�ũ��
/// </summary>
class Rigidbody :
    public Component
{
public:
    bool gravity;                       // �߷��� �������� üũ�մϴ�.
    float gravityMultiples;              // �߷� ���� ����Դϴ�.
    bool gravityLimit;                  // Ư�� �ӷ��� �Ǹ� �߷��� ���̻� �������� ���� ���Դϴ�.
    float gravitylimitSpeed;            // gravityLimit �ִ� ���ǵ�
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

