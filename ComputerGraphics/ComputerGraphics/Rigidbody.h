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
private:
    glm::vec3 m_presentDirecttion;
public:
    bool gravity;                       // �߷��� �������� üũ�մϴ�.

    //--- Getter
    glm::vec3 GetPresentDirection() { return m_presentDirecttion; }

    Rigidbody(Object* object);

    void AddForce(glm::vec3 direction);

    virtual void OnUpdate();
};

