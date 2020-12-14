#include "stdafx.h"
#include "Frag.h"
#include "Object.h"
#include "SceneSystem.h"
#include "Scene.h"

Frag::Frag(Object* object) : Component(object)
{
	//--- Flag √ ±‚»≠
	duration = 5;
	timer = 0;
}

void Frag::OnUpdate()
{
	SceneSystem& ss = SceneSystem::GetInstance();
	auto presentScene = ss.GetPresentScene();

	timer += DELTATIME;


	if (duration < timer)
	{
		presentScene->SubObject(GetBelongingObject());
	}
}
