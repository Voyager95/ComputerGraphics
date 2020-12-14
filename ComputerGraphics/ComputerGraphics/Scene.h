#pragma once
#include "stdafx.h"

class Object;
class Component;

class Scene
{
public:
	std::list<Object*> objects;
	std::list<Object*> toRemove;
private:
	bool m_IsActivatedScene;
public:
	//--- Getter
	bool GetIsActivatedScene() { return m_IsActivatedScene; }

	//--- Setter
	void SetIsActivatedScene(bool value) { m_IsActivatedScene = value; }

	//--- Constructor
	Scene();

	//--- Destorctor
	virtual ~Scene();

	void AddObject(Object* object);
	void SubObject(Object* object, bool toDelete = true); // *현재는 그냥 바로 삭제하게 되었습니다.

	virtual void OnCreate();			// 이 씬이 시작될 때, 불리는 함수입니다.
	virtual void OnUpdate();			// 업데이트 마다 불리는 함수 입니다. 	

	void ClearToRemove();
};

