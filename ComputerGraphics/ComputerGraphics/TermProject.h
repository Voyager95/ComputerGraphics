#pragma once
#include "Scene.h"

class Object;

/// <summary>
/// ���� �����մϴ�.
/// </summary>
/// <returns></returns>
Object* InstantiateBall();

/// <summary>
/// ���� Ÿ���� �����մϴ�.
/// </summary>
/// <returns></returns>
Object* InstantiateBlackTile();

/// <summary>
/// ���� Ÿ���� �����մϴ�.
/// </summary>
/// <returns></returns>
Object* InstantiateRedTile();

/// <summary>
/// Ŀ���� �������� �����մϴ�.
/// </summary>
/// <returns></returns>
Object* InstantiateBiggerItem();

/// <summary>
/// ������ ���� �������� �����մϴ�.
/// </summary>
/// <returns></returns>
Object* InstantiateLighterItem();

/// <summary>
/// Ÿ���� �����մϴ�.
/// </summary>
Object* InstantiateTower();

/// <summary>
/// Ÿ�ϵ��� ����, ��ũ�� �����մϴ�.
/// </summary>
/// <returns></returns>
Object* InstnatiateDisc();

class TermProject :
    public Scene
{
private:
    //--- Tower
    float m_TowerRotateSpeed = 10;
    std::vector<Object*> m_Tower;
public:
    TermProject();

    virtual void OnUpdate();
};

