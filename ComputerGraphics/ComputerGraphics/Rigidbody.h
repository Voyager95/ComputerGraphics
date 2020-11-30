#pragma once
#include "stdafx.h"
#include "Component.h"

class Object;

static glm::vec3 gravity = glm::vec3(0, -9.8, 0);

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

    Rigidbody(Object* object);

    void AddForce(glm:vec3 direction);

    virtual void OnUpdate();
};

