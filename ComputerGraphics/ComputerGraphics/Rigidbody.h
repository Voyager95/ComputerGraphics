#pragma once
#include "stdafx.h"
#include "Component.h"

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
    Rigidbody(std::shared_ptr<Object> object);
};

