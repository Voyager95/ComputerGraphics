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

	std::list<Component*> m_Components;
	std::queue<Component*> m_OnCreateComponents;
	Transform* m_Transform;
public:

	//-- Constructor
	Object();
	Object(std::string name);
	~Object();

	//---Getter
	Transform* GetTransform() { return m_Transform; }
	std::list<Component*> GetComponents() { return m_Components; }

	template <typename T>
	T* GetComponent();

	template<typename T>
	T* AddComponent();

	void OnAddTransform(Transform* transform);
	void AddComponent(Component* component);

	/// <summary>
	/// 컴포넌트들의 OnCreate함수를 호출합니다.
	/// </summary>
	void OnCreate();

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

template<typename T>
T* Object::GetComponent()
{
	for (auto c = m_Components.begin(); c != m_Components.end(); ++c)
	{
		auto result = dynamic_cast<T*>(*c);
		if (result != nullptr)
			return result;
	}
	return nullptr;
}

template<typename T>
T* Object::AddComponent()
{
	auto component = new T(this);
	AddComponent(component);
	return component;
}
