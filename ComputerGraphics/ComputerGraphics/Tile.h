#pragma once
#include "Component.h"

enum class TileType
{
    BLACK,
    RED
};

class Tile :
    public Component
{
public:
    TileType type;          // 이 타일의 타입
    float angle;            // 이 타일의 중심 각도입니다. 

    Tile(Object* object);

    virtual void OnCreate();

    virtual void OnUpdate();
};

