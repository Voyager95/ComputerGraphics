#pragma once
#include "Scene.h"

class Object;

/// <summary>
/// ���� �����մϴ�.
/// </summary>
/// <returns></returns>
Object* InstantiateBall();

/// <summary>
/// Ÿ���� �����մϴ�.
/// </summary>
/// <returns></returns>
Object* InstantiateBlackTile();

/// <summary>
/// Ŀ���� �������� �����մϴ�.
/// </summary>
/// <returns></returns>
Object* InstantiateBiggerItem();

Object* InstantiateLighterItem();

/// <summary>
/// Ÿ���� �����մϴ�.
/// </summary>
Object* InstantiateTower();

class TermProject :
    public Scene
{
public:
    TermProject();
};

