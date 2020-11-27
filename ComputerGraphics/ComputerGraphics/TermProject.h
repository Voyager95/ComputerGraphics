#pragma once
#include "Scene.h"
#include "Component.h"

class Object;

Object* CreateObject();

class TermProject :
    public Scene
{
public:
    TermProject();
};

class CameraController :
    public Component
{
private:
    bool isThirdPersonView;

public:

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
    float m_Timer;
    int m_PatrolPointTargetIndex;
public:
    Robot(Object* object);

    virtual void OnUpdate();
};