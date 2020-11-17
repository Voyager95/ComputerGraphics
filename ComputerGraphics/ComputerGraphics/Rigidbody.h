#pragma once
#include "stdafx.h"
#include "Component.h"

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
    Rigidbody(std::shared_ptr<Object> object);
};

