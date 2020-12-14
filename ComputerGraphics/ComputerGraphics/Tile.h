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
    TileType type;          // �� Ÿ���� Ÿ��
    float angle;            // �� Ÿ���� �߽� �����Դϴ�. 

    Tile(Object* object);

    void Destory();

    virtual void OnCreate();

    virtual void OnUpdate();
public:
    static Object* InstantiateRedFragTile();
    static Object* InstantiateBlackFragTile();
};

