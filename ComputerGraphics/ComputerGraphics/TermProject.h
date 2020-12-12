#pragma once
#include "Scene.h"


#define TILENUMPERDDISC 8
#define DISCNUMPERTOWER 8

#define TOWERHEIGHT 85

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
    //--- Ball
    Object* m_Ball;

    //--- Tower
    float m_TowerRotateSpeed = 200;
    std::vector<Object*> m_Tower; 
public:
    //--- Seting

    int towerInstantiateOffset = 60;

    /// <summary>
    /// �̸� ������ ���� ��ũ �����Դϴ�.
    /// </summary>
    std::vector<std::array<TileGenerate, TILENUMPERDDISC>> discSetting;

    /// <summary>
    /// ��ũ ������ �����Դϴ�.
    /// �̸� Ȱ���Ͽ� Ÿ���� �����մϴ�.
    /// </summary>
    std::vector<std::array<int, DISCNUMPERTOWER>> discList;

    //--- ������

    TermProject();

    //--- �̺�Ʈ �Լ�

    virtual void OnUpdate();

    //--- �⺻ �Լ�

    /// <summary>
    /// �÷��̾� ��ġ�� Ȯ���ϸ鼭 �ʿ��� ��� Ÿ���� ������ �ݴϴ�.
    /// </summary>
    void SpawnTower();

    //--- ���� �Լ�

    /// <summary>
    /// ��ũ ������ �ʱ�ȭ�մϴ�.
    /// </summary>
    void InitializeDiscSetting();

    /// <summary>
    /// ��ũ���õ��� ������ �ʱ�ȭ�մϴ�.
    /// </summary>
    void InitializeDiscCombination();

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
    /// Ÿ���� �����մϴ�. �������� �����մϴ�.
    /// </summary>
    Object* InstantiateTower();

    /// <summary>
    /// Ÿ���� �����մϴ�. Ư�� �ε����� ������� �����մϴ�.
    /// </summary>
    /// <param name="index">discCombination�� �ε����Դϴ�.</param>
    /// <returns></returns>
    Object* InstantiateTower(int index);

    /// <summary>
    /// Ÿ�ϵ��� ����, ��ũ�� �����մϴ�. 
    /// ���ڷ� ���� ����Ʈ���� 0�� ���� �����Ͽ� 45���� Y�� ȸ���� �Ͽ� ��ġ�˴ϴ�.
    /// </summary>
    /// <returns>Ÿ�ϵ��� �θ� ��ȯ�մϴ�.</returns>
    Object* InstantiateDisc(std::array<TileGenerate, TILENUMPERDDISC> discSetting);
};

