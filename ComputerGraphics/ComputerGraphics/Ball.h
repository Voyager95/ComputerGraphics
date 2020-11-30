#pragma once
#include "Component.h"

class Object;

class Ball :
    public Component
{
public:
    float radius;                   // ���� �����Դϴ�.
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

private:
    /// <summary>
    /// �� �ı��Ǵ� ��� ȣ���մϴ�.
    /// </summary>
    void Death();
};

