#pragma once
#include "stdafx.h"

class Component;
class Transform;
class Renderer;

class Object : public std::enable_shared_from_this<Object>
{
public:
	std::string name;
	std::string tag;
private:
	bool m_TransformExist;

	std::list<std::shared_ptr<Component>> m_Components;
	std::shared_ptr<Transform> m_Transform;
public:

	//-- Constructor
	Object();
	Object(std::string name);
	~Object();

	//---Getter
	std::shared_ptr<Transform> GetTransform() { return m_Transform; }
	std::list<std::shared_ptr<Component>> GetComponents() { return m_Components; }

	template<class T>
	std::shared_ptr<T> AddComponent();

	void OnAddTransform();
	void AddComponent(std::shared_ptr<Component> component);

	/// <summary>
	/// 컴포넌트들의 OnUpdate함수를 호출합니다.
	/// </summary>
	void OnUpdate();

	/// <summary>
	/// 컴포넌트들의 OnLateUpdate함수를 호출합니다.
	/// </summary>
	void OnLateUpdate();

	/// <summary>
	/// 컴포넌트들의 OnPreDraw함수를 호출합니다.
	/// </summary>
	void OnPreRender();
};
