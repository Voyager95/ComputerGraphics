#pragma once
#include "Scene.h"

class Object;

/// <summary>
/// 볼을 생성합니다.
/// </summary>
/// <returns></returns>
Object* InstantiateBall();

/// <summary>
/// 타일을 생성합니다.
/// </summary>
/// <returns></returns>
Object* InstantiateBlackTile();

/// <summary>
/// 커지는 아이템을 생성합니다.
/// </summary>
/// <returns></returns>
Object* InstantiateBiggerItem();

Object* InstantiateLighterItem();

/// <summary>
/// 타워를 생성합니다.
/// </summary>
Object* InstantiateTower();

class TermProject :
    public Scene
{
public:
    TermProject();
};

