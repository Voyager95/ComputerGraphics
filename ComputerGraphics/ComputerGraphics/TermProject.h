#pragma once
#include "Scene.h"


#define TILENUMPERDDISC 8
#define DISCNUMPERTOWER 8

class Object;

enum class TileGenerate
{
    NONE,
    BLACK,
    RED
};

class TermProject :
    public Scene
{
private:
    //--- Tower
    float m_TowerRotateSpeed = 20;
    std::vector<Object*> m_Tower;
public:

    /// <summary>
    /// 미리 설정해 놓은 디스크 세팅입니다.
    /// </summary>
    std::vector<std::array<TileGenerate, TILENUMPERDDISC>> discSetting;

    /// <summary>
    /// 디스크 세팅의 조합입니다.
    /// 이를 활용하여 타워를 생성합니다.
    /// </summary>
    std::vector<std::array<int, DISCNUMPERTOWER>> discList;

    TermProject();

    virtual void OnUpdate();

    /// <summary>
    /// 디스크 세팅을 초기화합니다.
    /// </summary>
    void InitializeDiscSetting();

    /// <summary>
    /// 디스크세팅들의 조합을 초기화합니다.
    /// </summary>
    void InitializeDiscCombination();

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
    /// 타워를 생성합니다. 랜덤으로 생성합니다.
    /// </summary>
    Object* InstantiateTower();

    /// <summary>
    /// 타워를 생성합니다. 특정 인덱스를 기반으로 생성합니다.
    /// </summary>
    /// <param name="index">discCombination의 인덱스입니다.</param>
    /// <returns></returns>
    Object* InstantiateTower(int index);

    /// <summary>
    /// 타일들의 모음, 디스크를 생성합니다. 
    /// 인자로 받은 리스트들은 0도 부터 시작하여 45도씩 Y축 회전을 하여 배치됩니다.
    /// </summary>
    /// <returns>타일들의 부모를 반환합니다.</returns>
    Object* InstantiateDisc(std::array<TileGenerate, TILENUMPERDDISC> discSetting);
};

