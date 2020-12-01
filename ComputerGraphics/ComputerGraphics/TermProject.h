#pragma once
#include "Scene.h"

class Object;

/// <summary>
/// 볼을 생성합니다.
/// </summary>
/// <returns></returns>
Object* InstantiateBall();

/// <summary>
/// 검정 타일을 생성합니다.
/// </summary>
/// <returns></returns>
Object* InstantiateBlackTile();

/// <summary>
/// 빨간 타일을 생성합니다.
/// </summary>
/// <returns></returns>
Object* InstantiateRedTile();

/// <summary>
/// 커지는 아이템을 생성합니다.
/// </summary>
/// <returns></returns>
Object* InstantiateBiggerItem();

/// <summary>
/// 가벼워 지는 아이템을 생성합니다.
/// </summary>
/// <returns></returns>
Object* InstantiateLighterItem();

/// <summary>
/// 타워를 생성합니다.
/// </summary>
Object* InstantiateTower();

/// <summary>
/// 타일들의 모음, 디스크를 생성합니다.
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

