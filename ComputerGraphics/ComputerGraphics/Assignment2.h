#pragma once
#include "Scene.h"
#include "stdafx.h"
#include "Component.h"

class Object;

Object* CreateRobot();

class Assignment2 :
    public Scene
{
public:
    Assignment2();
};

class CameraController :
    public Component
{
private:
    bool isThirdPersonView;

public:
    float dz;
    float dx;
    float dc;

    CameraController(Object* object);

    virtual void OnCreate();
    virtual void OnUpdate();
private:
    void FirstPersonView();
    void ThirdPersonView();
};

class Player :
    public Component
{
public:
    float dx;
    float dz;

    Player(Object* object);

    virtual void OnUpdate();
};

class Robot :
    public Component
{   
public:
    float detectDistance;
    std::vector<glm::vec3> patrolPoint;
private:
    bool m_IsDetectedPlayer;
    bool m_enoughDistance;
    float m_Timer;
    int m_PatrolPointTargetIndex;
public:
    Robot(Object* object);

    void LookAt(glm::vec3 targetPos);
    void LookAt(Object* target);

    virtual void OnUpdate();
};