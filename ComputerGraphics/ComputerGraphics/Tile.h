#pragma once
#include "Component.h"

enum class TileType
{
    BLACK,
    RED,
    LIGHTER,
    BIGGER,
};

class Tile :
    public Component
{
public:
    TileType type;          // 이 타일의 타입
    float angle;            // 이 타일의 중심 각도입니다. 

    Tile(Object* object);

    void Destory();

    virtual void OnCreate();

    virtual void OnUpdate();
public:
    static Object* InstantiateRedFragTile();
    static Object* InstantiateBlackFragTile();
};

