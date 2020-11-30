#pragma once
#include "stdafx.h"
#include "Component.h"

class Object;

static glm::vec3 gravity = glm::vec3(0, -9.8, 0);

/// <summary>
/// 파라미터 설정
/// -충돌처리를 할꺼니?
/// -충돌체 크기 설정
/// -중력크기
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

