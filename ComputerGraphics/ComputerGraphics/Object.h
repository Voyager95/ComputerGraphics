#pragma once
#include "stdafx.h"

class Component;
class Transform;
class Renderer;
class Scene;

class Object : public std::enable_shared_from_this<Object>
{
public:
	std::string name;
	std::string tag;
private:
	bool m_TransformExist;
	bool m_IsAddedScene;

	std::list<Component*> m_Components;
	std::queue<Component*> m_OnCreateComponents;
	Transform* m_Transform;

	Scene* m_BelongingScene;
public:

	//-- Constructor
	Object();
	Object(std::string name);
	~Object();

	//---Getter
	Transform* GetTransform() { return m_Transform; }
	std::list<Component*> GetComponents() { return m_Components; }
	bool GetIsAddedScene() { return m_IsAddedScene; }
	Scene* GetBelongingScene() { return m_BelongingScene; }

	//---Setter
	void SetIsAddedScene(bool value) { m_IsAddedScene = value; }

	template <typename T>
	T* GetComponent();

	template<typename T>
	T* AddComponent();

	void OnAddTransform(Transform* transform);
	void AddComponent(Component* component);

	void SubObject();

	/// <summary>
	/// ������Ʈ���� OnCreate�Լ��� ȣ���մϴ�.
	/// </summary>
	void OnCreate();

	/// <summary>
	/// ������Ʈ���� OnUpdate�Լ��� ȣ���մϴ�.
	/// </summary>
	void OnUpdate();

	/// <summary>
	/// ������Ʈ���� OnLateUpdate�Լ��� ȣ���մϴ�.
	/// </summary>
	void OnLateUpdate();

	/// <summary>
	/// ������Ʈ���� OnPreDraw�Լ��� ȣ���մϴ�.
	/// </summary>
	void OnPreRender();

	/// <summary>
	/// ������Ʈ���� OnAddScene�Լ��� ȣ���մϴ�.
	/// </summary>
	void OnAddScene(Scene* scene);

	/// <summary>
	/// ������Ʈ���� OnSubScene�Լ��� ȣ���մϴ�.
	/// </summary>
	void OnSubScene();
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
