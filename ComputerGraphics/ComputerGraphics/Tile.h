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
    TileType type;          // �� Ÿ���� Ÿ��
    float angle;            // �� Ÿ���� �߽� �����Դϴ�. 

    Tile(Object* object);

    virtual void OnCreate();

    virtual void OnUpdate();
};

