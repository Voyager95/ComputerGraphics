#include "stdafx.h"
#include "RigidbodySystem.h"

RigidbodySystem& RigidbodySystem::GetInstance()
{
    static RigidbodySystem instance;
    return instance;
}

RigidbodySystem::RigidbodySystem()
{
    
}
