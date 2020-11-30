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
private:
    glm::vec3 m_presentDirecttion;
public:
    bool gravity;                       // 중력을 적용할지 체크합니다.

    Rigidbody(Object* object);

    void AddForce(glm::vec3 direction);

    virtual void OnUpdate();
};

